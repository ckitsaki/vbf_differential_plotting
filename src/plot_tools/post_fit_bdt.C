/*
/ YOU HAVE TO RUN ON LXPLUS
/ This script is really awful, but the output is nice! 
*/


#include "../Style/AtlasStyle.C"

TCanvas* DumpCanvasFromFile(std::string input, std::string canvasName)
{
  std::string filename = "/eos/user/c/chenj/Rivet/analysisbase/final_result/postfitResults/fitResults_"+input+".root";
  TFile* myfile = new TFile(filename.c_str(),"READ");
  TKey* key; TCanvas* canvas;
  TIter nextkey(myfile->GetListOfKeys());
  while( (key=(TKey*)nextkey()))
  {
    TObject* obj = key->ReadObj();    
    if(strstr(obj->GetName(), canvasName.c_str()))
    {
      std::cout<<"got canvas with name: "<< obj->GetName()<<std::endl;
      canvas = (TCanvas*)obj;
      break;
    }
  }
  myfile->Close();
  return canvas;
}

void chooseBinning(std::string input, std::string canvasName, int &nbins, double* &binEdges, int Nbins_SR1, int Nbins_SR2, bool differentChoice, bool bins20)
{
  if(canvasName=="fitRes_obs_x_CRZjets_MT_CRZjets_MT"){
    nbins = 5;
    binEdges= new double[nbins+1]{40,62,84,106,128,150};
  } 
  if(canvasName=="fitRes_obs_x_CRGGF1_bdt_ggFCR1_CRGGF1_bdt_ggFCR1"){
    nbins = 4;
    binEdges= new double[nbins+1]{-1,-0.5,0.,0.5,1};
  }
  if(input!="SignedDPhijj" && canvasName=="fitRes_obs_x_CRTop_" + std::to_string(Nbins_SR2-1) + "_bdt_TopWWAll_CRTop_" + std::to_string(Nbins_SR2-1) + "_bdt_TopWWAll"){
    nbins = 2;
    binEdges= new double[nbins+1]{-1,0,1};
  }
  
  if( canvasName=="fitRes_obs_x_SRVBF_" + std::to_string(Nbins_SR1-1) + "_bdt_vbf_" + input + "_SRVBF_" + std::to_string(Nbins_SR1-1) + "_bdt_vbf_" + input){
    nbins = 4;
    binEdges= new double[nbins+1]{0.5, 0.7, 0.86, 0.94, 1.0};
  } 
  if( (input=="SignedDPhijj" || input=="inc") && differentChoice && canvasName=="fitRes_obs_x_CRTop_" + std::to_string(Nbins_SR2-1) + "_bdt_TopWWAll_CRTop_" + std::to_string(Nbins_SR2-1) + "_bdt_TopWWAll")
  {
    nbins = 4;
    binEdges= new double[nbins+1]{-1,-0.5,0.,0.5,1.};
  }
  if(input=="DYjj" && differentChoice && canvasName=="fitRes_obs_x_SRVBF_" + std::to_string(Nbins_SR1-1) + "_bdt_vbf_" + input + "_SRVBF_" + std::to_string(Nbins_SR1-1) + "_bdt_vbf_" + input)
  {
    nbins = 3;
    binEdges= new double[nbins+1]{.5,.7,.86,1.};
  }

  if( input=="DYjj" && bins20 && canvasName=="fitRes_obs_x_SRVBF_" + std::to_string(0) + "_bdt_vbf_" + input + "_SRVBF_" + std::to_string(0) + "_bdt_vbf_" + input)
  {
    nbins = 19;
    binEdges = new double[nbins+1]{0.5, 0.7, 0.86, 0.94, 1.0, 1.2, 1.36, 1.44, 1.5, 1.7, 1.86, 1.94, 2., 2.2, 2.36, 2.44, 2.5, 2.7, 2.86, 3.};
  }

  if( (input=="Mjj" || input=="lep0_pt" || input=="costhetastar" || input=="DPhill" || input=="DYll"  ) && bins20 && canvasName=="fitRes_obs_x_SRVBF_" + std::to_string(0) + "_bdt_vbf_" + input + "_SRVBF_" + std::to_string(0) + "_bdt_vbf_" + input) 
  {
    nbins = 20;
    binEdges = new double[nbins+1]{0.5, 0.7, 0.86, 0.94, 1.0, 1.2, 1.36, 1.44, 1.5, 1.7, 1.86, 1.94, 2., 2.2, 2.36, 2.44, 2.5, 2.7, 2.86, 2.94, 3.};
  }

  if( (input=="Mjj" || input=="lep0_pt" || input=="costhetastar" || input=="DPhill" || input=="DYll" || input=="DYjj") && bins20 && canvasName=="fitRes_obs_x_CRTop_" + std::to_string(0) + "_bdt_TopWWAll_CRTop_" + std::to_string(0) + "_bdt_TopWWAll") 
  {
    nbins = 10;
    binEdges = new double[nbins+1]{-1, 0., 1., 2., 3., 4., 5., 6., 7., 8., 9.};
  }

  if( (input=="SignedDPhijj") && bins20 && canvasName=="fitRes_obs_x_CRTop_" + std::to_string(0) + "_bdt_TopWWAll_CRTop_" + std::to_string(0) + "_bdt_TopWWAll") 
  {
    nbins = 16;
    binEdges = new double[nbins+1]{-1, -0.5, 0, 0.5, 1., 1.5, 2., 2.5, 3., 3.5, 4., 4.5, 5., 5.5, 6., 6.5, 7.};
  }

   if( (input=="lep1_pt" || input=="jet0_pt" || input=="jet1_pt" || input=="pt_H" || input=="Ptll" || input=="Mll" || input=="SignedDPhijj") && bins20 && canvasName=="fitRes_obs_x_SRVBF_" + std::to_string(0) + "_bdt_vbf_" + input + "_SRVBF_" + std::to_string(0) + "_bdt_vbf_" + input) 
  {
    nbins = 16;
    binEdges = new double[nbins+1]{0.5, 0.7, 0.86, 0.94, 1.0, 1.2, 1.36, 1.44, 1.5, 1.7, 1.86, 1.94, 2., 2.2, 2.36, 2.44, 2.5};
  }

  if( (input=="lep1_pt" || input=="jet0_pt" || input=="jet1_pt" || input=="pt_H" || input=="Ptll" || input=="Mll" ) && bins20 && canvasName=="fitRes_obs_x_CRTop_" + std::to_string(0) + "_bdt_TopWWAll_CRTop_" + std::to_string(0) + "_bdt_TopWWAll") 
  {
    nbins = 8;
    binEdges = new double[nbins+1]{-1, 0., 1., 2., 3., 4., 5., 6., 7.};
  }
}

std::string obs_title(std::string observable)
{
  if(observable=="Mjj") return "#it{m}_{jj}";
  if(observable=="Mll") return "#it{m}_{ll}";
  if(observable=="DYll") return "|#it{#Deltay}_{ll}|";
  if(observable=="DYjj") return "|#it{#Deltay}_{jj}|";
  if(observable=="lep0_pt") return "#it{p}_{T}^{l_{1}}";
  if(observable=="lep1_pt") return "#it{p}_{T}^{l_{2}}";
  if(observable=="jet0_pt") return "#it{p}_{T}^{j_{1}}";
  if(observable=="jet1_pt") return "#it{p}_{T}^{j_{2}}";
  if(observable=="SignedDPhijj") return "#it{#Delta#phi}_{jj}";
  if(observable=="DPhill") return "|#it{#Delta#phi}_{ll}|";
  if(observable=="costhetastar") return "#it{cos(#theta}_{#eta}*#it{)}";
  if(observable=="Ptll") return "#it{p}_{T}^{ll}";
  if(observable=="pt_H") return "#it{p}_{T}^{H}";

  return "";
}

RooCurve* GetRooCurveFromFile(std::string sample, TCanvas* canvas)
{
  RooCurve* rc = (RooCurve*)canvas->FindObject(sample.c_str());

  return rc;
}
void post_fit(std::string input="Mjj", int Nbins_SR1=5, int Nbins_SR2=5, bool doScale=false)
{
  gROOT->SetBatch(kTRUE);
  SetAtlasStyle();
  
  // ============== MT in ZjetsCR ====================== //
  std::string canvasName="fitRes_obs_x_CRZjets_MT_CRZjets_MT";
  TCanvas* can_DYCR = DumpCanvasFromFile(input, canvasName);

  RooCurve* rc_Zjets_DYCR = GetRooCurveFromFile("Zjets", can_DYCR);
  RooCurve* rc_vh_DYCR = GetRooCurveFromFile("vh", can_DYCR);
  RooCurve* rc_htt_DYCR = GetRooCurveFromFile("htt", can_DYCR);
  RooCurve* rc_vbf_DYCR = GetRooCurveFromFile("vbf", can_DYCR);
  RooCurve* rc_top_DYCR = GetRooCurveFromFile("top", can_DYCR);
  RooCurve* rc_diboson_DYCR = GetRooCurveFromFile("diboson", can_DYCR);
  RooCurve* rc_ggf_DYCR = GetRooCurveFromFile("ggf", can_DYCR);
  RooCurve* rc_Fakes_DYCR = GetRooCurveFromFile("Fakes", can_DYCR);
  RooCurve* rc_Vgamma_DYCR = GetRooCurveFromFile("Vgamma", can_DYCR);
  RooCurve* rc_sysErrorPdf_DYCR = GetRooCurveFromFile("sysErrorPdf", can_DYCR);
  
  RooHist* rh_Data_DYCR = (RooHist*)can_DYCR->FindObject("Data");

  // convert RooCurve -> TH1
  int nbins_DYCR;
  double *binEdges_DYCR;
  chooseBinning(input, canvasName, nbins_DYCR, binEdges_DYCR, 0, 0, false, false);

  TH1D* h_Zjets_DYCR = new TH1D("h_Zjets_DYCR", "", nbins_DYCR, binEdges_DYCR);
  TH1D* h_vh_DYCR = new TH1D("h_vh_DYCR", "", nbins_DYCR, binEdges_DYCR);
  TH1D* h_htt_DYCR = new TH1D("h_htt_DYCR", "", nbins_DYCR, binEdges_DYCR);
  TH1D* h_vbf_DYCR = new TH1D("h_vbf_DYCR", "", nbins_DYCR, binEdges_DYCR);
  TH1D* h_top_DYCR = new TH1D("h_top_DYCR", "", nbins_DYCR, binEdges_DYCR);
  TH1D* h_diboson_DYCR = new TH1D("h_diboson_DYCR", "", nbins_DYCR, binEdges_DYCR);
  TH1D* h_ggf_DYCR = new TH1D("h_ggf_DYCR", "", nbins_DYCR, binEdges_DYCR);
  TH1D* h_Fakes_DYCR = new TH1D("h_Fakes_DYCR", "", nbins_DYCR, binEdges_DYCR);
  TH1D* h_Vgamma_DYCR = new TH1D("h_Vgamma_DYCR", "", nbins_DYCR, binEdges_DYCR);
  TH1D* h_data_DYCR = new TH1D("h_data_DYCR", "", nbins_DYCR, binEdges_DYCR);

  TGraphAsymmErrors* h_sysErrorPdf_DYCR = new TGraphAsymmErrors();

  // ============== CRGGF =================================== //
  canvasName="fitRes_obs_x_CRGGF1_bdt_ggFCR1_CRGGF1_bdt_ggFCR1";
  TCanvas* can_CRGGF = DumpCanvasFromFile(input, canvasName);
  RooCurve* rc_Zjets_CRGGF = GetRooCurveFromFile("Zjets", can_CRGGF);
  RooCurve* rc_vh_CRGGF = GetRooCurveFromFile("vh", can_CRGGF);
  RooCurve* rc_htt_CRGGF = GetRooCurveFromFile("htt", can_CRGGF);
  RooCurve* rc_vbf_CRGGF = GetRooCurveFromFile("vbf", can_CRGGF);
  RooCurve* rc_top_CRGGF = GetRooCurveFromFile("top", can_CRGGF);
  RooCurve* rc_diboson_CRGGF = GetRooCurveFromFile("diboson", can_CRGGF);
  RooCurve* rc_ggf_CRGGF = GetRooCurveFromFile("ggf", can_CRGGF);
  RooCurve* rc_Fakes_CRGGF = GetRooCurveFromFile("Fakes", can_CRGGF);
  RooCurve* rc_Vgamma_CRGGF = GetRooCurveFromFile("Vgamma", can_CRGGF);
  RooCurve* rc_sysErrorPdf_CRGGF = GetRooCurveFromFile("sysErrorPdf", can_CRGGF);

  RooHist* rh_Data_CRGGF = (RooHist*)can_CRGGF->FindObject("Data");

  // convert RooCurve -> TH1
  int nbins_CRGGF;
  double *binEdges_CRGGF;
  chooseBinning(input, canvasName, nbins_CRGGF, binEdges_CRGGF, 0, 0, false, false);
  TH1D* h_Zjets_CRGGF = new TH1D("h_Zjets_CRGGF", "", nbins_CRGGF, binEdges_CRGGF);
  TH1D* h_vh_CRGGF = new TH1D("h_vh_CRGGF", "", nbins_CRGGF, binEdges_CRGGF);
  TH1D* h_htt_CRGGF = new TH1D("h_htt_CRGGF", "", nbins_CRGGF, binEdges_CRGGF);
  TH1D* h_vbf_CRGGF = new TH1D("h_vbf_CRGGF", "", nbins_CRGGF, binEdges_CRGGF);
  TH1D* h_top_CRGGF = new TH1D("h_top_CRGGF", "", nbins_CRGGF, binEdges_CRGGF);
  TH1D* h_diboson_CRGGF = new TH1D("h_diboson_CRGGF", "", nbins_CRGGF, binEdges_CRGGF);
  TH1D* h_ggf_CRGGF = new TH1D("h_ggf_CRGGF", "", nbins_CRGGF, binEdges_CRGGF);
  TH1D* h_Fakes_CRGGF = new TH1D("h_Fakes_CRGGF", "", nbins_CRGGF, binEdges_CRGGF);
  TH1D* h_Vgamma_CRGGF = new TH1D("h_Vgamma_CRGGF", "", nbins_CRGGF, binEdges_CRGGF);
  TH1D* h_data_CRGGF = new TH1D("h_data_CRGGF", "", nbins_CRGGF, binEdges_CRGGF);

  TGraphAsymmErrors* h_sysErrorPdf_CRGGF = new TGraphAsymmErrors();

  // ================= SR2 =================================== //
  std::vector<RooCurve*> v_rc_Zjets_SR2, v_rc_vh_SR2, v_rc_htt_SR2, v_rc_vbf_SR2, v_rc_top_SR2, v_rc_diboson_SR2, v_rc_ggf_SR2, v_rc_Fakes_SR2, v_rc_Vgamma_SR2, v_rc_sysErrorPdf_SR2;
  std::vector<RooHist*> v_rh_data_SR2;
  std::vector<TH1D*> v_h_Zjets_SR2, v_h_vh_SR2, v_h_htt_SR2, v_h_vbf_SR2, v_h_top_SR2, v_h_diboson_SR2, v_h_ggf_SR2, v_h_Fakes_SR2, v_h_Vgamma_SR2, v_h_data_SR2;
  std::vector<TGraphAsymmErrors*> v_h_sysErr_SR2;
  for(int SR2bin=0; SR2bin<Nbins_SR2; SR2bin++) {
    canvasName="fitRes_obs_x_CRTop_" + std::to_string(SR2bin) + "_bdt_TopWWAll_CRTop_" + std::to_string(SR2bin) + "_bdt_TopWWAll";
    TCanvas* can_SR2_tmp = DumpCanvasFromFile(input, canvasName);
    v_rc_Zjets_SR2.push_back(GetRooCurveFromFile("Zjets", can_SR2_tmp));
    v_rc_vh_SR2.push_back(GetRooCurveFromFile("vh", can_SR2_tmp));
    v_rc_htt_SR2.push_back(GetRooCurveFromFile("htt", can_SR2_tmp));
    v_rc_vbf_SR2.push_back(GetRooCurveFromFile("vbf", can_SR2_tmp));
    v_rc_top_SR2.push_back(GetRooCurveFromFile("top", can_SR2_tmp));
    v_rc_diboson_SR2.push_back(GetRooCurveFromFile("diboson", can_SR2_tmp));
    v_rc_ggf_SR2.push_back(GetRooCurveFromFile("ggf", can_SR2_tmp));
    v_rc_Fakes_SR2.push_back(GetRooCurveFromFile("Fakes", can_SR2_tmp));
    v_rc_Vgamma_SR2.push_back(GetRooCurveFromFile("Vgamma", can_SR2_tmp));
    v_rc_sysErrorPdf_SR2.push_back(GetRooCurveFromFile("sysErrorPdf", can_SR2_tmp));
    v_rh_data_SR2.push_back((RooHist*)can_SR2_tmp->FindObject("Data"));
  }

  bool differentChoice=false;
  for(int ihisto = 0; ihisto<v_rc_vbf_SR2.size(); ihisto++)
  {
    int nbins_SR2;
    double *binEdges_SR2;
    if(input=="SignedDPhijj") differentChoice=true;

    chooseBinning(input, canvasName, nbins_SR2, binEdges_SR2, 0, Nbins_SR2, differentChoice, false);

    std::string histo_name_Zjets = "h_Zjets_" + std::to_string(ihisto) + "_SR2";
    TH1D* h_tmp_Zjets = new TH1D(histo_name_Zjets.c_str(), "", nbins_SR2, binEdges_SR2);
    v_h_Zjets_SR2.push_back(h_tmp_Zjets);

    std::string histo_name_vh = "h_vh_" + std::to_string(ihisto) + "_SR2";
    TH1D* h_tmp_vh = new TH1D(histo_name_vh.c_str(), "", nbins_SR2, binEdges_SR2);
    v_h_vh_SR2.push_back(h_tmp_vh);

    std::string histo_name_htt = "h_htt_" + std::to_string(ihisto) + "_SR2";
    TH1D* h_tmp_htt = new TH1D(histo_name_htt.c_str(), "", nbins_SR2, binEdges_SR2);
    v_h_htt_SR2.push_back(h_tmp_htt);

    std::string histo_name_vbf = "h_vbf_" + std::to_string(ihisto) + "_SR2";
    TH1D* h_tmp_vbf = new TH1D(histo_name_vbf.c_str(), "", nbins_SR2, binEdges_SR2);
    v_h_vbf_SR2.push_back(h_tmp_vbf);

    std::string histo_name_top = "h_top_" + std::to_string(ihisto) + "_SR2";
    TH1D* h_tmp_top = new TH1D(histo_name_top.c_str(), "", nbins_SR2, binEdges_SR2);
    v_h_top_SR2.push_back(h_tmp_top);

    std::string histo_name_diboson = "h_diboson_" + std::to_string(ihisto) + "_SR2";
    TH1D* h_tmp_diboson = new TH1D(histo_name_diboson.c_str(), "", nbins_SR2, binEdges_SR2);
    v_h_diboson_SR2.push_back(h_tmp_diboson);

    std::string histo_name_ggf = "h_ggf_" + std::to_string(ihisto) + "_SR2";
    TH1D* h_tmp_ggf = new TH1D(histo_name_ggf.c_str(), "", nbins_SR2, binEdges_SR2);
    v_h_ggf_SR2.push_back(h_tmp_ggf);

    std::string histo_name_Fakes = "h_Fakes_" + std::to_string(ihisto) + "_SR2";
    TH1D* h_tmp_Fakes = new TH1D(histo_name_Fakes.c_str(), "", nbins_SR2, binEdges_SR2);
    v_h_Fakes_SR2.push_back(h_tmp_Fakes);

    std::string histo_name_Vgamma = "h_Vgamma_" + std::to_string(ihisto) + "_SR2";
    TH1D* h_tmp_Vgamma = new TH1D(histo_name_Vgamma.c_str(), "", nbins_SR2, binEdges_SR2);
    v_h_Vgamma_SR2.push_back(h_tmp_Vgamma);

    std::string histo_name_sysErr = "h_sysErrorPdf_" + std::to_string(ihisto) + "_SR2";
    TGraphAsymmErrors* h_tmp_sysErr = new TGraphAsymmErrors();
    h_tmp_sysErr->SetName(histo_name_sysErr.c_str());
    v_h_sysErr_SR2.push_back(h_tmp_sysErr);

    std::string histo_name_data = "h_data_" + std::to_string(ihisto) + "_SR2";
    TH1D* h_tmp_data = new TH1D(histo_name_data.c_str(), "", nbins_SR2, binEdges_SR2);
    v_h_data_SR2.push_back(h_tmp_data);
  }

  // ================= SR1 =================================== //
  std::vector<RooCurve*> v_rc_Zjets_SR1, v_rc_vh_SR1, v_rc_htt_SR1, v_rc_vbf_SR1, v_rc_top_SR1, v_rc_diboson_SR1, v_rc_ggf_SR1, v_rc_Fakes_SR1, v_rc_Vgamma_SR1, v_rc_sysErrorPdf_SR1;
  std::vector<RooHist*> v_rh_data_SR1;
  std::vector<TH1D*> v_h_Zjets_SR1, v_h_vh_SR1, v_h_htt_SR1, v_h_vbf_SR1, v_h_top_SR1, v_h_diboson_SR1, v_h_ggf_SR1, v_h_Fakes_SR1, v_h_Vgamma_SR1, v_h_data_SR1;
  std::vector<TGraphAsymmErrors*> v_h_sysErr_SR1;
  for(int SR1bin=0; SR1bin<Nbins_SR1; SR1bin++) {
    canvasName="fitRes_obs_x_SRVBF_"+ std::to_string(SR1bin) +"_bdt_vbf_" + input + "_SRVBF_" + std::to_string(SR1bin) + "_bdt_vbf_" + input;
    TCanvas* can_SR1_tmp = DumpCanvasFromFile(input, canvasName);
    v_rc_Zjets_SR1.push_back(GetRooCurveFromFile("Zjets", can_SR1_tmp));
    v_rc_vh_SR1.push_back(GetRooCurveFromFile("vh", can_SR1_tmp));
    v_rc_htt_SR1.push_back(GetRooCurveFromFile("htt", can_SR1_tmp));
    v_rc_vbf_SR1.push_back(GetRooCurveFromFile("vbf", can_SR1_tmp));
    v_rc_top_SR1.push_back(GetRooCurveFromFile("top", can_SR1_tmp));
    v_rc_diboson_SR1.push_back(GetRooCurveFromFile("diboson", can_SR1_tmp));
    v_rc_ggf_SR1.push_back(GetRooCurveFromFile("ggf", can_SR1_tmp));
    v_rc_Fakes_SR1.push_back(GetRooCurveFromFile("Fakes", can_SR1_tmp));
    v_rc_Vgamma_SR1.push_back(GetRooCurveFromFile("Vgamma", can_SR1_tmp));
    v_rc_sysErrorPdf_SR1.push_back(GetRooCurveFromFile("sysErrorPdf", can_SR1_tmp));
    v_rh_data_SR1.push_back((RooHist*)can_SR1_tmp->FindObject("Data"));
  }
  
  differentChoice=false;
  
  for(int ihisto = 0; ihisto<v_rc_vbf_SR1.size(); ihisto++)
  {
    int nbins_SR1;
    double *binEdges_SR1;
    
    if(input=="DYjj" && ihisto==(v_rc_vbf_SR1.size()-1)){ differentChoice=true; }
    
    chooseBinning(input, canvasName, nbins_SR1, binEdges_SR1, Nbins_SR1, 0, differentChoice, false);

    std::string histo_name_Zjets = "h_Zjets_" + std::to_string(ihisto) + "_SR1";
    TH1D* h_tmp_Zjets = new TH1D(histo_name_Zjets.c_str(), "", nbins_SR1, binEdges_SR1);
    v_h_Zjets_SR1.push_back(h_tmp_Zjets);

    std::string histo_name_vh = "h_vh_" + std::to_string(ihisto) + "_SR1";
    TH1D* h_tmp_vh = new TH1D(histo_name_vh.c_str(), "", nbins_SR1, binEdges_SR1);
    v_h_vh_SR1.push_back(h_tmp_vh);

    std::string histo_name_htt = "h_htt_" + std::to_string(ihisto) + "_SR1";
    TH1D* h_tmp_htt = new TH1D(histo_name_htt.c_str(), "", nbins_SR1, binEdges_SR1);
    v_h_htt_SR1.push_back(h_tmp_htt);

    std::string histo_name_vbf = "h_vbf_" + std::to_string(ihisto) + "_SR1";
    TH1D* h_tmp_vbf = new TH1D(histo_name_vbf.c_str(), "", nbins_SR1, binEdges_SR1);
    v_h_vbf_SR1.push_back(h_tmp_vbf);

    std::string histo_name_top = "h_top_" + std::to_string(ihisto) + "_SR1";
    TH1D* h_tmp_top = new TH1D(histo_name_top.c_str(), "", nbins_SR1, binEdges_SR1);
    v_h_top_SR1.push_back(h_tmp_top);

    std::string histo_name_diboson = "h_diboson_" + std::to_string(ihisto) + "_SR1";
    TH1D* h_tmp_diboson = new TH1D(histo_name_diboson.c_str(), "", nbins_SR1, binEdges_SR1);
    v_h_diboson_SR1.push_back(h_tmp_diboson);

    std::string histo_name_ggf = "h_ggf_" + std::to_string(ihisto) + "_SR1";
    TH1D* h_tmp_ggf = new TH1D(histo_name_ggf.c_str(), "", nbins_SR1, binEdges_SR1);
    v_h_ggf_SR1.push_back(h_tmp_ggf);

    std::string histo_name_Fakes = "h_Fakes_" + std::to_string(ihisto) + "_SR1";
    TH1D* h_tmp_Fakes = new TH1D(histo_name_Fakes.c_str(), "", nbins_SR1, binEdges_SR1);
    v_h_Fakes_SR1.push_back(h_tmp_Fakes);

    std::string histo_name_Vgamma = "h_Vgamma_" + std::to_string(ihisto) + "_SR1";
    TH1D* h_tmp_Vgamma = new TH1D(histo_name_Vgamma.c_str(), "", nbins_SR1, binEdges_SR1);
    v_h_Vgamma_SR1.push_back(h_tmp_Vgamma);

    std::string histo_name_sysErr = "h_sysErrorPdf_" + std::to_string(ihisto) + "_SR1";
    TGraphAsymmErrors* h_tmp_sysErr = new TGraphAsymmErrors();
    h_tmp_sysErr->SetName(histo_name_sysErr.c_str());
    v_h_sysErr_SR1.push_back(h_tmp_sysErr);

    std::string histo_name_data = "h_data_" + std::to_string(ihisto) + "_SR1";
    TH1D* h_tmp_data = new TH1D(histo_name_data.c_str(), "", nbins_SR1, binEdges_SR1);
    v_h_data_SR1.push_back(h_tmp_data);

  }
 
  int icount=1;
  int counter=1;

  // ZjetsCR
  for(int ibin=(rc_Zjets_DYCR->GetN()-1)/2; ibin--;)
  {
    if(ibin<0) break;

    double zjets, vh, htt, vbf, top, diboson, ggf, fakes, vgamma = 0.;

    vgamma = rc_Vgamma_DYCR->GetPointY(rc_Zjets_DYCR->GetN()-2*icount);
    fakes =  rc_Fakes_DYCR->GetPointY(rc_Zjets_DYCR->GetN()-2*icount) - rc_Vgamma_DYCR->GetPointY(rc_Zjets_DYCR->GetN()-2*icount);
    ggf = rc_ggf_DYCR->GetPointY(rc_Zjets_DYCR->GetN()-2*icount) - rc_Fakes_DYCR->GetPointY(rc_Zjets_DYCR->GetN()-2*icount);
    diboson = rc_diboson_DYCR->GetPointY(rc_Zjets_DYCR->GetN()-2*icount) - rc_ggf_DYCR->GetPointY(rc_Zjets_DYCR->GetN()-2*icount);
    top = rc_top_DYCR->GetPointY(rc_Zjets_DYCR->GetN()-2*icount) - rc_diboson_DYCR->GetPointY(rc_Zjets_DYCR->GetN()-2*icount);
    vbf = rc_vbf_DYCR->GetPointY(rc_Zjets_DYCR->GetN()-2*icount) - rc_top_DYCR->GetPointY(rc_Zjets_DYCR->GetN()-2*icount);
    htt = rc_htt_DYCR->GetPointY(rc_Zjets_DYCR->GetN()-2*icount) - rc_vbf_DYCR->GetPointY(rc_Zjets_DYCR->GetN()-2*icount);
    vh = rc_vh_DYCR->GetPointY(rc_Zjets_DYCR->GetN()-2*icount) - rc_htt_DYCR->GetPointY(rc_Zjets_DYCR->GetN()-2*icount);
    zjets = rc_Zjets_DYCR->GetPointY(rc_Zjets_DYCR->GetN()-2*icount) - rc_vh_DYCR->GetPointY(rc_Zjets_DYCR->GetN()-2*icount);

    h_Zjets_DYCR->SetBinContent(ibin, zjets);
    h_vh_DYCR->SetBinContent(ibin, vh);
    h_htt_DYCR->SetBinContent(ibin, htt);
    h_vbf_DYCR->SetBinContent(ibin, vbf);
    h_top_DYCR->SetBinContent(ibin, top);
    h_diboson_DYCR->SetBinContent(ibin, diboson);
    h_ggf_DYCR->SetBinContent(ibin, ggf);
    h_Fakes_DYCR->SetBinContent(ibin, fakes);
    h_Vgamma_DYCR->SetBinContent(ibin, vgamma);

    h_data_DYCR->SetBinContent(icount, rh_Data_DYCR->GetPointY(icount-1));

    
    counter+=2;
    icount++;    
  }
  for(int ibin=0; ibin<h_Zjets_DYCR->GetNbinsX(); ibin++)
  {
    double y = h_Zjets_DYCR->GetBinContent(ibin+1)+h_vh_DYCR->GetBinContent(ibin+1)+h_htt_DYCR->GetBinContent(ibin+1)+h_vbf_DYCR->GetBinContent(ibin+1)+h_top_DYCR->GetBinContent(ibin+1)+h_diboson_DYCR->GetBinContent(ibin+1)+h_ggf_DYCR->GetBinContent(ibin+1)+h_Fakes_DYCR->GetBinContent(ibin+1)+h_Vgamma_DYCR->GetBinContent(ibin+1); 
    h_sysErrorPdf_DYCR->SetPoint(ibin, h_Zjets_DYCR->GetBinCenter(ibin+1), y);
    h_sysErrorPdf_DYCR->SetPointEXlow(ibin, h_Zjets_DYCR->GetBinWidth(ibin+1)/2);
    h_sysErrorPdf_DYCR->SetPointEXhigh(ibin, h_Zjets_DYCR->GetBinWidth(ibin+1)/2);

  }

  // error band DYCR
  int ibin = 0;
  double total_mc = (h_Zjets_DYCR->GetBinContent(ibin+1)+h_vh_DYCR->GetBinContent(ibin+1)+h_htt_DYCR->GetBinContent(ibin+1)+h_vbf_DYCR->GetBinContent(ibin+1)+h_top_DYCR->GetBinContent(ibin+1)+h_diboson_DYCR->GetBinContent(ibin+1)+h_ggf_DYCR->GetBinContent(ibin+1)+h_Fakes_DYCR->GetBinContent(ibin+1)+h_Vgamma_DYCR->GetBinContent(ibin+1) );
  h_sysErrorPdf_DYCR->SetPointEYlow(0, std::abs( total_mc-rc_sysErrorPdf_DYCR->GetPointY(30)));
  h_sysErrorPdf_DYCR->SetPointEYhigh(0, std::abs(total_mc-rc_sysErrorPdf_DYCR->GetPointY(3)));
  ibin =1;
  total_mc = (h_Zjets_DYCR->GetBinContent(ibin+1)+h_vh_DYCR->GetBinContent(ibin+1)+h_htt_DYCR->GetBinContent(ibin+1)+h_vbf_DYCR->GetBinContent(ibin+1)+h_top_DYCR->GetBinContent(ibin+1)+h_diboson_DYCR->GetBinContent(ibin+1)+h_ggf_DYCR->GetBinContent(ibin+1)+h_Fakes_DYCR->GetBinContent(ibin+1)+h_Vgamma_DYCR->GetBinContent(ibin+1) );
  h_sysErrorPdf_DYCR->SetPointEYlow(1, std::abs(total_mc-rc_sysErrorPdf_DYCR->GetPointY(28)));
  h_sysErrorPdf_DYCR->SetPointEYhigh(1, std::abs(total_mc-rc_sysErrorPdf_DYCR->GetPointY(5)));
  ibin = 2;
  total_mc = (h_Zjets_DYCR->GetBinContent(ibin+1)+h_vh_DYCR->GetBinContent(ibin+1)+h_htt_DYCR->GetBinContent(ibin+1)+h_vbf_DYCR->GetBinContent(ibin+1)+h_top_DYCR->GetBinContent(ibin+1)+h_diboson_DYCR->GetBinContent(ibin+1)+h_ggf_DYCR->GetBinContent(ibin+1)+h_Fakes_DYCR->GetBinContent(ibin+1)+h_Vgamma_DYCR->GetBinContent(ibin+1) );
  h_sysErrorPdf_DYCR->SetPointEYlow(2, std::abs(total_mc-rc_sysErrorPdf_DYCR->GetPointY(26)));
  h_sysErrorPdf_DYCR->SetPointEYhigh(2, std::abs(total_mc-rc_sysErrorPdf_DYCR->GetPointY(7)));
  ibin = 3;
  total_mc = (h_Zjets_DYCR->GetBinContent(ibin+1)+h_vh_DYCR->GetBinContent(ibin+1)+h_htt_DYCR->GetBinContent(ibin+1)+h_vbf_DYCR->GetBinContent(ibin+1)+h_top_DYCR->GetBinContent(ibin+1)+h_diboson_DYCR->GetBinContent(ibin+1)+h_ggf_DYCR->GetBinContent(ibin+1)+h_Fakes_DYCR->GetBinContent(ibin+1)+h_Vgamma_DYCR->GetBinContent(ibin+1) );
  h_sysErrorPdf_DYCR->SetPointEYlow(3, std::abs(total_mc-rc_sysErrorPdf_DYCR->GetPointY(24)));
  h_sysErrorPdf_DYCR->SetPointEYhigh(3, std::abs(total_mc-rc_sysErrorPdf_DYCR->GetPointY(9)));
  ibin = 4;
  total_mc = (h_Zjets_DYCR->GetBinContent(ibin+1)+h_vh_DYCR->GetBinContent(ibin+1)+h_htt_DYCR->GetBinContent(ibin+1)+h_vbf_DYCR->GetBinContent(ibin+1)+h_top_DYCR->GetBinContent(ibin+1)+h_diboson_DYCR->GetBinContent(ibin+1)+h_ggf_DYCR->GetBinContent(ibin+1)+h_Fakes_DYCR->GetBinContent(ibin+1)+h_Vgamma_DYCR->GetBinContent(ibin+1) );
  h_sysErrorPdf_DYCR->SetPointEYlow(4, std::abs(total_mc-rc_sysErrorPdf_DYCR->GetPointY(22)));
  h_sysErrorPdf_DYCR->SetPointEYhigh(4, std::abs(total_mc-rc_sysErrorPdf_DYCR->GetPointY(11)));

  h_Zjets_DYCR->Sumw2();
  h_vh_DYCR->Sumw2();
  h_htt_DYCR->Sumw2();
  h_vbf_DYCR->Sumw2();
  h_top_DYCR->Sumw2();
  h_diboson_DYCR->Sumw2();
  h_ggf_DYCR->Sumw2();
  h_Fakes_DYCR->Sumw2();
  h_Vgamma_DYCR->Sumw2();

  h_Zjets_DYCR->SetLineWidth(1);
  h_vh_DYCR->SetLineWidth(1);
  h_htt_DYCR->SetLineWidth(1);
  h_vbf_DYCR->SetLineWidth(1);
  h_top_DYCR->SetLineWidth(1);
  h_diboson_DYCR->SetLineWidth(1);
  h_ggf_DYCR->SetLineWidth(1);
  h_Fakes_DYCR->SetLineWidth(1);
  h_Vgamma_DYCR->SetLineWidth(1);

  h_ggf_DYCR->Add(h_vh_DYCR);
  h_ggf_DYCR->Add(h_htt_DYCR);
  h_Zjets_DYCR->Add(h_Vgamma_DYCR);

  h_Zjets_DYCR->SetFillColor(kGreen+2);
  h_Fakes_DYCR->SetFillColor(kCyan-7);
  h_diboson_DYCR->SetFillColor(kViolet+2);
  h_top_DYCR->SetFillColor(kYellow-7);
  h_vbf_DYCR->SetFillColor(kRed+1);
  h_ggf_DYCR->SetFillColor(kOrange+1);

  THStack* h_stack_DYCR = new THStack("h_stack_DYCR", "");
  h_stack_DYCR->Add(h_Fakes_DYCR);
  h_stack_DYCR->Add(h_Zjets_DYCR);
  h_stack_DYCR->Add(h_diboson_DYCR);
  h_stack_DYCR->Add(h_top_DYCR);
  h_stack_DYCR->Add(h_ggf_DYCR);
  h_stack_DYCR->Add(h_vbf_DYCR);

  icount=1;
  counter=1;
  
  // GGFCR
  for(int ibin=(rc_Zjets_CRGGF->GetN()-1)/2; ibin--;)
  {
    if(ibin<0) break;

    double zjets, vh, htt, vbf, top, diboson, ggf, fakes, vgamma = 0.;

    ggf = rc_ggf_CRGGF->GetPointY(rc_Zjets_CRGGF->GetN()-2*icount);
    zjets = rc_Zjets_CRGGF->GetPointY(rc_Zjets_CRGGF->GetN()-2*icount) - rc_ggf_CRGGF->GetPointY(rc_Zjets_CRGGF->GetN()-2*icount);
    diboson = rc_diboson_CRGGF->GetPointY(rc_Zjets_CRGGF->GetN()-2*icount) - rc_Zjets_CRGGF->GetPointY(rc_Zjets_CRGGF->GetN()-2*icount);
    top = rc_top_CRGGF->GetPointY(rc_Zjets_CRGGF->GetN()-2*icount) - rc_diboson_CRGGF->GetPointY(rc_Zjets_CRGGF->GetN()-2*icount);
    vgamma = rc_Vgamma_CRGGF->GetPointY(rc_Zjets_CRGGF->GetN()-2*icount) - rc_top_CRGGF->GetPointY(rc_Zjets_CRGGF->GetN()-2*icount);
    fakes = rc_Fakes_CRGGF->GetPointY(rc_Zjets_CRGGF->GetN()-2*icount) - rc_Vgamma_CRGGF->GetPointY(rc_Zjets_CRGGF->GetN()-2*icount);
    htt = rc_htt_CRGGF->GetPointY(rc_Zjets_CRGGF->GetN()-2*icount) - rc_Fakes_CRGGF->GetPointY(rc_Zjets_CRGGF->GetN()-2*icount);
    vh = rc_vh_CRGGF->GetPointY(rc_Zjets_CRGGF->GetN()-2*icount) - rc_htt_CRGGF->GetPointY(rc_Zjets_CRGGF->GetN()-2*icount);
    vbf = rc_vbf_CRGGF->GetPointY(rc_Zjets_CRGGF->GetN()-2*icount) - rc_vh_CRGGF->GetPointY(rc_Zjets_CRGGF->GetN()-2*icount);
    
 
    h_Zjets_CRGGF->SetBinContent(ibin, zjets);
    h_vh_CRGGF->SetBinContent(ibin, vh);
    h_htt_CRGGF->SetBinContent(ibin, htt);
    h_vbf_CRGGF->SetBinContent(ibin, vbf);
    h_top_CRGGF->SetBinContent(ibin, top);
    h_diboson_CRGGF->SetBinContent(ibin, diboson);
    h_ggf_CRGGF->SetBinContent(ibin, ggf);
    h_Fakes_CRGGF->SetBinContent(ibin, fakes);
    h_Vgamma_CRGGF->SetBinContent(ibin, vgamma);

    h_data_CRGGF->SetBinContent(icount, rh_Data_CRGGF->GetPointY(icount-1));

    counter+=2;
    icount++;    
  }
  
  for(int ibin=0; ibin<h_Zjets_CRGGF->GetNbinsX(); ibin++)
  {
    double y = h_Zjets_CRGGF->GetBinContent(ibin+1)+h_vh_CRGGF->GetBinContent(ibin+1)+h_htt_CRGGF->GetBinContent(ibin+1)+h_vbf_CRGGF->GetBinContent(ibin+1)+h_top_CRGGF->GetBinContent(ibin+1)+h_diboson_CRGGF->GetBinContent(ibin+1)+h_ggf_CRGGF->GetBinContent(ibin+1)+h_Fakes_CRGGF->GetBinContent(ibin+1)+h_Vgamma_CRGGF->GetBinContent(ibin+1); 
    h_sysErrorPdf_CRGGF->SetPoint(ibin, h_Zjets_CRGGF->GetBinCenter(ibin+1), y);
    h_sysErrorPdf_CRGGF->SetPointEXlow(ibin, h_Zjets_CRGGF->GetBinWidth(ibin+1)/2);
    h_sysErrorPdf_CRGGF->SetPointEXhigh(ibin, h_Zjets_CRGGF->GetBinWidth(ibin+1)/2);

  }

  // error band CRGGF
  ibin = 0;
  total_mc = (h_Zjets_CRGGF->GetBinContent(ibin+1)+h_vh_CRGGF->GetBinContent(ibin+1)+h_htt_CRGGF->GetBinContent(ibin+1)+h_vbf_CRGGF->GetBinContent(ibin+1)+h_top_CRGGF->GetBinContent(ibin+1)+h_diboson_CRGGF->GetBinContent(ibin+1)+h_ggf_CRGGF->GetBinContent(ibin+1)+h_Fakes_CRGGF->GetBinContent(ibin+1)+h_Vgamma_CRGGF->GetBinContent(ibin+1) );
  h_sysErrorPdf_CRGGF->SetPointEYlow(0, std::abs( total_mc-rc_sysErrorPdf_CRGGF->GetPointY(26)));
  h_sysErrorPdf_CRGGF->SetPointEYhigh(0, std::abs(total_mc-rc_sysErrorPdf_CRGGF->GetPointY(3)));
  ibin =1;
  total_mc = (h_Zjets_CRGGF->GetBinContent(ibin+1)+h_vh_CRGGF->GetBinContent(ibin+1)+h_htt_CRGGF->GetBinContent(ibin+1)+h_vbf_CRGGF->GetBinContent(ibin+1)+h_top_CRGGF->GetBinContent(ibin+1)+h_diboson_CRGGF->GetBinContent(ibin+1)+h_ggf_CRGGF->GetBinContent(ibin+1)+h_Fakes_CRGGF->GetBinContent(ibin+1)+h_Vgamma_CRGGF->GetBinContent(ibin+1) );  
  h_sysErrorPdf_CRGGF->SetPointEYlow(1, std::abs(total_mc-rc_sysErrorPdf_CRGGF->GetPointY(24)));
  h_sysErrorPdf_CRGGF->SetPointEYhigh(1, std::abs(total_mc-rc_sysErrorPdf_CRGGF->GetPointY(5)));
  ibin = 2;
  total_mc = (h_Zjets_CRGGF->GetBinContent(ibin+1)+h_vh_CRGGF->GetBinContent(ibin+1)+h_htt_CRGGF->GetBinContent(ibin+1)+h_vbf_CRGGF->GetBinContent(ibin+1)+h_top_CRGGF->GetBinContent(ibin+1)+h_diboson_CRGGF->GetBinContent(ibin+1)+h_ggf_CRGGF->GetBinContent(ibin+1)+h_Fakes_CRGGF->GetBinContent(ibin+1)+h_Vgamma_CRGGF->GetBinContent(ibin+1) ); 
  h_sysErrorPdf_CRGGF->SetPointEYlow(2, std::abs(total_mc-rc_sysErrorPdf_CRGGF->GetPointY(22)));
  h_sysErrorPdf_CRGGF->SetPointEYhigh(2, std::abs(total_mc-rc_sysErrorPdf_CRGGF->GetPointY(7)));
  ibin = 3;
  total_mc = (h_Zjets_CRGGF->GetBinContent(ibin+1)+h_vh_CRGGF->GetBinContent(ibin+1)+h_htt_CRGGF->GetBinContent(ibin+1)+h_vbf_CRGGF->GetBinContent(ibin+1)+h_top_CRGGF->GetBinContent(ibin+1)+h_diboson_CRGGF->GetBinContent(ibin+1)+h_ggf_CRGGF->GetBinContent(ibin+1)+h_Fakes_CRGGF->GetBinContent(ibin+1)+h_Vgamma_CRGGF->GetBinContent(ibin+1) ); 
  h_sysErrorPdf_CRGGF->SetPointEYlow(3, std::abs(total_mc-rc_sysErrorPdf_CRGGF->GetPointY(20)));
  h_sysErrorPdf_CRGGF->SetPointEYhigh(3, std::abs(total_mc-rc_sysErrorPdf_CRGGF->GetPointY(9)));

  h_Zjets_CRGGF->Sumw2();
  h_vh_CRGGF->Sumw2();
  h_htt_CRGGF->Sumw2();
  h_vbf_CRGGF->Sumw2();
  h_top_CRGGF->Sumw2();
  h_diboson_CRGGF->Sumw2();
  h_ggf_CRGGF->Sumw2();
  h_Fakes_CRGGF->Sumw2();
  h_Vgamma_CRGGF->Sumw2();
  h_data_CRGGF->Sumw2();

  h_Zjets_CRGGF->SetLineWidth(1);
  h_vh_CRGGF->SetLineWidth(1);
  h_htt_CRGGF->SetLineWidth(1);
  h_vbf_CRGGF->SetLineWidth(1);
  h_top_CRGGF->SetLineWidth(1);
  h_diboson_CRGGF->SetLineWidth(1);
  h_ggf_CRGGF->SetLineWidth(1);
  h_Fakes_CRGGF->SetLineWidth(1);
  h_Vgamma_CRGGF->SetLineWidth(1);

  h_ggf_CRGGF->Add(h_vh_CRGGF);
  h_ggf_CRGGF->Add(h_htt_CRGGF);
  h_Zjets_CRGGF->Add(h_Vgamma_CRGGF);

  h_Zjets_CRGGF->SetFillColor(kGreen+2);
  h_Fakes_CRGGF->SetFillColor(kCyan-7);
  h_diboson_CRGGF->SetFillColor(kViolet+2);
  h_top_CRGGF->SetFillColor(kYellow-7);
  h_vbf_CRGGF->SetFillColor(kRed+1);
  h_ggf_CRGGF->SetFillColor(kOrange+1);

  THStack* h_stack_CRGGF = new THStack("h_stack_CRGGF", "");
  h_stack_CRGGF->Add(h_Fakes_CRGGF);
  h_stack_CRGGF->Add(h_Zjets_CRGGF);
  h_stack_CRGGF->Add(h_diboson_CRGGF);
  h_stack_CRGGF->Add(h_top_CRGGF);
  h_stack_CRGGF->Add(h_ggf_CRGGF);
  h_stack_CRGGF->Add(h_vbf_CRGGF);


  // SR1
  
  std::vector<THStack*> v_stack_SR1, v_stack_SR2;

  int nbins_all_SR1;
  double *binEdges_all_SR1;
  canvasName="fitRes_obs_x_SRVBF_"+ std::to_string(0) +"_bdt_vbf_" + input + "_SRVBF_" + std::to_string(0) + "_bdt_vbf_" + input;

  chooseBinning(input, canvasName, nbins_all_SR1, binEdges_all_SR1, 0, 0, false, true);

  TH1F* h_vbf_all_SR1 = new TH1F("h_vbf_all_SR1","",nbins_all_SR1,binEdges_all_SR1);
  TH1F* h_zjets_all_SR1 = new TH1F("h_zjets_all_SR1","",nbins_all_SR1,binEdges_all_SR1);
  TH1F* h_vh_all_SR1 = new TH1F("h_vh_all_SR1","",nbins_all_SR1,binEdges_all_SR1);
  TH1F* h_htt_all_SR1 = new TH1F("h_htt_all_SR1","",nbins_all_SR1,binEdges_all_SR1);
  TH1F* h_top_all_SR1 = new TH1F("h_top_all_SR1","",nbins_all_SR1,binEdges_all_SR1);
  TH1F* h_diboson_all_SR1 = new TH1F("h_diboson_all_SR1","",nbins_all_SR1,binEdges_all_SR1);
  TH1F* h_ggf_all_SR1 = new TH1F("h_ggf_all_SR1","",nbins_all_SR1,binEdges_all_SR1);
  TH1F* h_fakes_all_SR1 = new TH1F("h_fakes_all_SR1","",nbins_all_SR1,binEdges_all_SR1);
  TH1F* h_vgamma_all_SR1 = new TH1F("h_vgamma_all_SR1","",nbins_all_SR1,binEdges_all_SR1);
  TH1F* h_data_all_SR1 = new TH1F("h_data_all_SR1","",nbins_all_SR1,binEdges_all_SR1);
  TGraphAsymmErrors* h_sys_all_SR1 = new TGraphAsymmErrors();

  for(int ibin_SR1 = 0; ibin_SR1<Nbins_SR1; ibin_SR1++)
  {
    icount=1;
    counter=1;
    for(int ibin=(v_rc_Zjets_SR1.at(ibin_SR1)->GetN()-1)/2; ibin--;) 
    {
      if(ibin<0) break;
      
      double zjets, vh, htt, vbf, top, diboson, ggf, fakes, vgamma = 0.;

      ggf = v_rc_ggf_SR1.at(ibin_SR1)->GetPointY(v_rc_Zjets_SR1.at(ibin_SR1)->GetN()-2*icount);
      zjets = v_rc_Zjets_SR1.at(ibin_SR1)->GetPointY(v_rc_Zjets_SR1.at(ibin_SR1)->GetN()-2*icount) - v_rc_ggf_SR1.at(ibin_SR1)->GetPointY(v_rc_Zjets_SR1.at(ibin_SR1)->GetN()-2*icount);
      diboson = v_rc_diboson_SR1.at(ibin_SR1)->GetPointY(v_rc_Zjets_SR1.at(ibin_SR1)->GetN()-2*icount) - v_rc_Zjets_SR1.at(ibin_SR1)->GetPointY(v_rc_Zjets_SR1.at(ibin_SR1)->GetN()-2*icount);
      top = v_rc_top_SR1.at(ibin_SR1)->GetPointY(v_rc_Zjets_SR1.at(ibin_SR1)->GetN()-2*icount) - v_rc_diboson_SR1.at(ibin_SR1)->GetPointY(v_rc_Zjets_SR1.at(ibin_SR1)->GetN()-2*icount);
      vgamma = v_rc_Vgamma_SR1.at(ibin_SR1)->GetPointY(v_rc_Zjets_SR1.at(ibin_SR1)->GetN()-2*icount) - v_rc_top_SR1.at(ibin_SR1)->GetPointY(v_rc_Zjets_SR1.at(ibin_SR1)->GetN()-2*icount);
      fakes = v_rc_Fakes_SR1.at(ibin_SR1)->GetPointY(v_rc_Zjets_SR1.at(ibin_SR1)->GetN()-2*icount) - v_rc_Vgamma_SR1.at(ibin_SR1)->GetPointY(v_rc_Zjets_SR1.at(ibin_SR1)->GetN()-2*icount);
      htt = v_rc_htt_SR1.at(ibin_SR1)->GetPointY(v_rc_Zjets_SR1.at(ibin_SR1)->GetN()-2*icount) - v_rc_Fakes_SR1.at(ibin_SR1)->GetPointY(v_rc_Zjets_SR1.at(ibin_SR1)->GetN()-2*icount);
      vh = v_rc_vh_SR1.at(ibin_SR1)->GetPointY(v_rc_Zjets_SR1.at(ibin_SR1)->GetN()-2*icount) - v_rc_htt_SR1.at(ibin_SR1)->GetPointY(v_rc_Zjets_SR1.at(ibin_SR1)->GetN()-2*icount);
      vbf = v_rc_vbf_SR1.at(ibin_SR1)->GetPointY(v_rc_Zjets_SR1.at(ibin_SR1)->GetN()-2*icount) - v_rc_vh_SR1.at(ibin_SR1)->GetPointY(v_rc_Zjets_SR1.at(ibin_SR1)->GetN()-2*icount);

      v_h_Zjets_SR1.at(ibin_SR1)->SetBinContent(ibin, zjets);
      v_h_vh_SR1.at(ibin_SR1)->SetBinContent(ibin, vh);
      v_h_htt_SR1.at(ibin_SR1)->SetBinContent(ibin, htt);
      v_h_vbf_SR1.at(ibin_SR1)->SetBinContent(ibin, vbf);
      v_h_top_SR1.at(ibin_SR1)->SetBinContent(ibin, top);
      v_h_diboson_SR1.at(ibin_SR1)->SetBinContent(ibin, diboson);
      v_h_ggf_SR1.at(ibin_SR1)->SetBinContent(ibin, ggf);
      v_h_Fakes_SR1.at(ibin_SR1)->SetBinContent(ibin, fakes);
      v_h_Vgamma_SR1.at(ibin_SR1)->SetBinContent(ibin, vgamma);

      v_h_data_SR1.at(ibin_SR1)->SetBinContent(icount, v_rh_data_SR1.at(ibin_SR1)->GetPointY(icount-1));

      counter+=2;
      icount++;
    }
    for(int ibin=0; ibin<v_h_Zjets_SR1.at(ibin_SR1)->GetNbinsX(); ibin++)
    {
      double y = v_h_Zjets_SR1.at(ibin_SR1)->GetBinContent(ibin+1)+v_h_vh_SR1.at(ibin_SR1)->GetBinContent(ibin+1)+v_h_htt_SR1.at(ibin_SR1)->GetBinContent(ibin+1)+v_h_vbf_SR1.at(ibin_SR1)->GetBinContent(ibin+1)+v_h_top_SR1.at(ibin_SR1)->GetBinContent(ibin+1)+v_h_diboson_SR1.at(ibin_SR1)->GetBinContent(ibin+1)+v_h_ggf_SR1.at(ibin_SR1)->GetBinContent(ibin+1)+v_h_Fakes_SR1.at(ibin_SR1)->GetBinContent(ibin+1)+v_h_Vgamma_SR1.at(ibin_SR1)->GetBinContent(ibin+1); 
      v_h_sysErr_SR1.at(ibin_SR1)->SetPoint(ibin, v_h_Zjets_SR1.at(ibin_SR1)->GetBinCenter(ibin+1), y);
      v_h_sysErr_SR1.at(ibin_SR1)->SetPointEXlow(ibin, v_h_Zjets_SR1.at(ibin_SR1)->GetBinWidth(ibin+1)/2);
      v_h_sysErr_SR1.at(ibin_SR1)->SetPointEXhigh(ibin, v_h_Zjets_SR1.at(ibin_SR1)->GetBinWidth(ibin+1)/2);
  }


    v_h_Zjets_SR1.at(ibin_SR1)->Sumw2();
    v_h_vh_SR1.at(ibin_SR1)->Sumw2();
    v_h_htt_SR1.at(ibin_SR1)->Sumw2();
    v_h_vbf_SR1.at(ibin_SR1)->Sumw2();
    v_h_top_SR1.at(ibin_SR1)->Sumw2();
    v_h_diboson_SR1.at(ibin_SR1)->Sumw2();
    v_h_ggf_SR1.at(ibin_SR1)->Sumw2();
    v_h_Fakes_SR1.at(ibin_SR1)->Sumw2();
    v_h_Vgamma_SR1.at(ibin_SR1)->Sumw2();
    v_h_data_SR1.at(ibin_SR1)->Sumw2();

    // error band SR1
    
    int ibin = 0;
    if(input=="DYjj" && ibin_SR1==4) {
    double total_mc = v_h_Zjets_SR1.at(ibin_SR1)->GetBinContent(ibin+1)/(binEdges_all_SR1[ibin+1]-binEdges_all_SR1[ibin])+v_h_vh_SR1.at(ibin_SR1)->GetBinContent(ibin+1)/(binEdges_all_SR1[ibin+1]-binEdges_all_SR1[ibin])+v_h_htt_SR1.at(ibin_SR1)->GetBinContent(ibin+1)/(binEdges_all_SR1[ibin+1]-binEdges_all_SR1[ibin])+v_h_vbf_SR1.at(ibin_SR1)->GetBinContent(ibin+1)/(binEdges_all_SR1[ibin+1]-binEdges_all_SR1[ibin])+v_h_top_SR1.at(ibin_SR1)->GetBinContent(ibin+1)/(binEdges_all_SR1[ibin+1]-binEdges_all_SR1[ibin])+v_h_diboson_SR1.at(ibin_SR1)->GetBinContent(ibin+1)/(binEdges_all_SR1[ibin+1]-binEdges_all_SR1[ibin])+v_h_ggf_SR1.at(ibin_SR1)->GetBinContent(ibin+1)/(binEdges_all_SR1[ibin+1]-binEdges_all_SR1[ibin])+v_h_Fakes_SR1.at(ibin_SR1)->GetBinContent(ibin+1)/(binEdges_all_SR1[ibin+1]-binEdges_all_SR1[ibin])+v_h_Vgamma_SR1.at(ibin_SR1)->GetBinContent(ibin+1)/(binEdges_all_SR1[ibin+1]-binEdges_all_SR1[ibin]); 
    v_h_sysErr_SR1.at(ibin_SR1)->SetPointEYlow(0, std::abs( total_mc-v_rc_sysErrorPdf_SR1.at(ibin_SR1)->GetPointY(22)/(binEdges_all_SR1[ibin+1]-binEdges_all_SR1[ibin])));
    v_h_sysErr_SR1.at(ibin_SR1)->SetPointEYhigh(0, std::abs(total_mc-v_rc_sysErrorPdf_SR1.at(ibin_SR1)->GetPointY(3)/(binEdges_all_SR1[ibin+1]-binEdges_all_SR1[ibin])));
    ibin =1;
    total_mc = v_h_Zjets_SR1.at(ibin_SR1)->GetBinContent(ibin+1)/(binEdges_all_SR1[ibin+1]-binEdges_all_SR1[ibin])+v_h_vh_SR1.at(ibin_SR1)->GetBinContent(ibin+1)/(binEdges_all_SR1[ibin+1]-binEdges_all_SR1[ibin])+v_h_htt_SR1.at(ibin_SR1)->GetBinContent(ibin+1)/(binEdges_all_SR1[ibin+1]-binEdges_all_SR1[ibin])+v_h_vbf_SR1.at(ibin_SR1)->GetBinContent(ibin+1)/(binEdges_all_SR1[ibin+1]-binEdges_all_SR1[ibin])+v_h_top_SR1.at(ibin_SR1)->GetBinContent(ibin+1)/(binEdges_all_SR1[ibin+1]-binEdges_all_SR1[ibin])+v_h_diboson_SR1.at(ibin_SR1)->GetBinContent(ibin+1)/(binEdges_all_SR1[ibin+1]-binEdges_all_SR1[ibin])+v_h_ggf_SR1.at(ibin_SR1)->GetBinContent(ibin+1)/(binEdges_all_SR1[ibin+1]-binEdges_all_SR1[ibin])+v_h_Fakes_SR1.at(ibin_SR1)->GetBinContent(ibin+1)/(binEdges_all_SR1[ibin+1]-binEdges_all_SR1[ibin])+v_h_Vgamma_SR1.at(ibin_SR1)->GetBinContent(ibin+1)/(binEdges_all_SR1[ibin+1]-binEdges_all_SR1[ibin]); 
    v_h_sysErr_SR1.at(ibin_SR1)->SetPointEYlow(1, std::abs(total_mc-v_rc_sysErrorPdf_SR1.at(ibin_SR1)->GetPointY(20)/(binEdges_all_SR1[ibin+1]-binEdges_all_SR1[ibin])));
    v_h_sysErr_SR1.at(ibin_SR1)->SetPointEYhigh(1, std::abs(total_mc-v_rc_sysErrorPdf_SR1.at(ibin_SR1)->GetPointY(5)/(binEdges_all_SR1[ibin+1]-binEdges_all_SR1[ibin])));
    ibin = 2;
    total_mc = v_h_Zjets_SR1.at(ibin_SR1)->GetBinContent(ibin+1)/(binEdges_all_SR1[ibin+1]-binEdges_all_SR1[ibin])+v_h_vh_SR1.at(ibin_SR1)->GetBinContent(ibin+1)/(binEdges_all_SR1[ibin+1]-binEdges_all_SR1[ibin])+v_h_htt_SR1.at(ibin_SR1)->GetBinContent(ibin+1)/(binEdges_all_SR1[ibin+1]-binEdges_all_SR1[ibin])+v_h_vbf_SR1.at(ibin_SR1)->GetBinContent(ibin+1)/(binEdges_all_SR1[ibin+1]-binEdges_all_SR1[ibin])+v_h_top_SR1.at(ibin_SR1)->GetBinContent(ibin+1)/(binEdges_all_SR1[ibin+1]-binEdges_all_SR1[ibin])+v_h_diboson_SR1.at(ibin_SR1)->GetBinContent(ibin+1)/(binEdges_all_SR1[ibin+1]-binEdges_all_SR1[ibin])+v_h_ggf_SR1.at(ibin_SR1)->GetBinContent(ibin+1)/(binEdges_all_SR1[ibin+1]-binEdges_all_SR1[ibin])+v_h_Fakes_SR1.at(ibin_SR1)->GetBinContent(ibin+1)/(binEdges_all_SR1[ibin+1]-binEdges_all_SR1[ibin])+v_h_Vgamma_SR1.at(ibin_SR1)->GetBinContent(ibin+1)/(binEdges_all_SR1[ibin+1]-binEdges_all_SR1[ibin]); 
    v_h_sysErr_SR1.at(ibin_SR1)->SetPointEYlow(2, std::abs(total_mc-v_rc_sysErrorPdf_SR1.at(ibin_SR1)->GetPointY(18)/(binEdges_all_SR1[ibin+1]-binEdges_all_SR1[ibin])));
    v_h_sysErr_SR1.at(ibin_SR1)->SetPointEYhigh(2, std::abs(total_mc-v_rc_sysErrorPdf_SR1.at(ibin_SR1)->GetPointY(7)/(binEdges_all_SR1[ibin+1]-binEdges_all_SR1[ibin])));
    ibin = 3;
    total_mc = v_h_Zjets_SR1.at(ibin_SR1)->GetBinContent(ibin+1)/(binEdges_all_SR1[ibin+1]-binEdges_all_SR1[ibin])+v_h_vh_SR1.at(ibin_SR1)->GetBinContent(ibin+1)/(binEdges_all_SR1[ibin+1]-binEdges_all_SR1[ibin])+v_h_htt_SR1.at(ibin_SR1)->GetBinContent(ibin+1)/(binEdges_all_SR1[ibin+1]-binEdges_all_SR1[ibin])+v_h_vbf_SR1.at(ibin_SR1)->GetBinContent(ibin+1)/(binEdges_all_SR1[ibin+1]-binEdges_all_SR1[ibin])+v_h_top_SR1.at(ibin_SR1)->GetBinContent(ibin+1)/(binEdges_all_SR1[ibin+1]-binEdges_all_SR1[ibin])+v_h_diboson_SR1.at(ibin_SR1)->GetBinContent(ibin+1)/(binEdges_all_SR1[ibin+1]-binEdges_all_SR1[ibin])+v_h_ggf_SR1.at(ibin_SR1)->GetBinContent(ibin+1)/(binEdges_all_SR1[ibin+1]-binEdges_all_SR1[ibin])+v_h_Fakes_SR1.at(ibin_SR1)->GetBinContent(ibin+1)/(binEdges_all_SR1[ibin+1]-binEdges_all_SR1[ibin])+v_h_Vgamma_SR1.at(ibin_SR1)->GetBinContent(ibin+1)/(binEdges_all_SR1[ibin+1]-binEdges_all_SR1[ibin]); 
    v_h_sysErr_SR1.at(ibin_SR1)->SetPointEYlow(3, std::abs(total_mc-v_rc_sysErrorPdf_SR1.at(ibin_SR1)->GetPointY(16)/(binEdges_all_SR1[ibin+1]-binEdges_all_SR1[ibin])));
    v_h_sysErr_SR1.at(ibin_SR1)->SetPointEYhigh(3, std::abs(total_mc-v_rc_sysErrorPdf_SR1.at(ibin_SR1)->GetPointY(9)/(binEdges_all_SR1[ibin+1]-binEdges_all_SR1[ibin])));
    }
    else {
    double total_mc = v_h_Zjets_SR1.at(ibin_SR1)->GetBinContent(ibin+1)/(binEdges_all_SR1[ibin+1]-binEdges_all_SR1[ibin])+v_h_vh_SR1.at(ibin_SR1)->GetBinContent(ibin+1)/(binEdges_all_SR1[ibin+1]-binEdges_all_SR1[ibin])+v_h_htt_SR1.at(ibin_SR1)->GetBinContent(ibin+1)/(binEdges_all_SR1[ibin+1]-binEdges_all_SR1[ibin])+v_h_vbf_SR1.at(ibin_SR1)->GetBinContent(ibin+1)/(binEdges_all_SR1[ibin+1]-binEdges_all_SR1[ibin])+v_h_top_SR1.at(ibin_SR1)->GetBinContent(ibin+1)/(binEdges_all_SR1[ibin+1]-binEdges_all_SR1[ibin])+v_h_diboson_SR1.at(ibin_SR1)->GetBinContent(ibin+1)/(binEdges_all_SR1[ibin+1]-binEdges_all_SR1[ibin])+v_h_ggf_SR1.at(ibin_SR1)->GetBinContent(ibin+1)/(binEdges_all_SR1[ibin+1]-binEdges_all_SR1[ibin])+v_h_Fakes_SR1.at(ibin_SR1)->GetBinContent(ibin+1)/(binEdges_all_SR1[ibin+1]-binEdges_all_SR1[ibin])+v_h_Vgamma_SR1.at(ibin_SR1)->GetBinContent(ibin+1)/(binEdges_all_SR1[ibin+1]-binEdges_all_SR1[ibin]); 
    v_h_sysErr_SR1.at(ibin_SR1)->SetPointEYlow(0, std::abs( total_mc-v_rc_sysErrorPdf_SR1.at(ibin_SR1)->GetPointY(26)/(binEdges_all_SR1[ibin+1]-binEdges_all_SR1[ibin])));
    v_h_sysErr_SR1.at(ibin_SR1)->SetPointEYhigh(0, std::abs(total_mc-v_rc_sysErrorPdf_SR1.at(ibin_SR1)->GetPointY(3)/(binEdges_all_SR1[ibin+1]-binEdges_all_SR1[ibin])));
    ibin =1;
    total_mc = v_h_Zjets_SR1.at(ibin_SR1)->GetBinContent(ibin+1)/(binEdges_all_SR1[ibin+1]-binEdges_all_SR1[ibin])+v_h_vh_SR1.at(ibin_SR1)->GetBinContent(ibin+1)/(binEdges_all_SR1[ibin+1]-binEdges_all_SR1[ibin])+v_h_htt_SR1.at(ibin_SR1)->GetBinContent(ibin+1)/(binEdges_all_SR1[ibin+1]-binEdges_all_SR1[ibin])+v_h_vbf_SR1.at(ibin_SR1)->GetBinContent(ibin+1)/(binEdges_all_SR1[ibin+1]-binEdges_all_SR1[ibin])+v_h_top_SR1.at(ibin_SR1)->GetBinContent(ibin+1)/(binEdges_all_SR1[ibin+1]-binEdges_all_SR1[ibin])+v_h_diboson_SR1.at(ibin_SR1)->GetBinContent(ibin+1)/(binEdges_all_SR1[ibin+1]-binEdges_all_SR1[ibin])+v_h_ggf_SR1.at(ibin_SR1)->GetBinContent(ibin+1)/(binEdges_all_SR1[ibin+1]-binEdges_all_SR1[ibin])+v_h_Fakes_SR1.at(ibin_SR1)->GetBinContent(ibin+1)/(binEdges_all_SR1[ibin+1]-binEdges_all_SR1[ibin])+v_h_Vgamma_SR1.at(ibin_SR1)->GetBinContent(ibin+1)/(binEdges_all_SR1[ibin+1]-binEdges_all_SR1[ibin]); 
    v_h_sysErr_SR1.at(ibin_SR1)->SetPointEYlow(1, std::abs(total_mc-v_rc_sysErrorPdf_SR1.at(ibin_SR1)->GetPointY(24)/(binEdges_all_SR1[ibin+1]-binEdges_all_SR1[ibin])));
    v_h_sysErr_SR1.at(ibin_SR1)->SetPointEYhigh(1, std::abs(total_mc-v_rc_sysErrorPdf_SR1.at(ibin_SR1)->GetPointY(5)/(binEdges_all_SR1[ibin+1]-binEdges_all_SR1[ibin])));
    ibin = 2;
    total_mc = v_h_Zjets_SR1.at(ibin_SR1)->GetBinContent(ibin+1)/(binEdges_all_SR1[ibin+1]-binEdges_all_SR1[ibin])+v_h_vh_SR1.at(ibin_SR1)->GetBinContent(ibin+1)/(binEdges_all_SR1[ibin+1]-binEdges_all_SR1[ibin])+v_h_htt_SR1.at(ibin_SR1)->GetBinContent(ibin+1)/(binEdges_all_SR1[ibin+1]-binEdges_all_SR1[ibin])+v_h_vbf_SR1.at(ibin_SR1)->GetBinContent(ibin+1)/(binEdges_all_SR1[ibin+1]-binEdges_all_SR1[ibin])+v_h_top_SR1.at(ibin_SR1)->GetBinContent(ibin+1)/(binEdges_all_SR1[ibin+1]-binEdges_all_SR1[ibin])+v_h_diboson_SR1.at(ibin_SR1)->GetBinContent(ibin+1)/(binEdges_all_SR1[ibin+1]-binEdges_all_SR1[ibin])+v_h_ggf_SR1.at(ibin_SR1)->GetBinContent(ibin+1)/(binEdges_all_SR1[ibin+1]-binEdges_all_SR1[ibin])+v_h_Fakes_SR1.at(ibin_SR1)->GetBinContent(ibin+1)/(binEdges_all_SR1[ibin+1]-binEdges_all_SR1[ibin])+v_h_Vgamma_SR1.at(ibin_SR1)->GetBinContent(ibin+1)/(binEdges_all_SR1[ibin+1]-binEdges_all_SR1[ibin]); 
    v_h_sysErr_SR1.at(ibin_SR1)->SetPointEYlow(2, std::abs(total_mc-v_rc_sysErrorPdf_SR1.at(ibin_SR1)->GetPointY(22)/(binEdges_all_SR1[ibin+1]-binEdges_all_SR1[ibin])));
    v_h_sysErr_SR1.at(ibin_SR1)->SetPointEYhigh(2, std::abs(total_mc-v_rc_sysErrorPdf_SR1.at(ibin_SR1)->GetPointY(7)/(binEdges_all_SR1[ibin+1]-binEdges_all_SR1[ibin])));
    ibin = 3;
    total_mc = v_h_Zjets_SR1.at(ibin_SR1)->GetBinContent(ibin+1)/(binEdges_all_SR1[ibin+1]-binEdges_all_SR1[ibin])+v_h_vh_SR1.at(ibin_SR1)->GetBinContent(ibin+1)/(binEdges_all_SR1[ibin+1]-binEdges_all_SR1[ibin])+v_h_htt_SR1.at(ibin_SR1)->GetBinContent(ibin+1)/(binEdges_all_SR1[ibin+1]-binEdges_all_SR1[ibin])+v_h_vbf_SR1.at(ibin_SR1)->GetBinContent(ibin+1)/(binEdges_all_SR1[ibin+1]-binEdges_all_SR1[ibin])+v_h_top_SR1.at(ibin_SR1)->GetBinContent(ibin+1)/(binEdges_all_SR1[ibin+1]-binEdges_all_SR1[ibin])+v_h_diboson_SR1.at(ibin_SR1)->GetBinContent(ibin+1)/(binEdges_all_SR1[ibin+1]-binEdges_all_SR1[ibin])+v_h_ggf_SR1.at(ibin_SR1)->GetBinContent(ibin+1)/(binEdges_all_SR1[ibin+1]-binEdges_all_SR1[ibin])+v_h_Fakes_SR1.at(ibin_SR1)->GetBinContent(ibin+1)/(binEdges_all_SR1[ibin+1]-binEdges_all_SR1[ibin])+v_h_Vgamma_SR1.at(ibin_SR1)->GetBinContent(ibin+1)/(binEdges_all_SR1[ibin+1]-binEdges_all_SR1[ibin]); 
    v_h_sysErr_SR1.at(ibin_SR1)->SetPointEYlow(3, std::abs(total_mc-v_rc_sysErrorPdf_SR1.at(ibin_SR1)->GetPointY(20)/(binEdges_all_SR1[ibin+1]-binEdges_all_SR1[ibin])));
    v_h_sysErr_SR1.at(ibin_SR1)->SetPointEYhigh(3, std::abs(total_mc-v_rc_sysErrorPdf_SR1.at(ibin_SR1)->GetPointY(9)/(binEdges_all_SR1[ibin+1]-binEdges_all_SR1[ibin])));
    ibin = 4;
    total_mc = v_h_Zjets_SR1.at(ibin_SR1)->GetBinContent(ibin+1)/(binEdges_all_SR1[ibin+1]-binEdges_all_SR1[ibin])+v_h_vh_SR1.at(ibin_SR1)->GetBinContent(ibin+1)/(binEdges_all_SR1[ibin+1]-binEdges_all_SR1[ibin])+v_h_htt_SR1.at(ibin_SR1)->GetBinContent(ibin+1)/(binEdges_all_SR1[ibin+1]-binEdges_all_SR1[ibin])+v_h_vbf_SR1.at(ibin_SR1)->GetBinContent(ibin+1)/(binEdges_all_SR1[ibin+1]-binEdges_all_SR1[ibin])+v_h_top_SR1.at(ibin_SR1)->GetBinContent(ibin+1)/(binEdges_all_SR1[ibin+1]-binEdges_all_SR1[ibin])+v_h_diboson_SR1.at(ibin_SR1)->GetBinContent(ibin+1)/(binEdges_all_SR1[ibin+1]-binEdges_all_SR1[ibin])+v_h_ggf_SR1.at(ibin_SR1)->GetBinContent(ibin+1)/(binEdges_all_SR1[ibin+1]-binEdges_all_SR1[ibin])+v_h_Fakes_SR1.at(ibin_SR1)->GetBinContent(ibin+1)/(binEdges_all_SR1[ibin+1]-binEdges_all_SR1[ibin])+v_h_Vgamma_SR1.at(ibin_SR1)->GetBinContent(ibin+1)/(binEdges_all_SR1[ibin+1]-binEdges_all_SR1[ibin]); 
    v_h_sysErr_SR1.at(ibin_SR1)->SetPointEYlow(4, std::abs(total_mc-v_rc_sysErrorPdf_SR1.at(ibin_SR1)->GetPointY(18)/(binEdges_all_SR1[ibin+1]-binEdges_all_SR1[ibin])));
    v_h_sysErr_SR1.at(ibin_SR1)->SetPointEYhigh(4, std::abs(total_mc-v_rc_sysErrorPdf_SR1.at(ibin_SR1)->GetPointY(11)/(binEdges_all_SR1[ibin+1]-binEdges_all_SR1[ibin])));
    }

    

    v_h_Zjets_SR1.at(ibin_SR1)->SetLineWidth(1);
    v_h_vh_SR1.at(ibin_SR1)->SetLineWidth(1);
    v_h_htt_SR1.at(ibin_SR1)->SetLineWidth(1);
    v_h_vbf_SR1.at(ibin_SR1)->SetLineWidth(1);
    v_h_top_SR1.at(ibin_SR1)->SetLineWidth(1);
    v_h_diboson_SR1.at(ibin_SR1)->SetLineWidth(1);
    v_h_ggf_SR1.at(ibin_SR1)->SetLineWidth(1);
    v_h_Fakes_SR1.at(ibin_SR1)->SetLineWidth(1);
    v_h_Vgamma_SR1.at(ibin_SR1)->SetLineWidth(1);

    v_h_ggf_SR1.at(ibin_SR1)->Add(v_h_vh_SR1.at(ibin_SR1));
    v_h_ggf_SR1.at(ibin_SR1)->Add(v_h_htt_SR1.at(ibin_SR1));
    v_h_Zjets_SR1.at(ibin_SR1)->Add(v_h_Vgamma_SR1.at(ibin_SR1));

    v_h_Zjets_SR1.at(ibin_SR1)->SetFillColor(kGreen+2);
    v_h_Fakes_SR1.at(ibin_SR1)->SetFillColor(kCyan-7);
    v_h_diboson_SR1.at(ibin_SR1)->SetFillColor(kViolet+2);
    v_h_top_SR1.at(ibin_SR1)->SetFillColor(kYellow-7);
    v_h_vbf_SR1.at(ibin_SR1)->SetFillColor(kRed+1);
    v_h_ggf_SR1.at(ibin_SR1)->SetFillColor(kOrange+1);

    std::string stack_name = "h_stack_SR1_" + std::to_string(ibin_SR1);
    THStack* h_stack_SR1_tmp = new THStack(stack_name.c_str(), "");
    h_stack_SR1_tmp->Add(v_h_Fakes_SR1.at(ibin_SR1));
    h_stack_SR1_tmp->Add(v_h_Zjets_SR1.at(ibin_SR1));
    h_stack_SR1_tmp->Add(v_h_diboson_SR1.at(ibin_SR1));
    h_stack_SR1_tmp->Add(v_h_top_SR1.at(ibin_SR1));
    h_stack_SR1_tmp->Add(v_h_ggf_SR1.at(ibin_SR1));
    h_stack_SR1_tmp->Add(v_h_vbf_SR1.at(ibin_SR1));
    v_stack_SR1.push_back(h_stack_SR1_tmp);
   
  }
    
  int binSR1 =0;
  int next = 0; 
  float scale = 1;
  bool isScale = false;
  int totalBins = 20;

  
  if(!(input=="Mjj" || input=="lep0_pt" || input=="costhetastar" || input=="DPhill" || input=="DYll" )) totalBins = 16;
  if(input=="DYjj") totalBins =19;

  for(int ibin=0; ibin<totalBins; ibin++)
  {
    
    if(binSR1>3){
        binSR1=0;
        next++;
    }
      
      if(doScale) {
        isScale = true;
        if(input=="Mjj") {
        if(ibin<8 && ibin>3) scale=2;
        else if(ibin>7 && ibin<12) scale = 2;
        else if(ibin>11 ) scale = 2;
        else scale=1;

      }
       else if(input=="DYll") {
        if( (ibin>3 && ibin<12) ) scale = 2;
        else if(ibin>11 && ibin<16) scale = 4;
        else if (ibin>15) scale =2;
        else scale=1;
       }

       else if(input=="lep1_pt") {
        if(ibin>3 ) scale = 2;
     //   else if(ibin>7) scale = 4;
        else scale=1;
       }

       else if(input=="jet0_pt") {
        if(ibin>3) scale = 2;
       }
       else if(input=="jet1_pt") {
       // if(ibin>3 && ibin<8) scale =2;
        if(ibin>7) scale = 4;
        else scale = 1;
       }
       else if(input=="pt_H") {
        if(ibin>11) scale = 4;
        else if(ibin<4) scale = 2;
        else scale=1;
       }
       else if(input=="Ptll") {
       
       // if(ibin>7 && ibin<12) scale = 2;
        if(ibin>11) scale = 2;
        else if( ibin<4 ) scale =2;
        else scale = 1;

       }
       else if(input=="Mll") {
        if(ibin>7 ) scale = 2;
        else scale=1;
       }
       else if(input=="costhetastar") {
        if(ibin<12 ) scale = 2;
        else scale =1;
       }
       else if (input=="lep0_pt") {
        if(ibin<8) scale =2;
        else if(ibin>15) scale = 2;
        else scale =1;
       }
       else if(input=="DYjj") {
        
        scale=1;
       }


      }
    //  std::cout<<"before< "<<v_h_data_SR1.at(next)->GetBinError(binSR1+1)<<std::endl;
      h_vbf_all_SR1->SetBinContent(ibin+1, scale*v_h_vbf_SR1.at(next)->GetBinContent(binSR1+1));
      h_vbf_all_SR1->SetBinError(ibin+1, scale*TMath::Sqrt(v_h_vbf_SR1.at(next)->GetBinContent(binSR1+1)));
      h_zjets_all_SR1->SetBinContent(ibin+1, scale*v_h_Zjets_SR1.at(next)->GetBinContent(binSR1+1));
      h_zjets_all_SR1->SetBinError(ibin+1, scale*TMath::Sqrt(v_h_Zjets_SR1.at(next)->GetBinContent(binSR1+1)));
    
      h_top_all_SR1->SetBinContent(ibin+1, scale*v_h_top_SR1.at(next)->GetBinContent(binSR1+1));
      h_top_all_SR1->SetBinError(ibin+1, scale*TMath::Sqrt(v_h_top_SR1.at(next)->GetBinContent(binSR1+1)));
    
      h_diboson_all_SR1->SetBinContent(ibin+1, scale*v_h_diboson_SR1.at(next)->GetBinContent(binSR1+1));
      h_diboson_all_SR1->SetBinError(ibin+1, scale*TMath::Sqrt(v_h_diboson_SR1.at(next)->GetBinContent(binSR1+1)));
      h_ggf_all_SR1->SetBinContent(ibin+1, scale*v_h_ggf_SR1.at(next)->GetBinContent(binSR1+1));
      h_ggf_all_SR1->SetBinError(ibin+1, scale*TMath::Sqrt(v_h_ggf_SR1.at(next)->GetBinContent(binSR1+1)));
      h_fakes_all_SR1->SetBinContent(ibin+1, scale*v_h_Fakes_SR1.at(next)->GetBinContent(binSR1+1));
      h_fakes_all_SR1->SetBinError(ibin+1, scale*TMath::Sqrt(v_h_Fakes_SR1.at(next)->GetBinContent(binSR1+1)));

      h_data_all_SR1->SetBinContent(ibin+1, scale*v_h_data_SR1.at(next)->GetBinContent(binSR1+1));
      h_data_all_SR1->SetBinError(ibin+1, scale*TMath::Sqrt(v_h_data_SR1.at(next)->GetBinContent(binSR1+1)));

      h_sys_all_SR1->SetPointY(ibin, scale*v_h_sysErr_SR1.at(next)->GetPointY(binSR1)/(binEdges_all_SR1[ibin+1]-binEdges_all_SR1[ibin]));
      h_sys_all_SR1->SetPointX(ibin, (binEdges_all_SR1[ibin+1]-binEdges_all_SR1[ibin])/2 + binEdges_all_SR1[ibin]);
      h_sys_all_SR1->SetPointError(ibin, v_h_sysErr_SR1.at(next)->GetErrorXlow(binSR1), v_h_sysErr_SR1.at(next)->GetErrorXhigh(binSR1), scale*v_h_sysErr_SR1.at(next)->GetErrorYlow(binSR1), scale*v_h_sysErr_SR1.at(next)->GetErrorYhigh(binSR1));
      binSR1++;    
   
  }
  /*
  h_vbf_all_SR1->Sumw2();
  h_zjets_all_SR1->Sumw2();
  h_top_all_SR1->Sumw2();
  h_diboson_all_SR1->Sumw2();
  h_ggf_all_SR1->Sumw2();
  h_fakes_all_SR1->Sumw2();
  h_data_all_SR1->Sumw2();
*/
  h_vbf_all_SR1->Scale(1,"width");
  h_zjets_all_SR1->Scale(1,"width");
  h_top_all_SR1->Scale(1,"width");
  h_diboson_all_SR1->Scale(1,"width");
  h_ggf_all_SR1->Scale(1,"width");
  h_fakes_all_SR1->Scale(1,"width");
  h_data_all_SR1->Scale(1,"width");



  std::cout<<"DATA ERRORS: "<<h_data_all_SR1->GetBinError(1)<<" "<<h_data_all_SR1->GetBinError(5)<<std::endl;

  h_vbf_all_SR1->SetLineWidth(1);
  h_zjets_all_SR1->SetLineWidth(1);

  h_top_all_SR1->SetLineWidth(1);
  h_diboson_all_SR1->SetLineWidth(1);
  h_ggf_all_SR1->SetLineWidth(1);
  h_fakes_all_SR1->SetLineWidth(1);


  h_zjets_all_SR1->SetFillColor(kGreen+2);
  h_fakes_all_SR1->SetFillColor(kCyan-7);
  h_diboson_all_SR1->SetFillColor(kViolet+2);
  h_top_all_SR1->SetFillColor(kYellow-7);
  h_vbf_all_SR1->SetFillColor(kRed+1);
  h_ggf_all_SR1->SetFillColor(kOrange+1);

  std::string stack_name = "h_stack_SR1_all";
  THStack* h_stack_SR1_all = new THStack(stack_name.c_str(), "");
  h_stack_SR1_all->Add(h_fakes_all_SR1);
  h_stack_SR1_all->Add(h_zjets_all_SR1);
  h_stack_SR1_all->Add(h_diboson_all_SR1);
  h_stack_SR1_all->Add(h_top_all_SR1);
  h_stack_SR1_all->Add(h_ggf_all_SR1);
  h_stack_SR1_all->Add(h_vbf_all_SR1);


  // SR2
  for(int ibin_SR2 = 0; ibin_SR2<Nbins_SR2; ibin_SR2++)
  {
    icount=1;
    counter=1;

    for(int ibin=(v_rc_Zjets_SR2.at(ibin_SR2)->GetN()-1)/2; ibin--;) 
    {
      if(ibin<0) break;
      
      double zjets, vh, htt, vbf, top, diboson, ggf, fakes, vgamma = 0.;

      ggf = v_rc_ggf_SR2.at(ibin_SR2)->GetPointY(v_rc_Zjets_SR2.at(ibin_SR2)->GetN()-2*icount);
      zjets = v_rc_Zjets_SR2.at(ibin_SR2)->GetPointY(v_rc_Zjets_SR2.at(ibin_SR2)->GetN()-2*icount) - v_rc_ggf_SR2.at(ibin_SR2)->GetPointY(v_rc_Zjets_SR2.at(ibin_SR2)->GetN()-2*icount);
      diboson = v_rc_diboson_SR2.at(ibin_SR2)->GetPointY(v_rc_Zjets_SR2.at(ibin_SR2)->GetN()-2*icount) - v_rc_Zjets_SR2.at(ibin_SR2)->GetPointY(v_rc_Zjets_SR2.at(ibin_SR2)->GetN()-2*icount);
      top = v_rc_top_SR2.at(ibin_SR2)->GetPointY(v_rc_Zjets_SR2.at(ibin_SR2)->GetN()-2*icount) - v_rc_diboson_SR2.at(ibin_SR2)->GetPointY(v_rc_Zjets_SR2.at(ibin_SR2)->GetN()-2*icount);
      vgamma = v_rc_Vgamma_SR2.at(ibin_SR2)->GetPointY(v_rc_Zjets_SR2.at(ibin_SR2)->GetN()-2*icount) - v_rc_top_SR2.at(ibin_SR2)->GetPointY(v_rc_Zjets_SR2.at(ibin_SR2)->GetN()-2*icount);
      fakes = v_rc_Fakes_SR2.at(ibin_SR2)->GetPointY(v_rc_Zjets_SR2.at(ibin_SR2)->GetN()-2*icount) - v_rc_Vgamma_SR2.at(ibin_SR2)->GetPointY(v_rc_Zjets_SR2.at(ibin_SR2)->GetN()-2*icount);
      htt = v_rc_htt_SR2.at(ibin_SR2)->GetPointY(v_rc_Zjets_SR2.at(ibin_SR2)->GetN()-2*icount) - v_rc_Fakes_SR2.at(ibin_SR2)->GetPointY(v_rc_Zjets_SR2.at(ibin_SR2)->GetN()-2*icount);
      vh = v_rc_vh_SR2.at(ibin_SR2)->GetPointY(v_rc_Zjets_SR2.at(ibin_SR2)->GetN()-2*icount) - v_rc_htt_SR2.at(ibin_SR2)->GetPointY(v_rc_Zjets_SR2.at(ibin_SR2)->GetN()-2*icount);
      vbf = v_rc_vbf_SR2.at(ibin_SR2)->GetPointY(v_rc_Zjets_SR2.at(ibin_SR2)->GetN()-2*icount) - v_rc_vh_SR2.at(ibin_SR2)->GetPointY(v_rc_Zjets_SR2.at(ibin_SR2)->GetN()-2*icount);

      v_h_Zjets_SR2.at(ibin_SR2)->SetBinContent(ibin, zjets);
      v_h_vh_SR2.at(ibin_SR2)->SetBinContent(ibin, vh);
      v_h_htt_SR2.at(ibin_SR2)->SetBinContent(ibin, htt);
      v_h_vbf_SR2.at(ibin_SR2)->SetBinContent(ibin, vbf);
      v_h_top_SR2.at(ibin_SR2)->SetBinContent(ibin, top);
      v_h_diboson_SR2.at(ibin_SR2)->SetBinContent(ibin, diboson);
      v_h_ggf_SR2.at(ibin_SR2)->SetBinContent(ibin, ggf);
      v_h_Fakes_SR2.at(ibin_SR2)->SetBinContent(ibin, fakes);
      v_h_Vgamma_SR2.at(ibin_SR2)->SetBinContent(ibin, vgamma);

      v_h_data_SR2.at(ibin_SR2)->SetBinContent(icount, v_rh_data_SR2.at(ibin_SR2)->GetPointY(icount-1));

      counter+=2;
      icount++;
    }
    
  for(int ibin=0; ibin<v_h_Zjets_SR2.at(ibin_SR2)->GetNbinsX(); ibin++)
    {
      double y = v_h_Zjets_SR2.at(ibin_SR2)->GetBinContent(ibin+1)+v_h_vbf_SR2.at(ibin_SR2)->GetBinContent(ibin+1)+v_h_top_SR2.at(ibin_SR2)->GetBinContent(ibin+1)+v_h_diboson_SR2.at(ibin_SR2)->GetBinContent(ibin+1)+v_h_ggf_SR2.at(ibin_SR2)->GetBinContent(ibin+1)+v_h_Fakes_SR2.at(ibin_SR2)->GetBinContent(ibin+1); 
      v_h_sysErr_SR2.at(ibin_SR2)->SetPoint(ibin, v_h_Zjets_SR2.at(ibin_SR2)->GetBinCenter(ibin+1), y);
      v_h_sysErr_SR2.at(ibin_SR2)->SetPointEXlow(ibin, v_h_Zjets_SR2.at(ibin_SR2)->GetBinWidth(ibin+1)/2);
      v_h_sysErr_SR2.at(ibin_SR2)->SetPointEXhigh(ibin, v_h_Zjets_SR2.at(ibin_SR2)->GetBinWidth(ibin+1)/2);
  }

    v_h_Zjets_SR2.at(ibin_SR2)->Sumw2();
    v_h_vh_SR2.at(ibin_SR2)->Sumw2();
    v_h_htt_SR2.at(ibin_SR2)->Sumw2();
    v_h_vbf_SR2.at(ibin_SR2)->Sumw2();
    v_h_top_SR2.at(ibin_SR2)->Sumw2();
    v_h_diboson_SR2.at(ibin_SR2)->Sumw2();
    v_h_ggf_SR2.at(ibin_SR2)->Sumw2();
    v_h_Fakes_SR2.at(ibin_SR2)->Sumw2();
    v_h_Vgamma_SR2.at(ibin_SR2)->Sumw2();


    // error band SR2

  ibin = 0;
  if(input=="SignedDPhijj") {
    total_mc = (v_h_Zjets_SR2.at(ibin_SR2)->GetBinContent(ibin+1)+v_h_vh_SR2.at(ibin_SR2)->GetBinContent(ibin+1)+v_h_htt_SR2.at(ibin_SR2)->GetBinContent(ibin+1)+v_h_vbf_SR2.at(ibin_SR2)->GetBinContent(ibin+1)+v_h_top_SR2.at(ibin_SR2)->GetBinContent(ibin+1)+v_h_diboson_SR2.at(ibin_SR2)->GetBinContent(ibin+1)+v_h_ggf_SR2.at(ibin_SR2)->GetBinContent(ibin+1)+v_h_Fakes_SR2.at(ibin_SR2)->GetBinContent(ibin+1)+v_h_Vgamma_SR2.at(ibin_SR2)->GetBinContent(ibin+1) );
      v_h_sysErr_SR2.at(ibin_SR2)->SetPointEYlow(0, std::abs( total_mc-v_rc_sysErrorPdf_SR2.at(ibin_SR2)->GetPointY(26)));
      v_h_sysErr_SR2.at(ibin_SR2)->SetPointEYhigh(0, std::abs(total_mc-v_rc_sysErrorPdf_SR2.at(ibin_SR2)->GetPointY(3)));
      ibin =1;
      total_mc = (v_h_Zjets_SR2.at(ibin_SR2)->GetBinContent(ibin+1)+v_h_vh_SR2.at(ibin_SR2)->GetBinContent(ibin+1)+v_h_htt_SR2.at(ibin_SR2)->GetBinContent(ibin+1)+v_h_vbf_SR2.at(ibin_SR2)->GetBinContent(ibin+1)+v_h_top_SR2.at(ibin_SR2)->GetBinContent(ibin+1)+v_h_diboson_SR2.at(ibin_SR2)->GetBinContent(ibin+1)+v_h_ggf_SR2.at(ibin_SR2)->GetBinContent(ibin+1)+v_h_Fakes_SR2.at(ibin_SR2)->GetBinContent(ibin+1)+v_h_Vgamma_SR2.at(ibin_SR2)->GetBinContent(ibin+1) );
      v_h_sysErr_SR2.at(ibin_SR2)->SetPointEYlow(1, std::abs(total_mc-v_rc_sysErrorPdf_SR2.at(ibin_SR2)->GetPointY(24)));
      v_h_sysErr_SR2.at(ibin_SR2)->SetPointEYhigh(1, std::abs(total_mc-v_rc_sysErrorPdf_SR2.at(ibin_SR2)->GetPointY(5)));
      ibin = 2;
      total_mc = (v_h_Zjets_SR2.at(ibin_SR2)->GetBinContent(ibin+1)+v_h_vh_SR2.at(ibin_SR2)->GetBinContent(ibin+1)+v_h_htt_SR2.at(ibin_SR2)->GetBinContent(ibin+1)+v_h_vbf_SR2.at(ibin_SR2)->GetBinContent(ibin+1)+v_h_top_SR2.at(ibin_SR2)->GetBinContent(ibin+1)+v_h_diboson_SR2.at(ibin_SR2)->GetBinContent(ibin+1)+v_h_ggf_SR2.at(ibin_SR2)->GetBinContent(ibin+1)+v_h_Fakes_SR2.at(ibin_SR2)->GetBinContent(ibin+1)+v_h_Vgamma_SR2.at(ibin_SR2)->GetBinContent(ibin+1) );
      v_h_sysErr_SR2.at(ibin_SR2)->SetPointEYlow(2, std::abs(total_mc-v_rc_sysErrorPdf_SR2.at(ibin_SR2)->GetPointY(22)));
      v_h_sysErr_SR2.at(ibin_SR2)->SetPointEYhigh(2, std::abs(total_mc-v_rc_sysErrorPdf_SR2.at(ibin_SR2)->GetPointY(7)));
      ibin = 3;
      total_mc = (v_h_Zjets_SR2.at(ibin_SR2)->GetBinContent(ibin+1)+v_h_vh_SR2.at(ibin_SR2)->GetBinContent(ibin+1)+v_h_htt_SR2.at(ibin_SR2)->GetBinContent(ibin+1)+v_h_vbf_SR2.at(ibin_SR2)->GetBinContent(ibin+1)+v_h_top_SR2.at(ibin_SR2)->GetBinContent(ibin+1)+v_h_diboson_SR2.at(ibin_SR2)->GetBinContent(ibin+1)+v_h_ggf_SR2.at(ibin_SR2)->GetBinContent(ibin+1)+v_h_Fakes_SR2.at(ibin_SR2)->GetBinContent(ibin+1)+v_h_Vgamma_SR2.at(ibin_SR2)->GetBinContent(ibin+1) );
      v_h_sysErr_SR2.at(ibin_SR2)->SetPointEYlow(3, std::abs(total_mc-v_rc_sysErrorPdf_SR2.at(ibin_SR2)->GetPointY(20)));
      v_h_sysErr_SR2.at(ibin_SR2)->SetPointEYhigh(3, std::abs(total_mc-v_rc_sysErrorPdf_SR2.at(ibin_SR2)->GetPointY(9)));

  }
  else{
    total_mc = (v_h_Zjets_SR2.at(ibin_SR2)->GetBinContent(ibin+1)+v_h_vh_SR2.at(ibin_SR2)->GetBinContent(ibin+1)+v_h_htt_SR2.at(ibin_SR2)->GetBinContent(ibin+1)+v_h_vbf_SR2.at(ibin_SR2)->GetBinContent(ibin+1)+v_h_top_SR2.at(ibin_SR2)->GetBinContent(ibin+1)+v_h_diboson_SR2.at(ibin_SR2)->GetBinContent(ibin+1)+v_h_ggf_SR2.at(ibin_SR2)->GetBinContent(ibin+1)+v_h_Fakes_SR2.at(ibin_SR2)->GetBinContent(ibin+1)+v_h_Vgamma_SR2.at(ibin_SR2)->GetBinContent(ibin+1) );
    v_h_sysErr_SR2.at(ibin_SR2)->SetPointEYlow(0, std::abs( total_mc-v_rc_sysErrorPdf_SR2.at(ibin_SR2)->GetPointY(18)));
    v_h_sysErr_SR2.at(ibin_SR2)->SetPointEYhigh(0, std::abs(total_mc-v_rc_sysErrorPdf_SR2.at(ibin_SR2)->GetPointY(3)));
    ibin =1;
    total_mc = (v_h_Zjets_SR2.at(ibin_SR2)->GetBinContent(ibin+1)+v_h_vh_SR2.at(ibin_SR2)->GetBinContent(ibin+1)+v_h_htt_SR2.at(ibin_SR2)->GetBinContent(ibin+1)+v_h_vbf_SR2.at(ibin_SR2)->GetBinContent(ibin+1)+v_h_top_SR2.at(ibin_SR2)->GetBinContent(ibin+1)+v_h_diboson_SR2.at(ibin_SR2)->GetBinContent(ibin+1)+v_h_ggf_SR2.at(ibin_SR2)->GetBinContent(ibin+1)+v_h_Fakes_SR2.at(ibin_SR2)->GetBinContent(ibin+1)+v_h_Vgamma_SR2.at(ibin_SR2)->GetBinContent(ibin+1) );
    v_h_sysErr_SR2.at(ibin_SR2)->SetPointEYlow(1, std::abs(total_mc-v_rc_sysErrorPdf_SR2.at(ibin_SR2)->GetPointY(16)));
    v_h_sysErr_SR2.at(ibin_SR2)->SetPointEYhigh(1, std::abs(total_mc-v_rc_sysErrorPdf_SR2.at(ibin_SR2)->GetPointY(5)));
  }
  
    v_h_Zjets_SR2.at(ibin_SR2)->SetLineWidth(1);
    v_h_vh_SR2.at(ibin_SR2)->SetLineWidth(1);
    v_h_htt_SR2.at(ibin_SR2)->SetLineWidth(1);
    v_h_vbf_SR2.at(ibin_SR2)->SetLineWidth(1);
    v_h_top_SR2.at(ibin_SR2)->SetLineWidth(1);
    v_h_diboson_SR2.at(ibin_SR2)->SetLineWidth(1);
    v_h_ggf_SR2.at(ibin_SR2)->SetLineWidth(1);
    v_h_Fakes_SR2.at(ibin_SR2)->SetLineWidth(1);
    v_h_Vgamma_SR2.at(ibin_SR2)->SetLineWidth(1);

    v_h_ggf_SR2.at(ibin_SR2)->Add(v_h_vh_SR2.at(ibin_SR2));
    v_h_ggf_SR2.at(ibin_SR2)->Add(v_h_htt_SR2.at(ibin_SR2));
    v_h_Zjets_SR2.at(ibin_SR2)->Add(v_h_Vgamma_SR2.at(ibin_SR2));

    v_h_Zjets_SR2.at(ibin_SR2)->SetFillColor(kGreen+2);
    v_h_Fakes_SR2.at(ibin_SR2)->SetFillColor(kCyan-7);
    v_h_diboson_SR2.at(ibin_SR2)->SetFillColor(kViolet+2);
    v_h_top_SR2.at(ibin_SR2)->SetFillColor(kYellow-7);
    v_h_vbf_SR2.at(ibin_SR2)->SetFillColor(kRed+1);
    v_h_ggf_SR2.at(ibin_SR2)->SetFillColor(kOrange+1);

    std::string stack_name = "h_stack_SR2_" + std::to_string(ibin_SR2);
    THStack* h_stack_SR2_tmp = new THStack(stack_name.c_str(), "");
    h_stack_SR2_tmp->Add(v_h_Fakes_SR2.at(ibin_SR2));
    h_stack_SR2_tmp->Add(v_h_Zjets_SR2.at(ibin_SR2));
    h_stack_SR2_tmp->Add(v_h_diboson_SR2.at(ibin_SR2));
    h_stack_SR2_tmp->Add(v_h_top_SR2.at(ibin_SR2));
    h_stack_SR2_tmp->Add(v_h_ggf_SR2.at(ibin_SR2));
    h_stack_SR2_tmp->Add(v_h_vbf_SR2.at(ibin_SR2));
    v_stack_SR2.push_back(h_stack_SR2_tmp);
  }


  int nbins_all_SR2;
  double *binEdges_all_SR2;
  canvasName="fitRes_obs_x_CRTop_" + std::to_string(0) + "_bdt_TopWWAll_CRTop_" + std::to_string(0) + "_bdt_TopWWAll";

  chooseBinning(input, canvasName, nbins_all_SR2, binEdges_all_SR2, 0, 0, false, true);

  TH1F* h_vbf_all_SR2 = new TH1F("h_vbf_all_SR2","",nbins_all_SR2,binEdges_all_SR2);
  TH1F* h_zjets_all_SR2 = new TH1F("h_zjets_all_SR2","",nbins_all_SR2,binEdges_all_SR2);
  TH1F* h_vh_all_SR2 = new TH1F("h_vh_all_SR2","",nbins_all_SR2,binEdges_all_SR2);
  TH1F* h_htt_all_SR2 = new TH1F("h_htt_all_SR2","",nbins_all_SR2,binEdges_all_SR2);
  TH1F* h_top_all_SR2 = new TH1F("h_top_all_SR2","",nbins_all_SR2,binEdges_all_SR2);
  TH1F* h_diboson_all_SR2 = new TH1F("h_diboson_all_SR2","",nbins_all_SR2,binEdges_all_SR2);
  TH1F* h_ggf_all_SR2 = new TH1F("h_ggf_all_SR2","",nbins_all_SR2,binEdges_all_SR2);
  TH1F* h_fakes_all_SR2 = new TH1F("h_fakes_all_SR2","",nbins_all_SR2,binEdges_all_SR2);
  TH1F* h_vgamma_all_SR2 = new TH1F("h_vgamma_all_SR2","",nbins_all_SR2,binEdges_all_SR2);
  TH1F* h_data_all_SR2 = new TH1F("h_data_all_SR2","",nbins_all_SR2,binEdges_all_SR2);
  TGraphAsymmErrors* h_sys_all_SR2 = new TGraphAsymmErrors();


  int binSR2 =0;
  int next2 = 0; 
  float scale2 = 1;
  bool isScale2 = false;
  totalBins=10;
  if(!(input=="Mjj" || input=="lep0_pt" || input=="costhetastar" || input=="DPhill" || input=="DYll" || input=="DYjj")) totalBins=8;
 
  if(input=="SignedDPhijj") totalBins = 16;

  for(int ibin=0; ibin<totalBins; ibin++)
  {

    if(input=="SignedDPhijj")
    {
      if(binSR2>3){
        binSR2=0;
        next2++;
      }
    }
    else{
      if(binSR2>1){
        binSR2=0;
        next2++;
      }
  }

       if(doScale) {
        isScale2 = true;
        if(input=="Mjj") {
        if(ibin>1 && ibin<4) scale2=6;
        else if(ibin>3 && ibin<6) scale2=10;
        else if(ibin>5 && ibin<8) scale2=14;
        else if(ibin>7) scale2=40;
        else scale2 = 1;
      }
      if(input=="costhetastar") {
        if(ibin<6) scale2 = 10;
        else if(ibin>5 && ibin<8) scale2 = 4;
        else scale2 = 1;
      } 
      if(input=="DPhill") {
        if(ibin<8) scale2 = 2;
        else scale2=1;
      }
      if(input=="DYll") {
        if(ibin<2) scale2 = 2;
        else if(ibin>1 && ibin<8) scale2 = 4;
        else scale2 = 1;
      }
      if(input=="lep1_pt") {
        if(ibin>3) scale2 = 2;
      }
      if(input=="jet0_pt") {
        if(ibin>1 && ibin<4) scale2=4;
        else if(ibin>3) scale2 = 6;
        else scale2 =1;
      }
      if(input=="jet1_pt") {
        if(ibin>1 && ibin <4) scale2=4;
        else if(ibin>3) scale2=6;
        else scale2=1;
      }
      if(input=="pt_H") {
        if(ibin>3 && ibin <6) scale2 = 2;
        else if(ibin>5) scale2=8;
        else scale2=1;
      }
      if(input=="Ptll") {
        if(ibin<2 ) scale2 =2;
        else if(ibin>5) scale2 =2;
        else scale2=1;
      }
      else if(input=="Mll") {
        if(ibin<6) scale2 = 4;
        else scale2=1;
      }
      else if (input=="lep0_pt") {
        if(ibin<2) scale2 = 2;
        else scale2=1; 
      }
      else if (input=="DYjj") {
        if(ibin>3 && ibin<8) scale2=2;
        else if(ibin>7) scale2=4;
        else scale2=1;
      }

      }

      h_vbf_all_SR2->SetBinContent(ibin+1, scale2*v_h_vbf_SR2.at(next2)->GetBinContent(binSR2+1));
      h_vbf_all_SR2->SetBinError(ibin+1, scale2*TMath::Sqrt(v_h_vbf_SR2.at(next2)->GetBinContent(binSR2+1)));
      h_zjets_all_SR2->SetBinContent(ibin+1, scale2*v_h_Zjets_SR2.at(next2)->GetBinContent(binSR2+1));
      h_zjets_all_SR2->SetBinError(ibin+1, scale2*TMath::Sqrt(v_h_Zjets_SR2.at(next2)->GetBinContent(binSR2+1)));

      h_top_all_SR2->SetBinContent(ibin+1, scale2*v_h_top_SR2.at(next2)->GetBinContent(binSR2+1));
      h_top_all_SR2->SetBinError(ibin+1, scale2*TMath::Sqrt(v_h_top_SR2.at(next2)->GetBinContent(binSR2+1)));
      h_diboson_all_SR2->SetBinContent(ibin+1, scale2*v_h_diboson_SR2.at(next2)->GetBinContent(binSR2+1));
      h_diboson_all_SR2->SetBinError(ibin+1, scale2*TMath::Sqrt(v_h_diboson_SR2.at(next2)->GetBinContent(binSR2+1)));
      h_ggf_all_SR2->SetBinContent(ibin+1, scale2*v_h_ggf_SR2.at(next2)->GetBinContent(binSR2+1));
      h_ggf_all_SR2->SetBinError(ibin+1, scale2*TMath::Sqrt(v_h_ggf_SR2.at(next2)->GetBinContent(binSR2+1)));
      h_fakes_all_SR2->SetBinContent(ibin+1, scale2*v_h_Fakes_SR2.at(next2)->GetBinContent(binSR2+1));
      h_fakes_all_SR2->SetBinError(ibin+1, scale2*TMath::Sqrt(v_h_Fakes_SR2.at(next2)->GetBinContent(binSR2+1)));

      h_data_all_SR2->SetBinContent(ibin+1, scale2*v_h_data_SR2.at(next2)->GetBinContent(binSR2+1));
      h_data_all_SR2->SetBinError(ibin+1, scale2*TMath::Sqrt(v_h_data_SR2.at(next2)->GetBinContent(binSR2+1)));
      
      h_sys_all_SR2->SetPointY(ibin, scale2*v_h_sysErr_SR2.at(next2)->GetPointY(binSR2));
      h_sys_all_SR2->SetPointX(ibin, (binEdges_all_SR2[ibin+1]-binEdges_all_SR2[ibin])/2 + binEdges_all_SR2[ibin]);
      h_sys_all_SR2->SetPointError(ibin, v_h_sysErr_SR2.at(next2)->GetErrorXlow(binSR2), v_h_sysErr_SR2.at(next2)->GetErrorXhigh(binSR2), scale2*v_h_sysErr_SR2.at(next2)->GetErrorYlow(binSR2), scale2*v_h_sysErr_SR2.at(next2)->GetErrorYhigh(binSR2));

      binSR2++;      
  }

  h_vbf_all_SR2->SetLineWidth(1);
  h_zjets_all_SR2->SetLineWidth(1);

  h_top_all_SR2->SetLineWidth(1);
  h_diboson_all_SR2->SetLineWidth(1);
  h_ggf_all_SR2->SetLineWidth(1);
  h_fakes_all_SR2->SetLineWidth(1);


  h_zjets_all_SR2->SetFillColor(kGreen+2);
  h_fakes_all_SR2->SetFillColor(kCyan-7);
  h_diboson_all_SR2->SetFillColor(kViolet+2);
  h_top_all_SR2->SetFillColor(kYellow-7);
  h_vbf_all_SR2->SetFillColor(kRed+1);
  h_ggf_all_SR2->SetFillColor(kOrange+1);

  std::string stack2_name = "h_stack_SR2_all";
  THStack* h_stack_SR2_all = new THStack(stack2_name.c_str(), "");
  h_stack_SR2_all->Add(h_fakes_all_SR2);
  h_stack_SR2_all->Add(h_zjets_all_SR2);
  h_stack_SR2_all->Add(h_diboson_all_SR2);
  h_stack_SR2_all->Add(h_top_all_SR2);
  h_stack_SR2_all->Add(h_ggf_all_SR2);
  h_stack_SR2_all->Add(h_vbf_all_SR2);


// Draw everything on canvas

  TCanvas* chara = new TCanvas("chara", "chara", 600, 600);
  chara->cd();

  TPad* padsr1 = new TPad("padsr1","padsr1", 0, 0.68, 0.6, 1.);
  padsr1->SetTopMargin(0.05); // (0.05)
  padsr1->SetBottomMargin(0.028);
  padsr1->SetRightMargin(0.118);
  padsr1->SetLeftMargin(0.12);
  padsr1->Draw();
  padsr1->cd();

  // gPad->SetLogy();
  h_stack_SR1_all->Draw("hist");
  h_stack_SR1_all->SetMaximum(900);
  if(input=="DYjj") h_stack_SR1_all->SetMaximum(500);
  if(input=="Mll") h_stack_SR1_all->SetMaximum(900);
  if(input=="jet0_pt" ) h_stack_SR1_all->SetMaximum(900);
  if(input=="jet1_pt" ) h_stack_SR1_all->SetMaximum(1050);
  if(input=="lep1_pt" ) h_stack_SR1_all->SetMaximum(900);
  if(input=="Ptll") h_stack_SR1_all->SetMaximum(900);
  if(input=="DYll" ) h_stack_SR1_all->SetMaximum(1000);
  if(input=="DPhill" ) h_stack_SR1_all->SetMaximum(400);
  if(input=="Mjj") h_stack_SR1_all->SetMaximum(900);
  if(input=="lep0_pt") h_stack_SR1_all->SetMaximum(820);
  if(input=="SignedDPhijj") h_stack_SR1_all->SetMaximum(700);

  h_stack_SR1_all->GetYaxis()->SetTitle("Events / bin width");
 // h_stack_SR1_all->GetYaxis()->SetTitleOffset(5.);
  h_stack_SR1_all->GetXaxis()->SetLabelOffset(10);
  h_stack_SR1_all->GetYaxis()->SetLabelOffset(.0001);

  h_stack_SR1_all->GetYaxis()->SetLabelSize(.063);
  h_stack_SR1_all->GetYaxis()->SetTitleSize(.07);
  h_stack_SR1_all->GetYaxis()->SetTitleOffset(0.7);
  if(input=="jet1_pt") h_stack_SR1_all->GetYaxis()->SetTitleOffset(0.8);
  h_data_all_SR1->SetMarkerSize(.8);

  h_sys_all_SR1->SetFillStyle(3345);
  h_sys_all_SR1->SetFillColor(kGray+2);
  h_sys_all_SR1->Draw("e2 same");
  h_data_all_SR1->Draw("pe same");
  
  double mult = 120;
  double subtract = 2;
  if(input=="SignedDPhijj") {mult = 100; subtract=2;}
  if( input=="DYll" ) { mult = 100; subtract = -1;}
  if(input == "costhetastar" || input=="pt_H" ) { mult = 120; subtract = 2;}
  if(input == "lep0_pt" ){ mult =100; subtract =-1;}
  if(input=="DPhill") {mult =65; subtract=12;}
  if(input=="DYjj" ){mult =88; subtract=12;}
  TLine* line0 = new TLine(1., 0., 1., gPad->GetUymax() - mult*(gPad->GetUymax()-mult)/gPad->GetUymax() - 50. );
  TLine* line1 = new TLine(1.5, 0., 1.5, gPad->GetUymax() - mult*(gPad->GetUymax()-mult)/gPad->GetUymax() - 50. );
  TLine* line2 = new TLine(2., 0., 2., gPad->GetUymax() - mult*(gPad->GetUymax()-mult)/gPad->GetUymax() - 50. );
  TLine* line3 = new TLine(2.5, 0., 2.5, gPad->GetUymax() - mult*(gPad->GetUymax()-mult)/gPad->GetUymax() - 50. );
  line0->Draw("same");
  line1->Draw("same");
  line2->Draw("same");
  line3->Draw("same");

  TLatex mytext;

  mytext.SetTextSize(0.06);
  std::string subtit = "SR1";
  if(input=="SignedDPhijj" || input=="lep1_pt" || input=="jet0_pt" || input=="jet1_pt" || input=="pt_H" || input=="Mll" || input=="Ptll") mytext.DrawLatex(1.45, gPad->GetUymax() - mult*(gPad->GetUymax()-mult)/gPad->GetUymax()- mult/4, subtit.c_str());
  else mytext.DrawLatex(1.7, gPad->GetUymax() - mult*(gPad->GetUymax()-mult)/gPad->GetUymax()-mult/4, subtit.c_str());
  subtit=obs_title(input) + " Bin1";
  if(input=="costhetastar") subtit=obs_title(input);
  double xstart = .6;
  if(input=="costhetastar") xstart = .6;
  if(input=="Mjj") xstart = .65;
  //if(input=="DYll") xstart = .59;
  mytext.DrawLatex(xstart,gPad->GetUymax() - mult*(gPad->GetUymax()-mult)/gPad->GetUymax() - (mult-subtract) ,subtit.c_str());
  if(input=="costhetastar") mytext.DrawLatex(0.68, 585, "Bin1");
  if(isScale){
   if(input=="Mjj") mytext.DrawLatex(.75,610,"x1");
   if(input=="DYll") mytext.DrawLatex(.75,650,"x1");
   if(input=="lep1_pt") mytext.DrawLatex(.7,600,"x1");
   if(input=="jet0_pt") mytext.DrawLatex(.7,600,"x1");
   if(input=="jet1_pt") mytext.DrawLatex(.7,750,"x1");
   if(input=="pt_H") mytext.DrawLatex(.70,620,"x2");
   if(input=="Ptll") mytext.DrawLatex(.7,610,"x2");
   if(input=="Mll") mytext.DrawLatex(.7,610,"x1");
   if(input=="costhetastar") mytext.DrawLatex(.75,510,"x2");
   if(input=="lep0_pt") mytext.DrawLatex(.75,580,"x2");
  // if(input=="DYjj") mytext.DrawLatex(.75,330,"x1");
  // if(input=="DPhill") mytext.DrawLatex(.75,250,"x1");
  }
  subtit=obs_title(input) + " Bin2";
  if(input=="costhetastar") mytext.DrawLatex(1.18, 585, "Bin2");
  if(input=="costhetastar") subtit=obs_title(input);
  xstart = 1.1;
  if(input=="costhetastar" || input=="DPhill" || input=="DYjj") xstart = 1.05;
  if(input=="lep0_pt" || input=="DYll" ) xstart = 1.075;
  mytext.DrawLatex(xstart,gPad->GetUymax() - mult*(gPad->GetUymax()-mult)/gPad->GetUymax() - (mult-subtract) ,subtit.c_str());
  if(isScale) {
    if(input=="Mjj") mytext.DrawLatex(1.25,610,"x2");
    if(input=="DYll") mytext.DrawLatex(1.25,650,"x2");
    if(input=="lep1_pt") mytext.DrawLatex(1.2,600,"x2");
    if(input=="jet0_pt") mytext.DrawLatex(1.2,600,"x2");
    if(input=="jet1_pt") mytext.DrawLatex(1.2,750,"x1");
    if(input=="pt_H") mytext.DrawLatex(1.2,620,"x1");
    if(input=="Ptll") mytext.DrawLatex(1.2,610,"x1");
    if(input=="Mll") mytext.DrawLatex(1.2,610,"x1");
    if(input=="costhetastar") mytext.DrawLatex(1.25,510,"x2");
    if(input=="lep0_pt") mytext.DrawLatex(1.25,580,"x2");
  //  if(input=="DYjj") mytext.DrawLatex(1.25,330,"x1");
   // if(input=="DPhill") mytext.DrawLatex(1.25,250,"x1");
  }
  subtit=obs_title(input) + " Bin3";
  if(input=="costhetastar") mytext.DrawLatex(1.68, 585, "Bin3");
  if(input=="costhetastar") subtit=obs_title(input);
  xstart = 1.6;
  if(input=="costhetastar" || input=="DPhill" || input=="DYll"|| input=="DYjj") xstart = 1.55;
  if(input=="lep0_pt" ) xstart = 1.6;
  mytext.DrawLatex(xstart,gPad->GetUymax() - mult*(gPad->GetUymax()-mult)/gPad->GetUymax() - (mult-subtract) ,subtit.c_str());
  if(isScale) {
    if(input=="Mjj") mytext.DrawLatex(1.75,610,"x2");
    if(input=="DYll")  mytext.DrawLatex(1.75,650,"x2");
    if(input=="lep1_pt")  mytext.DrawLatex(1.7,600,"x2");
    if(input=="jet0_pt")  mytext.DrawLatex(1.7,600,"x2");
    if(input=="jet1_pt")  mytext.DrawLatex(1.7,750,"x4");
    if(input=="pt_H")  mytext.DrawLatex(1.7,620,"x1");
    if(input=="Ptll")  mytext.DrawLatex(1.7,610,"x1");
    if(input=="Mll")  mytext.DrawLatex(1.7,610,"x2");
    if(input=="costhetastar")  mytext.DrawLatex(1.75,510,"x2");
    if(input=="lep0_pt")  mytext.DrawLatex(1.75,580,"x1");
  //  if(input=="DYjj")  mytext.DrawLatex(1.75,330,"x1");
    //if(input=="DPhill") mytext.DrawLatex(1.75,250,"x1");
  }
  subtit=obs_title(input) + " Bin4";
  if(input=="costhetastar") mytext.DrawLatex(2.18, 585, "Bin4");
  if(input=="costhetastar") subtit=obs_title(input);
  xstart = 2.1;
  if(input=="costhetastar"|| input=="DPhill" || input=="DYll" ||  input=="DYjj") xstart = 2.05;
  if(input=="lep0_pt") xstart = 2.1;
  mytext.DrawLatex(xstart,gPad->GetUymax() - mult*(gPad->GetUymax()-mult)/gPad->GetUymax() - (mult-subtract) ,subtit.c_str());
  if(isScale) {
   if(input=="Mjj") mytext.DrawLatex(2.25,610,"x2");
   if(input=="DYll") mytext.DrawLatex(2.25,650,"x4");
   if(input=="lep1_pt") mytext.DrawLatex(2.2,600,"x2");
   if(input=="jet0_pt") mytext.DrawLatex(2.2,600,"x2");
   if(input=="jet1_pt") mytext.DrawLatex(2.2,750,"x4");
   if(input=="pt_H") mytext.DrawLatex(2.2,620,"x4");
   if(input=="Ptll") mytext.DrawLatex(2.2,610,"x2");
   if(input=="Mll") mytext.DrawLatex(2.2,610,"x2");
   if(input=="costhetastar") mytext.DrawLatex(2.25,510,"x1");
   if(input=="lep0_pt") mytext.DrawLatex(2.25,580,"x1");
  // if(input=="DYjj") mytext.DrawLatex(2.25,330,"x1");
   //if(input=="DPhill") mytext.DrawLatex(2.25,250,"x1");
 }
  subtit=obs_title(input) + " Bin5";
  mytext.DrawLatex(2.65, 585, "Bin5");
  if(input=="costhetastar") subtit=obs_title(input);
  if(input=="costhetastar") xstart=2.55;
  if(input=="costhetastar" || input=="DYll" || input=="DPhill"|| input=="DYjj") xstart = 2.53;
  if(input=="lep0_pt"  ) xstart = 2.6;
  mytext.DrawLatex(xstart,gPad->GetUymax() - mult*(gPad->GetUymax()-mult)/gPad->GetUymax() - (mult-subtract) ,subtit.c_str());
  if(isScale) {
    if(input=="Mjj") mytext.DrawLatex(2.75,610,"x2");
    if(input=="DYll") mytext.DrawLatex(2.75,650,"x2");
    if(input=="lep1_pt") mytext.DrawLatex(2.75,73,"x4");
    if(input=="costhetastar") mytext.DrawLatex(2.75,510,"x1");
    if(input=="lep0_pt") mytext.DrawLatex(2.75,580,"x2");
  //  if(input=="DYjj") mytext.DrawLatex(2.75,330,"x1");
    //if(input=="DPhill") mytext.DrawLatex(2.75,250,"x1");
  }

  chara->cd();
  TPad* subpadsr1 = new TPad("subpadsr1","subpadsr1", 0., 0.505, 0.6, .68);
  subpadsr1->SetTopMargin(0.08);
  subpadsr1->SetBottomMargin(0.3);
  subpadsr1->SetRightMargin(0.118);
  subpadsr1->SetLeftMargin(0.12);
  subpadsr1->Draw();
  subpadsr1->cd();
  gPad->SetGridy(1);

  TH1D* h_ratio_SR1_all = (TH1D*) h_data_all_SR1->Clone("ratio");
  TH1D* h_all_bkg_SR1_all = (TH1D*) h_zjets_all_SR1->Clone("all_bkg");
  h_all_bkg_SR1_all->Add(h_fakes_all_SR1);
  h_all_bkg_SR1_all->Add(h_top_all_SR1);
  h_all_bkg_SR1_all->Add(h_ggf_all_SR1);
  h_all_bkg_SR1_all->Add(h_diboson_all_SR1);
  h_all_bkg_SR1_all->Add(h_vbf_all_SR1);
 // std::cout<<"TOTAL BGK "<<h_all_bkg_SR1_all->GetBinContent(5)<<" DATA "<<h_data_all_SR1->GetBinContent(5)<<" RATIO "<<h_sys_all_SR1->GetErrorYlow(4)/h_all_bkg_SR1_all->GetBinContent(5)<<std::endl;
  h_ratio_SR1_all->Divide(h_all_bkg_SR1_all);

  TGraphAsymmErrors* h_ratio_unc_SR1_all = new TGraphAsymmErrors();
  totalBins=20;
  if(!(input=="Mjj" || input=="lep0_pt" || input=="costhetastar" || input=="DPhill" || input=="DYll" )) totalBins=16;
  if(input=="DYjj") totalBins = 19;
  for(int i=0; i<totalBins; i++)
  {
    h_ratio_unc_SR1_all->SetPoint(i, (binEdges_all_SR1[i+1]-binEdges_all_SR1[i])/2 + binEdges_all_SR1[i], 1);
    h_ratio_unc_SR1_all->SetPointError(i, (binEdges_all_SR1[i+1]-binEdges_all_SR1[i])/2,(binEdges_all_SR1[i+1]-binEdges_all_SR1[i])/2,h_sys_all_SR1->GetErrorYlow(i)/h_all_bkg_SR1_all->GetBinContent(i+1), h_sys_all_SR1->GetErrorYhigh(i)/h_all_bkg_SR1_all->GetBinContent(i+1));
  }

  h_ratio_SR1_all->Draw("pe");
  h_ratio_unc_SR1_all->SetFillColor(kGray+2);
  h_ratio_unc_SR1_all->SetFillStyle(3345);
  h_ratio_unc_SR1_all->Draw("e2 same");
  h_ratio_SR1_all->Draw("pe same");
  h_ratio_SR1_all->GetYaxis()->SetLabelSize(.12);

  h_ratio_SR1_all->GetYaxis()->SetLabelOffset(.003);

  h_ratio_SR1_all->GetYaxis()->SetNdivisions(505);
  h_ratio_SR1_all->GetYaxis()->CenterTitle(true);
  h_ratio_SR1_all->GetYaxis()->SetTitleOffset(.37);
  h_ratio_SR1_all->GetXaxis()->SetTitleOffset(.8);
 
  h_ratio_SR1_all->GetYaxis()->SetTitleSize(.13);
  h_ratio_SR1_all->GetYaxis()->SetTitle("Data / Pred.");
  h_ratio_SR1_all->GetXaxis()->SetTitleSize(.13);
  h_ratio_SR1_all->GetXaxis()->SetTitle("#it{D}_{VBF}");

   h_ratio_SR1_all->GetXaxis()->SetTickLength(.08);

   h_ratio_SR1_all->GetXaxis()->SetLabelOffset(10);
   mytext.SetTextSize(.11);

   TArrow *ar2 = new TArrow(2.9,1.25,2.9,1.4, .007,">");
    ar2->SetLineColor(kRed);
    ar2->SetFillColor(kWhite);
    
  if(input=="Mjj")  ar2->Draw();

  TLine* sr1_line = new TLine(0.5, 1, 3, 1 );
  if(input=="pt_H" || input=="Ptll" || input=="Mll" || input == "lep1_pt" || input=="jet1_pt" || input=="SignedDPhijj") sr1_line = new TLine(0.5, 1, 2.5, 1 );
  sr1_line->SetLineColor(kBlack);
  sr1_line->Draw("same");
  gPad->RedrawAxis();

   double xratiolabel_up = 1.518;
   double xratiolabel_down = .23;
   if(input=="lep0_pt" || input=="DPhill" ) { xratiolabel_up = 1.918; xratiolabel_down = -0.06;}
   mytext.DrawLatex(.45, xratiolabel_down, "0.5");
   mytext.DrawLatex(1., xratiolabel_down, "0.5");
   mytext.DrawLatex(1.51, xratiolabel_down, "0.5");
   mytext.DrawLatex(2., xratiolabel_down, "0.5");
   if(! (input=="lep1_pt" || input=="jet0_pt" || input=="jet1_pt" || input=="pt_H" || input=="Ptll" || input=="Mll" || input=="SignedDPhijj") ) mytext.DrawLatex(2.51, xratiolabel_down, "0.5");
   
   mytext.DrawLatex(0.93, xratiolabel_up, "1.0");
   mytext.DrawLatex(1.43, xratiolabel_up, "1.0");
   mytext.DrawLatex(1.93, xratiolabel_up, "1.0");
   mytext.DrawLatex(2.43, xratiolabel_up, "1.0");
   mytext.DrawLatex(2.93, xratiolabel_up, "1.0");
  
 
  h_ratio_SR1_all->GetYaxis()->SetRangeUser(0.4,1.5);
  double ratio_add_max = .5;
  double ratio_add_min = .4;
  if(input=="lep0_pt" || input=="DPhill"){
   h_ratio_SR1_all->GetYaxis()->SetRangeUser(0.2,1.9);
   ratio_add_max=.9;
   ratio_add_min=.2;
}

  TLine* line4 = new TLine(1., gPad->GetUymin() + ratio_add_min, 1.,  gPad->GetUymax() + ratio_add_max );
  TLine* line5 = new TLine(1.5, gPad->GetUymin() + ratio_add_min, 1.5, gPad->GetUymax() + ratio_add_max );
  TLine* line6 = new TLine(2., gPad->GetUymin() + ratio_add_min, 2.,  gPad->GetUymax() + ratio_add_max) ;
  TLine* line7 = new TLine(2.5, gPad->GetUymin() + ratio_add_min, 2.5, gPad->GetUymax() + ratio_add_max );
  line4->Draw("same");
  line5->Draw("same");
  line6->Draw("same");
  line7->Draw("same");

  chara->cd();

  TPad* pad2ggfcr = new TPad("pad2ggfcr","pad2ggfcr", 0.54, 0.68, 1., 1.);
  pad2ggfcr->SetTopMargin(0.05);
  pad2ggfcr->SetBottomMargin(0.028);
  pad2ggfcr->SetLeftMargin(0.025);
  pad2ggfcr->SetRightMargin(0.2);
  pad2ggfcr->Draw();
  pad2ggfcr->cd();
  h_stack_CRGGF->Draw("hist Y+");
  h_stack_CRGGF->SetMaximum(9000);
  h_stack_CRGGF->SetMinimum(0.);
  h_sysErrorPdf_CRGGF->SetFillStyle(3345);
  h_sysErrorPdf_CRGGF->SetFillColor(kGray+2);
  h_data_CRGGF->SetMarkerSize(.8);
  h_sysErrorPdf_CRGGF->Draw("e2 same");
  h_data_CRGGF->Draw("pe same");

  h_stack_CRGGF->GetXaxis()->SetLabelOffset(10);
  h_stack_CRGGF->GetYaxis()->SetLabelOffset(.007);
  h_stack_CRGGF->GetYaxis()->SetLabelSize(0.063);
  //h_stack_CRGGF->GetYaxis()->SetLabelOffset(.015);
  h_stack_CRGGF->GetYaxis()->SetTitle("Events / .50");
 
  h_stack_CRGGF->GetYaxis()->SetTitleSize(0.07);
  h_stack_CRGGF->GetYaxis()->SetTitleOffset(1.2);

  mytext.SetTextSize(0.06);
  subtit=obs_title(input) + " ggF CR";
  double ggf_y_title = 6900;
  //if(input=="lep0_pt" || input=="lep1_pt" || input=="jet0_pt" || input=="jet1_pt") ggf_y_title = 7900;
  mytext.DrawLatex(-0.2,ggf_y_title,subtit.c_str());

  gPad->RedrawAxis();
  
  chara->cd();
  TPad* ratiopad2ggfcr = new TPad("ratiopad2ggfcr","ratiopad2ggfcr", 0.54, 0.505, 1., .68);
  ratiopad2ggfcr->SetTopMargin(.08);
  ratiopad2ggfcr->SetBottomMargin(.3);
  ratiopad2ggfcr->SetLeftMargin(0.02);
  ratiopad2ggfcr->SetRightMargin(0.2);
  ratiopad2ggfcr->Draw();
  ratiopad2ggfcr->cd();
  gPad->SetGridy(1);

  TH1D* h_ratio_CRGGF_all = (TH1D*) h_data_CRGGF->Clone("ratio_all_ggfcr");
  TH1D* h_all_bkg_CRGGF_all = (TH1D*) h_Zjets_CRGGF->Clone("all_bkg_all_ggfcr");
  h_all_bkg_CRGGF_all->Add(h_Fakes_CRGGF);
  h_all_bkg_CRGGF_all->Add(h_top_CRGGF);
  h_all_bkg_CRGGF_all->Add(h_ggf_CRGGF);
  h_all_bkg_CRGGF_all->Add(h_diboson_CRGGF);
  h_all_bkg_CRGGF_all->Add(h_vbf_CRGGF);
  h_ratio_CRGGF_all->Divide(h_all_bkg_CRGGF_all);


  TGraphAsymmErrors* h_ratio_unc_CRGGF_all = new TGraphAsymmErrors();
  for(int i=0; i<v_h_Fakes_SR1.at(0)->GetNbinsX(); i++)
  {
    h_ratio_unc_CRGGF_all->SetPoint(i, h_ratio_CRGGF_all->GetBinCenter(i+1), 1);
    h_ratio_unc_CRGGF_all->SetPointError(i, h_ratio_CRGGF_all->GetBinWidth(i+1)/2,h_ratio_CRGGF_all->GetBinWidth(i+1)/2,h_sysErrorPdf_CRGGF->GetErrorYlow(i)/h_all_bkg_CRGGF_all->GetBinContent(i+1), h_sysErrorPdf_CRGGF->GetErrorYhigh(i)/h_all_bkg_CRGGF_all->GetBinContent(i+1));
  }

  h_ratio_CRGGF_all->Draw("pe Y+");
  h_ratio_unc_CRGGF_all->SetFillColor(kGray+2);
  h_ratio_unc_CRGGF_all->SetFillStyle(3345);
  h_ratio_CRGGF_all->SetMarkerSize(.8);
  h_ratio_unc_CRGGF_all->Draw("e2 same");
  h_ratio_CRGGF_all->Draw("pe same");
  h_ratio_CRGGF_all->GetYaxis()->SetLabelSize(.12);
  h_ratio_CRGGF_all->GetXaxis()->SetLabelSize(0.12);
  h_ratio_CRGGF_all->GetXaxis()->SetLabelOffset(.015);
  h_ratio_CRGGF_all->GetXaxis()->SetTitle("#it{D}_{ggF}");
  h_ratio_CRGGF_all->GetYaxis()->SetTitle("Data / Pred.");
  h_ratio_CRGGF_all->GetYaxis()->SetTitleSize(0.13);
  h_ratio_CRGGF_all->GetXaxis()->SetTitleSize(.13);
  h_ratio_CRGGF_all->GetXaxis()->SetTitleOffset(1.);
  h_ratio_CRGGF_all->GetYaxis()->SetTitleOffset(.6);
  h_ratio_CRGGF_all->GetYaxis()->SetLabelOffset(.008);
  h_ratio_CRGGF_all->GetYaxis()->SetNdivisions(505);
  h_ratio_CRGGF_all->GetXaxis()->SetTickLength(.08);
  h_ratio_CRGGF_all->GetYaxis()->SetRangeUser(0.95,1.05);

  TLine* ggfcr_line = new TLine(-1, 1, 1, 1 );
  ggfcr_line->SetLineColor(kBlack);
  ggfcr_line->Draw("same");
  gPad->RedrawAxis();

  gPad->RedrawAxis();

  chara->cd();
  TPad* padsr2 = new TPad("padsr2","padsr2", 0.0, 0.2, 0.6, .515);
  padsr2->SetTopMargin(0.055);
  padsr2->SetBottomMargin(0.035);
  padsr2->SetRightMargin(0.118);
  padsr2->SetLeftMargin(0.119);
  padsr2->Draw();
  padsr2->cd();

 // gPad->SetLogy();
  h_stack_SR2_all->Draw("hist");
  h_stack_SR2_all->SetMaximum(550);
  if(input=="jet0_pt" || input=="Mll" ) h_stack_SR2_all->SetMaximum(450);
  if(input=="DYll" || input=="lep1_pt") h_stack_SR2_all->SetMaximum(330);
  if(input=="DPhill" || input=="pt_H" || input=="Ptll" ) h_stack_SR2_all->SetMaximum(310);
  if(input=="lep0_pt" || input=="SignedDPhijj") h_stack_SR2_all->SetMaximum(200);
  if(input=="DYjj")  h_stack_SR2_all->SetMaximum(270);
  if(input=="costhetastar") h_stack_SR2_all->SetMaximum(650);

  if(input=="DPhijj") h_stack_SR2_all->GetYaxis()->SetTitle("Events / .50");
  else h_stack_SR2_all->GetYaxis()->SetTitle("Events / 1.0");
  h_stack_SR2_all->GetYaxis()->SetTitleSize(.055);
  h_stack_SR2_all->GetYaxis()->SetTitleOffset(0.95);
  h_stack_SR2_all->GetXaxis()->SetLabelOffset(10);
  h_stack_SR2_all->GetYaxis()->SetLabelOffset(.004);
  h_stack_SR2_all->GetYaxis()->SetLabelSize(.063);
  h_stack_SR2_all->GetYaxis()->SetTitleSize(.07);
  h_stack_SR2_all->GetYaxis()->SetTitleOffset(0.7);

  h_data_all_SR2->SetMarkerSize(.8);
  

  h_sys_all_SR2->SetFillStyle(3345);
  h_sys_all_SR2->SetFillColor(kGray+2);
  h_sys_all_SR2->Draw("e2 same");
  h_data_all_SR2->Draw("pe same");

  mult = 75;
  subtract=35;
  double minus = 3.;
  if( input=="jet0_pt" ) {mult=60; subtract = 30; minus=10;}
  if(input=="lep1_pt"  || input=="Ptll" || input=="DPhill" ) { mult =40; subtract=20;}
  if(input=="DYjj" ) {mult=45; subtract = 30;}
  if( input=="pt_H" ) {mult = 30; subtract = 1;}
  if( input=="DYll") {mult = 35; subtract = 10;}
  if(input=="lep0_pt" || input=="SignedDPhijj" ){mult = 25; subtract = 5; }
  if( input=="Ptll" || input=="DYjj") minus=20;
  if(input=="jet1_pt") subtract = 25;
  if( input=="DPhill" || input=="DYll" || input=="jet0_pt" || input=="lep0_pt" || input=="lep1_pt" || input=="pt_H" || input=="SignedDPhijj" ) minus=10;
  if(input=="Mll") {mult =55; subtract=25; minus=10;}
  TLine* line8 = new TLine(1., 0., 1., gPad->GetUymax() - mult*(gPad->GetUymax()-mult)/gPad->GetUymax() - minus );
  TLine* line9 = new TLine(3., 0., 3., gPad->GetUymax() - mult*(gPad->GetUymax()-mult)/gPad->GetUymax() - minus );
  TLine* line10 = new TLine(5., 0., 5., gPad->GetUymax() - mult*(gPad->GetUymax()-mult)/gPad->GetUymax() - minus );
  TLine* line11 = new TLine(7., 0., 7., gPad->GetUymax() - mult*(gPad->GetUymax()-mult)/gPad->GetUymax() - minus );
  line8->Draw("same");
  line9->Draw("same");
  line10->Draw("same");
  line11->Draw("same");

  mytext.SetTextSize(.06);
  subtit="SR2";
  xstart = 3.5;
  if(input=="SignedDPhijj" || input=="lep1_pt" || input=="jet0_pt" || input=="jet1_pt" || input=="pt_H" || input=="Ptll" || input=="Mll"){
     xstart =3.;
     mytext.DrawLatex(xstart, gPad->GetUymax() - mult*(gPad->GetUymax()-mult)/gPad->GetUymax() + mult/5, subtit.c_str());
   }
   else if (input=="DYll") mytext.DrawLatex(xstart, gPad->GetUymax() - mult*(gPad->GetUymax()-mult)/gPad->GetUymax() + mult/8, subtit.c_str());
   else 
    mytext.DrawLatex(xstart, gPad->GetUymax() - mult*(gPad->GetUymax()-mult)/gPad->GetUymax() + mult/4, subtit.c_str());
  subtit=obs_title(input) + " Bin1";
  if(input=="costhetastar") subtit=obs_title(input) ;
  if(input=="costhetastar") mytext.DrawLatex(-0.2, 470, "Bin1");
  xstart = -.5;
  if(input=="DPhill" || input=="DYll" || input=="DYjj") xstart = -.7;
  if(input=="costhetastar") xstart = -.6;
  mytext.DrawLatex(xstart, gPad->GetUymax() - mult*(gPad->GetUymax()-mult)/gPad->GetUymax() - (mult-subtract),subtit.c_str());
  if(isScale2) {
    if(input == "Mjj") mytext.DrawLatex(.045, 410,"x1");
    if(input == "costhetastar") mytext.DrawLatex(-.1, 420,"x10");
    if(input == "DPhill") mytext.DrawLatex(.05, 230,"x2");
    if(input == "DYll") mytext.DrawLatex(.05, 245,"x2");
    if(input == "lep1_pt") mytext.DrawLatex(-.1, 250,"x1");
    if(input == "jet0_pt") mytext.DrawLatex(-0.1, 330,"x1");
    if(input == "jet1_pt") mytext.DrawLatex(-0.1, 390,"x1");
    if(input == "pt_H") mytext.DrawLatex(-.1, 230,"x1");
    if(input == "Ptll") mytext.DrawLatex(-.1, 230,"x2");
    if(input == "Mll") mytext.DrawLatex(-.1, 340,"x4");
    if(input == "lep0_pt") mytext.DrawLatex(.05, 143,"x2");
    if(input == "DYjj") mytext.DrawLatex(.05, 190,"x1");
  }
  subtit=obs_title(input) + " Bin2";
  if(input=="costhetastar") mytext.DrawLatex(1.8, 470, "Bin2");
  if(input=="costhetastar") subtit=obs_title(input) ;
  xstart = 1.5;
  if(input=="DPhill" || input=="DYll" || input=="DYjj") xstart = 1.3;
  if(input=="lep0_pt" ) xstart = 1.6;
  if(input=="costhetastar") xstart = 1.3;
  mytext.DrawLatex(xstart, gPad->GetUymax() - mult*(gPad->GetUymax()-mult)/gPad->GetUymax() - (mult-subtract),subtit.c_str());
  if(isScale2) {
    if(input=="Mjj") mytext.DrawLatex(2.05, 410,"x6");
    if(input=="costhetastar") mytext.DrawLatex(1.9, 420,"x10");
    if(input=="DPhill") mytext.DrawLatex(2.1, 230,"x2");
    if(input=="DYll") mytext.DrawLatex(2.1, 245,"x4");
    if(input=="lep1_pt") mytext.DrawLatex(1.9, 250,"x1");
    if(input=="jet0_pt") mytext.DrawLatex(1.9, 330,"x4");
    if(input=="jet1_pt") mytext.DrawLatex(1.9, 390,"x4");
    if(input=="pt_H") mytext.DrawLatex(1.9, 230,"x1");
    if(input=="Ptll") mytext.DrawLatex(1.9, 230,"x1");
    if(input=="Mll") mytext.DrawLatex(1.9, 340,"x4");
    if(input=="lep0_pt") mytext.DrawLatex(2.1, 143,"x1");
    if(input=="DYjj") mytext.DrawLatex(2.1, 190,"x1");
  }
  subtit=obs_title(input) + " Bin3";
  if(input=="costhetastar") mytext.DrawLatex(3.8, 470, "Bin3");
  if(input=="costhetastar") subtit=obs_title(input) ;
  xstart = 3.3;
  if(input=="costhetastar") xstart = 3.4;
  mytext.DrawLatex(xstart, gPad->GetUymax() - mult*(gPad->GetUymax()-mult)/gPad->GetUymax() - (mult-subtract),subtit.c_str());
  if(isScale2) { 
  if(input=="Mjj") mytext.DrawLatex(3.85, 410,"x10");
  if(input=="costhetastar") mytext.DrawLatex(3.9, 420,"x10");
  if(input=="DPhill") mytext.DrawLatex(3.9, 230,"x2");
  if(input=="DYll") mytext.DrawLatex(3.9, 245,"x4");
  if(input=="lep1_pt") mytext.DrawLatex(3.6, 250,"x2");
  if(input=="jet0_pt") mytext.DrawLatex(3.6, 330,"x6");
  if(input=="jet1_pt") mytext.DrawLatex(3.6, 390,"x6");
  if(input=="pt_H") mytext.DrawLatex(3.6, 230,"x2");
  if(input=="Ptll") mytext.DrawLatex(3.6, 230,"x1");
  if(input=="Mll") mytext.DrawLatex(3.6, 340,"x4");
  if(input=="lep0_pt") mytext.DrawLatex(3.9, 143,"x1");
  if(input=="DYjj") mytext.DrawLatex(3.9, 190,"x2");
  }
  subtit=obs_title(input) + " Bin4";
  if(input=="costhetastar") subtit=obs_title(input) ;
  if(input=="costhetastar") mytext.DrawLatex(5.8, 470, "Bin4");
  xstart = 5.3;
  if(input=="costhetastar") xstart = 5.3;
  mytext.DrawLatex(xstart, gPad->GetUymax() - mult*(gPad->GetUymax()-mult)/gPad->GetUymax() - (mult-subtract),subtit.c_str());
  if(isScale2) {
    if(input=="Mjj") mytext.DrawLatex(5.85, 410,"x14");
    if(input=="costhetastar") mytext.DrawLatex(5.9, 420,"x10");
    if(input=="DPhill") mytext.DrawLatex(5.9, 230,"x2");
    if(input=="DYll") mytext.DrawLatex(5.9, 245,"x4");
    if(input=="lep1_pt") mytext.DrawLatex(5.8, 250,"x2");
    if(input=="jet0_pt") mytext.DrawLatex(5.8, 330,"x6");
    if(input=="jet1_pt") mytext.DrawLatex(5.8, 390,"x6");
    if(input=="pt_H") mytext.DrawLatex(5.8, 230,"x8");
    if(input=="Ptll") mytext.DrawLatex(5.8, 230,"x2");
    if(input=="Mll") mytext.DrawLatex(5.8, 340,"x1");
    if(input=="lep0_pt") mytext.DrawLatex(5.9, 143,"x1");
    if(input=="DYjj") mytext.DrawLatex(5.9, 190,"x2");
  }
  subtit=obs_title(input) + " Bin5";
  if(input=="costhetastar") mytext.DrawLatex(7.8, 470, "Bin5");
  if(input=="costhetastar") subtit=obs_title(input) ;
  xstart = 7.3;
  if(input=="DPhill" || input=="DYjj") xstart = 7.2;
  if(input=="lep0_pt" || input=="costhetastar"|| input=="DYll" || input=="DYjj") xstart = 7.2;
  mytext.DrawLatex(xstart, gPad->GetUymax() - mult*(gPad->GetUymax()-mult)/gPad->GetUymax() - (mult-subtract),subtit.c_str());
  if(isScale2) {
    if(input=="Mjj") mytext.DrawLatex(7.8, 410,"x40");
    if(input=="costhetastar") mytext.DrawLatex(7.9, 420,"x1");
    if(input=="DPhill") mytext.DrawLatex(7.9, 230,"x1");
    if(input=="DYll") mytext.DrawLatex(7.9, 245,"x1");
    if(input=="lep0_pt") mytext.DrawLatex(7.9, 143,"x1");
    if(input=="DYjj") mytext.DrawLatex(7.9, 190,"x4");
  }

  chara->cd();
  TPad* subpadsr2 = new TPad("subpadsr2","subpadsr2", 0, 0.0025, 0.6, .2);
  subpadsr2->SetTopMargin(0.08);
  subpadsr2->SetBottomMargin(0.4);
  subpadsr2->SetRightMargin(0.118);
  subpadsr2->SetLeftMargin(0.119);
  subpadsr2->Draw();
  subpadsr2->cd();
  gPad->SetGridy(1);

  TH1D* h_ratio_SR2_all = (TH1D*) h_data_all_SR2->Clone("ratio_sr2");
  TH1D* h_all_bkg_SR2_all = (TH1D*) h_zjets_all_SR2->Clone("all_bkg_sr2");
  h_all_bkg_SR2_all->Add(h_fakes_all_SR2);
  h_all_bkg_SR2_all->Add(h_top_all_SR2);
  h_all_bkg_SR2_all->Add(h_ggf_all_SR2);
  h_all_bkg_SR2_all->Add(h_diboson_all_SR2);
  h_all_bkg_SR2_all->Add(h_vbf_all_SR2);
  h_ratio_SR2_all->Divide(h_all_bkg_SR2_all);

  TGraphAsymmErrors* h_ratio_unc_SR2_all = new TGraphAsymmErrors();
  totalBins=20;
  if(!(input=="Mjj" || input=="lep0_pt" || input=="costhetastar" || input=="DPhill" || input=="DYll" )) totalBins=16;
  for(int i=0; i<totalBins; i++)
  {
    h_ratio_unc_SR2_all->SetPoint(i, (binEdges_all_SR2[i+1]-binEdges_all_SR2[i])/2 + binEdges_all_SR2[i], 1);
    h_ratio_unc_SR2_all->SetPointError(i, (binEdges_all_SR2[i+1]-binEdges_all_SR2[i])/2,(binEdges_all_SR2[i+1]-binEdges_all_SR2[i])/2,h_sys_all_SR2->GetErrorYlow(i)/h_all_bkg_SR2_all->GetBinContent(i+1), h_sys_all_SR2->GetErrorYhigh(i)/h_all_bkg_SR2_all->GetBinContent(i+1));
  }

  h_ratio_SR2_all->Draw("pe");
  h_ratio_unc_SR2_all->SetFillColor(kGray+2);
  h_ratio_unc_SR2_all->SetFillStyle(3345);
  h_ratio_unc_SR2_all->Draw("e2 same");
  h_ratio_SR2_all->Draw("pe same");
  h_ratio_SR2_all->GetYaxis()->SetLabelSize(.11);
 // h_ratio_SR2_all->GetXaxis()->SetLabelSize(.12);
  h_ratio_SR2_all->GetYaxis()->SetLabelOffset(.005);
 // h_ratio_SR1_all->GetXaxis()->SetLabelOffset(1.);
  h_ratio_SR2_all->GetYaxis()->SetNdivisions(505);
  h_ratio_SR2_all->GetYaxis()->CenterTitle(true);
  h_ratio_SR2_all->GetYaxis()->SetTitleOffset(.45);
  h_ratio_SR2_all->GetXaxis()->SetTitleOffset(.8);
 
  h_ratio_SR2_all->GetYaxis()->SetTitleSize(.11);
  h_ratio_SR2_all->GetYaxis()->SetTitle("Data / Pred.");
  h_ratio_SR2_all->GetXaxis()->SetTitleSize(.12);
  h_ratio_SR2_all->GetXaxis()->SetTitle("#it{D}_{Top+VV}");

   h_ratio_SR2_all->GetXaxis()->SetTickLength(.08);

   h_ratio_SR2_all->GetXaxis()->SetLabelOffset(10);
   
  
  h_ratio_SR2_all->GetYaxis()->SetRangeUser(0.5,1.4);
  TLine* line12 = new TLine(1., 0.5, 1., 1.4 );
  TLine* line13 = new TLine(3., 0.5, 3., 1.4 );
  TLine* line14 = new TLine(5., 0.5, 5., 1.4 );
  TLine* line15 = new TLine(7., 0.5, 7., 1.4 );
  if(input=="jet1_pt"){
   h_ratio_SR2_all->GetYaxis()->SetRangeUser(0.6,1.6);
   line12 = new TLine(1., 0.6, 1., 1.6 );
   line13 = new TLine(3., 0.6, 3., 1.6 );
   line14 = new TLine(5., 0.6, 5., 1.6 );
   line15 = new TLine(7., 0.6, 7., 1.6 );
   mytext.SetTextSize(.1);
   mytext.DrawLatex(-1, .45, "-1.0");
   mytext.DrawLatex(1., .45, "-1.0");
   mytext.DrawLatex(3., .45, "-1.0");
   mytext.DrawLatex(5., .45, "-1.0");
   mytext.DrawLatex(0.8, 1.63, "1.0");
   mytext.DrawLatex(2.8, 1.63, "1.0");
   mytext.DrawLatex(4.8, 1.63, "1.0");
   mytext.DrawLatex(6.8, 1.63, "1.0");


 }
 else {
   mytext.SetTextSize(.1);
   mytext.DrawLatex(-1.2, .35, "-1.0");
   mytext.DrawLatex(.8, .35, "-1.0");
   mytext.DrawLatex(2.8, .35, "-1.0");
   mytext.DrawLatex(4.8, .35, "-1.0");
   if( (input=="Mjj" || input=="lep0_pt" || input=="costhetastar" || input=="DPhill" || input=="DYll" ) )  mytext.DrawLatex(6.8, .35, "-1.0");
   
   mytext.DrawLatex(0.8, 1.42, "1.0");
   mytext.DrawLatex(2.8, 1.42, "1.0");
   mytext.DrawLatex(4.8, 1.42, "1.0");
   mytext.DrawLatex(6.8, 1.42, "1.0");
   mytext.DrawLatex(8.7, 1.42, "1.0");
 }
  
  line12->Draw("same");
  line13->Draw("same");
  line14->Draw("same");
  line15->Draw("same");

  TLine* sr2_line = new TLine(-1, 1, 9, 1 );
  if(input=="pt_H" || input=="Ptll"|| input=="Mll" || input == "lep1_pt" || input=="jet1_pt" || input=="SignedDPhijj") sr2_line = new TLine(-1, 1, 7, 1 );
  sr2_line->SetLineColor(kBlack);
  sr2_line->Draw("same");
  gPad->RedrawAxis();


  gPad->RedrawAxis();
  chara->cd();

  TPad* pad4dycr = new TPad("pad4dycr", "pad4dycr", .54, 0.2, 1., .5);

  pad4dycr->SetTopMargin(0.012);
  pad4dycr->SetBottomMargin(0.035);
  pad4dycr->SetLeftMargin(0.03);
  pad4dycr->SetRightMargin(.2);

  pad4dycr->Draw();
  pad4dycr->cd();


  h_stack_DYCR->Draw("hist Y+");
  h_stack_DYCR->SetMaximum(260);
  h_stack_DYCR->SetMinimum(0.);
  h_data_DYCR->Draw("pe same");
 // h_stack_DYCR->GetXaxis()->SetLimits(40,150);
  h_sysErrorPdf_DYCR->SetFillColor(kGray+2);
  h_sysErrorPdf_DYCR->SetFillStyle(3345);
  h_data_DYCR->SetMarkerSize(.8);
  h_sysErrorPdf_DYCR->Draw("e2 same");
  h_data_DYCR->Draw("pe same");
  h_stack_DYCR->GetXaxis()->SetLabelOffset(1.);
  h_stack_DYCR->GetYaxis()->SetLabelOffset(.006);
  h_stack_DYCR->GetYaxis()->SetLabelSize(.068);
  h_stack_DYCR->GetYaxis()->SetTitle("Events / 22 GeV");
  h_stack_DYCR->GetYaxis()->SetTitleSize(0.073);
  h_stack_DYCR->GetYaxis()->SetTitleOffset(1.1);

  mytext.SetTextSize(.065);

  double zjets_y_title = 220;
 // if( input=="lep1_pt" || input=="jet0_pt" || input=="jet1_pt") zjets_y_title = 232.5;
  subtit=obs_title(input) + " Z+jets CR";
  mytext.DrawLatex(88,zjets_y_title,subtit.c_str());

  TLegend* legendggfcr = new TLegend(0.38,0.42,.78,0.73);
  legendggfcr->SetBorderSize(0);
  legendggfcr->SetFillStyle(0);
  legendggfcr->SetTextSize(0.);
  legendggfcr->SetNColumns(2);
  legendggfcr->AddEntry(h_data_CRGGF, "#bf{Data}", "p");
  legendggfcr->AddEntry(h_sysErrorPdf_CRGGF, "#bf{Uncertainty}", "f");
  legendggfcr->AddEntry(h_vbf_CRGGF,"#bf{H_{VBF}}", "f");
  legendggfcr->AddEntry(h_ggf_CRGGF, "#bf{H_{other}}", "f");
  legendggfcr->AddEntry(h_top_CRGGF, "#bf{Top}","f");
  legendggfcr->AddEntry(h_diboson_CRGGF, "#bf{VV}", "f");
  legendggfcr->AddEntry(h_Zjets_CRGGF, "#bf{Z/#scale[1.1]{#gamma}*+jets}", "f");
  legendggfcr->AddEntry(h_Fakes_CRGGF, "#bf{Mis-Id}", "f");
  
  legendggfcr->Draw();

  chara->cd();
  TPad* ratiopad4dycr = new TPad("ratiopad4dycr","ratiopad4dycr", .54, 0.0025, 1., .2);

  ratiopad4dycr->SetLeftMargin(0.03);//(0.002);
  ratiopad4dycr->SetRightMargin(0.2);
  ratiopad4dycr->SetBottomMargin(.4);
  ratiopad4dycr->SetTopMargin(0.08);
  ratiopad4dycr->Draw();
  ratiopad4dycr->cd();
  gPad->SetGridy(1);
  TH1D* h_ratio_DYCR_all = (TH1D*) h_data_DYCR->Clone("ratio_DYCR_all");
  TH1D* h_all_bkg_DYCR_all = (TH1D*) h_Zjets_DYCR->Clone("all_bkg_DYCR_all");
  h_all_bkg_DYCR_all->Add(h_Fakes_DYCR);
  h_all_bkg_DYCR_all->Add(h_top_DYCR);
  h_all_bkg_DYCR_all->Add(h_ggf_DYCR);
  h_all_bkg_DYCR_all->Add(h_diboson_DYCR);
  h_all_bkg_DYCR_all->Add(h_vbf_DYCR);
  h_ratio_DYCR_all->Divide(h_all_bkg_DYCR_all);

  TGraphAsymmErrors* h_ratio_unc_DYCR_all = new TGraphAsymmErrors();

  for(int i=0; i<h_data_DYCR->GetNbinsX(); i++)
  {
    h_ratio_unc_DYCR_all->SetPoint(i, h_ratio_DYCR_all->GetBinCenter(i+1), 1);
    h_ratio_unc_DYCR_all->SetPointError(i, h_ratio_DYCR_all->GetBinWidth(i+1)/2,h_ratio_DYCR_all->GetBinWidth(i+1)/2,h_sysErrorPdf_DYCR->GetErrorYlow(i)/h_all_bkg_DYCR_all->GetBinContent(i+1), h_sysErrorPdf_DYCR->GetErrorYhigh(i)/h_all_bkg_DYCR_all->GetBinContent(i+1));
  }

/*  
  TLine *l=new TLine(m_xminimum,1.0,m_xmaximum,1.0);
  l->SetLineColor(kBlack);
  l->Draw("same");
*/
  h_ratio_DYCR_all->Draw("pe Y+");
  h_ratio_unc_DYCR_all->SetFillColor(kGray+2);
  h_ratio_unc_DYCR_all->SetFillStyle(3345);
  h_ratio_DYCR_all->SetMarkerSize(.8);
  h_ratio_unc_DYCR_all->Draw("e2 same");
  h_ratio_DYCR_all->Draw("pe same");

  h_ratio_DYCR_all->GetYaxis()->SetLabelSize(.106);
  h_ratio_DYCR_all->GetXaxis()->SetLabelSize(.106);
  h_ratio_DYCR_all->GetYaxis()->SetLabelOffset(.008);
  h_ratio_DYCR_all->GetXaxis()->SetLabelOffset(.01);
  h_ratio_DYCR_all->GetYaxis()->SetNdivisions(505);

  h_ratio_DYCR_all->GetYaxis()->SetTitle("Data / Pred.");

  h_ratio_DYCR_all->GetXaxis()->SetTickLength(.06);


  h_ratio_DYCR_all->GetXaxis()->SetTitleOffset(.9);
  h_ratio_DYCR_all->GetYaxis()->SetTitleOffset(.7);


  h_ratio_DYCR_all->GetXaxis()->SetTitleSize(.12);
  h_ratio_DYCR_all->GetYaxis()->SetTitleSize(.11);

  h_ratio_DYCR_all->GetXaxis()->SetTitle("#it{m}_{T} [GeV]");

  h_ratio_DYCR_all->GetYaxis()->SetRangeUser(0.7,1.35);

  TArrow *ar6 = new TArrow(140,1.15,140,1.25, .007,">");

  ar6->SetLineColor(kRed);
  ar6->SetFillColor(kWhite);
  ar6->Draw();

  TLine* dycr_line = new TLine(40, 1, 150, 1 );
  dycr_line->SetLineColor(kBlack);
  dycr_line->Draw("same");
  gPad->RedrawAxis();
  
  chara->cd();
  TLatex atlastex;
  atlastex.SetTextSize(.023);
  atlastex.DrawLatex(0.092, 0.95, "#it{#bf{#scale[1.2]{ATLAS}}}  Internal");
  atlastex.DrawLatex(.58, 0.95, "#sqrt{#scale[.8]{s}} #scale[.8]{= 13 TeV,} #scale[.8]{139 fb^{-1}}");


  std::string outfilename = "post_fit_bdt_"+input+".pdf";
  chara->SaveAs(outfilename.c_str());
  outfilename = "pos_fit_bdt_"+input+".eps";
  chara->SaveAs(outfilename.c_str());
  outfilename = "pos_fit_bdt_"+input+".png";
  chara->SaveAs(outfilename.c_str());

}
