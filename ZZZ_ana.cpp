#define ZZZ_ana_cxx
#include "ana.h"
bool ana::SFOS_Cut()
{
// true: e_total_charge==0 && m_total_charge==0
// false: else
   int i, sum=0;
   int n_elec=v_e_pid->size();
   int n_muon=v_m_pid->size();
   for(i=0; i<n_elec; i++) sum+= (*v_e_pid)[i];
   if(sum!=0) return false;
   sum=0;
   for(i=0; i<n_muon; i++) sum+= (*v_m_pid)[i];
   if(sum!=0) return false;
   return true;
}

bool ana::ZZZ_Cut()
{
   return false;
}

void ana::ZZZ_operation()
{
}
