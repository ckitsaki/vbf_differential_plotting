#include <stdlib.h>
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
	
	return " ";
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



