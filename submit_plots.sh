#!/bin/sh
export ATLAS_LOCAL_ROOT_BASE=/cvmfs/atlas.cern.ch/repo/ATLASLocalRootBase
source ${ATLAS_LOCAL_ROOT_BASE}/user/atlasLocalSetup.sh 
setupATLAS
export ALRB_rootVersion=6.20.06-x86_64-centos7-gcc8-opt
lsetup root 

ulimit -n 2048
# choose among SR, WWCR, TopCR, DYCR, ggFCR1, ggFCR2, ggFCR3
unblind=true # lep0_pt, lep1_pt, Ptll, lep0_eta, lep1_eta, Mll, nJets, jet0_pt, jet1_pt, jet2_pt, Mjj, jet0_eta, jet1_eta, Ml0j0, Ml0j1, Ml1j0, Ml1j1, MET, MT, DYll, DYjj, DPhill, DPhijj, SignedDPhijj, costhetastar, ptTot, pt_H, sumOfCentralitiesL
forPaper=false
addTheo=true
lxplus=false

region=$1
observable=$2
y_min=$3
y_max=$4
x_min=$5
x_max=$6
y_ratio_min=$7
y_ratio_max=$8
dir=/usatlas/u/ckitsaki/usatlasdata/supNote/vbf_differential_plotting/src
cd $dir
echo '==== plot production ===='
root -b -q -l "plotting.C(\"$region\", \"$observable\", $unblind, $forPaper, $addTheo, $lxplus, $y_min, $y_max, \"$x_min\", $x_max, \"$y_ratio_min\", $y_ratio_max)"


#lxplus=false

#region1=$1
#region2=$2
#observable=$3
#y_min=$4
#y_max=$5
#x_min=$6
#x_max=$7
#y_ratio_min=$8
#y_ratio_max=$9

#dir=/usatlas/u/ckitsaki/usatlasdata/supNote/vbf_differential_plotting/src
#cd $dir
#echo '==== plot production ===='
#root -b -q -l "plotting.C(\"$region1\", \"$region2\", \"$observable\", $lxplus, $y_min, $y_max, \"$x_min\", $x_max, \"$y_ratio_min\", $y_ratio_max)"

