#ifndef ZZZ_ana_h
#define ZZZ_ana_h
bool ana::ZZZ_ana::SFOS_Cut()
{
// true: e_total_charge==0 && m_total_charge==0
// false: else
   int i, sum=0;
   for(i=0; i<v_e_pid->size(); i++) sum+= v_e_pid[i];
   if(sum!=0) return false;
   sum=0;
   for(i=0; i<v_m_pid->size(); i++) sum+= v_m_pid[i];
   if(sum!=0) return false;
   return true;
}

#endif
