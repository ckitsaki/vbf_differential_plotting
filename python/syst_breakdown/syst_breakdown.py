#!/usr/bin/env python 
from astropy.table import Table
import ROOT
from ROOT import *
import argparse
import numpy as np
# In order to use this script set up a virtual environment.
# $ mkdir venv
# $ python3 -m vevn venv
# $ source venv/bin/activate
# $ python3 -m pip install astropy
# $ python3 -m pip install pyroot
# $ setupATLAS
# $ lsetup "root 6.26.04-x86_64-centos7-gcc11-opt"
# $ python3 sys_breakdown.py --observable SignedDPhijj --ymax 4e+03 --logY True --bins 4
# $ python3 sys_breakdown.py --observable pt_H --ymax 2e+04 --logY True --bins 4
# $ python3 sys_breakdown.py --observable DYjj --ymax 4e+03 --logY True --bins 5
# $ python3 sys_breakdown.py --observable Mjj --ymax 1e+05 --logY True --bins 5
# $ python3 sys_breakdown.py --observable jet1_pt --ymax 2e+04 --logY True --bins 4
# $ python3 sys_breakdown.py --observable jet0_pt --ymax 1e+04 --logY True --bins 4
# $ python3 sys_breakdown.py --observable costhetastar --ymax 4e+03 --logY True --bins 5
# $ python3 sys_breakdown.py --observable Mll --ymax 1e+05 --logY True --bins 4
# $ python3 sys_breakdown.py --observable DPhill --ymax 4e+03 --logY True --bins 5
# $ python3 sys_breakdown.py --observable lep1_pt --ymax 4e+03 --logY True --bins 4
# $ python3 sys_breakdown.py --observable lep0_pt --ymax 3e+04 --logY True --bins 5
# $ python3 sys_breakdown.py --observable Ptll --ymax 4e+03 --logY True --bins 4
# $ python3 sys_breakdown.py --observable DYll --ymax 5e+04 --logY True --bins 4

def setXaxisTitle(observable):
	xaxistitle = ''
	if(observable=='Mjj'):
		xaxistitle = '#it{m}_{jj} [GeV]'
	if(observable=='DYll'):
		xaxistitle = '#it{#Delta y}_{ll}'
	if(observable=="DYjj"):
		xaxistitle = '#it{#Delta y}_{jj}'
	if(observable=="DPhill"):
		xaxistitle = '#it{#Delta#phi}_{ll} [rad]'
	if(observable=="Mll"):
		xaxistitle = '#it{m}_{ll} [GeV]'
	if(observable=='jet0_pt'):
		xaxistitle = '#it{p}_{T}^{jet_{0}} [GeV]'
	if(observable=='jet1_pt'):
		xaxistitle = '#it{p}_{T}^{jet_{1}} [GeV]'
	if(observable=='lep0_pt'):
		xaxistitle = '#it{p}_{T}^{lep_{0}} [GeV]'
	if(observable=='lep1_pt'):
		xaxistitle = '#it{p}_{T}^{lep_{1}} [GeV]'
	if(observable=='pt_H'):
		xaxistitle = '#it{p}_{T}^{H} [GeV]'
	if(observable=='Ptll'):
		xaxistitle = '#it{p}_{T}^{ll} [GeV]'
	if(observable=='costhetastar'):
		xaxistitle = '#it{cos#theta}_{#eta}*'
	if(observable=='SignedDPhijj'):
		xaxistitle = '#it{#Delta#phi}_{jj} [rad]'
	return xaxistitle

def main(args):
	gROOT.LoadMacro("../src/Style/AtlasStyle.C")
	gROOT.LoadMacro("../src/Style/AtlasUtils.C")
	gROOT.LoadMacro("../src/Style/AtlasLabels.C")
	SetAtlasStyle()
	gROOT.SetBatch(True)

	lavender = TColor.GetColor("#dcbeff")
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

	bin_file = open('./inputs/binning.txt','r')
	lines = bin_file.readlines()
	line = []
	for iline in lines:
		if observable in iline.strip():
			iline.strip().split()
			line.append(iline.strip().split())
	bins_c = []
	#print(line[0][1])
	data = '/usatlas/u/sagar/usatlaswork/scripts/XSPlotsChara/HistMergingGraphs/XSPlot_Data_' + str(observable) + '.root'
	file = TFile(data,"READ")
	obj_statOnly = observable + '_StatOnly'
	statOnly = file.Get(obj_statOnly)
	obj_total = observable + '_StatSys'
	statSys = file.Get(obj_total)
	
	for ibin in range(statSys.GetN()+1):
		bins_c.append(float(line[0][ibin+1]))

	my_array = np.array(bins_c)
	h_totUnc = TH1D("h_totUnc", "h_totUnc", bins, np.array(bins_c))
	h_statUnc = TH1D("h_statUnc", "h_statUnc", bins, np.array(bins_c))
	#print(bins)
	for ibin in range(statSys.GetN()):
		#print(statOnly.GetPointY(ibin))
		#print(statSys.GetErrorY(ibin)/statOnly.GetPointY(ibin))
		h_totUnc.SetBinContent(ibin+1, statSys.GetErrorY(ibin)/statOnly.GetPointY(ibin)*100)
		h_statUnc.SetBinContent(ibin+1, statOnly.GetErrorY(ibin)/statOnly.GetPointY(ibin)*100)

	#print(bins_c)
	table_file = './inputs/ws_noGGF2_' + observable + '_Data.root_data_breakdown_reverse_rel.tex'
	tab = Table.read(table_file)
	rows = tab.pformat_all()

	#tab.pprint()
	
	columns_to_read = []
	for ibin in range(bins):
		name = f'sigma bin{ibin}'
		columns_to_read.append(name)

	lumi, fakes, signal_model, signal_pshower, lepton_model, jetmet, zjets_model, diboson_model, top_model, ggf_model, b_tag, mcstat = ([] for i in range(12))
	#, totunc = ([] for i in range(13))

	for i in range(len(columns_to_read)):
		column = tab[columns_to_read[i]]
		lumi.append(column[1]) #luminosity
		fakes.append(column[2])
		signal_model.append(column[11])
		signal_pshower.append(column[10])
		lepton_model.append(column[5])
		jetmet.append(column[4])
		zjets_model.append(column[6])
		diboson_model.append(column[7])
		top_model.append(column[8])
		ggf_model.append(column[9])
		b_tag.append(column[3])
		mcstat.append(column[0])
		#totunc.append(column[12])

	for elem in range(len(lumi)):
		newlumi = str(lumi[elem]).replace('$', '').replace('<', '')
		newfakes = str(fakes[elem]).replace('$','').replace('<','')
		newsignal_model = str(signal_model[elem]).replace('$','').replace('<','')
		newsignal_pshower = str(signal_pshower[elem]).replace('$','').replace('<','')
		newlepton_model = str(lepton_model[elem]).replace('$','').replace('<','')
		newjetmet = str(jetmet[elem]).replace('$','').replace('<','')
		newzjets_model = str(zjets_model[elem]).replace('$','').replace('<','')
		newdiboson_model = str(diboson_model[elem]).replace('$','').replace('<','')
		newtop_model = str(top_model[elem]).replace('$','').replace('<','')
		newggf_model = str(ggf_model[elem]).replace('$','').replace('<','')
		newbtag = str(b_tag[elem]).replace('$','').replace('<','')
		newmcstat = str(mcstat[elem]).replace('$','').replace('<','')
		#newtotunc = str(totunc[elem]).replace('$','').replace('<','')

		lumi[elem] = newlumi
		fakes[elem] = newfakes
		signal_model[elem] = newsignal_model
		signal_pshower[elem] = newsignal_pshower
		lepton_model[elem] = newlepton_model
		jetmet[elem] = newjetmet
		zjets_model[elem] = newzjets_model
		diboson_model[elem] = newdiboson_model
		top_model[elem] = newtop_model
		ggf_model[elem] = newggf_model
		b_tag[elem] = newbtag
		mcstat[elem] = newmcstat
		#totunc[elem] = newtotunc

	canvas = TCanvas("canvas","canvas",600,600)
	h_lumi = TH1D("lumi", "lumi",  bins, np.array(bins_c))
	h_fakes = TH1D("fakes", "fakes",  bins, np.array(bins_c))
	h_signal_model = TH1D("sigmodel", "sigmodel",  bins, np.array(bins_c))
	h_signal_pshower = TH1D("h_signal_pshower", "h_signal_pshower", bins, np.array(bins_c))
	h_lepton_model = TH1D("h_lepton_model", "h_lepton_model", bins, np.array(bins_c))
	h_jetmet = TH1D("h_jetmet", "h_jetmet", bins, np.array(bins_c))
	h_bkg_model = TH1D("h_bkg_model", "h_bkg_model", bins, np.array(bins_c))
	h_btag = TH1D("h_btag", "h_btag",  bins, np.array(bins_c))
	h_MCstat = TH1D("h_MCstat", "h_MCstat",  bins, np.array(bins_c))
	
	binSize = len(lumi)
	if observable == "DYll":
		binSize = len(lumi)-1
		h_lumi.SetBinContent(binSize+1, 3.5)
		h_fakes.SetBinContent(binSize+1, 3.5)
		h_signal_model.SetBinContent(binSize+1, 3.5)
		h_signal_pshower.SetBinContent(binSize+1, 3.5)
		h_lepton_model.SetBinContent(binSize+1, 3.5)
		h_jetmet.SetBinContent(binSize+1, 100*TMath.Sqrt( (0.19+0.198)*(0.19+0.198)/4 + (0.159+0.142)*(0.159+0.142)/4 + (0.105+0.106)*(0.105+0.106)/4 +(0.073+0.081)*(0.073+0.081)/4 + (0.079+0.075)*(0.079+0.075)/4 + (0.059+0.075)*(0.059+0.075)/4 + (0.053+0.073)*(0.053+0.073)/4 + (0.058+0.067)*(0.058+0.067)/4 + (0.056+0.048)*(0.056+0.048)/4 + (0.041+0.046)*(0.041+0.046)/4 + (0.040+0.042)*(0.040+0.042)/4 + (0.043+0.03)*(0.043+0.03)/4 ))
		h_MCstat.SetBinContent(binSize+1, 100*TMath.Sqrt( (0.334+0.306)*(0.334+0.306)/4 + (0.235+0.218)*(0.235+0.218)/4 + (0.155+0.149)*(0.155+0.149)/4 + (0.089+0.095)*(0.089+0.095)/4 + (0.072+0.067)*(0.072+0.067)/4 + (0.045+0.043)*(0.045+0.043)/4 + (0.029+0.040)*(0.029+0.040)/4 ) )
		h_bkg_model.SetBinContent(binSize+1, 100*TMath.Sqrt( (0.066+0.063)*(0.066+0.063)/4 + (0.063+0.064)*(0.063+0.064)/4 + (0.062+0.065)*(0.062+0.065)/4 + (0.068+0.05)*(0.068+0.05)/4 + (0.063+0.047)*(0.063+0.047)/4 + (0.084+0.017)*(0.084+0.017)/4 + (0.057+0.026)*(0.057+0.026)/4  ) )
		h_btag.SetBinContent(binSize+1, 3.5)

	for ibin in range(binSize):
		h_lumi.SetBinContent(ibin+1, float(lumi[ibin]))
		h_fakes.SetBinContent(ibin+1, float(fakes[ibin]))
		h_signal_model.SetBinContent(ibin+1, float(signal_model[ibin]))
		h_signal_pshower.SetBinContent(ibin+1, float(signal_pshower[ibin]))
		h_lepton_model.SetBinContent(ibin+1, float(lepton_model[ibin]))
		h_jetmet.SetBinContent(ibin+1, float(jetmet[ibin]))
		h_bkg_model.SetBinContent(ibin+1, TMath.Sqrt( float(zjets_model[ibin])*float(zjets_model[ibin]) + float(diboson_model[ibin])*float(diboson_model[ibin]) + float(top_model[ibin])*float(top_model[ibin]) + float(ggf_model[ibin])*float(ggf_model[ibin])))
		h_btag.SetBinContent(ibin+1, float(b_tag[ibin]))
		h_MCstat.SetBinContent(ibin+1, float(mcstat[ibin]))
		#h_totUnc.SetBinContent(ibin+1, float(totunc[ibin]))
	if(logY==True):
		h_lumi.GetYaxis().SetRangeUser(1e+00,ymax)
	else:
		h_lumi.GetYaxis().SetRangeUser(0,ymax)

	h_lumi.GetYaxis().SetTitle("Relative Uncertainty [%]")
	h_lumi.GetXaxis().SetTitle(setXaxisTitle(observable))
	h_lumi.GetYaxis().SetLabelSize(.035)
	h_lumi.GetXaxis().SetLabelSize(.035)
	h_lumi.GetXaxis().SetTitleSize(.035)
	h_lumi.GetYaxis().SetTitleSize(.035)
	h_lumi.GetXaxis().SetLabelOffset(10)
	h_lumi.GetYaxis().SetLabelOffset(.01)
	h_lumi.GetYaxis().SetTitleOffset(1.5)

	h_lumi.GetXaxis().SetTickLength(0)
	h_lumi.SetLineColor(peelOrange)
	h_fakes.SetLineColor(kCyan)
	h_signal_model.SetLineColor(kRed+1)
	h_signal_pshower.SetLineColor(kRed+1)
	h_lepton_model.SetLineColor(kAzure+2)
	h_jetmet.SetLineColor(darkGreen)
	h_bkg_model.SetLineColor(kOrange-8)
	h_btag.SetLineColor(kPink+1)
	h_MCstat.SetLineColor(15)
	h_statUnc.SetLineColor(15)
	h_totUnc.SetLineColor(kBlack)

	h_signal_model.SetLineStyle(2)
	h_signal_pshower.SetLineStyle(3)
	h_bkg_model.SetLineStyle(4)
	h_fakes.SetLineStyle(5)
	h_jetmet.SetLineStyle(6)
	h_btag.SetLineStyle(7)
	h_lepton_model.SetLineStyle(8)
	h_lumi.SetLineStyle(9)
	h_MCstat.SetLineStyle(kDashed)

	if(logY==True):
		gPad.SetLogy()
	h_lumi.Draw()
	h_signal_model.Draw("same")
	h_lepton_model.Draw("same")
	h_MCstat.Draw("same")
	h_jetmet.Draw("same")
	h_btag.Draw("same")
	h_fakes.Draw("same")
	h_statUnc.Draw("same")
	h_totUnc.Draw("same")
	h_bkg_model.Draw("same")
	h_signal_pshower.Draw("same")

	latex = TLatex()
	if(observable=="Mjj"):
		for i in range(len(bins_c)-1):
			character = "#scale[.7]{" + char(int(bins_c[i])) + "}"
			latex.DrawLatex(bins_c[i]-50,5.5e-01,character)
		latex.DrawLatex(3100,5.5e-01,"#scale[.7]{6000}")
	if(observable=="Mll"):
		for i in range(len(bins_c)-1):
			character = "#scale[.7]{" + char(int(bins_c[i])) + "}"
			latex.DrawLatex(bins_c[i]-1,5.5e-01,character)
		latex.DrawLatex(98,5.5e-01,"#infty")
	if(observable=="Ptll"):
		for i in range(len(bins_c)-1):
			character = "#scale[.7]{" + char(int(bins_c[i])) + "}"
			latex.DrawLatex(bins_c[i]-3,6.5e-01,character)
		latex.DrawLatex(220,6.5e-01,"#scale[.7]{1000}")
	if(observable=="jet0_pt"):
		for i in range(len(bins_c)-1):
			character = "#scale[.7]{" + char(int(bins_c[i])) + "}"
			latex.DrawLatex(bins_c[i]-5,6.5e-01,character)
		latex.DrawLatex(410,6.5e-01,"#scale[.7]{700}")
	if(observable=="jet1_pt"):
		for i in range(len(bins_c)-1):
			character = "#scale[.7]{" + char(int(bins_c[i])) + "}"
			latex.DrawLatex(bins_c[i]-2,6.5e-01,character)
		latex.DrawLatex(175,6.5e-01,"#scale[.7]{350}")		
	if(observable=="lep0_pt"):
		for i in range(len(bins_c)-1):
			character = "#scale[.7]{" + char(int(bins_c[i])) + "}"
			latex.DrawLatex(bins_c[i]-1,6.e-01,character)
		latex.DrawLatex(185,6.e-01,"#scale[.7]{350}")
	if(observable=="lep1_pt"):
		for i in range(len(bins_c)-1):
			character = "#scale[.7]{" + char(int(bins_c[i])) + "}"
			latex.DrawLatex(bins_c[i]-1,6.5e-01,character)
		latex.DrawLatex(97,6.5e-01,"#scale[.7]{200}")
	if(observable=="pt_H"):
		for i in range(len(bins_c)-1):
			character = "#scale[.7]{" + char(int(bins_c[i])) + "}"
			latex.DrawLatex(bins_c[i]-5,6.5e-01,character)
		latex.DrawLatex(380,6.e-01,"#scale[.7]{850}")
	if(observable=="DYjj"):
		for i in range(len(bins_c)):
			character = "#scale[.7]{" + char(bins_c[i]) + "}"
			latex.DrawLatex(bins_c[i]-0.1,6.5e-01,character)
	if(observable=="costhetastar"):
		for i in range(len(bins_c)-1):
			character = "#scale[.7]{" + char(round(bins_c[i],2)) + "}"
			latex.DrawLatex(bins_c[i]-0.01,6.5e-01,character)
		latex.DrawLatex(0.58,6.5e-01,"#scale[.7]{1.0}")
	if(observable=="SignedDPhijj"):
		for i in range(len(bins_c)):
			character = "#scale[.7]{" + char(round(bins_c[i],2)) + "}"
			latex.DrawLatex(bins_c[i]-0.2,6.5e-01,character)
	if(observable=="DPhill"):
		for i in range(len(bins_c)):
			character = "#scale[.7]{" + char(bins_c[i]) + "}"
			latex.DrawLatex(bins_c[i]-0.05,6.5e-01,character)
	if(observable=="DYll"):
		for i in range(len(bins_c)-1):
			character = "#scale[.7]{" + char(bins_c[i]) + "}"
			latex.DrawLatex(bins_c[i]-0.01,6.5e-01,character)
		latex.DrawLatex(bins_c[len(bins_c)-1]-0.01,6.5e-01,"#infty")
	legend = TLegend(0.2,0.6,.92,0.85);
	legend.SetBorderSize(0)
	legend.SetFillStyle(0)
	legend.SetTextSize(0.)
	legend.SetNColumns(2)
	legend.AddEntry(h_signal_model, '#bf{Signal modelling}', 'l')
	legend.AddEntry(h_signal_pshower, '#bf{Signal parton shower}', 'l')
	legend.AddEntry(h_bkg_model, '#bf{Background modelling}', 'l')
	legend.AddEntry(h_fakes, '#bf{Mis-Id. background}', 'l')
	legend.AddEntry(h_jetmet, '#bf{Jets + MET}', 'l')
	legend.AddEntry(h_btag, '#bf{b-tagging}', 'l')
	legend.AddEntry(h_lepton_model, '#bf{Leptons}', 'l')
	legend.AddEntry(h_lumi, '#bf{Luminosity}', 'l')
	legend.AddEntry(h_statUnc, '#bf{MC statistics}', 'l')
	legend.AddEntry(h_totUnc, '#bf{Tot. Uncertainty}', 'l')
	legend.Draw()

	atlastex = TLatex()
	atlastex.SetTextSize(.04)

	if(logY==True):
		if(observable=="Mll"):
			atlastex.DrawLatex( 15, 0.35*ymax, "#it{#bf{#scale[1.2]{ATLAS}}}  Internal")
			atlastex.DrawLatex( 60, 0.35*ymax, "#sqrt{#scale[.8]{s}} #scale[.8]{= 13 TeV,} #scale[.8]{139 fb^{-1}}")
		if(observable=="Mjj"):
			atlastex.DrawLatex( 600, 0.35*ymax, "#it{#bf{#scale[1.2]{ATLAS}}}  Internal")
			atlastex.DrawLatex(2100, 0.35*ymax, "#sqrt{#scale[.8]{s}} #scale[.8]{= 13 TeV,} #scale[.8]{139 fb^{-1}}")
		if(observable=="Ptll"):
			atlastex.DrawLatex( 15, 0.5*ymax, "#it{#bf{#scale[1.2]{ATLAS}}}  Internal")
			atlastex.DrawLatex( 140, 0.5*ymax, "#sqrt{#scale[.8]{s}} #scale[.8]{= 13 TeV,} #scale[.8]{139 fb^{-1}}")
		if(observable=="lep0_pt"):
			atlastex.DrawLatex( 30, 0.4*ymax, "#it{#bf{#scale[1.2]{ATLAS}}}  Internal")
			atlastex.DrawLatex( 120, 0.4*ymax, "#sqrt{#scale[.8]{s}} #scale[.8]{= 13 TeV,} #scale[.8]{139 fb^{-1}}")
		if(observable=="lep1_pt"):
			atlastex.DrawLatex( 20, 0.5*ymax, "#it{#bf{#scale[1.2]{ATLAS}}}  Internal")
			atlastex.DrawLatex( 60, 0.5*ymax, "#sqrt{#scale[.8]{s}} #scale[.8]{= 13 TeV,} #scale[.8]{139 fb^{-1}}")
		if(observable=="pt_H"):
			atlastex.DrawLatex( 20, 0.4*ymax, "#it{#bf{#scale[1.2]{ATLAS}}}  Internal")
			atlastex.DrawLatex( 220, 0.4*ymax, "#sqrt{#scale[.8]{s}} #scale[.8]{= 13 TeV,} #scale[.8]{139 fb^{-1}}")
		if(observable=="jet0_pt"):
			atlastex.DrawLatex( 60, 0.4*ymax, "#it{#bf{#scale[1.2]{ATLAS}}}  Internal")
			atlastex.DrawLatex( 260, 0.4*ymax, "#sqrt{#scale[.8]{s}} #scale[.8]{= 13 TeV,} #scale[.8]{139 fb^{-1}}")
		if(observable=="jet1_pt"):
			atlastex.DrawLatex( 40, 0.4*ymax, "#it{#bf{#scale[1.2]{ATLAS}}}  Internal")
			atlastex.DrawLatex( 120, 0.4*ymax, "#sqrt{#scale[.8]{s}} #scale[.8]{= 13 TeV,} #scale[.8]{139 fb^{-1}}")
		if(observable=="DYjj"):
			atlastex.DrawLatex( 2.5, 0.4*ymax, "#it{#bf{#scale[1.2]{ATLAS}}}  Internal")
			atlastex.DrawLatex( 6.15, 0.4*ymax, "#sqrt{#scale[.8]{s}} #scale[.8]{= 13 TeV,} #scale[.8]{139 fb^{-1}}")
		if(observable=="costhetastar"):
			atlastex.DrawLatex( 0.05, 0.4*ymax, "#it{#bf{#scale[1.2]{ATLAS}}}  Internal")
			atlastex.DrawLatex( .34, 0.4*ymax, "#sqrt{#scale[.8]{s}} #scale[.8]{= 13 TeV,} #scale[.8]{139 fb^{-1}}")
		if(observable=="SignedDPhijj"):
			atlastex.DrawLatex( -2.7, 0.4*ymax, "#it{#bf{#scale[1.2]{ATLAS}}}  Internal")
			atlastex.DrawLatex( 0.6, 0.4*ymax, "#sqrt{#scale[.8]{s}} #scale[.8]{= 13 TeV,} #scale[.8]{139 fb^{-1}}")
		if(observable=="DPhill"):
			atlastex.DrawLatex( 0.1, 0.4*ymax, "#it{#bf{#scale[1.2]{ATLAS}}}  Internal")
			atlastex.DrawLatex( 0.85, 0.4*ymax, "#sqrt{#scale[.8]{s}} #scale[.8]{= 13 TeV,} #scale[.8]{139 fb^{-1}}")
		if(observable=="DYll"):
			atlastex.DrawLatex( 0.05, 0.5*ymax, "#it{#bf{#scale[1.2]{ATLAS}}}  Internal")
			atlastex.DrawLatex( 0.85, 0.5*ymax, "#sqrt{#scale[.8]{s}} #scale[.8]{= 13 TeV,} #scale[.8]{139 fb^{-1}}")

	else :
		atlastex.DrawLatex( bins_c[0] + 0.3*bins_c[0], 0.9*ymax, "#it{#bf{#scale[1.2]{ATLAS}}}  Internal")
		atlastex.DrawLatex(bins_c[bins-1] - 0.1*bins_c[bins-1], 0.9*ymax, "#sqrt{#scale[.8]{s}} #scale[.8]{= 13 TeV,} #scale[.8]{139 fb^{-1}}")

	canvas.SaveAs(str(observable)+"_sys_breakdown.pdf")

if __name__ == "__main__":
	from argparse import ArgumentParser
	parser=argparse.ArgumentParser(description='relative unc. plot')
	parser.add_argument('-bins','--bins', type=int, default=5, help='number of differential bins')
	parser.add_argument('-ymax','--ymax', type=float, default=400, help='ymax')
	parser.add_argument('-observable', '--observable', type=str, default='Mjj', help='observable')
	parser.add_argument('-logY', '--logY', type=bool, default=False, help='set yaxis in logarithmic scale')
	args = parser.parse_args()
	observable = args.observable
	bins = args.bins
	ymax = args.ymax
	logY = args.logY
	main(args)
