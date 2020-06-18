#ifndef ana_h
#define ana_h
#include"ana_base.h"
#include<string.h>
#include"TFile.h"
#include"TH1F.h"
#include<vector>
#include"TLorentzVector.h"
using namespace std;

class ana:public ana_base
{
   public:
// variables
      vector<TLorentzVector> v_l_tlv;
      vector<int>            v_l_pid;
      vector<float>          v_l_wgt;
      vector<int>            W_id;
      map<int,int>           Z_pair_id;
      map<TString,bool>      Cutflow;
      const float            Z_mass=91187.6; //MeV
// ZZZ
      bool SFOS_Cut();
      bool ZZZ_Cut();
      void ZZZ_operation();
// WZZ
      bool WZZ_Cut();
      void WZZ_operation();
// WWZ
      bool WWZ_Cut();
      void WWZ_operation();
//Loop  functions
      ana(TTree* tree);
      void Loop();
      void Initialize();
      void Terminate();
      void Loop_initialize();
      void Loop_terminate();
//univeral functions
      pair<int, int> Find_best_Z_pair(vector<int> v_ignore);      

   private:
      TFile* _output;
      map<string, TH1F*> map_hist;
};
#endif
