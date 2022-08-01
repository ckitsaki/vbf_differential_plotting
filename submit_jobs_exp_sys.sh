#!/bin/sh

# experimental systematics submission
condor_submit ./submission_files/submit_diboson1.sub
condor_submit ./submission_files/submit_diboson2.sub
condor_submit ./submission_files/submit_Fakes.sub
condor_submit ./submission_files/submit_ggf.sub
condor_submit ./submission_files/submit_htt.sub
condor_submit ./submission_files/submit_top1.sub
condor_submit ./submission_files/submit_top2.sub
condor_submit ./submission_files/submit_vbf.sub
condor_submit ./submission_files/submit_Vgamma.sub
condor_submit ./submission_files/submit_vh.sub
condor_submit ./submission_files/submit_WWEW.sub
condor_submit ./submission_files/submit_Zjets.sub

