#!/usr/bin/env python
import ROOT as R
import sys,os
sys.path.append(os.path.join(os.path.dirname(__file__),"libs"))
import AtlasStyle
import MyPyRootPlot1d as plt
plot_dir="/lustre/umt3/user/zhichenw/wvz/WVZ_cutflow/run"
input_file= R.TFile.Open(plot_dir+"/output.root")

input_hist_1= input_file.Get("ZZZ_Z_pt_first")
input_hist_2= input_file.Get("ZZZ_Z_pt_second")

fp=plt.FlatPlot("test","test")

fp.SetDoShape()
fp.add(input_hist_1, lco=0, lab_name="first", drawop="EFhist", lab_op="fl",is_fill_color=True, fco=R.kRed, falpha=0.35)
fp.add(input_hist_2, lco = -1, ls = 1, lab_name = "second", lab_op="f", drawop="Fhist", is_fill_color = True, fco=R.kBlue, falpha=0.35)
fp.draw()
fp.Print("./PDFs/test.pdf")

