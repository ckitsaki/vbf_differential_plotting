
#include "Style/AtlasStyle.C"
#include "plotting.h"

std::string v_theo_vbf[5] = {"theo_vbf_scale", "theo_vbf_alphas", "theo_vbf_pdf4lhc", "theo_vbf_shower", "theo_vbf_generator"};

std::string v_theo_ggf[11] = {"theo_ggF_qcd_wg1_mu", "theo_ggF_qcd_wg1_res", "theo_ggF_qcd_wg1_mig01", "theo_ggF_qcd_wg1_mig12", "theo_ggF_qcd_wg1_vbf2j", "theo_ggF_qcd_wg1_vbf3j", "theo_ggF_qcd_wg1_qm_t", "theo_ggF_qcd_wg1_pTH", "theo_ggF_pdf4lhc", "theo_ggF_alphas", "theo_ggF_shower"};

std::string v_theo_top[6] = {"theo_ttbar_shower", "theo_ttbar_matching", "theo_ttbar_scale", "theo_ttbar_isr", "theo_ttbar_fsr", "theo_ttbar_pdf"};

std::string v_theo_Zjets[4] = {"theo_ztautau_scale", "theo_ztautau_alphas", "theo_ztautau_pdf", "theo_ztautau_generator"};

std::string v_theo_diboson[7] = {"theo_ww_scale", "theo_ww_alphas", "theo_ww_pdf", "theo_ww_QSF", "theo_ww_CKKW", "theo_ww_shower", "theo_ww_CSSKIN"};

TH1F* plotting::getNominalHisto(std::string sample, bool lxplus)
{
  std::string tree_name = getSampleName(sample) + "_nominal";
  
  TreeReader *treeReader = new TreeReader(m_regionName, sample, tree_name, lxplus);

  std::cout<<sample<<" - added \n";

  TH1F* h =  new TH1F("histo", "histo", m_nbins, m_xmin, m_xmax);

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

TH1F* plotting::getNominalHisto(std::string sample, std::vector<float> mcChannelNumber, bool lxplus)
{
  std::string tree_name = getSampleName(sample) + "_nominal";
  
  TreeReader *treeReader = new TreeReader(m_regionName, sample, tree_name, lxplus);

  std::cout<<sample<<" - added \n";

  TH1F* h =  new TH1F("histo", "histo", m_nbins, m_xmin, m_xmax);

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

TH1F* plotting::getTheoryHisto(std::string sample, std::string theo_sys, bool isUp)
{
  std::string theo_filename = "./theo_systematics/" + sample + "_theory_2jets.root";
  if(m_regionName=="ggFCR3") theo_filename = "./theo_systematics/" + sample + "_theory_01jets.root";
  TFile* f_theo_file = new TFile(theo_filename.c_str());
  std::string theo_nom = sample + "_" + theo_sys + "__Nom_" + m_regionName + "_" + m_obsName;
  std::string theo_var = sample + "_" + theo_sys + "__1up_" + m_regionName + "_" + m_obsName;
  if(!isUp) theo_var = sample + "_" + theo_sys + "__1down_" + m_regionName + "_" + m_obsName;
  TH1F* h_theo_nom = (TH1F*)f_theo_file->Get(theo_nom.c_str());
  TH1F* h_theo_var = (TH1F*)f_theo_file->Get(theo_var.c_str());

  h_theo_nom->Add(h_theo_var,-1);

  return h_theo_nom;
}

void plotting::PlotsforNote(std::string region, std::string observable, bool unblind, bool addTheo, bool lxplus)
{

  std::cout<<"Preparing the plot for the supporting note.."<<std::endl;

  std::vector<float> v_ttbar = {410472};
  std::vector<float> v_singleTop = {410648, 410649};

  h_Fakes = getNominalHisto("Fakes", lxplus);
  h_WW = getNominalHisto("diboson1", lxplus);
  h_NonWW = getNominalHisto("diboson2", lxplus);
  h_WWEW = getNominalHisto("WWEW", lxplus);
  h_Zjets = getNominalHisto("Zjets", lxplus);
  h_Vgamma = getNominalHisto("Vgamma", lxplus);
  h_ttbar1 = getNominalHisto("top1", v_ttbar, lxplus);
  h_ttbar2 = getNominalHisto("top2", v_ttbar, lxplus);
  h_singleTop1 = getNominalHisto("top1", v_singleTop, lxplus);
  h_singleTop2 = getNominalHisto("top2", v_singleTop, lxplus);
  h_vbf = getNominalHisto("vbf", lxplus);
  h_ggf = getNominalHisto("ggf", lxplus);
  h_vh = getNominalHisto("vh", lxplus);
  h_htt = getNominalHisto("htt", lxplus);
  
  if(unblind) h_data = getNominalHisto("data", lxplus);
  
  THStack* h_stack = new THStack("h_stack","");

  h_WW->Add(h_WWEW);
  h_ttbar1->Add(h_ttbar2);
  h_singleTop1->Add(h_singleTop2);
  h_NonWW->Add(h_Vgamma);

  h_Fakes->SetFillColor(kCyan);
  h_Fakes->SetLineColor(kBlack);
  h_WW->SetFillColor(kViolet+2);
  h_WW->SetLineColor(kBlack);
  h_NonWW->SetFillColor(kMagenta);
  h_NonWW->SetLineColor(kBlack);
  h_ttbar1->SetFillColor(kYellow-7);
  h_ttbar1->SetLineColor(kBlack);
  h_singleTop1->SetFillColor(kYellow+1);
  h_singleTop1->SetLineColor(kBlack);
  h_vbf->SetLineColor(kBlue);
  h_ggf->SetFillColor(kRed+1);
  h_ggf->SetLineColor(kRed+1);
  h_Zjets->SetFillColor(kGreen+2);
  h_Zjets->SetLineColor(kBlack);
  h_vh->SetFillColor(kViolet-8);
  h_vh->SetLineColor(kViolet-8);
  h_htt->SetFillColor(kOrange+3);
  h_htt->SetLineColor(kOrange+3);

  h_vbf->SetLineWidth(2);
  h_WW->SetLineWidth(1);
  h_Fakes->SetLineWidth(1);
  h_NonWW->SetLineWidth(1);
  h_ttbar1->SetLineWidth(1);
  h_singleTop1->SetLineWidth(1);
  h_Zjets->SetLineWidth(1);

  std::vector<float> fakes_stat, WW_stat, NonWW_stat, ttbar_stat, singleTop_stat, zjets_stat, vh_stat, htt_stat, ggf_stat, total_stat, x_stat, y_stat;

  // ================  statistical uncertainties ===================== //

  for(int ibin=0; ibin<m_nbins; ibin++)
  {
    fakes_stat.push_back(h_Fakes->GetBinError(ibin+1));
    WW_stat.push_back(h_WW->GetBinError(ibin+1));
    NonWW_stat.push_back(h_NonWW->GetBinError(ibin+1));
    ttbar_stat.push_back(h_ttbar1->GetBinError(ibin+1));
    singleTop_stat.push_back(h_singleTop1->GetBinError(ibin+1));

    zjets_stat.push_back(h_Zjets->GetBinError(ibin+1));
    vh_stat.push_back(h_vh->GetBinError(ibin+1));
    htt_stat.push_back(h_htt->GetBinError(ibin+1));
    ggf_stat.push_back(h_ggf->GetBinError(ibin+1));

    x_stat.push_back(h_Fakes->GetBinCenter(ibin+1));
    y_stat.push_back(h_Fakes->GetBinContent(ibin+1)+h_WW->GetBinContent(ibin+1)+h_NonWW->GetBinContent(ibin+1)+h_ttbar1->GetBinContent(ibin+1)+h_singleTop1->GetBinContent(ibin+1)+h_Zjets->GetBinContent(ibin+1)+h_vh->GetBinContent(ibin+1)+h_htt->GetBinContent(ibin+1)+h_ggf->GetBinContent(ibin+1));  
  }

  for(int istat=0; istat<fakes_stat.size(); istat++)
  {
    float stat = std::sqrt(std::pow(fakes_stat.at(istat),2)+std::pow(WW_stat.at(istat),2)+std::pow(NonWW_stat.at(istat),2)+std::pow(ttbar_stat.at(istat),2)+std::pow(singleTop_stat.at(istat),2)+std::pow(zjets_stat.at(istat),2)+std::pow(vh_stat.at(istat),2)+std::pow(htt_stat.at(istat),2)+std::pow(ggf_stat.at(istat),2));
    total_stat.push_back(stat);
  }
// ============================================================= //

 // if(unblind) h_data_stat = new TGraphAsymmErrors();
/*
  for(int istat = 0; istat<m_nbins; istat++)
  {
    if(unblind){
      h_data_stat->SetPoint(istat, h_data->GetBinCenter(istat+1), h_data->GetBinContent(istat+1));
      h_data_stat->SetPointError(istat, h_data->GetBinWidth(istat+1)/2, h_data->GetBinWidth(istat+1)/2, h_data->GetBinError(istat+1), h_data->GetBinError(istat+1));//std::sqrt(std::pow(h_data->GetBinError(istat+1),2)+std::pow(total_stat.at(istat),2)), std::sqrt(std::pow(h_data->GetBinError(istat+1),2)+std::pow(total_stat.at(istat),2)));
    }
    else break;
  }
*/
  // =============== add experimental systematics =================================== //
  std::string sys_path = "./exp_systematics/"+m_regionName+"/"+m_obsName+"_"+m_regionName+"_ExpSys.root";
  TFile *f_exp = new TFile(sys_path.c_str());
  size_t size1 = sizeof(v_sys_list)/sizeof(v_sys_list[0]);
  size_t size2 = sizeof(v_sys_MET)/sizeof(v_sys_MET[0]);
  size_t size3 = sizeof(v_sys_JER_MCSmear)/sizeof(v_sys_JER_MCSmear[0]);
 
  std::string all_sys[size1 + size2 + size3];
  std::copy(v_sys_list, v_sys_list + size1, all_sys);
  std::copy(v_sys_MET, v_sys_MET + size2, all_sys + size1);
  std::copy(v_sys_JER_MCSmear, v_sys_JER_MCSmear + size3, all_sys + size1 + size2);

  std::vector<std::string> histo_name_up;
  std::vector<std::string> histo_name_down;
  std::vector<TH1F*> h_exp_sys_up;
  std::vector<TH1F*> h_exp_sys_down;

  std::vector<std::string> name;

  std::vector<std::string> name_Zjets, name_diboson, name_Vgamma, name_top, name_Fakes, name_ggf, name_vh, name_htt;
  std::vector<std::string> name_Zjets_up, name_diboson_up, name_Vgamma_up, name_top_up, name_Fakes_up, name_ggf_up, name_vh_up, name_htt_up, name_Zjets_down, name_diboson_down, name_Vgamma_down, name_top_down, name_Fakes_down, name_ggf_down, name_vh_down, name_htt_down;
  std::vector<TH1F*> h_Zjets_up, h_diboson_up, h_Vgamma_up, h_top_up, h_Fakes_up, h_ggf_up, h_vh_up, h_htt_up, h_Zjets_down, h_diboson_down, h_Vgamma_down, h_top_down, h_Fakes_down, h_ggf_down, h_vh_down, h_htt_down;

  for(int i=0; i<(size1+size2+size3); i++)
  {
    name_Zjets.push_back(m_obsName + "_" + getSampleName("Zjets") + "_" + all_sys[i]);
    name_diboson.push_back(m_obsName + "_" + getSampleName("diboson1") + "_" + all_sys[i]);
    name_Vgamma.push_back(m_obsName + "_" + getSampleName("Vgamma") + "_" + all_sys[i]);
    name_top.push_back(m_obsName + "_" + getSampleName("top1") + "_" + all_sys[i]);
    name_ggf.push_back(m_obsName + "_" + getSampleName("ggf") + "_" + all_sys[i]);
    name_vh.push_back(m_obsName + "_" + getSampleName("vh") + "_" + all_sys[i]);
    name_htt.push_back(m_obsName + "_" + getSampleName("htt") + "_" + all_sys[i]);

  }
  //handle fakes
  for(int ifake=0; ifake<sizeof(v_sys_Fakes)/sizeof(v_sys_Fakes[0]); ifake++)
  {
    name_Fakes.push_back(m_obsName + "_" + getSampleName("Fakes") + "_" + v_sys_Fakes[ifake]);
  }

  for (size_t ifake = 0; ifake<name_Fakes.size(); ifake++)
  {
    name_Fakes_up.push_back(name_Fakes.at(ifake) + "__1up");
    name_Fakes_down.push_back(name_Fakes.at(ifake) + "__1down");
    h_Fakes_up.push_back((TH1F*)f_exp->Get(name_Fakes_up.at(ifake).c_str()));
    h_Fakes_down.push_back((TH1F*)f_exp->Get(name_Fakes_down.at(ifake).c_str()));
  }

  for(size_t i=0; i<name_Zjets.size(); i++){
    name_Zjets_up.push_back(name_Zjets.at(i) + "__1up");
    name_Zjets_down.push_back(name_Zjets.at(i) + "__1down");
    h_Zjets_up.push_back((TH1F*)f_exp->Get(name_Zjets_up.at(i).c_str()));
    h_Zjets_down.push_back((TH1F*)f_exp->Get(name_Zjets_down.at(i).c_str()));
  
    name_diboson_up.push_back(name_diboson.at(i) + "__1up");
    name_diboson_down.push_back(name_diboson.at(i) + "__1down");
    h_diboson_up.push_back((TH1F*)f_exp->Get(name_diboson_up.at(i).c_str()));
    h_diboson_down.push_back((TH1F*)f_exp->Get(name_diboson_down.at(i).c_str()));

    name_Vgamma_up.push_back(name_Vgamma.at(i) + "__1up");
    name_Vgamma_down.push_back(name_Vgamma.at(i) + "__1down");
    h_Vgamma_up.push_back((TH1F*)f_exp->Get(name_Vgamma_up.at(i).c_str()));
    h_Vgamma_down.push_back((TH1F*)f_exp->Get(name_Vgamma_down.at(i).c_str()));

    name_top_up.push_back(name_top.at(i) + "__1up");
    name_top_down.push_back(name_top.at(i) + "__1down");
    h_top_up.push_back((TH1F*)f_exp->Get(name_top_up.at(i).c_str()));
    h_top_down.push_back((TH1F*)f_exp->Get(name_top_down.at(i).c_str()));

    name_ggf_up.push_back(name_ggf.at(i) + "__1up");
    name_ggf_down.push_back(name_ggf.at(i) + "__1down");
    h_ggf_up.push_back((TH1F*)f_exp->Get(name_ggf_up.at(i).c_str()));
    h_ggf_down.push_back((TH1F*)f_exp->Get(name_ggf_down.at(i).c_str()));

    name_vh_up.push_back(name_vh.at(i) + "__1up");
    name_vh_down.push_back(name_vh.at(i) + "__1down");
    h_vh_up.push_back((TH1F*)f_exp->Get(name_vh_up.at(i).c_str()));
    h_vh_down.push_back((TH1F*)f_exp->Get(name_vh_down.at(i).c_str()));

    name_htt_up.push_back(name_htt.at(i) + "__1up");
    name_htt_down.push_back(name_htt.at(i) + "__1down");
    h_htt_up.push_back((TH1F*)f_exp->Get(name_htt_up.at(i).c_str()));
    h_htt_down.push_back((TH1F*)f_exp->Get(name_htt_down.at(i).c_str()));
  
  }

  std::vector<float> total_exp_sys_up, total_exp_sys_down, total_theo_up, total_theo_down;

  for(int ibin =0; ibin<m_nbins; ibin++){
    float total_sum_up = 0;
    float total_sum_down = 0;
    for(int i=0; i<name_Zjets.size(); i++){
      float total_up = std::pow(h_Zjets->GetBinContent(ibin+1) - h_Zjets_up.at(i)->GetBinContent(ibin+1),2) + std::pow(h_ttbar1->GetBinContent(ibin+1)+h_singleTop1->GetBinContent(ibin+1) - h_top_up.at(i)->GetBinContent(ibin+1),2) + std::pow(h_WW->GetBinContent(ibin+1) + h_NonWW->GetBinContent(ibin+1) - h_diboson_up.at(i)->GetBinContent(ibin+1) - h_Vgamma_up.at(i)->GetBinContent(ibin+1),2) + std::pow(h_ggf->GetBinContent(ibin+1) - h_ggf_up.at(i)->GetBinContent(ibin+1),2) + std::pow(h_vh->GetBinContent(ibin+1) - h_vh_up.at(i)->GetBinContent(ibin+1),2) + std::pow(h_htt->GetBinContent(ibin+1) - h_htt_up.at(i)->GetBinContent(ibin+1),2);
      if(i<sizeof(v_sys_Fakes)/sizeof(v_sys_Fakes[0])) total_up += (std::pow(h_Fakes->GetBinContent(ibin+1) - h_Fakes_up.at(i)->GetBinContent(ibin+1),2));
      total_sum_up +=total_up;
      float total_down = std::pow(h_Zjets->GetBinContent(ibin+1) - h_Zjets_down.at(i)->GetBinContent(ibin+1),2) + std::pow(h_ttbar1->GetBinContent(ibin+1)+h_singleTop1->GetBinContent(ibin+1) - h_top_down.at(i)->GetBinContent(ibin+1),2) + std::pow(h_WW->GetBinContent(ibin+1) + h_NonWW->GetBinContent(ibin+1) - h_diboson_down.at(i)->GetBinContent(ibin+1) - h_Vgamma_up.at(i)->GetBinContent(ibin+1),2) + std::pow(h_ggf->GetBinContent(ibin+1) - h_ggf_down.at(i)->GetBinContent(ibin+1),2) + std::pow(h_vh->GetBinContent(ibin+1) - h_vh_down.at(i)->GetBinContent(ibin+1),2) + std::pow(h_htt->GetBinContent(ibin+1) - h_htt_down.at(i)->GetBinContent(ibin+1),2);
      if(i<sizeof(v_sys_Fakes)/sizeof(v_sys_Fakes[0])) total_down += (std::pow(h_Fakes->GetBinContent(ibin+1) - h_Fakes_down.at(i)->GetBinContent(ibin+1),2));
      total_sum_down += total_down;
    }
      total_exp_sys_up.push_back(std::sqrt(total_sum_up));
      total_exp_sys_down.push_back(std::sqrt(total_sum_down));
  }
// ===================================================================== //

// ===================== add theory systematics ========================= //
  if(addTheo)
  {
    for(int ibin=0; ibin<m_nbins; ibin++)
    {
      float vbf_sum_theo_up = 0;
      float vbf_sum_theo_down = 0;
      for(int ivbf=0; ivbf<sizeof(v_theo_vbf)/sizeof(v_theo_vbf[0]); ivbf++)
      {
        TH1F* h_theo_up = getTheoryHisto("vbf", v_theo_vbf[ivbf], true);
        
        float total_up = std::pow(h_theo_up->GetBinContent(ibin+1), 2);
        vbf_sum_theo_up += total_up;

        TH1F* h_theo_down = getTheoryHisto("vbf", v_theo_vbf[ivbf], false);
        
        float total_down = std::pow(h_theo_down->GetBinContent(ibin+1), 2);
        vbf_sum_theo_down += total_down;
      }

      for(int iggf=0; iggf<sizeof(v_theo_ggf)/sizeof(v_theo_ggf[0]); iggf++)
      {
        TH1F* h_theo_up = getTheoryHisto("ggf", v_theo_ggf[iggf], true);
        float total_up = std::pow(h_theo_up->GetBinContent(ibin+1), 2);
        vbf_sum_theo_up += total_up;

        TH1F* h_theo_down = getTheoryHisto("ggf", v_theo_ggf[iggf], false);
        float total_down = std::pow(h_theo_down->GetBinContent(ibin+1), 2);
        vbf_sum_theo_down += total_down;
      }

      for(int itop=0; itop<sizeof(v_theo_top)/sizeof(v_theo_top[0]); itop++)
      {
        TH1F* h_theo_up = getTheoryHisto("top", v_theo_top[itop], true);
        float total_up = std::pow(h_theo_up->GetBinContent(ibin+1), 2);
        vbf_sum_theo_up += total_up;

        TH1F* h_theo_down = getTheoryHisto("top", v_theo_top[itop], false);
        float total_down = std::pow(h_theo_down->GetBinContent(ibin+1), 2);
        vbf_sum_theo_down += total_down;
      }

      for(int izjets=0; izjets<sizeof(v_theo_Zjets)/sizeof(v_theo_Zjets[0]); izjets++)
      {
        TH1F* h_theo_up = getTheoryHisto("Zjets", v_theo_Zjets[izjets], true);
        float total_up = std::pow(h_theo_up->GetBinContent(ibin+1), 2);
        vbf_sum_theo_up += total_up;

        TH1F* h_theo_down = getTheoryHisto("Zjets", v_theo_Zjets[izjets], false);
        float total_down = std::pow(h_theo_down->GetBinContent(ibin+1), 2);
        vbf_sum_theo_down += total_down;
      }

      for(int idiboson=0; idiboson<sizeof(v_theo_diboson)/sizeof(v_theo_diboson[0]); idiboson++)
      {
        TH1F* h_theo_up = getTheoryHisto("diboson", v_theo_diboson[idiboson], true);
        float total_up = std::pow(h_theo_up->GetBinContent(ibin+1), 2);
        vbf_sum_theo_up += total_up;

        TH1F* h_theo_down = getTheoryHisto("diboson", v_theo_diboson[idiboson], false);
        float total_down = std::pow(h_theo_down->GetBinContent(ibin+1), 2);
        vbf_sum_theo_down += total_down;
      }
      total_theo_up.push_back(std::sqrt(vbf_sum_theo_up));    
      total_theo_down.push_back(std::sqrt(vbf_sum_theo_down)); 
      std::cout<<"Bin-"<<ibin<<" "<<total_theo_up.at(ibin)<<" "<<total_theo_down.at(ibin)<<std::endl; 
    }
  }
// ====================================================================================================== //
  TGraphAsymmErrors* h_exp_sys_errors = new TGraphAsymmErrors();

  for(int isys = 0; isys<m_nbins; isys++)
  {
    h_exp_sys_errors->SetPoint(isys,x_stat.at(isys),y_stat.at(isys));
    if(addTheo) h_exp_sys_errors->SetPointError(isys, h_Fakes->GetBinWidth(isys)/2, h_Fakes->GetBinWidth(isys)/2, std::sqrt(std::pow(total_exp_sys_up.at(isys),2)+std::pow(total_stat.at(isys),2)+std::pow(total_theo_up.at(isys),2)), std::sqrt(std::pow(total_exp_sys_down.at(isys),2)+std::pow(total_stat.at(isys),2)+std::pow(total_theo_down.at(isys),2)));
    else h_exp_sys_errors->SetPointError(isys,h_Fakes->GetBinWidth(isys)/2,h_Fakes->GetBinWidth(isys)/2, std::sqrt(std::pow(total_exp_sys_up.at(isys),2)+std::pow(total_stat.at(isys),2)), std::sqrt(std::pow(total_exp_sys_down.at(isys),2)+std::pow(total_stat.at(isys),2))); 
  }

  if(m_regionName == "SR"){
    	h_stack->Add(h_vh); // vh
    	h_stack->Add(h_htt); // htt
    	h_stack->Add(h_ggf);  // ggF
    	h_stack->Add(h_NonWW); // nonWW + Vgamma
    	h_stack->Add(h_Fakes); // Fakes
    	h_stack->Add(h_singleTop1); // Single Top
    	h_stack->Add(h_Zjets); //Z+jets
    	h_stack->Add(h_WW); // WW +EWWW Madgraph
    	h_stack->Add(h_ttbar1); // ttbar
  }
  else{
    	h_stack->Add(h_vh);
    	h_stack->Add(h_htt);
    	h_stack->Add(h_ggf);
    	h_stack->Add(h_WW);
    	h_stack->Add(h_NonWW);
    	h_stack->Add(h_ttbar1);
    	h_stack->Add(h_singleTop1);
    	h_stack->Add(h_Zjets);
    	h_stack->Add(h_Fakes);
  }

  TCanvas *c = new TCanvas("atlas_square","Canvas title",0.,0.,600,600);

  if(unblind) h_data->SetMarkerStyle(8);//h_data_stat->SetMarkerStyle(8);

  if(unblind){
  pad1 = new TPad("pad1","pad1", 0, 0.35, 1., 1.);
 // pad1->SetLogy();
  pad1->SetBottomMargin(0.02);
  pad1->Draw();
  pad1->cd();
}
  
  h_stack->Draw("hist");
  h_vbf->Draw("hist same");
  
  h_exp_sys_errors->SetFillColor(kGray+2);
  h_exp_sys_errors->SetLineColor(kWhite);
  h_exp_sys_errors->SetFillStyle(3345);
  h_exp_sys_errors->Draw("e2 same");

  if(unblind){
   h_data->Draw("pe same");
  }

  h_stack->SetMinimum(m_yminimum);
  h_stack->SetMaximum(m_ymaximum);
 
  if(unblind) h_stack->GetXaxis()->SetRangeUser(m_xminimum,m_xmaximum);
  if(unblind) h_stack->GetXaxis()->SetLabelSize(0);

  if(!unblind){
  if(m_regionName=="SR") gPad->SetLogy();
  
  h_stack->GetXaxis()->SetTitle(xAxisTitle(observable).c_str());
  h_stack->GetXaxis()->SetTitleSize(.04);
  h_stack->GetXaxis()->SetLabelSize(.04);
  h_stack->GetYaxis()->SetLabelSize(.04);
  h_stack->GetYaxis()->SetTitleSize(.04);
  h_stack->GetYaxis()->SetTitleOffset(2.);
  if(m_regionName=="SR") h_stack->GetYaxis()->SetTitleOffset(1.5);
  }

  // y-axis label
  float binEvt = (h_stack->GetXaxis()->GetXmax() - h_stack->GetXaxis()->GetXmin())/m_nbins;
  char res[10];
  int digit = 0;
  if (binEvt<1) digit = 2;
  ftoa(binEvt, res, digit);
  std::string res_to_string = res;
  std::string unit=" GeV";
  if(m_obsName=="DPhill") unit = " rad";
  else if(m_obsName=="lep0_eta" || m_obsName=="lep1_eta" || m_obsName=="jet0_eta" || m_obsName=="jet1_eta" || m_obsName=="MT" || m_obsName=="DYll" || m_obsName=="DYjj" || m_obsName=="DPhijj" || m_obsName=="SignedDPhijj" || m_obsName=="costhetastar" || m_obsName=="sumOfCentralitiesL" || m_obsName=="bdt_vbf" || m_obsName=="bdt_TopWWAll" || m_obsName=="bdt_ggFCR1" || m_obsName=="bdt_ggFCR2" || m_obsName=="bdt_ggFCR3") unit="";
  std::string yTitle = "Events / "+ res_to_string + unit;
  if(m_obsName=="nJets") yTitle = "Events";
  h_stack->GetYaxis()->SetTitle(yTitle.c_str());

  if(unblind) legend = new TLegend(0.55,0.55,0.92,0.9);
  else legend = new TLegend(0.55,0.65,0.92,0.9); 
  legend->SetBorderSize(0);
  legend->SetFillStyle(0);
  legend->SetTextSize(0.);
  legend->SetNColumns(2);
 
  if(unblind) legend->AddEntry(h_data, "#bf{Data}", "pe");
  legend->AddEntry(h_exp_sys_errors, "#bf{Uncertainty}", "f");
  legend->AddEntry(h_vbf,"#bf{H_{VBF}}", "f");
  legend->AddEntry(h_ggf, "#bf{H_{ggF}}", "f");
  legend->AddEntry(h_vh, "#bf{H_{VH}}", "f");
  legend->AddEntry(h_htt, "#bf{H#rightarrow#tau#tau}", "f");
  legend->AddEntry(h_WW, "#bf{WW}", "f");
  legend->AddEntry(h_NonWW, "#bf{Other VV}", "f");
  legend->AddEntry(h_ttbar1, "#bf{t#bar{t}}","f");
  legend->AddEntry(h_singleTop1, "#bf{Single Top}","f");
  legend->AddEntry(h_Zjets, "#bf{Z/#gamma^{*}}", "f");
  legend->AddEntry(h_Fakes, "#bf{Mis-Id}", "f");
  
  legend->Draw();

  auto legAtlas = new TLegend(0.075,0.7,0.52,0.92);
  legAtlas->SetBorderSize(0);
  legAtlas->SetFillStyle(0);
  legAtlas->SetTextSize(0.);
  legAtlas->AddEntry((TObject*)0, "#it{#scale[1.5]{ATLAS}} #font[42]{#scale[1.5]{Internal}}", "");
  legAtlas->AddEntry((TObject*)0, "#bf{#sqrt{#scale[1.]{s}} #scale[1.]{= 13 TeV,} #scale[1.]{#int} #scale[1.]{Ldt = 139 fb^{-1}}}", "");
  std::string regionLabel = "#bf{e#mu + #mue channel}";//"#bf{"+region+"}";
  legAtlas->AddEntry((TObject*)0, regionLabel.c_str(),"");

  legAtlas->Draw();

  if(unblind){
  c->cd();

  
  pad2 = new TPad("pad2", "pad2", 0, 0., 1, 0.35);
  pad2->SetTopMargin(0.03);
  pad2->SetBottomMargin(.4);
  pad2->Draw();
  pad2->cd();
  gPad->SetGridy(1);
  
  TH1F* h_ratio = (TH1F*) h_data->Clone("ratio");
  TH1F* h_all_bkg = (TH1F*) h_Fakes->Clone("all_bkg");
  h_all_bkg->Add(h_Zjets);
  h_all_bkg->Add(h_WW);
  h_all_bkg->Add(h_NonWW);
  h_all_bkg->Add(h_ttbar1);
  h_all_bkg->Add(h_singleTop1);
  h_all_bkg->Add(h_vh);
  h_all_bkg->Add(h_htt);
  h_all_bkg->Add(h_ggf);
//  TH1F* h_all_bkg_signal = (TH1F*) h_all_bkg->Clone("all_bkg_signal");
//  h_all_bkg_signal->Add(h_vbf);
 // TH1F* h_ratio2 = (TH1F*) h_data->Clone("ratio2");
 // h_ratio2->Divide(h_all_bkg_signal);*/
  h_ratio->Divide(h_all_bkg);

  TGraphAsymmErrors* h_ratio_unc = new TGraphAsymmErrors();
  
  for(int i=0; i<m_nbins; i++){
    h_ratio_unc->SetPoint(i,h_ratio->GetBinCenter(i+1),1);
    h_ratio_unc->SetPointError(i,h_ratio->GetBinWidth(i+1)/2, h_ratio->GetBinWidth(i+1)/2, total_exp_sys_up.at(i)/h_data->GetBinContent(i+1), total_exp_sys_down.at(i)/h_data->GetBinContent(i+1));
  }

  h_ratio_unc->SetFillColor(kGray+2);  
  h_ratio_unc->SetFillStyle(3345);
  h_ratio->Draw("pe");

  TLine *l=new TLine(pad1->GetUxmin(),1.0,m_xmaximum,1.0);
  l->SetLineColor(kRed);
  l->Draw("same");
  h_ratio_unc->Draw("e2 same");
  h_ratio->Draw("pe same");

  h_ratio->GetXaxis()->SetTitle(xAxisTitle(observable).c_str());
  h_ratio->GetXaxis()->SetTitleSize(.09);
 // h_ratio->GetXaxis()->SetTitleOffset(2.5);
  h_ratio->GetXaxis()->SetLabelSize(.09);
  h_ratio->GetYaxis()->SetNdivisions(508);
  h_ratio->GetYaxis()->SetLabelSize(.09);
  h_ratio->GetYaxis()->CenterTitle(true);
  h_ratio->GetYaxis()->SetTitleSize(.09);
//  h_stack->GetYaxis()->SetLabelSize(.1);
//  h_stack->GetYaxis()->SetTitleSize(.04);
//  h_stack->GetYaxis()->SetLabelSize(.04);
  h_ratio->GetYaxis()->SetTitleOffset(.7);
  h_ratio->GetYaxis()->SetTitle("Data / Pred.");
 // h_stack->GetYaxis()->SetTitleOffset(.3);
  h_ratio->GetXaxis()->SetRangeUser(m_xminimum,m_xmaximum);
  h_ratio->GetYaxis()->SetRangeUser(m_y_ratio_min,m_y_ratio_max);
}

  std::string save_name = "./plots/"+region+"_"+observable+".pdf";
  c->SaveAs(save_name.c_str());


}

void plotting::PlotsforPaper(std::string region, std::string observable, bool unblind)
{
  std::cout<<"Preparing the plot for the paper.."<<std::endl;
}


plotting::plotting(std::string region, std::string observable, bool unblind, bool forPaper, bool setAxesLimits, bool addTheo, bool lxplus=true)
{
  gROOT->SetBatch(kTRUE);
  SetAtlasStyle();
  
  clock_t tStart = clock();
  auto t_start = std::chrono::high_resolution_clock::now();

  setObsName(observable);
  setRegionName(region);

  setBins(forPaper);

  if(setAxesLimits)
  {
    float y_maximum, x_minimum, x_maximum;
    std::cout<<"Set Y-axis maximum ";
    std::cin>>y_maximum;
    std::cout<<"Set X-axis minimum ";
    std::cin>>x_minimum;
    std::cout<<"Set X-axis maximum ";
    std::cin>>x_maximum;
    
    if (unblind)
    {
      float y_ratio_min, y_ratio_max;
      std::cout<<"==== Limits for the bottom panel ====\n";
      std::cout<<"y-axis min value \n";
      std::cin>>y_ratio_min;
      std::cout<<"y-axis max value \n";
      std::cin>>y_ratio_max;

      setYminRatio(y_ratio_min);
      setYmaxRatio(y_ratio_max);

    }
    setYMax(y_maximum);
    setXMin(x_minimum);
    setXMax(x_maximum);
  }
  else
  {
    setYaxisRanges();
    setXaxisRanges();
  }

  if(forPaper) PlotsforPaper(m_regionName, m_obsName, unblind);
  else PlotsforNote(m_regionName, m_obsName, unblind, addTheo, lxplus);

  clock_t tEnd = clock();
  auto t_end = std::chrono::high_resolution_clock::now();

  std::cout<<"Time taken: "<<(double)(tEnd - tStart)/CLOCKS_PER_SEC<<"s\n";
  std::cout<<"Wall clock time passed: "<<std::chrono::duration<double, std::milli>(t_end-t_start).count()<<"ms\n ";

}
