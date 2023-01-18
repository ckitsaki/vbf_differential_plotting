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
	if(observable=="DPhill") return "#it{#Delta#phi}_{ll}";
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
		histo->GetYaxis()->SetLabelOffset(0.03);
		if(region.find("SR1") != string::npos){
			if(setRatioLimits)
				histo->GetYaxis()->SetRangeUser(ymin_SR1, ymax_SR1);
			else
				histo->GetYaxis()->SetRangeUser(0.5,1.5);
		}
		else if(region.find("SR2") != string::npos){
			if(setRatioLimits){
				histo->GetYaxis()->SetRangeUser(ymin_SR2, ymax_SR2);
			}
			else
				histo->GetYaxis()->SetRangeUser(0.,2.);
		}
		if( bin==4 ) {
			std::string xaxis_tit = xAxisTitle(region);
			histo->GetXaxis()->SetTitle(xaxis_tit.c_str());
			histo->GetXaxis()->SetTitleOffset(0.5);
			histo->GetXaxis()->SetTitleSize(0.15);
		}
		else histo->GetXaxis()->SetTitleOffset(10);
		histo->GetXaxis()->SetLabelOffset(10);
		histo->GetXaxis()->SetNdivisions(505);
		histo->GetYaxis()->SetTickLength(.1);
		histo->GetYaxis()->SetTitleSize(0.12);
		histo->GetYaxis()->SetLabelSize(.12);
	}
	if(region=="ggFCR1" )
	{
		histo->GetYaxis()->SetTitleSize(.06);
		histo->GetYaxis()->SetRangeUser(0.8,1.2);
		histo->GetYaxis()->SetNdivisions(505);
		histo->GetYaxis()->SetTitleOffset(1.);
		histo->GetYaxis()->SetLabelSize(.06);
		histo->GetXaxis()->SetLabelSize(.06);
		histo->GetXaxis()->SetTitleSize(.06);
		histo->GetXaxis()->SetLabelOffset(.02);
		histo->GetYaxis()->SetTickLength(.02);
	}
	else if (region=="DYCR")
	{
		histo->GetYaxis()->SetTitleSize(.06);
		histo->GetYaxis()->SetNdivisions(505);
		histo->GetYaxis()->SetTitleOffset(1.);
		histo->GetYaxis()->SetLabelSize(.06);
		histo->GetXaxis()->SetLabelSize(.06);
		histo->GetXaxis()->SetTitleSize(.06);
		histo->GetXaxis()->SetLabelOffset(.02);
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
	histo->GetYaxis()->SetTitle("Events");
	histo->GetXaxis()->SetNdivisions(505);
	histo->GetYaxis()->SetTitleOffset(1.4);
	if(region=="ggFCR1" )
	{
		histo->GetYaxis()->SetTitleSize(.045);
		histo->GetYaxis()->SetTitleOffset(1.5);
		histo->GetYaxis()->SetLabelSize(.045);
		histo->GetYaxis()->SetTickLength(.015);
	} 
	else if (region=="DYCR")
	{
		histo->GetYaxis()->SetTitleSize(.06);
		histo->GetYaxis()->SetTitleOffset(1.1);
		histo->GetYaxis()->SetLabelSize(.06);
		histo->GetYaxis()->SetTickLength(.015);
		TLegend* leg = (TLegend*)pad->GetPrimitive("mylegend");
		leg->SetX1(0.55);
		leg->SetY1(0.41);
		leg->SetY2(0.71);
		leg->SetX2(0.89);
	}
	else {
		histo->GetYaxis()->SetTitleSize(.12);
		histo->GetYaxis()->SetLabelOffset(0.03);
		histo->GetYaxis()->SetLabelSize(.12);
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
  	mytext.SetTextSize(.014);
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

//  SR1 panel
	std::string region = "SR1";

	float xstart_main = 0.03;
	float xend_main = 0.15;
	float ystart_main = 0.65;
	float yend_main = 1.;

	float xstart_ratio = 0.03;
	float xend_ratio = 0.15;
	float ystart_ratio = 0.4;
	float yend_ratio = .65;
	
	for(int ibin=0; ibin<binSR1; ibin++)
	{
		std::string padName = "main_pad_bdt_vbf_"+ observable +"_" + region + observable +"_" + std::to_string(ibin);
		TPad* pad = DumpPadFromFile(region, padName, observable, ibin, setRatioLimits, ymin_SR1, ymax_SR1, ymin_SR2, ymax_SR2);
		pad->SetPad(xstart_main,ystart_main,xend_main,yend_main);
		pad->SetTopMargin(0.15);
		if(ibin==0)
			pad->SetLeftMargin(0.35);
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
			ratio_pad->SetLeftMargin(0.35);
		else 
			ratio_pad->SetLeftMargin(0.);
		if(ibin!= binSR1-1) ratio_pad->SetRightMargin(0);

		k->cd();
		ratio_pad->Draw();

		textname = "#bf{" + getObsName(observable) + "Bin" + std::to_string(ibin+1) + "}";
		mytext.DrawLatex(0.09+ibin*0.1, .91, textname.c_str());

		if(!v_mult_factors_SR1.empty())
   		{
   			std::string times = "#bf{x"+ v_mult_factors_SR1.at(ibin) + "}";
 			mytext.DrawLatex(0.1+ibin*0.1, 0.89, times.c_str());
   		}

		xstart_main = xend_main;
		xend_main += 0.1;

		xstart_ratio = xend_ratio;
		xend_ratio += 0.1;

	}
	
	textname = "#bf{" + region + "}";
  	mytext.DrawLatex(0.3, .925, textname.c_str());

  	labeltext.SetTextSize(.013);
  	std::string labelname_up = "#bf{1.0}";
  	std::string labelname_down = "#bf{0.5}";
  	for(int ibin=0; ibin<binSR1; ibin++) {
   		labeltext.DrawLatex(.13 + ibin*0.1, .63, labelname_up.c_str());
   		if(ibin==0) labeltext.DrawLatex(.07 , .485, labelname_down.c_str());
   		else
   			labeltext.DrawLatex(.08 + ibin*0.1-0.03, .485, labelname_down.c_str());

  	}
/*
  	TArrow *ar = new TArrow(.23,.6,.23,.61, .007,">");
  	ar->SetLineColor(kRed);
  	ar->SetFillColor(kWhite);
  	ar->Draw();

  	ar = new TArrow(.27,.51,.27,.52, .007,"<");
  	ar->SetLineColor(kRed);
  	ar->SetFillColor(kWhite);
  	ar->Draw();

  	ar = new TArrow(.525,.6,.525,.61, .007,">");
  	ar->SetLineColor(kRed);
  	ar->SetFillColor(kWhite);
  	ar->Draw();
*/
// GGFCR panel
	region= "ggFCR1";
	std::string padName = "main_pad_bdt_ggFCR1_ggFCR1";
	TPad* pad = DumpPadFromFile(region, padName, observable, -1, setRatioLimits, ymin_SR1, ymax_SR1, ymin_SR2, ymax_SR2);
	pad->SetPad(0.55, .65, 1., 1.);
	pad->SetTopMargin(0.15);
	pad->SetLeftMargin(0.2);
	pad->SetRightMargin(0.1);
	k->cd();
	pad->Draw();	

	padName = "ratio_pad_bdt_ggFCR1_ggFCR1";
	TPad* ratio_pad = DumpPadFromFile(region, padName, observable, -1, setRatioLimits, ymin_SR1, ymax_SR1, ymin_SR2, ymax_SR2);
	ratio_pad->SetPad(0.55, .41, 1., .65);
	ratio_pad->SetTopMargin(0.1);
	//ratio_pad->SetBottomMargin(0.1);
	ratio_pad->SetLeftMargin(0.2);
	ratio_pad->SetRightMargin(0.1);
	k->cd();
	ratio_pad->Draw();

	textname = "#bf{" + getObsName(observable) + " ggF CR}";
  	mytext.DrawLatex(0.79, .92, textname.c_str());

// DYCR panel
	region= "DYCR";
	padName = "main_pad_MT_DYCR";
	pad = DumpPadFromFile(region, padName, observable, -1, setRatioLimits, ymin_SR1, ymax_SR1, ymin_SR2, ymax_SR2);
	pad->SetPad(0.55, .2, 1., .46);
	//pad->SetTopMargin(0.1);
	pad->SetLeftMargin(0.2);
	pad->SetRightMargin(0.1);
	k->cd();
	pad->Draw();	

	padName = "ratio_pad_MT_DYCR";
	ratio_pad = DumpPadFromFile(region, padName, observable, -1, setRatioLimits, ymin_SR1, ymax_SR1, ymin_SR2, ymax_SR2);
	ratio_pad->SetPad(0.55, -0.04, 1., .2);
	ratio_pad->SetTopMargin(0.1);
	ratio_pad->SetLeftMargin(0.2);
	ratio_pad->SetRightMargin(0.1);
	k->cd();

	ratio_pad->Draw();
	TArrow *ar6 = new TArrow(.925,.15,.925,.16, .007,">");
  	ar6->SetLineColor(kRed);
  	ar6->SetFillColor(kWhite);
  	ar6->Draw();


  	textname = "#bf{" + getObsName(observable) + " Z+jets CR}";
  	mytext.DrawLatex(0.79, .42, textname.c_str());


// SR2 panel

	region = "SR2";

	xstart_main = 0.03;
	xend_main = 0.15;
	ystart_main = 0.2;
	yend_main = .46;

	xstart_ratio = 0.03;
	xend_ratio = 0.15;
	ystart_ratio = -0.04;
	yend_ratio = .2;
	
	for(int ibin=0; ibin<binSR1; ibin++)
	{
		padName = "main_pad_bdt_TopWWAll_" + region + observable +"_" + std::to_string(ibin);
		pad = DumpPadFromFile(region, padName, observable, ibin, setRatioLimits, ymin_SR1, ymax_SR1, ymin_SR2, ymax_SR2);
		pad->SetPad(xstart_main,ystart_main,xend_main,yend_main);
		if(ibin==0)
			pad->SetLeftMargin(0.35);
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
			ratio_pad->SetLeftMargin(0.35);
		else 
			ratio_pad->SetLeftMargin(0.);
		if(ibin!= binSR1-1) ratio_pad->SetRightMargin(0);

		k->cd();
		ratio_pad->Draw();

		textname = "#bf{" + getObsName(observable) + "Bin" + std::to_string(ibin+1) + "}";
		mytext.DrawLatex(0.09+ibin*0.1, .41, textname.c_str());

		if(!v_mult_factors_SR2.empty())
   		{
   			std::string times = "#bf{x"+ v_mult_factors_SR2.at(ibin) + "}";
 			mytext.DrawLatex(0.1+ibin*0.1, 0.39, times.c_str());
   		}

		gPad->RedrawAxis();

		xstart_main = xend_main;
		xend_main += 0.1;

		xstart_ratio = xend_ratio;
		xend_ratio += 0.1;
	}

	labelname_down = "#bf{-1.0}";
	for(int ibin=0; ibin<binSR1; ibin++) {
   		labeltext.DrawLatex(.13 + ibin*0.1, .18, labelname_up.c_str());
   		if(ibin==0) labeltext.DrawLatex(.07 , 0.04, labelname_down.c_str());
   		else
   			labeltext.DrawLatex(.08 + ibin*0.1-0.03, 0.04, labelname_down.c_str());
  	}
/*
  	ar6 = new TArrow(.36,.15,.36,.16, .007,">");
  	ar6->SetLineColor(kRed);
  	ar6->SetFillColor(kWhite);
  	ar6->Draw();
*/
	k->cd();
	TLatex atlastex;
  	atlastex.SetTextSize(.02);
  	atlastex.DrawLatex(0.075, 0.96, "#it{ATLAS}  #bf{Internal}");
  	atlastex.DrawLatex(.82, 0.96, "#bf{#sqrt{#scale[.8]{s}} #scale[.8]{= 13 TeV,} #scale[.8]{139 fb^{-1}}}");

  	textname = "#bf{" + region + "}";
  	mytext.DrawLatex(0.3, .425, textname.c_str());

  	std::string output = "prefit_BDT_" + observable + ".pdf";
	k->SaveAs(output.c_str());
}



