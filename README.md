# vbf_differential_plotting Repository

This repository can be used to produce the kinematic distributions at reconstruction level including the theory and experimental uncertainties as error bands for the needs of the VBF HWW analysis. 
The inputs are the ntuples produced by the [HWWAnalysisCode](https://gitlab.cern.ch/atlas-physics/higgs/hww/HWWAnalysisCode). 

Scripts for the pre and post-fit discriminants, correlation matrices, normalisation parameters and differential XS results are also provided.

This repo is still under development.

Email contact: chara.kitsaki@cern.ch  

## Uncertainties
The user can include the experimental and the theory uncertainties to the error bands of the final plot. 
### Experimental uncertainties 
In order to add the experimental uncertainties as error bands, for a given observable and region of interest, histograms for each experimental systematic are dumped and saved in a .root file which is then used by the plotting tool to produce the final plot. This procedure needs to be submitted through condor.

Usage:
1. `mkdir sys_files error log output` 
2. Modify the script `submit_systematics.sh`, i.e `region`, `observable` and `dir` variables should be changed according to what you wish to plot. Notice: dir variable should link to the src folder.
3. Run `./submit_jobs_exp_sys.sh`. Jobs for each systematic uncertainty and process (vbf, ggf, vh, htt, diboson, top, Zjets, Fakes) will be send to condor.
4. For each of the processes and systematic uncertainties a corresponding .root file is saved under the `sys_files` folder. Modify the `hadd_sys_files.sh` script by updating the `observable` variable with respect to what was declared at Step 2 and then run the script `./hadd_sys_files.sh`. All .root files will be hadded into a single .root file (i.e systematics.root) while at the same time contents under the directories `error`,`log` and `output` will be deleted. Rename the produced file `mv systematics.root observable_region_ExpSys.root` and move it inside the `exp_systematics` folder under the desired region folder.

Additional info:
* Before Step 4, one can check if the jobs ended successfully or failed. `grep -r "Error" ./error` will print out if anything went wrong. With the job id one can check for further details the corresponding files under `log` and `output` directories. There is also a script under `debugging` directory with which the .root files under `sys_files` directory are checked one by one and the problematic ones are printed out. In order to use this script do: 
```
cd debugging
root -l 
.L CheckFiles.C
checkFiles()
``` 
* The histogram binning can be changed in the `GetSystematics::setBins(bool forPaper)` function which is declared in `src/GetSystematics.h`. Important Notice: the same changes need to be passed in `plotting::setBins(bool forPaper)` function which is declared in `src/plotting.h`.
* Declare your cuts in `TreeReader::getCut()` function of `src/TreeReader.h` file.

### Theory uncertainties
This tool does not calculate theory uncertainties. Theory uncertainties are given as histograms (for Nominal and Up/Down variations) in root files which are found under `theo_systematics` folder. 
A debugging tool has been developed with the aim to be used to identify any problems with the theory inputs (it can be used for the experimental systematics checks too). For each systematic the nominal, up and down variations are plotted along with the total number of events for each component.

Produce the final plot
----------------------
The experimental and theory systematics need to be available as histograms stored in .root files under the directories `exp_systematics` and `theo_systematics` respectively. Once these files are present, the plotting tool can be used.

Usage:
1. `mkdir plots`. The requested plot will be saved under `plots` directory.
Run locally: 
2. Open root session in order to use the plotting tool.
```
root -l 
.L src/plotting.C
plotting("region","observable",unblind,forPaper,setAxesLimits,addTheo,lxplus)
OR
plotting("region", "observable",unblind,forPaper,addTheo,lxplus,y_min,y_max,"x_min",x_max,"y_ratio_min",y_ratio_max)
```
Arguments:
* region (string): choose among SR, TopCR, DYCR, WWCR, ggFCR1, ggFCR2, ggFCR3
* observable (string): choose among lep0_pt, lep1_pt, jet0_pt, jet1_pt, jet2_pt, Mjj, DPhill, DPhijj, DYjj, Mll, DYll, nJets, Ml0j0, Ml1j1, Ml0j1, Ml1j0, MET, jet0_eta, jet1_eta, lep0_eta, lep1_eta, Ptll, SignedDPhijj, MT, costhetastar, ptTot, sumOfCentralitiesL, pt_H, bdt_vbf, bdt_TopWWAll, bdt_ggFCR1, bdt_ggFCR2, bdt_ggFCR3
* unblind (bool): decides if data will be shown or not. Values: True or False.
* forPaper (bool): decides if the plot is for the supporting note or the paper. For the moment, set it to False. 
* setAxesLimits (bool): gives the ability to change the axes limits without diving in the code. Hint: at first set it to False to see the default limits and if needed change it to True to adjust the desired limits on axes. Values: True or False. 
* addTheo (bool): decides if the theory uncertainties will be taken into account in the error band.
* lxplus (bool): set it to True if you work on lxplus. For spar set it to False. 
* y_min and y_max (float): main pad y-axis limits
* x_min (string) and x_max (float): main and ratio pads x-axis limits
* y_ratio_min (string) and y_ratio (float): ratio pad y_axis limits

Job submission:
2. Modify the `submit_plots.sh`, `submit_jobs_plots.sh` and the corresponding configuration file under the path `./submission_files/plot_production/`and then run `./submit_jobs_plots.sh`. 

The resulting plot will be saved as pdf in the plots folder.
Additional info:
* xAxis labeling can be changed in function `std::string xAxisTitle(std::string observable)` of `src/TreeReader.h`
* many files are processed at the same time you can change the limit of the maximum number of open files in your system with `ulimit -n limit`, limit: any positive number ex. 2048.

### Pre-fit BDTs for each observable bin
Experimental systematic bands:

Step 1: Add the cut, e.g SR1Mjj_0 for Mjj in SR1 and bin-0, in `TreeReader::getCut()` function of `src/TreeReader.h` file.

Step 2: Define the region (e.g SR1Mjj_0) and observable (Mjj) in the script `submit_systematics.sh`

Step 3: Run `./submit_jobs_exp_sys.sh`

Step 4: Modify accordingly the hadd_sys_files.sh file and run `./hadd_sys_files.sh`. Rename (i.e name format: observable_region_ExpSys.root) and move the produced file under exp_systematics folder where a new folder with the name of the region already specified need to be created.

Once the experimental systematic band file is present the next step is to produce the pads to be combined, independently:

Step 1: Modify accordingly the `./submission_files/plot_production/submit_plots_prefit_BDT.sub` 

Step 2: Make sure that the correct configuration file is linked in submit_jobs_plots.sh and run `./submit_jobs_plots.sh`. The outputs are saved in prefit_bdt_inputs folder

Step 3: `cd src/plot_tools` and open a root session 
```
root -l
.L pre_fit_bdt.cpp
make_pre_fit_plot(binSR1,observable,setRatioLimits)
```
Arguments:
* binSR1 (int): total number of observable's bins in SR1 (and SR2)
* observable (string): the observable name
* setRatioLimits (bool): default is False. If set to True the ratio limits can be monitored on real time by the user. 
