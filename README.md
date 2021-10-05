vbf_differential_plotting Repository
====================================
This repository is used to produce the kinematic distributions at reconstruction level including the theory and experimental uncertainties as error bands for the needs of the VBF HWW analysis. 
The inputs are the ntuples produced by the [HWWAnalysisCode](https://gitlab.cern.ch/atlas-physics/higgs/hww/HWWAnalysisCode). 

Experimental uncertainties 
--------------------------
In order to add the experimental uncertainties as error bands, for a given observable and region of interest, histograms for each experimental systematic are dumped and saved in a .root file which is then used by the plotting tool to produce the final plot. This procedure needs to be submitted through condor.

Usage:
1. `mkdir sys_files error log output` 
2. Modify the script `submit_systematics.sh`, i.e `region`, `observable` and `dir` variables should be changed according to what you wish to plot.
3. Run `./submit_jobs.sh`. Jobs for each systematic uncertainty and process (vbf, ggf, vh, htt, diboson, top, Zjets, Fakes) will be send to condor.
4. For each of the processes and systematic uncertainties a corresponding .root file is saved under the `sys_files` folder. Modify the `hadd_sys_files.sh` script by updating the `observable` variable with respect to what was declared at Step 2 and then run the script `./hadd_sys_files.sh`. All .root files will be hadded into a single .root file (i.e systematics.root) while at the same time contents under the directories `error`,`log` and `output` will be deleted. 

Additional info:
* Before Step 4, one can check if the jobs ended successfully. `grep -r "Error" ./error` will print out if anything went wrong. With the job id one can check for further details the corresponding files under `log` and `output` directories. There is also a script under `debugging` directory with which the .root files under `sys_files` directory are checked one by one and the problematic ones are printed out. In order to use this script do: 
```
cd debugging
root -l 
.L CheckFiles.C
checkFiles()
``` 
* The histogram binning can be changed in the `GetSystematics::setBins(bool forPaper)` function which is declared in `src/GetSystematics.h`. Notice that the same changes need to be passed in `plotting::setBins(bool forPaper)` function which is declared in `src/plotting.h`.

Produce the final plot
----------------------
The experimental and theory systematics need to be available as histograms stored in .root files under the directories `exp_systematics` and `theo_systematics` respectively. Once these files are present, the plotting tool can be used.

Usage:
1. `mkdir plots`. The requested plot will be saved under `plots` directory.
2. Log in to root in order to use the plotting tool.
```
root -l 
.L src/plotting.C
plotting("region","observable",unblind,forPaper,setAxesLimits,addTheo,lxplus)
```
Arguments:
* region (string): choose among SR, TopCR, DYCR, WWCR, ggFCR1, ggFCR2, ggFCR3
* observable (string): choose among lep0_pt, lep1_pt, jet0_pt, jet1_pt, jet2_pt, Mjj, DPhill, DPhijj, DYjj, Mll, DYll, nJets, Ml0j0, Ml1j1, Ml0j1, Ml1j0, MET, jet0_eta,jet1_eta, lep0_eta, lep1_eta, Ptll, SignedDPhijj, MT, costhetastar, ptTot, sumOfCentralitiesL, pt_H
* unblind (bool): decides if data will be shown or not. Values: True or False.
* forPaper (bool): decides if the plot is for the supporting note or the paper. For the moment, set it to False. 
* setAxesLimits (bool): gives the ability to change the axes limits without diving in the code. Hint: at first set it to False to see the default limits and if needed change it to True to adjust the desired limits on axes. Values: True or False. 
* addTheo (bool): decides if the theory uncertainties will be taken into account in the error band. For the moment, set it to False until all theory systematics will be available.
* lxplus (bool): set it to True if you work on lxplus. For spar set it to False.

Additional info:
* xAxis labeling can be changed in function `std::string xAxisTitle(std::string observable)` of `src/TreeReader.h`
