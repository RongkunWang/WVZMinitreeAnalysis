#include<iostream>
#include<fstream>
#include<vector>
#include<TH1.h>
#include"TChain.h"
#include"TFile.h"
#include"ana.h"
using namespace std;

int main(int argc, char** argv)
{
   TString input_file_list="file.list";
   TString input_file_name;
   TString input_tree_name="tree_NOMINAL";
   TString input_hist_name="sumWeight";
   TString output_file_name="output.root";
   if(argc>1) 
   {
      output_file_name= argv[1];
   }
   std::cout<<"output file name is: "<<output_file_name<<'\n';
   // lumi, xs and eff data
   map<TString, float> m_lumi={{"r9364",36207.705},{"r10201",44307.223},{"r10724",58450.261}};
   map<TString, float> m_xs_eff;
   m_xs_eff["WWZ_4l2v"]=1.80e-3;
   m_xs_eff["WZZ_5l1v"]=1.88e-4;
   m_xs_eff["ZZZ_4l2v"]=8.65e-5;
   m_xs_eff["ZZZ_6l0v"]=1.45e-5;
   m_xs_eff["llll"]=1.25;
   m_xs_eff["ggllll_130M4l"]=1.01e-2;
   // sumofwgt, lumi, xs_eff inputdata
   vector<float>       iv_sumofwgt;
   vector<float>       iv_lumi;
   vector<float>       iv_xs_eff;
   bool boo_lumi;
   bool boo_xs_eff;
   // read file.list   
   TChain* ch= new TChain(input_tree_name);
   ifstream ifs;
   ifs.open(input_file_list.Data());
   while(ifs>>input_file_name)
   {
      if(input_file_name.BeginsWith("#")) continue; //file name begins with # will pass.      

      TFile* file= new TFile(input_file_name);
      TTree* tree= (TTree*) file->Get(input_tree_name);
      TH1D*  hist= (TH1D *) file->Get(input_hist_name);

      if(!tree || !hist) 
         cout<<"can't open: "<<input_file_name<<'\n';
      else
      {
         boo_lumi=false;
         boo_xs_eff=false;
         // add sum of weight
         iv_sumofwgt.insert(iv_sumofwgt.end(),hist->GetBinContent(2));
         // add lumi
         for(map<TString, float>::iterator it=m_lumi.begin(); it!=m_lumi.end(); it++)
         {
            if(input_file_name.Contains(it->first))
            {
               iv_lumi.insert(iv_lumi.end(),it->second); 
               boo_lumi=true;
               break;
            }
         }
         // add xs*eff
         for(map<TString, float>::iterator it=m_xs_eff.begin(); it!=m_xs_eff.end(); it++)
         {
            if(input_file_name.Contains(it->first))
            {
               iv_xs_eff.insert(iv_xs_eff.end(),it->second);
               boo_xs_eff=true;
               break;
            }
         }
         if(boo_lumi && boo_xs_eff) ch->Add(input_file_name);
      }

      delete tree;
      delete file;
   }

   ana* myanalysis= new ana(ch,output_file_name,iv_sumofwgt,iv_lumi,iv_xs_eff);
   myanalysis->Loop();
}

