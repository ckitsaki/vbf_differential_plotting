
#include "../Style/AtlasStyle.C"

void fidxsec(float central_value=1.68, float stat_up=0.33, float stat_down=0.32, float sys_up=0.23, float sys_down=0.21, float lumi=11, float powpy8 = 2.07, float vbfnlopy8=2.01, float vbfnlo = 2.18, float madher7 = 2.16, float powher7=1.93, float vbfnlolo=2.69)
{
  gROOT->SetBatch(kTRUE);
  SetAtlasStyle();

  TCanvas *c = new TCanvas("atlas_rectangle","Canvas title",0.,0.,600,600);

  TGraph* gr = new TGraph();
  gr->SetPoint(0, central_value, 0);
  gr->SetPoint(1, central_value, 2.5);
  gr->SetLineColor(kBlue);
  gr->SetLineWidth(2.);
  gr->GetXaxis()->SetLimits(-0.2,2.95);
  gr->GetYaxis()->SetRangeUser(0,2.5);
  gr->GetYaxis()->SetLabelSize(0);
  gr->GetYaxis()->SetNdivisions(0);
  gr->Draw("AL");

  TGraphAsymmErrors* h_tot_unc_band = new TGraphAsymmErrors();
 // float tot_unc = TMath::Sqrt(TMath::Power(stat,2) + TMath::Power(syst,2) + TMath::Power(lumi,2));
  float tot_unc_up = TMath::Sqrt(TMath::Power(stat_up,2) + TMath::Power(sys_up,2));
  float tot_unc_down = TMath::Sqrt(TMath::Power(stat_down,2) + TMath::Power(sys_down,2));
  h_tot_unc_band->SetPoint(0, central_value, 0);
  h_tot_unc_band->SetPoint(1, central_value, 2.5);
  h_tot_unc_band->SetPointError(0, tot_unc_up, tot_unc_up, 0, 2.5); // 0, unc_down , unc_up, yrange->0,1
  h_tot_unc_band->SetFillColor(kGreen);
  h_tot_unc_band->SetLineColor(kGreen);
  h_tot_unc_band->Draw("e2 same");

  TGraphAsymmErrors* h_stat_band = new TGraphAsymmErrors();
  h_stat_band->SetPoint(0, central_value, 0);
  h_stat_band->SetPoint(1, central_value, 2.5);
  h_stat_band->SetPointError(0, stat_up, stat_up, 0, 2.5); // 0, stat_down, stat_up, yrange->0,1
  h_stat_band->SetLineColor(kBlue);
  h_stat_band->SetLineStyle(kDashed);
  h_stat_band->SetLineWidth(2);
  h_stat_band->SetFillColor(kYellow);
  
  h_stat_band->Draw("e2 same");

  TLine *line1 = new TLine(central_value-stat_up-.005, 0, central_value-stat_up-.005, 2.5);
  line1->SetLineColor(kBlue);
  line1->SetLineWidth(2);
  line1->SetLineStyle(kDashed);
  line1->Draw("same");
  TLine *line2 = new TLine(central_value+stat_up+.005, 0, central_value+stat_up+.005, 2.5);
  line2->SetLineColor(kBlue);
  line2->SetLineWidth(2);
  line2->SetLineStyle(kDashed);
  line2->Draw("same");

  gr->Draw("L same");
 
  gr->GetXaxis()->SetTitleSize(0.035);
  gr->GetXaxis()->SetLabelSize(0.035);
  gr->GetXaxis()->SetTitle("#it{#sigma}^{fid} [fb]");

  gPad->RedrawAxis();

  TGraphAsymmErrors* gr_powpy8 = new TGraphAsymmErrors();
  TGraphAsymmErrors* gr_vbfnlopy8 = new TGraphAsymmErrors();
  TGraphAsymmErrors* gr_vbfnlo = new TGraphAsymmErrors();
  TGraphAsymmErrors* gr_madher7 = new TGraphAsymmErrors();
  TGraphAsymmErrors* gr_powher7 = new TGraphAsymmErrors();
  TGraphAsymmErrors* gr_vbfnlolo = new TGraphAsymmErrors();
  
  gr_powpy8->SetMarkerStyle(21);//33);
  gr_powher7->SetMarkerStyle(22);
  gr_madher7->SetMarkerStyle(29);
  gr_vbfnlopy8->SetMarkerStyle(23);
  gr_vbfnlo->SetMarkerStyle(33);
  gr_vbfnlolo->SetMarkerStyle(47);

  gr_powpy8->SetLineWidth(2);//33);
  gr_powher7->SetLineWidth(2);
  gr_madher7->SetLineWidth(2);
  gr_vbfnlopy8->SetLineWidth(2);
  gr_vbfnlo->SetLineWidth(2);
  gr_vbfnlolo->SetLineWidth(2);

  gr_powpy8->SetMarkerColor(kAzure-5);
  gr_powher7->SetMarkerColor(kOrange+2);
  gr_madher7->SetMarkerColor(kPink+5);
  gr_vbfnlopy8->SetMarkerColor(kGreen+2);
  gr_vbfnlolo->SetMarkerColor(kBlue-1);
  gr_vbfnlo->SetMarkerColor(kRed+2);
   
  gr_powpy8->SetLineColor(kAzure-5);
  gr_powher7->SetLineColor(kOrange+2);
  gr_madher7->SetLineColor(kPink+5);
  gr_vbfnlopy8->SetLineColor(kGreen+2);
  gr_vbfnlolo->SetLineColor(kBlue-1);
  gr_vbfnlo->SetLineColor(kRed+2);
  

  gr_powpy8->SetMarkerSize(1.5);
  gr_vbfnlopy8->SetMarkerSize(1.5);
  gr_vbfnlo->SetMarkerSize(2.1);
  gr_madher7->SetMarkerSize(2.1);
  gr_powher7->SetMarkerSize(1.5);
  gr_vbfnlolo->SetMarkerSize(1.5);
  
  gr_powpy8->SetPoint(0, powpy8, 1.74);
  gr_powpy8->SetPointError(0, powpy8*1.9/100, powpy8*2.1/100, 0, 0);
  gr_powher7->SetPoint(0, powher7,  1.58);
  gr_powher7->SetPointError(0, powher7*1.9/100, powher7*2.1/100, 0, 0);
  gr_madher7->SetPoint(0, madher7, 1.41);
  gr_madher7->SetPointError(0, 0, 0, 0, 0 );
  gr_vbfnlopy8->SetPoint(0, vbfnlopy8, 1.26);
  gr_vbfnlopy8->SetPointError(0, vbfnlopy8*5.2/100, vbfnlopy8*6/100, 0, 0);
  gr_vbfnlolo->SetPoint(0, vbfnlolo, 1.09);
  gr_vbfnlolo->SetPointError(0, vbfnlolo*5.2/100, vbfnlolo*6/100, 0, 0);
  gr_vbfnlo->SetPoint(0, vbfnlo, .96);
  gr_vbfnlo->SetPointError(0, vbfnlo*6.6/100, vbfnlo*5.1/100, 0, 0);

  gr_powpy8->Draw("psame");
  gr_vbfnlopy8->Draw("psame");
  gr_vbfnlo->Draw("psame");
  gr_madher7->Draw("psame");
  gr_powher7->Draw("psame");
  gr_vbfnlolo->Draw("psame");
  
  auto legAtlas = new TLegend(0.18,0.88,0.2,.92);
  legAtlas->SetBorderSize(0);
  legAtlas->SetFillStyle(0);
  legAtlas->SetTextSize(0.04);
  legAtlas->AddEntry((TObject*)0, "#it{ATLAS} #bf{Internal}", "");
  legAtlas->Draw();

  auto legend0 = new TLegend(0.17,0.44,0.4,0.72);
  legend0->SetBorderSize(0);
  legend0->SetFillStyle(0);
  legend0->SetTextSize(0.03);
  legend0->AddEntry(gr_powpy8,"#bf{Powheg+Pythia8}", "p");

  legend0->AddEntry((TObject*)0, "", "");
  legend0->AddEntry(gr_powher7, "#bf{Powheg+Herwig7}", "p");
  legend0->AddEntry((TObject*)0, "", "");
  legend0->AddEntry(gr_madher7, "#bf{MG5+Herwig7}", "p");
  legend0->AddEntry((TObject*)0, "", "");
  legend0->AddEntry(gr_vbfnlopy8, "#bf{VBFNLO@LO+Pythia8}", "p");
  legend0->AddEntry((TObject*)0, "", "");
  legend0->AddEntry(gr_vbfnlolo, "#bf{VBFNLO@LO}", "p");
  legend0->AddEntry((TObject*)0, "", "");
  legend0->AddEntry(gr_vbfnlo, "#bf{VBFNLO@NLO}", "p"); 
  legend0->Draw();

  TLatex latex;
  latex.SetTextSize(0.03);
  latex.DrawLatex(-0.1, 2.15, "H#rightarrow WW* #rightarrow #scale[0.95]{e}#nu + #mu#nu");
  latex.DrawLatex(-0.1, 2.00, "VBF fiducial cross section");
  //\ensuremath{H{\rightarrow\,}WW^{\ast}{\rightarrow\,}e\nu\mu\nu}


  auto legend = new TLegend(0.18,0.19,0.5,0.38);
  legend->SetBorderSize(0);
  legend->SetFillStyle(0);
  legend->SetTextSize(0.03);
  legend->SetHeader("#bf{Data #sqrt{#it{s}} = 13 TeV, 139 fb^{-1}}");
  legend->AddEntry(gr, "#bf{1.68 #pm 0.33 #pm 0.23 fb}", "l");
  legend->AddEntry(h_stat_band, "#bf{stat.}", "f");
  legend->AddEntry(h_tot_unc_band, "#bf{stat. + syst.}","f");
  legend->Draw();
  
  c->SaveAs("./fid_xsec.pdf");
}
