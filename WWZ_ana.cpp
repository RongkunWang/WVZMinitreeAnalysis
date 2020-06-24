#define WWZ_ana_cxx
#include <iostream>
#include "ana.h"
#include <time.h>
bool ana::WWZ_Cut()
{
   //All
   cutflow("WWZ").pass("WWZ","All",wgt);
   //lepton numbers
   if(v_l_pid.size()==6) cutflow("WWZ").pass("WWZ","6l",wgt);
   if(v_l_pid.size()==5) cutflow("WWZ").pass("WWZ","5l",wgt);
   if(v_l_pid.size()==4) cutflow("WWZ").pass("WWZ","4l",wgt);

   //dilepton
   for(int i=0;i<v_l_tlv.size();i++)
      for(int j=i+1;j<v_l_tlv.size();j++)
      {
         if(v_l_pid[i]+v_l_pid[j]!=0) continue;
         if((v_l_tlv[i]+v_l_tlv[j]).M()<12000){ return false;}
      }
   cutflow("WWZ").pass("WWZ","Dilepton",wgt);
   //bveto
   Bjet_Cut("WWZ","WWZ");
   return true;
}


void ana::WWZ_operation()
{
}
