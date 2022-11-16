# Correlation Matrices

Run
```
./doAllCorrMatrices.sh
```
the correlation matrices for all the observables are saved under ../plots directory in pdf format. The matrices are saved as 2D histograms in the file correlationMatrices.root which is created with the above command.

If the user wants to create one correlation matrix at a time then simply run 
```
python corMatrix.py --triangular True --observable observableName
```
the final produced plot as pdf will be saved under ../plots and the root file corMatrix_observableName.root is created in the current directory. 
