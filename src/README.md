# How to make the detector level plots pre-fit we have in the paper: 

you should work inside the `src` dir.
```
cd src
root -l
.L plotting.C
```
and then call the appropriate function as listed below 
**but before be sure you're**
**using the correct theory inputs** [lines to be changed](https://gitlab.cern.ch/ckitsaki/vbf_differential_plotting/-/blob/master/src/plotting.C#L96-97)

## SIGNAL REGION 
### MT, Mll, jet0_pt, sumOfCentralitiesL, DYll, jet0_eta, jet1_eta, jet1_pt, SignedDPhijj, Ml0j0
theory unc files to be used

"/usatlas/u/sagar/usatlaswork/scripts/CharaStackPlotsHists/StackPlots_22Feb2022/"+ sample + "_histos_2jets.root";

"/usatlas/u/sagar/usatlaswork/scripts/CharaStackPlotsHists/StackPlots_22Feb2022/diboson-ewk_histos_2jets.root";

- plotting("SR","MT",1,0,1,0,0,300,"0",250,"0.6",1.4,false)
- plotting("SR","Mll",1,0,1,0,0,300,"0",200,"0.",2,false)
- plotting("SR","jet0_pt",1,0,1,0,0,150,"0",310,"0.2",1.6,false)
- plotting("SR","sumOfCentralitiesL",1,0,1,0,0,350,"0",2,"0.2",1.6,false)
- plotting("SR","DYll",1,0,1,0,0,650,"0",4.5,"0.5",1.5,false)
- plotting("SR","jet0_eta",1,0,1,0,0,300,")-4.5",4.5,"0.6",1.3,false)
- plotting("SR","jet1_eta",1,0,1,0,0,300,")-4.5",4.5,"0.5",1.5,false)
- plotting("SR","jet1_pt",1,0,1,0,0,600,"0",200,"0.",2,false)
- plotting("SR","SignedDPhijj",1,0,1,0,0,150,")-3.14",3.14,"0.5",1.5,false)
- plotting("SR","Ml0j0",1,0,1,0,0,200,"0",600,"0.5",1.5,false)

### DPhill, DYjj, Mjj
theory unc files to be used

"/usatlas/u/sagar/usatlaswork/scripts/CharaStackPlotsHists/StackPlots_Rebin_SR12_1Jun2022/"+ sample + "_histos_SR.root";

"/usatlas/u/sagar/usatlaswork/scripts/CharaStackPlotsHists/StackPlots_Rebin_SR12_1Jun2022/diboson-ewk_histos_SR.root";

- plotting("SR","DPhill",1,1,1,0,0,1500,"0",1.4,"0.6",1.3,true)

- plotting("SR","DYjj",1,1,1,0,0,600,"2.1",9,"0.6",1.3,true)

We show Mjj in log scale comment out [this line](https://gitlab.cern.ch/ckitsaki/vbf_differential_plotting/-/blob/master/src/plotting.C#L1063)

- plotting("SR","Mjj",1,1,1,0,1e-04,1e+04,"450",6000,"0.6",1.3,true)

### BDT_VBF
theory unc files to be used
"/usatlas/u/sagar/usatlaswork/scripts/CharaStackPlotsHists/StackPlots_Rebin_SR12_1Jun2022/"+ sample + "_histos_SR12.root";

"/usatlas/u/sagar/usatlaswork/scripts/CharaStackPlotsHists/StackPlots_Rebin_SR12_1Jun2022/diboson-ewk_histos_SR12.root";

- plotting("SR1","bdt_vbf",1,1,1,0,0,2500,"0.5",1,"0.7",1.3,true)
- plotting("SR2","bdt_TopWWAll",1,1,1,0,0,800,")-1",1,"0.7",1.3,false)


### GGFCR
"/usatlas/u/sagar/usatlaswork/scripts/CharaStackPlotsHists/StackPlots_22Feb2022/"+ sample + "_histos_2jets.root";

"/usatlas/u/sagar/usatlaswork/scripts/CharaStackPlotsHists/StackPlots_22Feb2022/diboson-ewk_histos_2jets.root";

**USE THE CORRECT BINNING for MT** [here](https://gitlab.cern.ch/ckitsaki/vbf_differential_plotting/-/blob/master/src/plotting.h#L173-181)
- plotting("ggFCR1","MT",1,0,1,0,0,6000,"0",250,"0.8",1.2,false) 
- plotting("ggFCR1","DYll",1,0,1,0,0,10000,"0",4,"0.7",1.3,false)
- plotting("ggFCR1","Mll",1,0,1,0,0,4500,"0",200,"0.7",1.3,false)
- plotting("ggFCR1","DPhill",1,0,1,0,0,8000,"0",1.56,"0.8",1.2,false)
- plotting("ggFCR1","bdt_ggFCR1",1,1,1,0,0,12000,")-1",1,"0.85",1.15,false)
- plotting("ggFCR1","SignedDPhijj",1,0,1,0,0,2200,")-3.14",3.14,"0.8",1.2,false)
- plotting("ggFCR1","MET",1,0,1,0,0,3500,"0",250,"0.7",1.3,false)
- plotting("ggFCR1","jet0_pt",1,0,1,0,0,4100,"0",310,"0.7",1.3,false)
- plotting("ggFCR1","jet1_pt",1,0,1,0,0,11000,"0",210,"0.6",1.4,false)

### Z+JETS CR
"/usatlas/u/sagar/usatlaswork/scripts/CharaStackPlotsHists/StackPlots_MT/"+ sample + "_histos_MT.root";

"/usatlas/u/sagar/usatlaswork/scripts/CharaStackPlotsHists/StackPlots_22Feb2022/diboson-ewk_histos_2jets.root";

- plotting("DYCR","MT",1,0,1,0,0,520,"40",150,"0.",2,false)
