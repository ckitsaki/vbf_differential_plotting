// THIS SCRIPT PRODUCES THE INCLUSIVE POST FIT BDT DISTRIBUTIONS. THE INPUT FILE USED SITS INSIDE postfit_bdt_input FOLDER
// HOW TO USE:
// > root -l
// > .L post_fit_bdt_inc.C
// > post_fit_bdt_inc()
#include "Style/AtlasStyle.C"

TCanvas* DumpCanvasFromFile(std::string input, std::string canvasName)
{
  std::string filename = "../../postfit_bdt_input/fitResults_inc1.root";//"/eos/user/c/chenj/Rivet/analysisbase/final_result/postfitResults/fitResults_"+input+".root";
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

void chooseBinning(std::string input, std::string canvasName, int &nbins, double* &binEdges, int Nbins_SR1, int Nbins_SR2, bool differentChoice)
{
  if(canvasName=="fitRes_obs_x_CRZjets_MT_CRZjets_MT"){
    nbins = 5;
    binEdges= new double[nbins+1]{40,62,84,106,128,150};
  } 
  if(input!="SignedDPhijj" && canvasName=="fitRes_obs_x_CRTop_" + std::to_string(Nbins_SR2-1) + "_bdt_TopWWAll_CRTop_" + std::to_string(Nbins_SR2-1) + "_bdt_TopWWAll"){
    nbins = 2;
    binEdges= new double[nbins+1]{-1,0,1};
  }
  if(canvasName=="fitRes_obs_x_CRGGF1_bdt_ggFCR1_CRGGF1_bdt_ggFCR1"){
    nbins = 4;
    binEdges= new double[nbins+1]{-1,-0.5,0.,0.5,1};
  }
  if(canvasName=="fitRes_obs_x_SRVBF_" + std::to_string(Nbins_SR1-1) + "_bdt_vbf_" + input + "_SRVBF_" + std::to_string(Nbins_SR1-1) + "_bdt_vbf_" + input){
    nbins = 4;
    binEdges= new double[nbins+1]{0.5, 0.7, 0.86, 0.94, 1.0};
  } 
  if( (input=="SignedDPhijj" || input=="inc") && canvasName=="fitRes_obs_x_CRTop_" + std::to_string(Nbins_SR2-1) + "_bdt_TopWWAll_CRTop_" + std::to_string(Nbins_SR2-1) + "_bdt_TopWWAll")
  {
  	nbins = 4;
  	binEdges= new double[nbins+1]{-1,-0.5,0.,0.5,1.};
  }
  if(input=="DYjj" && differentChoice && canvasName=="fitRes_obs_x_SRVBF_" + std::to_string(Nbins_SR1-1) + "_bdt_vbf_" + input + "_SRVBF_" + std::to_string(Nbins_SR1-1) + "_bdt_vbf_" + input)
  {
  	nbins = 4;
  	binEdges= new double[nbins+1]{.5,.7,.86,1.};
  }
}

RooCurve* GetRooCurveFromFile(std::string sample, TCanvas* canvas)
{
  RooCurve* rc = (RooCurve*)canvas->FindObject(sample.c_str());

  return rc;
}
void post_fit_inc(std::string input="inc", int Nbins_SR1=1, int Nbins_SR2=1)
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
  chooseBinning(input, canvasName, nbins_DYCR, binEdges_DYCR, 0, 0, false);
  std::cout<<nbins_DYCR<<" "<<binEdges_DYCR[0]<<std::endl;
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
  chooseBinning(input, canvasName, nbins_CRGGF, binEdges_CRGGF, 0, 0, false);
  std::cout<<nbins_CRGGF<<" "<<binEdges_CRGGF[0]<<std::endl;
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
//  std::cout<<canvasName<<" "<<nbins_SR2<<" "<<binEdges_SR2[0]<<std::endl;
  for(int ihisto = 0; ihisto<v_rc_vbf_SR2.size(); ihisto++)
  {
  	int nbins_SR2;
  	double *binEdges_SR2;
  	if(input=="SignedDPhijj") differentChoice=true;
  	
  	chooseBinning(input, canvasName, nbins_SR2, binEdges_SR2, 0, Nbins_SR2, differentChoice);
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
//  std::cout<<canvasName<<" "<<nbins_SR1<<" "<<binEdges_SR1[0]<<std::endl;
  for(int ihisto = 0; ihisto<v_rc_vbf_SR1.size(); ihisto++)
  {
  	int nbins_SR1;
  	double *binEdges_SR1;
  	if(input=="DYjj" && ihisto==v_rc_vbf_SR1.size()-1) differentChoice=true;
  	
  	chooseBinning(input, canvasName, nbins_SR1, binEdges_SR1, Nbins_SR1, 0, differentChoice);

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
/* 
  TCanvas *k = new TCanvas();
  k->Divide(3,3);
  k->cd(1);
  rc_Zjets_DYCR->Draw("ALF");

  rc_Zjets_DYCR->SetFillColor(kGreen+2);
  rc_Zjets_DYCR->SetLineColor(kBlack);
  rc_vh_DYCR->Draw("same LF");
  rh_Data_DYCR->Draw("same");
  rc_sysErrorPdf_DYCR->SetFillColor(kGray+10);
  rc_sysErrorPdf_DYCR->SetFillStyle(3004);
  rc_sysErrorPdf_DYCR->Draw("same F");
*/
/*
  k->cd(2);
  rc_Zjets_CRGGF->Draw("ALF");

  rc_Zjets_CRGGF->SetFillColor(kGreen+2);
  rc_Zjets_CRGGF->SetLineColor(kBlack);
  rc_vh_CRGGF->Draw("same LF");
  rh_Data_CRGGF->Draw("same");
  rc_sysErrorPdf_CRGGF->SetFillColor(kGray+10);
  rc_sysErrorPdf_CRGGF->SetFillStyle(3004);
  rc_sysErrorPdf_CRGGF->Draw("same F");
  rc_Zjets_CRGGF->GetYaxis()->SetRangeUser(0,14000);
*/  
 // k->SaveAs("roocurves.pdf");
  
  std::cout<<"DATA=====>\n";
  std::cout<<"DYCR: "<<rh_Data_DYCR->GetN()<<std::endl;
  std::cout<<"GGFCR: "<<rh_Data_CRGGF->GetN()<<std::endl;
  std::cout<<"SR1: "<<v_rh_data_SR1.at(0)->GetN()<<std::endl;
  std::cout<<"SR2: "<<v_rh_data_SR2.at(0)->GetN()<<std::endl;

  std::cout<<"MC ======> \n";
  std::cout<<"DYCR: "<<rc_Zjets_DYCR->GetN()<<std::endl;
  std::cout<<"GGFCR: "<<rc_Zjets_CRGGF->GetN()<<std::endl;
  std::cout<<"SR1: "<<v_rc_Zjets_SR1.at(0)->GetN()<<std::endl;
  std::cout<<"SR2: "<<v_rc_Zjets_SR2.at(0)->GetN()<<std::endl;


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

  // error band SR1
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

  // error band SR1
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
  		std::cout<<"binSR1: "<<ibin_SR1<<std::endl;
    	double y = v_h_Zjets_SR1.at(ibin_SR1)->GetBinContent(ibin+1)/v_h_Zjets_SR1.at(ibin_SR1)->GetBinWidth(ibin+1)+v_h_vh_SR1.at(ibin_SR1)->GetBinContent(ibin+1)/v_h_Zjets_SR1.at(ibin_SR1)->GetBinWidth(ibin+1)+v_h_htt_SR1.at(ibin_SR1)->GetBinContent(ibin+1)/v_h_Zjets_SR1.at(ibin_SR1)->GetBinWidth(ibin+1)+v_h_vbf_SR1.at(ibin_SR1)->GetBinContent(ibin+1)/v_h_Zjets_SR1.at(ibin_SR1)->GetBinWidth(ibin+1)+v_h_top_SR1.at(ibin_SR1)->GetBinContent(ibin+1)/v_h_Zjets_SR1.at(ibin_SR1)->GetBinWidth(ibin+1)+v_h_diboson_SR1.at(ibin_SR1)->GetBinContent(ibin+1)/v_h_Zjets_SR1.at(ibin_SR1)->GetBinWidth(ibin+1)+v_h_ggf_SR1.at(ibin_SR1)->GetBinContent(ibin+1)/v_h_Zjets_SR1.at(ibin_SR1)->GetBinWidth(ibin+1)+v_h_Fakes_SR1.at(ibin_SR1)->GetBinContent(ibin+1)/v_h_Zjets_SR1.at(ibin_SR1)->GetBinWidth(ibin+1)+v_h_Vgamma_SR1.at(ibin_SR1)->GetBinContent(ibin+1)/v_h_Zjets_SR1.at(ibin_SR1)->GetBinWidth(ibin+1); 
    	v_h_sysErr_SR1.at(ibin_SR1)->SetPoint(ibin, v_h_Zjets_SR1.at(ibin_SR1)->GetBinCenter(ibin+1), y);
    	v_h_sysErr_SR1.at(ibin_SR1)->SetPointEXlow(ibin, v_h_Zjets_SR1.at(ibin_SR1)->GetBinWidth(ibin+1)/2);
    	v_h_sysErr_SR1.at(ibin_SR1)->SetPointEXhigh(ibin, v_h_Zjets_SR1.at(ibin_SR1)->GetBinWidth(ibin+1)/2);
 	}

/*
 	v_h_Zjets_SR1.at(ibin_SR1)->Sumw2();
  	v_h_vh_SR1.at(ibin_SR1)->Sumw2();
 	v_h_htt_SR1.at(ibin_SR1)->Sumw2();
  	v_h_vbf_SR1.at(ibin_SR1)->Sumw2();
  	v_h_top_SR1.at(ibin_SR1)->Sumw2();
  	v_h_diboson_SR1.at(ibin_SR1)->Sumw2();
  	v_h_ggf_SR1.at(ibin_SR1)->Sumw2();
  	v_h_Fakes_SR1.at(ibin_SR1)->Sumw2();
  	v_h_Vgamma_SR1.at(ibin_SR1)->Sumw2();
*/
  	// error band SR1
  	int ibin = 0;
  	double total_mc = (v_h_Zjets_SR1.at(0)->GetBinContent(ibin+1)/v_h_Zjets_SR1.at(0)->GetBinWidth(ibin+1)+v_h_vh_SR1.at(0)->GetBinContent(ibin+1)/v_h_Zjets_SR1.at(0)->GetBinWidth(ibin+1)+v_h_htt_SR1.at(0)->GetBinContent(ibin+1)/v_h_Zjets_SR1.at(0)->GetBinWidth(ibin+1)+v_h_vbf_SR1.at(0)->GetBinContent(ibin+1)/v_h_Zjets_SR1.at(0)->GetBinWidth(ibin+1)+v_h_top_SR1.at(0)->GetBinContent(ibin+1)/v_h_Zjets_SR1.at(0)->GetBinWidth(ibin+1)+v_h_diboson_SR1.at(0)->GetBinContent(ibin+1)/v_h_Zjets_SR1.at(0)->GetBinWidth(ibin+1)+v_h_ggf_SR1.at(0)->GetBinContent(ibin+1)/v_h_Zjets_SR1.at(0)->GetBinWidth(ibin+1)+v_h_Fakes_SR1.at(0)->GetBinContent(ibin+1)/v_h_Zjets_SR1.at(0)->GetBinWidth(ibin+1)+v_h_Vgamma_SR1.at(0)->GetBinContent(ibin+1)/v_h_Zjets_SR1.at(0)->GetBinWidth(ibin+1) );
  	v_h_sysErr_SR1.at(0)->SetPointEYlow(0, std::abs( total_mc-v_rc_sysErrorPdf_SR1.at(0)->GetPointY(26)/v_h_Zjets_SR1.at(0)->GetBinWidth(ibin+1)));
  	v_h_sysErr_SR1.at(0)->SetPointEYhigh(0, std::abs(total_mc-v_rc_sysErrorPdf_SR1.at(0)->GetPointY(3)/v_h_Zjets_SR1.at(0)->GetBinWidth(ibin+1)));
  	ibin =1;
  	total_mc = (v_h_Zjets_SR1.at(0)->GetBinContent(ibin+1)/v_h_Zjets_SR1.at(0)->GetBinWidth(ibin+1)+v_h_vh_SR1.at(0)->GetBinContent(ibin+1)/v_h_Zjets_SR1.at(0)->GetBinWidth(ibin+1)+v_h_htt_SR1.at(0)->GetBinContent(ibin+1)/v_h_Zjets_SR1.at(0)->GetBinWidth(ibin+1)+v_h_vbf_SR1.at(0)->GetBinContent(ibin+1)/v_h_Zjets_SR1.at(0)->GetBinWidth(ibin+1)+v_h_top_SR1.at(0)->GetBinContent(ibin+1)/v_h_Zjets_SR1.at(0)->GetBinWidth(ibin+1)+v_h_diboson_SR1.at(0)->GetBinContent(ibin+1)/v_h_Zjets_SR1.at(0)->GetBinWidth(ibin+1)+v_h_ggf_SR1.at(0)->GetBinContent(ibin+1)/v_h_Zjets_SR1.at(0)->GetBinWidth(ibin+1)+v_h_Fakes_SR1.at(0)->GetBinContent(ibin+1)/v_h_Zjets_SR1.at(0)->GetBinWidth(ibin+1)+v_h_Vgamma_SR1.at(0)->GetBinContent(ibin+1)/v_h_Zjets_SR1.at(0)->GetBinWidth(ibin+1) );
  	v_h_sysErr_SR1.at(0)->SetPointEYlow(1, std::abs(total_mc-v_rc_sysErrorPdf_SR1.at(0)->GetPointY(24)/v_h_Zjets_SR1.at(0)->GetBinWidth(ibin+1)));
  	v_h_sysErr_SR1.at(0)->SetPointEYhigh(1, std::abs(total_mc-v_rc_sysErrorPdf_SR1.at(0)->GetPointY(5)/v_h_Zjets_SR1.at(0)->GetBinWidth(ibin+1)));
  	ibin = 2;
 	total_mc = (v_h_Zjets_SR1.at(0)->GetBinContent(ibin+1)/v_h_Zjets_SR1.at(0)->GetBinWidth(ibin+1)+v_h_vh_SR1.at(0)->GetBinContent(ibin+1)/v_h_Zjets_SR1.at(0)->GetBinWidth(ibin+1)+v_h_htt_SR1.at(0)->GetBinContent(ibin+1)/v_h_Zjets_SR1.at(0)->GetBinWidth(ibin+1)+v_h_vbf_SR1.at(0)->GetBinContent(ibin+1)/v_h_Zjets_SR1.at(0)->GetBinWidth(ibin+1)+v_h_top_SR1.at(0)->GetBinContent(ibin+1)/v_h_Zjets_SR1.at(0)->GetBinWidth(ibin+1)+v_h_diboson_SR1.at(0)->GetBinContent(ibin+1)/v_h_Zjets_SR1.at(0)->GetBinWidth(ibin+1)+v_h_ggf_SR1.at(0)->GetBinContent(ibin+1)/v_h_Zjets_SR1.at(0)->GetBinWidth(ibin+1)+v_h_Fakes_SR1.at(0)->GetBinContent(ibin+1)/v_h_Zjets_SR1.at(0)->GetBinWidth(ibin+1)+v_h_Vgamma_SR1.at(0)->GetBinContent(ibin+1)/v_h_Zjets_SR1.at(0)->GetBinWidth(ibin+1) );
  	v_h_sysErr_SR1.at(0)->SetPointEYlow(2, std::abs(total_mc-v_rc_sysErrorPdf_SR1.at(0)->GetPointY(22)/v_h_Zjets_SR1.at(0)->GetBinWidth(ibin+1)));
  	v_h_sysErr_SR1.at(0)->SetPointEYhigh(2, std::abs(total_mc-v_rc_sysErrorPdf_SR1.at(0)->GetPointY(7)/v_h_Zjets_SR1.at(0)->GetBinWidth(ibin+1)));
  	ibin = 3;
  	total_mc = (v_h_Zjets_SR1.at(0)->GetBinContent(ibin+1)/v_h_Zjets_SR1.at(0)->GetBinWidth(ibin+1)+v_h_vh_SR1.at(0)->GetBinContent(ibin+1)/v_h_Zjets_SR1.at(0)->GetBinWidth(ibin+1)+v_h_htt_SR1.at(0)->GetBinContent(ibin+1)/v_h_Zjets_SR1.at(0)->GetBinWidth(ibin+1)+v_h_vbf_SR1.at(0)->GetBinContent(ibin+1)/v_h_Zjets_SR1.at(0)->GetBinWidth(ibin+1)+v_h_top_SR1.at(0)->GetBinContent(ibin+1)/v_h_Zjets_SR1.at(0)->GetBinWidth(ibin+1)+v_h_diboson_SR1.at(0)->GetBinContent(ibin+1)/v_h_Zjets_SR1.at(0)->GetBinWidth(ibin+1)+v_h_ggf_SR1.at(0)->GetBinContent(ibin+1)/v_h_Zjets_SR1.at(0)->GetBinWidth(ibin+1)+v_h_Fakes_SR1.at(0)->GetBinContent(ibin+1)/v_h_Zjets_SR1.at(0)->GetBinWidth(ibin+1)+v_h_Vgamma_SR1.at(0)->GetBinContent(ibin+1)/v_h_Zjets_SR1.at(0)->GetBinWidth(ibin+1) );
  	v_h_sysErr_SR1.at(0)->SetPointEYlow(3, std::abs(total_mc-v_rc_sysErrorPdf_SR1.at(0)->GetPointY(20)/v_h_Zjets_SR1.at(0)->GetBinWidth(ibin+1)));
  	v_h_sysErr_SR1.at(0)->SetPointEYhigh(3, std::abs(total_mc-v_rc_sysErrorPdf_SR1.at(0)->GetPointY(9)/v_h_Zjets_SR1.at(0)->GetBinWidth(ibin+1)));
  	ibin = 4;
  	total_mc = (v_h_Zjets_SR1.at(0)->GetBinContent(ibin+1)/v_h_Zjets_SR1.at(0)->GetBinWidth(ibin+1)+v_h_vh_SR1.at(0)->GetBinContent(ibin+1)/v_h_Zjets_SR1.at(0)->GetBinWidth(ibin+1)+v_h_htt_SR1.at(0)->GetBinContent(ibin+1)/v_h_Zjets_SR1.at(0)->GetBinWidth(ibin+1)+v_h_vbf_SR1.at(0)->GetBinContent(ibin+1)/v_h_Zjets_SR1.at(0)->GetBinWidth(ibin+1)+v_h_top_SR1.at(0)->GetBinContent(ibin+1)/v_h_Zjets_SR1.at(0)->GetBinWidth(ibin+1)+v_h_diboson_SR1.at(0)->GetBinContent(ibin+1)/v_h_Zjets_SR1.at(0)->GetBinWidth(ibin+1)+v_h_ggf_SR1.at(0)->GetBinContent(ibin+1)/v_h_Zjets_SR1.at(0)->GetBinWidth(ibin+1)+v_h_Fakes_SR1.at(0)->GetBinContent(ibin+1)/v_h_Zjets_SR1.at(0)->GetBinWidth(ibin+1)+v_h_Vgamma_SR1.at(0)->GetBinContent(ibin+1)/v_h_Zjets_SR1.at(0)->GetBinWidth(ibin+1) );
  	v_h_sysErr_SR1.at(0)->SetPointEYlow(4, std::abs(total_mc-v_rc_sysErrorPdf_SR1.at(0)->GetPointY(18)/v_h_Zjets_SR1.at(0)->GetBinWidth(ibin+1)));
  	v_h_sysErr_SR1.at(0)->SetPointEYhigh(4, std::abs(total_mc-v_rc_sysErrorPdf_SR1.at(0)->GetPointY(11)/v_h_Zjets_SR1.at(0)->GetBinWidth(ibin+1)));
  
  	std::cout<<v_h_sysErr_SR1.at(0)->GetN()<<std::endl;


    v_h_Zjets_SR1.at(ibin_SR1)->Scale(1,"width");
    v_h_vh_SR1.at(ibin_SR1)->Scale(1,"width");
    v_h_htt_SR1.at(ibin_SR1)->Scale(1,"width");
    v_h_vbf_SR1.at(ibin_SR1)->Scale(1,"width");
    v_h_top_SR1.at(ibin_SR1)->Scale(1,"width");
    v_h_diboson_SR1.at(ibin_SR1)->Scale(1,"width");
    v_h_ggf_SR1.at(ibin_SR1)->Scale(1,"width");
    v_h_Fakes_SR1.at(ibin_SR1)->Scale(1,"width");
    v_h_Vgamma_SR1.at(ibin_SR1)->Scale(1,"width");
    v_h_data_SR1.at(ibin_SR1)->Scale(1,"width");

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
    	double y = v_h_Zjets_SR2.at(ibin_SR2)->GetBinContent(ibin+1)+v_h_vh_SR2.at(ibin_SR2)->GetBinContent(ibin+1)+v_h_htt_SR2.at(ibin_SR2)->GetBinContent(ibin+1)+v_h_vbf_SR2.at(ibin_SR2)->GetBinContent(ibin+1)+v_h_top_SR2.at(ibin_SR2)->GetBinContent(ibin+1)+v_h_diboson_SR2.at(ibin_SR2)->GetBinContent(ibin+1)+v_h_ggf_SR2.at(ibin_SR2)->GetBinContent(ibin+1)+v_h_Fakes_SR2.at(ibin_SR2)->GetBinContent(ibin+1)+v_h_Vgamma_SR2.at(ibin_SR2)->GetBinContent(ibin+1); 
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
  	total_mc = (v_h_Zjets_SR2.at(0)->GetBinContent(ibin+1)+v_h_vh_SR2.at(0)->GetBinContent(ibin+1)+v_h_htt_SR2.at(0)->GetBinContent(ibin+1)+v_h_vbf_SR2.at(0)->GetBinContent(ibin+1)+v_h_top_SR2.at(0)->GetBinContent(ibin+1)+v_h_diboson_SR2.at(0)->GetBinContent(ibin+1)+v_h_ggf_SR2.at(0)->GetBinContent(ibin+1)+v_h_Fakes_SR2.at(0)->GetBinContent(ibin+1)+v_h_Vgamma_SR2.at(0)->GetBinContent(ibin+1) );
  	v_h_sysErr_SR2.at(0)->SetPointEYlow(0, std::abs( total_mc-v_rc_sysErrorPdf_SR2.at(0)->GetPointY(26)));
  	v_h_sysErr_SR2.at(0)->SetPointEYhigh(0, std::abs(total_mc-v_rc_sysErrorPdf_SR2.at(0)->GetPointY(3)));
  	ibin =1;
  	total_mc = (v_h_Zjets_SR2.at(0)->GetBinContent(ibin+1)+v_h_vh_SR2.at(0)->GetBinContent(ibin+1)+v_h_htt_SR2.at(0)->GetBinContent(ibin+1)+v_h_vbf_SR2.at(0)->GetBinContent(ibin+1)+v_h_top_SR2.at(0)->GetBinContent(ibin+1)+v_h_diboson_SR2.at(0)->GetBinContent(ibin+1)+v_h_ggf_SR2.at(0)->GetBinContent(ibin+1)+v_h_Fakes_SR2.at(0)->GetBinContent(ibin+1)+v_h_Vgamma_SR2.at(0)->GetBinContent(ibin+1) );
  	v_h_sysErr_SR2.at(0)->SetPointEYlow(1, std::abs(total_mc-v_rc_sysErrorPdf_SR2.at(0)->GetPointY(24)));
  	v_h_sysErr_SR2.at(0)->SetPointEYhigh(1, std::abs(total_mc-v_rc_sysErrorPdf_SR2.at(0)->GetPointY(5)));
  	ibin = 2;
  	total_mc = (v_h_Zjets_SR2.at(0)->GetBinContent(ibin+1)+v_h_vh_SR2.at(0)->GetBinContent(ibin+1)+v_h_htt_SR2.at(0)->GetBinContent(ibin+1)+v_h_vbf_SR2.at(0)->GetBinContent(ibin+1)+v_h_top_SR2.at(0)->GetBinContent(ibin+1)+v_h_diboson_SR2.at(0)->GetBinContent(ibin+1)+v_h_ggf_SR2.at(0)->GetBinContent(ibin+1)+v_h_Fakes_SR2.at(0)->GetBinContent(ibin+1)+v_h_Vgamma_SR2.at(0)->GetBinContent(ibin+1) );
  	v_h_sysErr_SR2.at(0)->SetPointEYlow(2, std::abs(total_mc-v_rc_sysErrorPdf_SR2.at(0)->GetPointY(22)));
  	v_h_sysErr_SR2.at(0)->SetPointEYhigh(2, std::abs(total_mc-v_rc_sysErrorPdf_SR2.at(0)->GetPointY(7)));
  	ibin = 3;
  	total_mc = (v_h_Zjets_SR2.at(0)->GetBinContent(ibin+1)+v_h_vh_SR2.at(0)->GetBinContent(ibin+1)+v_h_htt_SR2.at(0)->GetBinContent(ibin+1)+v_h_vbf_SR2.at(0)->GetBinContent(ibin+1)+v_h_top_SR2.at(0)->GetBinContent(ibin+1)+v_h_diboson_SR2.at(0)->GetBinContent(ibin+1)+v_h_ggf_SR2.at(0)->GetBinContent(ibin+1)+v_h_Fakes_SR2.at(0)->GetBinContent(ibin+1)+v_h_Vgamma_SR2.at(0)->GetBinContent(ibin+1) );
  	v_h_sysErr_SR2.at(0)->SetPointEYlow(3, std::abs(total_mc-v_rc_sysErrorPdf_SR2.at(0)->GetPointY(20)));
  	v_h_sysErr_SR2.at(0)->SetPointEYhigh(3, std::abs(total_mc-v_rc_sysErrorPdf_SR2.at(0)->GetPointY(9)));
  	ibin = 4;
  	total_mc = (v_h_Zjets_SR2.at(0)->GetBinContent(ibin+1)+v_h_vh_SR2.at(0)->GetBinContent(ibin+1)+v_h_htt_SR2.at(0)->GetBinContent(ibin+1)+v_h_vbf_SR2.at(0)->GetBinContent(ibin+1)+v_h_top_SR2.at(0)->GetBinContent(ibin+1)+v_h_diboson_SR2.at(0)->GetBinContent(ibin+1)+v_h_ggf_SR2.at(0)->GetBinContent(ibin+1)+v_h_Fakes_SR2.at(0)->GetBinContent(ibin+1)+v_h_Vgamma_SR2.at(0)->GetBinContent(ibin+1) );
  	v_h_sysErr_SR2.at(0)->SetPointEYlow(4, std::abs(total_mc-v_rc_sysErrorPdf_SR2.at(0)->GetPointY(18)));
  	v_h_sysErr_SR2.at(0)->SetPointEYhigh(4, std::abs(total_mc-v_rc_sysErrorPdf_SR2.at(0)->GetPointY(11)));
  
  	std::cout<<v_h_sysErr_SR2.at(0)->GetN()<<std::endl;

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
/*
  k->cd(3);
  h_stack_DYCR->Draw("hist");
  h_data_DYCR->SetMarkerStyle(8);
  h_data_DYCR->Draw("PE same");
  
  //h_sysErrorPdf_DYCR->SetFillColor(kGray+2);
  //h_sysErrorPdf_DYCR->SetLineWidth(0);
  //h_sysErrorPdf_DYCR->SetFillStyle(3345);
  //h_sysErrorPdf_DYCR->Draw("e2 same");

  k->cd(2);
  h_stack_CRGGF->Draw("hist");
  h_data_CRGGF->SetMarkerStyle(8);
  h_data_CRGGF->Draw("PE same");
  

  k->cd(4);
  v_stack_SR1.at(0)->Draw("hist");
  v_h_data_SR1.at(0)->SetMarkerStyle(8);
  v_h_data_SR1.at(0)->Draw("PE same");

  k->cd(5);
  v_stack_SR1.at(1)->Draw("hist");
  v_h_data_SR1.at(1)->SetMarkerStyle(8);
  v_h_data_SR1.at(1)->Draw("PE same");

  k->cd(5);
  v_stack_SR1.at(2)->Draw("hist");
  v_h_data_SR1.at(2)->SetMarkerStyle(8);
  v_h_data_SR1.at(2)->Draw("PE same");

  k->cd(6);
  v_stack_SR1.at(3)->Draw("hist");
  v_h_data_SR1.at(3)->SetMarkerStyle(8);
  v_h_data_SR1.at(3)->Draw("PE same");

 // k->cd(7);
 // v_stack_SR1.at(4)->Draw("hist");
 // v_h_data_SR1.at(4)->SetMarkerStyle(8);
 // v_h_data_SR1.at(4)->Draw("PE same");

  k->cd(8);
  v_stack_SR2.at(0)->Draw("hist");
  v_h_data_SR2.at(0)->SetMarkerStyle(8);
  v_h_data_SR2.at(0)->Draw("PE same");

  k->cd(9);
  v_stack_SR2.at(1)->Draw("hist");
  v_h_data_SR2.at(1)->SetMarkerStyle(8);
  v_h_data_SR2.at(1)->Draw("PE same");
 */ 
//  k->SaveAs("heree.pdf");


  TCanvas* atlascanvas = new TCanvas("atlascanvas", "atlascanvas", 600, 600);
  atlascanvas->SetRightMargin(0);
  atlascanvas->SetLeftMargin(0);
  atlascanvas->cd();

  TLatex latex;

  TPad* pad1 = new TPad("pad1","pad1",  0, 0.68, 0.6, 1.);
  pad1->SetTopMargin(0.05);
  pad1->SetBottomMargin(0.025);
  pad1->SetRightMargin(0.118);
  pad1->SetLeftMargin(0.12);
  pad1->Draw();
  pad1->cd();
  v_stack_SR1.at(0)->Draw("hist");
 
  v_stack_SR1.at(0)->GetXaxis()->SetLabelOffset(10);
  v_stack_SR1.at(0)->GetXaxis()->SetLabelSize(0);
  v_stack_SR1.at(0)->GetYaxis()->SetLabelOffset(.0001);
 // v_stack_SR1.at(0)->GetXaxis()->SetAxisColor(0);
  v_stack_SR1.at(0)->SetMaximum(1500);
  v_stack_SR1.at(0)->SetMinimum(0.);
  v_h_sysErr_SR1.at(0)->SetFillColor(kGray+2);
  v_h_sysErr_SR1.at(0)->SetFillStyle(3345);
  v_h_sysErr_SR1.at(0)->Draw("e2 same");
  v_h_data_SR1.at(0)->SetMarkerSize(.8);
  v_h_data_SR1.at(0)->Draw("pe same");
  v_stack_SR1.at(0)->GetYaxis()->SetTitle("Events / bin width");
  v_stack_SR1.at(0)->GetYaxis()->SetTitleOffset(.82);
  v_stack_SR1.at(0)->GetYaxis()->SetLabelSize(.07);
  v_stack_SR1.at(0)->GetYaxis()->SetTitleSize(.07);
  //v_stack_SR1.at(0)->GetXaxis()->ChangeLabel(1,-1,0,-1,-1,-1,"");
/*
  auto legAtlas = new TLegend(0.1,0.65,1.,0.8);
  legAtlas->SetBorderSize(0);
  legAtlas->SetFillStyle(0);
  legAtlas->SetTextSize(0.);
  legAtlas->AddEntry((TObject*)0, "#it{#scale[1.2]{ATLAS}}   #bf{Internal}",""); 
  legAtlas->AddEntry((TObject*)0, "#bf{#sqrt{#scale[.8]{s}} #scale[.8]{= 13 TeV,} #scale[.8]{139 fb^{-1}}}", "");
  legAtlas->Draw(); 
  */
  latex.SetTextSize(0.065);
  latex.DrawLatex(0.75,1200,"SR1");
  
  gPad->RedrawAxis();

  atlascanvas->cd();
  TPad* ratiopad1 = new TPad("subpad1","subpad1", 0., 0.505, 0.6, .68);
  ratiopad1->Draw();
ratiopad1->SetGridy(1);  
ratiopad1->cd();
  ratiopad1->SetTopMargin(.08);
  ratiopad1->SetRightMargin(0.118);
  ratiopad1->SetLeftMargin(0.12);
  ratiopad1->SetBottomMargin(.3);
  TH1D* h_ratio_SR1 = (TH1D*) v_h_data_SR1.at(0)->Clone("ratio");
  TH1D* h_all_bkg_SR1 = (TH1D*) v_h_Zjets_SR1.at(0)->Clone("all_bkg");
  h_all_bkg_SR1->Add(v_h_Fakes_SR1.at(0));
  h_all_bkg_SR1->Add(v_h_top_SR1.at(0));
  h_all_bkg_SR1->Add(v_h_ggf_SR1.at(0));
  h_all_bkg_SR1->Add(v_h_diboson_SR1.at(0));
  h_all_bkg_SR1->Add(v_h_vbf_SR1.at(0));
  h_ratio_SR1->Divide(h_all_bkg_SR1);

  TGraphAsymmErrors* h_ratio_unc_SR1 = new TGraphAsymmErrors();
  for(int i=0; i<v_h_Fakes_SR1.at(0)->GetNbinsX(); i++)
  {
    h_ratio_unc_SR1->SetPoint(i, h_ratio_SR1->GetBinCenter(i+1), 1);
    h_ratio_unc_SR1->SetPointError(i, h_ratio_SR1->GetBinWidth(i+1)/2,h_ratio_SR1->GetBinWidth(i+1)/2,v_h_sysErr_SR1.at(0)->GetErrorYlow(i)/h_all_bkg_SR1->GetBinContent(i+1), v_h_sysErr_SR1.at(0)->GetErrorYhigh(i)/h_all_bkg_SR1->GetBinContent(i+1));
  }

  h_ratio_SR1->Draw("pe");
  h_ratio_unc_SR1->SetFillColor(kGray+2);
  h_ratio_unc_SR1->SetFillStyle(3345);
  h_ratio_unc_SR1->Draw("e2 same");
  h_ratio_SR1->SetMarkerSize(.8);
  h_ratio_SR1->Draw("pe same");
  h_ratio_SR1->GetYaxis()->SetLabelSize(.12);
  h_ratio_SR1->GetXaxis()->SetLabelSize(.12);
  h_ratio_SR1->GetYaxis()->SetLabelOffset(.003);

  h_ratio_SR1->GetYaxis()->SetNdivisions(505);
  h_ratio_SR1->GetYaxis()->CenterTitle(true);
  h_ratio_SR1->GetYaxis()->SetTitleOffset(.38);
  h_ratio_SR1->GetXaxis()->SetTitleOffset(.85);
 
  h_ratio_SR1->GetYaxis()->SetTitleSize(.13);
  h_ratio_SR1->GetYaxis()->SetTitle("Data / Pred.");
  h_ratio_SR1->GetXaxis()->SetTitleSize(.13);
  h_ratio_SR1->GetXaxis()->SetTitle("#it{D}_{VBF}");

   h_ratio_SR1->GetXaxis()->SetTickLength(.08);

//  h_ratio_SR1->GetXaxis()->SetLabelOffset(10);



  h_ratio_SR1->GetYaxis()->SetRangeUser(0.7,1.3);

  TLine* sr1_line = new TLine(0.5, 1, 1, 1 );
  sr1_line->SetLineColor(kBlack);
  sr1_line->Draw("same");
  gPad->RedrawAxis();

 // v_h_data_SR1.at(0)->Draw();
 // v_h_data_SR1.at(0)->GetYaxis()->SetLabelSize(.1);
 // v_h_data_SR1.at(0)->GetXaxis()->SetLabelSize(.1);
  gPad->RedrawAxis();

  atlascanvas->cd();
  TPad* pad2 = new TPad("pad2","pad2",  0.54, 0.68, 1., 1.);
  pad2->SetTopMargin(0.05);
  pad2->SetBottomMargin(0.025);
  pad2->SetLeftMargin(0.025);
  pad2->SetRightMargin(0.2);
  pad2->Draw();
  pad2->cd();
  h_stack_CRGGF->Draw("hist Y+ ");
  h_stack_CRGGF->SetMaximum(9000);
  h_stack_CRGGF->SetMinimum(0.);
  h_sysErrorPdf_CRGGF->SetFillStyle(3345);
  h_sysErrorPdf_CRGGF->SetFillColor(kGray+2);
  h_sysErrorPdf_CRGGF->Draw("e2 same");
  h_data_CRGGF->SetMarkerSize(.8);
  h_data_CRGGF->Draw("pe same");

  
  h_stack_CRGGF->GetXaxis()->SetLabelOffset(10);
  h_stack_CRGGF->GetYaxis()->SetLabelOffset(.007);
  h_stack_CRGGF->GetYaxis()->SetLabelSize(0.07);
  //h_stack_CRGGF->GetYaxis()->SetLabelOffset(.015);
  h_stack_CRGGF->GetYaxis()->SetTitle("Events / .50");
 
  h_stack_CRGGF->GetYaxis()->SetTitleSize(0.07);
  h_stack_CRGGF->GetYaxis()->SetTitleOffset(1.2);

  latex.SetTextSize(.065);
  latex.DrawLatex(-0.05,6900,"ggF CR");

  gPad->RedrawAxis();
  
  atlascanvas->cd();
  TPad* ratiopad2 = new TPad("subpad2","subpad2",  0.54, 0.505, 1., .68);
ratiopad2->SetGridy(1);  
ratiopad2->SetTopMargin(.08);
  ratiopad2->SetBottomMargin(.3);
  ratiopad2->SetLeftMargin(0.022);
  ratiopad2->SetRightMargin(0.2);
  ratiopad2->Draw();
  ratiopad2->cd();


  TH1D* h_ratio_CRGGF = (TH1D*) h_data_CRGGF->Clone("ratio");
  TH1D* h_all_bkg_CRGGF = (TH1D*) h_Zjets_CRGGF->Clone("all_bkg");
  h_all_bkg_CRGGF->Add(h_Fakes_CRGGF);
  h_all_bkg_CRGGF->Add(h_top_CRGGF);
  h_all_bkg_CRGGF->Add(h_ggf_CRGGF);
  h_all_bkg_CRGGF->Add(h_diboson_CRGGF);
  h_all_bkg_CRGGF->Add(h_vbf_CRGGF);
  h_ratio_CRGGF->Divide(h_all_bkg_CRGGF);

  TGraphAsymmErrors* h_ratio_unc_CRGGF = new TGraphAsymmErrors();
  for(int i=0; i<v_h_Fakes_SR1.at(0)->GetNbinsX(); i++)
  {
    h_ratio_unc_CRGGF->SetPoint(i, h_ratio_CRGGF->GetBinCenter(i+1), 1);
    h_ratio_unc_CRGGF->SetPointError(i, h_ratio_CRGGF->GetBinWidth(i+1)/2,h_ratio_CRGGF->GetBinWidth(i+1)/2,h_sysErrorPdf_CRGGF->GetErrorYlow(i)/h_all_bkg_CRGGF->GetBinContent(i+1), h_sysErrorPdf_CRGGF->GetErrorYhigh(i)/h_all_bkg_CRGGF->GetBinContent(i+1));
  }

  h_ratio_CRGGF->Draw("pe Y+");
  h_ratio_unc_CRGGF->SetFillColor(kGray+2);
  h_ratio_unc_CRGGF->SetFillStyle(3345);
  h_ratio_unc_CRGGF->Draw("e2 same");
  h_ratio_CRGGF->SetMarkerSize(.8);
  h_ratio_CRGGF->Draw("pe same");
  h_ratio_CRGGF->GetYaxis()->SetLabelSize(.12);
  h_ratio_CRGGF->GetXaxis()->SetLabelSize(0.12);
  h_ratio_CRGGF->GetXaxis()->SetLabelOffset(.015);
  h_ratio_CRGGF->GetXaxis()->SetTitle("#it{D}_{ggF}");
  h_ratio_CRGGF->GetYaxis()->SetTitle("Data / Pred.");
  h_ratio_CRGGF->GetYaxis()->SetTitleSize(0.13);
  h_ratio_CRGGF->GetXaxis()->SetTitleSize(.13);
  h_ratio_CRGGF->GetXaxis()->SetTitleOffset(1.);
  h_ratio_CRGGF->GetYaxis()->SetTitleOffset(.6);
  h_ratio_CRGGF->GetYaxis()->SetLabelOffset(.008);
  h_ratio_CRGGF->GetYaxis()->SetNdivisions(505);
  h_ratio_CRGGF->GetXaxis()->SetTickLength(.08);
  h_ratio_CRGGF->GetYaxis()->SetRangeUser(0.95,1.05);
  h_ratio_CRGGF->GetYaxis()->SetRangeUser(0.95,1.05);

  TLine* ggfcr_line = new TLine(-1, 1, 1, 1 );
  ggfcr_line->SetLineColor(kBlack);
  ggfcr_line->Draw("same");
  gPad->RedrawAxis();

 // v_h_data_SR1.at(0)->Draw();
 // v_h_data_SR1.at(0)->GetYaxis()->SetLabelSize(.1);
 // v_h_data_SR1.at(0)->GetXaxis()->SetLabelSize(.1);
  gPad->RedrawAxis();

  atlascanvas->cd();
  TPad* pad3 = new TPad("pad3", "pad3", 0.0, 0.2, 0.6, .515);
  pad3->SetTopMargin(0.055);
  pad3->SetBottomMargin(0.035);
  pad3->SetRightMargin(0.118);
  pad3->SetLeftMargin(0.119);

  //pad3->SetTopMargin(0);
 // pad3->SetRightMargin(0.05);
  pad3->Draw();
  pad3->cd();
  v_stack_SR2.at(0)->Draw("hist");
  v_stack_SR2.at(0)->SetMaximum(450);
  v_stack_SR2.at(0)->SetMinimum(0.);
  v_h_sysErr_SR2.at(0)->SetFillColor(kGray+2);
  v_h_sysErr_SR2.at(0)->SetFillStyle(3345);
  v_h_sysErr_SR2.at(0)->Draw("e2 same");
  v_h_data_SR2.at(0)->SetMarkerSize(.8);
  v_h_data_SR2.at(0)->Draw("pe same");
  v_stack_SR2.at(0)->GetYaxis()->SetTitle("Events / .50");

   v_stack_SR2.at(0)->GetYaxis()->SetTitleSize(.055);
  v_stack_SR2.at(0)->GetYaxis()->SetTitleOffset(0.95);
  v_stack_SR2.at(0)->GetXaxis()->SetLabelOffset(10);
  v_stack_SR2.at(0)->GetYaxis()->SetLabelOffset(.004);
  v_stack_SR2.at(0)->GetYaxis()->SetLabelSize(.07);
  v_stack_SR2.at(0)->GetYaxis()->SetTitleSize(.07);
  v_stack_SR2.at(0)->GetYaxis()->SetTitleOffset(0.7);

//  v_stack_SR2.at(0)->GetYaxis()->SetTitleSize(.055);
//  v_stack_SR2.at(0)->GetYaxis()->SetTitleOffset(1.2);
//  v_stack_SR2.at(0)->GetYaxis()->SetLabelOffset(.015);
//  v_stack_SR2.at(0)->GetYaxis()->SetLabelSize(.055);

  latex.SetTextSize(.065);
  latex.DrawLatex(-0.1,400,"SR2");

  TLegend* legendggfcr = new TLegend(0.23,0.38,.62,0.71);
  legendggfcr->SetBorderSize(0);
  legendggfcr->SetFillStyle(0);
  legendggfcr->SetTextSize(0.065);
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


  atlascanvas->cd();
  TPad* ratiopad3 = new TPad("subpad4","subpad4", 0, 0.0025, 0.6, .2);
  ratiopad3->SetTopMargin(.08);
  ratiopad3->SetBottomMargin(0.4);
  ratiopad3->SetLeftMargin(0.118);
  ratiopad3->SetRightMargin(0.119);
ratiopad3->SetGridy(1); 
 ratiopad3->Draw();
  ratiopad3->cd();

  TH1D* h_ratio_SR2 = (TH1D*) v_h_data_SR2.at(0)->Clone("ratio");
  TH1D* h_all_bkg_SR2 = (TH1D*) v_h_Zjets_SR2.at(0)->Clone("all_bkg");
  h_all_bkg_SR2->Add(v_h_Fakes_SR2.at(0));
  h_all_bkg_SR2->Add(v_h_top_SR2.at(0));
  h_all_bkg_SR2->Add(v_h_ggf_SR2.at(0));
  h_all_bkg_SR2->Add(v_h_diboson_SR2.at(0));
  h_all_bkg_SR2->Add(v_h_vbf_SR2.at(0));
  h_ratio_SR2->Divide(h_all_bkg_SR2);

  TGraphAsymmErrors* h_ratio_unc_SR2 = new TGraphAsymmErrors();
  for(int i=0; i<v_h_Fakes_SR2.at(0)->GetNbinsX(); i++)
  {
    h_ratio_unc_SR2->SetPoint(i, h_ratio_SR2->GetBinCenter(i+1), 1);
    h_ratio_unc_SR2->SetPointError(i, h_ratio_SR2->GetBinWidth(i+1)/2,h_ratio_SR2->GetBinWidth(i+1)/2,v_h_sysErr_SR2.at(0)->GetErrorYlow(i)/h_all_bkg_SR2->GetBinContent(i+1), v_h_sysErr_SR2.at(0)->GetErrorYhigh(i)/h_all_bkg_SR2->GetBinContent(i+1));
  }

  h_ratio_SR2->Draw("pe");
  h_ratio_unc_SR2->SetFillColor(kGray+2);
  h_ratio_unc_SR2->SetFillStyle(3345);
  h_ratio_unc_SR2->Draw("e2 same");
  h_ratio_SR2->SetMarkerSize(.8);
  h_ratio_SR2->Draw("pe same");
//  h_ratio_SR2->GetXaxis()->SetLabelOffset(.02);
  h_ratio_SR2->GetYaxis()->SetLabelSize(.11);
  h_ratio_SR2->GetXaxis()->SetLabelSize(.11);
  h_ratio_SR2->GetYaxis()->SetLabelOffset(.005);
  h_ratio_SR2->GetXaxis()->SetLabelOffset(.01);
  h_ratio_SR2->GetYaxis()->SetTitleOffset(.45);
  h_ratio_SR2->GetYaxis()->CenterTitle(true);
  h_ratio_SR2->GetYaxis()->SetTitle("Data / Pred.");
  h_ratio_SR2->GetYaxis()->SetTitleSize(.11);
  h_ratio_SR2->GetYaxis()->SetNdivisions(505);
  h_ratio_SR2->GetXaxis()->SetTitle("#it{D}_{Top+VV}");
  h_ratio_SR2->GetXaxis()->SetTitleSize(.13);
  h_ratio_SR2->GetXaxis()->SetTitleOffset(.8);

  h_ratio_SR2->GetXaxis()->SetTickLength(.08);

  TLine* sr2_line = new TLine(-1, 1, 1, 1 );
  sr2_line->SetLineColor(kBlack);
  sr2_line->Draw("same");
  gPad->RedrawAxis();


 // h_ratio_SR2->GetYaxis()->SetRangeUser(0.7,1.3);

  atlascanvas->cd();
  TPad* pad4 = new TPad("pad4", "pad4", .54, 0.2, 1., .5);

 // ("pad2","pad2", 0.5, 0.649, .92, 1.);
  pad4->SetTopMargin(0.012);
  pad4->SetBottomMargin(0.035);
  pad4->SetLeftMargin(0.03);
  pad4->SetRightMargin(.2);
  //pad4->SetBottomMargin(0.055);
  //pad4->SetLeftMargin(0.15);
 // pad4->SetRightMargin(0.05);
  pad4->Draw();
  pad4->cd();
  h_stack_DYCR->Draw("hist Y+");
  h_stack_DYCR->SetMaximum(260);
  h_stack_DYCR->SetMinimum(0.);
  h_data_DYCR->Draw("pe same");
  h_sysErrorPdf_DYCR->SetFillColor(kGray+2);
  h_sysErrorPdf_DYCR->SetFillStyle(3345);
  h_sysErrorPdf_DYCR->Draw("e2 same");
  h_data_DYCR->SetMarkerSize(.8);
  h_data_DYCR->Draw("pe same");
  h_stack_DYCR->GetXaxis()->SetLabelOffset(1.);
  h_stack_DYCR->GetYaxis()->SetLabelOffset(.006);
  h_stack_DYCR->GetYaxis()->SetLabelSize(.068);
  h_stack_DYCR->GetYaxis()->SetTitle("Events / 22 GeV");
  h_stack_DYCR->GetYaxis()->SetTitleSize(0.075);
  h_stack_DYCR->GetYaxis()->SetTitleOffset(1.1);

  latex.SetTextSize(.065);
  latex.DrawLatex(90,235,"Z+jets CR");

  
  atlascanvas->cd();
  TPad* ratiopad4 = new TPad("subpad4","subpad4", .54, 0.0025, 1., .2);
  ratiopad4->SetLeftMargin(0.03);
  ratiopad4->SetRightMargin(0.2);
  ratiopad4->SetBottomMargin(.4);
  ratiopad4->SetTopMargin(.08);
  ratiopad4->Draw();
  ratiopad4->cd();
  gPad->SetGridy(1);
  TH1D* h_ratio_DYCR = (TH1D*) h_data_DYCR->Clone("ratio_DYCR");
  TH1D* h_all_bkg_DYCR = (TH1D*) h_Zjets_DYCR->Clone("all_bkg_DYCR");
  h_all_bkg_DYCR->Add(h_Fakes_DYCR);
  h_all_bkg_DYCR->Add(h_top_DYCR);
  h_all_bkg_DYCR->Add(h_ggf_DYCR);
  h_all_bkg_DYCR->Add(h_diboson_DYCR);
  h_all_bkg_DYCR->Add(h_vbf_DYCR);
  h_ratio_DYCR->Divide(h_all_bkg_DYCR);

  TGraphAsymmErrors* h_ratio_unc_DYCR = new TGraphAsymmErrors();

  for(int i=0; i<h_data_DYCR->GetNbinsX(); i++)
  {
    h_ratio_unc_DYCR->SetPoint(i, h_ratio_DYCR->GetBinCenter(i+1), 1);
    h_ratio_unc_DYCR->SetPointError(i, h_ratio_DYCR->GetBinWidth(i+1)/2,h_ratio_DYCR->GetBinWidth(i+1)/2,h_sysErrorPdf_DYCR->GetErrorYlow(i)/h_all_bkg_DYCR->GetBinContent(i+1), h_sysErrorPdf_DYCR->GetErrorYhigh(i)/h_all_bkg_DYCR->GetBinContent(i+1));
  }

  h_ratio_DYCR->Draw("pe Y+");
  h_ratio_unc_DYCR->SetFillColor(kGray+2);
  h_ratio_unc_DYCR->SetFillStyle(3345);
  h_ratio_unc_DYCR->Draw("e2 same");
  h_ratio_DYCR->SetMarkerSize(.8);
  h_ratio_DYCR->Draw("pe same");
  h_ratio_DYCR->GetYaxis()->SetLabelSize(.106);
  h_ratio_DYCR->GetXaxis()->SetLabelSize(.106);
  h_ratio_DYCR->GetYaxis()->SetLabelOffset(.008);
  h_ratio_DYCR->GetXaxis()->SetLabelOffset(.01);
  h_ratio_DYCR->GetYaxis()->SetNdivisions(505);

  h_ratio_DYCR->GetYaxis()->SetTitle("Data / Pred.");

  h_ratio_DYCR->GetXaxis()->SetTickLength(.06);


  h_ratio_DYCR->GetXaxis()->SetTitleOffset(.9);
  h_ratio_DYCR->GetYaxis()->SetTitleOffset(.7);


  h_ratio_DYCR->GetXaxis()->SetTitleSize(.13);
  h_ratio_DYCR->GetYaxis()->SetTitleSize(.11);

  h_ratio_DYCR->GetXaxis()->SetTitle("#it{m}_{T} [GeV]");

  h_ratio_DYCR->GetYaxis()->SetRangeUser(0.7,1.35);

  h_ratio_DYCR->GetYaxis()->SetRangeUser(0.7,1.35);

  TArrow *ar6 = new TArrow(140,1.18,140,1.25, .007,">");
  //ar6->SetLineWidth(2);
  ar6->SetLineColor(kRed);
  ar6->SetFillColor(kWhite);
  ar6->Draw();
  TLine* dycr_line = new TLine(40, 1, 150, 1 );
  dycr_line->SetLineColor(kBlack);
  dycr_line->Draw("same");
  gPad->RedrawAxis();

  gPad->RedrawAxis();

  atlascanvas->cd();
  TLatex atlastex;
  atlastex.SetTextSize(.025);
  atlastex.DrawLatex(0.1, 0.95, "#it{#bf{#scale[1.2]{ATLAS}}}  Internal");
  atlastex.DrawLatex(.58, 0.95, "#sqrt{#scale[.8]{s}} #scale[.8]{= 13 TeV,} #scale[.8]{139 fb^{-1}}");
  atlascanvas->SaveAs("post-fit-bdt-inc.pdf");

  std::cout<<"DATA: \n";
  for(int idata=0; idata< v_h_data_SR2.at(0)->GetNbinsX(); idata++)
  {
    std::cout<<idata<<" "<<v_h_data_SR2.at(0)->GetBinContent(idata+1)<<std::endl;
  }
  std::cout<<"SYSTEMATICS: \n";

  for(int isys=0; isys<v_rc_sysErrorPdf_SR2.at(0)->GetN(); isys++)
  {

    std::cout<<isys<<" "<<v_rc_sysErrorPdf_SR2.at(0)->GetPointY(isys)<<std::endl;
  }

/*
  std::cout<<"DATA: \n";
  for(int idata=0; idata< v_h_data_SR1.at(0)->GetNbinsX(); idata++)
  {
    std::cout<<idata<<" "<<v_h_data_SR1.at(0)->GetBinContent(idata+1)<<std::endl;
  }
  std::cout<<"SYSTEMATICS: \n";

  for(int isys=0; isys<v_rc_sysErrorPdf_SR1.at(0)->GetN(); isys++)
  {

    std::cout<<isys<<" "<<v_rc_sysErrorPdf_SR1.at(0)->GetPointY(isys)<<std::endl;
  }
*/
  

  pad1->SaveAs("pad1.pdf");

/*
  
//  std::cout<<h_Zjets->GetNbinsX()<<" "<<h_vh->GetNbinsX()<<std::endl;



/*  std::cout<<"DATA: \n";
  for(int idata=0; idata< rc_Data->GetN(); idata++)
  {
    std::cout<<idata<<" "<<rc_Data->GetPointY(idata)<<std::endl;
  }
  std::cout<<"SYSTEMATICS: \n";

  for(int isys=0; isys<rc_sysErrorPdf->GetN(); isys++)
  {

    std::cout<<isys<<" "<<rc_sysErrorPdf->GetPointY(isys)<<std::endl;
  }

*/
 // h_sysErrorPdf->RemovePoint(0);
 // h_sysErrorPdf->RemovePoint(5);
 // h_sysErrorPdf->RemovePoint(6);
  //h_sysErrorPdf->RemovePoint(7);
//  std::cout<<"NPOINTS: "<<h_sysErrorPdf->GetN()<<std::endl;
//  std::cout<<rc_sysErrorPdf->GetPointY(28)-rc_sysErrorPdf->GetPointY(5)<<std::endl;
//  h_sysErrorPdf->SetErrorYhigh(0, 0);
/*  int ibin = 0;
  h_sysErrorPdf->SetPointEYlow(1, std::abs( (h_Zjets->GetBinContent(ibin+1)+h_vh->GetBinContent(ibin+1)+h_htt->GetBinContent(ibin+1)+h_vbf->GetBinContent(ibin+1)+h_top->GetBinContent(ibin+1)+h_diboson->GetBinContent(ibin+1)+h_ggf->GetBinContent(ibin+1)+h_Fakes->GetBinContent(ibin+1)+h_Vgamma->GetBinContent(ibin+1) )-rc_sysErrorPdf->GetPointY(30)));
  h_sysErrorPdf->SetPointEYhigh(1, std::abs((h_Zjets->GetBinContent(ibin+1)+h_vh->GetBinContent(ibin+1)+h_htt->GetBinContent(ibin+1)+h_vbf->GetBinContent(ibin+1)+h_top->GetBinContent(ibin+1)+h_diboson->GetBinContent(ibin+1)+h_ggf->GetBinContent(ibin+1)+h_Fakes->GetBinContent(ibin+1)+h_Vgamma->GetBinContent(ibin+1) )-rc_sysErrorPdf->GetPointY(3)));
  ibin =1;
  h_sysErrorPdf->SetPointEYlow(2, std::abs((h_Zjets->GetBinContent(ibin+1)+h_vh->GetBinContent(ibin+1)+h_htt->GetBinContent(ibin+1)+h_vbf->GetBinContent(ibin+1)+h_top->GetBinContent(ibin+1)+h_diboson->GetBinContent(ibin+1)+h_ggf->GetBinContent(ibin+1)+h_Fakes->GetBinContent(ibin+1)+h_Vgamma->GetBinContent(ibin+1) )-rc_sysErrorPdf->GetPointY(28)));
  h_sysErrorPdf->SetPointEYhigh(2, std::abs((h_Zjets->GetBinContent(ibin+1)+h_vh->GetBinContent(ibin+1)+h_htt->GetBinContent(ibin+1)+h_vbf->GetBinContent(ibin+1)+h_top->GetBinContent(ibin+1)+h_diboson->GetBinContent(ibin+1)+h_ggf->GetBinContent(ibin+1)+h_Fakes->GetBinContent(ibin+1)+h_Vgamma->GetBinContent(ibin+1) )-rc_sysErrorPdf->GetPointY(5)));
  ibin = 2;
  h_sysErrorPdf->SetPointEYlow(3, std::abs((h_Zjets->GetBinContent(ibin+1)+h_vh->GetBinContent(ibin+1)+h_htt->GetBinContent(ibin+1)+h_vbf->GetBinContent(ibin+1)+h_top->GetBinContent(ibin+1)+h_diboson->GetBinContent(ibin+1)+h_ggf->GetBinContent(ibin+1)+h_Fakes->GetBinContent(ibin+1)+h_Vgamma->GetBinContent(ibin+1) )-rc_sysErrorPdf->GetPointY(26)));
  h_sysErrorPdf->SetPointEYhigh(3, std::abs((h_Zjets->GetBinContent(ibin+1)+h_vh->GetBinContent(ibin+1)+h_htt->GetBinContent(ibin+1)+h_vbf->GetBinContent(ibin+1)+h_top->GetBinContent(ibin+1)+h_diboson->GetBinContent(ibin+1)+h_ggf->GetBinContent(ibin+1)+h_Fakes->GetBinContent(ibin+1)+h_Vgamma->GetBinContent(ibin+1) )-rc_sysErrorPdf->GetPointY(7)));
  ibin = 3;
  h_sysErrorPdf->SetPointEYlow(4, std::abs((h_Zjets->GetBinContent(ibin+1)+h_vh->GetBinContent(ibin+1)+h_htt->GetBinContent(ibin+1)+h_vbf->GetBinContent(ibin+1)+h_top->GetBinContent(ibin+1)+h_diboson->GetBinContent(ibin+1)+h_ggf->GetBinContent(ibin+1)+h_Fakes->GetBinContent(ibin+1)+h_Vgamma->GetBinContent(ibin+1) )-rc_sysErrorPdf->GetPointY(24)));
  h_sysErrorPdf->SetPointEYhigh(4, std::abs((h_Zjets->GetBinContent(ibin+1)+h_vh->GetBinContent(ibin+1)+h_htt->GetBinContent(ibin+1)+h_vbf->GetBinContent(ibin+1)+h_top->GetBinContent(ibin+1)+h_diboson->GetBinContent(ibin+1)+h_ggf->GetBinContent(ibin+1)+h_Fakes->GetBinContent(ibin+1)+h_Vgamma->GetBinContent(ibin+1) )-rc_sysErrorPdf->GetPointY(9)));
  ibin = 4;
  h_sysErrorPdf->SetPointEYlow(5, std::abs((h_Zjets->GetBinContent(ibin+1)+h_vh->GetBinContent(ibin+1)+h_htt->GetBinContent(ibin+1)+h_vbf->GetBinContent(ibin+1)+h_top->GetBinContent(ibin+1)+h_diboson->GetBinContent(ibin+1)+h_ggf->GetBinContent(ibin+1)+h_Fakes->GetBinContent(ibin+1)+h_Vgamma->GetBinContent(ibin+1) )-rc_sysErrorPdf->GetPointY(22)));
  h_sysErrorPdf->SetPointEYhigh(5, std::abs((h_Zjets->GetBinContent(ibin+1)+h_vh->GetBinContent(ibin+1)+h_htt->GetBinContent(ibin+1)+h_vbf->GetBinContent(ibin+1)+h_top->GetBinContent(ibin+1)+h_diboson->GetBinContent(ibin+1)+h_ggf->GetBinContent(ibin+1)+h_Fakes->GetBinContent(ibin+1)+h_Vgamma->GetBinContent(ibin+1) )-rc_sysErrorPdf->GetPointY(11)));
//  h_sysErrorPdf->SetErrorYhigh(6, 0);
//  h_sysErrorPdf->SetErrorYhigh(7, 0);
  //h_sysErrorPdf->SetPointError(7, 0);
  h_sysErrorPdf->RemovePoint(0);

  h_sysErrorPdf->RemovePoint(6);
  h_sysErrorPdf->RemovePoint(7);
  h_sysErrorPdf->RemovePoint(5);
  //h_sysErrorPdf->RemovePoint(6);
  //h_sysErrorPdf->RemovePoint(7);
  //h_sysErrorPdf->RemovePoint(8);

 // std::cout<<"ICOUNT: "<<icount<<" NPOINTS:"<<h_sysErrorPdf->GetN()<<std::endl;
  TCanvas *c = new TCanvas("cs","cs",600,600);
  TPad* pad1 = new TPad("pad1","pad1", 0, 0.35, 1., 1.);
  pad1->SetBottomMargin(0.02);
  pad1->Draw();
  pad1->cd();
  
  h_Zjets->Sumw2();
  h_vh->Sumw2();
  h_htt->Sumw2();
  h_vbf->Sumw2();
  h_top->Sumw2();
  h_diboson->Sumw2();
  h_ggf->Sumw2();
  h_Fakes->Sumw2();
  h_Vgamma->Sumw2();

  h_Zjets->SetLineWidth(1);
  h_vh->SetLineWidth(1);
  h_htt->SetLineWidth(1);
  h_vbf->SetLineWidth(1);
  h_top->SetLineWidth(1);
  h_diboson->SetLineWidth(1);
  h_ggf->SetLineWidth(1);
  h_Fakes->SetLineWidth(1);
  h_Vgamma->SetLineWidth(1);

  h_ggf->Add(h_vh);
  h_ggf->Add(h_htt);
  h_Zjets->Add(h_Vgamma);

  h_Zjets->SetFillColor(kGreen+2);
  h_Fakes->SetFillColor(kCyan-7);
  h_diboson->SetFillColor(kViolet+2);
  h_top->SetFillColor(kYellow-7);
  h_vbf->SetFillColor(kRed+1);
  h_ggf->SetFillColor(kOrange+3);


  THStack* h_stack = new THStack("h_stack", "");
  h_stack->Add(h_Fakes);
  h_stack->Add(h_Zjets);
  h_stack->Add(h_diboson);
  h_stack->Add(h_top);
  h_stack->Add(h_ggf);
  h_stack->Add(h_vbf);

  h_stack->Draw("hist");

  
  h_data->SetMarkerStyle(8);
  h_data->Draw("PE same");

  h_sysErrorPdf->SetFillColor(kGray+2);
  h_sysErrorPdf->SetLineWidth(0);
  h_sysErrorPdf->SetFillStyle(3345);
  h_sysErrorPdf->Draw("e2 same");

  //gPad->SetLogy();
  //h_stack->GetYaxis()->SetRangeUser(10e-03,23e+02);
  h_stack->GetYaxis()->SetTitle("Events");
  h_stack->GetYaxis()->SetRangeUser(0,400);
  h_stack->GetXaxis()->SetLabelSize(.05);
  h_stack->GetYaxis()->SetLabelSize(.05);
  h_stack->GetYaxis()->SetLabelOffset(.01);
  h_stack->GetXaxis()->SetLabelOffset(1);
  h_stack->GetXaxis()->SetTitleSize(.09);

  h_stack->SetMinimum(0);
  h_stack->SetMaximum(400);

  TLegend* legend = new TLegend(0.55,0.65,0.92,0.9);
  legend->SetBorderSize(0);
  legend->SetFillStyle(0);
  legend->SetTextSize(0.);
  legend->SetNColumns(2);
 
  legend->AddEntry(h_data, "#bf{Data}", "pe");
  legend->AddEntry(h_sysErrorPdf, "#bf{Uncertainty}", "f");
  legend->AddEntry(h_vbf,"#bf{H_{VBF}}", "f");
  legend->AddEntry(h_ggf, "#bf{H_{other}}", "f");
  legend->AddEntry(h_diboson, "#bf{VV}", "f");
  legend->AddEntry(h_top, "#bf{Top}","f");
  legend->AddEntry(h_Zjets, "#bf{Z/#scale[1.1]{#gamma}*+jets}", "f");
  legend->AddEntry(h_Fakes, "#bf{Mis-Id}", "f");
  
  legend->Draw();

  auto legAtlas = new TLegend(0.1,0.75,0.55,0.9);
  legAtlas->SetBorderSize(0);
  legAtlas->SetFillStyle(0);
  legAtlas->SetTextSize(0.);
  legAtlas->AddEntry((TObject*)0, "#it{#scale[1.2]{ATLAS}}   #bf{Internal}",""); 
  legAtlas->AddEntry((TObject*)0, "#bf{#sqrt{#scale[.8]{s}} #scale[.8]{= 13 TeV,} #scale[.8]{139 fb^{-1}}}", "");
  legAtlas->Draw();

  c->cd();
  TPad* pad2 = new TPad("pad2", "pad2", 0, 0., 1, .35);
  pad2->SetBottomMargin(.3);
  pad2->Draw();
  pad2->cd();
  gPad->SetGridy(1);
  
  TH1D* h_ratio = (TH1D*) h_data->Clone("ratio");
  TH1D* h_all_bkg = (TH1D*) h_Zjets->Clone("all_bkg");
  h_all_bkg->Add(h_Fakes);
  h_all_bkg->Add(h_top);
  h_all_bkg->Add(h_ggf);
  h_all_bkg->Add(h_diboson);
  h_all_bkg->Add(h_vbf);
  h_ratio->Divide(h_all_bkg);

  TGraphAsymmErrors* h_ratio_unc = new TGraphAsymmErrors();
  for(int i=0; i<5; i++)
  {
    h_ratio_unc->SetPoint(i, h_ratio->GetBinCenter(i+1), 1);
    h_ratio_unc->SetPointError(i, h_ratio->GetBinWidth(i+1)/2,h_ratio->GetBinWidth(i+1)/2,h_sysErrorPdf->GetErrorYlow(i)/h_all_bkg->GetBinContent(i+1), h_sysErrorPdf->GetErrorYhigh(i)/h_all_bkg->GetBinContent(i+1));
  }

  h_ratio->Draw("pe");
  h_ratio_unc->SetFillColor(kGray+2);
  h_ratio_unc->SetFillStyle(3345);
  h_ratio_unc->Draw("e2 same");
  h_ratio->Draw("pe same");
  h_ratio->GetYaxis()->SetLabelSize(.09);
  h_ratio->GetXaxis()->SetLabelSize(.09);
  h_ratio->GetYaxis()->SetLabelOffset(.01);
  h_ratio->GetXaxis()->SetLabelOffset(.01);
  h_ratio->GetYaxis()->SetNdivisions(508);
  h_ratio->GetYaxis()->CenterTitle(true);
  h_ratio->GetYaxis()->SetTitleOffset(.8);
  h_ratio->GetYaxis()->SetTitleSize(.08);
  h_ratio->GetYaxis()->SetTitle("Data / Pred.");
  h_ratio->GetXaxis()->SetTitleSize(.08);
  h_ratio->GetXaxis()->SetTitle("#it{m}_{T} [GeV]");

  h_ratio->GetYaxis()->SetRangeUser(-0.1,2.5);


  TCanvas* kanl= new TCanvas("kanl","cs",600,600);
  kanl->cd();
  h_sysErrorPdf->SetFillColor(kBlack);
  h_sysErrorPdf->SetFillStyle(3004);
  h_sysErrorPdf->Draw("a2");
  h_data->Draw("Psame");
  kanl->SaveAs("data_curves.pdf");
  c->SaveAs("post-fit-test.pdf");

*/
}
