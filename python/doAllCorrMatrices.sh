#!/bin/sh

echo '==== produce correlation matrices ===='
declare -a observables=(costhetastar DYjj DPhill Mjj Mll lep0_pt lep1_pt jet0_pt jet1_pt SignedDPhijj Ptll pt_H inc DYll)
for iobservable in ${observables[@]}; do
	echo $iobservable
	python corrMatrix.py --triangular True --observable $iobservable
done

hadd correlationMatrices.root *.root 
rm corMatrix_*.root
