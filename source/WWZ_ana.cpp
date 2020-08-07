#define WWZ_ana_cxx
#include <iostream>
#include "ana.h"
#include <time.h>
bool ana::WWZ_Cut()
{
   //All
   cutflow("WWZ").pass("WWZ",">=4l",wgt*v_Z_wgt[0]);
   //lepton numbers
   int nlepton=v_l_pid.size();
   //define weight
   WWZ_wgt= wgt*v_Z_wgt[0];
   int nW=0;
   int W_id[2];
   for(int i=0;i<nlepton;i++)
   {
      if(v_l_order[i]==v_Z_pair[0].first || v_l_order[i]==v_Z_pair[0].second) continue;
      WWZ_wgt*= v_l_wgt[v_l_order[i]];
      if(nW>=2) break;
      W_id[nW]=v_l_order[i];
      nW++;
   }
   //dilepton
   for(int i=0;i<v_l_tlv.size();i++)
      for(int j=i+1;j<v_l_tlv.size();j++)
      {
         if(v_l_pid[i]+v_l_pid[j]!=0) continue;
         if((v_l_tlv[i]+v_l_tlv[j]).M()<12000){ return false;}
      }
   cutflow("WWZ").pass("WWZ","Dilepton",WWZ_wgt);
   //bveto
   Bjet_Cut("WWZ","WWZ",WWZ_wgt);
   //lepton number infomation
   if(nlepton>6) cutflow("WWZ").pass("WWZ","WWZ_>6l",WWZ_wgt);
   if(nlepton==6) cutflow("WWZ").pass("WWZ","WWZ_6l",WWZ_wgt);
   if(nlepton==5) cutflow("WWZ").pass("WWZ","WWZ_5l",WWZ_wgt);
   if(nlepton==4) cutflow("WWZ").pass("WWZ","WWZ_4l",WWZ_wgt);
   Find_m4l();

   if(cutflow("WWZ").isPass("WWZ","B_veto60"))
   {

      // SF_noZ and SF_inZ
      if( abs(v_l_pid[W_id[0]])==abs(v_l_pid[W_id[1]]))
      {

         if(abs((v_l_tlv[W_id[0]]+v_l_tlv[W_id[1]]).M()-Z_mass)<10e3)
            cutflow("WWZ").pass("WWZ","WWZ_SF_inZ",WWZ_wgt);
         else
            cutflow("WWZ").pass("WWZ","WWZ_SF_noZ",WWZ_wgt);

      }
      //em

      else
         cutflow("WWZ").pass("WWZ","WWZ_em",WWZ_wgt);

   }

   return true;
}


void ana::WWZ_operation()
{
   if(cutflow("WWZ").isPass("WWZ","B_veto60"))
   {
      channel_fillhist("WWZ",1,WWZ_wgt);
      makehist("m4l")->Fill(mass_4l/1000,WWZ_wgt);
   }
}
