#include <stdlib.h>

#include "../Style/AtlasStyle.C"
std::vector<std::string> v_mult_factors_SR1;
std::vector<std::string> v_mult_factors_SR2;
std::string xAxisTitle(std::string region)
{
	if(region=="SR1") return "#it{D}_{VBF}";
	if(region=="SR2") return "#it{D}_{top+VV}";
	if(region=="ggFCR1") return "#it{D}_{ggF}";
	if(region=="DYCR") return "#it{m}_{T} [GeV]";

	return " ";
}

std::string getObsName(std::string observable)
{
	if(observable=="DPhill") return "|#it{#Delta#phi}_{ll}|";
	if(observable=="Mjj") return "#it{m}_{jj}";
	
	return "";
}

TH1F* DumpHistoFromFile(std::string region, std::string padName, std::string observable, int bin, std::string histoname, bool isMain)
{
	TH1F* histo = new TH1F();	
	std::string filename = "../../prefit_bdt_inputs/my_out_"+region+".root";

  	if( (region.find("SR")!= string::npos)) filename = "../../prefit_bdt_inputs/my_out_" + region + observable + "_" + bin + ".root";
  	TFile* myfile = new TFile(filename.c_str(),"READ");
  	TKey* key,keypad; TPad* pad;
  	TIter nextkey(myfile->GetListOfKeys());
  	while( (key=(TKey*)nextkey()))
  	{
    	TObject* obj = key->ReadObj();    
    	if(strstr(obj->GetName(), padName.c_str()))
    	{
      		std::cout<<"got pad with name: "<< obj->GetName()<<std::endl;
      		pad = (TPad*)obj;
      		padName = obj->GetName();
      		break;
    	}
  	}
  	
  	TIter next(pad->GetListOfPrimitives());
  	while (TObject *obj = next())
  	{	
  		std::string objectname = obj->GetName();
  		if(objectname.find(histoname.c_str()) != string::npos)
  		{
  			histoname=obj->GetName();
  			break;
  		}
  	}
  	if(isMain) {
  		if(padName.find("main") != string::npos) {

  		histo = (TH1F*)pad->GetPrimitive(histoname.c_str());
  		std::cout<<histo->GetName();
		return histo;
		}
  	}
  	else {
  		if(padName.find("ratio") != string::npos) {
  		histo = (TH1F*)pad->GetPrimitive(histoname.c_str());
  		//std::cout<<histo->GetName();
		return histo;
		}
  	}
	
	return histo;
}


THStack* DumpStackFromFile(std::string region, std::string padName, std::string observable, int bin, std::string histoname)
{
	THStack* histo = new THStack();	
	std::string filename = "../../prefit_bdt_inputs/my_out_"+region+".root";

  	if( (region.find("SR")!= string::npos)) filename = "../../prefit_bdt_inputs/my_out_" + region + observable + "_" + bin + ".root";
  	TFile* myfile = new TFile(filename.c_str(),"READ");
  	TKey* key,keypad; TPad* pad;
  	TIter nextkey(myfile->GetListOfKeys());
  	while( (key=(TKey*)nextkey()))
  	{
    	TObject* obj = key->ReadObj();    
    	if(strstr(obj->GetName(), padName.c_str()))
    	{
      		std::cout<<"got pad with name: "<< obj->GetName()<<std::endl;
      		pad = (TPad*)obj;
      		padName = obj->GetName();
      		break;
    	}
  	}
  	
  	TIter next(pad->GetListOfPrimitives());
  	while (TObject *obj = next())
  	{	
  		std::string objectname = obj->GetName();
  		if(objectname.find(histoname.c_str()) != string::npos)
  		{
  			histoname=obj->GetName();
  			break;
  		}
  	}

  		if(padName.find("main") != string::npos) {

  		histo = (THStack*)pad->GetPrimitive(histoname.c_str());
  		std::cout<<histo->GetName();
		return histo;
		}


  	
	
	return histo;
}



std::vector<TH1F*> DumpHistoFromFile(std::string region, std::string padName, std::string observable, int bin, std::string histoname) // SR1 - SR2 main pads
{
	std::vector<TH1F*> v_histos;

	std::string filename = "../../prefit_bdt_inputs/my_out_"+region+".root";

  	if( (region.find("SR")!= string::npos)) filename = "../../prefit_bdt_inputs/my_out_" + region + observable + "_" + bin + ".root";
  	TFile* myfile = new TFile(filename.c_str(),"READ");
  	TKey* key,keypad; TPad* pad;
  	TIter nextkey(myfile->GetListOfKeys());
  	while( (key=(TKey*)nextkey()))
  	{
    	TObject* obj = key->ReadObj();    
    	if(strstr(obj->GetName(), padName.c_str()))
    	{
      		std::cout<<"got pad with name: "<< obj->GetName()<<std::endl;
      		pad = (TPad*)obj;
      		padName = obj->GetName();
      		break;
    	}
  	}
  	
  	TIter next(pad->GetListOfPrimitives());
  	while (TObject *obj = next())
  	{	
  		std::string objectname = obj->GetName();
  		if(objectname.find(histoname.c_str()) != string::npos)
  		{
  			histoname=obj->GetName();
  			break;
  		}
  	}
  		
  		if(padName.find("main") != string::npos) {
  		if(histoname=="h_stack"){
  		THStack* histostack = (THStack*)pad->GetPrimitive(histoname.c_str());
  		
  		TIter nexthisto(histostack->GetHists());
  		TH1F* htest;
  		while( (htest=(TH1F*)nexthisto()))
  		{
  			v_histos.push_back(htest);
  		}
  	
  		}
  	}

  	std::size_t found = padName.find("mult");
  	if(found != string::npos)
  	{ 
  		char my_character[2];
  		int digit=0;
  		std::string substr = padName.substr(found+4);
  		for(int i=substr.length(); i--; )
  		{
  			while(substr.find(".") != string::npos)
  				substr.pop_back();
  		}
  		if(region.find("SR1") != string::npos)
  			v_mult_factors_SR1.push_back(substr);
  		else if(region.find("SR2") != string::npos)
  			v_mult_factors_SR2.push_back(substr);
  	}

	return v_histos;
}



TGraphAsymmErrors* DumpErrorBandFromFile(std::string region, std::string padName, std::string observable, int bin, std::string histoname, bool isMain)
{
	TGraphAsymmErrors* histo = new TGraphAsymmErrors();	
	std::string filename = "../../prefit_bdt_inputs/my_out_"+region+".root";

  	if( (region.find("SR")!= string::npos)) filename = "../../prefit_bdt_inputs/my_out_" + region + observable + "_" + bin + ".root";
  	TFile* myfile = new TFile(filename.c_str(),"READ");
  	TKey* key; TPad* pad;
  	TIter nextkey(myfile->GetListOfKeys());
  	while( (key=(TKey*)nextkey()))
  	{
    	TObject* obj = key->ReadObj();    
    	if(strstr(obj->GetName(), padName.c_str()))
    	{
      		std::cout<<"got pad with name: "<< obj->GetName()<<std::endl;
      		pad = (TPad*)obj;
      		padName = obj->GetName();
      		break;
    	}
  	}

  	TIter next(pad->GetListOfPrimitives());
  	while (TObject *obj = next())
  	{	
  		std::string objectname = obj->GetName();
  		if(objectname.find(histoname.c_str()) != string::npos)
  		{
  			histoname=obj->GetName();
  			break;
  		}
  	}

  	if(isMain) {
  		if(padName.find("main") != string::npos) {
  		histo = (TGraphAsymmErrors*)pad->GetPrimitive(histoname.c_str());
  		//std::cout<<histo->GetName();
		return histo;
		}
  	}
  	else {
  		if(padName.find("ratio") != string::npos) {
  		histo = (TGraphAsymmErrors*)pad->GetPrimitive(histoname.c_str());
  		//std::cout<<histo->GetName();
		return histo;
		}
  	}
  	
	
	return histo;
}

TPad* DumpPadFromFile(std::string region, std::string padName, std::string observable, int bin, bool setRatioLimits=false, float ymin_SR1=0, float ymax_SR1=2, float ymin_SR2=0, float ymax_SR2=2)
{	
  std::string filename = "../../prefit_bdt_inputs/my_out_"+region+".root";
  if( (region.find("SR")!= string::npos)) filename = "../../prefit_bdt_inputs/my_out_" + region + observable + "_" + bin + ".root";
  TFile* myfile = new TFile(filename.c_str(),"READ");
  TKey* key; TPad* pad;
  TIter nextkey(myfile->GetListOfKeys());
  while( (key=(TKey*)nextkey()))
  {
    TObject* obj = key->ReadObj();    
    if(strstr(obj->GetName(), padName.c_str()))
    {
      std::cout<<"got pad with name: "<< obj->GetName()<<std::endl;
      pad = (TPad*)obj;
      padName = obj->GetName();
      break;
    }
  }
  
  if(padName.find("ratio") != string::npos) {
  	TH1F* histo = (TH1F*)pad->GetPrimitive("ratio");
	histo->SetTitle("");
	
	if( (region.find("SR")!= string::npos)) {
		histo->GetYaxis()->SetTitleOffset(1.4);
		histo->GetYaxis()->SetLabelOffset(0.003);
		if(region.find("SR1") != string::npos){
			if(setRatioLimits)
				histo->GetYaxis()->SetRangeUser(ymin_SR1, ymax_SR1);
			else
				histo->GetYaxis()->SetRangeUser(0.3,1.7);
		}
		else if(region.find("SR2") != string::npos){
			if(setRatioLimits){
				histo->GetYaxis()->SetRangeUser(ymin_SR2, ymax_SR2);
			}
			else
				histo->GetYaxis()->SetRangeUser(0.3,1.7);
		}
		if( bin==4 ) {
			std::string xaxis_tit = xAxisTitle(region);
			histo->GetXaxis()->SetTitle(xaxis_tit.c_str());
			histo->GetXaxis()->SetTitleOffset(0.4);
			histo->GetXaxis()->SetTitleSize(0.18);
		}
		else histo->GetXaxis()->SetTitleOffset(10);
		histo->GetXaxis()->SetLabelOffset(10);
		histo->GetXaxis()->SetNdivisions(505);
		histo->GetYaxis()->SetTickLength(.1);
		histo->GetYaxis()->SetTitleSize(0.13);
		histo->GetYaxis()->SetLabelSize(.14);
	}
	if(region=="ggFCR1" )
	{
		histo->GetYaxis()->SetTitleSize(.09);
		histo->GetYaxis()->SetRangeUser(0.8,1.2);
		histo->GetYaxis()->SetNdivisions(505);
		//histo->GetYaxis()->SetTitleOffset(1.);
		histo->GetYaxis()->SetLabelSize(.085);
		histo->GetXaxis()->SetLabelSize(.085);
		histo->GetXaxis()->SetTitleSize(.08);
		histo->GetXaxis()->SetTitleOffset(1.1);
		histo->GetXaxis()->SetLabelOffset(.005);
		histo->GetYaxis()->SetTickLength(.02);
	}
	else if (region=="DYCR")
	{
		histo->GetYaxis()->SetTitleSize(.09);
		histo->GetYaxis()->SetNdivisions(505);
		//histo->GetYaxis()->SetTitleOffset(1.);
		histo->GetYaxis()->SetLabelSize(.085);
		histo->GetXaxis()->SetLabelSize(.085);
		histo->GetXaxis()->SetTitleSize(.085);
		histo->GetXaxis()->SetTitleOffset(.9);
		histo->GetXaxis()->SetLabelOffset(.005);
		histo->GetYaxis()->SetTickLength(.02);
	}
	if(bin==-1) 
	{
		std::string xaxis_tit = xAxisTitle(region);
		histo->GetXaxis()->SetTitle(xaxis_tit.c_str());
	}
  }
  if(padName.find("main") != string::npos) {
  	THStack* histo = (THStack*)pad->GetPrimitive("h_stack");
	
	histo->GetXaxis()->SetNdivisions(505);
	//histo->GetYaxis()->SetTitleOffset(1.4);
	if(region=="ggFCR1" )
	{
		histo->GetYaxis()->SetTitle("Events / .50");
		histo->GetYaxis()->SetTitleSize(.06);
	//	histo->GetYaxis()->SetTitleOffset(1.5);
		histo->GetYaxis()->SetLabelSize(.06);
		histo->GetYaxis()->SetLabelOffset(0.006);
		histo->GetYaxis()->SetTickLength(.015);
	} 
	else if (region=="DYCR")
	{
		histo->GetYaxis()->SetTitle("Events / 22 GeV");
		histo->GetYaxis()->SetTitleSize(.08);
		histo->GetYaxis()->SetTitleOffset(.8);
		histo->GetYaxis()->SetLabelSize(.08);
		histo->GetYaxis()->SetTickLength(.015);
		histo->GetYaxis()->SetLabelOffset(0.006);
		TLegend* leg = (TLegend*)pad->GetPrimitive("mylegend");
		leg->SetX1(0.42);
		leg->SetY1(0.35);
		leg->SetY2(0.71);
		leg->SetX2(0.88);
	}
	else {
		if(region.find("SR2") != string::npos) histo->GetYaxis()->SetTitle("Events / .50");
		else {
			histo->GetYaxis()->SetTitle("Events / bin width");
		}
		histo->GetYaxis()->SetTitleSize(.13);
	//	histo->GetYaxis()->SetTitleOffset(1.2);
		histo->GetYaxis()->SetLabelOffset(0.003);
		histo->GetYaxis()->SetLabelSize(.14);
		histo->GetYaxis()->SetTickLength(.05);
	}
  }
  std::size_t found = padName.find("mult");
  if(found != string::npos)
  	{
  		char my_character[2];
  		int digit=0;
  		std::string substr = padName.substr(found+4);
  		for(int i=substr.length(); i--; )
  		{
  			while(substr.find(".") != string::npos)
  				substr.pop_back();
  		}
  		if(region.find("SR1") != string::npos)
  			v_mult_factors_SR1.push_back(substr);
  		else if(region.find("SR2") != string::npos)
  			v_mult_factors_SR2.push_back(substr);
  	}


  myfile->Close();
  return pad;
}

void make_pre_fit_plot(int binSR1, std::string observable, bool setRatioLimits=false)
{
	gROOT->SetBatch(kTRUE);
	TCanvas* k = new TCanvas("k","",600,600); 

	gStyle->SetErrorX(0.0001);
  	gStyle->SetEndErrorSize(0.);

  	TLatex mytext;
  	TLatex labeltext;
  	mytext.SetTextSize(.018);
  	std::string textname = "";

  	float ymin_SR1, ymin_SR2, ymax_SR1, ymax_SR2;
  	if(setRatioLimits)
  	{
  		std::cout<<"SR1 ==>\n";
  		std::cout<<"ymin: ";
  		std::cin >> ymin_SR1;
  		std::cout<<std::endl;
  		std::cout<<"ymax: ";
  		std::cin >> ymax_SR1;
  		std::cout<<std::endl;
  		std::cout<<"SR2 ==>\n";
  		std::cout<<"ymin: ";
  		std::cin >> ymin_SR2;
  		std::cout<<"ymax: ";
  		std::cin >> ymax_SR2;
  	}


// GGFCR panel
	std::string region= "ggFCR1";
	std::string padName = "main_pad_bdt_ggFCR1_ggFCR1";
	TPad* pad = DumpPadFromFile(region, padName, observable, -1, setRatioLimits, ymin_SR1, ymax_SR1, ymin_SR2, ymax_SR2);
	pad->SetPad(0.55, .65, 1., 1.);
	pad->SetBottomMargin(0.026);
	pad->SetTopMargin(0.15);
	pad->SetLeftMargin(0.1);
	pad->SetRightMargin(0.18);
	k->cd();
	pad->Draw();	

	padName = "ratio_pad_bdt_ggFCR1_ggFCR1";
	TPad* ratio_pad = DumpPadFromFile(region, padName, observable, -1, setRatioLimits, ymin_SR1, ymax_SR1, ymin_SR2, ymax_SR2);
	ratio_pad->SetPad(0.55, .41, 1., .65);
	ratio_pad->SetTopMargin(0.1);
	//ratio_pad->SetBottomMargin(0.1);
	ratio_pad->SetLeftMargin(0.1);
	ratio_pad->SetRightMargin(0.15);
	k->cd();
	ratio_pad->Draw();

	textname = "#bf{" + getObsName(observable) + " ggF CR}";
  	mytext.DrawLatex(0.72, .87, textname.c_str());

// DYCR panel
	region= "DYCR";
	padName = "main_pad_MT_DYCR";
	pad = DumpPadFromFile(region, padName, observable, -1, setRatioLimits, ymin_SR1, ymax_SR1, ymin_SR2, ymax_SR2);
	pad->SetPad(0.55, .2, 1., .46);
	pad->SetBottomMargin(0.026);
	//pad->SetTopMargin(0.1);
	pad->SetLeftMargin(0.1);
	pad->SetRightMargin(0.15);
	k->cd();
	pad->Draw();	

	padName = "ratio_pad_MT_DYCR";
	ratio_pad = DumpPadFromFile(region, padName, observable, -1, setRatioLimits, ymin_SR1, ymax_SR1, ymin_SR2, ymax_SR2);
	ratio_pad->SetPad(0.55, -0.04, 1., .2);
	ratio_pad->SetTopMargin(0.1);
	ratio_pad->SetLeftMargin(0.1);
	ratio_pad->SetRightMargin(0.15);
	k->cd();

	ratio_pad->Draw();
	TArrow *ar6 = new TArrow(.90,.15,.90,.16, .007,">");
  	ar6->SetLineColor(kRed);
  	ar6->SetFillColor(kWhite);
  	ar6->Draw();


  	textname = "#bf{" + getObsName(observable) + " Z+jets CR}";
  	mytext.DrawLatex(0.73, .41, textname.c_str());

//  SR1 panel
	region = "SR1";

	float xstart_main = 0.02;
	float xend_main = 0.18;
	float ystart_main = 0.65;
	float yend_main = 1.;

	float xstart_ratio = 0.02;
	float xend_ratio = 0.18;
	float ystart_ratio = 0.4;
	float yend_ratio = .65;
	
	for(int ibin=0; ibin<binSR1; ibin++)
	{
		std::string padName = "main_pad_bdt_vbf_"+ observable +"_" + region + observable +"_" + std::to_string(ibin);
		TPad* pad = DumpPadFromFile(region, padName, observable, ibin, setRatioLimits, ymin_SR1, ymax_SR1, ymin_SR2, ymax_SR2);
		pad->SetPad(xstart_main,ystart_main,xend_main,yend_main);
		pad->SetTopMargin(0.15);
		pad->SetBottomMargin(0.026);
		if(ibin==0) {
			pad->SetLeftMargin(0.475);
			
		}
		else 
			pad->SetLeftMargin(0.);
		if(ibin!= binSR1-1) pad->SetRightMargin(0);

		k->cd();
		pad->Draw();
		
		padName = "ratio_pad_bdt_vbf_" + observable + "_" + region + observable + "_" + std::to_string(ibin);
		TPad* ratio_pad = DumpPadFromFile(region, padName, observable, ibin, setRatioLimits, ymin_SR1, ymax_SR1, ymin_SR2, ymax_SR2);
		ratio_pad->SetPad(xstart_ratio,ystart_ratio,xend_ratio,yend_ratio);
		ratio_pad->SetTopMargin(0.1);
		if(ibin==0)
			ratio_pad->SetLeftMargin(0.475);
		else 
			ratio_pad->SetLeftMargin(0.);
		if(ibin!= binSR1-1) ratio_pad->SetRightMargin(0);

		k->cd();
		ratio_pad->Draw();

		textname = "#bf{" + getObsName(observable) + "Bin" + std::to_string(ibin+1) + "}";
		if(ibin==0) mytext.DrawLatex(0.105, .875, textname.c_str());
		else
		mytext.DrawLatex(0.105+ibin*0.1-0.01, .875, textname.c_str());

		if(!v_mult_factors_SR1.empty())
   		{
   			std::string times = "#bf{x"+ v_mult_factors_SR1.at(ibin) + "}";
 			mytext.DrawLatex(0.12+ibin*0.1, 0.85, times.c_str());
   		}

		xstart_main = xend_main;
		xend_main += 0.1;

		xstart_ratio = xend_ratio;
		xend_ratio += 0.1;

	}
	
	textname = "#bf{" + region + "}";
  	mytext.DrawLatex(0.33, .905, textname.c_str());

  	labeltext.SetTextSize(.018);
  	std::string labelname_up = "#bf{1.0}";
  	std::string labelname_down = "#bf{0.5}";
  	for(int ibin=0; ibin<binSR1; ibin++) {
   		labeltext.DrawLatex(.165 + ibin*0.1, .63, labelname_up.c_str());
   		if(ibin==0) labeltext.DrawLatex(.085 , .48, labelname_down.c_str());
   		else
   			labeltext.DrawLatex(.085 + ibin*0.1-0.01, .48, labelname_down.c_str());

  	}

 /* 	TArrow *ar = new TArrow(.26,.6,.26,.61, .007,">");
  	ar->SetLineColor(kRed);
  	ar->SetFillColor(kWhite);
  	ar->Draw();

  	ar = new TArrow(.30,.51,.30,.52, .007,"<");
  	ar->SetLineColor(kRed);
  	ar->SetFillColor(kWhite);
  	ar->Draw();

  	TArrow *ar = new TArrow(.56,.6,.56,.61, .007,">");
  	ar->SetLineColor(kRed);
  	ar->SetFillColor(kWhite);
  	ar->Draw();

*/
// SR2 panel

	region = "SR2";

	xstart_main = 0.02;
	xend_main = 0.18;
	ystart_main = 0.2;
	yend_main = .46;

	xstart_ratio = 0.02;
	xend_ratio = 0.18;
	ystart_ratio = -0.04;
	yend_ratio = .2;
	
	for(int ibin=0; ibin<binSR1; ibin++)
	{
		padName = "main_pad_bdt_TopWWAll_" + region + observable +"_" + std::to_string(ibin);
		pad = DumpPadFromFile(region, padName, observable, ibin, setRatioLimits, ymin_SR1, ymax_SR1, ymin_SR2, ymax_SR2);
		pad->SetPad(xstart_main,ystart_main,xend_main,yend_main);
		pad->SetBottomMargin(0.04);
		if(ibin==0)
			pad->SetLeftMargin(0.475);
		else 
			pad->SetLeftMargin(0.);
		if(ibin!= binSR1-1) pad->SetRightMargin(0);

		k->cd();
		pad->Draw();

		padName = "ratio_pad_bdt_TopWWAll_" + region + observable + "_" + std::to_string(ibin);
		ratio_pad = DumpPadFromFile(region, padName, observable, ibin, setRatioLimits, ymin_SR1, ymax_SR1, ymin_SR2, ymax_SR2);
		ratio_pad->SetPad(xstart_ratio,ystart_ratio,xend_ratio,yend_ratio);
		ratio_pad->SetTopMargin(0.1);
		if(ibin==0)
			ratio_pad->SetLeftMargin(0.475);
		else 
			ratio_pad->SetLeftMargin(0.);
		if(ibin!= binSR1-1) ratio_pad->SetRightMargin(0);

		k->cd();
		ratio_pad->Draw();

		textname = "#bf{" + getObsName(observable) + "Bin" + std::to_string(ibin+1) + "}";
		if(ibin==0) mytext.DrawLatex(0.105, .40, textname.c_str());
		else
		mytext.DrawLatex(0.105+ibin*0.1-0.01, .40, textname.c_str());

		if(!v_mult_factors_SR2.empty())
   		{
   			std::string times = "#bf{x"+ v_mult_factors_SR2.at(ibin) + "}";
 			mytext.DrawLatex(0.12+ibin*0.1, 0.375, times.c_str());
   		}

		gPad->RedrawAxis();

		xstart_main = xend_main;
		xend_main += 0.1;

		xstart_ratio = xend_ratio;
		xend_ratio += 0.1;
	}

	labelname_down = "#bf{-1.0}";
	for(int ibin=0; ibin<binSR1; ibin++) {
   		labeltext.DrawLatex(.165 + ibin*0.1, .18, labelname_up.c_str());
   		if(ibin==0) labeltext.DrawLatex(.085 , 0.035, labelname_down.c_str());
   		else
   			labeltext.DrawLatex(.085 + ibin*0.1-0.02, 0.035, labelname_down.c_str());
  	}
/*
  	ar6 = new TArrow(.39,.15,.39,.16, .007,">");
  	ar6->SetLineColor(kRed);
  	ar6->SetFillColor(kWhite);
  	ar6->Draw();
*/


	k->cd();
	TLatex atlastex;
  	atlastex.SetTextSize(.025);
  	atlastex.DrawLatex(0.1, 0.915, "#it{ATLAS}  #bf{Internal}");
  	atlastex.DrawLatex(.73, 0.915, "#bf{#sqrt{#scale[.8]{s}} #scale[.8]{= 13 TeV,} #scale[.8]{139 fb^{-1}}}");


  	textname = "#bf{" + region + "}";
  	mytext.DrawLatex(0.33, .423, textname.c_str());

  	std::string output = "prefit_BDT_" + observable + ".pdf";
	k->SaveAs(output.c_str());
}

void test_plot(int binSR1, std::string observable)
{

	/*   main pad 
	 OBJ: TH1F	h_bdt_ggFCR1_ggFCR1_Fakes	h_bdt_ggFCR1_ggFCR1_Fakes : 0 at: 0x3ea4dd0
     OBJ: TH1F	h_bdt_ggFCR1_ggFCR1_Zjets	h_bdt_ggFCR1_ggFCR1_Zjets : 0 at: 0x3ed0e60
     OBJ: TH1F	h_bdt_ggFCR1_ggFCR1_diboson1	h_bdt_ggFCR1_ggFCR1_diboson1 : 0 at: 0x3ed1410
     OBJ: TH1F	h_bdt_ggFCR1_ggFCR1_top1	h_bdt_ggFCR1_ggFCR1_top1 : 0 at: 0x3ed19c0
     OBJ: TH1F	h_bdt_ggFCR1_ggFCR1_ggf	h_bdt_ggFCR1_ggFCR1_ggf : 0 at: 0x3ed1f70
     OBJ: TH1F	h_bdt_ggFCR1_ggFCR1_vbf	h_bdt_ggFCR1_ggFCR1_vbf : 0 at: 0x3ed2520
  	 OBJ: TGraphAsymmErrors	error_band_bdt_ggFCR1_ggFCR1	 : 1 at: 0x3ed2ff0
  	 OBJ: TH1F	h_bdt_ggFCR1_ggFCR1_data	h_bdt_ggFCR1_ggFCR1_data : 1 at: 0x3eda050

  	====> ratio pad 
  	 OBJ: TList	TList	Doubly linked list : 0
     OBJ: TH1F	ratio	h_bdt_ggFCR1_ggFCR1_data : 1 at: 0x5c4e010
     TLine  X1=-1.000000 Y1=1.000000 X2=1.000000 Y2=1.000000
     OBJ: TGraphAsymmErrors	ratio_band_bdt_ggFCR1_ggFCR1	 : 1 at: 0x4dd3dc0
     OBJ: TH1F	ratio	h_bdt_ggFCR1_ggFCR1_data : 1 at: 0x5c4e010
  */


	gROOT->SetBatch(kTRUE);
	TCanvas* k = new TCanvas("k","",600,600); 
	SetAtlasStyle();
	//gStyle->SetErrorX(0.0001);
  	//gStyle->SetEndErrorSize(0.);
  	//gStyle->SetOptStat(0);

  	float ymin_SR1, ymin_SR2, ymax_SR1, ymax_SR2;

  	bool isMainPad = false;

// ==================================    GGF CR  ================================ //
  	std::string region = "ggFCR1";
  	std::string padName = "main_pad_bdt_ggFCR1_ggFCR1";
  	
  
  	// dump main pad primitives 
  	TH1F* h_data_ggFCR;
  	THStack* h_stack_ggFCR;
  	TGraphAsymmErrors* h_sys_band_ggFCR;
  	
  	isMainPad = true;
  	h_data_ggFCR = DumpHistoFromFile(region, padName, observable, -1, "h_bdt_ggFCR1_ggFCR1_data", isMainPad);
  	h_stack_ggFCR = DumpStackFromFile(region, padName, observable, -1, "h_stack");
  	h_sys_band_ggFCR = DumpErrorBandFromFile(region, padName, observable, -1, "error_band_bdt_ggFCR1_ggFCR1", isMainPad);
  	
  	// dump ratio pad primitives
  	TH1F* h_ratio_ggFCR;
  	TGraphAsymmErrors* h_ratio_sys_band_ggFCR;
  	padName = "ratio_pad_bdt_ggFCR1_ggFCR1";
  	isMainPad = false;

  	h_ratio_ggFCR = DumpHistoFromFile(region, padName, observable, -1, "ratio", isMainPad);
  	h_ratio_sys_band_ggFCR = DumpErrorBandFromFile(region, padName, observable, -1, "ratio_band_bdt_ggFCR1_ggFCR1", isMainPad);
// ==================================   END GGF CR ================================ //

// ==================================    DY CR  =================================== //

  	region = "DYCR";
  	padName = "main_pad_MT_DYCR";
  	
  	// dump main pad primitives 
  	TH1F* h_data_DYCR;
  	THStack* h_stack_DYCR;
  	TGraphAsymmErrors* h_sys_band_DYCR;
  	
  	isMainPad = true;
  	h_data_DYCR = DumpHistoFromFile(region, padName, observable, -1, "h_MT_DYCR_data", isMainPad);
  	h_stack_DYCR = DumpStackFromFile(region, padName, observable, -1, "h_stack");
  	h_sys_band_DYCR = DumpErrorBandFromFile(region, padName, observable, -1, "error_band_MT_DYCR", isMainPad);
  	
  	// dump ratio pad primitives
  	TH1F* h_ratio_DYCR;
  	TGraphAsymmErrors* h_ratio_sys_band_DYCR;
  	padName = "ratio_pad_MT_DYCR";
  	isMainPad = false;

  	h_ratio_DYCR = DumpHistoFromFile(region, padName, observable, -1, "ratio", isMainPad);
  	h_ratio_sys_band_DYCR = DumpErrorBandFromFile(region, padName, observable, -1, "ratio_band_MT_DYCR", isMainPad);
// ==================================   END DY CR ================================ //


// ==================================    SR1  =================================== // 
  	region = "SR1";
  	
  	std::vector<TH1F*> v_h_data_SR1_bin;
  	std::vector<TH1F*> v_h_Fakes_SR1_bin;
  	std::vector<TH1F*> v_h_Zjets_SR1_bin;
  	std::vector<TH1F*> v_h_diboson_SR1_bin;
  	std::vector<TH1F*> v_h_top_SR1_bin;
  	std::vector<TH1F*> v_h_ggf_SR1_bin;
  	std::vector<TH1F*> v_h_vbf_SR1_bin;
  	std::vector<TH1F*> v_histos_stacked;
  	std::vector<TGraphAsymmErrors*> v_sys_band_SR1_bin;

  	std::vector<TH1F*> v_ratio_SR1_bin;
  	std::vector<TGraphAsymmErrors*> v_ratio_sys_band_SR1_bin;
	
	for(int ibin=0; ibin<binSR1; ibin++)
	{
		isMainPad = true;
		std::string padName = "main_pad_bdt_vbf_"+ observable +"_" + region + observable +"_" + std::to_string(ibin);
		
		std::string dumpname = "h_bdt_vbf_"+observable+"_"+region+ observable +"_" + std::to_string(ibin)+"_data";
		TH1F* h_data_SR1 = DumpHistoFromFile(region, padName, observable, ibin, dumpname, isMainPad);
		v_h_data_SR1_bin.push_back(h_data_SR1);

		dumpname = "h_bdt_vbf_"+observable+"_"+region+ observable +"_" + std::to_string(ibin);
		v_histos_stacked = DumpHistoFromFile(region, padName, observable, ibin, "h_stack");
		v_h_Fakes_SR1_bin.push_back(v_histos_stacked.at(0));
		v_h_Zjets_SR1_bin.push_back(v_histos_stacked.at(1));
		v_h_diboson_SR1_bin.push_back(v_histos_stacked.at(2));
		v_h_top_SR1_bin.push_back(v_histos_stacked.at(3));
		v_h_ggf_SR1_bin.push_back(v_histos_stacked.at(4));
		v_h_vbf_SR1_bin.push_back(v_histos_stacked.at(5));

		v_histos_stacked.clear();
		v_histos_stacked.shrink_to_fit();

		dumpname = "error_band_bdt_vbf_"+observable +"_"+ region + observable +"_" + std::to_string(ibin);
		TGraphAsymmErrors* h_sys_band_SR1 = DumpErrorBandFromFile(region, padName, observable, ibin, dumpname, isMainPad);
		v_sys_band_SR1_bin.push_back(h_sys_band_SR1);

		isMainPad = false;
		padName = "ratio_pad_bdt_vbf_"+ observable +"_" + region + observable +"_" + std::to_string(ibin);
		TH1F* h_ratio = DumpHistoFromFile(region, padName, observable, ibin, "ratio", isMainPad);
		v_ratio_SR1_bin.push_back(h_ratio);
		dumpname = "ratio_band_bdt_vbf_"+observable +"_"+ region + observable +"_" + std::to_string(ibin);
		TGraphAsymmErrors* h_ratio_sys_band_SR1 = DumpErrorBandFromFile(region, padName, observable, ibin, dumpname, isMainPad);
		v_ratio_sys_band_SR1_bin.push_back(h_ratio_sys_band_SR1);
	}

	// Fill a single histogram that contains the different bins
	int n_bins = v_h_data_SR1_bin.at(0)->GetNbinsX(); // how many bins has the bdt_vbf 
	double *binsEdges;


	binsEdges = new double[21]{0, 0.2, 0.36, 0.44, 0.5, 0.7, .86, .94, 1., 1.2, 1.36, 1.44, 1.5, 1.7, 1.86, 1.94, 2., 2.2, 2.36, 2.44, 2.5};

	TH1F* h_Fakes_SR1_all = new TH1F("h_Fakes_SR1_all", "h_Fakes_SR1_all", 20, binsEdges);
	TH1F* h_Zjets_SR1_all = new TH1F("h_Zjets_SR1_all", "h_Zjets_SR1_all", 20, binsEdges);
	TH1F* h_diboson_SR1_all = new TH1F("h_diboson_SR1_all", "h_diboson_SR1_all", 20, binsEdges);
	TH1F* h_top_SR1_all = new TH1F("h_top_SR1_all", "h_top_SR1_all", 20, binsEdges);
	TH1F* h_ggf_SR1_all = new TH1F("h_ggf_SR1_all", "h_ggf_SR1_all", 20, binsEdges);
	TH1F* h_vbf_SR1_all = new TH1F("h_vbf_SR1_all", "h_vbf_SR1_all", 20, binsEdges);

	TH1F* h_data_SR1_all = new TH1F("h_data_SR1_all", "h_data_SR1_all", binSR1*n_bins, binsEdges);
	TGraphAsymmErrors* sys_band_SR1_all = new TGraphAsymmErrors();
	TH1F* h_ratio_SR1_all = new TH1F("h_ratio_SR1_all", "h_ratio_SR1_all", binSR1*n_bins, binsEdges);
	TGraphAsymmErrors* ratio_sys_band_SR1_all = new TGraphAsymmErrors();

	int i=0; //count the SR1 bins 0->4
	int ibinsingle=1; //count the bins
	for(int ibin=0; ibin<h_Fakes_SR1_all->GetNbinsX(); ibin++)
	{	
		h_Fakes_SR1_all->SetBinContent(ibin+1, v_h_Fakes_SR1_bin.at(i)->GetBinContent(ibinsingle));
		h_Fakes_SR1_all->SetBinError(ibin+1, v_h_Fakes_SR1_bin.at(i)->GetBinError(ibinsingle));
		
		h_Zjets_SR1_all->SetBinContent(ibin+1, v_h_Zjets_SR1_bin.at(i)->GetBinContent(ibinsingle));
		h_Zjets_SR1_all->SetBinError(ibin+1, v_h_Zjets_SR1_bin.at(i)->GetBinError(ibinsingle));

		h_diboson_SR1_all->SetBinContent(ibin+1, v_h_diboson_SR1_bin.at(i)->GetBinContent(ibinsingle));
		h_diboson_SR1_all->SetBinError(ibin+1, v_h_diboson_SR1_bin.at(i)->GetBinError(ibinsingle));

		h_top_SR1_all->SetBinContent(ibin+1, v_h_top_SR1_bin.at(i)->GetBinContent(ibinsingle));
		h_top_SR1_all->SetBinError(ibin+1, v_h_top_SR1_bin.at(i)->GetBinError(ibinsingle));

		h_ggf_SR1_all->SetBinContent(ibin+1, v_h_ggf_SR1_bin.at(i)->GetBinContent(ibinsingle));
		h_ggf_SR1_all->SetBinError(ibin+1, v_h_ggf_SR1_bin.at(i)->GetBinError(ibinsingle));

		h_vbf_SR1_all->SetBinContent(ibin+1, v_h_vbf_SR1_bin.at(i)->GetBinContent(ibinsingle));
		h_vbf_SR1_all->SetBinError(ibin+1, v_h_vbf_SR1_bin.at(i)->GetBinError(ibinsingle));

		h_data_SR1_all->SetBinContent(ibin+1, v_h_data_SR1_bin.at(i)->GetBinContent(ibinsingle));
		h_data_SR1_all->SetBinError(ibin+1, v_h_data_SR1_bin.at(i)->GetBinError(ibinsingle));

		h_ratio_SR1_all->SetBinContent(ibin+1, v_ratio_SR1_bin.at(i)->GetBinContent(ibinsingle));
		h_ratio_SR1_all->SetBinError(ibin+1, v_ratio_SR1_bin.at(i)->GetBinError(ibinsingle));
		
		sys_band_SR1_all->SetPointX(ibin, h_Fakes_SR1_all->GetBinCenter(ibin+1));
		sys_band_SR1_all->SetPointY(ibin, v_sys_band_SR1_bin.at(i)->GetPointY(ibinsingle-1));
		sys_band_SR1_all->SetPointError(ibin, v_sys_band_SR1_bin.at(i)->GetErrorXlow(ibinsingle-1), v_sys_band_SR1_bin.at(i)->GetErrorXhigh(ibinsingle-1), v_sys_band_SR1_bin.at(i)->GetErrorYlow(ibinsingle-1), v_sys_band_SR1_bin.at(i)->GetErrorYhigh(ibinsingle-1));
		

		ratio_sys_band_SR1_all->SetPointX(ibin, h_Fakes_SR1_all->GetBinCenter(ibin+1));
		ratio_sys_band_SR1_all->SetPointY(ibin, v_ratio_sys_band_SR1_bin.at(i)->GetPointY(ibinsingle-1));
		ratio_sys_band_SR1_all->SetPointError(ibin, v_ratio_sys_band_SR1_bin.at(i)->GetErrorXlow(ibinsingle-1), v_ratio_sys_band_SR1_bin.at(i)->GetErrorXhigh(ibinsingle-1), v_ratio_sys_band_SR1_bin.at(i)->GetErrorYlow(ibinsingle-1), v_ratio_sys_band_SR1_bin.at(i)->GetErrorYhigh(ibinsingle-1));
		ibinsingle++;
		if(ibinsingle>4) {ibinsingle=1; i++;} 
	}
	//std::cout<<"FAKES bin - 1 "<<h_data_SR1_all->GetBinContent(2)<<std::endl;
	
// ==================================   END SR1 ================================ //

// ==================================    SR2  =================================== // 
  	region = "SR2";
 
	std::vector<TH1F*> v_h_data_SR2_bin;
  	std::vector<TH1F*> v_h_Fakes_SR2_bin;
  	std::vector<TH1F*> v_h_Zjets_SR2_bin;
  	std::vector<TH1F*> v_h_diboson_SR2_bin;
  	std::vector<TH1F*> v_h_top_SR2_bin;
  	std::vector<TH1F*> v_h_ggf_SR2_bin;
  	std::vector<TH1F*> v_h_vbf_SR2_bin;
  	std::vector<TH1F*> v_histos_stacked_SR2;
  	std::vector<TGraphAsymmErrors*> v_sys_band_SR2_bin;

  	std::vector<TH1F*> v_ratio_SR2_bin;
  	std::vector<TGraphAsymmErrors*> v_ratio_sys_band_SR2_bin;
	
	for(int ibin=0; ibin<binSR1; ibin++)
	{
		isMainPad = true;
		std::string padName = "main_pad_bdt_TopWWAll_"+ region + observable +"_" + std::to_string(ibin);
		
		std::string dumpname = "h_bdt_TopWWAll_"+ region + observable +"_" + std::to_string(ibin)+"_data";
		TH1F* h_data_SR2 = DumpHistoFromFile(region, padName, observable, ibin, dumpname, isMainPad);
		v_h_data_SR2_bin.push_back(h_data_SR2);

		dumpname = "h_bdt_TopWWAll_"+region+ observable +"_" + std::to_string(ibin);
		v_histos_stacked_SR2 = DumpHistoFromFile(region, padName, observable, ibin, "h_stack");
		v_h_Fakes_SR2_bin.push_back(v_histos_stacked_SR2.at(0));
		v_h_Zjets_SR2_bin.push_back(v_histos_stacked_SR2.at(1));
		v_h_diboson_SR2_bin.push_back(v_histos_stacked_SR2.at(2));
		v_h_top_SR2_bin.push_back(v_histos_stacked_SR2.at(3));
		v_h_ggf_SR2_bin.push_back(v_histos_stacked_SR2.at(4));
		v_h_vbf_SR2_bin.push_back(v_histos_stacked_SR2.at(5));

		v_histos_stacked_SR2.clear();
		v_histos_stacked_SR2.shrink_to_fit();

		dumpname = "error_band_bdt_TopWWAll_"+ region + observable +"_" + std::to_string(ibin);
		TGraphAsymmErrors* h_sys_band_SR2 = DumpErrorBandFromFile(region, padName, observable, ibin, dumpname, isMainPad);
		v_sys_band_SR2_bin.push_back(h_sys_band_SR2);

		isMainPad = false;
		padName = "ratio_pad_bdt_TopWWAll_"+ region + observable +"_" + std::to_string(ibin);
		TH1F* h_ratio = DumpHistoFromFile(region, padName, observable, ibin, "ratio", isMainPad);
		v_ratio_SR2_bin.push_back(h_ratio);
		dumpname = "ratio_band_bdt_TopWWAll_"+ region + observable +"_" + std::to_string(ibin);
		TGraphAsymmErrors* h_ratio_sys_band_SR2 = DumpErrorBandFromFile(region, padName, observable, ibin, dumpname, isMainPad);
		v_ratio_sys_band_SR2_bin.push_back(h_ratio_sys_band_SR2);
	}

	// Fill a single histogram that contains the different bins
	n_bins = v_h_data_SR2_bin.at(0)->GetNbinsX(); // how many bins has the bdt_vbf 

	double *binsEdges2;


// EDW NA ORISW TA BINEDGES
	binsEdges2 = new double[11]{-1, 0., 1. , 2., 3., 4., 5., 6., 7., 8., 9.};

	TH1F* h_Fakes_SR2_all = new TH1F("h_Fakes_SR2_all", "h_Fakes_SR2_all", 10, binsEdges2);
	TH1F* h_Zjets_SR2_all = new TH1F("h_Zjets_SR2_all", "h_Zjets_SR2_all", 10, binsEdges2);
	TH1F* h_diboson_SR2_all = new TH1F("h_diboson_SR2_all", "h_diboson_SR2_all", 10, binsEdges2);
	TH1F* h_top_SR2_all = new TH1F("h_top_SR2_all", "h_top_SR2_all", 10, binsEdges2);
	TH1F* h_ggf_SR2_all = new TH1F("h_ggf_SR2_all", "h_ggf_SR2_all", 10, binsEdges2);
	TH1F* h_vbf_SR2_all = new TH1F("h_vbf_SR2_all", "h_vbf_SR2_all", 10, binsEdges2);

	TH1F* h_data_SR2_all = new TH1F("h_data_SR2_all", "h_data_SR2_all", binSR1*n_bins, binsEdges2);
	TGraphAsymmErrors* sys_band_SR2_all = new TGraphAsymmErrors();
	TH1F* h_ratio_SR2_all = new TH1F("h_ratio_SR2_all", "h_ratio_SR2_all", binSR1*n_bins, binsEdges2);
	TGraphAsymmErrors* ratio_sys_band_SR2_all = new TGraphAsymmErrors();

	i=0; //count the SR1 bins 0->4
	ibinsingle=1; //count the bins
	for(int ibin=0; ibin<h_Fakes_SR2_all->GetNbinsX(); ibin++)
	{	
		h_Fakes_SR2_all->SetBinContent(ibin+1, v_h_Fakes_SR2_bin.at(i)->GetBinContent(ibinsingle));
		h_Fakes_SR2_all->SetBinError(ibin+1, v_h_Fakes_SR2_bin.at(i)->GetBinError(ibinsingle));
		
		h_Zjets_SR2_all->SetBinContent(ibin+1, v_h_Zjets_SR2_bin.at(i)->GetBinContent(ibinsingle));
		h_Zjets_SR2_all->SetBinError(ibin+1, v_h_Zjets_SR2_bin.at(i)->GetBinError(ibinsingle));

		h_diboson_SR2_all->SetBinContent(ibin+1, v_h_diboson_SR2_bin.at(i)->GetBinContent(ibinsingle));
		h_diboson_SR2_all->SetBinError(ibin+1, v_h_diboson_SR2_bin.at(i)->GetBinError(ibinsingle));

		h_top_SR2_all->SetBinContent(ibin+1, v_h_top_SR2_bin.at(i)->GetBinContent(ibinsingle));
		h_top_SR2_all->SetBinError(ibin+1, v_h_top_SR2_bin.at(i)->GetBinError(ibinsingle));

		h_ggf_SR2_all->SetBinContent(ibin+1, v_h_ggf_SR2_bin.at(i)->GetBinContent(ibinsingle));
		h_ggf_SR2_all->SetBinError(ibin+1, v_h_ggf_SR2_bin.at(i)->GetBinError(ibinsingle));

		h_vbf_SR2_all->SetBinContent(ibin+1, v_h_vbf_SR2_bin.at(i)->GetBinContent(ibinsingle));
		h_vbf_SR2_all->SetBinError(ibin+1, v_h_vbf_SR2_bin.at(i)->GetBinError(ibinsingle));

		h_data_SR2_all->SetBinContent(ibin+1, v_h_data_SR2_bin.at(i)->GetBinContent(ibinsingle));
		h_data_SR2_all->SetBinError(ibin+1, v_h_data_SR2_bin.at(i)->GetBinError(ibinsingle));

		h_ratio_SR2_all->SetBinContent(ibin+1, v_ratio_SR2_bin.at(i)->GetBinContent(ibinsingle));
		h_ratio_SR2_all->SetBinError(ibin+1, v_ratio_SR2_bin.at(i)->GetBinError(ibinsingle));
		
		sys_band_SR2_all->SetPointX(ibin, h_Fakes_SR2_all->GetBinCenter(ibin+1));
		sys_band_SR2_all->SetPointY(ibin, v_sys_band_SR2_bin.at(i)->GetPointY(ibinsingle-1));
		sys_band_SR2_all->SetPointError(ibin, v_sys_band_SR2_bin.at(i)->GetErrorXlow(ibinsingle-1), v_sys_band_SR2_bin.at(i)->GetErrorXhigh(ibinsingle-1), v_sys_band_SR2_bin.at(i)->GetErrorYlow(ibinsingle-1), v_sys_band_SR2_bin.at(i)->GetErrorYhigh(ibinsingle-1));
		

		ratio_sys_band_SR2_all->SetPointX(ibin, h_Fakes_SR2_all->GetBinCenter(ibin+1));
		ratio_sys_band_SR2_all->SetPointY(ibin, v_ratio_sys_band_SR2_bin.at(i)->GetPointY(ibinsingle-1));
		ratio_sys_band_SR2_all->SetPointError(ibin, v_ratio_sys_band_SR2_bin.at(i)->GetErrorXlow(ibinsingle-1), v_ratio_sys_band_SR2_bin.at(i)->GetErrorXhigh(ibinsingle-1), v_ratio_sys_band_SR2_bin.at(i)->GetErrorYlow(ibinsingle-1), v_ratio_sys_band_SR2_bin.at(i)->GetErrorYhigh(ibinsingle-1));
		ibinsingle++;
		if(ibinsingle>2) {ibinsingle=1; i++;} 
	}

	for(int k=0; k<h_data_SR2_all->GetNbinsX(); k++)
	{
		std::cout<<h_data_SR2_all->GetBinContent(k+1)<<std::endl;
	}
	//std::cout<<"FAKES bin - 1 "<<h_data_SR1_all->GetBinContent(2)<<std::endl;


// ==================================   END SR2 ================================ //
//	std::string pName = "main_pad_bdt_vbf_Mjj_SR1Mjj_0";
//	std::vector<TH1F*> v = DumpHistoFromFile("SR1", pName, "Mjj", 0, "h_stack");
	//v.at(0)->Draw("hist");

  	TCanvas* can = new TCanvas("can", "can", 600,  600);
  	can->cd();
  	TPad* padsr1 = new TPad("padsr1","padsr1", 0, 0.68, 0.6, 1.);
  	padsr1->SetTopMargin(0.05); // (0.05)
  	padsr1->SetBottomMargin(0.028);
  	padsr1->SetRightMargin(0.118);
 	padsr1->SetLeftMargin(0.12);
  	padsr1->Draw();
  	padsr1->cd();

  	h_Fakes_SR1_all->SetFillColor(kCyan-7);
	h_Zjets_SR1_all->SetFillColor(kGreen+2);
	h_diboson_SR1_all->SetFillColor(kViolet+2);
	h_top_SR1_all->SetFillColor(kYellow-7);
	h_ggf_SR1_all->SetFillColor(kOrange+1);
	h_vbf_SR1_all->SetFillColor(kRed+1);

	h_Fakes_SR1_all->SetLineWidth(1);
	h_Zjets_SR1_all->SetLineWidth(1);
	h_diboson_SR1_all->SetLineWidth(1);
	h_top_SR1_all->SetLineWidth(1);
	h_ggf_SR1_all->SetLineWidth(1);
	h_vbf_SR1_all->SetLineWidth(1);

	h_Fakes_SR1_all->SetLineColor(kBlack);
	h_Zjets_SR1_all->SetLineColor(kBlack);
	h_diboson_SR1_all->SetLineColor(kBlack);
	h_top_SR1_all->SetLineColor(kBlack);
	h_ggf_SR1_all->SetLineColor(kBlack);
	h_vbf_SR1_all->SetLineColor(kBlack);

	THStack* h_SR1 = new THStack();
	h_SR1->Add(h_Fakes_SR1_all);
	h_SR1->Add(h_Zjets_SR1_all);
	h_SR1->Add(h_diboson_SR1_all);
	h_SR1->Add(h_top_SR1_all);
	h_SR1->Add(h_ggf_SR1_all);
	h_SR1->Add(h_vbf_SR1_all);



	h_SR1->SetMaximum(990);
	if(observable=="DPhill") h_SR1->SetMaximum(500);


  	h_SR1->Draw("hist");
  	h_SR1->GetXaxis()->SetLabelOffset(10);
  	h_SR1->GetYaxis()->SetTitle("Events / bin width");
  	
  	h_data_SR1_all->SetMarkerStyle(8);
  	h_data_SR1_all->SetMarkerSize(.8);
  	h_SR1->GetYaxis()->SetLabelOffset(.0001);
  	h_SR1->GetYaxis()->SetLabelSize(.063);
  	h_SR1->GetYaxis()->SetTitleSize(.07);
  	h_SR1->GetYaxis()->SetTitleOffset(0.7);

  	sys_band_SR1_all->SetFillColor(kGray+2);
  	sys_band_SR1_all->SetLineColor(kWhite);
  	sys_band_SR1_all->SetFillStyle(3345);
  	sys_band_SR1_all->Draw("e2 same");
  	h_data_SR1_all->Draw("pe same");


  	float ymax = 810;
  	if(observable=="DPhill") ymax = 430;
  	TLatex mytext;
  	mytext.SetTextSize(0.06);
  	std::string subtit = "SR1";
  	mytext.DrawLatex(1.2, ymax+50, subtit.c_str());
  	TLine* line0 = new TLine(.5, 0., .5, ymax );
  	TLine* line1 = new TLine(1., 0., 1., ymax );
  	TLine* line2 = new TLine(1.5, 0., 1.5, ymax );
  	TLine* line3 = new TLine(2., 0., 2., ymax );
  	line0->Draw("same");
  	line1->Draw("same");
  	line2->Draw("same");
  	line3->Draw("same");

  	subtit=getObsName(observable) + " Bin1";
  	mytext.DrawLatex(.1,ymax-30 ,subtit.c_str());

  	subtit=getObsName(observable) + " Bin2";
  	mytext.DrawLatex(.55,ymax-30 ,subtit.c_str());

  	subtit=getObsName(observable) + " Bin3";
  	mytext.DrawLatex(1.05,ymax-30 ,subtit.c_str());

  	subtit=getObsName(observable) + " Bin4";
  	mytext.DrawLatex(1.55,ymax-30 ,subtit.c_str());

  	subtit=getObsName(observable) + " Bin5";
  	mytext.DrawLatex(2.02,ymax-30 ,subtit.c_str());

for(int ibin=0; ibin<binSR1; ibin++){
  	if(!v_mult_factors_SR1.empty())
   	{
   			std::string times = "x"+ v_mult_factors_SR1.at(ibin);
 			mytext.DrawLatex(0.25+2*ibin*0.25-0.05, 710, times.c_str());
   	}
}
  	can->cd();
  	TPad* subpadsr1 = new TPad("subpadsr1","subpadsr1", 0., 0.505, 0.6, .68);
  	subpadsr1->SetTopMargin(0.08);
  	subpadsr1->SetBottomMargin(0.3);
  	subpadsr1->SetRightMargin(0.118);
  	subpadsr1->SetLeftMargin(0.12);
  	subpadsr1->Draw();
  	subpadsr1->cd();
  	gPad->SetGridy(1);
  	h_ratio_SR1_all->SetLineColor(kBlack);
  	h_ratio_SR1_all->SetMarkerStyle(8);
  	h_ratio_SR1_all->SetMarkerSize(.8);
  	h_ratio_SR1_all->Draw("ep");
  	ratio_sys_band_SR1_all->SetFillColor(kGray+2);
    ratio_sys_band_SR1_all->SetFillStyle(3345);
  	ratio_sys_band_SR1_all->Draw("e2 same");
  	h_ratio_SR1_all->Draw("ep same");
  	h_ratio_SR1_all->GetXaxis()->SetLabelOffset(10);

  	TLine* sr1_line = new TLine(0., 1, 2.5, 1 );
  	sr1_line->SetLineColor(kBlack);
  	sr1_line->Draw("same");
  	gPad->RedrawAxis();

   double xratiolabel_up = 1.518;
   double xratiolabel_down = .23;

   //if(observable=="DPhill" ) { xratiolabel_up = 1.918; xratiolabel_down = -0.06;}
   
   mytext.SetTextSize(.11);
   mytext.DrawLatex(-0.05, xratiolabel_down, "0.5");
   mytext.DrawLatex(.45, xratiolabel_down, "0.5");
   mytext.DrawLatex(.95, xratiolabel_down, "0.5");
   mytext.DrawLatex(1.45, xratiolabel_down, "0.5");
   mytext.DrawLatex(1.95, xratiolabel_down, "0.5");

   mytext.DrawLatex(0.45, xratiolabel_up, "1.0");
   mytext.DrawLatex(0.95, xratiolabel_up, "1.0");
   mytext.DrawLatex(1.45, xratiolabel_up, "1.0");
   mytext.DrawLatex(1.95, xratiolabel_up, "1.0");
   mytext.DrawLatex(2.43, xratiolabel_up, "1.0");

   h_ratio_SR1_all->GetYaxis()->SetRangeUser(0.4,1.5);
   double ratio_add_max = .5;
   double ratio_add_min = .4;
  if( observable=="DPhill"){
   h_ratio_SR1_all->GetYaxis()->SetRangeUser(0.4,1.5);
   ratio_add_max=.5;
   ratio_add_min=.4;
  }

if(observable=="Mjj") {
  TArrow *ar = new TArrow(2.4,1.25,2.4,1.4, .007,">");
  	ar->SetLineColor(kRed);
  	ar->SetFillColor(kWhite);
  	ar->Draw();
}
  h_ratio_SR1_all->GetYaxis()->SetLabelSize(.12);

  h_ratio_SR1_all->GetYaxis()->SetLabelOffset(.003);

  h_ratio_SR1_all->GetYaxis()->SetNdivisions(505);
  h_ratio_SR1_all->GetYaxis()->CenterTitle(true);
  h_ratio_SR1_all->GetYaxis()->SetTitleOffset(.4);
  h_ratio_SR1_all->GetXaxis()->SetTitleOffset(.8);
 
  h_ratio_SR1_all->GetYaxis()->SetTitleSize(.12);
  h_ratio_SR1_all->GetYaxis()->SetTitle("Data / Pred.");
  h_ratio_SR1_all->GetXaxis()->SetTitleSize(.13);
  h_ratio_SR1_all->GetXaxis()->SetTitle("#it{D}_{VBF}");

   h_ratio_SR1_all->GetXaxis()->SetTickLength(.08);


  TLine* line4 = new TLine(.5, gPad->GetUymin() + ratio_add_min, .5,  gPad->GetUymax() + ratio_add_max );
  TLine* line5 = new TLine(1., gPad->GetUymin() + ratio_add_min, 1., gPad->GetUymax() + ratio_add_max );
  TLine* line6 = new TLine(1.5, gPad->GetUymin() + ratio_add_min, 1.5,  gPad->GetUymax() + ratio_add_max) ;
  TLine* line7 = new TLine(2., gPad->GetUymin() + ratio_add_min, 2., gPad->GetUymax() + ratio_add_max );
  line4->Draw("same");
  line5->Draw("same");
  line6->Draw("same");
  line7->Draw("same");

  can->cd();

  TPad* pad2ggfcr = new TPad("pad2ggfcr","pad2ggfcr", 0.54, 0.68, 1., 1.);
  pad2ggfcr->SetTopMargin(0.05);
  pad2ggfcr->SetBottomMargin(0.028);
  pad2ggfcr->SetLeftMargin(0.025);
  pad2ggfcr->SetRightMargin(0.2);
  pad2ggfcr->Draw();
  pad2ggfcr->cd();

  h_stack_ggFCR->Draw("hist Y+");
  
  h_sys_band_ggFCR->SetFillColor(kGray+2);
  h_sys_band_ggFCR->SetLineColor(kWhite);
  h_sys_band_ggFCR->SetFillStyle(3345);
  h_sys_band_ggFCR->Draw("e2 same");
  h_data_ggFCR->SetMarkerSize(.8);
  h_data_ggFCR->SetMarkerStyle(8);
  h_data_ggFCR->Draw("ep same");

  h_stack_ggFCR->GetXaxis()->SetLabelOffset(10);


  h_stack_ggFCR->GetYaxis()->SetLabelOffset(.008);
  h_stack_ggFCR->GetYaxis()->SetLabelSize(0.065);
  //h_stack_CRGGF->GetYaxis()->SetLabelOffset(.015);
  h_stack_ggFCR->GetYaxis()->SetTitle("Events / .50");
  
  h_stack_ggFCR->GetYaxis()->SetTitleSize(0.07);
  h_stack_ggFCR->GetYaxis()->SetTitleOffset(1.3);

  mytext.SetTextSize(0.06);
  subtit=getObsName(observable) + " ggF CR";
  double ggf_y_title = 8100;
  //if(input=="lep0_pt" || input=="lep1_pt" || input=="jet0_pt" || input=="jet1_pt") ggf_y_title = 7900;
  mytext.DrawLatex(-0.2,ggf_y_title,subtit.c_str());

  gPad->RedrawAxis();

  can->cd();
  TPad* ratiopad2ggfcr = new TPad("ratiopad2ggfcr","ratiopad2ggfcr", 0.54, 0.505, 1., .68);
  ratiopad2ggfcr->SetTopMargin(.08);
  ratiopad2ggfcr->SetBottomMargin(.3);
  ratiopad2ggfcr->SetLeftMargin(0.02);
  ratiopad2ggfcr->SetRightMargin(0.2);
  ratiopad2ggfcr->Draw();
  ratiopad2ggfcr->cd();
  gPad->SetGridy(1);
  h_ratio_ggFCR->SetMarkerStyle(8);
  h_ratio_ggFCR->SetMarkerSize(.8);
  h_ratio_ggFCR->Draw("ep Y+");
  h_ratio_sys_band_ggFCR->SetFillColor(kGray+2);
  h_ratio_sys_band_ggFCR->SetLineColor(kWhite);
  h_ratio_sys_band_ggFCR->SetFillStyle(3345);
  h_ratio_sys_band_ggFCR->Draw("e2 same");
  h_ratio_ggFCR->Draw("ep same");

  h_ratio_ggFCR->GetYaxis()->SetLabelSize(.12);
  h_ratio_ggFCR->GetXaxis()->SetLabelSize(0.12);
  h_ratio_ggFCR->GetXaxis()->SetLabelOffset(.015);
  h_ratio_ggFCR->GetXaxis()->SetTitle("#it{D}_{ggF}");
  h_ratio_ggFCR->GetYaxis()->SetTitle("Data / Pred.");
  h_ratio_ggFCR->GetYaxis()->SetTitleSize(0.13);
  h_ratio_ggFCR->GetXaxis()->SetTitleSize(.13);
  h_ratio_ggFCR->GetXaxis()->SetTitleOffset(1.);
  h_ratio_ggFCR->GetYaxis()->SetTitleOffset(.6);
  h_ratio_ggFCR->GetYaxis()->SetLabelOffset(.008);
  h_ratio_ggFCR->GetYaxis()->SetNdivisions(505);
  h_ratio_ggFCR->GetXaxis()->SetTickLength(.08);
  h_ratio_ggFCR->GetYaxis()->SetRangeUser(0.8,1.2);

  TLine* ggfcr_line = new TLine(-1, 1, 1, 1 );
  ggfcr_line->SetLineColor(kBlack);
  ggfcr_line->Draw("same");
  gPad->RedrawAxis();

  gPad->RedrawAxis();

    can->cd();
  	TPad* padsr2 = new TPad("padsr1","padsr1", 0.0, 0.2, 0.6, .515);
  	padsr2->SetTopMargin(0.055); // (0.05)
  	padsr2->SetBottomMargin(0.035);
  	padsr2->SetRightMargin(0.118);
 	padsr2->SetLeftMargin(0.119);
  	padsr2->Draw();
  	padsr2->cd();

  	h_Fakes_SR2_all->SetFillColor(kCyan-7);
	h_Zjets_SR2_all->SetFillColor(kGreen+2);
	h_diboson_SR2_all->SetFillColor(kViolet+2);
	h_top_SR2_all->SetFillColor(kYellow-7);
	h_ggf_SR2_all->SetFillColor(kOrange+1);
	h_vbf_SR2_all->SetFillColor(kRed+1);

	h_Fakes_SR2_all->SetLineWidth(1);
	h_Zjets_SR2_all->SetLineWidth(1);
	h_diboson_SR2_all->SetLineWidth(1);
	h_top_SR2_all->SetLineWidth(1);
	h_ggf_SR2_all->SetLineWidth(1);
	h_vbf_SR2_all->SetLineWidth(1);

	h_Fakes_SR2_all->SetLineColor(kBlack);
	h_Zjets_SR2_all->SetLineColor(kBlack);
	h_diboson_SR2_all->SetLineColor(kBlack);
	h_top_SR2_all->SetLineColor(kBlack);
	h_ggf_SR2_all->SetLineColor(kBlack);
	h_vbf_SR2_all->SetLineColor(kBlack);

	THStack* h_SR2 = new THStack();
	h_SR2->Add(h_Fakes_SR2_all);
	h_SR2->Add(h_Zjets_SR2_all);
	h_SR2->Add(h_diboson_SR2_all);
	h_SR2->Add(h_top_SR2_all);
	h_SR2->Add(h_ggf_SR2_all);
	h_SR2->Add(h_vbf_SR2_all);



	h_SR2->SetMaximum(550);
	if(observable=="DPhill") h_SR2->SetMaximum(550);


  	h_SR2->Draw("hist");
  	h_SR2->GetXaxis()->SetLabelOffset(10);
  	h_SR2->GetYaxis()->SetTitle("Events / 1.0");
  	
  	h_data_SR2_all->SetMarkerStyle(8);
  	h_data_SR2_all->SetMarkerSize(.8);
  	h_SR2->GetYaxis()->SetLabelOffset(.004);
  	h_SR2->GetYaxis()->SetLabelSize(.063);
  	h_SR2->GetYaxis()->SetTitleSize(.07);
  	h_SR2->GetYaxis()->SetTitleOffset(0.7);

  	sys_band_SR2_all->SetFillColor(kGray+2);
  	sys_band_SR2_all->SetLineColor(kWhite);
  	sys_band_SR2_all->SetFillStyle(3345);
  	sys_band_SR2_all->Draw("e2 same");
  	h_data_SR2_all->Draw("pe same");


  	ymax = 500;
  	if(observable=="DPhill") ymax = 470;
  	mytext.SetTextSize(0.06);
  	subtit = "SR2";
  	mytext.DrawLatex(3.5, 520, subtit.c_str());
  	line0 = new TLine(1., 0., 1., ymax );
  	line1 = new TLine(3., 0., 3., ymax );
  	line2 = new TLine(5., 0., 5., ymax );
  	line3 = new TLine(7., 0., 7., ymax );
  	line0->Draw("same");
  	line1->Draw("same");
  	line2->Draw("same");
  	line3->Draw("same");

  	if(observable=="Mjj")
  	{
  		subtit=getObsName(observable) + " Bin1";
  	mytext.DrawLatex(-0.7,470 ,subtit.c_str());

  	subtit=getObsName(observable) + " Bin2";
  	mytext.DrawLatex(1.2,470 ,subtit.c_str());

  	subtit=getObsName(observable) + " Bin3";
  	mytext.DrawLatex(3.2,470 ,subtit.c_str());

  	subtit=getObsName(observable) + " Bin4";
  	mytext.DrawLatex(5.2,470 ,subtit.c_str());

  	subtit=getObsName(observable) + " Bin5";
  	mytext.DrawLatex(7.1,470 ,subtit.c_str());
  	}
else{
  	subtit=getObsName(observable) + " Bin1";
  	mytext.DrawLatex(-0.7,430 ,subtit.c_str());

  	subtit=getObsName(observable) + " Bin2";
  	mytext.DrawLatex(1.2,430 ,subtit.c_str());

  	subtit=getObsName(observable) + " Bin3";
  	mytext.DrawLatex(3.2,430 ,subtit.c_str());

  	subtit=getObsName(observable) + " Bin4";
  	mytext.DrawLatex(5.2,430 ,subtit.c_str());

  	subtit=getObsName(observable) + " Bin5";
  	mytext.DrawLatex(7.1,430 ,subtit.c_str());
  }

for(int ibin=0; ibin<binSR1; ibin++){
  	if(!v_mult_factors_SR2.empty())
   	{
   		std::string times = "x"+ v_mult_factors_SR2.at(ibin);
   		std::cout<<times<<std::endl;
   		if(ibin>2)
 			mytext.DrawLatex(0.+2*ibin-0.4, 430, times.c_str());
 		else mytext.DrawLatex(0.+2*ibin-0.2, 430, times.c_str());
   	}
}
  	can->cd();
  	TPad* subpadsr2 = new TPad("subpadsr2","subpadsr2", 0, 0.0025, 0.6, .2);
  	subpadsr2->SetTopMargin(0.08);
  	subpadsr2->SetBottomMargin(0.4);
  	subpadsr2->SetRightMargin(0.118);
  	subpadsr2->SetLeftMargin(0.119);
  	subpadsr2->Draw();
  	subpadsr2->cd();
  	gPad->SetGridy(1);
  	h_ratio_SR2_all->SetLineColor(kBlack);
  	h_ratio_SR2_all->SetMarkerStyle(8);
  	h_ratio_SR2_all->SetMarkerSize(.8);
  	h_ratio_SR2_all->Draw("ep");
  	ratio_sys_band_SR2_all->SetFillColor(kGray+2);
    ratio_sys_band_SR2_all->SetFillStyle(3345);
  	ratio_sys_band_SR2_all->Draw("e2 same");
  	h_ratio_SR2_all->Draw("ep same");
  	h_ratio_SR2_all->GetXaxis()->SetLabelOffset(10);


   mytext.SetTextSize(.1);
   mytext.DrawLatex(-1.2, .2, "-1.0");
   mytext.DrawLatex(.8, .2, "-1.0");
   mytext.DrawLatex(2.8, .2, "-1.0");
   mytext.DrawLatex(4.8, .2, "-1.0");
   mytext.DrawLatex(6.8, .2, "-1.0");
   mytext.DrawLatex(0.8, 1.53, "1.0");
   mytext.DrawLatex(2.8, 1.53, "1.0");
   mytext.DrawLatex(4.8, 1.53, "1.0");
   mytext.DrawLatex(6.8, 1.53, "1.0");
   mytext.DrawLatex(8.6, 1.53, "1.0");

   h_ratio_SR2_all->GetYaxis()->SetRangeUser(0.4,1.5);
   ratio_add_max = .5;
   ratio_add_min = .4;
  if( observable=="DPhill"){
   h_ratio_SR2_all->GetYaxis()->SetRangeUser(0.4,1.5);
   ratio_add_max=.5;
   ratio_add_min=.4;
  }


  h_ratio_SR2_all->GetYaxis()->SetLabelSize(.11);
  h_ratio_SR2_all->GetYaxis()->SetLabelOffset(.005);

  h_ratio_SR2_all->GetYaxis()->SetNdivisions(505);
  h_ratio_SR2_all->GetYaxis()->CenterTitle(true);
  h_ratio_SR2_all->GetYaxis()->SetTitleOffset(.45);
  h_ratio_SR2_all->GetXaxis()->SetTitleOffset(.8);
 
  h_ratio_SR2_all->GetYaxis()->SetTitleSize(.11);
  h_ratio_SR2_all->GetYaxis()->SetTitle("Data / Pred.");
  h_ratio_SR2_all->GetXaxis()->SetTitleSize(.13);
  h_ratio_SR2_all->GetXaxis()->SetTitle("#it{D}_{Top+VV}");

   h_ratio_SR2_all->GetXaxis()->SetTickLength(.08);


  line4 = new TLine(1., gPad->GetUymin() + ratio_add_min, 1.,  gPad->GetUymax() + ratio_add_max );
  line5 = new TLine(3., gPad->GetUymin() + ratio_add_min, 3., gPad->GetUymax() + ratio_add_max );
  line6 = new TLine(5., gPad->GetUymin() + ratio_add_min, 5.,  gPad->GetUymax() + ratio_add_max) ;
  line7 = new TLine(7., gPad->GetUymin() + ratio_add_min, 7., gPad->GetUymax() + ratio_add_max );
  line4->Draw("same");
  line5->Draw("same");
  line6->Draw("same");
  line7->Draw("same");

  TLine* sr2_line = new TLine(-1, 1, 9, 1 );

  sr2_line->SetLineColor(kBlack);
  sr2_line->Draw("same");
  gPad->RedrawAxis();


  gPad->RedrawAxis();


  can->cd();

  TPad* pad4dycr = new TPad("pad4dycr", "pad4dycr", .54, 0.2, 1., .5);

  pad4dycr->SetTopMargin(0.012);
  pad4dycr->SetBottomMargin(0.035);
  pad4dycr->SetLeftMargin(0.03);
  pad4dycr->SetRightMargin(.2);

  pad4dycr->Draw();
  pad4dycr->cd();

  h_stack_DYCR->Draw("hist Y+");
  
  h_sys_band_DYCR->SetFillColor(kGray+2);
  h_sys_band_DYCR->SetLineColor(kWhite);
  h_sys_band_DYCR->SetFillStyle(3345);
  h_sys_band_DYCR->Draw("e2 same");
  h_data_DYCR->SetMarkerSize(.8);
  h_data_DYCR->SetMarkerStyle(8);
  h_data_DYCR->Draw("ep same");

  h_stack_DYCR->GetXaxis()->SetLabelOffset(1.);
  h_stack_DYCR->GetYaxis()->SetLabelOffset(.006);
  h_stack_DYCR->GetYaxis()->SetLabelSize(.068);
  h_stack_DYCR->GetYaxis()->SetTitle("Events / 22 GeV");
  h_stack_DYCR->GetYaxis()->SetTitleSize(0.073);
  h_stack_DYCR->GetYaxis()->SetTitleOffset(1.1);

  mytext.SetTextSize(.065);

  double zjets_y_title = 320;
 // if( input=="lep1_pt" || input=="jet0_pt" || input=="jet1_pt") zjets_y_title = 232.5;
  subtit=getObsName(observable) + " Z+jets CR";
  mytext.DrawLatex(88,zjets_y_title,subtit.c_str());

  TLegend* legendggfcr = new TLegend(0.36,0.42,.76,0.73);
  legendggfcr->SetBorderSize(0);
  legendggfcr->SetFillStyle(0);
  legendggfcr->SetTextSize(0.);
  legendggfcr->SetNColumns(2);
  legendggfcr->AddEntry(h_data_DYCR, "#bf{Data}", "p");
  legendggfcr->AddEntry(h_sys_band_DYCR, "#bf{Uncertainty}", "f");
  legendggfcr->AddEntry(h_vbf_SR1_all,"#bf{H_{VBF}}", "f");
  legendggfcr->AddEntry(h_ggf_SR1_all, "#bf{H_{other}}", "f");
  legendggfcr->AddEntry(h_top_SR1_all, "#bf{Top}","f");
  legendggfcr->AddEntry(h_diboson_SR1_all, "#bf{VV}", "f");
  legendggfcr->AddEntry(h_Zjets_SR1_all, "#bf{Z/#scale[1.1]{#gamma}*+jets}", "f");
  legendggfcr->AddEntry(h_Fakes_SR1_all, "#bf{Mis-Id}", "f");
  
  legendggfcr->Draw();

  can->cd();
  TPad* ratiopad4dycr = new TPad("ratiopad4dycr","ratiopad4dycr", .54, 0.0025, 1., .2);

  ratiopad4dycr->SetLeftMargin(0.03);//(0.002);
  ratiopad4dycr->SetRightMargin(0.2);
  ratiopad4dycr->SetBottomMargin(.4);
  ratiopad4dycr->SetTopMargin(0.08);
  ratiopad4dycr->Draw();
  ratiopad4dycr->cd();
  gPad->SetGridy(1);
  h_ratio_DYCR->SetMarkerSize(.8);
  h_ratio_DYCR->SetMarkerStyle(8);
  h_ratio_DYCR->Draw("ep Y+");
  h_ratio_sys_band_DYCR->SetFillColor(kGray+2);
  h_ratio_sys_band_DYCR->SetLineColor(kWhite);
  h_ratio_sys_band_DYCR->SetFillStyle(3345);
  h_ratio_sys_band_DYCR->Draw("e2 same");
  h_ratio_DYCR->Draw("ep same");

  h_ratio_DYCR->GetYaxis()->SetLabelSize(.106);
  h_ratio_DYCR->GetXaxis()->SetLabelSize(.106);
  h_ratio_DYCR->GetYaxis()->SetLabelOffset(.008);
  h_ratio_DYCR->GetXaxis()->SetLabelOffset(.01);
  h_ratio_DYCR->GetYaxis()->SetNdivisions(505);

  h_ratio_DYCR->GetYaxis()->SetTitle("Data / Pred.");

  h_ratio_DYCR->GetXaxis()->SetTickLength(.06);


  h_ratio_DYCR->GetXaxis()->SetTitleOffset(.9);
  h_ratio_DYCR->GetYaxis()->SetTitleOffset(.7);


  h_ratio_DYCR->GetXaxis()->SetTitleSize(.12);
  h_ratio_DYCR->GetYaxis()->SetTitleSize(.11);

  h_ratio_DYCR->GetXaxis()->SetTitle("#it{m}_{T} [GeV]");

  h_ratio_DYCR->GetYaxis()->SetRangeUser(0.2,1.6);

  TArrow *ar6 = new TArrow(140,1.2,140,1.4, .007,">");

  ar6->SetLineColor(kRed);
  ar6->SetFillColor(kWhite);
  ar6->Draw();

  TLine* dycr_line = new TLine(40, 1, 150, 1 );
  dycr_line->SetLineColor(kBlack);
  dycr_line->Draw("same");
  gPad->RedrawAxis();

  can->cd();

  TLatex atlastex;
  atlastex.SetTextSize(.023);
  atlastex.DrawLatex(0.092, 0.95, "#it{#bf{#scale[1.2]{ATLAS}}}  Internal");
  atlastex.DrawLatex(.58, 0.95, "#sqrt{#scale[.8]{s}} #scale[.8]{= 13 TeV,} #scale[.8]{139 fb^{-1}}");

  std::string output = "prefit_BDT_" + observable + ".pdf";
  can->SaveAs(output.c_str());


}



