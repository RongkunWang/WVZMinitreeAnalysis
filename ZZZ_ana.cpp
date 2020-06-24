#define ZZZ_ana_cxx
#include "ana.h"
bool ana::ZZZ_Cut()
{
   // 6 leptons
   if(v_l_pid.size()!=6) return false;
   cutflow("ZZZ").pass("ZZZ","6l",wgt);
   // electron total charge = 0
   int sum=0;
   for(int i=0; i<v_e_pid->size(); i++) sum+= (*v_e_pid)[i];
   if(sum!=0) return false;
   // muon total charge =0
   sum=0;
   for(int i=0; i<v_m_pid->size(); i++) sum+= (*v_m_pid)[i];
   if(sum!=0) return false;
   cutflow("ZZZ").pass("ZZZ","3_SFOS",wgt);
   return true;
}

void ana::ZZZ_operation()
{
}
