#ifndef GET_SYSTEMATICS_H
#define GET_SYSTEMATICS_H

#include "TreeReader.C"

class TreeReader;
class GetSystematics{
public:

  TH1F* h_nominal;

  std::vector<TH1F*> h_JER_up;
  std::vector<TH1F*> h_JER_down;

  TH1F* h_Fakes;
  TH1F* h_WW;
  TH1F* h_NonWW;
  TH1F* h_WWEW;
  TH1F* h_top1;
  TH1F* h_top2;
  TH1F* h_vbf;
  TH1F* h_ggf;
  TH1F* h_vh;
  TH1F* h_htt;
  TH1F* h_Zjets;
  TH1F* h_Vgamma;
  TH1F* h_data;

  inline std::string getSampleName(std::string sample);
  inline void setObsName(std::string observable){m_obsName = observable;};
  inline std::string getObsName(){return m_obsName;};
  inline void setRegionName(std::string region){m_regionName=region;};
  inline std::string getRegionName(){return m_regionName;};
  inline bool isForPaper(){return m_forPaper;};
  TH1F* getNominalHisto(std::string sample, bool lxplus);
  TH1F* getNominalHisto(std::string sample, std::string campaign);
  TH1F* getSysHist(bool sys_up, std::string sample, std::string sysName, bool lxplus);
  TH1F* getMETHist(bool sys_up, std::string sample, std::string sysName, bool lxplus);
  TH1F* getSysHist(bool sys_up, std::string sample, std::string sysName, std::string campaign);
  TH1F* getMETHist(bool sys_up, std::string sample, std::string sysName, std::string campaign);

  inline void setBins(bool forPaper);

  GetSystematics(std::string region, std::string observable, std::string sample, std::string campaign, std::string sys_name, std::string JER0, std::string MET0, std::string other0, std::string forPaper0);

private:
  std::string m_obsName;
  std::string m_regionName;
  bool m_forPaper;
  size_t m_nbins;
  float m_xmin;
  float m_xmax;
  double *m_binsEdges;
};

inline std::string GetSystematics::getSampleName(std::string sample)
{

  if(sample=="diboson1" || sample=="diboson2" || sample=="WWEW") return "diboson";
  if(sample=="top1" || sample=="top2") return "top";

  return sample;
}

inline void GetSystematics::setBins(bool forPaper)
{ 

  if(!forPaper){
    if(m_obsName=="bdt_vbf" || m_obsName=="bdt_TopWWAll" || m_obsName=="bdt_ggFCR1" || m_obsName=="bdt_ggFCR2" || m_obsName=="bdt_ggFCR3")
    {
      m_nbins = 20; 
      m_xmin = -1;
      m_xmax = 1;
    }
    if(m_obsName=="MET" || m_obsName=="pt_H")
    {
      m_nbins = 25;
      m_xmin = 0.;
      m_xmax = 250;
    }
    if(m_obsName=="MT")
    {
      //m_nbins = 5;
      //m_xmin = 40; 
      //m_xmax = 150;
      m_nbins = 10;
      m_xmin = 0;
      m_xmax = 250;
    }
    if(m_obsName=="sumOfCentralitiesL")
    {
      m_nbins = 30;
      m_xmin = 0;
      m_xmax = 6;
    }
    if(m_obsName=="ptTot")
    {
      m_nbins = 16;
      m_xmin = 0.;
      m_xmax = 80.;
    }
    if(m_obsName=="lep0_pt" || m_obsName=="jet0_pt")
    {
      m_nbins = 30;
      m_xmin = 0;
      m_xmax = 310;
    }
    if(m_obsName=="jet2_pt")
    {
      m_nbins = 20;
      m_xmin = 0;
      m_xmax = 100;
    }
    if(m_obsName=="lep1_pt" || m_obsName=="jet1_pt")
    {
      m_nbins = 20;
      m_xmin = 10;
      m_xmax = 210;
    }
    if(m_obsName=="lep0_eta" || m_obsName=="lep1_eta")
    {
      m_nbins = 12;
      m_xmin = -3;
      m_xmax = 3;
    }
    if(m_obsName=="jet0_eta" || m_obsName=="jet1_eta")
    {
      m_nbins = 12;
      m_xmin = -4.5;
      m_xmax = 4.5;
    }
    if(m_obsName=="Mll" || m_obsName=="Ptll")
    {
      m_nbins = 20;
      m_xmin = 0;
      m_xmax = 200;
    }
    if(m_obsName=="DPhill")
    {
      m_nbins = 10;
      m_xmin = 0.;
      m_xmax = 3.14;
    }
    if(m_obsName=="DYll" || m_obsName=="DYjj")
    {
      m_nbins = 18;
      m_xmin = 0;
      m_xmax = 9;
    }
    if(m_obsName=="costhetastar")
    {
      m_nbins = 20;
      m_xmin = 0;
      m_xmax = 1.;
    }
    if(m_obsName=="Mjj")
    {
      m_nbins = 25;
      m_xmin = 0; 
      m_xmax = 2500;
    }
    if(m_obsName=="DPhijj")
    {
      m_nbins = 10;
      m_xmin = 0;
      m_xmax = TMath::Pi();
    }
    if(m_obsName=="SignedDPhijj")
    {
      m_nbins = 20;
      m_xmin = -1*TMath::Pi();
      m_xmax = TMath::Pi();
    }
    if(m_obsName=="mtt")
    {
      m_nbins = 10;
      m_xmin = 0;
      m_xmax = 200;
    }
    if(m_obsName=="pt_H")
    {
      m_nbins = 25;
      m_xmin = 0;
      m_xmax = 250;
    }
    if(m_obsName=="Ml0j0" || m_obsName=="Ml0j1")
    {
      m_nbins = 20;
      m_xmin = 0;
      m_xmax = 600;
    }
    if(m_obsName=="Ml1j1" || m_obsName=="Ml1j0")
    {
      m_nbins = 20; 
      m_xmin = 0;
      m_xmax = 500;
    }
    if(m_obsName=="nJets")
    {
      m_nbins = 10;
      m_xmin = 0;
      m_xmax = 10;
    }
  }
  else{
    if(m_obsName=="bdt_vbf" || m_obsName=="bdt_vbf_Mjj" || m_obsName=="bdt_vbf_Mll" || m_obsName=="bdt_vbf_DYjj" || m_obsName=="bdt_vbf_DYll" || m_obsName=="bdt_vbf_DPhijj" || m_obsName=="bdt_vbf_DPhill" || m_obsName=="bdt_vbf_jet0_pt" || m_obsName=="bdt_vbf_jet1_pt") //SR1
    {
      m_nbins = 4;
      m_binsEdges = new double[m_nbins+1]{0.5, 0.7, .86, .94, 1.};
    }
    if(m_obsName == "bdt_TopWWAll" || m_obsName=="bdt_ggFCR1")
    {
      m_nbins = 4;
      m_binsEdges = new double[m_nbins+1]{-1., -0.5, 0, 0.5, 1.};
    }
    if(m_obsName=="ptTot")
    {
      m_nbins = 12;
      m_binsEdges = new double[m_nbins+1]{0.,5.,10.,15.,20.,25.,30.,35.,40.,45.,50.,55.,60.};
    }

    if(m_obsName=="Mll")
    {
      m_nbins = 10;
      m_binsEdges = new double[m_nbins+1]{0.,20.,40.,60.,80.,100.,120.,140.,160.,180.,200.};
    }
    if(m_obsName=="Mjj")
    {
      m_nbins = 5;
      m_binsEdges = new double[m_nbins+1]{450, 950, 1200, 1500, 2200, 6000};
     // m_binsEdges = new double[m_nbins+1]{450, 700, 950, 1200, 1500, 2200, 6000};
     // m_nbins = 10;
     // m_binsEdges = new double[m_nbins+1]{0.,100.,200.,300.,400.,500.,600.,700.,800.,900.,1000.};
    }
    if(m_obsName=="pt_H")
    {
      m_nbins = 5;
      m_binsEdges = new double[m_nbins+1]{0, 80, 120, 160, 260, 850};
    }
    if(m_obsName=="DYll")
    {
      m_nbins = 6;
      m_binsEdges = new double[m_nbins+1]{0,1.5,3.,4.5,6.,7.5,9.};
    }
    if(m_obsName=="DYjj")
    {
      m_nbins = 5;
      m_binsEdges = new double[m_nbins+1]{2.1, 4.0, 5, 5.5, 6.25, 9};
     // m_binsEdges = new double[m_nbins+1]{2.1, 4.0, 4.375, 5, 5.5, 6.25, 9};
      //for the problematic theory 
      //m_nbins = 9;
      //m_binsEdges = new double[m_nbins+1]{0,1.,2.,3.,4.,5.,6.,7.,8.,9.};
    }
    if(m_obsName=="DPhill")
    {
      m_nbins = 5;
      m_binsEdges = new double[m_nbins+1]{0, 0.2, 0.4, 0.6, 0.8, 1.4};
    }
    if(m_obsName == "SignedDPhijj")
    {
      m_nbins = 4;
      m_binsEdges = new double[m_nbins+1]{-3.14, -1.57, 0, 1.57, 3.14};
    }
    if(m_obsName=="costhetastar")
    {
      m_nbins = 10;
      m_binsEdges = new double[m_nbins+1]{0,0.1,0.2,0.3,0.4,0.5,0.6,0.7,0.8,0.9,1.};
    }
    if(m_obsName=="Ptll")
    {
      m_nbins = 5;
      m_binsEdges = new double[m_nbins+1]{0, 60, 80, 100, 140, 1000};
    }
    if(m_obsName=="jet0_pt")
    {
      m_nbins = 9;
      m_binsEdges = new double[m_nbins+1]{31.,62.,93.,124.,155.,186.,217.,248.,279.,310.};
    }
    if(m_obsName=="jet1_pt")
    {
      m_nbins = 5;
      m_binsEdges = new double[m_nbins+1]{30, 45, 60, 90, 120, 350};
    }
    if(m_obsName=="lep0_pt")
    {
      m_nbins = 10;
      m_binsEdges = new double[m_nbins+1]{0.,31.,62.,93.,124.,155.,186.,217.,248.,279.,310.};
    }
    if(m_obsName=="lep1_pt")
    {
      m_nbins = 10;
      m_binsEdges = new double[m_nbins+1]{10,30,50,70,90,110,130,150,170,190,210};
    }
  }
  
}

#endif