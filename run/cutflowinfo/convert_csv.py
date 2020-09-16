#!/usr/bin/env python

def _list_read(file_name_list):
	_output_dic={}
        for file_name in file_name_list:
                with open(file_name+".txt","r") as f_in:
                        temp_lst=[]
                        for line in f_in.readlines():
                                if 'START' in line or ':' not in line:
                                        continue
                                lst_line=line.split(':')
                                lst_event=lst_line[1].split("+")[0].split("(")
                                temp_lst.append([lst_line[0],lst_event[0],lst_event[1]])
                        _output_dic[file_name]=temp_lst
	return _output_dic
def _write_csv(file_name_list,output_file_name="yield.csv",add_wgt=True):

	yield_dic=_list_read(file_name_list)
	with open(output_file_name,"w") as f_out:
		f_out.write("{}".format("Yield"))
		for lst in yield_dic[file_name_list[0]]:
			f_out.write(",{}".format(lst[0]))
		f_out.write('\n')
		if(add_wgt):
			index=2
		else:
			index=1
		for file_name in file_name_list:
			f_out.write("{}".format(file_name))
			for lst in yield_dic[file_name]:
				f_out.write(",{}".format(lst[index]))
			f_out.write('\n')

if __name__=="__main__":
	file_name_list=["llll","ggllll_130M4l","WWZ_4l2v","WZZ_5l1v","ZZZ_6l0v","ZZZ_4l2v","ZqqZll","WqqZll","WWZ_3l1v2j","WZZ_4l2j","WZZ_3l1v2j","WWW_3l3v","WWZ_2l4v","WZZ_3l3v","ZZZ_2l4v","lllv","llvv","lllljj","lllvjj","llvvjj","llll_lowMllPt","lllv_lowMllPt","llvv_lowMllPt"]
	_write_csv(file_name_list)		
