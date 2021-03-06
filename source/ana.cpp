#define ana_cxx
#include "ana.h"
#include <iostream>
#include <time.h>
#include <fstream>
#include <TLorentzVector.h>
#include <fstream>
#include <iostream>
#include "TString.h"
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
   wgt= weight/v_sumofwgt[fCurrent];
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
   // fill Z_mass_first Z_mass_second Z_mass_third
   TString s_number[3]={"first","second","third"};
   for(int i=0;i<v_Z_pair.size();i++)
   {
      TLorentzVector Z_tlv=v_l_tlv[v_Z_pair[i].first]+v_l_tlv[v_Z_pair[i].second];
      makehist("Z_mass_"+s_number[i])->Fill(Z_tlv.M()/1000,wgt);
   }

   // Z window 20 GeV
   if(abs((v_l_tlv[v_Z_pair[0].first]+v_l_tlv[v_Z_pair[0].second]).M()-Z_mass)>20e3) return false;
   cutflow("initial").pass("initial","Z_window",wgt*v_Z_wgt[0]);
   if(passTrig) cutflow("initial").pass("initial","passTrig",wgt*v_Z_wgt[0]);
   // find m4l
   Find_m4l();
   // forward electron
   n_e_fwd=0;
   for(int i=0;i<v_e_fwd->size();i++)
   {
      if((*v_e_fwd)[i]){n_e_fwd++;} 
   }
   if(n_e_fwd>0) cutflow("initial").pass("initial","e_fwd",wgt*v_Z_wgt[0]);
   if(n_e_fwd==1) cutflow("initial").pass("initial","e_fwd_1",wgt*v_Z_wgt[0]);
   // low pt muon
   n_m_lowpt=0;
   for(int i=0;i<v_m_lowpt->size();i++)
   {
      if((*v_m_lowpt)[i]){ n_m_lowpt++;}
   }
   if(n_m_lowpt>0) cutflow("initial").pass("initial","m_lowpt",wgt*v_Z_wgt[0]);
   if(n_m_lowpt==1) cutflow("initial").pass("initial","m_lowpt_1",wgt*v_Z_wgt[0]);
   if(n_e_fwd==0 && n_m_lowpt==0) cutflow("initial").pass("initial","no_fwde_lowptm",wgt*v_Z_wgt[0]);
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
   b_wgt[0]=btag_wgt;

   btag_wgt=1;
   btag_veto=true;
   for(int i=0;i<njet;i++)
   {
      if(v_j_btag70->at(i)) btag_veto=false;
      btag_wgt*=v_j_wgt_btag70->at(i);
   }
   if(btag_veto) cutflow(s_flow).pass(s_cut,"B_veto70",wgt_base*btag_wgt);
   b_wgt[1]=btag_wgt;

   btag_wgt=1;
   btag_veto=true;
   for(int i=0;i<njet;i++)
   {
      if(v_j_btag77->at(i)) btag_veto=false;
      btag_wgt*=v_j_wgt_btag77->at(i);
   }
   if(btag_veto) cutflow(s_flow).pass(s_cut,"B_veto77",wgt_base*btag_wgt);
   b_wgt[2]=btag_wgt;

   btag_wgt=1;
   btag_veto=true;
   for(int i=0;i<njet;i++)
   {
      if(v_j_btag85->at(i)) btag_veto=false;
      btag_wgt*=v_j_wgt_btag85->at(i);
   }
   if(btag_veto) cutflow(s_flow).pass(s_cut,"B_veto85",wgt_base*btag_wgt);
   b_wgt[3]=btag_wgt;
}

void ana::pt_sort(vector<TLorentzVector> v_tlv,vector<int>& v_order)
{
   int temp;
   int nparticle=v_tlv.size();
   for(int i=0;i<nparticle;i++)
      v_order.insert(v_order.end(),i);
   for(int i=0;i<nparticle;i++)   
      for(int j=i+1;j<nparticle;j++)      
         if(v_tlv[v_order[i]].Pt()<v_tlv[v_order[j]].Pt())
         {
            temp=v_order[i];
            v_order[i]=v_order[j];
            v_order[j]=temp;
         }  
}

void ana::Find_m4l_best()
{
   int nlepton=v_l_pid.size();
   int iter[4];
   TLorentzVector m4l_tlv = v_l_tlv[v_l_order[0]];
   for(int i=1;i<4;i++)
      m4l_tlv += v_l_tlv[v_l_order[i]];
   for(int i=0;i<4;i++)
      m4l[i]=v_l_order[i];
   for(iter[0]=0;iter[0]<nlepton;iter[0]++)
      for(iter[1]=iter[0]+1;iter[1]<nlepton;iter[1]++)
         for(iter[2]=iter[1]+1;iter[2]<nlepton;iter[2]++)
            for(iter[3]=iter[2]+1;iter[3]<nlepton;iter[3]++)
            {
               TLorentzVector temp_tlv=v_l_tlv[iter[0]];
               for(int i=1;i<4;i++)
                  temp_tlv += v_l_tlv[iter[i]];
               if(abs(temp_tlv.M()-Z_mass)<abs(m4l_tlv.M()-Z_mass))
               {
                  for(int i=0;i<4;i++)
                     m4l[i]=iter[i];
                  m4l_tlv=temp_tlv;
               }
            }   
   
}
bool ana::Find_m4l()
{
   m4l[0]=v_Z_pair[0].first;
   m4l[1]=v_Z_pair[0].second;
   int j=2;
   for(int i=0;i<v_l_pid.size() && j<4;i++)
   {
      if(v_l_order[i]==m4l[0] || v_l_order[i]==m4l[1]) continue;
      if(j==2) m4l[j]=v_l_order[i];
      if(j==3) {
        // TODO: For emu channel, can never find such m4l
        // if((v_l_pid[v_l_order[i]]+v_l_pid[m4l[2]])==0) m4l[j]=v_l_order[i];
        // else continue;
        m4l[j] = v_l_order[i];
      }
      j++;
   }
   // require 2SFOS
   if (j < 4) {
     mass_4l = -9999.;
     return false;
   }

   TLorentzVector tlv_4l;
   for(int i=0;i<4;i++) tlv_4l+=v_l_tlv[m4l[i]];
   mass_4l=tlv_4l.M();
   return true;
}
void ana::WWZ_chi2()
{
   // to reduce ZZ event
   TLorentzVector WWZ_tlv[4];
   WWZ_tlv[0]=v_l_tlv[v_Z_pair[0].first];
   WWZ_tlv[1]=v_l_tlv[v_Z_pair[0].second];
   WWZ_tlv[2]=v_l_tlv[W_id[0]];
   WWZ_tlv[3]=v_l_tlv[W_id[1]];
   chi2=999999;
   float temp;
   TLorentzVector Z1_tlv,Z2_tlv;
   for(int i=1; i<4; i++)
   {
      Z1_tlv=WWZ_tlv[0]+WWZ_tlv[i];
      for(int j=1; j<4; j++)
      {
         if(j==i) continue;
         Z2_tlv+=WWZ_tlv[j];
      }
      temp=((Z1_tlv.M()-Z_mass)*(Z1_tlv.M()-Z_mass)+(Z2_tlv.M()-Z_mass)*(Z2_tlv.M()-Z_mass))/(2495.2*2495.2);
      if(temp<chi2) chi2= temp;
   }
}
////////////////////////////////////////////////below is major part of ana///////////////////////////////////////////////////////////
////////////////////////////////////////////////////constructors/////////////////////////////////////////////////////////////////////
ana::ana(TTree* tree): ana_base(tree){}

ana::ana(TTree* tree, TString output_file, vector<float> iv_sumofwgt):
   ana_base(tree),
   _output_dir("../output/"),
   _output_file(output_file),
   v_sumofwgt(iv_sumofwgt){}

ana::ana(TTree* tree, TString output_dir, TString output_file, vector<float> iv_sumofwgt): 
   ana_base(tree),
   _output_dir(output_dir),
   _output_file(output_file),
   v_sumofwgt(iv_sumofwgt){}
//////////////////////////////////////////////////////cutflow///////////////////////////////////////////////////////////////////////
CutFlowTool& ana::cutflow(string s, bool ini)
{
   if(ini) m_CutFlowTool.emplace(s,s);
   return m_CutFlowTool.at(s);
}
/////////////////////////////////////////////////////histogram//////////////////////////////////////////////////////////////////////
TH1F* ana::makehist(TString s, bool ini, int nbin, float start, float end)
{
   if(ini) m_hist.emplace(s,new TH1F(s,s,nbin,start,end));
   return m_hist.at(s);
}
TH2F* ana::makehist2d(TString s, bool ini, int xbin, float xstart, float xend, int ybin, float ystart, float yend)
{
   if(ini) m_hist2d.emplace(s, new TH2F(s,s,xbin,xstart,xend,ybin,ystart,yend));
   m_hist2d.at(s)->SetOption("colz");
   return m_hist2d.at(s);
}

void ana::channel_makehist(TString channel_name, int nZ)
{
   makehist(channel_name+"_m4l",true,100,0,1000);
   if(nZ>3) return;
   TString s_number[3]={"first","second","third"};
   for(int i=0;i<nZ;i++)
   {
      makehist(channel_name+"_Z_mass_"+s_number[i],true,60,0,300);
      makehist(channel_name+"_Z_pt_"+s_number[i],true,60,0,300);
   }
   makehist(channel_name+"_MET",true,80,0,400);
   makehist(channel_name+"_METSig",true,80,0,40);
   makehist(channel_name+"_jet_number",true,20,0,20);
   for(int i=0;i<7;i++)
   {
      makehist(channel_name+"_lepton_pt_"+TString::Format("%d",i+1),true, 200, 0, 400);
      makehist(channel_name+"_lepton_eta_"+TString::Format("%d",i+1),true,30,-3,3);
   }
    makehist(channel_name+"_fwdele_pt", true, 200, 0, 400);
    makehist(channel_name+"_fwdele_eta", true,30,-3,3);
   for(int i=0;i<10;i++)
   {
      makehist(channel_name+"_jet_pt_"+TString::Format("%d",i+1),true);
      makehist(channel_name+"_jet_eta_"+TString::Format("%d",i+1),true,30,-3,3);
   }

}


void ana::channel_fillhist(TString channel_name, int nZ, float fill_wgt)
{
   if(nZ>3) {
     std::cerr << "got 4 Z?" << std::endl;
     return;
   }
   TString s_number[3]={"first","second","third"};
   TLorentzVector Z_tlv;
   int nlepton=v_l_tlv.size();
   int njet=v_j_tlv->size();
   makehist(channel_name+"_MET")->Fill(MET/1000,fill_wgt);
   makehist(channel_name+"_METSig")->Fill(METSig,fill_wgt);
   makehist(channel_name+"_m4l")->Fill(mass_4l/1000,fill_wgt);
   for(int i=0;i<nZ;i++)
   {
      Z_tlv=v_l_tlv[v_Z_pair[i].first]+v_l_tlv[v_Z_pair[i].second];
      makehist(channel_name+"_Z_mass_"+s_number[i])->Fill(Z_tlv.M()/1000,fill_wgt);
      makehist(channel_name+"_Z_pt_"+s_number[i])->Fill(Z_tlv.Pt()/1000,fill_wgt);
   }
   makehist(channel_name+"_jet_number")->Fill(njet,fill_wgt);
   for(int i=0;i<nlepton && i<7;i++)
   {
      makehist(channel_name+"_lepton_pt_"+TString::Format("%d",i+1))->Fill(v_l_tlv[v_l_order[i]].Pt()/1000,fill_wgt);
      makehist(channel_name+"_lepton_eta_"+TString::Format("%d",i+1))->Fill(v_l_tlv[v_l_order[i]].Eta(),fill_wgt);
   }
   for(int i=0;i<v_e_tlv->size() && i < 7; ++i) {
    if (!v_e_fwd->at(i)) continue;
      makehist(channel_name+"_fwdele_pt")->Fill(v_e_tlv->at(i).Pt()/1000,fill_wgt);
      makehist(channel_name+"_fwdele_eta")->Fill(v_e_tlv->at(i).Eta(),fill_wgt);
   }
   for(int i=0;i<njet && i<10;i++)
   {
      makehist(channel_name+"_jet_pt_"+TString::Format("%d",i+1))->Fill((*v_j_tlv)[v_j_order[i]].Pt()/1000,fill_wgt);
      makehist(channel_name+"_jet_eta_"+TString::Format("%d",i+1))->Fill((*v_j_tlv)[v_j_order[i]].Eta(),fill_wgt);
   }
}

void ana::WWZ_makehist(TString channel_name){
   makehist(channel_name+"_Zl_pt_1",true,200,0,400);
   makehist(channel_name+"_Zl_pt_2",true,200,0,400);
   makehist(channel_name+"_Wl_pt_1",true,200,0,400);
   makehist(channel_name+"_Wl_pt_2",true,200,0,400);
   makehist(channel_name+"_ZWl1_eta",true,30,-3,3);
   makehist(channel_name+"_ZWl2_eta",true,30,-3,3);
   makehist(channel_name+"_ZWl1_phi",true,40,0,3.14);
   makehist(channel_name+"_ZWl2_phi",true,40,0,3.14);
   makehist(channel_name+"_WW_eta",true,30,-3,3);
   makehist(channel_name+"_WW_phi",true,40,0,3.14);
   makehist(channel_name+"_chi2",true,100,0,100);
   makehist(channel_name+"_dR",true,40,0,4);
   makehist2d(channel_name+"_m4l_vs_mll2",true,100,0,1000,100,0,1000);
   makehist2d(channel_name+"_WW_phi_vs_eta",true,30,-3,3,40,0,3.14);
   makehist2d(channel_name+"_dR_vs_mll",true,40,0,400,40,0,4);
}
void ana::WWZ_fillhist(TString channel_name, float fill_wgt){
   TLorentzVector Z_tlv, W1_tlv, W2_tlv;
   Z_tlv = v_l_tlv[v_Z_pair[0].first]+v_l_tlv[v_Z_pair[0].second];
   W1_tlv = v_l_tlv[W_id[0]];
   W2_tlv = v_l_tlv[W_id[1]];
   makehist(channel_name+"_Zl_pt_1")->Fill(v_l_tlv[v_Z_pair[0].first].Pt()/1000,fill_wgt);
   makehist(channel_name+"_Zl_pt_2")->Fill(v_l_tlv[v_Z_pair[0].second].Pt()/1000,fill_wgt);
   makehist(channel_name+"_Wl_pt_1")->Fill( W1_tlv.Pt()/1000, fill_wgt);
   makehist(channel_name+"_Wl_pt_2")->Fill( W2_tlv.Pt()/1000, fill_wgt);
   makehist(channel_name+"_ZWl1_eta")->Fill( Z_tlv.Rapidity()-W1_tlv.Rapidity(), fill_wgt);
   makehist(channel_name+"_ZWl2_eta")->Fill( Z_tlv.Rapidity()-W2_tlv.Rapidity(), fill_wgt);
   makehist(channel_name+"_ZWl1_phi")->Fill( deltaphi(Z_tlv, W1_tlv), fill_wgt);
   makehist(channel_name+"_ZWl2_phi")->Fill( deltaphi(Z_tlv, W2_tlv), fill_wgt);
   makehist(channel_name+"_WW_eta")->Fill( W1_tlv.Rapidity()-W2_tlv.Rapidity(), fill_wgt);
   makehist(channel_name+"_WW_phi")->Fill( deltaphi(W1_tlv, W2_tlv), fill_wgt);
   makehist(channel_name+"_chi2")->Fill( chi2 , fill_wgt);
   makehist(channel_name+"_dR")->Fill(dR, fill_wgt);
   makehist2d(channel_name+"_m4l_vs_mll2")->Fill(mass_4l/1000, (W1_tlv+W2_tlv).M()/1000, fill_wgt);
   makehist2d(channel_name+"_WW_phi_vs_eta")->Fill(W1_tlv.Rapidity()-W2_tlv.Rapidity(), deltaphi(W1_tlv, W2_tlv), fill_wgt);
   makehist2d(channel_name+"_dR_vs_mll")->Fill((W1_tlv+W2_tlv).M()/1000, dR, fill_wgt);
}
float ana::deltaphi(TLorentzVector tlv1, TLorentzVector tlv2){
   float dphi = abs(tlv1.Phi()-tlv2.Phi());
   if(dphi > 3.14159){
      dphi = 2*3.14159 - dphi;
   }
   return dphi;
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
         std::cout<<"#####################begin of file##################"<<'\n';
         std::cout<<"#sum of weight: "<<v_sumofwgt[fCurrent]<<'\n';
         std::cout<<"#####################end of file####################"<<'\n';
      }
      if(initial_Cut()){ 
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
      }
      Loop_terminate();
   }    
   Terminate();

} 

void ana::Loop_initialize()
{

  for (int i=0; i < v_e_tlv->size(); ++i) {
    // do not consider it temporarily
    if (v_e_fwd->at(i)) continue;
    v_l_tlv.push_back(v_e_tlv->at(i));
    v_l_pid.push_back(v_e_pid->at(i));
    v_l_wgt.push_back(v_e_wgtLoose->at(i));
  }
  for (int i=0; i < v_m_tlv->size(); ++i) {
    // do not consider it temporarily
    if (v_m_lowpt->at(i)) continue;
    v_l_tlv.push_back(v_m_tlv->at(i));
    v_l_pid.push_back(v_m_pid->at(i));
    v_l_wgt.push_back(v_m_wgtLoose->at(i));
  }
   pt_sort(v_l_tlv,v_l_order);
   pt_sort(*v_j_tlv,v_j_order);
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
   _output= new TFile(_output_dir+_output_file+".root","recreate");
   _WWZ_tree = new TTree("WWZ","WWZ");
   _WWZ_tree->Branch("WWZ_Z_mass",&WWZ_Z_mass,"WWZ_Z_mass/F");
   _WWZ_tree->Branch("WWZ_dilepton_mass",&WWZ_dilepton_mass,"WWZ_dilepton_mass/F");
 
   cutflow("initial",true)
      .regFlow("initial","initial selection")
      .regCut("All")
      .regCut(">3l")
      .regCut("1_SFOS")
      .regCut("Z_window")
      .regCut("passTrig","",true)
      .regCut("no_fwde_lowptm","",true)
      .regCut("e_fwd","",true)
      .regCut("e_fwd_1","",true)
      .regCut("m_lowpt","",true)
      .regCut("m_lowpt_1","",true)
      .regCut(">6l","",true)
      .regCut("6l","",true)
      .regCut("5l","",true)
      .regCut("4l","",true);   
   cutflow("ZZZ",true)
      .regFlow("ZZZ","cutflow of ZZZ channel")
      .regCut("All")
      .regCut("1_SFOS","",true)
      .regCut("2_SFOS_>6l","",true)
      .regCut("2_SFOS_=6l","",true)
      .regCut("ee_before","",true)
      .regCut("mm_before","",true)
      .regCut("em_before","",true)
      .regCut("3_SFOS_before","",true)
      .regCut("Z3_40GeV")
      .regCut("3_SFOS_after","",true)
      .regCut("passTrig","",true)
      .regCut("no_fwde_lowptm","",true)
      .regCut("e_fwd","",true)
      .regCut("e_fwd_1","",true)
      .regCut("m_lowpt","",true)
      .regCut("m_lowpt_1","",true)
      .regCut("ee_after","",true)
      .regCut("mm_after","",true)
      .regCut("em_after","",true)
      .regCut("ZZZ_>6l","",true)
      .regCut("ZZZ_6l","",true);
   cutflow("WZZ",true)
      .regFlow("WZZ","cutflow of WZZ channel")
      .regCut(">=5l")
      .regCut("2_SFOS")
      .regCut("Z_window")
      .regCut("LeptonPt")
      .regCut("B_veto60","",true)
      .regCut("B_veto70","",true)
      .regCut("B_veto77","",true)
      .regCut("B_veto85","",true)
      .regCut("passTrig","",true)
      .regCut("no_fwde_lowptm","",true)
      .regCut("e_fwd","",true)
      .regCut("e_fwd_1","",true)
      .regCut("m_lowpt","",true)
      .regCut("m_lowpt_1","",true)
      .regCut("WZZ_>6l","",true)
      .regCut("WZZ_6l","",true)
      .regCut("WZZ_5l","",true);
   cutflow("WWZ",true)
      .regFlow("WWZ","cutflow of WWZ channel")
      .regCut(">=4l")
      .regCut("Dilepton")
      .regCut("LeptonPt")
      .regCut("dR>0.1")
      .regCut("B_veto60","",true)
      .regCut("B_veto70","",true)
      .regCut("B_veto77","",true)
      .regCut("B_veto85","",true)
      .regCut("passTrig","",true)
      .regCut("WWZ_>6l","",true)
      .regCut("WWZ_6l","",true)
      .regCut("WWZ_5l","",true)
      .regCut("WWZ_4l","",true)
      .regCut("WWZ_SF_noZ","",true)
      .regCut("WWZ_SF_inZ","",true)
      .regCut("WWZ_em","",true);
   // make your own hist
   makehist("Z_mass_first",true);
   makehist("Z_mass_second",true);
   makehist("Z_mass_third",true);
   channel_makehist("ZZZ",3);
   channel_makehist("WZZ",2);
   channel_makehist("WWZ",1);
   channel_makehist("WWZ_SF_noZ",1);
   channel_makehist("WWZ_SF_inZ",1);
   channel_makehist("WWZ_em",1);
   // WWZ channel
   WWZ_makehist("WWZ");
   WWZ_makehist("WWZ_SF_noZ");
   WWZ_makehist("WWZ_SF_inZ");
   WWZ_makehist("WWZ_em");
}

void ana::Terminate()
{
   std::ofstream _ofs_cutflow(_output_dir+_output_file+".txt",std::ofstream::out);   
   cutflow("initial").print(_ofs_cutflow);
   cutflow("ZZZ").print(_ofs_cutflow);
   cutflow("WZZ").print(_ofs_cutflow);
   cutflow("WWZ").print(_ofs_cutflow);
   _ofs_cutflow.close();
   _output->Write("All");
   _output->Close();
   delete _output;
}
