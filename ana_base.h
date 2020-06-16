//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Mon Jun 15 16:57:42 2020 by ROOT version 6.18/04
// from TTree tree_NOMINAL/output tree
// found on file: sample_testMinitree.root
//////////////////////////////////////////////////////////

#ifndef ana_base_h
#define ana_base_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <vector>
#include "TLorentzVector.h"
// Header file for the classes stored in the TTree if any.
#include "vector"
#include "vector"
#include "vector"
using namespace std;
class ana_base {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

// Fixed size dimensions of array or collections stored in the TTree if any.

   // Declaration of leaf types
   Float_t         mu;
   Int_t           run;
   ULong64_t       event;
   Double_t        weight;
   Float_t         w_sf_jvt;
   Float_t         w_prw;
   vector<TLorentzVector> *v_e_tlv;
   vector<int>     *v_e_pid;
   vector<bool>    *v_e_LHTight;
   vector<bool>    *v_e_ambiguous;
   vector<float>   *v_e_wgt;
   vector<TLorentzVector> *v_m_tlv;
   vector<int>     *v_m_pid;
   vector<float>   *v_m_wgt;
   vector<TLorentzVector> *v_j_tlv;
   vector<bool>    *v_j_btag60;
   vector<bool>    *v_j_btag70;
   vector<bool>    *v_j_btag77;
   vector<bool>    *v_j_btag85;
   vector<float>   *v_j_wgt_btag60;
   vector<float>   *v_j_wgt_btag70;
   vector<float>   *v_j_wgt_btag77;
   vector<float>   *v_j_wgt_btag85;
   vector<int>     *v_j_btagCont;
   vector<float>   *v_j_wgt_btagCont;

   // List of branches
   TBranch        *b_mu;   //!
   TBranch        *b_run;   //!
   TBranch        *b_event;   //!
   TBranch        *b_weight;   //!
   TBranch        *b_w_sf_jvt;   //!
   TBranch        *b_w_prw;   //!
   TBranch        *b_v_e_tlv;   //!
   TBranch        *b_v_e_pid;   //!
   TBranch        *b_v_e_LHTight;   //!
   TBranch        *b_v_e_ambiguous;   //!
   TBranch        *b_v_e_wgt;   //!
   TBranch        *b_v_m_tlv;   //!
   TBranch        *b_v_m_pid;   //!
   TBranch        *b_v_m_wgt;   //!
   TBranch        *b_v_j_tlv;   //!
   TBranch        *b_v_j_btag60;   //!
   TBranch        *b_v_j_btag70;   //!
   TBranch        *b_v_j_btag77;   //!
   TBranch        *b_v_j_btag85;   //!
   TBranch        *b_v_j_wgt_btag60;   //!
   TBranch        *b_v_j_wgt_btag70;   //!
   TBranch        *b_v_j_wgt_btag77;   //!
   TBranch        *b_v_j_wgt_btag85;   //!
   TBranch        *b_v_j_btagCont;   //!
   TBranch        *b_v_j_wgt_btagCont;   //!

   ana_base(TTree *tree=0);
   virtual ~ana_base();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef ana_base_cxx
ana_base::ana_base(TTree *tree) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("sample_testMinitree.root");
      if (!f || !f->IsOpen()) {
         f = new TFile("sample_testMinitree.root");
      }
      f->GetObject("tree_NOMINAL",tree);

   }
   Init(tree);
}

ana_base::~ana_base()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t ana_base::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t ana_base::LoadTree(Long64_t entry)
{
// Set the environment to read one entry
   if (!fChain) return -5;
   Long64_t centry = fChain->LoadTree(entry);
   if (centry < 0) return centry;
   if (fChain->GetTreeNumber() != fCurrent) {
      fCurrent = fChain->GetTreeNumber();
      Notify();
   }
   return centry;
}

void ana_base::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set object pointer
   v_e_tlv = 0;
   v_e_pid = 0;
   v_e_LHTight = 0;
   v_e_ambiguous = 0;
   v_e_wgt = 0;
   v_m_tlv = 0;
   v_m_pid = 0;
   v_m_wgt = 0;
   v_j_tlv = 0;
   v_j_btag60 = 0;
   v_j_btag70 = 0;
   v_j_btag77 = 0;
   v_j_btag85 = 0;
   v_j_wgt_btag60 = 0;
   v_j_wgt_btag70 = 0;
   v_j_wgt_btag77 = 0;
   v_j_wgt_btag85 = 0;
   v_j_btagCont = 0;
   v_j_wgt_btagCont = 0;
   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("mu", &mu, &b_mu);
   fChain->SetBranchAddress("run", &run, &b_run);
   fChain->SetBranchAddress("event", &event, &b_event);
   fChain->SetBranchAddress("weight", &weight, &b_weight);
   fChain->SetBranchAddress("w_sf_jvt", &w_sf_jvt, &b_w_sf_jvt);
   fChain->SetBranchAddress("w_prw", &w_prw, &b_w_prw);
   fChain->SetBranchAddress("v_e_tlv", &v_e_tlv, &b_v_e_tlv);
   fChain->SetBranchAddress("v_e_pid", &v_e_pid, &b_v_e_pid);
   fChain->SetBranchAddress("v_e_LHTight", &v_e_LHTight, &b_v_e_LHTight);
   fChain->SetBranchAddress("v_e_ambiguous", &v_e_ambiguous, &b_v_e_ambiguous);
   fChain->SetBranchAddress("v_e_wgt", &v_e_wgt, &b_v_e_wgt);
   fChain->SetBranchAddress("v_m_tlv", &v_m_tlv, &b_v_m_tlv);
   fChain->SetBranchAddress("v_m_pid", &v_m_pid, &b_v_m_pid);
   fChain->SetBranchAddress("v_m_wgt", &v_m_wgt, &b_v_m_wgt);
   fChain->SetBranchAddress("v_j_tlv", &v_j_tlv, &b_v_j_tlv);
   fChain->SetBranchAddress("v_j_btag60", &v_j_btag60, &b_v_j_btag60);
   fChain->SetBranchAddress("v_j_btag70", &v_j_btag70, &b_v_j_btag70);
   fChain->SetBranchAddress("v_j_btag77", &v_j_btag77, &b_v_j_btag77);
   fChain->SetBranchAddress("v_j_btag85", &v_j_btag85, &b_v_j_btag85);
   fChain->SetBranchAddress("v_j_wgt_btag60", &v_j_wgt_btag60, &b_v_j_wgt_btag60);
   fChain->SetBranchAddress("v_j_wgt_btag70", &v_j_wgt_btag70, &b_v_j_wgt_btag70);
   fChain->SetBranchAddress("v_j_wgt_btag77", &v_j_wgt_btag77, &b_v_j_wgt_btag77);
   fChain->SetBranchAddress("v_j_wgt_btag85", &v_j_wgt_btag85, &b_v_j_wgt_btag85);
   fChain->SetBranchAddress("v_j_btagCont", &v_j_btagCont, &b_v_j_btagCont);
   fChain->SetBranchAddress("v_j_wgt_btagCont", &v_j_wgt_btagCont, &b_v_j_wgt_btagCont);
   Notify();
}

Bool_t ana_base::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void ana_base::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t ana_base::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef ana_base_cxx
