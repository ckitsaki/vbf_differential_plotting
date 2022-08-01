#!/bin/sh

# plot production submission (supporting note)
#condor_submit ./submission_files/plot_production/submit_plots_SR.sub
#condor_submit ./submission_files/plot_production/submit_plots_SR_linear.sub
#condor_submit ./submission_files/plot_production/submit_plots_DYCR.sub
#condor_submit ./submission_files/plot_production/submit_plots_TopCR.sub
#condor_submit ./submission_files/plot_production/submit_plots_WWCR.sub
#condor_submit ./submission_files/plot_production/submit_plots_ggFCR1.sub
#condor_submit ./submission_files/plot_production/submit_plots_ggFCR2.sub
#condor_submit ./submission_files/plot_production/submit_plots_ggFCR3.sub
#
# 
# random examples
#condor_submit ./submission_files/plot_production/submit_plots_single1.sub
#condor_submit ./submission_files/plot_production/submit_plots.sub
#
# differential cross sections 
#condor_submit ./submission_files/plot_production/submit_plots_diff_XS.sub
# inputs for pre-fit BDTs >> the final plot is produced by using the script src/plot_tools/pre_fit_bdt.cpp <<
condor_submit ./submission_files/plot_production/submit_plots_prefit_BDT.sub
