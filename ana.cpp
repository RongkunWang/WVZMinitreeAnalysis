#define ana_cxx
#include "ana.h"
#include <iostream>
#include <time.h>
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
   }
};

bool ana::operator()(int i, int j)
{
   return v_l_tlv[i].Pt()>v_l_tlv[j].Pt();
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
      // if (Cut(ientry) < 0) continue;
      Loop_initialize();
      if(ientry%10000==0) std::cout<<"processing event: "<<ientry<<'\n';
      if(ientry>100000) break;
      if     (ZZZ_Cut()){ZZZ_operation();}
      else if(WZZ_Cut()){WZZ_operation();}
      else if(WWZ_Cut()){WWZ_operation();}
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
}

void ana::Loop_terminate()
{
   v_l_tlv.clear();
   v_l_pid.clear();
   v_l_wgt.clear();
/*
   v_W_id.clear();
   v_Z_pair.clear();
   v_ignore.clear();
*/
}


void ana::Initialize()
{
   _output= new TFile("output.root","recreate");
   
   cutflow("WWZ_4l",true)
      .regFlow("4l","WWZ 4l channel flow")
      .regCut("All")
      .regCut("6l","",true)
      .regCut("5l","",true)
      .regCut("3l","",true)
      .regCut("4l")
      .regCut("Pt")
      .regCut("Z_window")
      .regCut("Dilepton")
      .regCut("B_veto60","",true)
      .regCut("B_veto70","",true)
      .regCut("B_veto77","",true)
      .regCut("B_veto85","",true);

}

void ana::Terminate()
{
   cutflow("WWZ_4l").print(std::cout);
   _output->Write("All");
   _output->Close();
}
