#define WZZ_ana_cxx
#include "ana.h"
bool ana::WZZ_Cut()
{
   int nlepton=v_l_pid.size();
   // at least 5 leptons
   if(nlepton<5) return false;
   cutflow("WZZ").pass("WZZ","All",wgt*v_Z_wgt[0]);
   if(nlepton==6) cutflow("WZZ").pass("WZZ","6l",wgt*v_Z_wgt[0]);
   if(nlepton==5) cutflow("WZZ").pass("WZZ","5l",wgt*v_Z_wgt[0]);
   // at least 2 SFOS pairs
   // Find_Z_pair(); 
   if(v_Z_pair.size()<2) return false;
   cutflow("WZZ").pass("WZZ","2_SFOS",wgt*v_Z_wgt[0]*v_Z_wgt[1]);
   // Z window 15 GeV
   if(abs((v_l_tlv[v_Z_pair[1].first]+v_l_tlv[v_Z_pair[1].second]).M()-Z_mass)>15e3) return false;
   cutflow("WZZ").pass("WZZ","Z_window",wgt*v_Z_wgt[0]*v_Z_wgt[1]);
   // bveto
   Bjet_Cut("WZZ","WZZ",wgt*v_Z_wgt[0]*v_Z_wgt[1]);
   return true;
}

void ana::WZZ_operation()
{
   if(cutflow("WZZ").isPass("WZZ","B_veto60")) channel_fillhist("WZZ",2);
}
