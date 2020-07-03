#define ZZZ_ana_cxx
#include "ana.h"
bool ana::ZZZ_Cut()
{
   if(v_Z_pair.size()!=3) return false;
   // define weight
   ZZZ_wgt=wgt;
   for(int i=0;i<v_Z_wgt.size();i++) 
      ZZZ_wgt*=v_Z_wgt[i];
   // pass 3 SFOS cutflow
   cutflow("ZZZ").pass("ZZZ","3_SFOS",ZZZ_wgt); 
   // lepton number information
   if(v_l_pid.size()>6) cutflow("ZZZ").pass("ZZZ","ZZZ_>6l",ZZZ_wgt);
   if(v_l_pid.size()==6) cutflow("ZZZ").pass("ZZZ","ZZZ_6l",ZZZ_wgt);
   return true;
}

void ana::ZZZ_operation()
{
   if(cutflow("ZZZ").isPass("ZZZ","3_SFOS")) channel_fillhist("ZZZ",3,ZZZ_wgt);
}
