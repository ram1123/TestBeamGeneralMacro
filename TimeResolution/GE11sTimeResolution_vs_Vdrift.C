/*
 * =====================================================================================
 *
 *       Filename:  GE11sEfficiencyScan.C
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  Sunday 02 August 2015 11:33:33  CEST
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Ramkrishna Sharma (Ram), ramkrishna.sharma71@gmail.com
 *   Organization:  CERN
 *
 * =====================================================================================
 */

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
//#include "tdrstyle.C"
#include "setTDRStyle.C"
#include "CMS_lumi.C"
//#include ".h"

void GE11sTimeResolution_vs_Vdrift()
{
   
   // Input Files 
   ifstream File1, File2, File3, File4;
   //File1.open("EfficiencyData_R306_R407_Lat21_GE11_IV_GIF.txt");
   //File2.open("EfficiencyData_R306_R407_Lat21_GE11_IV.txt");
   //File3.open("EfficiencyData_R306_R407_Lat22_GE11_V.txt");

    File1.open("TimeResolution_etaphi52_ArCO2.tex");
    File2.open("TR_3Gas_eta1.txt");
    File3.open("TimeResolution_etaphi52_ArCO2CF4.tex");
    File4.open("TR_3Gas_eta8.txt");

   // Name of Detector
   //const char*  Detector1 = "#left(i#eta,i#phi#right)=#left(5,2#right)";
   //const char*  Detector2 = "#left(i#eta,i#phi#right)=#left(1,2#right)";
   //const char*  Detector3 = "#left(i#eta,i#phi#right)=#left(8,2#right)";
   const char*  Detector1 = "#left(i#eta,i#phi#right)=#left(5,2#right)";
   //const char*  Detector1 = "#left(i#eta,i#phi#right)=#left(5,2#right); Ar/CO_{2} (70/30)";
   const char*  Detector2 = "#left(i#eta,i#phi#right)=#left(1,2#right); Ar/CO_{2}/CF_{4} (45/15/40)";
   const char*  Detector3 = "#left(i#eta,i#phi#right)=#left(5,2#right)";
   //const char*  Detector3 = "#left(i#eta,i#phi#right)=#left(5,2#right); Ar/CO_{2}/CF_{4} (45/15/40)";
   const char*  Detector4 = "#left(i#eta,i#phi#right)=#left(8,2#right); Ar/CO_{2}/CF_{4} (45/15/40)";
   //const char*  Detector1 = "Latency 21: GE11_IV_GIF";
   //const char*  Detector2 = "Latency 21: GE11_IV";
   //const char*  Detector3 = "Latency 22: GE11_V";

   const char* RunRange = "Gap Config = 3/1/2/1 mm";
   //const char* RunRange = "Threshold=15 VFAT units";
   const char* BeamType = "";
   const char* MSPL = "";
   const char* Threshold = "";
   //const char* Threshold = "Errors= Error*4.0";
   const char* GasUsed = "";
   const char* ClockMode = "";
   const char* EtaPhiSector = "";

   const char* CanvasName   = "TimeResolution_wrt_VDrift";
   const char* pdfFile	    = "TimeResolution_wrt_VDrift.pdf";
   const char* pngFile	    = "TimeResolution_wrt_VDrift.png";
   TFile *f = new   TFile(    "TimeResolution_wrt_VDrift.root","RECREATE");

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
   TNtuple *NT_Detector2 = new TNtuple(Detector2,"data from text file","NT_Detector2_CurrentToHVDivider:NT_Detector2_Eff:NT_Detector2_EffErr");
   TNtuple *NT_Detector3 = new TNtuple(Detector3,"data from text file","NT_Detector3_CurrentToHVDivider:NT_Detector3_Eff:NT_Detector3_EffErr");
   TNtuple *NT_Detector4 = new TNtuple(Detector4,"data from text file","NT_Detector4_CurrentToHVDivider:NT_Detector4_Eff:NT_Detector4_EffErr");

   Int_t nlines = 0;

   vector<double> NT_Detector1_HV,NT_Detector1_Eff,NT_Detector1_EffErr,NT_Detector2_HV,NT_Detector2_Eff,NT_Detector2_EffErr,NT_Detector3_HV,NT_Detector3_Eff,NT_Detector3_EffErr, NT_Detector1_Gain, NT_Detector2_Gain, NT_Detector3_Gain, NT_Detector4_HV,NT_Detector4_Eff,NT_Detector4_EffErr, NT_Detector4_Gain;
   double current, eff, efferr;
   while (1) 
   {
     File1 >> current >> eff >> efferr;
     cout<<"==> "<<current*4.7<<"\t"<<eff<<"\t"<<efferr<<endl;
	if (!File1.good()) break;

	NT_Detector1_HV.push_back(current*4.7);
	//NT_Detector1_HV.push_back(current);
	NT_Detector1_Eff.push_back(eff);
        NT_Detector1_EffErr.push_back(efferr);

	NT_Detector1->Fill(current,eff,efferr);
	nlines++;
   }
   while (1) 
   {
     File2 >> current >> eff >> efferr;
     cout<<"==> "<<current<<"\t"<<eff<<"\t"<<efferr<<endl;
	if (!File2.good()) break;

	NT_Detector2_HV.push_back(current*4.7);
	//NT_Detector2_HV.push_back(current);
	NT_Detector2_Eff.push_back(eff);
        NT_Detector2_EffErr.push_back(efferr);

	NT_Detector2->Fill(current,eff,efferr);
	nlines++;
   }
   while (1) 
   {
     File3 >> current >> eff >> efferr;
     cout<<"==> "<<current*4.7<<"\t"<<eff<<"\t"<<efferr<<endl;
	if (!File3.good()) break;

	NT_Detector3_HV.push_back(current*4.7);
	//NT_Detector3_HV.push_back(current);
	NT_Detector3_Eff.push_back(eff);
        NT_Detector3_EffErr.push_back(efferr);

	NT_Detector3->Fill(current,eff,efferr);
	nlines++;
   }
   while (1) 
   {
     File4 >> current >> eff >> efferr;
     //cout<<"==> "<<current<<"\t"<<eff<<"\t"<<efferr<<endl;
	if (!File4.good()) break;

	NT_Detector4_HV.push_back(current*4.7);
	//NT_Detector3_HV.push_back(current);
	NT_Detector4_Eff.push_back(eff);
        NT_Detector4_EffErr.push_back(efferr);

	NT_Detector4->Fill(current,eff,efferr);
	nlines++;
   }

   File1.close();
   File2.close();
   File3.close();
   File4.close();
   
   TCanvas* c1 = new TCanvas(CanvasName,"",1);
   c1->Range(0,0,1,1);
   TPad *pad = new TPad("pad","",0,0,1,1);
   pad->SetGrid();
   pad->Draw();
   pad->cd();

   TF1 *f1 = new TF1("f1","pol2",2867,3337);
   TF1 *f2 = new TF1("f2","pol6",3196,3760);


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
   gr1->GetXaxis()->SetTitle("Drift Voltage (V)");
   //gr1->GetXaxis()->SetTitle("Effective Gain");
   gr1->GetYaxis()->SetTitle("Time resolution (ns)");
   gr1->SetTitle(GraphTitle);
   gr1->GetYaxis()->SetRangeUser(5,20);
   //gr1->GetXaxis()->SetLimits(104,23211);
   gr1->GetXaxis()->SetLimits(2800,4400);
   gr1->GetYaxis()->SetDecimals(1);
   f1->SetLineColor(kMagenta+2);
   gr1->Fit("f1","ER");
   gr1->Draw("AP");
      // create first graph
   TGraphErrors *gr5 = new TGraphErrors(NT_Detector2_HV.size());
   for(unsigned int i=0;i<NT_Detector2_HV.size();i++)
   {
       gr5->SetPoint(i,NT_Detector2_HV[i],NT_Detector2_Eff[i]);
       gr5->SetPointError(i,0,4*NT_Detector2_EffErr[i]);
   }
   gr5->SetMarkerColor(kBlack);
   gr5->SetLineColor(kBlack);
   gr5->SetMarkerStyle(22);
   gr5->GetXaxis()->SetTitle("Current Supplied To HV Divider (uA)");
   gr5->GetYaxis()->SetTitle("Efficiency");
   gr5->SetTitle(GraphTitle);
   //gr5->GetXaxis()->SetRangeUser(500,810);
   //gr5->Fit("f2","R");
   //gr5->Draw("SameP");
      // create first graph
   TGraphErrors *gr8 = new TGraphErrors(NT_Detector3_HV.size());
   for(unsigned int i=0;i<NT_Detector3_HV.size();i++)
   {
       gr8->SetPoint(i,NT_Detector3_HV[i],NT_Detector3_Eff[i]);
       gr8->SetPointError(i,0,4*NT_Detector3_EffErr[i]);
   }
   gr8->SetMarkerColor(kGreen+3);
   gr8->SetLineColor(kGreen+3);
   gr8->SetMarkerStyle(21);
   gr8->GetXaxis()->SetTitle("Current Supplied To HV Divider (uA)");
   gr8->GetYaxis()->SetTitle("Efficiency");
   gr8->SetTitle(GraphTitle);
   //gr8->GetXaxis()->SetRangeUser(500,810);
   f2->SetLineColor(kGreen+3);
   gr8->Fit("f2","ER");
   gr8->Draw("SameP");
      // create first graph
   TGraphErrors *gr9 = new TGraphErrors(NT_Detector4_HV.size());
   for(unsigned int i=0;i<NT_Detector4_HV.size();i++)
   {
       gr9->SetPoint(i,NT_Detector4_HV[i],NT_Detector4_Eff[i]);
       gr9->SetPointError(i,0,4*NT_Detector4_EffErr[i]);
   }
   gr9->SetMarkerColor(kMagenta+2);
   gr9->SetLineColor(kMagenta+2);
   gr9->SetMarkerStyle(23);
   gr9->GetXaxis()->SetTitle("Current Supplied To HV Divider (uA)");
   gr9->GetYaxis()->SetTitle("Efficiency");
   gr9->SetTitle(GraphTitle);
   //gr8->GetXaxis()->SetRangeUser(500,810);
//   gr8->Fit("f3","ER");
//   gr9->Draw("SameP");
   //Draw the Legend 
   TLegend *leg = new TLegend(0.50,0.600,0.90,0.70);
   TLegend *leg2 = new TLegend(0.50,0.450,0.90,0.55);
   leg->SetTextSize(0.05);
   leg2->SetTextSize(0.05);
   leg->SetTextFont(42);
   leg2->SetTextFont(42);
   //leg->AddEntry(gr1,"(i#eta,i#phi)=(1,2)","LPE");
   //leg->AddEntry(gr5,"(i#eta,i#phi)=(5,2)","LPE");
   //leg->AddEntry(gr8,"(i#eta,i#phi)=(8.2)","LPE");
   leg->AddEntry(gr1,Detector1,"PE");
//   leg->AddEntry(gr5,Detector2,"PE");
   leg2->AddEntry(gr8,Detector3,"PE");
//   leg->AddEntry(gr9,Detector4,"PE");

   leg->Draw("same");
   leg2->Draw("same");

   TLatex *text1 = new TLatex(3600.0,19,"Threshold = 1.2 fC");
   TLatex *text2 = new TLatex(3600.0,18,"Beam: Muon");
   TLatex *text3 = new TLatex(3600.0,17,"Gap Config: 3/1/2/1 mm");
   TLatex *text4 = new TLatex(3600.0,16,"Gas: Ar/CO2 (70/30)");
   TLatex *text5 = new TLatex(3600.0,13,"Gas: Ar/CO2/CF4 (45/15/40)");
//   TLatex *text3 = new TLatex(3800,0.38,MSPL);
//   TLatex *text4 = new TLatex(3800,0.22,Threshold);
//   TLatex *text5 = new TLatex(3250,0.64,ClockMode);
   TLatex *text6 = new TLatex(3250,0.56,EtaPhiSector);
   TLatex *text7 = new TLatex(3250,0.48,GasUsed);


   text1->SetTextFont(42);
   text2->SetTextFont(42);
   text3->SetTextFont(42);
   text4->SetTextFont(42);
   text5->SetTextFont(42);
   text1->SetTextSize(0.05);
   text2->SetTextSize(0.05);
   text3->SetTextSize(0.05);
   text4->SetTextSize(0.05);
   text5->SetTextSize(0.05);
   TLatex *cmsprem = new TLatex(2800,20.2,"CMS #it{Preliminary} ");
   //TLatex *cmsprem = new TLatex(2.1,20.2,"#it{CMS Preliminary}");
   TLatex *Ecmsprem = new TLatex(2.265,5.7,"Region of efficiency > 95%");
   //TLatex *cmsprem = new TLatex(2.1,20.2,"CMS #it{Preliminary}");
   //cmsprem->SetTextFont(42);
   //cmsprem->SetTextSize(0.05);
   TLatex *gen = new TLatex(4235,20.2,"GE1/1");
   //gen->SetTextFont(42);
   //gen->SetTextSize(0.05);
//   cmsprem->SetTextSize(0.04);
   text1->Draw("same");
   text2->Draw("same");
   text3->Draw("same");
   text4->Draw("same");
   text5->Draw("same");
   text6->Draw("same");
   text7->Draw("same");
   cmsprem->Draw("same");
   Ecmsprem->Draw("same");
   gen->Draw("same");

   TPad *p = new TPad("p","p",0.,0.,1.,1.); p->SetFillStyle(0); p->Draw("same"); p->cd();
   TBox *b = new TBox(0.2,0.15,0.68,0.465);
   //b->SetFillColor(2);
   b->SetFillStyle(0);
   b->SetLineColor(2);
   b->SetLineWidth(2.);
   b->Draw("same");
//
////   CMS_lumi( c1, iPeriod, 0 );
//   

//   Float_t rightmax = 1.1*gr1->GetMaximum();

   //draw an axis on the right side
//   TGaxis *axis = new TGaxis(gPad->GetUxmin(),gPad->GetUymin(),
//	   gPad->GetUxmax(), gPad->GetUymax(),0,rightmax,510,"+L");
//   TGaxis *axis = new TGaxis(104,1.01,23211,1.01,3370,4252,15,"-");
//   cout<<"GetUxmax = "<<gPad->GetUxmin()<<"\tGetUymin = "<<gPad->GetUxmax()<<endl;
//   cout<<"GetUxmax = "<<gPad->GetUymin()<<"\tGetUymin = "<<gPad->GetUymax()<<endl;
//   axis->SetTitle("V_Drift (volts)");
// //  axis->SetTitleSize(2.5);
//  axis->SetTitleFont(42);
//  axis->SetTitleColor(1);
//  //axis->SetTitleFontSize(0.05);
//   axis->SetLineColor(kBlack);
//   axis->SetLabelColor(kBlack);
//   axis->Draw("sames");

   c1->Update();
   c1->SaveAs(pdfFile);
   c1->SaveAs(pngFile);
   //c1->SaveAs();

   c1->Write();
   f->Write();

}
