#!/bin/sh
export ATLAS_LOCAL_ROOT_BASE=/cvmfs/atlas.cern.ch/repo/ATLASLocalRootBase
source ${ATLAS_LOCAL_ROOT_BASE}/user/atlasLocalSetup.sh 
setupATLAS
export ALRB_rootVersion=6.20.06-x86_64-centos7-gcc8-opt
lsetup root 

ulimit -n 2048
#ulimit -s 65536

region=$1
observable=$2
obsBins=$3
x_min=$4
x_max=$5
y_min=$6
y_max=$7
y_ratio_min=$8
y_ratio_max=$9
pad_xmin=${10}
pad_xmax=${11}
pad_ymin=${12}
pad_ymax=${13}
ratiopad_ymin=${14}
ratiopad_ymax=${15}
forPaper=${16}
multfactor=${17}

dir=/usatlas/u/ckitsaki/usatlasdata/supNote/vbf_differential_plotting/src
cd $dir
echo '==== plot production ===='
root -b -q -l "plotting.C(\"$region\", \"$observable\", $obsBins, $forPaper, $y_min, $y_max, \"$x_min\", $x_max, \"$y_ratio_min\", $y_ratio_max, $pad_xmin, $pad_xmax, $pad_ymin, $pad_ymax, $ratiopad_ymin, $ratiopad_ymax, \"$multfactor\")"
