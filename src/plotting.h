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

  TH1F* h_Fakes_over;
  TH1F* h_WW_over;
  TH1F* h_NonWW_over;
  TH1F* h_ttbar_over;
  TH1F* h_singleTop_over;
  TH1F* h_vbf_over;
  TH1F* h_ggf_over;
  TH1F* h_Zjets_over;
  TH1F* h_vh_over;
  TH1F* h_htt_over;
  //TH1F* h_data_over;

  inline std::string getSampleName(std::string sample);
  inline void setObsName(std::string observable){m_obsName = observable;};
  inline std::string getObsName(){return m_obsName;};
  inline void setRegionName(std::string region){m_regionName=region;};
  inline std::string getRegionName(){return m_regionName;};

  TH1F* getNominalHisto(std::string sample);
  TH1F* getNominalHisto(std::string sample, std::vector<float> mcChannelNumber);
  TH1F* DrawOverflow(TH1F* h);

  inline void setBins(bool forPaper);
 
  void PlotsforNote(std::string region, std::string observable, bool unblind, bool overflow=false);
  void PlotsforPaper(std::string region, std::string observable, bool unblind);
  plotting(std::string region, std::string observable, bool unblind, bool forPaper); 


private:
  std::string m_obsName;
  std::string m_regionName;
  size_t m_nbins;
  float m_xmin;
  float m_xmax;
  double *m_binsEdges;

};


inline void plotting::setBins(bool forPaper)
{ 

  if(!forPaper){
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