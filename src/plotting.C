
#include "Style/AtlasStyle.C"
#include "plotting.h"

std::string v_theo_vbf[5] =  	{"theo_vbf_shower", "theo_vbf_alphas", "theo_vbf_scale", "theo_vbf_pdf4lhc", "theo_vbf_generator"}; 

std::string v_theo_ggf[11] =  	{"theo_ggF_shower", "theo_ggF_alphas", "theo_ggF_pdf4lhc", "theo_ggF_qcd_wg1_mu", "theo_ggF_qcd_wg1_res", "theo_ggF_qcd_wg1_mig01", "theo_ggF_qcd_wg1_mig12", "theo_ggF_qcd_wg1_vbf2j", "theo_ggF_qcd_wg1_vbf3j", "theo_ggF_qcd_wg1_qm_t", "theo_ggF_qcd_wg1_pTH" };

std::string v_theo_top[6] =     {"theo_ttbar_shower", "theo_ttbar_scale", "theo_ttbar_pdf", "theo_ttbar_matching", "theo_ttbar_isr", "theo_ttbar_fsr" };

std::string v_theo_Zjets[4] =   {"theo_ztautau_alphas", "theo_ztautau_scale", "theo_ztautau_pdf", "theo_ztautau_generator"};

std::string v_theo_diboson[5] = {"theo_ww_shower",  "theo_ww_alphas", "theo_ww_scale", "theo_ww_pdf", "theo_ww_CKKW"};

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
  h->Sumw2();

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
  h->Sumw2();

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

void plotting::getTheoryVariations(std::string sample, std::string theo_sys, int ibin, float &nom_content, float &var_up, float &var_down)
{
  std::string theo_filename =  "/usatlas/u/sagar/usatlaswork/scripts/CharaStackPlotsHists/StackPlots_22Feb2022/"+ sample + "_histos_2jets.root";//"/usatlas/u/sagar/usatlaswork/scripts/CharaStackPlotsHists/StackPlots_UnfBin_FullSR_11Mar2022/" + sample + "_histos_SR12.root";//"/usatlas/u/sagar/usatlaswork/scripts/CharaStackPlotsHists/StackPlots_SR12/"+ sample + "_histos_SR12.root";//"/usatlas/u/sagar/usatlaswork/scripts/CharaStackPlotsHists/StackPlots_SR12/"+sample+"_histos_SR12.root";//"/usatlas/u/sagar/usatlaswork/scripts/CharaStackPlotsHists/StackPlots_1Feb2022/"+ sample + "_histos_2jets.root";//"../theo_systematics/" + sample + "_theory_2jets.root"; //for submission one dir back
  if(m_regionName=="ggFCR3") theo_filename = "/usatlas/u/sagar/usatlaswork/scripts/CharaStackPlotsHists/StackPlots_1Feb2022/"+ sample + "_histos_1jets.root";//"../theo_systematics/" + sample + "_theory_1jets.root";
  TFile* f_theo_file = new TFile(theo_filename.c_str(), "READ");
  std::string name;
  if(strstr(m_regionName.c_str(),"SR1")) name = "SR1";
  else if(strstr(m_regionName.c_str(),"SR2")) name = "SR2";
  else name = m_regionName;
  std::string theo_nom = sample + "_" + theo_sys + "__Nom_" + name + "_" + m_obsName;
  std::string theo_var_up = sample + "_" + theo_sys + "__1up_" + name + "_" + m_obsName;
  std::string theo_var_down = sample + "_" + theo_sys + "__1down_" + name + "_" + m_obsName;
  TH1F* h_theo_nom = (TH1F*)f_theo_file->Get(theo_nom.c_str());
  TH1F* h_theo_var_up = (TH1F*)f_theo_file->Get(theo_var_up.c_str());
  TH1F* h_theo_var_down = (TH1F*)f_theo_file->Get(theo_var_down.c_str());

  nom_content = h_theo_nom->GetBinContent(ibin+1);

  var_up = h_theo_var_up->GetBinContent(ibin+1);
  var_down = h_theo_var_down->GetBinContent(ibin+1);

}

void plotting::PlotsforNote(std::string region, std::string observable, bool unblind, bool addTheo)
{

  std::cout<<"Preparing the plot for the supporting note.."<<std::endl;

  std::vector<float> v_ttbar = {410472};
  std::vector<float> v_singleTop = {410648, 410649};

  h_Fakes = getNominalHisto("Fakes");
  h_WW = getNominalHisto("diboson1");
  h_NonWW = getNominalHisto("diboson2");
  h_WWEW = getNominalHisto("WWEW");
  h_Zjets = getNominalHisto("Zjets");
  h_Vgamma = getNominalHisto("Vgamma");
  h_ttbar1 = getNominalHisto("top1", v_ttbar);
  h_ttbar2 = getNominalHisto("top2", v_ttbar);
  h_singleTop1 = getNominalHisto("top1", v_singleTop);
  h_singleTop2 = getNominalHisto("top2", v_singleTop);
  h_vbf = getNominalHisto("vbf");
  h_ggf = getNominalHisto("ggf");
  h_vh = getNominalHisto("vh");
  h_htt = getNominalHisto("htt");
  
  if(unblind) h_data = getNominalHisto("data");
  
  THStack* h_stack = new THStack("h_stack","");

/*
  for(int ibin=0; ibin<m_nbins; ibin++)
  {
    std::cout<<"Bin-"<<ibin+1<<" "<<h_vbf->GetBinContent(ibin+1)+h_vh->GetBinContent(ibin+1)+h_htt->GetBinContent(ibin+1)+h_Fakes->GetBinContent(ibin+1)+h_Vgamma->GetBinContent(ibin+1)+h_ttbar1->GetBinContent(ibin+1)+h_ttbar2->GetBinContent(ibin+1)+h_singleTop1->GetBinContent(ibin+1)+h_singleTop2->GetBinContent(ibin+1)+h_WW->GetBinContent(ibin+1)+h_WWEW->GetBinContent(ibin+1)+h_NonWW->GetBinContent(ibin+1)+h_Zjets->GetBinContent(ibin+1)+h_ggf->GetBinContent(ibin+1)<<" total bkg"<<std::endl;
    std::cout<<"Bin-"<<ibin+1<<" "<<h_vbf->GetBinContent(ibin+1)<<" vbf"<<std::endl;
    std::cout<<"Bin-"<<ibin+1<<" "<<h_vh->GetBinContent(ibin+1)<<" vh"<<std::endl;
    std::cout<<"Bin-"<<ibin+1<<" "<<h_htt->GetBinContent(ibin+1)<<" htt"<<std::endl;
    std::cout<<"Bin-"<<ibin+1<<" "<<h_Fakes->GetBinContent(ibin+1)<<" Fakes"<<std::endl;
    std::cout<<"Bin-"<<ibin+1<<" "<<h_Vgamma->GetBinContent(ibin+1)<<" Vgamma"<<std::endl;
    std::cout<<"Bin-"<<ibin+1<<" "<<h_ttbar1->GetBinContent(ibin+1)+h_ttbar2->GetBinContent(ibin+1)+h_singleTop1->GetBinContent(ibin+1)+h_singleTop2->GetBinContent(ibin+1)<<" top"<<std::endl;
    std::cout<<"Bin-"<<ibin+1<<" "<<h_WW->GetBinContent(ibin+1)+h_WWEW->GetBinContent(ibin+1)+h_NonWW->GetBinContent(ibin+1)<<" diboson"<<std::endl;
    std::cout<<"Bin-"<<ibin+1<<" "<<h_Zjets->GetBinContent(ibin+1)<<" Zjets"<<std::endl;
    std::cout<<"Bin-"<<ibin+1<<" "<<h_ggf->GetBinContent(ibin+1)<<" ggf"<<std::endl;

  }
*/

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
  h_vbf->SetLineColor(kBlack);
  h_vbf->SetFillColor(kRed+1);
  h_ggf->SetFillColor(kBlue);
  h_ggf->SetLineColor(kBlack);
  h_Zjets->SetFillColor(kGreen+2);
  h_Zjets->SetLineColor(kBlack);
  h_vh->SetFillColor(kViolet-8);
  h_vh->SetLineColor(kBlack);
  h_htt->SetFillColor(kOrange+3);
  h_htt->SetLineColor(kBlack);

  h_vbf->SetLineWidth(1);
  h_WW->SetLineWidth(1);
  h_Fakes->SetLineWidth(1);
  h_NonWW->SetLineWidth(1);
  h_ttbar1->SetLineWidth(1);
  h_singleTop1->SetLineWidth(1);
  h_Zjets->SetLineWidth(1);
  h_ggf->SetLineWidth(1);
  h_htt->SetLineWidth(1);
  h_vh->SetLineWidth(1);

  std::vector<float> fakes_stat, WW_stat, NonWW_stat, ttbar_stat, singleTop_stat, zjets_stat, vh_stat, htt_stat, ggf_stat, vbf_stat, total_stat, x_stat, y_stat;
 
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
    vbf_stat.push_back(h_vbf->GetBinError(ibin+1));

    x_stat.push_back(h_Fakes->GetBinCenter(ibin+1));
    y_stat.push_back(h_Fakes->GetBinContent(ibin+1)+h_WW->GetBinContent(ibin+1)+h_NonWW->GetBinContent(ibin+1)+h_ttbar1->GetBinContent(ibin+1)+h_singleTop1->GetBinContent(ibin+1)+h_Zjets->GetBinContent(ibin+1)+h_vh->GetBinContent(ibin+1)+h_htt->GetBinContent(ibin+1)+h_ggf->GetBinContent(ibin+1)+h_vbf->GetBinContent(ibin+1));  
  }

  for(int istat=0; istat<m_nbins; istat++)
  {
      float stat = std::pow(fakes_stat.at(istat),2)+std::pow(WW_stat.at(istat),2)+std::pow(NonWW_stat.at(istat),2)+std::pow(ttbar_stat.at(istat),2)+std::pow(singleTop_stat.at(istat),2)+std::pow(zjets_stat.at(istat),2)+std::pow(vh_stat.at(istat),2)+std::pow(htt_stat.at(istat),2)+std::pow(ggf_stat.at(istat),2);
      total_stat.push_back(stat);
  }

// ============================================================= //


// =============== add experimental systematics =================================== //
  std::string sys_path = "../exp_systematics/"+m_regionName+"/"+m_obsName+"_"+m_regionName+"_ExpSys.root"; //for submission one dir back
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

  std::vector<std::string> name_Zjets, name_diboson, name_Vgamma, name_top, name_Fakes, name_ggf, name_vh, name_htt, name_vbf;
  std::vector<std::string> name_Zjets_up, name_diboson_up, name_Vgamma_up, name_top_up, name_Fakes_up, name_ggf_up, name_vh_up, name_htt_up, name_vbf_up, name_Zjets_down, name_diboson_down, name_Vgamma_down, name_top_down, name_Fakes_down, name_ggf_down, name_vh_down, name_htt_down, name_vbf_down;
  std::vector<TH1F*> h_Zjets_up, h_diboson_up, h_Vgamma_up, h_top_up, h_Fakes_up, h_ggf_up, h_vh_up, h_htt_up, h_vbf_up, h_Zjets_down, h_diboson_down, h_Vgamma_down, h_top_down, h_Fakes_down, h_ggf_down, h_vh_down, h_htt_down, h_vbf_down;

  for(int i=0; i<(size1+size2+size3); i++)
  {
    name_Zjets.push_back(m_obsName + "_" + getSampleName("Zjets") + "_" + all_sys[i]);
    name_diboson.push_back(m_obsName + "_" + getSampleName("diboson1") + "_" + all_sys[i]);
    name_Vgamma.push_back(m_obsName + "_" + getSampleName("Vgamma") + "_" + all_sys[i]);
    name_top.push_back(m_obsName + "_" + getSampleName("top1") + "_" + all_sys[i]);
    name_ggf.push_back(m_obsName + "_" + getSampleName("ggf") + "_" + all_sys[i]);
    name_vh.push_back(m_obsName + "_" + getSampleName("vh") + "_" + all_sys[i]);
    name_htt.push_back(m_obsName + "_" + getSampleName("htt") + "_" + all_sys[i]);
    name_vbf.push_back(m_obsName + "_" + getSampleName("vbf") + "_" + all_sys[i]);

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

    name_vbf_up.push_back(name_vbf.at(i) + "__1up");
    name_vbf_down.push_back(name_vbf.at(i) + "__1down");
    h_vbf_up.push_back((TH1F*)f_exp->Get(name_vbf_up.at(i).c_str()));
    h_vbf_down.push_back((TH1F*)f_exp->Get(name_vbf_down.at(i).c_str()));
  
  }

  std::vector<float> total_exp_sys_up, total_exp_sys_down;

  for(int ibin =0; ibin<m_nbins; ibin++){
    float total_sum_up = 0;
    float total_sum_down = 0;
    float total_sum_nom = 0;

    float diff_up = 0 ;
    float diff_down = 0;
    
    for(int i=0; i<name_Zjets.size(); i++){
    	float total_sum_nom = h_Zjets->GetBinContent(ibin+1) +  h_ttbar1->GetBinContent(ibin+1)+ h_singleTop1->GetBinContent(ibin+1) + h_WW->GetBinContent(ibin+1) + h_NonWW->GetBinContent(ibin+1) + h_ggf->GetBinContent(ibin+1)	+ h_vh->GetBinContent(ibin+1) + h_htt->GetBinContent(ibin+1) + h_vbf->GetBinContent(ibin+1);
    	float total_sum_up = h_Zjets_up.at(i)->GetBinContent(ibin+1) +  h_top_up.at(i)->GetBinContent(ibin+1) + h_diboson_up.at(i)->GetBinContent(ibin+1) + h_Vgamma_up.at(i)->GetBinContent(ibin+1) + h_ggf_up.at(i)->GetBinContent(ibin+1)	+ h_vh_up.at(i)->GetBinContent(ibin+1) + h_htt_up.at(i)->GetBinContent(ibin+1) + h_vbf_up.at(i)->GetBinContent(ibin+1);
    	float total_sum_down = h_Zjets_down.at(i)->GetBinContent(ibin+1) +  h_top_down.at(i)->GetBinContent(ibin+1) + h_diboson_down.at(i)->GetBinContent(ibin+1) + h_Vgamma_down.at(i)->GetBinContent(ibin+1) + h_ggf_down.at(i)->GetBinContent(ibin+1)	+ h_vh_down.at(i)->GetBinContent(ibin+1) + h_htt_down.at(i)->GetBinContent(ibin+1) + h_vbf_down.at(i)->GetBinContent(ibin+1);

      	diff_up += std::pow(total_sum_nom - total_sum_up,2);
      	diff_down += std::pow(total_sum_nom - total_sum_down,2);
    }
    for(int j=0; j<name_Fakes.size(); j++) {
    	float total_sum_nom = h_Fakes->GetBinContent(ibin+1);
    	float total_sum_up = h_Fakes_up.at(j)->GetBinContent(ibin+1);
    	float total_sum_down = h_Fakes_down.at(j)->GetBinContent(ibin+1);

    	diff_up += std::pow(total_sum_nom - total_sum_up , 2);
    	diff_down += std::pow(total_sum_nom - total_sum_down , 2);
    }

      total_exp_sys_up.push_back(diff_up);
      total_exp_sys_down.push_back(diff_down);
  }

// ===================================================================== //

// ===================== add theory systematics ========================= //
std::vector<float>  total_theo_up, total_theo_down;

  if(addTheo)
  {
  	float nom_content = 0; 
    float var_up = 0;
    float var_down = 0;
    
  	for(int ibin=0; ibin<m_nbins; ibin++)
    {
      float theo_total_nom = 0;
      float theo_total_up = 0;
      float theo_total_down = 0;
    
      float diff_up = 0;
      float diff_down = 0;

      // add vbf theo variations
      for(int ivbf=0; ivbf<sizeof(v_theo_vbf)/sizeof(v_theo_vbf[0]); ivbf++)
      {
      	getTheoryVariations("vbf", v_theo_vbf[ivbf], ibin, nom_content, var_up, var_down);
      	diff_up += std::pow(nom_content - var_up, 2);
      	diff_down += std::pow(nom_content - var_down, 2);
      }
      // add ggf theo variations
      for(int iggf=0; iggf<sizeof(v_theo_ggf)/sizeof(v_theo_ggf[0]); iggf++)
      {
      	getTheoryVariations("ggf", v_theo_ggf[iggf], ibin, nom_content, var_up, var_down);
      	diff_up += std::pow(nom_content - var_up, 2);
      	diff_down += std::pow(nom_content - var_down, 2);
      }

      // add top theo variations
      for(int itop=0; itop<sizeof(v_theo_top)/sizeof(v_theo_top[0]); itop++)
      {
      	getTheoryVariations("top", v_theo_top[itop], ibin, nom_content, var_up, var_down);
      	diff_up += std::pow(nom_content - var_up, 2);
        diff_down += std::pow(nom_content - var_down, 2);
      }

      // add Zjets variations
      for(int izjets=0; izjets<sizeof(v_theo_Zjets)/sizeof(v_theo_Zjets[0]); izjets++)
      {
      	getTheoryVariations("Zjets0", v_theo_Zjets[izjets], ibin, nom_content, var_up, var_down);
      	diff_up += std::pow(nom_content - var_up, 2);
      	diff_down += std::pow(nom_content - var_down, 2);
      }

      // add diboson variations
      for(int idib=0; idib<sizeof(v_theo_diboson)/sizeof(v_theo_diboson[0]); idib++)
      {
      	getTheoryVariations("diboson", v_theo_diboson[idib], ibin, nom_content, var_up, var_down);
      	diff_up += std::pow(nom_content - var_up, 2);
      	diff_down += std::pow(nom_content - var_down, 2);
      }

      total_theo_up.push_back(diff_up);    
      total_theo_down.push_back(diff_down); 
    }
  }
// ====================================================================================================== //
  
  TGraphAsymmErrors* h_exp_sys_errors = new TGraphAsymmErrors();

  for(int isys = 0; isys<m_nbins; isys++)
  {
    h_exp_sys_errors->SetPoint(isys,x_stat.at(isys),y_stat.at(isys));
    if(addTheo) h_exp_sys_errors->SetPointError(isys, h_Fakes->GetBinWidth(isys+1)/2, h_Fakes->GetBinWidth(isys+1)/2, std::sqrt( total_exp_sys_up.at(isys) + total_stat.at(isys) + total_theo_up.at(isys) ), std::sqrt( total_exp_sys_down.at(isys) + total_stat.at(isys) + total_theo_down.at(isys)) );
    else h_exp_sys_errors->SetPointError(isys,h_Fakes->GetBinWidth(isys+1)/2,h_Fakes->GetBinWidth(isys+1)/2, std::sqrt(total_exp_sys_up.at(isys) + total_stat.at(isys)) , std::sqrt( total_exp_sys_down.at(isys) + total_stat.at(isys))); 
  }

  if(strstr(m_regionName.c_str(),"SR")) {
    	h_stack->Add(h_vh); // vh
    	h_stack->Add(h_htt); // htt
    	h_stack->Add(h_ggf);  // ggF
    	h_stack->Add(h_NonWW); // nonWW + Vgamma
    	h_stack->Add(h_Fakes); // Fakes
    	h_stack->Add(h_singleTop1); // Single Top
    	h_stack->Add(h_Zjets); //Z+jets
    	h_stack->Add(h_WW); // WW +EWWW Madgraph
    	h_stack->Add(h_ttbar1); // ttbar
      h_stack->Add(h_vbf); //vbf
  }
  else{
      h_stack->Add(h_vbf);
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

  if(unblind) h_data->SetMarkerStyle(8);
  pad1 = new TPad("pad1","pad1", 0, 0.35, 1., 1.);
  //if(strstr(m_regionName.c_str(),"SR")) { pad1->SetBottomMargin(0.); pad1->SetLogy();}// logY 
  //else 
    pad1->SetBottomMargin(0.02);

  pad1->Draw();
  pad1->cd();


  h_stack->Draw("hist");
//  h_vbf->Draw("hist same");
  
  h_exp_sys_errors->SetFillColor(kGray+2);
  h_exp_sys_errors->SetLineColor(kWhite);
  h_exp_sys_errors->SetFillStyle(3345);
  h_exp_sys_errors->Draw("e2 same");

  if(unblind){
   h_data->Draw("pe same");
  }


  h_stack->SetMinimum(m_yminimum);
  h_stack->SetMaximum(m_ymaximum);
 
  h_stack->GetXaxis()->SetRangeUser(m_xminimum,m_xmaximum);
  h_stack->GetXaxis()->SetLabelSize(0);


  if(!unblind){
  //if(strstr(m_regionName.c_str(),"SR")) pad1->SetLogy(); 
  
  h_stack->GetXaxis()->SetTitle(xAxisTitle(observable).c_str());
  h_stack->GetXaxis()->SetTitleSize(.04);
  h_stack->GetXaxis()->SetLabelSize(.04);
  h_stack->GetYaxis()->SetLabelSize(.04);
  h_stack->GetYaxis()->SetTitleSize(.04);
  h_stack->GetYaxis()->SetTitleOffset(2.);
  h_stack->GetXaxis()->SetTitleOffset(2.);
  if(strstr(m_regionName.c_str(),"SR")) h_stack->GetYaxis()->SetTitleOffset(1.5);
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
  if(m_obsName=="nJets" || binEvt==1 || strstr(m_regionName.c_str(),"SR1") || strstr(m_regionName.c_str(),"SR2")) yTitle = "Events";
  h_stack->GetYaxis()->SetTitle(yTitle.c_str());

  legend = new TLegend(0.55,0.55,0.92,0.9);
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
  std::string reg = region;
  if(strstr(m_regionName.c_str(),"ggFCR3")) reg = "ggF-VR3";
  if(strstr(m_regionName.c_str(),"ggFCR2")) reg = "ggF-VR2";
  if(strstr(m_regionName.c_str(),"ggFCR1")) reg = "ggF-CR1";
  if(strstr(m_regionName.c_str(),"DYCR")) reg = "Drell-Yan CR";
  if(strstr(m_regionName.c_str(),"WWCR")) reg = "WW VR";
  if(strstr(m_regionName.c_str(),"TopCR")) reg = "Top VR";

  std::string regionLabel = "#bf{"+reg+"}";//"#bf{e#mu + #mue channel}";//"#bf{"+region+"}";
  legAtlas->AddEntry((TObject*)0, regionLabel.c_str(),"");

  legAtlas->Draw();

  if(unblind){
  c->cd();

  //if(strstr(m_obsName.c_str(),"Mll")) pad1->SetLogx();
  pad2 = new TPad("pad2", "pad2", 0, 0., 1, 0.35);
  pad2->SetTopMargin(0.03);
  pad2->SetBottomMargin(.4);
  pad2->Draw();
  pad2->cd();
  gPad->SetGridy(1);
  //if(strstr(m_obsName.c_str(),"Mll")) pad2->SetLogx();

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
  h_all_bkg->Add(h_vbf);


//  TH1F* h_all_bkg_signal = (TH1F*) h_all_bkg->Clone("all_bkg_signal");
//  h_all_bkg_signal->Add(h_vbf);
 // TH1F* h_ratio2 = (TH1F*) h_data->Clone("ratio2");
 // h_ratio2->Divide(h_all_bkg_signal);*/
  h_ratio->Divide(h_all_bkg);

  TGraphAsymmErrors* h_ratio_unc = new TGraphAsymmErrors();
  
  for(int i=0; i<m_nbins; i++){
    h_ratio_unc->SetPoint(i,h_ratio->GetBinCenter(i+1),1);
    if(addTheo) h_ratio_unc->SetPointError(i,h_ratio->GetBinWidth(i+1)/2, h_ratio->GetBinWidth(i+1)/2, std::sqrt( total_exp_sys_up.at(i) + total_theo_up.at(i) + total_stat.at(i) )/h_all_bkg->GetBinContent(i+1), std::sqrt( total_exp_sys_down.at(i) + total_theo_down.at(i) + total_stat.at(i) )/h_all_bkg->GetBinContent(i+1));
    else h_ratio_unc->SetPointError(i,h_ratio->GetBinWidth(i+1)/2, h_ratio->GetBinWidth(i+1)/2, std::sqrt((total_exp_sys_up.at(i) + total_stat.at(i)))/h_all_bkg->GetBinContent(i+1), std::sqrt((total_exp_sys_down.at(i) + total_stat.at(i)))/h_all_bkg->GetBinContent(i+1));
  }

  h_ratio_unc->SetFillColor(kGray+2);  
  h_ratio_unc->SetFillStyle(3345);
  h_ratio->Draw("pe");

  TLine *l=new TLine(m_xminimum,1.0,m_xmaximum,1.0);
  l->SetLineColor(kRed);
  l->Draw("same");
  h_ratio_unc->Draw("e2 same");
  h_ratio->Draw("pe same");

  h_ratio->GetXaxis()->SetTitle(xAxisTitle(observable).c_str());
  h_ratio->GetXaxis()->SetTitleSize(.09);
  h_ratio->GetXaxis()->SetLabelSize(.09);
  h_ratio->GetYaxis()->SetNdivisions(508);
  h_ratio->GetYaxis()->SetLabelSize(.09);
  h_ratio->GetYaxis()->CenterTitle(true);
  h_ratio->GetYaxis()->SetTitleSize(.09);
  h_ratio->GetYaxis()->SetTitleOffset(.7);
  h_ratio->GetYaxis()->SetTitle("Data / Pred.");
  h_ratio->GetXaxis()->SetRangeUser(m_xminimum,m_xmaximum);
  h_ratio->GetYaxis()->SetRangeUser(m_y_ratio_min,m_y_ratio_max);
}

if(!unblind){
  c->cd();

  
  pad2 = new TPad("pad2", "pad2", 0, 0., 1, 0.35);
  pad2->SetTopMargin(0.03); 
  pad2->SetBottomMargin(.4); 
  pad2->Draw();
  pad2->cd();
  gPad->SetGridy(1);
  
  TH1F* h_all_bkg = (TH1F*) h_Fakes->Clone("all_bkg");
  h_all_bkg->Add(h_Zjets);
  h_all_bkg->Add(h_WW);
  h_all_bkg->Add(h_NonWW);
  h_all_bkg->Add(h_ttbar1);
  h_all_bkg->Add(h_singleTop1);
  h_all_bkg->Add(h_vh);
  h_all_bkg->Add(h_htt);
  h_all_bkg->Add(h_ggf);
  h_all_bkg->Add(h_vbf);


  TGraphAsymmErrors* h_ratio_unc = new TGraphAsymmErrors();
  std::cout<<"check tot bkg bin content: \n";
  for(int i=0; i<m_nbins; i++){
    h_ratio_unc->SetPoint(i,h_all_bkg->GetBinCenter(i+1),1);
    if(addTheo) h_ratio_unc->SetPointError(i,h_all_bkg->GetBinWidth(i+1)/2, h_all_bkg->GetBinWidth(i+1)/2, std::sqrt( total_exp_sys_up.at(i) + total_theo_up.at(i) + total_stat.at(i) )/h_all_bkg->GetBinContent(i+1), std::sqrt( total_exp_sys_down.at(i) + total_theo_down.at(i) + total_stat.at(i) )/h_all_bkg->GetBinContent(i+1));
    else h_ratio_unc->SetPointError(i,h_all_bkg->GetBinWidth(i+1)/2, h_all_bkg->GetBinWidth(i+1)/2, std::sqrt((total_exp_sys_up.at(i) + total_stat.at(i)))/h_all_bkg->GetBinContent(i+1), std::sqrt((total_exp_sys_down.at(i) + total_stat.at(i)))/h_all_bkg->GetBinContent(i+1));
  }

  h_ratio_unc->SetFillColor(kGray+2);  
  h_ratio_unc->SetFillStyle(3345);
  h_ratio_unc->Draw("ae2");

  TLine *l=new TLine(m_xminimum,1.0,m_xmaximum,1.0);
  l->SetLineColor(kRed);
  l->Draw("same");
  
  h_ratio_unc->GetXaxis()->SetTitle(xAxisTitle(observable).c_str());
  h_ratio_unc->GetXaxis()->SetTitleSize(.07); 
  h_ratio_unc->GetXaxis()->SetLabelSize(.07);
  h_ratio_unc->GetYaxis()->SetNdivisions(508);
  h_ratio_unc->GetYaxis()->SetLabelSize(.07);
  h_ratio_unc->GetYaxis()->CenterTitle(true);
  h_ratio_unc->GetYaxis()->SetTitleSize(.07);
  h_ratio_unc->GetYaxis()->SetTitleOffset(.7);
  h_ratio_unc->GetYaxis()->SetTitle("Data / Pred.");
  h_ratio_unc->GetXaxis()->SetRangeUser(m_xminimum,m_xmaximum);
  h_ratio_unc->GetYaxis()->SetRangeUser(m_y_ratio_min,m_y_ratio_max);
}

  std::string save_name = "../plots/updates/"+region+"_"+observable+".pdf"; // for submission one dir back
  c->SaveAs(save_name.c_str());

}

void plotting::PlotsforPaper(std::string region, std::string observable, bool addTheo)
{
  std::cout<<"Preparing the plot for the paper.."<<std::endl;

  h_Fakes = getNominalHisto("Fakes"); // Mis-Id
  h_WW = getNominalHisto("diboson1"); // VV
  h_NonWW = getNominalHisto("diboson2");
  h_WWEW = getNominalHisto("WWEW");
  h_Zjets = getNominalHisto("Zjets"); //Zgamma*+jets
  h_Vgamma = getNominalHisto("Vgamma"); 
  h_top1 = getNominalHisto("top1"); //Top
  h_top2 = getNominalHisto("top2");
  h_vbf = getNominalHisto("vbf");
  h_ggf = getNominalHisto("ggf");
  h_vh = getNominalHisto("vh");
  h_htt = getNominalHisto("htt");
  
  h_data = getNominalHisto("data");
  
  THStack* h_stack = new THStack("h_stack","");

  h_WW->Add(h_WWEW);
  h_WW->Add(h_NonWW);
  h_top1->Add(h_top2);
  h_Zjets->Add(h_Vgamma);
  h_ggf->Add(h_vh);
  h_ggf->Add(h_htt);



  h_Fakes->SetFillColor(kCyan-7); //Mis-Id
  h_Fakes->SetLineColor(kBlack);
 
  h_WW->SetFillColor(kViolet+2); //VV
  h_WW->SetLineColor(kBlack);
  
  h_top1->SetFillColor(kYellow-7); //Top
  h_top1->SetLineColor(kBlack);

  h_vbf->SetLineColor(kBlack); //VBF
  h_vbf->SetFillColor(kRed+1);

  h_ggf->SetFillColor(kOrange+3); //Other Higgs
  h_ggf->SetLineColor(kBlack);
  
  h_Zjets->SetFillColor(kGreen+2); //Zgamma*+jets
  h_Zjets->SetLineColor(kBlack);
  
  h_vbf->SetLineWidth(1);
  h_WW->SetLineWidth(1);
  h_Fakes->SetLineWidth(1);
  h_top1->SetLineWidth(1);
  h_Zjets->SetLineWidth(1);
  h_ggf->SetLineWidth(1);
  

  std::vector<float> fakes_stat, WW_stat, top_stat, zjets_stat, ggf_stat, vbf_stat, total_stat, x_stat, y_stat;
 
  // ================  statistical uncertainties ===================== //
  for(int ibin=0; ibin<m_nbins; ibin++)
  {
    fakes_stat.push_back(h_Fakes->GetBinError(ibin+1));
    WW_stat.push_back(h_WW->GetBinError(ibin+1));
    top_stat.push_back(h_top1->GetBinError(ibin+1));

    zjets_stat.push_back(h_Zjets->GetBinError(ibin+1));
   
    ggf_stat.push_back(h_ggf->GetBinError(ibin+1));
    vbf_stat.push_back(h_vbf->GetBinError(ibin+1));

    x_stat.push_back(h_Fakes->GetBinCenter(ibin+1));
    y_stat.push_back(h_Fakes->GetBinContent(ibin+1)+h_WW->GetBinContent(ibin+1)+h_top1->GetBinContent(ibin+1)+h_Zjets->GetBinContent(ibin+1)+h_ggf->GetBinContent(ibin+1)+h_vbf->GetBinContent(ibin+1));  
  }

  for(int istat=0; istat<m_nbins; istat++)
  {
      float stat = std::pow(fakes_stat.at(istat),2)+std::pow(WW_stat.at(istat),2)+std::pow(top_stat.at(istat),2)+std::pow(zjets_stat.at(istat),2)+std::pow(ggf_stat.at(istat),2)+std::pow(vbf_stat.at(istat),2);
      total_stat.push_back(stat);
  }

// ============================================================= //


// =============== add experimental systematics =================================== //
  std::string sys_path = "../exp_systematics/"+m_regionName+"/"+m_obsName+"_"+m_regionName+"_ExpSys.root"; //for submission one dir back
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

  std::vector<std::string> name_Zjets, name_diboson, name_Vgamma, name_top, name_Fakes, name_ggf, name_vh, name_htt, name_vbf;
  std::vector<std::string> name_Zjets_up, name_diboson_up, name_Vgamma_up, name_top_up, name_Fakes_up, name_ggf_up, name_vh_up, name_htt_up, name_vbf_up, name_Zjets_down, name_diboson_down, name_Vgamma_down, name_top_down, name_Fakes_down, name_ggf_down, name_vh_down, name_htt_down, name_vbf_down;
  std::vector<TH1F*> h_Zjets_up, h_diboson_up, h_Vgamma_up, h_top_up, h_Fakes_up, h_ggf_up, h_vh_up, h_htt_up, h_vbf_up, h_Zjets_down, h_diboson_down, h_Vgamma_down, h_top_down, h_Fakes_down, h_ggf_down, h_vh_down, h_htt_down, h_vbf_down;

  for(int i=0; i<(size1+size2+size3); i++)
  {
    name_Zjets.push_back(m_obsName + "_" + getSampleName("Zjets") + "_" + all_sys[i]);
    name_diboson.push_back(m_obsName + "_" + getSampleName("diboson1") + "_" + all_sys[i]);
    name_Vgamma.push_back(m_obsName + "_" + getSampleName("Vgamma") + "_" + all_sys[i]);
    name_top.push_back(m_obsName + "_" + getSampleName("top1") + "_" + all_sys[i]);
    name_ggf.push_back(m_obsName + "_" + getSampleName("ggf") + "_" + all_sys[i]);
    name_vh.push_back(m_obsName + "_" + getSampleName("vh") + "_" + all_sys[i]);
    name_htt.push_back(m_obsName + "_" + getSampleName("htt") + "_" + all_sys[i]);
    name_vbf.push_back(m_obsName + "_" + getSampleName("vbf") + "_" + all_sys[i]);

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

    name_vbf_up.push_back(name_vbf.at(i) + "__1up");
    name_vbf_down.push_back(name_vbf.at(i) + "__1down");
    h_vbf_up.push_back((TH1F*)f_exp->Get(name_vbf_up.at(i).c_str()));
    h_vbf_down.push_back((TH1F*)f_exp->Get(name_vbf_down.at(i).c_str()));
  
  }

  std::vector<float> total_exp_sys_up, total_exp_sys_down;

  for(int ibin =0; ibin<m_nbins; ibin++){
    float total_sum_up = 0;
    float total_sum_down = 0;
    float total_sum_nom = 0;

    float diff_up = 0 ;
    float diff_down = 0;
    
    for(int i=0; i<name_Zjets.size(); i++){
      float total_sum_nom = h_Zjets->GetBinContent(ibin+1) +  h_top1->GetBinContent(ibin+1) + h_WW->GetBinContent(ibin+1) + h_ggf->GetBinContent(ibin+1) + h_vbf->GetBinContent(ibin+1);
      float total_sum_up = h_Zjets_up.at(i)->GetBinContent(ibin+1) +  h_top_up.at(i)->GetBinContent(ibin+1) + h_diboson_up.at(i)->GetBinContent(ibin+1) + h_Vgamma_up.at(i)->GetBinContent(ibin+1) + h_ggf_up.at(i)->GetBinContent(ibin+1)  + h_vh_up.at(i)->GetBinContent(ibin+1) + h_htt_up.at(i)->GetBinContent(ibin+1) + h_vbf_up.at(i)->GetBinContent(ibin+1);
      float total_sum_down = h_Zjets_down.at(i)->GetBinContent(ibin+1) +  h_top_down.at(i)->GetBinContent(ibin+1) + h_diboson_down.at(i)->GetBinContent(ibin+1) + h_Vgamma_down.at(i)->GetBinContent(ibin+1) + h_ggf_down.at(i)->GetBinContent(ibin+1)  + h_vh_down.at(i)->GetBinContent(ibin+1) + h_htt_down.at(i)->GetBinContent(ibin+1) + h_vbf_down.at(i)->GetBinContent(ibin+1);

        diff_up += std::pow(total_sum_nom - total_sum_up,2);
        diff_down += std::pow(total_sum_nom - total_sum_down,2);
    }
    for(int j=0; j<name_Fakes.size(); j++) {
      float total_sum_nom = h_Fakes->GetBinContent(ibin+1);
      float total_sum_up = h_Fakes_up.at(j)->GetBinContent(ibin+1);
      float total_sum_down = h_Fakes_down.at(j)->GetBinContent(ibin+1);

      diff_up += std::pow(total_sum_nom - total_sum_up , 2);
      diff_down += std::pow(total_sum_nom - total_sum_down , 2);
    }

      total_exp_sys_up.push_back(diff_up);
      total_exp_sys_down.push_back(diff_down);
  }

// ===================================================================== //

// ===================== add theory systematics ========================= //
std::vector<float>  total_theo_up, total_theo_down;

  if(addTheo)
  {
    float nom_content = 0; 
    float var_up = 0;
    float var_down = 0;
    
    for(int ibin=0; ibin<m_nbins; ibin++)
    {
      float theo_total_nom = 0;
      float theo_total_up = 0;
      float theo_total_down = 0;
    
      float diff_up = 0;
      float diff_down = 0;

      // add vbf theo variations
      for(int ivbf=0; ivbf<sizeof(v_theo_vbf)/sizeof(v_theo_vbf[0]); ivbf++)
      {
        getTheoryVariations("vbf", v_theo_vbf[ivbf], ibin, nom_content, var_up, var_down);
        diff_up += std::pow(nom_content - var_up, 2);
        diff_down += std::pow(nom_content - var_down, 2);
      }
      // add ggf theo variations
      for(int iggf=0; iggf<sizeof(v_theo_ggf)/sizeof(v_theo_ggf[0]); iggf++)
      {
        getTheoryVariations("ggf", v_theo_ggf[iggf], ibin, nom_content, var_up, var_down);
        diff_up += std::pow(nom_content - var_up, 2);
        diff_down += std::pow(nom_content - var_down, 2);
      }

      // add top theo variations
      for(int itop=0; itop<sizeof(v_theo_top)/sizeof(v_theo_top[0]); itop++)
      {
        getTheoryVariations("top", v_theo_top[itop], ibin, nom_content, var_up, var_down);
        diff_up += std::pow(nom_content - var_up, 2);
        diff_down += std::pow(nom_content - var_down, 2);
      }

      // add Zjets variations
      for(int izjets=0; izjets<sizeof(v_theo_Zjets)/sizeof(v_theo_Zjets[0]); izjets++)
      {
        getTheoryVariations("Zjets0", v_theo_Zjets[izjets], ibin, nom_content, var_up, var_down);
        diff_up += std::pow(nom_content - var_up, 2);
        diff_down += std::pow(nom_content - var_down, 2);
      }

      // add diboson variations
      for(int idib=0; idib<sizeof(v_theo_diboson)/sizeof(v_theo_diboson[0]); idib++)
      {
        getTheoryVariations("diboson", v_theo_diboson[idib], ibin, nom_content, var_up, var_down);
        diff_up += std::pow(nom_content - var_up, 2);
        diff_down += std::pow(nom_content - var_down, 2);
      }

      total_theo_up.push_back(diff_up);    
      total_theo_down.push_back(diff_down); 
    }
  }
// ====================================================================================================== //
  
  TGraphAsymmErrors* h_exp_sys_errors = new TGraphAsymmErrors();

  for(int isys = 0; isys<m_nbins; isys++)
  {
    h_exp_sys_errors->SetPoint(isys,x_stat.at(isys),y_stat.at(isys));
    if(addTheo) h_exp_sys_errors->SetPointError(isys, h_Fakes->GetBinWidth(isys+1)/2, h_Fakes->GetBinWidth(isys+1)/2, std::sqrt( total_exp_sys_up.at(isys) + total_stat.at(isys) + total_theo_up.at(isys) ), std::sqrt( total_exp_sys_down.at(isys) + total_stat.at(isys) + total_theo_down.at(isys)) );
    else h_exp_sys_errors->SetPointError(isys,h_Fakes->GetBinWidth(isys+1)/2,h_Fakes->GetBinWidth(isys+1)/2, std::sqrt(total_exp_sys_up.at(isys) + total_stat.at(isys)) , std::sqrt( total_exp_sys_down.at(isys) + total_stat.at(isys))); 
  }

  h_stack->Add(h_Fakes); // Fakes
  h_stack->Add(h_Zjets); //Z+jets
  h_stack->Add(h_WW); // VV
  h_stack->Add(h_top1); // ttbar
  h_stack->Add(h_ggf); 
  h_stack->Add(h_vbf); //vbf

  TCanvas *c = new TCanvas("atlas_square","Canvas title",0.,0.,600,600);

  h_data->SetMarkerStyle(8);
  pad1 = new TPad("pad1","pad1", 0, 0.35, 1., 1.);
  pad1->SetBottomMargin(0.02);
  pad1->Draw();
  pad1->cd();

  h_stack->Draw("hist");
//  h_vbf->Draw("hist same");
  
  h_exp_sys_errors->SetFillColor(kGray+2);
  h_exp_sys_errors->SetLineColor(kWhite);
  h_exp_sys_errors->SetFillStyle(3345);
  h_exp_sys_errors->Draw("e2 same");

  h_data->Draw("pe same");

  h_stack->SetMinimum(m_yminimum);
  h_stack->SetMaximum(m_ymaximum);
 
  h_stack->GetXaxis()->SetRangeUser(m_xminimum,m_xmaximum);
  h_stack->GetXaxis()->SetLabelSize(0);


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
  if(m_obsName=="nJets" || binEvt==1 || strstr(m_regionName.c_str(),"SR1") || strstr(m_regionName.c_str(),"SR2")) yTitle = "Events";
  if(m_obsName=="DPhill" || m_obsName=="DYjj" || m_obsName=="Mjj" || m_obsName=="MT") yTitle = "Events";
  h_stack->GetYaxis()->SetTitle(yTitle.c_str());
  h_stack->GetYaxis()->SetLabelSize(.045);
  h_stack->GetYaxis()->SetLabelOffset(.004);

  legend = new TLegend(0.58,0.6,0.9,0.9);
  legend->SetBorderSize(0);
  legend->SetFillStyle(0);
  legend->SetTextSize(0.);
  legend->SetNColumns(2);
 
  legend->AddEntry(h_data, "#bf{#scale[.8]{Data}}", "pe");
  legend->AddEntry(h_exp_sys_errors, "#bf{#scale[.8]{Uncertainty}}", "f");
  legend->AddEntry(h_vbf,"#bf{#scale[.8]{H_{VBF}}}", "f");
  legend->AddEntry(h_ggf, "#bf{#scale[.8]{H_{other}}}", "f");
  legend->AddEntry(h_top1, "#bf{#scale[.8]{Top}}","f");
  legend->AddEntry(h_WW, "#bf{#scale[.8]{VV}}", "f");
  legend->AddEntry(h_Zjets, "#bf{#scale[.8]{Z/#scale[1.1]{#gamma}*+jets}}", "f");
  legend->AddEntry(h_Fakes, "#bf{#scale[.8]{Mis-Id}}", "f");
  
  legend->Draw();

  auto legAtlas = new TLegend(0.1,0.6,0.55,0.9);
  legAtlas->SetBorderSize(0);
  legAtlas->SetFillStyle(0);
  legAtlas->SetTextSize(0.);
  legAtlas->AddEntry((TObject*)0, "#it{#scale[1.2]{ATLAS}}",""); //"#font[42]{#scale[1.2]{Internal}}", "");
  //legAtlas->AddEntry((TObject*)0, "", "");
  legAtlas->AddEntry((TObject*)0, "#bf{#sqrt{#scale[.8]{s}} #scale[.8]{= 13 TeV,} #scale[.8]{#int} #scale[.8]{Ldt = 139 fb^{-1}}}", "");
  std::string reg = region;
  if(strstr(m_regionName.c_str(),"SR")) reg = "Signal Region";
  if(strstr(m_regionName.c_str(),"SR1")) reg = "Signal Region - 1";
  if(strstr(m_regionName.c_str(),"SR2")) reg = "Signal Region - 2";
  if(strstr(m_regionName.c_str(),"ggFCR3")) reg = "ggF-VR3";
  if(strstr(m_regionName.c_str(),"ggFCR2")) reg = "ggF-VR2";
  if(strstr(m_regionName.c_str(),"ggFCR1")) reg = "ggF Control Region";
  if(strstr(m_regionName.c_str(),"DYCR")) reg = "Drell-Yan Control Region";
  if(strstr(m_regionName.c_str(),"WWCR")) reg = "WW Validation Region";
  if(strstr(m_regionName.c_str(),"TopCR")) reg = "Top VR";
  std::string regionLabel = "#bf{#scale[.8]{"+reg+"}}";//"#bf{e#mu + #mue channel}";//"#bf{"+region+"}";
 // legAtlas->AddEntry((TObject*)0, "", "");
  legAtlas->AddEntry((TObject*)0, regionLabel.c_str(),"");
  legAtlas->Draw();

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
  h_all_bkg->Add(h_top1);
  h_all_bkg->Add(h_ggf);
  h_all_bkg->Add(h_vbf);

  h_ratio->Divide(h_all_bkg);

  TGraphAsymmErrors* h_ratio_unc = new TGraphAsymmErrors();
  
  for(int i=0; i<m_nbins; i++){
    h_ratio_unc->SetPoint(i,h_ratio->GetBinCenter(i+1),1);
    if(addTheo) h_ratio_unc->SetPointError(i,h_ratio->GetBinWidth(i+1)/2, h_ratio->GetBinWidth(i+1)/2, std::sqrt( total_exp_sys_up.at(i) + total_theo_up.at(i) + total_stat.at(i) )/h_all_bkg->GetBinContent(i+1), std::sqrt( total_exp_sys_down.at(i) + total_theo_down.at(i) + total_stat.at(i) )/h_all_bkg->GetBinContent(i+1));
    else h_ratio_unc->SetPointError(i,h_ratio->GetBinWidth(i+1)/2, h_ratio->GetBinWidth(i+1)/2, std::sqrt((total_exp_sys_up.at(i) + total_stat.at(i)))/h_all_bkg->GetBinContent(i+1), std::sqrt((total_exp_sys_down.at(i) + total_stat.at(i)))/h_all_bkg->GetBinContent(i+1));
  }

  h_ratio_unc->SetFillColor(kGray+2);  
  h_ratio_unc->SetFillStyle(3345);
  h_ratio->Draw("pe");

  TLine *l=new TLine(m_xminimum,1.0,m_xmaximum,1.0);
  l->SetLineColor(kRed);
  l->Draw("same");
  h_ratio_unc->Draw("e2 same");
  h_ratio->Draw("pe same");

  h_ratio->GetXaxis()->SetTitle(xAxisTitle(observable).c_str());
  h_ratio->GetXaxis()->SetTitleSize(.09);
  h_ratio->GetXaxis()->SetLabelSize(.08);
  h_ratio->GetXaxis()->SetLabelOffset(.04);
  h_ratio->GetYaxis()->SetLabelOffset(.006);
  h_ratio->GetYaxis()->SetNdivisions(508);
  h_ratio->GetYaxis()->SetLabelSize(.08);
  h_ratio->GetYaxis()->CenterTitle(true);
  h_ratio->GetYaxis()->SetTitleSize(.09);
  h_ratio->GetYaxis()->SetTitleOffset(.7);
  h_ratio->GetYaxis()->SetTitle("Data / Pred.");
  h_ratio->GetXaxis()->SetRangeUser(m_xminimum,m_xmaximum);
  h_ratio->GetYaxis()->SetRangeUser(m_y_ratio_min,m_y_ratio_max);

  std::string save_name = "../plots/paper/"+region+"_"+observable+".pdf"; // for submission one dir back
  c->SaveAs(save_name.c_str());

}

void plotting::Plots(std::string region1, std::string region2, std::string observable)
{
  std::cout<<"Preparing the plots.."<<std::endl;

  setRegionName(region1.c_str());
  setBins(true);
  TH1F* h_Zjets_1 = getNominalHisto("Zjets");
  setRegionName(region2.c_str());
  setBins(true);
  TH1F* h_Zjets_2 = getNominalHisto("Zjets");

  //h_Zjets_1->SetFillColorAlpha(kGreen+2, 0.35);
  h_Zjets_1->SetFillColor(kGreen+2);
  h_Zjets_1->SetLineColor(kBlack);
  h_Zjets_1->SetMarkerStyle(0);
 // h_Zjets_2->SetFillColorAlpha(kGreen, 0.35);
  h_Zjets_2->SetFillColor(kGreen);
  h_Zjets_2->SetLineColor(kBlack);
  h_Zjets_2->SetMarkerStyle(0);



  TCanvas *c = new TCanvas("atlas_square","Canvas title",0.,0.,600,600);

  pad1 = new TPad("pad1","pad1", 0, 0.35, 1., 1.);

  pad1->SetBottomMargin(0.02);

  pad1->Draw();
  pad1->cd();

  THStack* h_stack = new THStack("h_stack","");
  h_stack->Add(h_Zjets_1);
  h_stack->Add(h_Zjets_2);

  h_stack->Draw("histE");
 // h_Zjets_1->Draw("histE");
 // h_Zjets_2->Draw("histE same");

//  h_exp_sys_errors->SetFillColor(kGray+2);
//  h_exp_sys_errors->SetLineColor(kWhite);
//  h_exp_sys_errors->SetFillStyle(3345);
//  h_exp_sys_errors->Draw("e2 same");


  h_stack->SetMinimum(m_yminimum);
  h_stack->SetMaximum(m_ymaximum);
 
  h_stack->GetXaxis()->SetRangeUser(m_xminimum,m_xmaximum);
  h_stack->GetXaxis()->SetLabelSize(0);

  h_stack->GetXaxis()->SetTitle(xAxisTitle(observable).c_str());
  h_stack->GetXaxis()->SetTitleSize(.0);
  h_stack->GetXaxis()->SetLabelSize(.0);
  h_stack->GetYaxis()->SetLabelSize(.04);
  h_stack->GetYaxis()->SetTitleSize(.04);
  h_stack->GetYaxis()->SetTitleOffset(1.5);
  h_stack->GetXaxis()->SetTitleOffset(2.);

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
  if(m_obsName=="nJets" || binEvt==1 ) yTitle = "Events";

  h_stack->GetYaxis()->SetTitle(yTitle.c_str());

  legend = new TLegend(0.55,0.55,0.92,0.9);
  legend->SetBorderSize(0);
  legend->SetFillStyle(0);
  legend->SetTextSize(0.);
  legend->SetNColumns(2);
 
  std::string leg1 = Form("Zjets in %s", region1.c_str());
  std::string leg2 = Form("Zjets in %s", region2.c_str());
  legend->AddEntry(h_Zjets_1, Form("#scale[1.]{Zjets in %s}",region1.c_str()), "f");
  legend->AddEntry(h_Zjets_2, Form("#scale[1.]{Zjets in %s}",region2.c_str()), "f");
  legend->AddEntry((TObject*)0, Form("#scale[1.]{%3.0f evnts}",h_Zjets_1->Integral()), "");
  legend->AddEntry((TObject*)0, Form("#scale[1.]{%3.0f evnts}",h_Zjets_2->Integral()), "");
 
  
  legend->Draw();

  auto legAtlas = new TLegend(0.075,0.7,0.52,0.92);
  legAtlas->SetBorderSize(0);
  legAtlas->SetFillStyle(0);
  legAtlas->SetTextSize(0.);
  legAtlas->AddEntry((TObject*)0, "#it{#scale[1.5]{ATLAS}} #font[42]{#scale[1.5]{Internal}}", "");
  legAtlas->AddEntry((TObject*)0, "#bf{#sqrt{#scale[1.]{s}} #scale[1.]{= 13 TeV,} #scale[1.]{#int} #scale[1.]{Ldt = 139 fb^{-1}}}", "");
  std::string regionLabel = "#bf{"+region1+" / "+ region2+"}";//"#bf{e#mu + #mue channel}";//"#bf{"+region+"}";
  legAtlas->AddEntry((TObject*)0, regionLabel.c_str(),"");

  legAtlas->Draw();

  c->cd();
  pad2 = new TPad("pad2", "pad2", 0, 0., 1, 0.35);
  pad2->SetTopMargin(0.03);
  pad2->SetBottomMargin(.4);
  pad2->Draw();
  pad2->cd();
  gPad->SetGridy(1);

  TH1F* h_ratio = (TH1F*) h_Zjets_1->Clone("ratio");
  
//  TH1F* h_all_bkg_signal = (TH1F*) h_all_bkg->Clone("all_bkg_signal");
//  h_all_bkg_signal->Add(h_vbf);
 // TH1F* h_ratio2 = (TH1F*) h_data->Clone("ratio2");
 // h_ratio2->Divide(h_all_bkg_signal);*/
  h_ratio->Divide(h_Zjets_2);


//  h_ratio_unc->SetFillColor(kGray+2);  
//  h_ratio_unc->SetFillStyle(3345);
  h_ratio->Draw("pe");

  TLine *l=new TLine(m_xminimum,1.0,m_xmaximum,1.0);
  l->SetLineColor(kRed);
  l->Draw("same");
  h_ratio->Draw("pe same");

  h_ratio->GetXaxis()->SetTitle(xAxisTitle(observable).c_str());
  h_ratio->GetXaxis()->SetTitleSize(.09);
  h_ratio->GetXaxis()->SetLabelSize(.09);
  h_ratio->GetYaxis()->SetNdivisions(508);
  h_ratio->GetYaxis()->SetLabelSize(.09);
  h_ratio->GetYaxis()->CenterTitle(true);
  h_ratio->GetYaxis()->SetTitleSize(.09);
  h_ratio->GetYaxis()->SetTitleOffset(.7);
  h_ratio->SetMarkerStyle(20);
//  std::string ratio_title = Form("Zjets^{%s}",region1.c_str()) + "/" + Form("Zjets_%s",region2.c_str());
  h_ratio->GetYaxis()->SetTitle("Zjets^{SR}/Zjets^{DYCR}");
  h_ratio->GetXaxis()->SetRangeUser(m_xminimum,m_xmaximum);
  h_ratio->GetYaxis()->SetRangeUser(m_y_ratio_min,m_y_ratio_max);

  std::string save_name = "../plots/submission/"+region1+"_"+region2+"_"+observable+".pdf"; // for submission one dir back
  c->SaveAs(save_name.c_str());

}

plotting::plotting(std::string region1, std::string region2, std::string observable, bool lxplus, float y_min, float y_max, std::string x_min, float x_max, std::string y_ratio_min, float y_ratio_max)
{
  gROOT->SetBatch(kTRUE);
  SetAtlasStyle();

  clock_t tStart = clock();
  auto t_start = std::chrono::high_resolution_clock::now();
  workOnLxplus(lxplus);
  setObsName(observable);
  
  if(x_min.find(")") != string::npos) x_min.erase(0,1);
  if(y_ratio_min.find(")") != string::npos) y_ratio_min.erase(0,1);

    float xmin = std::stof(x_min);
    setXMin(xmin);
    setXMax(x_max);
    float yratiomin = std::stof(y_ratio_min);
    setYMin(y_min);
    setYMax(y_max);
    

    setYminRatio(yratiomin);
    setYmaxRatio(y_ratio_max);

    Plots(region1, region2, observable);

  clock_t tEnd = clock();
  auto t_end = std::chrono::high_resolution_clock::now();

  std::cout<<"Time taken: "<<(double)(tEnd - tStart)/CLOCKS_PER_SEC<<"s\n";
  std::cout<<"Wall clock time passed: "<<std::chrono::duration<double, std::milli>(t_end-t_start).count()<<"ms\n ";
}

plotting::plotting(std::string region, std::string observable, bool unblind, bool forPaper, bool setAxesLimits, bool addTheo, bool lxplus)
{
  gROOT->SetBatch(kTRUE);
  SetAtlasStyle();
  
  clock_t tStart = clock();
  auto t_start = std::chrono::high_resolution_clock::now();

  workOnLxplus(lxplus);

  setObsName(observable);
  setRegionName(region);

  plotsForPaper(forPaper);
  setBins(forPaper);

  if(setAxesLimits)
  {
    float y_maximum, y_minimum, x_minimum, x_maximum;
    std::cout<<"Set Y-axis minimum ";
    std::cin>>y_minimum;
    std::cout<<"Set Y-axis maximum ";
    std::cin>>y_maximum;
    std::cout<<"Set X-axis minimum ";
    std::cin>>x_minimum;
    std::cout<<"Set X-axis maximum ";
    std::cin>>x_maximum;
    

    float y_ratio_min, y_ratio_max;
    std::cout<<"==== Limits for the bottom panel ====\n";
    std::cout<<"y-axis min value \n";
    std::cin>>y_ratio_min;
    std::cout<<"y-axis max value \n";
    std::cin>>y_ratio_max;

    setYminRatio(y_ratio_min);
    setYmaxRatio(y_ratio_max);


    setYMin(y_minimum);
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
  else PlotsforNote(m_regionName, m_obsName, unblind, addTheo);

  clock_t tEnd = clock();
  auto t_end = std::chrono::high_resolution_clock::now();

  std::cout<<"Time taken: "<<(double)(tEnd - tStart)/CLOCKS_PER_SEC<<"s\n";
  std::cout<<"Wall clock time passed: "<<std::chrono::duration<double, std::milli>(t_end-t_start).count()<<"ms\n ";

}

plotting::plotting(std::string region, std::string observable, bool unblind, bool forPaper, bool addTheo, bool lxplus, float y_min, float y_max, std::string x_min, float x_max, std::string y_ratio_min, float y_ratio_max)
{
	gROOT->SetBatch(kTRUE);
  	SetAtlasStyle();

  	workOnLxplus(lxplus);

  	setObsName(observable);
  	setRegionName(region);

  	plotsForPaper(forPaper);
  	setBins(forPaper);

    if(x_min.find(")") != string::npos) x_min.erase(0,1);
    if(y_ratio_min.find(")") != string::npos) y_ratio_min.erase(0,1);

    float xmin = std::stof(x_min);
    setXMin(xmin);
    setXMax(x_max);
    float yratiomin = std::stof(y_ratio_min);
  	setYMin(y_min);
    setYMax(y_max);
    

    setYminRatio(yratiomin);
    setYmaxRatio(y_ratio_max);

    //if(forPaper) 
    PlotsforPaper(m_regionName, m_obsName, addTheo);
    //PlotsforNote(m_regionName, m_obsName, unblind, addTheo);//(m_regionName, m_obsName, unblind);
    //else PlotsforNote(m_regionName, m_obsName, unblind, addTheo);

    std::cout<<"Plot for "<<observable<<" in "<<region<<" done!\n";
}

