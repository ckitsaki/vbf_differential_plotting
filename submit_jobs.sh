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

# plot production submission
#condor_submit ./submission_files/plot_production/submit_plots_SR.sub
#condor_submit ./submission_files/plot_production/submit_plots_SR_linear.sub
#condor_submit ./submission_files/plot_production/submit_plots_DYCR.sub
#condor_submit ./submission_files/plot_production/submit_plots_TopCR.sub
#condor_submit ./submission_files/plot_production/submit_plots_WWCR.sub
#condor_submit ./submission_files/plot_production/submit_plots_ggFCR1.sub
#condor_submit ./submission_files/plot_production/submit_plots_ggFCR2.sub
#condor_submit ./submission_files/plot_production/submit_plots_ggFCR3.sub

#condor_submit ./submission_files/plot_production/submit_plots_single.sub
#condor_submit ./submission_files/plot_production/submit_plots_paper.sub
