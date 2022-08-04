#!/usr/bin/env python 
from astropy.table import Table
import ROOT
from ROOT import *
import argparse
import numpy as np

def setXaxisTitle(observable):
	xaxistitle = ''
	if(observable=='Mjj'):
		xaxistitle = '#it{m}_{jj} [GeV]'
	if(observable=='DYll'):
		xaxistitle = '#it{#Delta y}_{ll}'
	if(observable=="DYjj"):
		xaxistitle = '#it{#Delta y}_{jj}'
	if(observable=="Mll"):
		xaxistitle = '#it{m}_{ll}'
	if(observable=='jet0_pt'):
		xaxistitle = '#it{p}_{T}^{lead jet}'
	return xaxistitle

def main(args):
	gROOT.LoadMacro("./Style/AtlasStyle.C")
	gROOT.LoadMacro("./Style/AtlasUtils.C")
	gROOT.LoadMacro("./Style/AtlasLabels.C")
	SetAtlasStyle()
	gROOT.SetBatch(True)

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

	bin_file = open('./binning_postmerging.txt','r')
	lines = bin_file.readlines()
	line = []
	for iline in lines:
		if observable in iline.strip():
			iline.strip().split()
			line.append(iline.strip().split())
	bins_c = []
	#print(line[0][1])
	data = 'XSPlot_Data_Mjj.root'
	file = TFile(data,"READ")
	obj_statOnly = observable + '_StatOnly'
	statOnly = file.Get(obj_statOnly)
	obj_total = observable + '_StatSys'
	statSys = file.Get(obj_total)
	
	for ibin in range(statSys.GetN()):
		bins_c.append(float(line[0][ibin+1]))

	my_array = np.array(bins_c)
	print(bins_c)
	h_totUnc = TH1D("h_totUnc", "h_totUnc", bins-1, np.array(bins_c))
	for ibin in range(statSys.GetN()):
		#print(statOnly.GetPointY(ibin))
		#print(statSys.GetErrorY(ibin)/statOnly.GetPointY(ibin))
		h_totUnc.SetBinContent(ibin+1, statSys.GetErrorY(ibin)/statOnly.GetPointY(ibin)*100)

	print(bins_c)
	table_file = 'ws_noGGF2_' + observable + '_Data.root_data_breakdown_reverse_rel.tex'
	tab = Table.read(table_file)
	rows = tab.pformat_all()

	tab.pprint()
	
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
	h_lumi = TH1D("lumi", "lumi",  bins-1, np.array(bins_c))
	h_fakes = TH1D("fakes", "fakes",  bins-1, np.array(bins_c))
	h_signal_model = TH1D("sigmodel", "sigmodel",  bins-1, np.array(bins_c))
	h_signal_pshower = TH1D("h_signal_pshower", "h_signal_pshower", bins-1, np.array(bins_c))
	h_lepton_model = TH1D("h_lepton_model", "h_lepton_model", bins-1, np.array(bins_c))
	h_jetmet = TH1D("h_jetmet", "h_jetmet", bins-1, np.array(bins_c))
	h_bkg_model = TH1D("h_bkg_model", "h_bkg_model", bins-1, np.array(bins_c))
	h_btag = TH1D("h_btag", "h_btag",  bins-1, np.array(bins_c))
	h_MCstat = TH1D("h_MCstat", "h_MCstat",  bins-1, np.array(bins_c))
	

	for ibin in range(len(lumi)):
		h_lumi.SetBinContent(ibin+1, float(lumi[ibin]))
		h_fakes.SetBinContent(ibin+1, float(fakes[ibin]))
		h_signal_model.SetBinContent(ibin+1, float(signal_model[ibin]))
		h_signal_pshower.SetBinContent(ibin+1, float(signal_pshower[ibin]))
		h_lepton_model.SetBinContent(ibin+1, float(lepton_model[ibin]))
		h_jetmet.SetBinContent(ibin+1, float(jetmet[ibin]))
		h_bkg_model.SetBinContent(ibin+1, TMath.Sqrt( float(zjets_model[ibin]) + float(diboson_model[ibin]) + float(top_model[ibin]) + float(ggf_model[ibin])))
		h_btag.SetBinContent(ibin+1, float(b_tag[ibin]))
		h_MCstat.SetBinContent(ibin+1, float(mcstat[ibin]))
		#h_totUnc.SetBinContent(ibin+1, float(totunc[ibin]))

	h_lumi.GetYaxis().SetRangeUser(0,ymax)
	h_lumi.GetYaxis().SetTitle("Relative Uncertainty [%]")
	h_lumi.GetXaxis().SetTitle(setXaxisTitle(observable))
	h_lumi.GetYaxis().SetLabelSize(.035)
	h_lumi.GetXaxis().SetLabelSize(.035)
	h_lumi.GetXaxis().SetTitleSize(.035)
	h_lumi.GetYaxis().SetTitleSize(.035)

	h_lumi.SetLineColor(peelOrange)
	h_fakes.SetLineColor(kCyan)
	h_signal_model.SetLineColor(kRed+2)
	h_signal_pshower.SetLineColor(kRed-7)
	h_lepton_model.SetLineColor(robinBlue)
	h_jetmet.SetLineColor(darkGreen)
	h_bkg_model.SetLineColor(kMagenta-5)#(kTeal-8)
	h_btag.SetLineColor(lightAtlasBlue)
	h_MCstat.SetLineColor(kTeal-8)
	h_totUnc.SetLineColor(kBlack)
	h_totUnc.SetLineStyle(kDashed)

	h_lumi.Draw()
	h_fakes.Draw("same")
	h_signal_model.Draw("same")
	h_signal_pshower.Draw("same")
	h_lepton_model.Draw("same")
	h_jetmet.Draw("same")
	h_bkg_model.Draw("same")
	h_btag.Draw("same")
	h_MCstat.Draw("same")
	h_totUnc.Draw("same")

	legend = TLegend(0.62,0.6,.92,0.8);
	legend.SetBorderSize(0)
	legend.SetFillStyle(0)
	legend.SetTextSize(0.)
	#legend.SetNColumns(2)
	legend.AddEntry(h_signal_model, '#bf{Signal modelling}', 'l')
	legend.AddEntry(h_signal_pshower, '#bf{Signal parton shower}', 'l')
	legend.AddEntry(h_bkg_model, '#bf{Background modelling}', 'l')
	legend.AddEntry(h_fakes, '#bf{Mis-Id. background}', 'l')
	legend.AddEntry(h_jetmet, '#bf{Jets + MET}', 'l')
	legend.AddEntry(h_btag, '#bf{b-tagging}', 'l')
	legend.AddEntry(h_lepton_model, '#bf{Leptons}', 'l')
	legend.AddEntry(h_lumi, '#bf{Luminosity}', 'l')
	legend.AddEntry(h_MCstat, '#bf{MC statistics}', 'l')
	legend.AddEntry(h_totUnc, '#bf{Tot. Uncertainty}', 'l')
	legend.Draw()

	atlastex = TLatex()
	atlastex.SetTextSize(.04)
	print(bins_c[0])
	atlastex.DrawLatex( bins_c[0] + 0.3*bins_c[0], 0.9*ymax, "#it{#bf{#scale[1.2]{ATLAS}}}  Internal")
	atlastex.DrawLatex(bins_c[bins-1] - 0.3*bins_c[bins-1], 0.9*ymax, "#sqrt{#scale[.8]{s}} #scale[.8]{= 13 TeV,} #scale[.8]{139 fb^{-1}}")

	print(lumi)
	print(ggf_model)
	canvas.SaveAs("mytest.pdf")

if __name__ == "__main__":
	from argparse import ArgumentParser
	parser=argparse.ArgumentParser(description='relative unc. plot')
	parser.add_argument('-bins','--bins', type=int, default=5, help='number of differential bins')
	parser.add_argument('-ymax','--ymax', type=float, default=400, help='ymax')
	parser.add_argument('-observable', '--observable', type=str, default='Mjj', help='observable')
	args = parser.parse_args()
	observable = args.observable
	bins = args.bins
	ymax = args.ymax
	main(args);

