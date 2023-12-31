
#include "./src/Style/AtlasStyle.C"
#include "./src/plotting.h"


std::string v_theo_vbf[5] =  	{"theo_vbf_shower", "theo_vbf_alphas", "theo_vbf_scale", "theo_vbf_pdf4lhc", "theo_vbf_generator"}; 

std::string v_theo_ggf[11] =  	{"theo_ggF_shower", "theo_ggF_alphas", "theo_ggF_pdf4lhc", "theo_ggF_qcd_wg1_mu", "theo_ggF_qcd_wg1_res", "theo_ggF_qcd_wg1_mig01", "theo_ggF_qcd_wg1_mig12", "theo_ggF_qcd_wg1_vbf2j", "theo_ggF_qcd_wg1_vbf3j", "theo_ggF_qcd_wg1_qm_t", "theo_ggF_qcd_wg1_pTH" };

std::string v_theo_top[6] =     {"theo_ttbar_shower", "theo_ttbar_scale", "theo_ttbar_pdf", "theo_ttbar_matching", "theo_ttbar_isr", "theo_ttbar_fsr" };

std::string v_theo_Zjets[4] =   {"theo_ztautau_alphas", "theo_ztautau_scale", "theo_ztautau_pdf", "theo_ztautau_generator"};

std::string v_theo_diboson[5] = {"theo_ww_shower",  "theo_ww_alphas", "theo_ww_scale", "theo_ww_pdf", "theo_ww_CKKW"};

TH1F* plotting::getNominalHisto(std::string sample)
{
  std::string tree_name = getSampleName(sample) + "_nominal";
  
  TreeReader *treeReader = new TreeReader(m_regionName, sample, tree_name, m_lxplus);
  
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
//1Feb itan to proigoumeno
  std::string theo_filename = "/usatlas/u/sagar/usatlaswork/scripts/CharaStackPlotsHists/StackPlots_MT/"+ sample + "_histos_MT.root";//"/usatlas/u/sagar/usatlaswork/scripts/CharaStackPlotsHists/StackPlots_22Feb2022/"+ sample + "_histos_2jets.root";//"/usatlas/u/sagar/usatlaswork/scripts/CharaStackPlotsHists/StackPlots_SR12/"+sample+"_histos_SR12.root";//"/usatlas/u/sagar/usatlaswork/scripts/CharaStackPlotsHists/StackPlots_1Feb2022/"+ sample + "_histos_2jets.root";//"./theo_systematics/" + sample + "_histos_2jets.root";
  if(m_regionName=="ggFCR3") theo_filename = "/usatlas/u/sagar/usatlaswork/scripts/CharaStackPlotsHists/StackPlots_22Feb2022/"+ sample + "_histos_1jets.root";//"./theo_systematics/" + sample + "_histos_1jets.root";
  TFile* f_theo_file = new TFile(theo_filename.c_str(), "READ");
  std::string theo_nom = sample + "_" + theo_sys + "__Nom_" + m_regionName + "_" + m_obsName;
  std::string theo_var_up = sample + "_" + theo_sys + "__1up_" + m_regionName + "_" + m_obsName;
  std::string theo_var_down = sample + "_" + theo_sys + "__1down_" + m_regionName + "_" + m_obsName;
  
  TH1F* h_theo_nom = (TH1F*)f_theo_file->Get(theo_nom.c_str());
  TH1F* h_theo_var_up = (TH1F*)f_theo_file->Get(theo_var_up.c_str());
  TH1F* h_theo_var_down = (TH1F*)f_theo_file->Get(theo_var_down.c_str());

  h_theo_nom->SetMarkerStyle(1);
  TCanvas* canvas = new TCanvas();
  canvas->cd();

  h_theo_var_up->SetLineColor(kGreen+2);
  h_theo_nom->SetLineColor(kBlue+2);
  h_theo_var_down->SetLineColor(kRed+2);

  h_theo_nom->Draw("histE");

  h_theo_var_up->Draw("hist same");
  h_theo_var_down->Draw("hist same");
  h_theo_nom->GetYaxis()->UnZoom();
  h_theo_var_down->GetYaxis()->UnZoom();
  h_theo_var_up->GetYaxis()->UnZoom();


  auto legend = new TLegend(0.5,0.7,0.72,0.92);
  legend->SetBorderSize(0);
  legend->SetFillStyle(0);
  legend->SetTextSize(0.);
  legend->AddEntry(h_theo_nom, Form("#scale[1.]{Nominal %3.0f evnts}",h_theo_nom->Integral()), "f");
  legend->AddEntry(h_theo_var_up, Form("#scale[1.]{up %3.0f evnts}",h_theo_var_up->Integral()), "f");
  legend->AddEntry(h_theo_var_down, Form("#scale[1.]{down %3.0f evnts}",h_theo_var_down->Integral()), "f");
  legend->AddEntry(h_theo_nom, "#scale[1.]{stat unc.}", "le");
  legend->Draw();
  std::string out_name = "./debugging/sys_checks/theo/" + sample + "_" + theo_sys + ".pdf";
  canvas->SaveAs(out_name.c_str());
  f->cd();
  std::string canv_name = theo_sys + "_" + m_regionName + "_canv"; 
  canvas->SetName(canv_name.c_str());
  canvas->Write();

}

plotting::plotting(std::string sample, std::string observable, std::string region, bool checkTheory)
{
  gROOT->SetBatch(kTRUE);
  SetAtlasStyle();
  gStyle->SetOptStat(1111);
  setObsName(observable);
  setRegionName(region);

if(checkTheory) {  
  int v_size;
  std::vector<std::string> lvec;

  std::string filename = "./debugging/sys_checks/theo/output_"+sample+"_"+region+"_"+observable+".root";
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
 else {
  workOnLxplus(false);
  plotsForPaper(false);
  setBins(false);
  std::string exp_filename = "./debugging/sys_checks/exp_systematics/"+region+"/"+observable+"_"+region+"_ExpSys.root";//"./sys_files/systematics.root"; //"./exp_systematics/"+region+"/"+observable+"_"+region+"_ExpSys.root";
  TFile* f_expsys_file = new TFile(exp_filename.c_str(), "READ");

  TDirectory *current_sourcedir = gDirectory;
  int totalKeys = current_sourcedir->GetNkeys();
  TList* list = current_sourcedir->GetListOfKeys();

  std::string filename = "./debugging/sys_checks/exp_sys/output_"+sample+"_"+region+"_"+observable+"_expSys_checks.root";
  TFile* out_file = new TFile(filename.c_str(),"RECREATE");

  TH1F* h_nom;
  if(sample == "diboson"){
     h_nom = getNominalHisto("diboson1");
     TH1F* h_nom_2 = getNominalHisto("diboson2");
     TH1F* h_nom_3 = getNominalHisto("WWEW");
     h_nom->Add(h_nom_2);
     h_nom->Add(h_nom_3);

   }

   if(sample == "vh") h_nom = getNominalHisto("vh");
   if(sample == "top") {
    h_nom = getNominalHisto("top1");
    TH1F* h_nom_2 = getNominalHisto("top2");
    h_nom->Add(h_nom_2);
   }
   if(sample == "vbf") h_nom = getNominalHisto("vbf");
   if(sample == "Vgamma") h_nom = getNominalHisto("Vgamma");
   if(sample == "ggf") h_nom = getNominalHisto("ggf");
   if(sample == "htt") h_nom = getNominalHisto("htt");
   if(sample == "Zjets") h_nom = getNominalHisto("Zjets");
   if(sample == "Fakes") h_nom = getNominalHisto("Fakes");

  int ikey = 0;
  do{
    std::string process;
    
    current_sourcedir->cd();
    TObject* f = list->At(ikey);
    TH1F* h_up = (TH1F*)gDirectory->Get(f->GetName());
    process = h_up->GetName();

    if( !(process.find(sample.c_str()) != std::string::npos)){ ikey++; continue;}
   
   std::cout<<ikey<<std::endl;
   ikey++;

   TObject* fob = list->At(ikey);
   current_sourcedir->cd();
   TH1F* h_down = (TH1F*)gDirectory->Get(fob->GetName());
  
   // start plotting
   h_nom->SetMarkerStyle(1);
   TCanvas* canvas = new TCanvas();
   canvas->cd();

  h_up->SetLineColor(kGreen+2);
  h_nom->SetLineColor(kBlue+2);
  h_down->SetLineColor(kRed+2);

  h_nom->Draw("histE");
  h_up->Draw("hist same");
  h_down->Draw("hist same");
  h_nom->GetYaxis()->UnZoom();
  h_nom->SetName(fob->GetName());

  auto legend = new TLegend(0.5,0.7,0.72,0.92);
  legend->SetBorderSize(0);
  legend->SetFillStyle(0);
  legend->SetTextSize(0.);
  legend->AddEntry(h_nom, Form("#scale[1.]{Nominal %3.0f evnts}",h_nom->Integral()), "f");
  legend->AddEntry(h_up, Form("#scale[1.]{up %3.0f evnts}",h_up->Integral()), "f");
  legend->AddEntry(h_down, Form("#scale[1.]{down %3.0f evnts}",h_down->Integral()), "f");
  legend->AddEntry(h_nom, "#scale[1.]{stat unc.}", "le");
  legend->Draw();

  process.erase(process.length()-5);
  std::string out_name = "./debugging/sys_checks/exp_sys/" + process + ".pdf";
  canvas->SaveAs(out_name.c_str());
  out_file->cd();
  std::string canv_name = process + "_" + m_regionName + "_canv"; 
  canvas->SetName(canv_name.c_str());
  canvas->Write();
   
   ikey++;

   delete h_up;
   delete h_down;

  }while(ikey<totalKeys);

  out_file->Close();
 }


}

void check_theo_inputs(std::string observable, std::string region)
{

  std::string theo_names[5] = {"vbf", "ggf", "diboson", "top", "Zjets0"};
  
  for(int i=0; i<sizeof(theo_names)/sizeof(theo_names[0]); i++)
    plotting *do_plots = new plotting(theo_names[i] ,observable, region, true);
}

void check_exp_sys_inputs(std::string observable, std::string region)
{
  std::string names[9] = {"diboson", "vh", "top", "vbf", "Vgamma", "ggf", "htt", "Zjets", "Fakes"};
  
  for(int i=0; i<sizeof(names)/sizeof(names[0]); i++)
    plotting *test = new plotting(names[i].c_str(), observable, region, false);
}


