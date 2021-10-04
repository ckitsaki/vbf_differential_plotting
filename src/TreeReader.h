
#ifndef TREEREADER_H 
#define TREEREADER_H

class TreeReader{
 public:

  TFile *f_the_file_c16a_0jet;
  TFile *f_the_file_c16d_0jet;
  TFile *f_the_file_c16e_0jet;

  TFile *f_the_file_c16a_1jet;
  TFile *f_the_file_c16d_1jet;
  TFile *f_the_file_c16e_1jet;

  TFile *f_the_file_c16a_2jet;
  TFile *f_the_file_c16d_2jet;
  TFile *f_the_file_c16e_2jet;

  TTree *t_the_tree_c16a_0jet;
  TTree *t_the_tree_c16d_0jet;
  TTree *t_the_tree_c16e_0jet;

  TTree *t_the_tree_c16a_1jet;
  TTree *t_the_tree_c16d_1jet;
  TTree *t_the_tree_c16e_1jet;

  TTree *t_the_tree_c16a_2jet;
  TTree *t_the_tree_c16d_2jet;
  TTree *t_the_tree_c16e_2jet;

  TFile *f_the_file_0jet;
  TFile *f_the_file_1jet;
  TFile *f_the_file_2jet;

  TTree *t_the_tree_0jet;
  TTree *t_the_tree_1jet;
  TTree *t_the_tree_2jet;

  float lep0_pt;
  float lep1_pt;
  float jet0_pt;
  float jet1_pt;
  float jet2_pt;
  float Mjj;
  float DPhill;
  float DPhijj;
  float DYjj;
  float Mll;
  float DYll;
  float nJets;
  float Ml0j0;
  float Ml1j1; 
  float Ml0j1;
  float Ml1j0;
  float MET;
  float jet0_eta;
  float jet1_eta;
  float lep0_eta;
  float lep1_eta;
  float Ptll;
  float SignedDPhijj;
  float MT;
  float costhetastar;
  float ptTot;
  float sumOfCentralitiesL;
  float pt_H;
  float inSR;
  float inWWCR;
  float inTopCR;
  float inZjetsCR;
  float inggFCR1;
  float inggFCR2;
  float inggFCR3;
  float mcChannelNumber;
  float bdt_vbf;
  double weight;

  TreeReader(std::string region, std::string sample, std::string tree_name);
  TreeReader(std::string region, std::string sample, std::string tree_name, std::string campaign);
  virtual ~TreeReader()=default;
  inline std::string xAxisTitle(std::string observable);
  inline void Init(TTree* tree);
  inline float getCut();
  inline float getObservable(std::string observable);
  std::vector<TTree*> getTrees();
  std::vector<TTree*> getTreesPerCampaign(); 
  inline void setSample(std::string sample) {m_sample = sample;};
  inline std::string getSample(){return m_sample;};
  inline void setRegion(std::string region) {m_region = region;};
  inline std::string getRegion() {return m_region;};

private:
  TTree *the_tree;
  std::string m_sample;
  std::string m_region;
  std::string path0;
  std::string path1;
  std::string path2;

};


inline void TreeReader::Init(TTree* tree)
{
  lep0_pt = 0;
  lep1_pt = 0;
  jet0_pt = 0;
  jet1_pt = 0;
  jet2_pt = 0;
  Mjj = 0;
  DPhill = 0;
  DPhijj = 0;
  DYjj = 0;
  Mll = 0;
  DYll = 0;
  nJets = 0;
  jet0_eta = 0;
  jet1_eta = 0;
  lep0_eta = 0;
  lep1_eta = 0;
  Ml0j0 = 0;
  Ml1j1 = 0;
  Ml1j0 = 0;
  Ml0j1 = 0;
  MET = 0;
  pt_H = 0;
  costhetastar = 0;
  ptTot = 0;
  MT = 0;
  SignedDPhijj = 0;
  sumOfCentralitiesL = 0;
  Ptll = 0;
  inSR = -1;
  inWWCR = -1;
  inTopCR = -1;
  inZjetsCR = -1;
  inggFCR1 = -1;
  inggFCR2 = -1;
  inggFCR3 = -1;
  mcChannelNumber = -1;
  bdt_vbf = 0;
  weight = 0;

  the_tree = tree;

  the_tree->SetBranchAddress("lep0_pt", &lep0_pt);
  the_tree->SetBranchAddress("lep1_pt", &lep1_pt);
  the_tree->SetBranchAddress("Ptll", &Ptll);
  the_tree->SetBranchAddress("jet0_pt", &jet0_pt);
  the_tree->SetBranchAddress("jet1_pt", &jet1_pt);
  the_tree->SetBranchAddress("jet2_pt", &jet2_pt);
  the_tree->SetBranchAddress("Mjj", &Mjj);
  the_tree->SetBranchAddress("nJets", &nJets);
  the_tree->SetBranchAddress("DPhill", &DPhill);
  the_tree->SetBranchAddress("DPhijj", &DPhijj);
  the_tree->SetBranchAddress("DYjj", &DYjj);
  the_tree->SetBranchAddress("Mll", &Mll);
  the_tree->SetBranchAddress("DYll", &DYll);
  the_tree->SetBranchAddress("jet0_eta", &jet0_eta);
  the_tree->SetBranchAddress("jet1_eta", &jet1_eta);
  the_tree->SetBranchAddress("lep0_eta", &lep0_eta);
  the_tree->SetBranchAddress("lep1_eta", &lep1_eta);
  the_tree->SetBranchAddress("SignedDPhijj", &SignedDPhijj);
  the_tree->SetBranchAddress("Ml0j0", &Ml0j0);
  the_tree->SetBranchAddress("Ml1j1", &Ml1j1);
  the_tree->SetBranchAddress("Ml0j1", &Ml0j1);
  the_tree->SetBranchAddress("Ml1j0", &Ml1j0);
  the_tree->SetBranchAddress("MET", &MET);
  the_tree->SetBranchAddress("MT", &MT);
  the_tree->SetBranchAddress("costhetastar", &costhetastar);
  the_tree->SetBranchAddress("sumOfCentralitiesL", &sumOfCentralitiesL);
  the_tree->SetBranchAddress("pt_H", &pt_H);
  the_tree->SetBranchAddress("ptTot", &ptTot);
  the_tree->SetBranchAddress("inSR", &inSR);
  the_tree->SetBranchAddress("inWWCR", &inWWCR);
  the_tree->SetBranchAddress("inTopCR", &inTopCR);
  the_tree->SetBranchAddress("inZjetsCR", &inZjetsCR);
  the_tree->SetBranchAddress("inggFCR1", &inggFCR1);
  the_tree->SetBranchAddress("inggFCR2", &inggFCR2);
  the_tree->SetBranchAddress("inggFCR3", &inggFCR3);
  the_tree->SetBranchAddress("mcChannelNumber", &mcChannelNumber);
  the_tree->SetBranchAddress("bdt_vbf", &bdt_vbf);
  the_tree->SetBranchAddress("weight", &weight);

}

inline float TreeReader::getCut()
{
  float cut = -1;
  if(m_region=="SR") cut = weight*(inSR==1 && Mjj/1000 > 450 && DPhill < 1.4);
  if(m_region=="SR1") cut = weight*(inSR==1 && Mjj/1000 > 450 && DPhill < 1.4 && bdt_vbf>0.5);
  if(m_region=="SR2") cut = weight*(inSR==1 && Mjj/1000 > 450 && DPhill < 1.4 && bdt_vbf<0.5);
  if(m_region=="WWCR") cut = weight*(inWWCR==1);
  if(m_region=="TopCR") cut = weight*(inTopCR==1);
  if(m_region=="DYCR") cut = weight*(inZjetsCR == 1 && Mjj/1000 > 450);
  if(m_region=="ggFCR1") cut = weight*(inggFCR1 == 1 && DPhill < 1.4);
  if(m_region=="ggFCR2") cut = weight*(inggFCR2 == 1 && DPhill < 1.4);
  if(m_region=="ggFCR3") cut = weight*(inggFCR3 == 1 && DPhill < 1.4);

  return cut;
}

inline float TreeReader::getObservable(std::string observable)
{
  float variable_to_plot = -1;
  if(observable=="Mjj") variable_to_plot = (Mjj)/1000;
  if(observable=="Mll") variable_to_plot = (Mll)/1000;
  if(observable=="DYjj") variable_to_plot = DYjj;
  if(observable=="DYll") variable_to_plot = DYll;
  if(observable=="jet0_pt") variable_to_plot = (jet0_pt)/1000;
  if(observable=="jet1_pt") variable_to_plot = (jet1_pt)/1000;
  if(observable=="jet2_pt") variable_to_plot = (jet2_pt)/1000;
  if(observable=="costhetastar") variable_to_plot = costhetastar;
  if(observable=="ptTot") variable_to_plot = (ptTot)/1000;
  if(observable=="pt_H") variable_to_plot = (pt_H)/1000;
  if(observable=="sumOfCentralitiesL") variable_to_plot = sumOfCentralitiesL;
  if(observable=="SignedDPhijj") variable_to_plot = SignedDPhijj;
  if(observable=="DPhijj") variable_to_plot = DPhijj;
  if(observable=="DPhill") variable_to_plot = DPhill;
  if(observable=="MT") variable_to_plot = (MT)/1000;
  if(observable=="MET") variable_to_plot = (MET)/1000;
  if(observable == "Ml1j1") variable_to_plot = (Ml1j1)/1000;
  if(observable == "Ml1j0") variable_to_plot = (Ml1j0)/1000;
  if(observable == "Ml0j1") variable_to_plot = (Ml0j1)/1000;
  if(observable == "Ml0j0") variable_to_plot = (Ml0j0)/1000;
  if(observable=="jet0_eta") variable_to_plot = jet0_eta;
  if(observable=="jet1_eta") variable_to_plot = jet1_eta;
  if(observable=="nJets") variable_to_plot = nJets;
  if(observable=="lep0_pt") variable_to_plot = (lep0_pt)/1000;
  if(observable=="lep1_pt") variable_to_plot = (lep1_pt)/1000;
  if(observable=="lep0_eta") variable_to_plot = lep0_eta;
  if(observable=="lep1_eta") variable_to_plot = lep1_eta;
  if(observable=="Ptll") variable_to_plot = Ptll/1000;

  return variable_to_plot;
}


inline std::string xAxisTitle(std::string observable)
{
  std::string title;
  if(observable == "Mjj") title = "m_{jj} [GeV]";
  if(observable == "Mll") title = "m_{#ell#ell} [GeV]";
  if(observable == "DYjj") title = "#Delta y_{jj}";
  if(observable == "DYll") title = "#Delta y_{#ell#ell}";
  if(observable == "jet0_pt") title = "leading jet #it{p}_{T} [GeV]";
  if(observable == "jet1_pt") title = "subleading jet #it{p}_{T} [GeV]";
  if(observable == "jet2_pt") title = "third jet #it{p}_{T} [GeV]";
  if(observable == "bdt_vbf") title = "BDT output VBF vs Top+WW";
  if(observable == "bdt_TopWWAll") title = "BDT output Top+WW";
  if(observable == "costhetastar") title = "|cos#theta^{*}|";
  if(observable == "ptTot") title = "#it{p}_{T}^{Tot} [GeV]";
  if(observable == "pt_H") title = "#it{p}_{T}^{H} [GeV]";
  if(observable == "sumOfCentralitiesL") title = "sumOfCentralitiesL";
  if(observable == "SignedDPhijj") title = "#Delta#phi_{jj}";
  if(observable == "DPhijj") title = "|#Delta#phi_{jj}|";
  if(observable == "DPhill") title = "#Delta#phi_{#ell#ell} [rad]";
  if(observable == "MT") title = "m_T";
  if(observable == "MET") title = "E_{T}^{miss} [GeV]";
  if(observable == "Ml1j1") title = "m_{#el_{1}j_{1}} [GeV]";
  if(observable == "Ml1j0") title = "m_{#el_{1}j_{0}} [GeV]";
  if(observable == "Ml0j1") title = "m_{#el_{0}j_{1}} [GeV]";
  if(observable == "Ml0j0") title = "m_{#el_{0}j_{0}} [GeV]";
  if(observable == "jet0_eta") title = "leading jet #eta";
  if(observable == "jet1_eta") title = "subleading jet #eta";
  if(observable == "nJets") title = "n_{jet}";
  if(observable == "lep0_pt") title = "leading lepton #it{p}_{T} [GeV]";
  if(observable == "lep1_pt") title = "subleading lepton #it{p}_{T} [GeV]";
  if(observable == "lep0_eta") title = "leading lepton #it{#eta}";
  if(observable == "lep1_eta") title = "subleading lepton #it{#eta}";
  if(observable == "Ptll") title = "P_{t}^{#ell#ell} [GeV]";

  return title;
}

#endif
