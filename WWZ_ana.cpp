#define WWZ_ana_cxx
#include <iostream>
#include "ana.h"
bool ana::WWZ_Cut()
{
   //here I used cutflow tool for every cut for test, afterwards we can replace cutflow with return false.
   //All
   float wgt=weight*w_sf_jvt;
   cutflow("WWZ_4l").pass("4l","All",wgt);
   
   //lepton numbers
   if(v_l_pid.size()==6) cutflow("WWZ_4l").pass("4l","6l",wgt);
   if(v_l_pid.size()==5) cutflow("WWZ_4l").pass("4l","5l",wgt);
   if(v_l_pid.size()==3) cutflow("WWZ_4l").pass("4l","3l",wgt);
   if(v_l_pid.size()==4) cutflow("WWZ_4l").pass("4l","4l",wgt);
   //lepton number=4 cut, only for test
   if(v_l_pid.size()>4) return false; // will delete this part afterwards, choose lepton number<=4
   if(v_l_pid.size()<4) return false;
   //define Z and W leptons
   Find_Z_pair();
   if(v_Z_pair.size()==0) return false;
   for(int i=0;i<v_l_pid.size();i++)
   {
      if(find(v_ignore.begin(),v_ignore.end(),i)!=v_ignore.end()) continue;
      v_W_id.insert(v_W_id.end(),i);
   }
   //sort W lepton by pt
   std::sort(v_W_id.begin(), v_W_id.end(), *this);

   //pt
   if(v_l_tlv[v_Z_pair[0].first].Pt()>25000 && v_l_tlv[v_Z_pair[0].second].Pt()>10000)
   {
      wgt*=v_l_wgt[v_Z_pair[0].first]*v_l_wgt[v_Z_pair[0].second];
      for(int i=0;i<v_W_id.size();i++)
         for(int j=i+1;j<v_W_id.size();j++)
         {
            if(v_l_tlv[v_W_id[i]].Pt()<=25000 || v_l_tlv[v_W_id[j]].Pt()<=10000) continue;
            if(v_l_pid[v_W_id[i]]*v_l_pid[v_W_id[j]]<0)
            {
               wgt*=v_l_wgt[v_W_id[i]]*v_l_wgt[v_W_id[j]];
               cutflow("WWZ_4l").pass("4l","Pt",wgt);
               break;
            }
         }
   }

   //Z_onshell
   if(abs((v_l_tlv[v_Z_pair[0].first]+v_l_tlv[v_Z_pair[0].second]).M()-Z_mass)<15e3) cutflow("WWZ_4l").pass("4l","Z_window",wgt);

   //dilepton
   bool dilepton=true;
   for(int i=0;i<v_l_tlv.size();i++)
      for(int j=i+1;j<v_l_tlv.size();j++)
      {
         if(v_l_pid[i]+v_l_pid[j]!=0) continue;
         if((v_l_tlv[i]+v_l_tlv[j]).M()<12000){ dilepton=false; break;}
      }
   if(dilepton) cutflow("WWZ_4l").pass("4l","Dilepton",wgt);
   
   //bveto
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
   if(btag_veto) cutflow("WWZ_4l").pass("4l","B_veto60",wgt*btag_wgt);

   btag_wgt=1;
   btag_veto=true;
   for(int i=0;i<njet;i++)
   {
      if(v_j_btag70->at(i)) btag_veto=false;
      btag_wgt*=v_j_wgt_btag70->at(i);
   }
   if(btag_veto) cutflow("WWZ_4l").pass("4l","B_veto70",wgt*btag_wgt);

   btag_wgt=1;
   btag_veto=true;
   for(int i=0;i<njet;i++)
   {
      if(v_j_btag77->at(i)) btag_veto=false;
      btag_wgt*=v_j_wgt_btag77->at(i);
   }
   if(btag_veto) cutflow("WWZ_4l").pass("4l","B_veto77",wgt*btag_wgt);

   btag_wgt=1;
   btag_veto=true;
   for(int i=0;i<njet;i++)
   {
      if(v_j_btag85->at(i)) btag_veto=false;
      btag_wgt*=v_j_wgt_btag85->at(i);
   }
   if(btag_veto) cutflow("WWZ_4l").pass("4l","B_veto85",wgt*btag_wgt);
   
   return true;
}

void ana::WWZ_operation()
{
//   std::cout<<"success!!"<<'\n';
}
