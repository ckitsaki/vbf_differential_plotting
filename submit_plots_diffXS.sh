#!/bin/sh
export ATLAS_LOCAL_ROOT_BASE=/cvmfs/atlas.cern.ch/repo/ATLASLocalRootBase
source ${ATLAS_LOCAL_ROOT_BASE}/user/atlasLocalSetup.sh 
setupATLAS
export ALRB_rootVersion=6.20.06-x86_64-centos7-gcc8-opt
lsetup root 

datatype=Data 

observable=$1
y_min=$2
ymax=$3
y_ratio_min=$4
ratio_ymax=$5
merged=$6
dir=/usatlas/u/ckitsaki/usatlasdata/supNote/vbf_differential_plotting/src/plot_tools
cd $dir
echo '==== plot production ===='
root -b -q -l "diff_xsec.C(\"$observable\", $merged, \"$datatype\", \"$y_min\", $ymax, \"$y_ratio_min\", $ratio_ymax)"
