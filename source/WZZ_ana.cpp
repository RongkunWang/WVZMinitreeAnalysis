#define WZZ_ana_cxx
#include "ana.h"
bool ana::WZZ_Cut()
{
   int nlepton=v_l_pid.size();
   // at least 5 leptons
   if(nlepton<5) return false;
   cutflow("WZZ").pass("WZZ",">=5l",wgt*v_Z_wgt[0]);
   // at least 2 SFOS pairs & calculate weight
   if(v_Z_pair.size()<2) return false;
   WZZ_wgt=wgt*v_Z_wgt[0]*v_Z_wgt[1];
   for(int i=0;i<nlepton;i++)
   {
      if(v_l_order[i]==v_Z_pair[0].first || v_l_order[i]==v_Z_pair[0].second || v_l_order[i]==v_Z_pair[1].first || v_l_order[i]==v_Z_pair[1].second) continue;
      WZZ_wgt*=v_l_wgt[v_l_order[i]];
      break;
   }
   cutflow("WZZ").pass("WZZ","2_SFOS",WZZ_wgt);
   // Z window 15 GeV
   if(abs((v_l_tlv[v_Z_pair[1].first]+v_l_tlv[v_Z_pair[1].second]).M()-Z_mass)>15e3) return false;
   cutflow("WZZ").pass("WZZ","Z_window",WZZ_wgt);
   // bveto
   Bjet_Cut("WZZ","WZZ",WZZ_wgt);
   // lepton number infomation
   if(nlepton>6)  cutflow("WZZ").pass("WZZ","WZZ_>6l",WZZ_wgt);
   if(nlepton==6) cutflow("WZZ").pass("WZZ","WZZ_6l",WZZ_wgt);
   if(nlepton==5) cutflow("WZZ").pass("WZZ","WZZ_5l",WZZ_wgt);
   return true;
}

void ana::WZZ_operation()
{
   if(cutflow("WZZ").isPass("WZZ","B_veto60")) channel_fillhist("WZZ",2,WZZ_wgt);
}
