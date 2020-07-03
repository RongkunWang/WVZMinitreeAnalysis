#!/usr/bin/env python
import ROOT as R
import sys,os
plot_dir=os.path.dirname(__file__)
sys.path.append(os.path.join(plot_dir,"libs"))
import AtlasStyle
import MyPyRootPlot1d as plt
file_name_list=["llll","WWZ_4l2v","WZZ_5l1v","ZZZ_6l0v","ZZZ_4l2v"]
# set color
# 0--red  1--blue  2--green  3--purple  4--orange  5--brown  6--pink  7--yellow  8--dark blue  9--dark green  10--grey  11--black  12--white
color_dic={}
color_dic["llll"]=0
color_dic["WWZ_4l2v"]=1
color_dic["WZZ_5l1v"]=2
color_dic["ZZZ_6l0v"]=3
color_dic["ZZZ_4l2v"]=4


var_name_list=["ZZZ_Z_pt_first","WWZ_leading_lepton_pt","WWZ_subleading_lepton_pt"]
# set stack dictionary
s_dic={}

for var_name in var_name_list:
	s_dic[var_name]=plt.FlatPlot(var_name,var_name)

for file_name in file_name_list:
	input_file= R.TFile.Open(os.path.join(plot_dir,"root",file_name+".root"))
	for var_name in var_name_list:
		input_hist= input_file.Get(var_name)

		s_dic[var_name].SetDoShape()
		s_dic[var_name].add(input_hist, lco=color_dic[file_name], lab_name=file_name, drawop="E", lab_op="fl",is_fill_color=True, fco=color_dic[file_name], falpha=0.1)
		
for var_name in var_name_list:
	s_dic[var_name].draw()
	s_dic[var_name].Print("./PDFs/"+var_name+".pdf")

