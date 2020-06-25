#define ana_cxx
#include "ana.h"
#include <iostream>
#include <time.h>
#include <fstream>
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
   wgt= weight*w_sf_jvt;
   cutflow("initial").pass("initial","All",wgt);
   // lepton number > 3
   if(v_l_pid.size()<=3) return false;
   cutflow("initial").pass("initial",">3l",wgt);
   // at least one SFOS pair
   Find_Z_pair();
   if(v_Z_pair.size()==0) return false;
   cutflow("initial").pass("initial","1_SFOS",wgt*v_Z_wgt[0]);
   // Z window 15 GeV
   if(abs((v_l_tlv[v_Z_pair[0].first]+v_l_tlv[v_Z_pair[0].second]).M()-Z_mass)>15e3) return false;
   cutflow("initial").pass("initial","Z_window",wgt*v_Z_wgt[0]);
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
////////////////////////////////////////////////below is major part of ana///////////////////////////////////////////////////////////
ana::ana(TTree* tree): ana_base(tree){}

CutFlowTool& ana::cutflow(string n, bool ini)
{
   if(ini) m_CutFlowTool.emplace(n,n);
   return m_CutFlowTool.at(n);
}

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
/////////////////////////////////////////////////////////////////////////////////////////////////////////
      Loop_initialize();

      if(ientry%100000==0) std::cout<<"processing event: "<<ientry<<'\n';
//      if(ientry>100000) break;

      if(initial_Cut()) 
      if     (ZZZ_Cut()){ZZZ_operation();}
      else if(WZZ_Cut()){WZZ_operation();}
      else if(WWZ_Cut()){WWZ_operation();}

      Loop_terminate();
//////////////////////////////////////////////////////////////////////////////////////////////////////////
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
}

void ana::Loop_terminate()
{
   v_l_tlv.clear();
   v_l_pid.clear();
   v_l_wgt.clear();
   if(v_Z_pair.size()!=0)
   {
      v_Z_pair.clear();
      v_ignore.clear();
      v_Z_wgt.clear();
   }
}


void ana::Initialize()
{
   _output= new TFile("output.root","recreate");

   cutflow("initial",true)
      .regFlow("initial","initial selection")
      .regCut("All")
      .regCut(">3l")
      .regCut("1_SFOS")
      .regCut("Z_window");   
   cutflow("ZZZ",true)
      .regFlow("ZZZ","cutflow of ZZZ channel")
      .regCut("6l")
      .regCut("3_SFOS");
   cutflow("WZZ",true)
      .regFlow("WZZ","cutflow of WZZ channel")
      .regCut("All")
      .regCut("6l","",true)
      .regCut("5l","",true)
      .regCut("2_SFOS")
      .regCut("Z_window")
      .regCut("B_veto60","",true)
      .regCut("B_veto70","",true)
      .regCut("B_veto77","",true)
      .regCut("B_veto85","",true);
   cutflow("WWZ",true)
      .regFlow("WWZ","cutflow of WWZ channel")
      .regCut("All")
      .regCut("6l","",true)
      .regCut("5l","",true)
      .regCut("4l","",true)
      .regCut("Dilepton")
      .regCut("B_veto60","",true)
      .regCut("B_veto70","",true)
      .regCut("B_veto77","",true)
      .regCut("B_veto85","",true);
}

void ana::Terminate()
{
   std::ofstream ofs("cutflow_info.txt",std::ofstream::out);
   cutflow("initial").print(ofs);
   cutflow("ZZZ").print(ofs);
   cutflow("WZZ").print(ofs);
   cutflow("WWZ").print(ofs);
   ofs.close();
   _output->Write("All");
   _output->Close();
}
