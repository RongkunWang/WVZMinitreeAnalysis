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
   
   TChain* ch= new TChain(input_tree_name);
   ifstream ifs;
   ifs.open(input_file_list.Data());
   // try to open the file
   while(ifs>>input_file_name)
   {
      if(input_file_name.BeginsWith("#")) continue; //file name begins with # will pass.

      TFile* file= new TFile(input_file_name);
      TTree* tree= (TTree*) file->Get(input_tree_name);
      if(!tree) cout<<"can't open: "<<input_file_name<<'\n';
      else ch->Add(input_file_name);
      delete tree;
      delete file;
   }
   ana* myanalysis= new ana(ch);
   myanalysis->Loop();
}

