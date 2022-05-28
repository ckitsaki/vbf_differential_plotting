#!/usr/bin/env python 

import glob, os, sys
import commands
from ROOT import *
from glob import *
import time
import math
from os.path import join as pjoin
import argparse

# inputs
inputs = "/afs/cern.ch/user/c/ckitsaki/private/paperPlotting/myPlotting/"

atlasLabel = "Internal"
uncVerticalLayout = False
centerTicks = False
noTicks = False

# load Atlas Style 
gROOT.LoadMacro("../src/Style/AtlasStyle.C")
gROOT.LoadMacro("../src/Style/AtlasUtils.C")
gROOT.LoadMacro("../src/Style/AtlasLabels.C")
SetAtlasStyle()

gStyle.SetEndErrorSize(8.0)
gROOT.SetBatch(True)
gStyle.SetOptStat(0)

# Helper functions
def myText(x,y,color,text,tsize,align=None):
	l=TLatex();
	l.SetTextSize(tsize);
	if align: l.SetTextAlign(30)
	l.SetNDC();
	l.SetTextFont(42);
	l.SetTextColor(color);
	l.DrawLatex(x,y,text);

def myTextBold(x,y,color,text,tsize):
	l=TLatex();
	l.SetTextSize(tsize);
	l.SetNDC();
	l.SetTextFont(62);
	l.SetTextColor(color);
	l.DrawLatex(x,y,text);

def changeName(poi):

    name=""
    if poi=="mu_Zjets":
        name="#mu Zjets"    
    if poi=="mu_Zjets_CRGGF":
    	name="#mu Zjets CRGGF"
    if poi=="mu_wwTop_SR0":
        name="#mu VV+Top-1"
    if poi=="mu_wwTop_SR1":
        name="#mu VV+Top-2"
    if poi=="mu_wwTop_SR2":
        name="#mu VV+Top-3"
    if poi=="mu_wwTop_SR3":
        name="#mu VV+Top-4"
    if poi=="mu_Zjets":
    	name="#mu Z+jets"
    if poi=="mu_Zjets_CRGGF1":
    	name="#mu Z+jets ggF"
    if poi=="mu_wwTop_CRGGF":
    	name="#mu VV+Top ggF"
    if poi=="mu_wwTop_SR":
		name="#mu VV+Top"
    if poi=="mu_ggf":
		name="#mu ggF"
    if poi=="mu_Zjets_CRGGF1":
		name="#mu Z+jets ggF"
    if poi=="mu_wwTop_CRGGF":
		name="#mu VV+Top ggF"
    return name

def main(args):

	output= path + "mu_" + observable + ".pdf"

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
	###################

	values = []

	
	theFile=file(pjoin(inputs, "mu_pre_merge.txt" )) 
	#my_input="./mu_observables/" + observable + ".txt"
	#theFile=file(pjoin(inputs, my_input))
	lines=theFile.readlines()
	
	for line in lines:
		name = line.split()[0]
		value = line.split('^')[0].split(name+' ')[1]
		total = line.split('^')[1]
		errorTot_u = total.split('}_{')[0].split('{+')[1]
		errorTot_d = total.split('_{-')[1].split('}')[0]
		errorStat = line.split('(tot)')[1].split('(stat)')[0]
		errorStat_u = errorStat.split('}_{')[0].split('{+')[1]
		errorStat_d = errorStat.split('_{-')[1].split('}')[0]
		errorSys = line.split('(stat)')[1].split('(sys)')[0]
		errorSys_u = errorSys.split('}_{')[0].split('{+')[1]
		errorSys_d = errorSys.split('_{-')[1].split('}')[0]

		values.append([changeName(name), value, errorTot_u, errorTot_d, errorStat_u, errorStat_d, errorSys_u, errorSys_d])

	print values

	xMax = 2.2
	xMin = 0.2
	xoffset = 0
	yUpOffset = 6 if not centerTicks else 5
	theHisto = TH2D("histo", "histo", 20 , xMin-xoffset, xMax+xoffset, len(values)+yUpOffset, 0, len(values)+yUpOffset)

	theHisto.GetYaxis().SetTickLength(0.00)

	theHisto.GetYaxis().SetNdivisions(int(len(values)+yUpOffset), False)

	theHisto.GetXaxis().SetTitleSize(0.03)
	xTitle = "N^{data}/N^{MC}"
	theHisto.GetXaxis().SetTitle(xTitle)

	theHisto.GetYaxis().SetLabelSize(0.035)

	theHisto.GetXaxis().SetTitleOffset(0.4)

	theHisto.GetYaxis().SetLabelFont(42)
	theHisto.GetXaxis().SetLabelFont(42)
	theHisto.GetYaxis().SetLabelOffset(0.004)
	theHisto.GetXaxis().SetLabelSize(0.025)

	theHisto.GetXaxis().SetLabelOffset(-0.01)

	theHisto.GetXaxis().SetLimits(xMin-xoffset, xMax+xoffset)
	theHisto.GetXaxis().SetTickLength(0.01)

	valAndTotUnc = TGraphAsymmErrors()
	valAndTotUnc.SetMarkerStyle(20)
	valAndTotUnc.SetMarkerSize(0.9)
	valAndTotUnc.SetMarkerColor(almostBlack)
	valAndTotUnc.SetLineWidth(2)
	valAndTotUnc.SetLineColor(veryDarkGrey)

	statBox = TGraphAsymmErrors()
	statBox.SetMarkerStyle(20)
	statBox.SetMarkerSize(0)
	statBox.SetMarkerColor(almostBlack)
	statBox.SetLineWidth(1)
	statBox.SetLineColor(veryDarkGrey)
	statBox.SetFillColor(veryLightAtlasRed)

	sysBox = TGraphAsymmErrors()
	sysBox.SetMarkerStyle(20)
	sysBox.SetMarkerSize(0)
	sysBox.SetMarkerColor(almostBlack)
	sysBox.SetLineWidth(1)
	sysBox.SetLineColor(veryDarkGrey)
	sysBox.SetFillColor(lightAtlasBlue)


	count=-1
	for obj in values:
		count+=1
		offset =1.5
		theHisto.GetYaxis().SetBinLabel(count+2,obj[0])
		yCoordinate = float(count+offset)
		valAndTotUnc.SetPoint( int(count), float(obj[1]), float(yCoordinate))
		valAndTotUnc.SetPointEXhigh( int(count), float(obj[2]))
		valAndTotUnc.SetPointEXlow( int(count), float(obj[3]))
		valAndTotUnc.SetPointEYhigh( int(count), float(0))
		valAndTotUnc.SetPointEYlow( int(count), float(0))

		statBox.SetPoint(int(count), float(obj[1]), float(yCoordinate-0.15)) #-.275
		statBox.SetPointEYhigh( int(count), float(0.15))
		statBox.SetPointEYlow( int(count), float(0.15))
		statBox.SetPointEXhigh(int(count), float(obj[4]))
		statBox.SetPointEXlow(int(count), float(obj[5]))

		sysBox.SetPoint(int(count), float(obj[1]), float(yCoordinate+0.15))
		sysBox.SetPointEYhigh(int(count), float(0.15))
		sysBox.SetPointEYlow(int(count), float(0.15))
		sysBox.SetPointEXhigh(int(count), float(obj[6]))
		sysBox.SetPointEXlow(int(count), float(obj[7]))


	canvas = TCanvas("canvas","canvas",600,1500)

	theHisto.Draw()
	valAndTotUnc.Draw("SAMEP")
	statBox.Draw("2SAMEP")
	sysBox.Draw("2SAMEP")
	valAndTotUnc.Draw("SAMEP")


	ATLASLabel(0.215,0.956," Internal", 1)
	myText(0.215,0.94,1,"#sqrt{#it{s}} = 13 TeV, 139 fb^{#minus1}",0.035)
	
	
	totalUncErrBar = TLine()
	totalUncErrBar.SetLineWidth(3)
	totalUncErrBar.SetLineColor(veryDarkGrey)
	X1 = (xMax) / 3 + .8
	Y1 = len(values) + 4.3
	X2 = X1 + .15
	Y2 = Y1
	totalUncErrBar.DrawLine(X1, Y1, X2, Y2)
	X1 = X1
	X2 = X1 
	Y1 -= 0.15
	Y2 += 0.15
	totalUncErrBar.DrawLine(X1, Y1, X2, Y2)
	X1 = X1 + 0.15
	X2 = X1
	totalUncErrBar.DrawLine(X1, Y1, X2, Y2)
	point = TMarker()
	point.SetMarkerStyle(kFullCircle)
	point.SetMarkerColor(almostBlack)
	X = X1 - 0.075
	Y = Y1 + 0.15
	point.DrawMarker(X,Y)

	statUncErrBox = TBox()
	statUncErrBox.SetFillColor(lightAtlasBlue)
	X1 = (xMax) / 3 + .95
	Y1 = len(values) + 2.5
	X1 = X1 - 0.15
	X2 = X1 + 0.15
	Y2 = Y1 + .8
	statUncErrBox.DrawBox(X1, Y1, X2, Y2)

	systUncErrBox = TBox()
	systUncErrBox.SetFillColor(veryLightAtlasRed)
	X1 = (xMax) / 3 + .95
	Y1 = len(values) + 1.
	X1 = X1 - 0.15
	X2 = X1 + 0.15
	Y2 = Y1 + 0.8
	systUncErrBox.DrawBox(X1, Y1, X2, Y2)

	gPad.SetLeftMargin(0.2)
	gPad.SetBottomMargin(0.1)
	gPad.SetTopMargin(0.02)

	myline0=TLine(0.2,8,2.2,8)
	myline1=TLine(0.2,15,2.2,15)
	myline2=TLine(0.2,22,2.2,22)
	myline3=TLine(0.2,28,2.2,28)
	myline4=TLine(0.2,34,2.2,34)
	myline5=TLine(0.2,40,2.2,40)
	myline6=TLine(0.2,46,2.2,46)
	myline7=TLine(0.2,54,2.2,54)
	myline8=TLine(0.2,61,2.2,61)
	myline9=TLine(0.2,67,2.2,67)
	myline10=TLine(0.2,73,2.2,73)
	myline11=TLine(0.2,79,2.2,79)
	myline12=TLine(0.2,86,2.2,86)
	
	myline0.Draw("same")
	myline1.Draw("same")
	myline2.Draw("same")
	myline3.Draw("same")
	myline4.Draw("same")
	myline5.Draw("same")
	myline6.Draw("same")
	myline7.Draw("same")
	myline8.Draw("same")
	myline9.Draw("same")
	myline10.Draw("same")
	myline11.Draw("same")
	myline12.Draw("same")

	t = TLatex()
	t.SetTextSize(.032)
	t.DrawLatex(1.8,93.,"Total")
	t.DrawLatex(1.8,91.5,"Stat. Unc.")
	t.DrawLatex(1.8,90.,"Sys. Unc.")
	
	t.DrawLatex(1.8,3,"#it{M}_{jj}") 
	t.DrawLatex(1.8,12,"#it{p}_{T}^{H}")
	t.DrawLatex(1.8,18,"#it{Dy}_{jj}")
	t.DrawLatex(1.8,25,"#it{p}_{T}^{jet_{0}}")
	t.DrawLatex(1.8,31,"#it{p}_{T}^{jet_{1}}")
	t.DrawLatex(1.8,37,"signed #it{D#phi}_{jj}")
	t.DrawLatex(1.8,43,"#it{D#phi}_{ll}")
	t.DrawLatex(1.8,49,"#it{cos}#theta*")
	t.DrawLatex(1.8,57,"#it{p}_{T}^{lep_{0}}")
	t.DrawLatex(1.8,63,"#it{p}_{T}^{lep_{1}}")
	t.DrawLatex(1.8,69,"#it{Dy}_{ll}")
	t.DrawLatex(1.8,75,"#it{M}_{ll}")
	t.DrawLatex(1.8,83,"#it{p}_{T}^{ll}")
	t.DrawLatex(1.8,88,"inclusive") 

	canvas.Print(output)


if __name__ == "__main__":
	parser=argparse.ArgumentParser(description='plotMaker')
	parser.add_argument('-p', '--path', type=str, default='./plots/mu_plots/', help='name of directory where results are located.')
	parser.add_argument('-obs','--observable', type=str, default='Mjj', help='observable')
	args = parser.parse_args()
	observable = args.observable
	path = args.path
	sys.argv=[]

	main(args);
