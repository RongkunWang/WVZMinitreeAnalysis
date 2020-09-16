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
   TString output_file_name="output";
   if(argc>1) 
   {
      output_file_name= argv[1];
   }
   std::cout<<"output file name is: "<<output_file_name+".root"<<'\n';
   // sumofwgt, lumi, xs_eff inputdata
   vector<float>       iv_sumofwgt;
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
         // add sum of weight
         iv_sumofwgt.insert(iv_sumofwgt.end(),hist->GetBinContent(2));
         ch->Add(input_file_name);
      }

      delete tree;
      delete file;
   }

   ana* myanalysis= new ana(ch,output_file_name,iv_sumofwgt);
   myanalysis->Loop();
}

