#define WWZ_ana_cxx
#include <iostream>
#include "ana.h"
bool ana::WWZ_Cut()
{
   if(v_l_pid.size()>4) return false; // will delete this part afterwards, choose lepton number<=4
   if(v_l_pid.size()<4) return false;
   Find_Z_pair();
   if(v_Z_pair.size()==0) return false;
   for(int i=0;i<v_l_pid.size();i++)
   {
      if(find(v_ignore.begin(),v_ignore.end(),i)!=v_ignore.end()) continue;
      v_W_id.insert(v_W_id.end(),i);
   }
   //sort W lepton by pt
   
   //pt
   //Z_onshell
   //dilepton
   //bveto
   return true;
}

void ana::WWZ_operation()
{
   std::cout<<"success!!"<<'\n';
}
