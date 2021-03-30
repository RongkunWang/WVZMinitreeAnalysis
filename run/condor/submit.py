#!/usr/bin/env python
"""
an example to run systematics histograms for H4l minitrees, locally or on condor
"""

import common
if __name__ == "__main__":
    common.job("../output/data20210318_noem", 
            short_queue = False,
            sample_list = [
                #  "mc16_13TeV.364243.Sherpa_222_NNPDF30NNLO_WWZ_4l2v_EW6",
                #  "mc16_13TeV.364244.Sherpa_222_NNPDF30NNLO_WWZ_2l4v_EW6",
                #  "364245",
                #  "410080",
                ],
            sample_veto = [
                #  "410080",
                ],
            batch_name = "WVZ_optim")
    pass
