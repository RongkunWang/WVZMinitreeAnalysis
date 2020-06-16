#ifndef ana_h
#define ana_h
#include"ana_base_h"
#include<string.h>
#include"TFile.h"
#include"TH1F.h"
using namespace std;
class ana:public ana_base
{
   public:
// variables
      const float            Z_mass=91187.6; //MeV
      vector<TLorentzVector> v_l_tlv;
      vector<int>            v_l_pid;
      vector<float>          v_l_wgt;
// classes
      class ZZZ_ana
      {
         bool SFOS_Cut();
      }
      class WZZ_ana
      {
      }
      class WWZ_ana
      {
         pair<int, int> Find_WW_pair(vector<int> v_ignore);
      }
// functions
      ana(TTree* tree);
      void Loop();
      void Initialize();
      void Terminate();

      void Loop_initialize();
      bool ZZZ_Cut();
      bool WZZ_Cut();
      bool WWZ_Cut();
      void Loop_terminate();
      pair<int, int> Find_best_Z_pair(vector<int> v_ignore);      

   private:
      TFile* _output;
      map<string, TH1F*> map_hist;
}

bool ana::ZZZ_ana::SFOS_Cut()
{
// true: e_total_charge==0 && m_total_charge==0
// false: else
   int i, sum=0;
   for(i=0; i<v_e_pid->size(); i++) sum+= v_e_pid[i];
   if(sum!=0) return false;
   sum=0;
   for(i=0; i<v_m_pid->size(); i++) sum+= v_m_pid[i];
   if(sum!=0) return false;
   return true;     
}

pair<int, int> ana::Find_best_Z_pair(vector<int> v_ignore)
{
// return best Z_pair: pair<int, int>
// v_ignore is the ignore list vector: vector<int>, numbers in v_ignore will not be calculated.
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
         if(Z_pair_temp.first<0 || Z_pair_temp_second<0){ Z_pair_temp= make_pair(i,j); continue;}
         if(abs((v_l_tlv[i]+v_l_tlv[j]).M()-Z_mass) < abs((v_l_tlv[Z_pair_temp.first]+v_l_tlv[Z_pair_temp.second]).M()-Z_mass))
            Z_pair_temp= make_pair(i,j);
      }
   }
   return Z_pair_temp;
}

bool ana::ZZZ_Cut()
{
   return false;
}

bool ana::WZZ_Cut()
{
   return false;
}

bool ana::WWZ_Cut()
{
   pair<int, int> best_Z_pair= Find_best_Z_pair(vector<int>());
   
   return false;
}
#endif
