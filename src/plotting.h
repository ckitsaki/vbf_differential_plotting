#ifndef PLOTTING_H
#define PLOTTING_H

#include "GetSystematics.C"

class TreeReader;
class GetSystematics;
class plotting {
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
  TH1F* h_ttbar1;
  TH1F* h_ttbar2;
  TH1F* h_singleTop1;
  TH1F* h_singleTop2;
  TH1F* h_vbf;
  TH1F* h_ggf;
  TH1F* h_vh;
  TH1F* h_htt;
  TH1F* h_Zjets;
  TH1F* h_Vgamma;
  TH1F* h_data;

  TGraphAsymmErrors* h_data_stat;

  TPad* pad1;
  TPad* pad2;
  TLegend* legend;

  inline std::string getSampleName(std::string sample);
  inline void setObsName(std::string observable){m_obsName = observable;};
  inline std::string getObsName(){return m_obsName;};
  inline void setRegionName(std::string region){m_regionName=region;};
  inline std::string getRegionName(){return m_regionName;};
  inline float getYMin(){return m_yminimum;};
  inline float getYMax(){return m_ymaximum;};
  inline void setYMax(float maximum){m_ymaximum = maximum;};
  inline void setXMax(float maximum){m_xmaximum = maximum;};
  inline void setXMin(float minimum){m_xminimum = minimum;};
  inline void setYminRatio(float y_min){m_y_ratio_min = y_min;};
  inline void setYmaxRatio(float y_max){m_y_ratio_max = y_max;};
  inline void setYaxisRanges();
  inline void setXaxisRanges();

  TH1F* getNominalHisto(std::string sample);
  TH1F* getNominalHisto(std::string sample, std::vector<float> mcChannelNumber);
  TH1F* getTheoryHisto(std::string sample, std::string theo_sys, bool isUp);

  inline void setBins(bool forPaper);
 
  void PlotsforNote(std::string region, std::string observable, bool unblind, bool addTheo);
  void PlotsforPaper(std::string region, std::string observable, bool unblind);
  plotting(std::string region, std::string observable, bool unblind, bool forPaper, bool setAxesLimits, bool addTheo); 


private:
  std::string m_obsName;
  std::string m_regionName;
  size_t m_nbins;
  float m_xmin;
  float m_xmax;
  double *m_binsEdges;
  float m_yminimum;
  float m_ymaximum;
  float m_xminimum;
  float m_xmaximum;
  float m_y_ratio_min=0.;
  float m_y_ratio_max=3.;

};

inline void plotting::setXaxisRanges()
{
  if(m_obsName=="lep0_eta" || m_obsName=="lep1_eta" || m_obsName=="jet0_eta" || m_obsName=="jet1_eta") m_xminimum = -3.;
  else m_xminimum=0;

  m_xmaximum = m_xmax;

}

inline void plotting::setYaxisRanges()
{
  m_yminimum=0;
  if(m_regionName=="SR")
  {
    m_yminimum = 10e-04;
    if(m_obsName=="MT" || m_obsName=="jet2_pt" || m_obsName=="nJets" || m_obsName=="jet1_pt" || m_obsName=="Ml1j1" || m_obsName=="Ptll") m_ymaximum = 10e+08;
    else m_ymaximum = 10e+06;
  }
  if(m_regionName=="DYCR")
  {
    if(m_obsName=="mtt" || m_obsName=="lep1_pt" || m_obsName=="DYll") m_ymaximum = 400;
    else if(m_obsName=="Mll" )m_ymaximum = 300;
    else if(m_obsName=="MT") m_ymaximum = 500;
    else if(m_obsName=="pt_H" || m_obsName=="SignedDPhijj" || m_obsName=="costhetastar" || m_obsName=="jet1_pt") m_ymaximum=100;
    else m_ymaximum = 200;
  }
  if(m_regionName=="TopCR")
  {
    if(m_obsName=="Mjj" || m_obsName=="DYll" ) m_ymaximum = 60000;
    else if(m_obsName=="lep1_pt" || m_obsName=="jet1_pt" || m_obsName=="jet0_eta" || m_obsName=="ptTot" || m_obsName=="DYjj" || m_obsName=="MT") m_ymaximum=40000;
    else if(m_obsName=="pt_H" || m_obsName=="Mll" ) m_ymaximum=15000;
    else m_ymaximum = 20000;
  }
  if(m_regionName=="WWCR")
  {
    if(m_obsName=="lep0_pt" || m_obsName=="lep1_pt" || m_obsName=="Ptll" || m_obsName=="lep0_eta" || m_obsName=="lep1_eta") m_ymaximum=3000;
    else if(m_obsName=="nJets" || m_obsName=="DYll" || m_obsName=="DYjj") m_ymaximum=15000;
    else if(m_obsName=="Mll" || m_obsName=="jet0_pt" || m_obsName=="Ml0j0" || m_obsName=="MET" || m_obsName=="SignedDPhijj" || m_obsName=="pt_H" || m_obsName=="sumOfCentralitiesL") m_ymaximum=2000;

    else m_ymaximum=10000;
  }
  if(m_regionName=="ggFCR1")
  {
    if(m_obsName=="nJets" || m_obsName=="DYjj") m_ymaximum=20000;
    else if(m_obsName=="Ptll" || m_obsName=="lep0_eta" || m_obsName=="lep1_eta" || m_obsName=="Mll" || m_obsName=="jet0_pt" || m_obsName=="MET" || m_obsName=="DPhijj" || m_obsName=="SignedDPhijj" || m_obsName=="costhetastar" || m_obsName=="pt_H") m_ymaximum=5000;
    else m_ymaximum=10000;
  }

  if(m_regionName=="ggFCR2")
  {
    if(m_obsName=="pt_H" || m_obsName=="costhetastar" || m_obsName=="SignedDPhijj" || m_obsName=="MET" || m_obsName=="jet0_pt") m_ymaximum=1000;
    else if(m_obsName=="lep1_pt" || m_obsName=="nJets" || m_obsName=="Mjj" || m_obsName=="DYjj" || m_obsName=="DPhill" || m_obsName=="DYll" || m_obsName=="jet1_pt") m_ymaximum=3000;
    else m_ymaximum = 2000;
  }

  if(m_regionName=="ggFCR3")
  {
    if(m_obsName=="lep0_pt" || m_obsName=="MT" || m_obsName=="DPhill") m_ymaximum = 20000;
    else if(m_obsName=="lep1_pt" || m_obsName=="DYll") m_ymaximum = 30000;
    else if(m_obsName=="costhetastar") m_ymaximum = 10000;
    else m_ymaximum=15000;
  }
}

inline void plotting::setBins(bool forPaper)
{ 

  if(!forPaper){
    if(m_obsName=="MET" || m_obsName=="pt_H")
    {
      m_nbins = 25;
      m_xmin = 0.;
      m_xmax = 250;
    }
    if(m_obsName=="MT")
    {
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
    if(m_obsName=="pTH")
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
    if(m_obsName=="Mll")
    {
      m_nbins = 5;
      m_binsEdges = new double[m_nbins+1]{10, 20, 30, 40, 55, 200};
    }
    if(m_obsName=="Mjj")
    {
      m_nbins = 6;
      m_binsEdges = new double[m_nbins+1]{450, 700, 950, 1200, 1500, 2200, 2500};
    }
    if(m_obsName=="pTH")
    {
      m_nbins = 6;
      m_binsEdges = new double[m_nbins+1]{0, 80, 120, 160, 200, 260, 850};
    }
    if(m_obsName=="DYll")
    {
      m_nbins = 5;
      m_binsEdges = new double[m_nbins+1]{0, 0.4, 0.6, 0.8, 1., 9.};
    }
    if(m_obsName=="DYjj")
    {
      m_nbins = 6;
      m_binsEdges = new double[m_nbins+1]{2.1, 4.0, 4.375, 5, 5.5, 6.25, 7};
    }
    if(m_obsName=="DPhill")
    {
      m_nbins = 5;
      m_binsEdges = new double[m_nbins+1]{0, 0.2, 0.4, 0.6, 0.8, 1.4};
    }
    if(m_obsName == "SignedDPhijj")
    {
      m_nbins = 8;
      m_binsEdges = new double[m_nbins+1]{-3.14, -2.36, -1.57, -0.786, 0, 0.786, 1.57, 2.36, 3.14};
    }
    if(m_obsName=="costhetastar")
    {
      m_nbins = 8;
      m_binsEdges = new double[m_nbins+1]{0, 0.0625, 0.125, 0.1875, 0.25, 0.3125, 0.315, 0.375, 1.};
    }
    if(m_obsName=="Ptll")
    {
      m_nbins = 5;
      m_binsEdges = new double[m_nbins+1]{0, 60, 80, 100, 140, 1000};
    }
    if(m_obsName=="jet0_pt")
    {
      m_nbins = 5;
      m_binsEdges = new double[m_nbins+1]{30, 90, 120, 160, 220, 310};
    }
    if(m_obsName=="jet1_pt")
    {
      m_nbins = 5;
      m_binsEdges = new double[m_nbins+1]{30, 45, 60, 90, 120, 210};
    }
    if(m_obsName=="lep0_pt")
    {
      m_nbins = 6;
      m_binsEdges = new double[m_nbins+1]{22, 40, 50, 60, 70, 100, 500};
    }
    if(m_obsName=="lep1_pt")
    {
      m_nbins = 5;
      m_binsEdges = new double[m_nbins+1]{15, 22, 30, 40, 50, 200};
    }
  }
  
}


inline std::string plotting::getSampleName(std::string sample)
{

  if(sample=="diboson1" || sample=="diboson2" || sample=="WWEW") return "diboson";
  if(sample=="top1" || sample=="top2") return "top";
  if(sample=="Fakes") return "Fakes";
  if(sample=="Vgamma") return "Vgamma";
  if(sample=="Zjets") return "Zjets";
  if(sample=="ggf") return "ggf";
  if(sample=="vbf") return "vbf";
  if(sample=="vh") return "vh";
  if(sample=="htt") return "htt";

  return sample;
}

#endif