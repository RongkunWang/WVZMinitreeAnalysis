#!/usr/bin/env python
import ROOT as R
import sys,os
plot_dir=os.path.dirname(__file__)
sys.path.append(os.path.join(plot_dir,"libs"))
import AtlasStyle
import MyPyRootPlot1d as plt
file_name_list=["output.root"]
for file_name in file_name_list:
	input_file= R.TFile.Open(os.path.join(plot_dir,"root",file_name))
	#input_file= R.TFile.Open("/lustre/umt3/user/zhichenw/wvz/WVZ_cutflow/plot/root/output.root")

	input_hist_1= input_file.Get("ZZZ_Z_pt_first")
	input_hist_2= input_file.Get("ZZZ_Z_pt_second")

	fp=plt.FlatPlot("test","test")

	fp.SetDoShape()
	fp.add(input_hist_1, lco=0, lab_name="first", drawop="EFhist", lab_op="fl",is_fill_color=True, fco=R.kRed, falpha=0.35)
	fp.add(input_hist_2, lco = -1, ls = 1, lab_name = "second", lab_op="f", drawop="Fhist", is_fill_color = True, fco=R.kBlue, falpha=0.35)
	fp.draw()
	fp.Print("./PDFs/test.pdf")

