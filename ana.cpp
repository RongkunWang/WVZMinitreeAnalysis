#define ana_cxx
#include "ana.h"

pair<int, int> ana::Find_best_Z_pair(vector<int> v_ignore)
{
   int i,j;
   vector<int>::iterator iter;
   pair<int, int> Z_pair_temp(-1,-1);
   for(i=0; i<v_l_tlv.size(); i++)
   {
      iter=find(v_ignore.begin(), v_ignore.end(), i);
      if(iter== v_ignore.end()) continue;

      for(j=i+1; j<v_l_tlv.size(); j++)
      {
         iter=find(v_ignore.begin(), v_ignore.end(), j);
         if(iter== v_ignore.end())    continue;
         if(v_l_pid[i]+v_l_pid[j]!=0) continue;
         if(Z_pair_temp.first<0 || Z_pair_temp.second<0){ Z_pair_temp= make_pair(i,j); continue;}
         if(abs((v_l_tlv[i]+v_l_tlv[j]).M()-Z_mass) < abs((v_l_tlv[Z_pair_temp.first]+v_l_tlv[Z_pair_temp.second]).M()-Z_mass))
            Z_pair_temp= make_pair(i,j);
      }
   }
   return Z_pair_temp;
};

ana::ana(TTree* tree): ana_base(tree){}

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
      if(ZZZ_Cut()){ZZZ_operation(); continue;}
      if(WZZ_Cut()){WZZ_operation(); continue;}
      if(WWZ_Cut()){WWZ_operation(); continue;}
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
}

void ana::Initialize()
{
}

void ana::Terminate()
{
}
