#define ZZZ_ana_cxx
#include "ana.h"
#include<iostream>
bool ana::ZZZ_Cut()
{
   int nZ=v_Z_pair.size();
   int nlepton=v_l_pid.size();
   int sumofpid=0;
   // define weight
   ZZZ_wgt=wgt;
   // nlepton>=6 cut
   if(nlepton<6) return false;
   cutflow("ZZZ").pass("ZZZ","All",wgt);
   // 1 SFOS: not recover
   if(nZ==1)
   {
      cutflow("ZZZ").pass("ZZZ","1_SFOS",wgt);
      return false;
   }
   // 2 SFOS with more than 6 leptons: not recover
   if(nZ==2 && nlepton>6)
   {
      cutflow("ZZZ").pass("ZZZ","2_SFOS_>6l",wgt);
   }
   // 2 SFOS with 6 leptons: try to recover
   if(nZ==2 && nlepton==6) 
   {
      //ZZZ_wgt
      for(int i=0;i<nlepton;i++) ZZZ_wgt*=v_l_wgt[i];
      // all 2 SFOS 
      cutflow("ZZZ").pass("ZZZ","2_SFOS_=6l",ZZZ_wgt);
      for(int i=0;i<nlepton;i++)
      {
         sumofpid+=v_l_pid[i];
      }
      if(nlepton==6)
      {
         if(sumofpid==22 || sumofpid==-22) cutflow("ZZZ").pass("ZZZ","ee",ZZZ_wgt);
         else if(sumofpid==26 || sumofpid==-26) cutflow("ZZZ").pass("ZZZ","mm",ZZZ_wgt);
         else if(sumofpid==2 || sumofpid==-2 || sumofpid==24 || sumofpid==-24)
         {
            cutflow("ZZZ").pass("ZZZ","em",ZZZ_wgt);
            return false;
         }
      }
      if(nlepton>6)
         return false;
   }
   // 3 SFOS cut
   if(nZ==3)
   {
      for(int i=0;i<nZ;i++) ZZZ_wgt*=v_Z_wgt[i];
      // pass 3 SFOS cutflow
      cutflow("ZZZ").pass("ZZZ","3_SFOS",ZZZ_wgt); 
   }
   // Z3 mass > 40GeV
   if(nZ==2)
   {
      TLorentzVector Z3_tlv;
      for(int i=0;i<nlepton;i++)
      {
         if(find(v_ignore.begin(),v_ignore.end(),i)!=v_ignore.end()) continue;
         Z3_tlv +=v_l_tlv[i];
      }
      if(Z3_tlv.M()>40e3)
         cutflow("ZZZ").pass("ZZZ","Z3_40GeV",ZZZ_wgt);
         
      else
         return false;
   }
   if(nZ==3) 
   {
      if((v_l_tlv[v_Z_pair[2].first]+v_l_tlv[v_Z_pair[2].second]).M()>40e3)
         cutflow("ZZZ").pass("ZZZ","Z3_40GeV",ZZZ_wgt);
      else
         return false;
   }
   // lepton number information
   if(nlepton>6) cutflow("ZZZ").pass("ZZZ","ZZZ_>6l",ZZZ_wgt);
   if(nlepton==6) cutflow("ZZZ").pass("ZZZ","ZZZ_6l",ZZZ_wgt);
   return true;
}

void ana::ZZZ_operation()
{
   if(cutflow("ZZZ").isPass("ZZZ","3_SFOS")) 
   {
      channel_fillhist("ZZZ",3,ZZZ_wgt);
   }
}
