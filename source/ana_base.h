//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Mon Oct 12 05:54:51 2020 by ROOT version 6.20/06
// from TTree tree_NOMINAL/output tree
// found on file: mc16_13TeV.364243.Sherpa_222_NNPDF30NNLO_WWZ_4l2v_EW6.deriv.DAOD_STDM3.e5887_s3126_r10201_p4097.root
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
   Bool_t          passTrig;
   ULong64_t       event;
   Double_t        weight;
   Float_t         w_sf_jvt;
   Float_t         w_prw;
   vector<TLorentzVector> *v_e_tlv;
   vector<int>     *v_e_pid;
   vector<bool>    *v_e_LHTight;
   vector<bool>    *v_e_ambiguous;
   vector<bool>    *v_e_fwd;
   vector<float>   *v_e_passIso;
   vector<float>   *v_e_wgtLoose;
   vector<float>   *v_e_wgtTight;
   vector<float>   *v_e_wgtIso;
   vector<TLorentzVector> *v_m_tlv;
   vector<int>     *v_m_pid;
   vector<float>   *v_m_d0;
   vector<bool>    *v_m_lowpt;
   vector<bool>    *v_m_passIso;
   vector<bool>    *v_m_passIsoVarRad;
   vector<float>   *v_m_wgtLoose;
   vector<float>   *v_m_wgtIso;
   vector<float>   *v_m_wgtIsoVarRad;
   vector<TLorentzVector> *v_m_tlv_fsr;
   vector<int>     *v_m_pid_fsr;
   vector<float>   *v_m_d0_fsr;
   vector<bool>    *v_m_lowpt_fsr;
   vector<bool>    *v_m_passIso_fsr;
   vector<bool>    *v_m_passIsoVarRad_fsr;
   vector<float>   *v_m_wgtLoose_fsr;
   vector<float>   *v_m_wgtIso_fsr;
   vector<float>   *v_m_wgtIsoVarRad_fsr;
   Double_t        MET;
   Double_t        METSig;
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
   vector<float>   *v_e_ptvarcone30_TightTTVA_pt1000;
   vector<float>   *v_m_ptvarcone30_TightTTVA_pt1000;
   vector<float>   *v_m_ptvarcone30_TightTTVA_pt1000_fsr;
   vector<float>   *v_e_ptvarcone30_TightTTVA_pt500;
   vector<float>   *v_m_ptvarcone30_TightTTVA_pt500;
   vector<float>   *v_m_ptvarcone30_TightTTVA_pt500_fsr;
   vector<float>   *v_e_ptcone20_TightTTVA_pt1000;
   vector<float>   *v_m_ptcone20_TightTTVA_pt1000;
   vector<float>   *v_m_ptcone20_TightTTVA_pt1000_fsr;
   vector<float>   *v_e_ptcone20_TightTTVA_pt500;
   vector<float>   *v_m_ptcone20_TightTTVA_pt500;
   vector<float>   *v_m_ptcone20_TightTTVA_pt500_fsr;
   vector<float>   *v_e_neflowisol20;
   vector<float>   *v_m_neflowisol20;
   vector<float>   *v_m_neflowisol20_fsr;
   vector<TLorentzVector> *v_truth_l_tlv;
   vector<int>     *v_truth_l_pdgId;
   vector<bool>    *v_truth_l_fromTau;
   vector<TLorentzVector> *v_truth_j_tlv;
   Bool_t          tauEvent;

   // List of branches
   TBranch        *b_mu;   //!
   TBranch        *b_run;   //!
   TBranch        *b_passTrig;   //!
   TBranch        *b_event;   //!
   TBranch        *b_weight;   //!
   TBranch        *b_w_sf_jvt;   //!
   TBranch        *b_w_prw;   //!
   TBranch        *b_v_e_tlv;   //!
   TBranch        *b_v_e_pid;   //!
   TBranch        *b_v_e_LHTight;   //!
   TBranch        *b_v_e_ambiguous;   //!
   TBranch        *b_v_e_fwd;   //!
   TBranch        *b_v_e_passIso;   //!
   TBranch        *b_v_e_wgtLoose;   //!
   TBranch        *b_v_e_wgtTight;   //!
   TBranch        *b_v_e_wgtIso;   //!
   TBranch        *b_v_m_tlv;   //!
   TBranch        *b_v_m_pid;   //!
   TBranch        *b_v_m_d0;   //!
   TBranch        *b_v_m_lowpt;   //!
   TBranch        *b_v_m_passIso;   //!
   TBranch        *b_v_m_passIsoVarRad;   //!
   TBranch        *b_v_m_wgtLoose;   //!
   TBranch        *b_v_m_wgtIso;   //!
   TBranch        *b_v_m_wgtIsoVarRad;   //!
   TBranch        *b_v_m_tlv_fsr;   //!
   TBranch        *b_v_m_pid_fsr;   //!
   TBranch        *b_v_m_d0_fsr;   //!
   TBranch        *b_v_m_lowpt_fsr;   //!
   TBranch        *b_v_m_passIso_fsr;   //!
   TBranch        *b_v_m_passIsoVarRad_fsr;   //!
   TBranch        *b_v_m_wgtLoose_fsr;   //!
   TBranch        *b_v_m_wgtIso_fsr;   //!
   TBranch        *b_v_m_wgtIsoVarRad_fsr;   //!
   TBranch        *b_MET;   //!
   TBranch        *b_METSig;   //!
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
   TBranch        *b_v_e_ptvarcone30_TightTTVA_pt1000;   //!
   TBranch        *b_v_m_ptvarcone30_TightTTVA_pt1000;   //!
   TBranch        *b_v_m_ptvarcone30_TightTTVA_pt1000_fsr;   //!
   TBranch        *b_v_e_ptvarcone30_TightTTVA_pt500;   //!
   TBranch        *b_v_m_ptvarcone30_TightTTVA_pt500;   //!
   TBranch        *b_v_m_ptvarcone30_TightTTVA_pt500_fsr;   //!
   TBranch        *b_v_e_ptcone20_TightTTVA_pt1000;   //!
   TBranch        *b_v_m_ptcone20_TightTTVA_pt1000;   //!
   TBranch        *b_v_m_ptcone20_TightTTVA_pt1000_fsr;   //!
   TBranch        *b_v_e_ptcone20_TightTTVA_pt500;   //!
   TBranch        *b_v_m_ptcone20_TightTTVA_pt500;   //!
   TBranch        *b_v_m_ptcone20_TightTTVA_pt500_fsr;   //!
   TBranch        *b_v_e_neflowisol20;   //!
   TBranch        *b_v_m_neflowisol20;   //!
   TBranch        *b_v_m_neflowisol20_fsr;   //!
   TBranch        *b_v_truth_l_tlv;   //!
   TBranch        *b_v_truth_l_pdgId;   //!
   TBranch        *b_v_truth_l_fromTau;   //!
   TBranch        *b_v_truth_j_tlv;   //!
   TBranch        *b_tauEvent;   //!

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
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("mc16_13TeV.364243.Sherpa_222_NNPDF30NNLO_WWZ_4l2v_EW6.deriv.DAOD_STDM3.e5887_s3126_r10201_p4097.root");
      if (!f || !f->IsOpen()) {
         f = new TFile("mc16_13TeV.364243.Sherpa_222_NNPDF30NNLO_WWZ_4l2v_EW6.deriv.DAOD_STDM3.e5887_s3126_r10201_p4097.root");
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
   v_e_fwd = 0;
   v_e_passIso = 0;
   v_e_wgtLoose = 0;
   v_e_wgtTight = 0;
   v_e_wgtIso = 0;
   v_m_tlv = 0;
   v_m_pid = 0;
   v_m_d0 = 0;
   v_m_lowpt = 0;
   v_m_passIso = 0;
   v_m_passIsoVarRad = 0;
   v_m_wgtLoose = 0;
   v_m_wgtIso = 0;
   v_m_wgtIsoVarRad = 0;
   v_m_tlv_fsr = 0;
   v_m_pid_fsr = 0;
   v_m_d0_fsr = 0;
   v_m_lowpt_fsr = 0;
   v_m_passIso_fsr = 0;
   v_m_passIsoVarRad_fsr = 0;
   v_m_wgtLoose_fsr = 0;
   v_m_wgtIso_fsr = 0;
   v_m_wgtIsoVarRad_fsr = 0;
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
   v_e_ptvarcone30_TightTTVA_pt1000 = 0;
   v_m_ptvarcone30_TightTTVA_pt1000 = 0;
   v_m_ptvarcone30_TightTTVA_pt1000_fsr = 0;
   v_e_ptvarcone30_TightTTVA_pt500 = 0;
   v_m_ptvarcone30_TightTTVA_pt500 = 0;
   v_m_ptvarcone30_TightTTVA_pt500_fsr = 0;
   v_e_ptcone20_TightTTVA_pt1000 = 0;
   v_m_ptcone20_TightTTVA_pt1000 = 0;
   v_m_ptcone20_TightTTVA_pt1000_fsr = 0;
   v_e_ptcone20_TightTTVA_pt500 = 0;
   v_m_ptcone20_TightTTVA_pt500 = 0;
   v_m_ptcone20_TightTTVA_pt500_fsr = 0;
   v_e_neflowisol20 = 0;
   v_m_neflowisol20 = 0;
   v_m_neflowisol20_fsr = 0;
   v_truth_l_tlv = 0;
   v_truth_l_pdgId = 0;
   v_truth_l_fromTau = 0;
   v_truth_j_tlv = 0;
   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("mu", &mu, &b_mu);
   fChain->SetBranchAddress("run", &run, &b_run);
   fChain->SetBranchAddress("passTrig", &passTrig, &b_passTrig);
   fChain->SetBranchAddress("event", &event, &b_event);
   fChain->SetBranchAddress("weight", &weight, &b_weight);
   fChain->SetBranchAddress("w_sf_jvt", &w_sf_jvt, &b_w_sf_jvt);
   fChain->SetBranchAddress("w_prw", &w_prw, &b_w_prw);
   fChain->SetBranchAddress("v_e_tlv", &v_e_tlv, &b_v_e_tlv);
   fChain->SetBranchAddress("v_e_pid", &v_e_pid, &b_v_e_pid);
   fChain->SetBranchAddress("v_e_LHTight", &v_e_LHTight, &b_v_e_LHTight);
   fChain->SetBranchAddress("v_e_ambiguous", &v_e_ambiguous, &b_v_e_ambiguous);
   fChain->SetBranchAddress("v_e_fwd", &v_e_fwd, &b_v_e_fwd);
   fChain->SetBranchAddress("v_e_passIso", &v_e_passIso, &b_v_e_passIso);
   fChain->SetBranchAddress("v_e_wgtLoose", &v_e_wgtLoose, &b_v_e_wgtLoose);
   fChain->SetBranchAddress("v_e_wgtTight", &v_e_wgtTight, &b_v_e_wgtTight);
   fChain->SetBranchAddress("v_e_wgtIso", &v_e_wgtIso, &b_v_e_wgtIso);
   fChain->SetBranchAddress("v_m_tlv", &v_m_tlv, &b_v_m_tlv);
   fChain->SetBranchAddress("v_m_pid", &v_m_pid, &b_v_m_pid);
   fChain->SetBranchAddress("v_m_d0", &v_m_d0, &b_v_m_d0);
   fChain->SetBranchAddress("v_m_lowpt", &v_m_lowpt, &b_v_m_lowpt);
   fChain->SetBranchAddress("v_m_passIso", &v_m_passIso, &b_v_m_passIso);
   fChain->SetBranchAddress("v_m_passIsoVarRad", &v_m_passIsoVarRad, &b_v_m_passIsoVarRad);
   fChain->SetBranchAddress("v_m_wgtLoose", &v_m_wgtLoose, &b_v_m_wgtLoose);
   fChain->SetBranchAddress("v_m_wgtIso", &v_m_wgtIso, &b_v_m_wgtIso);
   fChain->SetBranchAddress("v_m_wgtIsoVarRad", &v_m_wgtIsoVarRad, &b_v_m_wgtIsoVarRad);
   fChain->SetBranchAddress("v_m_tlv_fsr", &v_m_tlv_fsr, &b_v_m_tlv_fsr);
   fChain->SetBranchAddress("v_m_pid_fsr", &v_m_pid_fsr, &b_v_m_pid_fsr);
   fChain->SetBranchAddress("v_m_d0_fsr", &v_m_d0_fsr, &b_v_m_d0_fsr);
   fChain->SetBranchAddress("v_m_lowpt_fsr", &v_m_lowpt_fsr, &b_v_m_lowpt_fsr);
   fChain->SetBranchAddress("v_m_passIso_fsr", &v_m_passIso_fsr, &b_v_m_passIso_fsr);
   fChain->SetBranchAddress("v_m_passIsoVarRad_fsr", &v_m_passIsoVarRad_fsr, &b_v_m_passIsoVarRad_fsr);
   fChain->SetBranchAddress("v_m_wgtLoose_fsr", &v_m_wgtLoose_fsr, &b_v_m_wgtLoose_fsr);
   fChain->SetBranchAddress("v_m_wgtIso_fsr", &v_m_wgtIso_fsr, &b_v_m_wgtIso_fsr);
   fChain->SetBranchAddress("v_m_wgtIsoVarRad_fsr", &v_m_wgtIsoVarRad_fsr, &b_v_m_wgtIsoVarRad_fsr);
   fChain->SetBranchAddress("MET", &MET, &b_MET);
   fChain->SetBranchAddress("METSig", &METSig, &b_METSig);
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
   fChain->SetBranchAddress("v_e_ptvarcone30_TightTTVA_pt1000", &v_e_ptvarcone30_TightTTVA_pt1000, &b_v_e_ptvarcone30_TightTTVA_pt1000);
   fChain->SetBranchAddress("v_m_ptvarcone30_TightTTVA_pt1000", &v_m_ptvarcone30_TightTTVA_pt1000, &b_v_m_ptvarcone30_TightTTVA_pt1000);
   fChain->SetBranchAddress("v_m_ptvarcone30_TightTTVA_pt1000_fsr", &v_m_ptvarcone30_TightTTVA_pt1000_fsr, &b_v_m_ptvarcone30_TightTTVA_pt1000_fsr);
   fChain->SetBranchAddress("v_e_ptvarcone30_TightTTVA_pt500", &v_e_ptvarcone30_TightTTVA_pt500, &b_v_e_ptvarcone30_TightTTVA_pt500);
   fChain->SetBranchAddress("v_m_ptvarcone30_TightTTVA_pt500", &v_m_ptvarcone30_TightTTVA_pt500, &b_v_m_ptvarcone30_TightTTVA_pt500);
   fChain->SetBranchAddress("v_m_ptvarcone30_TightTTVA_pt500_fsr", &v_m_ptvarcone30_TightTTVA_pt500_fsr, &b_v_m_ptvarcone30_TightTTVA_pt500_fsr);
   fChain->SetBranchAddress("v_e_ptcone20_TightTTVA_pt1000", &v_e_ptcone20_TightTTVA_pt1000, &b_v_e_ptcone20_TightTTVA_pt1000);
   fChain->SetBranchAddress("v_m_ptcone20_TightTTVA_pt1000", &v_m_ptcone20_TightTTVA_pt1000, &b_v_m_ptcone20_TightTTVA_pt1000);
   fChain->SetBranchAddress("v_m_ptcone20_TightTTVA_pt1000_fsr", &v_m_ptcone20_TightTTVA_pt1000_fsr, &b_v_m_ptcone20_TightTTVA_pt1000_fsr);
   fChain->SetBranchAddress("v_e_ptcone20_TightTTVA_pt500", &v_e_ptcone20_TightTTVA_pt500, &b_v_e_ptcone20_TightTTVA_pt500);
   fChain->SetBranchAddress("v_m_ptcone20_TightTTVA_pt500", &v_m_ptcone20_TightTTVA_pt500, &b_v_m_ptcone20_TightTTVA_pt500);
   fChain->SetBranchAddress("v_m_ptcone20_TightTTVA_pt500_fsr", &v_m_ptcone20_TightTTVA_pt500_fsr, &b_v_m_ptcone20_TightTTVA_pt500_fsr);
   fChain->SetBranchAddress("v_e_neflowisol20", &v_e_neflowisol20, &b_v_e_neflowisol20);
   fChain->SetBranchAddress("v_m_neflowisol20", &v_m_neflowisol20, &b_v_m_neflowisol20);
   fChain->SetBranchAddress("v_m_neflowisol20_fsr", &v_m_neflowisol20_fsr, &b_v_m_neflowisol20_fsr);
   fChain->SetBranchAddress("v_truth_l_tlv", &v_truth_l_tlv, &b_v_truth_l_tlv);
   fChain->SetBranchAddress("v_truth_l_pdgId", &v_truth_l_pdgId, &b_v_truth_l_pdgId);
   fChain->SetBranchAddress("v_truth_l_fromTau", &v_truth_l_fromTau, &b_v_truth_l_fromTau);
   fChain->SetBranchAddress("v_truth_j_tlv", &v_truth_j_tlv, &b_v_truth_j_tlv);
   fChain->SetBranchAddress("tauEvent", &tauEvent, &b_tauEvent);
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
