#!/usr/bin/env python
import ROOT as R
import sys,os
plot_dir=os.path.dirname(__file__)
sys.path.append(os.path.join(plot_dir,"libs"))
import AtlasStyle
import MyPyRootPlot1d as plt

# define shape_compare function
def shape_compare(file_name_list, var_name_list):
	s_dic={}
	for var_name in var_name_list:
		s_dic[var_name]=plt.FlatPlot(var_name,var_name)

	for file_name in file_name_list:
		input_file= R.TFile.Open(os.path.join(plot_dir,"root",file_name+".root"))
		for var_name in var_name_list:
			input_hist= input_file.Get(var_name)

			s_dic[var_name].SetDoShape()
			s_dic[var_name].add(input_hist, lco=color_dic[file_name], lab_name=file_name, drawop="E", lab_op="fl",is_fill_color=False, falpha=0.1)
		
	for var_name in var_name_list:
		s_dic[var_name].draw()
		s_dic[var_name].Print("./PDFs/"+var_name+".png")


# define stack function
def stack_hist(file_name_list, var_name_list):
	pass


# main function
if __name__=="__main__":
	#file_name_list=["qqZZ","ggZZ_m4l>130","WWZ_4l2v","WZZ_5l1v","ZZZ_6l0v","ZZZ_4l2v"]
	file_name_list=["llll","WWZ_4l2v","WZZ_5l1v","ZZZ_6l0v","ZZZ_4l2v"]
	# set color
	# 0--red  1--blue  2--green  3--purple  4--orange  5--brown  6--pink  7--yellow  8--dark blue  9--dark green  10--grey  11--black  12--white
	color_dic={}
	color_dic["llll"]=0
	color_dic["WWZ_4l2v"]=1
	color_dic["WZZ_5l1v"]=2
	color_dic["ZZZ_6l0v"]=3
	color_dic["ZZZ_4l2v"]=4


	var_name_list=["ZZZ_Z_pt_first","ZZZ_Z_pt_second","ZZZ_Z_pt_third","WZZ_Z_pt_first","WZZ_Z_pt_second","WWZ_Z_pt_first",
               "ZZZ_leading_lepton_pt","ZZZ_subleading_lepton_pt","WZZ_leading_lepton_pt","WZZ_subleading_lepton_pt","WWZ_leading_lepton_pt","WWZ_subleading_lepton_pt",
               "ZZZ_Z_mass_first","ZZZ_Z_mass_second","ZZZ_Z_mass_third","WZZ_Z_mass_first","WZZ_Z_mass_second","WWZ_Z_mass_first" ]

	shape_compare(file_name_list,var_name_list)

