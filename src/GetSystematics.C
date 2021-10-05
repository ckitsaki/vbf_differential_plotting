
#include "GetSystematics.h"

/////////////////////////////////////////////////////////////////
// List of the experimental systematics used in the analysis. //
///////////////////////////////////////////////////////////////
std::string v_sys_list[99] = {"EL_EFF_ID_CorrUncertaintyNP5", "EL_EFF_ID_CorrUncertaintyNP6", "EL_EFF_ID_CorrUncertaintyNP7", "EL_EFF_ID_CorrUncertaintyNP8", "EL_EFF_ID_CorrUncertaintyNP9", "EL_EFF_ID_CorrUncertaintyNP10", "EL_EFF_ID_CorrUncertaintyNP11", "EL_EFF_ID_CorrUncertaintyNP12", "EL_EFF_ID_CorrUncertaintyNP13", "EL_EFF_ID_CorrUncertaintyNP14", "FT_EFF_extrapolation", "FT_EFF_extrapolation_from_charm", "JET_JvtEfficiency", "MUON_EFF_RECO_STAT", "MUON_EFF_RECO_STAT_LOWPT", "MUON_EFF_RECO_SYS", "MUON_EFF_RECO_SYS_LOWPT", "MUON_EFF_TrigStatUncertainty", "MUON_EFF_TrigSystUncertainty", "EG_RESOLUTION_ALL", "EG_SCALE_AF2", "EG_SCALE_ALL", "JET_BJES_Response", "JET_EffectiveNP_Detector1", "JET_EffectiveNP_Detector2", "JET_EffectiveNP_Mixed1", "JET_EffectiveNP_Mixed2", "JET_EffectiveNP_Mixed3", "JET_EffectiveNP_Modelling2", "JET_EffectiveNP_Modelling3", "JET_EffectiveNP_Modelling4", "JET_EffectiveNP_Statistical1", "JET_EffectiveNP_Statistical2", "JET_EffectiveNP_Statistical4", "JET_EffectiveNP_Statistical6", "JET_EffectiveNP_Modelling1", "JET_EtaIntercalibration_Modelling", "JET_EtaIntercalibration_NonClosure_highE", "JET_EtaIntercalibration_NonClosure_negEta", "JET_EtaIntercalibration_NonClosure_posEta", "JET_EtaIntercalibration_TotalStat", "JET_Pileup_OffsetNPV", "JET_Pileup_PtTerm", "JET_Pileup_RhoTopology", "JET_PunchThrough_MC16", "JET_SingleParticle_HighPt", "EL_EFF_ID_CorrUncertaintyNP0", "EL_EFF_ID_CorrUncertaintyNP1", "EL_EFF_ID_CorrUncertaintyNP2", "EL_EFF_ID_CorrUncertaintyNP3", "EL_EFF_ID_CorrUncertaintyNP4", "JET_EffectiveNP_Statistical5", "MUON_ID", "MUON_MS", "JET_EffectiveNP_Statistical3", "JET_Flavor_Composition", "MUON_SCALE", "MUON_SAGITTA_RHO", "MUON_SAGITTA_RESBIAS", "JET_Flavor_Response", "JET_Pileup_OffsetMu", "EL_EFF_ID_CorrUncertaintyNP15", "EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP0", "EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP1", "EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP2", "EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP3", "EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP4", "EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP5", "EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP6", "EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP7", "EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP8", "EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP9", "EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP10", "EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP11", "EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP12", "EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP13", "EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP14", "EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP15", "EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP16", "EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP17", "EL_EFF_Iso_TOTAL_1NPCOR_PLUS_UNCOR", "EL_EFF_Reco_TOTAL_1NPCOR_PLUS_UNCOR", "EL_EFF_Trigger_TOTAL_1NPCOR_PLUS_UNCOR", "FT_EFF_Eigen_B_0", "FT_EFF_Eigen_B_1", "FT_EFF_Eigen_B_2", "FT_EFF_Eigen_C_0", "FT_EFF_Eigen_C_1", "FT_EFF_Eigen_C_2", "FT_EFF_Eigen_Light_0", "FT_EFF_Eigen_Light_1", "FT_EFF_Eigen_Light_2", "FT_EFF_Eigen_Light_3", "MUON_EFF_ISO_STAT", "MUON_EFF_ISO_SYS", "MUON_EFF_TTVA_STAT", "MUON_EFF_TTVA_SYS", "PRW_DATASF", "EL_EFF_TriggerEff_TOTAL_1NPCOR_PLUS_UNCOR"};

std::string v_sys_MET[4] = {"MET_SoftTrk_ScaleUp", "MET_SoftTrk_ScaleDown", "MET_SoftTrk_ResoPerp", "MET_SoftTrk_ResoPara"};

std::string v_sys_JER_PDSmear[13] = {"JET_JER_DataVsMC_MC16_PDsmear", "JET_JER_EffectiveNP_1_PDsmear", "JET_JER_EffectiveNP_2_PDsmear", "JET_JER_EffectiveNP_3_PDsmear", "JET_JER_EffectiveNP_4_PDsmear", "JET_JER_EffectiveNP_5_PDsmear", "JET_JER_EffectiveNP_6_PDsmear", "JET_JER_EffectiveNP_7_PDsmear", "JET_JER_EffectiveNP_8_PDsmear", "JET_JER_EffectiveNP_9_PDsmear", "JET_JER_EffectiveNP_10_PDsmear", "JET_JER_EffectiveNP_11_PDsmear", "JET_JER_EffectiveNP_12restTerm_PDsmear"};

std::string v_sys_JER_MCSmear[13] = {"JET_JER_DataVsMC_MC16_MCsmear", "JET_JER_EffectiveNP_1_MCsmear", "JET_JER_EffectiveNP_2_MCsmear", "JET_JER_EffectiveNP_3_MCsmear", "JET_JER_EffectiveNP_4_MCsmear", "JET_JER_EffectiveNP_5_MCsmear", "JET_JER_EffectiveNP_6_MCsmear", "JET_JER_EffectiveNP_7_MCsmear", "JET_JER_EffectiveNP_8_MCsmear", "JET_JER_EffectiveNP_9_MCsmear", "JET_JER_EffectiveNP_10_MCsmear", "JET_JER_EffectiveNP_11_MCsmear", "JET_JER_EffectiveNP_12restTerm_MCsmear"};

std::string v_sys_Fakes[54] = {"mu_FF_Com", "el_FF_Com", "mu_FF_EWSUBTR", "el_FF_EWSUBTR", "el_FF_STAT_2015_2018_3_1", "el_FF_STAT_2015_2018_4_1", "el_FF_STAT_2015_1_1", "el_FF_STAT_2015_2_1", "el_FF_STAT_2015_3_1", "el_FF_STAT_2015_4_1", "el_FF_STAT_2017_1_1", "el_FF_STAT_2017_2_1", "el_FF_STAT_2017_3_1", "el_FF_STAT_2017_4_1", "el_FF_STAT_2016_1_1", "mu_FF_STAT_2017_2_2", "mu_FF_STAT_2017_3_1", "mu_FF_STAT_2017_3_2", "mu_FF_STAT_2016_1_1", "mu_FF_STAT_2016_1_2", "mu_FF_STAT_2016_2_1", "mu_FF_STAT_2016_2_2", "mu_FF_STAT_2016_3_1", "mu_FF_STAT_2016_3_2", "mu_FF_STAT_2018_1_1", "mu_FF_STAT_2018_1_2", "mu_FF_STAT_2018_2_1", "mu_FF_STAT_2018_2_2", "mu_FF_STAT_2018_3_1", "mu_FF_STAT_2018_3_2", "el_FF_STAT_2015_2018_1_1", "el_FF_STAT_2015_2018_2_1", "mu_FF_STAT_2015_2018_1_1", "mu_FF_STAT_2015_2018_1_2", "mu_FF_STAT_2015_2018_2_1", "mu_FF_STAT_2015_2018_2_2", "mu_FF_STAT_2015_2018_3_1", "mu_FF_STAT_2015_2018_3_2", "mu_FF_STAT_2015_1_1", "mu_FF_STAT_2015_1_2", "mu_FF_STAT_2015_2_1", "mu_FF_STAT_2015_2_2", "mu_FF_STAT_2015_3_1", "mu_FF_STAT_2015_3_2", "mu_FF_STAT_2017_1_1", "mu_FF_STAT_2017_1_2", "mu_FF_STAT_2017_2_1", "el_FF_STAT_2016_2_1", "el_FF_STAT_2016_3_1", "el_FF_STAT_2016_4_1", "el_FF_STAT_2018_1_1", "el_FF_STAT_2018_2_1", "el_FF_STAT_2018_3_1", "el_FF_STAT_2018_4_1"};

///////////////////////////////////////////////////////////
// Tool to convert a floating point number to string    //
// Reverses a string 'str' of length 'len'             //
////////////////////////////////////////////////////////
void reverse(char* str, int len)
{
    int i = 0, j = len - 1, temp;
    while (i < j) {
        temp = str[i];
        str[i] = str[j];
        str[j] = temp;
        i++;
        j--;
    }
}

/////////////////////////////////////////////////////////////
// Converts a given integer x to string str[].            //
// d is the number of digits required in the output.     // 
// If d is more than the number of digits in x,         //
// then 0s are added at the beginning.                 //
////////////////////////////////////////////////////////
int intToStr(int x, char str[], int d)
{
    int i = 0;
    while (x) {
        str[i++] = (x % 10) + '0';
        x = x / 10;
    }
  
    // If number of digits required is more, then
    // add 0s at the beginning
    while (i < d)
        str[i++] = '0';
  
    reverse(str, i);
    str[i] = '\0';
    return i;
}
//////////////////////////////////////////////////////////////
// Converts a floating-point/double number to a string.    //
////////////////////////////////////////////////////////////
void ftoa(float n, char* res, int afterpoint)
{
    // Extract integer part
    int ipart = (int)n;
  
    // Extract floating part
    float fpart = n - (float)ipart;
  
    // convert integer part to string
    int i = intToStr(ipart, res, 0);
  
    // check for display option after point
    if (afterpoint != 0) {
        res[i] = '.'; // add dot
  
        // Get the value of fraction part upto given no.
        // of points after dot. The third parameter 
        // is needed to handle cases like 233.007
        fpart = fpart * pow(10, afterpoint);

               intToStr((int)fpart, res + i + 1, afterpoint);
    }
}



TH1F* GetSystematics::getNominalHisto(std::string sample, bool lxplus)
{
  std::string tree_name = getSampleName(sample) + "_nominal";
  
  TreeReader *treeReader = new TreeReader(m_regionName, sample, tree_name, lxplus);

  std::cout<<sample<<" - added \n";

  TH1F* h;
  if(!isForPaper())
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

TH1F* GetSystematics::getNominalHisto(std::string sample, std::string campaign)
{
  std::string tree_name = getSampleName(sample) + "_nominal";
  
  TreeReader *treeReader = new TreeReader(m_regionName, sample, tree_name, campaign);

  std::cout<<sample<<" - added for campaign "<<campaign<<"\n";

  TH1F* h;
  if(!isForPaper())
  {
    h = new TH1F("histo", "histo", m_nbins, m_xmin, m_xmax);
  }
  else h = new TH1F("histo", "histo", m_nbins, m_binsEdges);

  std::vector<TTree*> v = treeReader->getTreesPerCampaign();

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

TH1F* GetSystematics::getSysHist(bool sys_up, std::string sample, std::string sysName, bool lxplus)
{

  std::string sys_type="__1up";
  if(!sys_up) sys_type="__1down";

  std::string tree_name = getSampleName(sample) + "_" + sysName + sys_type;
  
  std::cout<<"preparing... "<<tree_name<<'\n';

  TreeReader *treeReader = new TreeReader(m_regionName, sample, tree_name, lxplus);

  std::string histo_name = m_obsName + "_" + tree_name ;

  TH1F* h;
  if(!isForPaper())
  {
    h = new TH1F(histo_name.c_str(), histo_name.c_str(), m_nbins, m_xmin, m_xmax);
  }
  else h = new TH1F(histo_name.c_str(), histo_name.c_str(), m_nbins, m_binsEdges);
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

TH1F* GetSystematics::getSysHist(bool sys_up, std::string sample, std::string sysName, std::string campaign)
{

  std::string sys_type="__1up";
  if(!sys_up) sys_type="__1down";

  std::string tree_name = getSampleName(sample) + "_" + sysName + sys_type;
  
  std::cout<<"preparing... "<<tree_name<<'\n';

  TreeReader *treeReader = new TreeReader(m_regionName, sample, tree_name, campaign);

  std::string histo_name = m_obsName + "_" + tree_name ;

  TH1F* h;
  if(!isForPaper())
  {
    h = new TH1F(histo_name.c_str(), histo_name.c_str(), m_nbins, m_xmin, m_xmax);
  }
  else h = new TH1F(histo_name.c_str(), histo_name.c_str(), m_nbins, m_binsEdges);

  std::vector<TTree*> v = treeReader->getTreesPerCampaign();

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

TH1F* GetSystematics::getMETHist(bool sys_up, std::string sample, std::string sysName, bool lxplus)
{

  std::string sys_type="__1up";
  if(!sys_up) sys_type="__1down";

  std::string tree_name = getSampleName(sample) + "_" + sysName;
  
  std::cout<<"preparing... "<<tree_name<<'\n';

  TreeReader *treeReader = new TreeReader(m_regionName, sample, tree_name, lxplus);

  std::string histo_name = m_obsName + "_" + tree_name + sys_type;

  TH1F* h;
  if(!isForPaper())
  {
    h = new TH1F(histo_name.c_str(), histo_name.c_str(), m_nbins, m_xmin, m_xmax);
  }
  else h = new TH1F(histo_name.c_str(), histo_name.c_str(), m_nbins, m_binsEdges);

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

TH1F* GetSystematics::getMETHist(bool sys_up, std::string sample, std::string sysName, std::string campaign)
{

  std::string sys_type="__1up";
  if(!sys_up) sys_type="__1down";

  std::string tree_name = getSampleName(sample) + "_" + sysName;
  
  std::cout<<"preparing... "<<tree_name<<'\n';

  TreeReader *treeReader = new TreeReader(m_regionName, sample, tree_name, campaign);

  std::string histo_name = m_obsName + "_" + tree_name + sys_type;

  TH1F* h;
  if(!isForPaper())
  {
    h = new TH1F(histo_name.c_str(), histo_name.c_str(), m_nbins, m_xmin, m_xmax);
  }
  else h = new TH1F(histo_name.c_str(), histo_name.c_str(), m_nbins, m_binsEdges);

  std::vector<TTree*> v = treeReader->getTreesPerCampaign();

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

bool String2Convert(std::string var){   
  if(var == "true" || var == "TRUE" || var == "True" || var =="1")      
    return true;   
  else if( var=="false" || var=="FALSE" || var=="0" )  
    return false; 

  else return false;
}

GetSystematics::GetSystematics(std::string region, std::string observable, std::string sample, std::string campaign, std::string sys_name, std::string JER0, std::string MET0, std::string other0, std::string forPaper0)
{
  bool JER = String2Convert(JER0);  
  bool MET = String2Convert(MET0);
  bool other = String2Convert(other0);
  m_forPaper = String2Convert(forPaper0);

  setObsName(observable);
  setRegionName(region);
  setBins(m_forPaper);
  
  std::string filename = "../sys_files/" + m_obsName + "_" + sample + "_" + campaign + "_" + sys_name + ".root";
  
  TFile *outputFile = new TFile(filename.c_str(),"RECREATE");  

  // ==== Fix & book JER sys ==== //
  if(JER){
    TH1F* h_nominal = getNominalHisto(sample, campaign);
 
    int index = std::distance(v_sys_JER_PDSmear, std::find(v_sys_JER_PDSmear, v_sys_JER_PDSmear + sizeof(v_sys_JER_PDSmear)/sizeof(v_sys_JER_PDSmear[0]), sys_name));

      TH1F* h_pdsmear_up = getSysHist(1,sample, v_sys_JER_PDSmear[index], campaign);
      TH1F* h_mcsmear_up = getSysHist(1,sample, v_sys_JER_MCSmear[index], campaign);
      h_mcsmear_up->Add(h_pdsmear_up,-1);
      h_mcsmear_up->Add(h_nominal);

      outputFile->cd();
      h_mcsmear_up->Write();
      delete h_mcsmear_up;
      delete h_pdsmear_up;
    
      TH1F*  h_pdsmear_down = getSysHist(0,sample, v_sys_JER_PDSmear[index], campaign);
      TH1F*  h_mcsmear_down = getSysHist(0,sample, v_sys_JER_MCSmear[index], campaign);
      h_mcsmear_down->Add(h_pdsmear_down,-1);
      h_mcsmear_down->Add(h_nominal);

      outputFile->cd();
      h_mcsmear_down->Write();

      delete h_mcsmear_down;
      delete h_pdsmear_down;
 
    delete h_nominal;
  }
  // ========================= //

  // ==== Book exp sys ==== //
  if(other){
     TH1F* h_up = getSysHist(1, sample, sys_name, campaign); 
     TH1F* h_down = getSysHist(0, sample, sys_name, campaign); 
    
      outputFile->cd();
      h_up->Write();
      h_down->Write();
      delete h_up;
      delete h_down;
  }
  // ========================= //

  // ==== Book MET sys ===== //
  if(MET){
      TH1F* h_met_up = getMETHist(1, sample, sys_name, campaign);
      TH1F* h_met_down = getMETHist(0, sample, sys_name, campaign);

      outputFile->cd();
      h_met_up->Write();
      h_met_down->Write();   
      delete h_met_down;
      delete h_met_up; 
  }
  // ========================= //

  delete outputFile;

}
