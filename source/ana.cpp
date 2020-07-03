#define ana_cxx
#include "ana.h"
#include <iostream>
#include <time.h>
#include <fstream>
#include <TLorentzVector.h>
#include <fstream>
#include <iostream>
using namespace std;
///////////////////////////////////////////////////below is universal functions for help////////////////////////////////////////////////
void ana::Find_Z_pair()
{
   int i,j;
   vector<int>::iterator iter;
   pair<int, int> Z_pair_temp(-1,-1);
   for(i=0; i<v_l_pid.size(); i++)
   {
      if(find(v_ignore.begin(),v_ignore.end(),i)!= v_ignore.end()) continue;
      for(j=i+1; j<v_l_pid.size(); j++)
      {
         if(find(v_ignore.begin(),v_ignore.end(),j)!= v_ignore.end())    continue;
         if(v_l_pid[i]+v_l_pid[j]!=0) continue;
         if(Z_pair_temp.first<0 || Z_pair_temp.second<0){ Z_pair_temp= make_pair(i,j); continue;}
         if(abs((v_l_tlv[i]+v_l_tlv[j]).M()-Z_mass) < abs((v_l_tlv[Z_pair_temp.first]+v_l_tlv[Z_pair_temp.second]).M()-Z_mass))
            Z_pair_temp= make_pair(i,j);
      }
   }
   if(v_l_tlv[Z_pair_temp.first].Pt()<v_l_tlv[Z_pair_temp.second].Pt()) Z_pair_temp= make_pair(Z_pair_temp.second,Z_pair_temp.first);
   if(Z_pair_temp!= make_pair(-1,-1))
   {
      v_ignore.insert(v_ignore.end(),Z_pair_temp.first);
      v_ignore.insert(v_ignore.end(),Z_pair_temp.second);
      v_Z_pair.insert(v_Z_pair.end(),Z_pair_temp);
      float Z_wgt= v_l_wgt[Z_pair_temp.first] * v_l_wgt[Z_pair_temp.second];
      v_Z_wgt.insert(v_Z_wgt.end(),Z_wgt);
   }
};

bool ana::initial_Cut()
{
   wgt= weight*w_sf_jvt/v_sumofwgt[file_iter]*v_lumi[file_iter]*v_xs_eff[file_iter];
   cutflow("initial").pass("initial","All",wgt);
   // lepton number > 3
   if(v_l_pid.size()<=3) return false;
   cutflow("initial").pass("initial",">3l",wgt);
   // at least one SFOS pair
   Find_Z_pair();
   Find_Z_pair();
   Find_Z_pair();
   if(v_Z_pair.size()==0) return false;
   cutflow("initial").pass("initial","1_SFOS",wgt*v_Z_wgt[0]);
   // Z window 15 GeV
   if(abs((v_l_tlv[v_Z_pair[0].first]+v_l_tlv[v_Z_pair[0].second]).M()-Z_mass)>15e3) return false;
   cutflow("initial").pass("initial","Z_window",wgt*v_Z_wgt[0]);
   // lepton number information
   int nlepton=v_l_pid.size();
   if(nlepton>6) cutflow("initial").pass("initial",">6l",wgt*v_Z_wgt[0]);
   if(nlepton==6) cutflow("initial").pass("initial","6l",wgt*v_Z_wgt[0]);
   if(nlepton==5) cutflow("initial").pass("initial","5l",wgt*v_Z_wgt[0]);
   if(nlepton==4) cutflow("initial").pass("initial","4l",wgt*v_Z_wgt[0]);
   return true;
}

void ana::Bjet_Cut(string s_flow, string s_cut, float wgt_base)
{
   bool btag_veto;
   float btag_wgt;
   int njet=v_j_tlv->size();

   btag_wgt=1;
   btag_veto=true;
   for(int i=0;i<njet;i++)
   {
      if(v_j_btag60->at(i)) btag_veto=false;
      btag_wgt*=v_j_wgt_btag60->at(i);
   }
   if(btag_veto) cutflow(s_flow).pass(s_cut,"B_veto60",wgt_base*btag_wgt);

   btag_wgt=1;
   btag_veto=true;
   for(int i=0;i<njet;i++)
   {
      if(v_j_btag70->at(i)) btag_veto=false;
      btag_wgt*=v_j_wgt_btag70->at(i);
   }
   if(btag_veto) cutflow(s_flow).pass(s_cut,"B_veto70",wgt_base*btag_wgt);

   btag_wgt=1;
   btag_veto=true;
   for(int i=0;i<njet;i++)
   {
      if(v_j_btag77->at(i)) btag_veto=false;
      btag_wgt*=v_j_wgt_btag77->at(i);
   }
   if(btag_veto) cutflow(s_flow).pass(s_cut,"B_veto77",wgt_base*btag_wgt);

   btag_wgt=1;
   btag_veto=true;
   for(int i=0;i<njet;i++)
   {
      if(v_j_btag85->at(i)) btag_veto=false;
      btag_wgt*=v_j_wgt_btag85->at(i);
   }
   if(btag_veto) cutflow(s_flow).pass(s_cut,"B_veto85",wgt_base*btag_wgt);
}

void ana::lepton_pt_sort()
{
   int temp;
   for(int i=0;i<v_l_pid.size();i++)
      v_l_order.insert(v_l_order.end(),i);
   for(int i=0;i<v_l_pid.size();i++)   
      for(int j=i+1;j<v_l_pid.size();j++)      
         if(v_l_tlv[v_l_order[i]].Pt()<v_l_tlv[v_l_order[j]].Pt())
         {
            temp=v_l_order[i];
            v_l_order[i]=v_l_order[j];
            v_l_order[j]=temp;
         }  
}
////////////////////////////////////////////////below is major part of ana///////////////////////////////////////////////////////////
////////////////////////////////////////////////////constructors/////////////////////////////////////////////////////////////////////
ana::ana(TTree* tree): ana_base(tree){}

ana::ana(TTree* tree, TString output_file_name, vector<float> iv_sumofwgt, vector<float>iv_lumi, vector<float>iv_xs_eff): 
   ana_base(tree),
   _output_file_name(output_file_name),
   v_sumofwgt(iv_sumofwgt),
   v_lumi(iv_lumi),
   v_xs_eff(iv_xs_eff){}
//////////////////////////////////////////////////////cutflow///////////////////////////////////////////////////////////////////////
CutFlowTool& ana::cutflow(string s, bool ini)
{
   if(ini) m_CutFlowTool.emplace(s,s);
   return m_CutFlowTool.at(s);
}
/////////////////////////////////////////////////////histogram//////////////////////////////////////////////////////////////////////
TH1F* ana::makehist(TString s, bool ini)
{
   if(ini) m_hist.emplace(s,new TH1F(s,s,20,0,400));
   return m_hist.at(s);
}

void ana::channel_makehist(TString channel_name, int nZ)
{
   if(nZ>3) return;
   TString s_number[3]={"first","second","third"};
   for(int i=0;i<nZ;i++)
   {
      makehist(channel_name+"_Z_mass_"+s_number[i],true);
      makehist(channel_name+"_Z_pt_"+s_number[i],true);
   }
   makehist(channel_name+"_leading_lepton_pt",true);
   makehist(channel_name+"_subleading_lepton_pt",true);
}

void ana::channel_fillhist(TString channel_name, int nZ, float fill_wgt)
{
   if(nZ>3) return;
   TString s_number[3]={"first","second","third"};
   TLorentzVector Z_tlv;
   for(int i=0;i<nZ;i++)
   {
      Z_tlv=v_l_tlv[v_Z_pair[i].first]+v_l_tlv[v_Z_pair[i].second];
      makehist(channel_name+"_Z_mass_"+s_number[i])->Fill(Z_tlv.M()/1000,fill_wgt);
      makehist(channel_name+"_Z_pt_"+s_number[i])->Fill(Z_tlv.Pt()/1000,fill_wgt);
   }
   makehist(channel_name+"_leading_lepton_pt")->Fill(v_l_tlv[v_l_order[0]].Pt()/1000,fill_wgt);
   makehist(channel_name+"_subleading_lepton_pt")->Fill(v_l_tlv[v_l_order[1]].Pt()/1000,fill_wgt);

}
/////////////////////////////////////////////////////////////////Loop///////////////////////////////////////////////////
void ana::Loop()
{
   if (fChain == 0) return;
   Initialize();

   Long64_t nentries = fChain->GetEntriesFast();

   Long64_t nbytes = 0, nb = 0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;

      Loop_initialize();

      if(ientry%100000==0) std::cout<<"processing event: "<<ientry<<'\n';
//      if(ientry>100000) break;
      if(ientry==0)
      { 
         file_iter++;
         std::cout<<"#####################begin of file##################"<<'\n';
         std::cout<<"#sum of weight: "<<v_sumofwgt[file_iter]<<'\n';
         std::cout<<"#luminosity: "<<v_lumi[file_iter]<<'\n';
         std::cout<<"#cross section*efficiency: "<<v_xs_eff[file_iter]<<'\n';
         std::cout<<"#####################end of file####################"<<'\n';
      }
      if(initial_Cut()) 
      if(ZZZ_Cut())
      {
         ZZZ_operation();
      }
      else if(WZZ_Cut())
      {
         WZZ_operation();
      }
      else if(WWZ_Cut())
      {
         WWZ_operation();
      }

      Loop_terminate();
   }    
   Terminate();

} 

void ana::Loop_initialize()
{
   v_l_tlv.insert(v_l_tlv.end(), v_e_tlv->begin(), v_e_tlv->end());
   v_l_tlv.insert(v_l_tlv.end(), v_m_tlv->begin(), v_m_tlv->end());
   v_l_pid.insert(v_l_pid.end(), v_e_pid->begin(), v_e_pid->end());
   v_l_pid.insert(v_l_pid.end(), v_m_pid->begin(), v_m_pid->end());
   v_l_wgt.insert(v_l_wgt.end(), v_e_wgt->begin(), v_e_wgt->end());
   v_l_wgt.insert(v_l_wgt.end(), v_m_wgt->begin(), v_m_wgt->end());
   lepton_pt_sort();
}

void ana::Loop_terminate()
{
   v_l_tlv.clear();
   v_l_pid.clear();
   v_l_wgt.clear();
   v_l_order.clear();
   if(v_Z_pair.size()!=0)
   {
      v_Z_pair.clear();
      v_ignore.clear();
      v_Z_wgt.clear();
   }
}


void ana::Initialize()
{
   _output= new TFile("../plot/root/"+_output_file_name+".root","recreate");
   file_iter=-1;
   cutflow("initial",true)
      .regFlow("initial","initial selection")
      .regCut("All")
      .regCut(">3l")
      .regCut("1_SFOS")
      .regCut("Z_window")
      .regCut(">6l","",true)
      .regCut("6l","",true)
      .regCut("5l","",true)
      .regCut("4l","",true);   
   cutflow("ZZZ",true)
      .regFlow("ZZZ","cutflow of ZZZ channel")
      .regCut("3_SFOS")
      .regCut("ZZZ_>6l","",true)
      .regCut("ZZZ_6l","",true);
   cutflow("WZZ",true)
      .regFlow("WZZ","cutflow of WZZ channel")
      .regCut(">=5l")
      .regCut("2_SFOS")
      .regCut("Z_window")
      .regCut("B_veto60","",true)
      .regCut("B_veto70","",true)
      .regCut("B_veto77","",true)
      .regCut("B_veto85","",true)
      .regCut("WZZ_>6l","",true)
      .regCut("WZZ_6l","",true)
      .regCut("WZZ_5l","",true);
   cutflow("WWZ",true)
      .regFlow("WWZ","cutflow of WWZ channel")
      .regCut(">=4l")
      .regCut("Dilepton")
      .regCut("B_veto60","",true)
      .regCut("B_veto70","",true)
      .regCut("B_veto77","",true)
      .regCut("B_veto85","",true)
      .regCut("WWZ_>6l","",true)
      .regCut("WWZ_6l","",true)
      .regCut("WWZ_5l","",true)
      .regCut("WWZ_4l","",true);

   channel_makehist("ZZZ",3);
   channel_makehist("WZZ",2);
   channel_makehist("WWZ",1);
}

void ana::Terminate()
{
   std::ofstream _ofs_cutflow("./cutflowinfo/"+_output_file_name+".txt",std::ofstream::out);   
   cutflow("initial").print(_ofs_cutflow);
   cutflow("ZZZ").print(_ofs_cutflow);
   cutflow("WZZ").print(_ofs_cutflow);
   cutflow("WWZ").print(_ofs_cutflow);
   _ofs_cutflow.close();
   _output->Write("All");
   _output->Close();
}
