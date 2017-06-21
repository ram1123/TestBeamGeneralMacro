#include <iostream>
#include <fstream>
#include "TFile.h"
#include "TNtuple.h"
#include "string.h"
#include <vector>
#include "TCanvas.h"
#include "TPad.h"
#include "TH1F.h"
#include "TGraphErrors.h"
#include "TGaxis.h"
#include "TFrame.h"
#include "TLegend.h"
#include "TArrow.h"
#include "setTDRStyle.C"
#include "CMS_lumi.C"
//#include ".h"

void GE11sTimeResolution_vs_current_and_VDrift_BothAxis()
{

   
   // Input Files 
   ifstream File1;

    File1.open("TimeResolution_etaphi52_ArCO2.txt");

   // Name of Detector
   const char*  Detector1 = "#left(i#eta,i#phi#right)=#left(5,2#right)";
   const char* RunRange = "Gap Config = 3/1/2/1 mm";

   const char* CanvasName   = "TimeResolution_wrt_Current";
   const char* pdfFile	    = "TimeResolution_wrt_Current.pdf";
   const char* pngFile	    = "TimeResolution_wrt_Current.png";

   TFile *f = new   TFile(    "TimeResolution_wrt_Current.root","RECREATE");

   TGaxis::SetMaxDigits(6);
   gStyle->SetOptStat(0);

   //const char* GraphTitle = "Efficiency For Run Range 306 To 407: 2014H2B";
   const char* GraphTitle = "";


   // Set TDR Style
   setTDRStyle();
   gStyle->SetOptFit(0);

   writeExtraText = true;       // if extra text
   extraText  = "#italic{Preliminary}";  // default extra text is "Preliminary"
   int iPeriod = 0;    // 1=7TeV, 2=8TeV, 3=7+8TeV, 7=7+8+13TeV, 0=free form (uses lumi_sqrtS)

   TNtuple *NT_Detector1 = new TNtuple(Detector1,"data from text file","NT_Detector1_CurrentToHVDivider:NT_Detector1_Eff:NT_Detector1_EffErr");

   Int_t nlines = 0;

   vector<double> NT_Detector1_HV,NT_Detector1_Eff,NT_Detector1_EffErr,NT_Detector2_HV,NT_Detector2_Eff,NT_Detector2_EffErr,NT_Detector3_HV,NT_Detector3_Eff,NT_Detector3_EffErr, NT_Detector1_Gain, NT_Detector2_Gain, NT_Detector3_Gain, NT_Detector4_HV,NT_Detector4_Eff,NT_Detector4_EffErr, NT_Detector4_Gain;

   double current, eff, efferr;
   while (1) 
   {
     File1 >> current >> eff >> efferr;
     cout<<"==> "<<current<<"\t"<<eff<<"\t"<<efferr<<endl;
	if (!File1.good()) break;

	NT_Detector1_HV.push_back(current);
	//NT_Detector1_HV.push_back(current);
	NT_Detector1_Eff.push_back(eff);
        NT_Detector1_EffErr.push_back(efferr);

	NT_Detector1->Fill(current,eff,efferr);
	nlines++;
   }

   File1.close();
   
   TCanvas* c1 = new TCanvas(CanvasName);
   c1->Range(0,0,1,1);
   TPad *pad = new TPad("pad","",0,0,1,1);
   pad->SetTopMargin(0.15);
   pad->SetGrid();
   pad->SetTicks(0,1);
   pad->Draw();
   pad->cd();

   TF1 *f1 = new TF1("f1","pol2",610,710);


   // create first graph
   TGraphErrors *gr1 = new TGraphErrors(NT_Detector1_HV.size());
   for(unsigned int i=0;i<NT_Detector1_HV.size();i++)
   {
       gr1->SetPoint(i,NT_Detector1_HV[i],NT_Detector1_Eff[i]);
       gr1->SetPointError(i,0,4*NT_Detector1_EffErr[i]);
   }
   gr1->SetMarkerColor(kMagenta+2);
   gr1->SetLineColor(kMagenta+2);
   gr1->SetMarkerStyle(20);
   gr1->GetXaxis()->SetTitle("Current Supplied to HV Divider (#mu A)");
   gr1->GetYaxis()->SetTitle("Time resolution (ns)");
   gr1->SetTitle(GraphTitle);
   gr1->GetYaxis()->SetRangeUser(5,20);
   gr1->GetXaxis()->SetLimits(600,800);
   gr1->GetYaxis()->SetDecimals(1);
   f1->SetLineColor(kMagenta+2);
   gr1->Fit("f1","ER");
   gr1->Draw("AP");

   //Draw the Legend 
   TLegend *leg = new TLegend(0.50,0.450,0.90,0.55);
   leg->SetTextSize(0.05);
   leg->SetTextFont(42);
   leg->AddEntry(gr1,Detector1,"PE");

   leg->Draw("same");

   TLatex *text1 = new TLatex(700.0,18,"Threshold = 1.2 fC");
   TLatex *text2 = new TLatex(700.0,16.5,"Beam: Muon");
   TLatex *text3 = new TLatex(700.0,15,"Gap Config: 3/1/2/1 mm");
   TLatex *text4 = new TLatex(700.0,13.5,"Gas: Ar/CO2 (70/30)");
   TLatex *text8 = new TLatex(624.0,06.0,"Region of efficiency > 95%");


   text1->SetTextFont(42);
   text2->SetTextFont(42);
   text3->SetTextFont(42);
   text4->SetTextFont(42);
   text8->SetTextFont(42);
   text1->SetTextSize(0.05);
   text2->SetTextSize(0.05);
   text3->SetTextSize(0.05);
   text4->SetTextSize(0.05);
   text8->SetTextSize(0.06);
   text8->SetTextColor(2);
   TLatex *cmsprem = new TLatex(580.,20.2,"CMS #it{Preliminary}");
   TLatex *Ecmsprem = new TLatex(2.265,5.7,"Region of efficiency > 95%");
   TLatex *gen = new TLatex(885,20.2,"GE1/1");
   //gen->SetTextFont(42);
   //gen->SetTextSize(0.05);
   //cmsprem->SetTextSize(0.04);
   text1->Draw("same");
   text2->Draw("same");
   text3->Draw("same");
   text4->Draw("same");
   text8->Draw("same");
   //cmsprem->Draw("same");
   //Ecmsprem->Draw("same");
   //gen->Draw("same");


	// Ref: https://root.cern.ch/root/htmldoc/tutorials/hist/twoscales.C.html
   //draw an axis on the right side
   TGaxis *axis_1 = new TGaxis(600,20.0,800,20.0,
   								0.600*4.7,0.800*4.7,510,"-");	// 4.7M ohm is the equivalent resistance, so this will give drift voltage in Volts; 600-> 600/1000 to convert Volts to kV.
   axis_1->SetTitle("V_Drift (kV)");
   axis_1->SetTitleOffset(1.0);
   axis_1->SetTitleFont(42);
   axis_1->SetTitleSize(0.06);
   axis_1->SetTitleColor(1);
   axis_1->SetLabelFont(42);
   axis_1->SetLabelSize(0.05);
   axis_1->SetLabelColor(kBlack);
   axis_1->SetLineColor(kBlack);
   axis_1->Draw("sames");


   TPad *p = new TPad("p","p",0.,0.,1.,1.); p->SetFillStyle(0); p->Draw("same"); p->cd();
   TBox *b = new TBox(0.2,0.15,0.68,0.445);
   //b->SetFillColor(2);
   b->SetFillStyle(0);
   b->SetLineColor(2);
   b->SetLineWidth(2.);
   b->Draw("same");

   c1->Update();
   c1->SaveAs(pdfFile);
   c1->SaveAs(pngFile);
   //c1->SaveAs();

   c1->Write();
   f->Write();
}
