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

   const char* GraphTitle = "";

   TFile *f = new   TFile(    "TimeResolution_wrt_Current.root","RECREATE");

   TGaxis::SetMaxDigits(6);
   gStyle->SetOptStat(0);


   // Set TDR Style
   setTDRStyle();
   gStyle->SetOptFit(0);

   writeExtraText = true;       // if extra text
   extraText  = "#italic{Preliminary}";  // default extra text is "Preliminary"
   int iPeriod = 0;    // 1=7TeV, 2=8TeV, 3=7+8TeV, 7=7+8+13TeV, 0=free form (uses lumi_sqrtS)

   TNtuple *NT_Detector1 = new TNtuple("TimeResolutionRawData_ArCO2","data from text file","CurrentSuppliedToHVDivider:TimeResolution:ErrInTimeRes");

   Int_t nlines = 0;

   vector<double> NT_Detector1_HV,NT_Detector1_Eff,NT_Detector1_EffErr;

   double current, eff, efferr;
   while (1) 
   {
     File1 >> current >> eff >> efferr;
     cout<<"==> "<<current<<"\t"<<eff<<"\t"<<efferr<<endl;
	if (!File1.good()) break;

	NT_Detector1_HV.push_back(current);
	NT_Detector1_Eff.push_back(eff);
        NT_Detector1_EffErr.push_back(efferr);

	NT_Detector1->Fill(current,eff,efferr);
	nlines++;
   }

   File1.close();
   
   TCanvas* c1 = new TCanvas(CanvasName,CanvasName);
   gPad->SetTicks(0,1);

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
   gr1->GetYaxis()->SetRangeUser(6,20);
   gr1->GetXaxis()->SetLimits(600.0001,720);
   gr1->GetYaxis()->SetDecimals(1);
   f1->SetLineColor(kMagenta+2);
   gr1->Fit("f1","ER");
   gr1->Draw("AP");

   //Draw the Legend 
   TLegend *leg = new TLegend(0.47,0.770,0.91,0.87);
   leg->SetFillStyle(0);
   leg->SetBorderSize(0);
   leg->SetTextSize(0.05);
   leg->SetTextFont(42);
   leg->AddEntry(gr1,Detector1,"PE");

   leg->Draw("same");

   TLatex *text1 = new TLatex(660.0,17.0,"Threshold = 1.2 fC");
   TLatex *text2 = new TLatex(660.0,15.8,"Beam: Muon");
   TLatex *text3 = new TLatex(660.0,14.6,"Gap Config: 3/1/2/1 mm");
   TLatex *text4 = new TLatex(660.0,13.4,"Gas: Ar/CO2 (70/30)");
   TLatex *text8 = new TLatex(644.0,07.0,"Region of efficiency > 95%");


   text1->SetTextFont(42);
   text2->SetTextFont(42);
   text3->SetTextFont(42);
   text4->SetTextFont(42);
   text8->SetTextFont(42);
   text1->SetTextSize(0.05);
   text2->SetTextSize(0.05);
   text3->SetTextSize(0.05);
   text4->SetTextSize(0.05);
   text8->SetTextSize(0.055);
   text8->SetTextColor(2);
   text1->Draw("same");
   text2->Draw("same");
   text3->Draw("same");
   text4->Draw("same");
   text8->Draw("same");

   TLatex *cmsprem = new TLatex(580.,20.2,"CMS #it{Preliminary}");
   TLatex *gen = new TLatex(885,20.2,"GE1/1");
   gen->SetTextSize(0.05);
   cmsprem->SetTextSize(0.04);
   //cmsprem->Draw("same");
   //gen->Draw("same");


	// Ref: https://root.cern.ch/root/htmldoc/tutorials/hist/twoscales.C.html
   //draw an axis on the right side
   TGaxis *axis_1 = new TGaxis(600.0001,20.0,720,20.0,
   								0.6000001*4.7,0.720*4.7,510,"-");	// 4.7M ohm is the equivalent resistance, so this will give drift voltage in Volts; 600-> 600/1000 to convert Volts to kV.
   axis_1->SetTitle("V_{Drift} (kV)");
   axis_1->SetTitleOffset(1.0);
   axis_1->SetTitleFont(42);
   axis_1->SetTitleSize(0.05);
   axis_1->SetTitleColor(1);
   axis_1->SetLabelFont(42);
   axis_1->SetLabelSize(0.05);
   axis_1->SetLabelColor(kBlack);
   axis_1->SetLineColor(kBlack);
   axis_1->Draw("sames");


   TPad *p = new TPad("p","p",0.,0.,1.,1.); p->SetFillStyle(0); p->Draw("same"); p->cd();
   TBox *b = new TBox(0.4,0.15,0.88,0.430);
   //b->SetFillColor(2);
   b->SetFillStyle(0);
   b->SetLineColor(2);
   b->SetLineWidth(2.);
   b->Draw("same");

   c1->Update();
   c1->SaveAs(pdfFile);
   c1->SaveAs(pngFile);

   c1->Write();
   f->Write();
}
