#include "Style/AtlasStyle.C"
#include <fstream>
#include <stdio.h>
#include <string.h>

TGraphAsymmErrors* getHistogram(TFile* fin, std::string observable="Mjj")
{
  TGraphAsymmErrors* gr;
  TDirectory *current_sourcedir = gDirectory;
  TList* list = current_sourcedir->GetListOfKeys();
 
  for(int ikey=0; ikey<fin->GetNkeys(); ++ikey)
  {
    TObject* fin = list->At(ikey);
    if(fin->GetName()!=observable) continue;
    else gr=(TGraphAsymmErrors*)gDirectory->Get(fin->GetName());
  }

  return gr;
}

std::string getAxisTitle(std::string observable="Mjj")
{
  std::string title_obs="";
  if(observable=="DYjj") title_obs = "#it{#Deltay}_{jj}"; 
  if(observable=="Mll")  title_obs = "#it{m}_{ll}";
  if(observable=="Mjj")  title_obs = "#it{m}_{jj}";
  if(observable=="costhetastar") title_obs = "#it{cos#theta*}";
  if(observable=="DYll") title_obs = "#it{#Deltay}_{ll}";
  if(observable=="DPhill") title_obs = "#it{#Delta#phi}_{ll}";
  if(observable=="SignedDPhijj") title_obs = "#it{#Delta#phi}_{jj}";
  if(observable=="pt_H") title_obs = "#it{p}_{T}^{H}";
  if(observable=="Ptll") title_obs = "#it{p}_{T}^{ll}";
  if(observable=="lep0_pt") title_obs = "#it{p}_{T}^{lep_{0}}";
  if(observable=="lep1_pt") title_obs = "#it{p}_{T}^{lep_{1}}";
  if(observable=="jet0_pt") title_obs = "#it{p}_{T}^{jet_{0}}";
  if(observable=="jet1_pt") title_obs = "#it{p}_{T}^{jet_{1}}";

  return title_obs;
}

std::string getUnits(std::string observable="Mjj")
{
  std::string title_obs="";
  if(observable=="Mjj" || observable=="pt_H" || observable=="Mll" || observable=="Ptll" || observable=="jet1_pt" || observable=="jet0_pt" || observable=="lep0_pt" || observable=="lep1_pt") title_obs = " [fb/GeV]"; 
  if(observable=="DYll" || observable=="DYjj" || observable=="costhetastar") title_obs = " [fb]";
  if(observable=="SignedDPhijj" || observable=="DPhill") title_obs = " [fb/rad]";

  return title_obs;
}

void diff_xsec2(std::string observable="Mjj", bool merged=false, std::string datatype="Asimov", std::string y_min="0", float ymax=5, std::string y_ratio_min=")-10", float ratio_ymax=10, bool latexOneColumn=false)
{
  gROOT->SetBatch(kTRUE);
  SetAtlasStyle();

  if(y_min.find(")") != string::npos) y_min.erase(0,1);
  if(y_ratio_min.find(")") != string::npos) y_ratio_min.erase(0,1);

  float ymin = std::stof(y_min);
  float ratio_ymin = std::stof(y_ratio_min);


// Get the binning ==========================================
  std::string bin_file = "../predictions_for_diff_xsec_plots/binning_postmerging.txt";
  if(!merged) bin_file = "../predictions_for_diff_xsec_plots/binning_premerging.txt";
  std::ifstream binning_f(bin_file.c_str());

  std::string binning;
  if(binning_f.is_open())
  {
    std::string line;
    do {
      if(line.find(observable) != std::string::npos) binning = line;
      else continue;
    } while(std::getline(binning_f, line));    
  }
  binning_f.close();
  std::cout<<binning<<std::endl;

  char str[binning.length()];
  int i;
  for(i = 0; i<sizeof(str); i++) str[i] = binning[i];
  char* token;
  char* rest = str;
  std::vector<float> v_binEdges;
  while( (token=strtok_r(rest, " ", &rest)) ) 
  {
    if(token==observable) continue;
    std::string fs(token);
    float num = std::stof(fs);
    v_binEdges.push_back(num);
  }

  float *bin_edges = &v_binEdges[0];
// ======================================================

  // used for the error asymmetry checks
  TH1F* h_data_test = new TH1F("h_data_test", "", v_binEdges.size()-1, bin_edges); 

  // access data histo 
  std::string data_filename = "/usatlas/u/sagar/usatlaswork/scripts/XSPlotsChara/HistMergingGraphs/XSPlot_"+datatype+"_" + observable +".root";
  if(!merged) data_filename = "/usatlas/u/sagar/usatlaswork/scripts/XSPlotsChara/PreMergingGraphs/XSPlot_"+datatype+"_" + observable +".root";
  TFile* f_data = new TFile(data_filename.c_str(),"READ");
  std::string statonly = observable + "_StatOnly";
  std::string statsys  = observable + "_StatSys";
  TGraphAsymmErrors* gr_data_stat = getHistogram(f_data, statonly);

  TGraphAsymmErrors* gr_data_statsys = getHistogram(f_data, statsys);
  gROOT->cd();

  // access prediction histos 
  std::string powpy8_filename    = "../predictions_for_diff_xsec_plots/PowPy8-theo-hist-fineBin_remerged_rebin.root";
  std::string vbfnlonlo_filename = "../predictions_for_diff_xsec_plots/VBFNLO-LO-theo-hist-fineBin_remerged_rebin.root";
  std::string powh7_filename     = "../predictions_for_diff_xsec_plots/PowH7-theo-hist-fineBin_remerged_rebin.root";
  std::string vbfnlolo_filename  = "../predictions_for_diff_xsec_plots/VBFNLO-NLO-theo-hist-fineBin_remerged_rebin.root";

  if(!merged) {
  	powpy8_filename    = "../predictions_for_diff_xsec_plots/PowPy8-theo-hist-fineBin_rebin.root";
  	vbfnlonlo_filename = "../predictions_for_diff_xsec_plots/VBFNLO-LO-theo-hist-fineBin_rebin.root";
  	powh7_filename     = "../predictions_for_diff_xsec_plots/PowH7-theo-hist-fineBin_rebin.root";
  	vbfnlolo_filename  = "../predictions_for_diff_xsec_plots/VBFNLO-NLO-theo-hist-fineBin_rebin.root ";
  }

  if(observable=="SignedDPhijj") observable="DPhijj";
  TFile* f_powpy8    = new TFile(powpy8_filename.c_str(),"READ");
  TGraphAsymmErrors* gr_powpy8_obs    = getHistogram(f_powpy8, observable);
  gROOT->cd();
  TFile* f_vbfnlonlo = new TFile(vbfnlonlo_filename.c_str(),"READ");
  TGraphAsymmErrors* gr_vbfnlonlo_obs = getHistogram(f_vbfnlonlo, observable);
  gROOT->cd();
  TFile* f_powh7     = new TFile(powh7_filename.c_str(),"READ");
  TGraphAsymmErrors* gr_powh7_obs     = getHistogram(f_powh7, observable);
  gROOT->cd();
  TFile* f_vbfnlolo = new TFile(vbfnlolo_filename.c_str(),"READ");
  TGraphAsymmErrors* gr_vbfnlopy8_obs  = getHistogram(f_vbfnlolo, observable);
  gROOT->cd();

  if(observable=="DPhijj") observable = "SignedDPhijj";
  TGraphAsymmErrors *gr_ratio_powpy8 = 		new TGraphAsymmErrors();
  TGraphAsymmErrors *gr_ratio_vbfnlonlo =  	new TGraphAsymmErrors();
  TGraphAsymmErrors *gr_ratio_powh7 = 		new TGraphAsymmErrors();
  TGraphAsymmErrors *gr_ratio_vbfnlopy8 = 	new TGraphAsymmErrors();
  TGraphAsymmErrors *gr_ratio_data_stat = 	new TGraphAsymmErrors();
  TGraphAsymmErrors *gr_ratio_data_tot = 	new TGraphAsymmErrors();

  TGraphAsymmErrors* gr_data_stat_only = new TGraphAsymmErrors();
  TGraphAsymmErrors* gr_data_tot = new TGraphAsymmErrors();

  TGraphAsymmErrors *gr_powpy8_0 = 		new TGraphAsymmErrors();
  TGraphAsymmErrors *gr_vbfnlonlo_0 =  	new TGraphAsymmErrors();
  TGraphAsymmErrors *gr_powh7_0 = 		new TGraphAsymmErrors();
  TGraphAsymmErrors *gr_vbfnlopy8_0 = 	new TGraphAsymmErrors();

  TH1F* h_up = new TH1F("h_up", " ", h_data_test->GetNbinsX(), h_data_test->GetBinLowEdge(1), h_data_test->GetBinLowEdge(h_data_test->GetNbinsX()+1) );
  TGraphAsymmErrors* gr_statistical = new TGraphAsymmErrors();
  for(int ibin=0; ibin<gr_vbfnlonlo_obs->GetN(); ibin++)
  {
  	float inc = h_data_test->GetBinWidth(ibin+1)/6;
  	float bin_low_edge = h_data_test->GetBinLowEdge(ibin+1);
  	float bin_upper_edge = h_data_test->GetBinLowEdge(ibin+1) + h_data_test->GetBinWidth(ibin+1);

  	gr_powpy8_0->SetPointX(ibin, bin_low_edge+3*inc-inc/2);
  	gr_vbfnlonlo_0->SetPointX(ibin, bin_low_edge+3*inc-inc);
  	gr_data_stat_only->SetPointX(ibin, bin_low_edge+3*inc);
  	gr_powh7_0->SetPointX(ibin, bin_low_edge+3*inc+inc/2);
  	gr_vbfnlopy8_0->SetPointX(ibin, bin_low_edge+3*inc+inc);
  	
  	gr_data_stat_only->SetPointY(ibin, gr_data_stat->GetPointY(ibin));
    gr_statistical->SetPointX(ibin, bin_low_edge+3*inc);
    gr_statistical->SetPointY(ibin, gr_data_stat->GetPointY(ibin));
    gr_statistical->SetPointError(ibin, h_data_test->GetBinWidth(ibin+1)/12, h_data_test->GetBinWidth(ibin+1)/12, gr_data_stat->GetErrorYlow(ibin), gr_data_stat->GetErrorYhigh(ibin));
  	//gr_data_stat_only->SetPointError(ibin, h_data_test->GetBinWidth(ibin+1)/2, h_data_test->GetBinWidth(ibin+1)/2, gr_data_stat->GetErrorYlow(ibin), gr_data_stat->GetErrorYhigh(ibin));
    //gr_data_stat_only->SetPointError(ibin, h_data_test->GetBinWidth(ibin+1)/2, h_data_test->GetBinWidth(ibin+1)/2, 0, 0);

  	gr_powpy8_0->SetPointY(ibin, gr_powpy8_obs->GetPointY(ibin));
  	//gr_powpy8_0->SetPointError(ibin, h_data_test->GetBinWidth(ibin+1)/2 - inc/2, h_data_test->GetBinWidth(ibin+1)/2 + inc/2, gr_powpy8_obs->GetErrorYlow(ibin), gr_powpy8_obs->GetErrorYhigh(ibin));
    gr_powpy8_0->SetPointError(ibin, (h_data_test->GetBinWidth(ibin+1)/2 - inc/2)/12, (h_data_test->GetBinWidth(ibin+1)/2 - inc/2)/12, gr_powpy8_obs->GetErrorYlow(ibin), gr_powpy8_obs->GetErrorYhigh(ibin));


  	gr_vbfnlonlo_0->SetPointY(ibin, gr_vbfnlonlo_obs->GetPointY(ibin));
  	//gr_vbfnlonlo_0->SetPointError(ibin, h_data_test->GetBinWidth(ibin+1)/2 - inc, h_data_test->GetBinWidth(ibin+1)/2 + inc, gr_vbfnlonlo_obs->GetErrorYlow(ibin), gr_vbfnlonlo_obs->GetErrorYhigh(ibin));
    gr_vbfnlonlo_0->SetPointError(ibin, (h_data_test->GetBinWidth(ibin+1)/2 - inc)/12, (h_data_test->GetBinWidth(ibin+1)/2 - inc)/12, gr_vbfnlonlo_obs->GetErrorYlow(ibin), gr_vbfnlonlo_obs->GetErrorYhigh(ibin));


  	gr_powh7_0->SetPointY(ibin, gr_powh7_obs->GetPointY(ibin));
  //	gr_powh7_0->SetPointError(ibin, h_data_test->GetBinWidth(ibin+1)/2 +inc/2, h_data_test->GetBinWidth(ibin+1)/2 - inc/2, gr_powh7_obs->GetErrorYlow(ibin), gr_powh7_obs->GetErrorYhigh(ibin));
    gr_powh7_0->SetPointError(ibin, (h_data_test->GetBinWidth(ibin+1)/2 +inc/2)/12, (h_data_test->GetBinWidth(ibin+1)/2 +inc/2)/12, gr_powh7_obs->GetErrorYlow(ibin), gr_powh7_obs->GetErrorYhigh(ibin));


  	gr_vbfnlopy8_0->SetPointY(ibin, gr_vbfnlopy8_obs->GetPointY(ibin));
  	//gr_vbfnlopy8_0->SetPointError(ibin, h_data_test->GetBinWidth(ibin+1)/2 +inc, h_data_test->GetBinWidth(ibin+1)/2 - inc, gr_vbfnlopy8_obs->GetErrorYlow(ibin), gr_vbfnlopy8_obs->GetErrorYhigh(ibin));
    gr_vbfnlopy8_0->SetPointError(ibin, (h_data_test->GetBinWidth(ibin+1)/2 +inc)/12, (h_data_test->GetBinWidth(ibin+1)/2 +inc)/12, gr_vbfnlopy8_obs->GetErrorYlow(ibin), gr_vbfnlopy8_obs->GetErrorYhigh(ibin));

 // 	gr_vbfnlopy8_obs->SetPointEXlow(ibin, h_data_test->GetBinWidth(ibin+1)/2);

	// fill histogram for error asymmetry checks  
  	gr_data_tot->SetPointX(ibin, bin_low_edge+3*inc);
  	gr_data_tot->SetPointY(ibin, gr_data_stat->GetPointY(ibin));

  	// sys uncertainty shown as error band 
  	gr_data_tot->SetPointError(ibin, h_data_test->GetBinWidth(ibin+1)/2, h_data_test->GetBinWidth(ibin+1)/2, gr_data_statsys->GetErrorYlow(ibin), gr_data_statsys->GetErrorYhigh(ibin));
  
  	gr_ratio_powpy8->SetPointX(ibin, gr_powpy8_0->GetPointX(ibin));
  	gr_ratio_vbfnlonlo->SetPointX(ibin, gr_vbfnlonlo_0->GetPointX(ibin));
  	gr_ratio_powh7->SetPointX(ibin, gr_powh7_0->GetPointX(ibin));
  	gr_ratio_vbfnlopy8->SetPointX(ibin, gr_vbfnlopy8_0->GetPointX(ibin));
  	gr_ratio_data_stat->SetPointX(ibin, gr_data_stat_only->GetPointX(ibin));
  	gr_ratio_data_tot->SetPointX(ibin, gr_data_tot->GetPointX(ibin));

  }
// =========================================

// Error asymmetry check
/*   
  TCanvas *k = new TCanvas("my_canvas","my_canvas", 0, 0, 600, 600);
  k->cd();
  h_up->SetLineColor(kGreen);
  h_up->Draw("hist");
  h_up->GetYaxis()->SetTitle("{up-down} / {up+down}");
  h_up->GetYaxis()->SetRangeUser(0,1);
  h_up->GetXaxis()->SetTitle(getAxisTitle(observable).c_str());
  std::string exp_name = observable + ".pdf"; 
  k->SaveAs(exp_name.c_str());
*/

  TCanvas *c = new TCanvas("atlas_square","Canvas title",0.,0.,600,600);
  TPad* pad1 = new TPad("pad1","pad1", 0, 0.35, 1., 1.);
  pad1->SetBottomMargin(0.03);
  pad1->Draw();
  pad1->cd();

  gr_data_stat_only->SetMarkerColor(kBlack);
  gr_data_stat_only->SetLineColor(kBlack);
  
  gr_data_stat_only->SetMarkerSize(1.);
  gr_data_stat_only->SetMarkerStyle(8);
  //gr_data_stat_only->SetLineWidth(2);
  gr_powpy8_0->SetMarkerSize(1.);
  //gr_powpy8_0->SetLineWidth(2);
  gr_vbfnlonlo_0->SetMarkerSize(1.6);
  //gr_vbfnlonlo_0->SetLineWidth(2.);
  gr_powh7_0->SetMarkerSize(1.2);
  //gr_powh7_0->SetLineWidth(2.);
  gr_vbfnlopy8_0->SetMarkerSize(1.2);
  //gr_vbfnlopy8_0->SetLineWidth(2.);
  gr_powpy8_0->SetMarkerColor(kAzure+2);
  gr_powpy8_0->SetFillColorAlpha(kAzure+2,.35);
  gr_vbfnlonlo_0->SetMarkerColor(kRed+2);
  gr_vbfnlonlo_0->SetFillColorAlpha(kRed+2,.35);
  gr_powh7_0->SetMarkerColor(kOrange+2);
  gr_powh7_0->SetFillColorAlpha(kOrange+2,.35);
  gr_vbfnlopy8_0->SetMarkerColor(kGreen+2);
  gr_vbfnlopy8_0->SetFillColorAlpha(kGreen+2,.35);
  gr_powpy8_0->SetLineColor(kAzure+2);
  gr_vbfnlonlo_0->SetLineColor(kRed+2);
  gr_powh7_0->SetLineColor(kOrange+2);
  gr_vbfnlopy8_0->SetLineColor(kGreen+2);
  gr_powpy8_0->SetMarkerStyle(21);
  gr_vbfnlonlo_0->SetMarkerStyle(33);
  gr_powh7_0->SetMarkerStyle(22);
  gr_vbfnlopy8_0->SetMarkerStyle(23);

  gr_powpy8_0->Draw("AP");
  gr_data_tot->SetFillColor(kGray);
//  gr_data_tot->SetFillStyle(3005);//(3144);
  gr_data_tot->SetLineColor(kWhite);
  gr_statistical->SetLineColor(kWhite);
  gr_statistical->SetFillColor(kGray+1);
 // gr_statistical->SetFillStyle(3005);
  gr_data_tot->Draw("e2 same");
  gr_statistical->Draw("e2 same");

  for(int ibin=0; ibin<gr_data_tot->GetN(); ++ibin)
  {
    TLine* line = new TLine(h_data_test->GetBinLowEdge(ibin+1), gr_data_stat->GetPointY(ibin), h_data_test->GetBinLowEdge(ibin+1)+h_data_test->GetBinWidth(ibin+1), gr_data_stat->GetPointY(ibin));
    line->SetLineColor(kBlack);
    line->SetLineWidth(2.);
    line->Draw("same");
  }
  
  gr_powpy8_0->Draw("pe2 same");
  gr_vbfnlonlo_0->Draw("pe2 same");
  gr_powh7_0->Draw("pe2 same");
  gr_vbfnlopy8_0->Draw("pe2 same");
  gr_data_stat_only->Draw("pe2 same");
  
  
  gPad->Modified();
  float first = h_data_test->GetBinLowEdge(1);
  if(observable!="SignedDPhijj" && observable!="DYjj") first = 0;
  float last = h_data_test->GetBinLowEdge(h_data_test->GetNbinsX()+1);
  std::cout<<first<<" "<<last<<std::endl;
  gr_powpy8_0->GetXaxis()->SetLimits(first,last); 
  gr_powpy8_0->GetXaxis()->SetLabelOffset(10);
  gr_powpy8_0->GetYaxis()->SetRangeUser(ymin,ymax);
  
  std::string y_title = "d#it{#sigma}/d" + getAxisTitle(observable) + getUnits(observable);
  gr_powpy8_0->GetYaxis()->SetTitle(y_title.c_str());
  gr_powpy8_0->GetYaxis()->SetLabelSize(.04);

  TLegend *legend = new TLegend(0.63,0.5,0.84,0.9);
  if(latexOneColumn) legend = new TLegend(0.58, 0.32, 0.82, .74);
  legend->SetBorderSize(0);
  legend->SetFillStyle(0);
  legend->SetTextSize(0.04);
 
  legend->AddEntry(gr_data_stat_only, "#bf{Data}", "p");
  //legend->AddEntry((TObject*)0, "", "");
  legend->AddEntry(gr_statistical, "#bf{Data Stat. Unc.}", "f");
  legend->AddEntry(gr_data_tot, "#bf{Data Total Unc.}", "f");
  legend->AddEntry(gr_powpy8_0,"#bf{Powheg+Pythia8}", "p");
  legend->AddEntry(gr_powh7_0,"#bf{Powheg+Herwig7}", "p");
  legend->AddEntry(gr_vbfnlopy8_0, "#bf{VBFNLO@LO+Pythia8}", "p"); 
  legend->AddEntry(gr_vbfnlonlo_0, "#bf{VBFNLO@NLO}", "p"); 
  
  legend->Draw();

  auto legAtlas = new TLegend(0.1,0.73,0.55,0.9);
  if(latexOneColumn) legAtlas = new TLegend(0.48, 0.74, .94, .9);
  legAtlas->SetBorderSize(0);
  legAtlas->SetFillStyle(0);
  legAtlas->SetTextSize(0.);
  legAtlas->AddEntry((TObject*)0, "#it{#scale[1.1]{ATLAS} #bf{Internal}}", "");
  legAtlas->AddEntry((TObject*)0, "#bf{#sqrt{#scale[.7]{#it{s}}} #scale[.7]{= 13 TeV, 139 fb^{-1}}  }", "");
  legAtlas->Draw();
 /*

  TLegend *legend = new TLegend(0.62,0.6,0.86,0.9);
  if(latexOneColumn) legend = new TLegend(0.6, 0.42, 0.78, .74);
  legend->SetBorderSize(0);
  legend->SetFillStyle(0);
  legend->SetTextSize(0.04);
 
  legend->AddEntry(gr_data_stat_only, "#bf{Data Stat. Unc.}", "p");
  legend->AddEntry(gr_data_tot, "#bf{Data Total Unc.}", "f");
  legend->AddEntry(gr_powpy8_0,"#bf{Powheg+Pythia8}", "pe");
  legend->AddEntry(gr_vbfnlonlo_0, "#bf{VBFNLO@NLO}", "pe"); 
  legend->AddEntry(gr_powh7_0,"#bf{Powheg+Herwig7}", "pe");
  legend->AddEntry(gr_vbfnlopy8_0, "#bf{VBFNLO@LO}", "pe"); 
  legend->Draw();

  auto legAtlas = new TLegend(0.1,0.73,0.55,0.9);
  if(latexOneColumn) legAtlas = new TLegend(0.51, 0.74, .94, .9);
  legAtlas->SetBorderSize(0);
  legAtlas->SetFillStyle(0);
  legAtlas->SetTextSize(0.);
  legAtlas->AddEntry((TObject*)0, "#it{#scale[1.]{ATLAS}}", "");
  legAtlas->AddEntry((TObject*)0, "#bf{#sqrt{#scale[.8]{#it{s}}} #scale[.8]{= 13 TeV, 139 fb^{-1}}  }", "");
  legAtlas->Draw(); */
  gPad->RedrawAxis(); //to avoid the overlapping of error bands with axis ticks
  
  float x_start, x_end, minus, plus, x1, x2, x3, x4;
  if(observable=="DYll" || observable=="Mjj" || observable=="Mll" || observable=="jet0_pt" || observable=="jet1_pt" || observable=="DYll" || observable=="Ptll" || observable=="lep0_pt" || observable=="lep1_pt" || observable=="pt_H" || observable=="costhetastar")
  {
  	if(observable=="DYll")
  	{
  		x_start=1.15;
  		x_end=1.18;
  		minus=.2;
  		plus=.2;
  		x1 = .01;
      	x2 = .01; 
      	x3 = .02;
      	x4 = .04; 
  	}
    if(observable=="costhetastar")
    {
      x_start = 0.442;
      x_end = .45;
      minus = .2;
      plus = .2;
      x1 = .004;
      x2 = .004; 
      x3 = .005;
      x4 = .012; 
    }
    if(observable=="Mjj")
    {
      x_start = 2710;
      x_end = 2780;
      minus = .00008;
      plus = .0001;
      x1 = 20;
      x2 = 25;
      x3 = 2*x2;
      x4 = 95;
    }
    if(observable=="Mll")
    {
      x_start = 82;
      x_end = 84;
      minus = .002;
      plus = 0.002;
      x1 = 1.;
      x2 = 1.;
      x3 = 1.1;
      x4 = 3.;
    } 
    if(observable=="lep1_pt")
    {
      x_start = 72;
      x_end = 74;
      minus = .005;
      plus = 0.006;
      x1 = 1.;
      x2 = 1.;
      x3 = 1.1;
      x4 = 3.;
    }
    if(observable=="jet0_pt") 
    {
      x_start = 320;
      x_end = 325;
      minus = .0005;
      plus = .0006;
      x1 = 1.5;
      x2 = 2.5;
      x3= 3.5;
      x4 =7.5;
    }
    if(observable=="jet1_pt")
    {
      x_start = 150;
      x_end = 154;
      minus = 0.001;
      plus = 0.002;
      x1 = 1.;
      x2 = 1.8; 
      x3 = 3.;
      x4 = 5.5; 
    }
    if(observable=="Ptll") 
    {
      x_start = 181;
      x_end = 184;
      minus = .001;
      plus = .001;
      x1 = 1.9;
      x2 = 2.1;
      x3= 1.1;
      x4 =5.1;
    }
    if(observable=="lep0_pt")
    {
      x_start = 146;
      x_end = 149;
      minus = 0.001;
      plus = 0.002;
      x1 = 1.;
      x2 = 1.8; 
      x3 = 2.;
      x4 = 4.8; 
    }
    if(observable=="pt_H")
    {
      x_start = 330;
      x_end = 335;
      minus = 0.0008;
      plus = 0.001;
      x1 = 1.;
      x2 = 1.8; 
      x3 = 3.5;
      x4 = 6.3; 
    }

    TLine* line01 = new TLine(x_start, ymin, x_end, ymin);
    line01->SetLineColor(kWhite);
    line01->SetLineWidth(15);
    line01->Draw("same");
    TLine* line02 = new TLine(x_start-x1, ymin-minus, x_start+x2, ymin+plus);
    line02->SetLineColor(kBlack);
    line02->SetLineWidth(1.);
    line02->Draw("same");
    TLine* line03 = new TLine(x_start+x3, ymin-minus, x_start+x4, ymin+plus);
    line03->SetLineColor(kBlack);
    line03->SetLineWidth(1.);
    line03->Draw("same");
  }

  c->cd();
  TPad* pad2 = new TPad("pad2", "pad2", 0, 0., 1., 0.35);
  pad2->SetTopMargin(0.03);
  pad2->SetBottomMargin(.4);
  pad2->Draw();
  pad2->cd();
 // gPad->SetGridy(1);
  
  for(int ipoint=0; ipoint<gr_ratio_data_tot->GetN(); ipoint++)
  {
    float inc = h_data_test->GetBinWidth(ipoint+1)/6;
  	gr_ratio_data_stat->SetPointY(ipoint, gr_data_stat->GetPointY(ipoint)/gr_data_stat->GetPointY(ipoint));
  	float error_data_low = gr_data_stat->GetErrorYlow(ipoint)/gr_data_stat->GetPointY(ipoint);
  	float error_data_high = gr_data_stat->GetErrorYhigh(ipoint)/gr_data_stat->GetPointY(ipoint);
  	gr_ratio_data_stat->SetPointError(ipoint, h_data_test->GetBinWidth(ipoint+1)/2, h_data_test->GetBinWidth(ipoint+1)/2, error_data_low, error_data_high);

  	gr_ratio_data_tot->SetPointY(ipoint, gr_data_stat->GetPointY(ipoint)/gr_data_stat->GetPointY(ipoint));
  	float error_tot_low = gr_data_tot->GetErrorYlow(ipoint)/gr_data_stat->GetPointY(ipoint); 
  	float error_tot_high = gr_data_tot->GetErrorYhigh(ipoint)/gr_data_stat->GetPointY(ipoint);
  	gr_ratio_data_tot->SetPointError(ipoint, h_data_test->GetBinWidth(ipoint+1)/2, h_data_test->GetBinWidth(ipoint+1)/2, error_tot_low, error_tot_high);

  	gr_ratio_powpy8->SetPointY(ipoint, gr_powpy8_0->GetPointY(ipoint)/gr_data_stat->GetPointY(ipoint));
  	float error_powpy8 = gr_powpy8_0->GetErrorYlow(ipoint)/gr_data_stat->GetPointY(ipoint);
  	//gr_ratio_powpy8->SetPointError(ipoint, h_data_test->GetBinWidth(ipoint+1)/2- inc/2, h_data_test->GetBinWidth(ipoint+1)/2+inc/2, error_powpy8, error_powpy8);
    gr_ratio_powpy8->SetPointError(ipoint, (h_data_test->GetBinWidth(ipoint+1)/2- inc/2)/12, (h_data_test->GetBinWidth(ipoint+1)/2- inc/2)/12, error_powpy8, error_powpy8);

  	gr_ratio_vbfnlonlo->SetPointY(ipoint, gr_vbfnlonlo_0->GetPointY(ipoint)/gr_data_stat->GetPointY(ipoint));
  	float error_vbfnlonlo = gr_vbfnlonlo_0->GetErrorYlow(ipoint)/gr_data_stat->GetPointY(ipoint);
  //	gr_ratio_vbfnlonlo->SetPointError(ipoint, h_data_test->GetBinWidth(ipoint+1)/2 -inc, h_data_test->GetBinWidth(ipoint+1)/2+inc, error_vbfnlonlo, error_vbfnlonlo);
    gr_ratio_vbfnlonlo->SetPointError(ipoint, (h_data_test->GetBinWidth(ipoint+1)/2 -inc)/12, (h_data_test->GetBinWidth(ipoint+1)/2 -inc)/12, error_vbfnlonlo, error_vbfnlonlo);

  	gr_ratio_powh7->SetPointY(ipoint, gr_powh7_0->GetPointY(ipoint)/gr_data_stat->GetPointY(ipoint));
  	float error_powh7 = gr_powh7_0->GetErrorYlow(ipoint)/gr_data_stat->GetPointY(ipoint);
//  	gr_ratio_powh7->SetPointError(ipoint, h_data_test->GetBinWidth(ipoint+1)/2+inc/2, h_data_test->GetBinWidth(ipoint+1)/2-inc/2, error_powh7, error_powh7);
    gr_ratio_powh7->SetPointError(ipoint, (h_data_test->GetBinWidth(ipoint+1)/2+inc/2)/12, (h_data_test->GetBinWidth(ipoint+1)/2+inc/2)/12, error_powh7, error_powh7);

  	gr_ratio_vbfnlopy8->SetPointY(ipoint, gr_vbfnlopy8_0->GetPointY(ipoint)/gr_data_stat->GetPointY(ipoint));
  	float error_vbfnlopy8 = gr_vbfnlopy8_0->GetErrorYlow(ipoint)/gr_data_stat->GetPointY(ipoint);
//  	gr_ratio_vbfnlopy8->SetPointError(ipoint, h_data_test->GetBinWidth(ipoint+1)/2+inc, h_data_test->GetBinWidth(ipoint+1)/2-inc, error_vbfnlopy8, error_vbfnlopy8);
    gr_ratio_vbfnlopy8->SetPointError(ipoint, (h_data_test->GetBinWidth(ipoint+1)/2+inc)/12, (h_data_test->GetBinWidth(ipoint+1)/2+inc)/12, error_vbfnlopy8, error_vbfnlopy8);

    //if(ipoint==gr_ratio_data_tot->GetN()-1) gr_ratio_data_stat->GetXaxis()->
  }

 // gr_ratio_data_stat->SetMarkerColor(kBlack);
 // gr_ratio_data_stat->SetMarkerSize(0);
 // gr_ratio_data_stat->SetMarkerStyle(8);
 // gr_ratio_data_stat->Draw("ape");
  
  gr_ratio_data_tot->SetFillColor(kGray);
//  gr_ratio_data_tot->SetFillStyle(3005);//(3144);
  gr_ratio_data_tot->SetLineColor(kWhite);
  gr_ratio_data_tot->Draw("ae2");

  gr_ratio_powpy8->SetMarkerColor(kAzure+2);
  gr_ratio_powpy8->SetFillColorAlpha(kAzure+2,.35);
  gr_ratio_powpy8->SetMarkerSize(.9);
  gr_ratio_powpy8->SetLineWidth(2);
  gr_ratio_powpy8->SetLineColor(kAzure+2);
  gr_ratio_powpy8->SetMarkerStyle(21);

  gr_ratio_vbfnlonlo->SetMarkerSize(1.5);
  gr_ratio_vbfnlonlo->SetLineWidth(2.);
  gr_ratio_vbfnlonlo->SetMarkerColor(kRed+2);
  gr_ratio_vbfnlonlo->SetLineColor(kRed+2);
  gr_ratio_vbfnlonlo->SetFillColorAlpha(kRed+2,.35);
  gr_ratio_vbfnlonlo->SetMarkerStyle(33);

  gr_ratio_powh7->SetMarkerSize(1.2);
  gr_ratio_powh7->SetLineWidth(2.);
  gr_ratio_powh7->SetMarkerColor(kOrange+2);
  gr_ratio_powh7->SetLineColor(kOrange+2);
  gr_ratio_powh7->SetFillColorAlpha(kOrange+2,.35);
  gr_ratio_powh7->SetMarkerStyle(22);

  gr_ratio_vbfnlopy8->SetMarkerSize(1.2);
  gr_ratio_vbfnlopy8->SetLineWidth(2.);
  gr_ratio_vbfnlopy8->SetMarkerColor(kGreen+2);
  gr_ratio_vbfnlopy8->SetLineColor(kGreen+2);
  gr_ratio_vbfnlopy8->SetFillColorAlpha(kGreen+2,.35);
  gr_ratio_vbfnlopy8->SetMarkerStyle(23);

  TLine* line_ratio = new TLine(first, 1, last, 1);
  line_ratio->SetLineColor(kBlack);
 // line_ratio->SetLineStyle(kDashed);
  line_ratio->Draw("same");

 //gr_ratio_data_stat->Draw("pe same");
  gr_ratio_powpy8->Draw("pe2 same");
  gr_ratio_vbfnlonlo->Draw("pe2 same");
  gr_ratio_powh7->Draw("pe2 same");
  gr_ratio_vbfnlopy8->Draw("pe2 same");

  float div_min, div_max;

  for(int ipoint=0; ipoint<gr_ratio_data_tot->GetN(); ipoint++)
  {

    if(observable=="SignedDPhijj" )
    {
      div_min = .2;
      div_max = .1;
    }
    if(observable=="jet1_pt" || observable == "costhetastar" || observable=="DPhill" || observable=="Mjj" || observable=="jet0_pt" || observable=="DYjj" || observable=="Ptll" )
    {
      div_min = .3;
      div_max = .1;
    }
    if(observable == "Mll" || observable=="lep0_pt" || observable=="lep1_pt" || observable=="pt_H")
    {
      div_min = .4;
      div_max = .1;
    }
    if(observable=="DYll")
    {
      div_min = .3;
      div_max =.1;
    }

    if(gr_ratio_powpy8->GetPointY(ipoint) > ratio_ymax) {
         TArrow *ar_pow_up = new TArrow(gr_ratio_powpy8->GetPointX(ipoint),ratio_ymax-div_min,gr_ratio_powpy8->GetPointX(ipoint),ratio_ymax-div_max,0.01,">");
         ar_pow_up->SetLineWidth(2);
         ar_pow_up->SetLineColor(kAzure+2);
         ar_pow_up->SetFillColor(kWhite);
         ar_pow_up->Draw();
    }
    if(gr_ratio_powpy8->GetPointY(ipoint) < ratio_ymin) {
         TArrow *ar_pow_min = new TArrow(gr_ratio_powpy8->GetPointX(ipoint),ratio_ymin+div_max,gr_ratio_powpy8->GetPointX(ipoint),ratio_ymin+div_min,0.01,"<");
         ar_pow_min->SetLineWidth(2);
         ar_pow_min->SetLineColor(kAzure+2);
         ar_pow_min->SetFillColor(kWhite);
         ar_pow_min->Draw();
    }

    if(gr_ratio_vbfnlonlo->GetPointY(ipoint) > ratio_ymax) {
         TArrow *ar_pow_up = new TArrow(gr_ratio_vbfnlonlo->GetPointX(ipoint),ratio_ymax-div_min,gr_ratio_vbfnlonlo->GetPointX(ipoint),ratio_ymax-div_max,0.01,">");
         ar_pow_up->SetLineWidth(2);
         ar_pow_up->SetLineColor(kRed+2);
         ar_pow_up->SetFillColor(kWhite);
         ar_pow_up->Draw();
    }
    if(gr_ratio_vbfnlonlo->GetPointY(ipoint) < ratio_ymin) {
         TArrow *ar_pow_min = new TArrow(gr_ratio_vbfnlonlo->GetPointX(ipoint),ratio_ymin+div_max,gr_ratio_vbfnlonlo->GetPointX(ipoint),ratio_ymin+div_min,0.01,"<");
         ar_pow_min->SetLineWidth(2);
         ar_pow_min->SetLineColor(kRed+2);
         ar_pow_min->SetFillColor(kWhite);
         ar_pow_min->Draw();
    }

    if(gr_ratio_powh7->GetPointY(ipoint) > ratio_ymax) {
         TArrow *ar_pow_up = new TArrow(gr_ratio_powh7->GetPointX(ipoint),ratio_ymax-div_min,gr_ratio_powh7->GetPointX(ipoint),ratio_ymax-div_max,0.01,">");
         ar_pow_up->SetLineWidth(2);
         ar_pow_up->SetLineColor(kOrange+2);
         ar_pow_up->SetFillColor(kWhite);
         ar_pow_up->Draw();
    }
    if(gr_ratio_powh7->GetPointY(ipoint) < ratio_ymin) {
         TArrow *ar_pow_min = new TArrow(gr_ratio_powh7->GetPointX(ipoint),ratio_ymin+div_max,gr_ratio_powh7->GetPointX(ipoint),ratio_ymin+div_min,0.01,"<");
         ar_pow_min->SetLineWidth(2);
         ar_pow_min->SetLineColor(kOrange+2);
         ar_pow_min->SetFillColor(kWhite);
         ar_pow_min->Draw();
    }

    if(gr_ratio_vbfnlopy8->GetPointY(ipoint) > ratio_ymax) {
         TArrow *ar_pow_up = new TArrow(gr_ratio_vbfnlopy8->GetPointX(ipoint),ratio_ymax-div_min,gr_ratio_vbfnlopy8->GetPointX(ipoint),ratio_ymax-div_max,0.01,">");
         ar_pow_up->SetLineWidth(2);
         ar_pow_up->SetLineColor(kGreen+2);
         ar_pow_up->SetFillColor(kWhite);
         ar_pow_up->Draw();
    }
    if(gr_ratio_vbfnlopy8->GetPointY(ipoint) < ratio_ymin) {
         TArrow *ar_pow_min = new TArrow(gr_ratio_vbfnlopy8->GetPointX(ipoint),ratio_ymin+div_max,gr_ratio_vbfnlopy8->GetPointX(ipoint),ratio_ymin+div_min,0.01,"<");
         ar_pow_min->SetLineWidth(2);
         ar_pow_min->SetLineColor(kGreen+2);
         ar_pow_min->SetFillColor(kWhite);
         ar_pow_min->Draw();
    }
  }


  gPad->Modified();
  gr_ratio_data_tot->GetXaxis()->SetLimits(first,last); // need to be adjusted

  std::string xtit = getAxisTitle(observable);
  if(observable=="SignedDPhijj" || observable=="DPhill") xtit = getAxisTitle(observable) + " [rad]";
  else if(observable=="DYjj" || observable=="DYll" || observable=="costhetastar") xtit = getAxisTitle(observable);
  else  xtit = getAxisTitle(observable) + " [GeV]";
  gr_ratio_data_tot->GetXaxis()->SetTitle(xtit.c_str());
  gr_ratio_data_tot->GetXaxis()->SetTitleSize(.09);
  gr_ratio_data_tot->GetXaxis()->SetLabelSize(.08);
  gr_ratio_data_tot->GetXaxis()->SetLabelOffset(.04);
  gr_ratio_data_tot->GetYaxis()->SetNdivisions(508);
  gr_ratio_data_tot->GetYaxis()->SetLabelSize(.08);
  gr_ratio_data_tot->GetYaxis()->CenterTitle(true);
  gr_ratio_data_tot->GetYaxis()->SetTitleSize(.08);
  gr_ratio_data_tot->GetYaxis()->SetTitleOffset(.8);
  gr_ratio_data_tot->GetYaxis()->SetTitle("Prediction / Data");

  gr_ratio_data_tot->GetXaxis()->SetTickLength(.05);
  gPad->RedrawAxis(); //to avoid the overlapping of error bands with axis ticks
  gr_ratio_data_tot->GetYaxis()->SetRangeUser(ratio_ymin,ratio_ymax);
  
  if(observable=="DYll" || observable=="Mjj" || observable=="Mll" || observable=="jet0_pt" || observable=="jet1_pt" || observable=="DYll" || observable=="Ptll" || observable=="lep0_pt" || observable=="lep1_pt" || observable=="pt_H" || observable=="costhetastar")
  {
    std::string labelname = "";
    float x_lab, lab_minus;
    if(observable=="DYll")
    {
    	gr_ratio_data_tot->GetXaxis()->ChangeLabel(8,-1,0,-1,-1,-1,"");
      	gr_ratio_data_tot->GetXaxis()->ChangeLabel(7,-1,0,-1,-1,-1,""); 
      	//gr_ratio_data_tot->GetXaxis()->ChangeLabel(6,-1,0,-1,-1,-1,""); 
      	labelname="#infty";
      	lab_minus=.28;
      	x_lab=1.4;
    }
    if(observable == "costhetastar")
    {
      gr_ratio_data_tot->GetXaxis()->ChangeLabel(7,-1,0,-1,-1,-1,"");
      gr_ratio_data_tot->GetXaxis()->ChangeLabel(6,-1,0,-1,-1,-1,""); 
      gr_ratio_data_tot->GetXaxis()->ChangeLabel(5,-1,0,-1,-1,-1,""); 
      labelname="1.0";
      minus = .1;
      plus = .1;
      x_lab = 0.58;
      lab_minus=.32;
      //ratio_ymin=0.2;

    }
    if(observable == "Mjj") {
    gr_ratio_data_tot->GetXaxis()->ChangeLabel(7,-1,0,-1,-1,-1,"");
    gr_ratio_data_tot->GetXaxis()->ChangeLabel(6,-1,0,-1,-1,-1,"");
    labelname="6000";
    minus = .1;
    plus = .2;
    x1 = 15;
    x2 = 30;
    x3 =55;
    x4 = 100;
    x_lab = 3100;
    lab_minus = .4;
    }
    if(observable == "Mll") {
      gr_ratio_data_tot->GetXaxis()->ChangeLabel(7,-1,0,-1,-1,-1,"");
      gr_ratio_data_tot->GetXaxis()->ChangeLabel(8,-1,0,-1,-1,-1,"");
      gr_ratio_data_tot->GetXaxis()->ChangeLabel(9,-1,0,-1,-1,-1,"");
      gr_ratio_data_tot->GetXaxis()->ChangeLabel(10,-1,0,-1,-1,-1,"");
      gr_ratio_data_tot->GetXaxis()->ChangeLabel(11,-1,0,-1,-1,-1,"");
      labelname="#infty";
      x_lab=98;
      lab_minus = 0.7;
      minus = .2;
      plus = .2;
      x1=1.;
      x2 =1.;
    }
    if(observable=="jet0_pt")
    {
      gr_ratio_data_tot->GetXaxis()->ChangeLabel(9,-1,0,-1,-1,-1,"");
      gr_ratio_data_tot->GetXaxis()->ChangeLabel(8,-1,0,-1,-1,-1,"");
      gr_ratio_data_tot->GetXaxis()->ChangeLabel(7,-1,0,-1,-1,-1,"");
      gr_ratio_data_tot->GetXaxis()->ChangeLabel(6,-1,0,-1,-1,-1,""); 
      labelname = "700";
      x_lab = 410;
      lab_minus=0.38;
      minus = 0.15;
      plus = .15;
      x1 =1.5;
      x2 =1.9;
      x3 = 3.5;
      x4 = 6.5;
    }
    if(observable=="jet1_pt")
    {
      gr_ratio_data_tot->GetXaxis()->ChangeLabel(10,-1,0,-1,-1,-1,"");
      gr_ratio_data_tot->GetXaxis()->ChangeLabel(9,-1,0,-1,-1,-1,"");
      gr_ratio_data_tot->GetXaxis()->ChangeLabel(8,-1,0,-1,-1,-1,"");
     // gr_ratio_data_tot->GetXaxis()->ChangeLabel(7,-1,0,-1,-1,-1,"");
     // gr_ratio_data_tot->GetXaxis()->ChangeLabel(6,-1,0,-1,-1,-1,""); 
      labelname = "350";
      x_lab = 178;
      lab_minus = 0.38;
      minus = 0.1;
      plus = 0.15;
      x1 = 1.;
      x2 = 1.5; 
      x3 = 3;
      x4 = 5.5; 
    }
    if(observable=="Ptll")
    {
      gr_ratio_data_tot->GetXaxis()->ChangeLabel(12,-1,0,-1,-1,-1,"");
      gr_ratio_data_tot->GetXaxis()->ChangeLabel(11,-1,0,-1,-1,-1,"");
      gr_ratio_data_tot->GetXaxis()->ChangeLabel(10,-1,0,-1,-1,-1,"");
      gr_ratio_data_tot->GetXaxis()->ChangeLabel(9,-1,0,-1,-1,-1,"");
      labelname = "1000";
      x_lab = 220;
      lab_minus = 0.35;
      minus = 0.15;
      plus = 0.15;
      x1 = 1.7;
      x2 = 1.8; 
      x3 = 1.2;
      x4 = 4.7; 
    }
    if(observable=="lep0_pt")
    {
      gr_ratio_data_tot->GetXaxis()->ChangeLabel(10,-1,0,-1,-1,-1,"");
      gr_ratio_data_tot->GetXaxis()->ChangeLabel(9,-1,0,-1,-1,-1,"");
      gr_ratio_data_tot->GetXaxis()->ChangeLabel(8,-1,0,-1,-1,-1,"");
      gr_ratio_data_tot->GetXaxis()->ChangeLabel(7,-1,0,-1,-1,-1,"");
      labelname="500";
      x_lab = 185;
      lab_minus = 0.7;
      minus=0.2;
      plus=0.2;
      x1 = 1.;
      x2 = 1.5; 
      x3 = 2.;
      x4 = 4.5; 
    }
    if(observable=="lep1_pt")
    {
      gr_ratio_data_tot->GetXaxis()->ChangeLabel(11,-1,0,-1,-1,-1,"");
      gr_ratio_data_tot->GetXaxis()->ChangeLabel(10,-1,0,-1,-1,-1,"");
      gr_ratio_data_tot->GetXaxis()->ChangeLabel(9,-1,0,-1,-1,-1,"");
      gr_ratio_data_tot->GetXaxis()->ChangeLabel(8,-1,0,-1,-1,-1,"");
      gr_ratio_data_tot->GetXaxis()->ChangeLabel(7,-1,0,-1,-1,-1,"");
  
      labelname="200";
      x_lab = 98;
      lab_minus = 0.35;
      minus=0.2;
      plus=0.25;
      x1 = .6;
      x2 = .8; 
      x3 = 1.3;
      x4 = 2.7; 
    }
    if(observable=="pt_H")
    {
      gr_ratio_data_tot->GetXaxis()->ChangeLabel(9,-1,0,-1,-1,-1,"");
      gr_ratio_data_tot->GetXaxis()->ChangeLabel(8,-1,0,-1,-1,-1,"");
      gr_ratio_data_tot->GetXaxis()->ChangeLabel(7,-1,0,-1,-1,-1,"");
      labelname="850";
      x_lab = 390;
      lab_minus=0.73;
      minus = 0.2;
      plus = 0.4;
      x1 = 1.;
      x2 = 1.8; 
      x3 = 3.7;
      x4 = 6.5; 
    }

    TLatex latex;
    latex.SetTextSize(.08);
    if(observable=="Mll") latex.SetTextSize(.1);
    latex.DrawLatex(x_lab,ratio_ymin-lab_minus,labelname.c_str());
    TLine* line1 = new TLine(x_start, ratio_ymin, x_end, ratio_ymin);
    line1->SetLineColor(kWhite);
    line1->SetLineWidth(2);
    line1->Draw("same");
    TLine* line2 = new TLine(x_start-x1, ratio_ymin-minus, x_start+x2, ratio_ymin+plus);
    line2->SetLineColor(kBlack);
    line2->SetLineWidth(1.);
    line2->Draw("same");
    TLine* line3 = new TLine(x_start+x3, ratio_ymin-minus, x_start+x4, ratio_ymin+plus);
    line3->SetLineColor(kBlack);
    line3->SetLineWidth(1.);
    line3->Draw("same");
  }

  std::string savefile = "../plots/paper/" + observable + "diffXS_" + datatype +".pdf";
  c->SaveAs(savefile.c_str());
}
  