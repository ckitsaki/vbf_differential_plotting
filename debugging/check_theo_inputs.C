
#include "./src/Style/AtlasStyle.C"
#include "./src/plotting.h"



std::string v_theo_vbf[5] =  	{"theo_vbf_shower", "theo_vbf_alphas", "theo_vbf_scale", "theo_vbf_pdf4lhc", "theo_vbf_generator"}; 

std::string v_theo_ggf[11] =  	{"theo_ggF_shower", "theo_ggF_alphas", "theo_ggF_pdf4lhc", "theo_ggF_qcd_wg1_mu", "theo_ggF_qcd_wg1_res", "theo_ggF_qcd_wg1_mig01", "theo_ggF_qcd_wg1_mig12", "theo_ggF_qcd_wg1_vbf2j", "theo_ggF_qcd_wg1_vbf3j", "theo_ggF_qcd_wg1_qm_t", "theo_ggF_qcd_wg1_pTH" };

std::string v_theo_top[6] =     {"theo_ttbar_shower", "theo_ttbar_scale", "theo_ttbar_pdf", "theo_ttbar_matching", "theo_ttbar_isr", "theo_ttbar_fsr" };

std::string v_theo_Zjets[4] =   {"theo_ztautau_alphas", "theo_ztautau_scale", "theo_ztautau_pdf", "theo_ztautau_generator"};

std::string v_theo_diboson[7] = {"theo_ww_shower",  "theo_ww_alphas", "theo_ww_scale", "theo_ww_pdf", "theo_ww_QSF", "theo_ww_CKKW",  "theo_ww_CSSKIN"};

TH1F* plotting::getNominalHisto(std::string sample)
{
  std::string tree_name = getSampleName(sample) + "_nominal";
  
  TreeReader *treeReader = new TreeReader(m_regionName, sample, tree_name, m_lxplus);

  std::cout<<sample<<" - added \n";
  
  TH1F* h;
  if(!m_forPaper)
  {
    h = new TH1F("histo", "histo", m_nbins, m_xmin, m_xmax);
  }
  else h = new TH1F("histo", "histo", m_nbins, m_binsEdges);

  std::vector<TTree*> v = treeReader->getTrees();

  for(int i=0; i<v.size(); i++)
  {
    for(int j=0; j<v.at(i)->GetEntries(); j++){
      (v.at(i))->GetEvent(j);
      float variable_to_plot = treeReader->getObservable(m_obsName);
      if(treeReader->getCut()) h->Fill(variable_to_plot,treeReader->weight);
      else continue;
    }
    
  } 

  std::cout<<h->Integral()<<"\n";

  delete treeReader;
  return h;
}

TH1F* plotting::getNominalHisto(std::string sample, std::vector<float> mcChannelNumber)
{
  std::string tree_name = getSampleName(sample) + "_nominal";
  
  TreeReader *treeReader = new TreeReader(m_regionName, sample, tree_name, m_lxplus);

  std::cout<<sample<<" - added \n";

  TH1F* h;
  if(!m_forPaper)
  {
    h = new TH1F("histo", "histo", m_nbins, m_xmin, m_xmax);
  }
  else h = new TH1F("histo", "histo", m_nbins, m_binsEdges);

  std::vector<TTree*> v = treeReader->getTrees();

  for(int i=0; i<v.size(); i++)
  {
    for(int j=0; j<v.at(i)->GetEntries(); j++){
      (v.at(i))->GetEvent(j);
      float variable_to_plot = treeReader->getObservable(m_obsName);
    
    for(int ndsid=0; ndsid<mcChannelNumber.size(); ndsid++){
      if(treeReader->mcChannelNumber==mcChannelNumber.at(ndsid)){
        if(treeReader->getCut()) h->Fill(variable_to_plot,treeReader->weight);
        else continue;
      }
      else continue;
    }    
    }
  } 

  std::cout<<h->Integral()<<"\n";

  delete treeReader;
  return h;
}

void plotting::getTheoryVariations(std::string sample, std::string theo_sys, TFile* f)
{

  std::string theo_filename = "./theo_systematics/" + sample + "_theory_2jets.root";
  if(m_regionName=="ggFCR3") theo_filename = "./theo_systematics/" + sample + "_theory_1jets.root";
  TFile* f_theo_file = new TFile(theo_filename.c_str(), "READ");
  std::string theo_nom = sample + "_" + theo_sys + "__Nom_" + m_regionName + "_" + m_obsName;
  std::string theo_var_up = sample + "_" + theo_sys + "__1up_" + m_regionName + "_" + m_obsName;
  std::string theo_var_down = sample + "_" + theo_sys + "__1down_" + m_regionName + "_" + m_obsName;
  
  TH1F* h_theo_nom = (TH1F*)f_theo_file->Get(theo_nom.c_str());
  TH1F* h_theo_var_up = (TH1F*)f_theo_file->Get(theo_var_up.c_str());
  TH1F* h_theo_var_down = (TH1F*)f_theo_file->Get(theo_var_down.c_str());

  TCanvas* canvas = new TCanvas();
  canvas->cd();
  h_theo_var_up->SetLineColor(kGreen+2);
  h_theo_nom->SetLineColor(kBlue+2);
  h_theo_var_down->SetLineColor(kRed+2);

 //fix this if(m_regionName=="SR") gPad->SetLogy();

  int nom_bin_max = h_theo_nom->GetMaximumBin();
  int up_bin_max = h_theo_var_up->GetMaximumBin();
  int down_bin_max = h_theo_var_down->GetMaximumBin();

  int nom_bin_min = h_theo_nom->GetMinimumBin();
  int up_bin_min = h_theo_var_up->GetMinimumBin();
  int down_bin_min = h_theo_var_down->GetMinimumBin();
  int min = 0;

  if( (h_theo_nom->GetBinContent(nom_bin_max) > h_theo_var_up->GetBinContent(up_bin_max) ) && (h_theo_nom->GetBinContent(nom_bin_max) > h_theo_var_down->GetBinContent(down_bin_max) ) )
  {
    if( h_theo_nom->GetBinContent(nom_bin_min)<0 ) min = h_theo_nom->GetBinContent(nom_bin_min)*0.2;
    if( h_theo_var_up->GetBinContent(nom_bin_min)<0 ) min = h_theo_var_up->GetBinContent(up_bin_min)*0.2;
    if( h_theo_var_down->GetBinContent(nom_bin_min)<0 ) min = h_theo_var_down->GetBinContent(down_bin_min)*0.2;
    h_theo_nom->Draw("hist");
    h_theo_nom->GetYaxis()->SetRangeUser(min, h_theo_nom->GetBinContent(nom_bin_max)*0.2);
    h_theo_var_up->Draw("hist same");
    h_theo_var_down->Draw("hist same");
  }

  if( (h_theo_var_up->GetBinContent(up_bin_max) > h_theo_nom->GetBinContent(nom_bin_max) ) && (h_theo_var_up->GetBinContent(up_bin_max) > h_theo_var_down->GetBinContent(down_bin_max) ) )
  {
    if( h_theo_nom->GetBinContent(nom_bin_min)<0 ) min = h_theo_nom->GetBinContent(nom_bin_min)*1.5;
    if( h_theo_var_up->GetBinContent(nom_bin_min)<0 ) min = h_theo_var_up->GetBinContent(up_bin_min)*1.5;
    if( h_theo_var_down->GetBinContent(nom_bin_min)<0 ) min = h_theo_var_down->GetBinContent(down_bin_min)*1.5;
    h_theo_var_up->Draw("hist");
    h_theo_var_up->GetYaxis()->SetRangeUser(min, h_theo_var_up->GetBinContent(up_bin_max)*1.5);
    h_theo_nom->Draw("hist same");
    h_theo_var_down->Draw("hist same");
  }

  if( (h_theo_var_down->GetBinContent(down_bin_max) > h_theo_nom->GetBinContent(nom_bin_max) ) && (h_theo_var_down->GetBinContent(down_bin_max) > h_theo_var_up->GetBinContent(up_bin_max) ) )
  {
    if( h_theo_nom->GetBinContent(nom_bin_min)<0 ) min = h_theo_nom->GetBinContent(nom_bin_min)*1.5;
    if( h_theo_var_up->GetBinContent(nom_bin_min)<0 ) min = h_theo_var_up->GetBinContent(up_bin_min)*1.5;
    if( h_theo_var_down->GetBinContent(nom_bin_min)<0 ) min = h_theo_var_down->GetBinContent(down_bin_min)*1.5;
    h_theo_var_down->Draw("hist");
    h_theo_var_down->GetYaxis()->SetRangeUser(min, h_theo_var_down->GetBinContent(down_bin_max)*1.5);
    h_theo_nom->Draw("hist same");
    h_theo_var_up->Draw("hist same");
  }

  auto legend = new TLegend(0.5,0.7,0.72,0.92);
  legend->SetBorderSize(0);
  legend->SetFillStyle(0);
  legend->SetTextSize(0.);
  legend->AddEntry(h_theo_nom, "Nominal", "f");
  legend->AddEntry(h_theo_var_up, "up", "f");
  legend->AddEntry(h_theo_var_down, "down", "f");


  legend->Draw();
  std::string out_name = "./sys_checks/" + sample + "_" + theo_sys + ".pdf";
  canvas->SaveAs(out_name.c_str());
  f->cd();
  std::string canv_name = theo_sys + "_" + m_regionName + "_canv"; 
  canvas->SetName(canv_name.c_str());
  canvas->Write();

}

plotting::plotting(std::string sample, std::string observable, std::string region)
{
  gROOT->SetBatch(kTRUE);
  SetAtlasStyle();
  gStyle->SetOptStat(1111);
  setObsName(observable);
  setRegionName(region);
  
  int v_size;
  std::vector<std::string> lvec;

  std::string filename = "./sys_checks/output_"+sample+"_"+region+"_"+observable+".root";
  TFile* out_file = new TFile(filename.c_str(),"RECREATE");

  if(sample=="vbf") {
    v_size = sizeof(v_theo_vbf)/sizeof(v_theo_vbf[0]);
    for(int i=0; i<v_size; ++i) lvec.push_back(v_theo_vbf[i]);
  }
  if(sample=="ggf") {
    v_size = sizeof(v_theo_ggf)/sizeof(v_theo_ggf[0]);
    for(int i=0; i<v_size; ++i) lvec.push_back(v_theo_ggf[i]);
  }
  if(sample=="diboson") {
    v_size = sizeof(v_theo_diboson)/sizeof(v_theo_diboson[0]);
    for(int i=0; i<v_size; ++i) lvec.push_back(v_theo_diboson[i]);
  }
  if(sample=="top") {
    v_size = sizeof(v_theo_top)/sizeof(v_theo_top[0]);
    for(int i=0; i<v_size; ++i) lvec.push_back(v_theo_top[i]);
  }
  if(sample=="Zjets0") {
    v_size = sizeof(v_theo_Zjets)/sizeof(v_theo_Zjets[0]);
    for(int i=0; i<v_size; ++i) lvec.push_back(v_theo_Zjets[i]);
  }

  out_file->cd();

  for(int i = 0; i < v_size; i++)
  {
    getTheoryVariations(sample, lvec.at(i), out_file);
  }

  out_file->Close();

}

void check_theo_inputs(std::string observable, std::string region)
{

  std::string theo_names[5] = {"vbf", "ggf", "diboson", "top", "Zjets0"};
  
  for(int i=0; i<sizeof(theo_names)/sizeof(theo_names[0]); i++)
    plotting *do_plots = new plotting(theo_names[i] ,observable, region);
}


