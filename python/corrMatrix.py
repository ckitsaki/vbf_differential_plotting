#!/usr/bin/env python 

import glob, os, sys
import commands
import ROOT
from ROOT import *
from glob import *
import time
import math
from os.path import join as pjoin
import argparse
import pandas as pd
import xlrd
from array import array

atlasLabel = "Internal"
uncVerticalLayout = False
centerTicks = False
noTicks = False

output = ""

# load Atlas Style 
gROOT.LoadMacro("../src/Style/AtlasStyle.C")
gROOT.LoadMacro("../src/Style/AtlasUtils.C")
gROOT.LoadMacro("../src/Style/AtlasLabels.C")
SetAtlasStyle()

gROOT.SetBatch(True)

# Helper functions
def str2bool(v):
	if isinstance(v, bool):
		return v
	if v.lower() in ('yes', 'true', 't', 'y', '1'):
		return True
	elif v.lower() in ('no', 'false', 'f', 'n', '0'):
		return False
	else:
		raise argparse.ArgumentTypeError('Boolean value expected.')

def myText(x,y,color,text,tsize,align=None):
	l=TLatex();
	l.SetTextSize(tsize);
	if align: l.SetTextAlign(30)
	l.SetNDC();
	l.SetTextFont(42);
	l.SetTextColor(color);
	l.DrawLatex(x,y,text);

def changeName(poi):

    name=""
    if poi=="sigma_bin0":
        name="#sigma_{1}"    
    if poi=="sigma_bin1":
        name="#sigma_{2}"        
    if poi=="sigma_bin2":
        name="#sigma_{3}"
    if poi=="sigma_bin3":
        name="#sigma_{4}"
    if poi=="sigma_bin4":
        name="#sigma_{5}"
    if poi=="sigma_bin5":
    	name="#sigma_{6}"
    if poi=="mu_wwTop_SR_0":
        name="N^{Data} / N^{MC} VV+Top-1"
    if poi=="mu_wwTop_SR_1":
        name="N^{Data} / N^{MC} VV+Top-2"
    if poi=="mu_wwTop_SR_2":
        name="N^{Data} / N^{MC} VV+Top-3"
    if poi=="mu_wwTop_SR_3":
        name="N^{Data} / N^{MC} VV+Top-4"
    if poi=="mu_Zjets":
    	name="N^{Data} / N^{MC} Z+jets"
    if poi=="mu_Zjets_CRGGF1":
    	name="N^{Data} / N^{MC} Z+jets ggF"
    if poi=="mu_wwTop_CRGGF":
    	name="N^{Data} / N^{MC} VV+Top ggF"
    if poi=="mu_wwTop_SR":
    	name="N^{Data} / N^{MC} VV+Top"
    if poi=="mu_ggf":
    	name="N^{Data} / N^{MC} ggF"
    if poi=="mu_Zjets_CRGGF1":
    	name="N^{Data} / N^{MC} Z+jets ggF"
    if poi=="mu_wwTop_CRGGF":
    	name="N^{Data} / N^{MC} VV+Top ggF"

    return name
##################################################


def main(args):

	if triangular:
		output="../plots/corMatrix_triang_" + observable + ".pdf"
	else:
		output="../plots/corMatrix.pdf"

	filename = 'corMatrix_' + observable + '.root'
	rootfile = TFile(filename,'RECREATE')


	##################
	# Color/fill settings
	creamYellow = TColor.GetColor("#FFFFCC")
	peelOrange = TColor.GetColor("#FF9900")
	pureBlue = kBlue
	portageBlue = TColor.GetColor("#9999FF")
	pureRed = kRed
	veryLightGrey = TColor.GetColor("#CCCCCC")
	pureGray = kGray
	veryDarkGrey = kGray+3
	almostBlack = TColor.GetColor("#141414")
	pureBlack = kBlack
	atlasOrange = TColor.GetColor("#F1910B")
	lightAtlasOrange = TColor.GetColor("#f8c87f")
	darkAtlasOrange = TColor.GetColor("#c23e01")
	robinBlue = TColor.GetColor("#262799")
	darkGreen = kGreen+2
	atlasBlue = TColor.GetColor("#0174ae")
	lightAtlasBlue = TColor.GetColor("#81d1f0")
	atlasRed = TColor.GetColor("#a92d31")
	darkAtlasRed = TColor.GetColor("#96282C")
	veryLightAtlasRed = TColor.GetColor("#dc979b")
	atlasWhite = kWhite

	inputs = "./corrMatrix_inputs/correlation_" + observable+ "_Data.xlsx"
	wb = xlrd.open_workbook(inputs)
	sheet = wb.sheet_by_index(0)

	histoname = 'corMatrix_' + observable
	corrMatrix = TH2D(histoname, observable, sheet.nrows-1, 0, sheet.nrows-1, sheet.ncols-1, 0, sheet.ncols-1)
	labels = []
	for ilabel in range(sheet.ncols):
		if not ilabel==0:
			labels.append(sheet.cell_value(0,ilabel))
			corrMatrix.LabelsOption("h","X")
			corrMatrix.GetXaxis().SetBinLabel(ilabel,changeName(sheet.cell_value(0,ilabel)))
			corrMatrix.GetYaxis().SetBinLabel(sheet.ncols-ilabel,changeName(sheet.cell_value(0,ilabel)))
	
	for numBin in range(corrMatrix.GetNbinsX()+1):
		if 'sigma' not in sheet.cell_value(0,numBin):
			corrMatrix.GetXaxis().ChangeLabel(numBin, 330, 0.018, 3, 1, 35, changeName(sheet.cell_value(0,numBin)))

	for icol in range(sheet.ncols):
		for irow in range(sheet.nrows):
			if icol!=0 and irow!=0:
				if triangular:
					if irow <= icol:
						#print(irow,icol)
						corrMatrix.SetBinContent(irow,sheet.ncols-icol,sheet.cell_value(irow,icol))
				else:
					corrMatrix.SetBinContent(irow,sheet.ncols-icol,sheet.cell_value(irow,icol))

	corrMatrix.GetXaxis().SetLabelSize(.03)
	corrMatrix.GetYaxis().SetLabelSize(.03)

	canvas = TCanvas("canvas","canvas",600,600)
	if triangular:
		gPad.SetLeftMargin(0.22)
		gPad.SetRightMargin(0.15)
		gPad.SetBottomMargin(0.25)
	else:
		gPad.SetLeftMargin(0.23)
		gPad.SetRightMargin(0.12)
		gPad.SetBottomMargin(0.25)
	corrMatrix.Draw("colztext")
	gStyle.SetPaintTextFormat("4.2f")
	corrMatrix.SetMarkerSize(.8);
	corrMatrix.GetXaxis().SetTickLength(0);
	corrMatrix.GetYaxis().SetTickLength(0);
	corrMatrix.GetZaxis().SetLabelSize(.025)
	corrMatrix.GetZaxis().SetTitleOffset(1.5)
	corrMatrix.GetZaxis().SetTitleSize(0.025)
	corrMatrix.GetZaxis().SetTitle("Correlation");
	canvas.SetBorderMode(0)
	canvas.SetBorderSize(0)
	canvas.SetFrameLineColor(0)
	canvas.SetFrameLineWidth(0)
	canvas.SetFrameBorderMode(0)
	corrMatrix.GetZaxis().SetRangeUser(-1, 1);

	Red    = [ 0.2, 1.00, 0.80]
	Green  = [ 0.45, 1.00, 0.50]
	Blue   = [ .6, 1., .3]
	Length = [ 0.00, 0.50, 1.00]
	lenghtArray = array('d', Length)
	redArray = array('d', Red)
	greenArray = array('d', Green)
	blueArray = array('d', Blue)

	TColor.CreateGradientColorTable(3,lenghtArray,redArray,greenArray,blueArray,50)
	corrMatrix.SetContour(50)

	if triangular:
		myText(0.62,0.88,1,"#bf{#it{ATLAS}} Internal",0.035)
		myText(0.62,0.82,1,"#sqrt{#it{s}} = 13 TeV, 139 fb^{#minus1}",0.025)
	else:
		ATLASLabel(0.235,.955,atlasLabel, 1)
		myText(0.57,0.955,1,"#sqrt{#it{s}} = 13 TeV, 139 fb^{#minus1}",0.018)
		myText(0.738,0.955,1,"#it{H} #rightarrow #it{WW}* #rightarrow #it{e#nu#mu#nu}",0.018)

	canvas.Print(output)
	rootfile.cd()
	corrMatrix.Write()


if __name__ == "__main__":
	from argparse import ArgumentParser
	parser=argparse.ArgumentParser(description='make correlation matrix')
	parser.add_argument('-tr','--triangular', type=str2bool, default=False, help='set it to true for a triangular matrix')
	parser.add_argument('-obs','--observable', type=str, default='Mjj', help='observable')
	args = parser.parse_args()
	triangular = args.triangular
	observable = args.observable
	if triangular==True:
		print("Creating a triangular matrix...\n")
	main(args);
