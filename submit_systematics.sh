#!/bin/sh
export ATLAS_LOCAL_ROOT_BASE=/cvmfs/atlas.cern.ch/repo/ATLASLocalRootBase
source ${ATLAS_LOCAL_ROOT_BASE}/user/atlasLocalSetup.sh 
setupATLAS
export ALRB_rootVersion=6.20.06-x86_64-centos7-gcc8-opt
lsetup root 
region="ggFCR2" # choose among SR, WWCR, TopCR, DYCR, ggFCR1, ggFCR2, ggFCR3
observable="costhetastar" # lep0_pt, lep1_pt, Ptll, lep0_eta, lep1_eta, Mll, nJets, jet0_pt, jet1_pt, jet2_pt, Mjj, jet0_eta, jet1_eta, Ml0j0, Ml0j1, Ml1j0, Ml1j1, MET, MT, DYll, DYjj, DPhill, DPhijj, SignedDPhijj, costhetastar, ptTot, pt_H, sumOfCentralitiesL
campaign="c16a"
forPaper="false"
sample=$1
sys_name=$2
JER=$3
MET=$4
other=$5
dir=/afs/cern.ch/user/c/ckitsaki/private/paperPlotting/vbf_differential_plotting/src
cd $dir
echo 'dumping systematics'
root -b -q -l "GetSystematics.C(\"$region\", \"$observable\", \"$sample\", \"$campaign\", \"$sys_name\", \"$JER\", \"$MET\", \"$other\", \"$forPaper\")"
campaign="c16d"
root -b -q -l "GetSystematics.C(\"$region\", \"$observable\", \"$sample\", \"$campaign\", \"$sys_name\", \"$JER\", \"$MET\", \"$other\", \"$forPaper\")"
campaign="c16e"
root -b -q -l "GetSystematics.C(\"$region\", \"$observable\", \"$sample\", \"$campaign\", \"$sys_name\", \"$JER\", \"$MET\", \"$other\", \"$forPaper\")"
