#ifndef ana_h
#define ana_h
#include"ana_base.h"
#include"CutFlowTool.h"
#include<string.h>
#include"TFile.h"
#include"TH1F.h"
#include<vector>
#include"TLorentzVector.h"
#include<time.h>
#define Z_mass 91187.6
using namespace std;

class ana:public ana_base
{
   public:
// variables
      float                        wgt;
      vector<TLorentzVector>       v_l_tlv;
      vector<int>                  v_l_pid;
      vector<float>                v_l_wgt;
      vector<int>                  v_l_order;
      vector<float>                v_Z_wgt; // weight for Z leptons, related to v_Z_pair
      vector<pair<int,int> >       v_Z_pair;
      vector<int>                  v_ignore;
// initial cut
      bool initial_Cut();
// ZZZ
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
//universal functions
      CutFlowTool&  cutflow(string s="NOMINAL",bool ini=false);
      TH1F*         makehist(TString s="NULL",bool ini=false);
      void          channel_makehist(TString channel_name, int nZ=0);
      void          channel_fillhist(TString channel_name, int nZ=0);
      void          lepton_pt_sort();
      void          Find_Z_pair();      
      void          Bjet_Cut(string s_flow, string s_cut, float wgt_base);

   private:
      TFile*                       _output;
      map<TString, TH1F*>          m_hist;
      map<string,CutFlowTool>      m_CutFlowTool;
};
#endif