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
#include "setTDRStyle.C"
#include "CMS_lumi.C"
//#include ".h"

void GE11sEfficiencyPlots_3Sector_EGain()
{
   
   // Input Files 
   ifstream File1, File2, File3, File4;
   //File1.open("EfficiencyData_R306_R407_Lat21_GE11_IV_GIF.txt");
   //File2.open("EfficiencyData_R306_R407_Lat21_GE11_IV.txt");
   //File3.open("EfficiencyData_R306_R407_Lat22_GE11_V.txt");

    File1.open("EfficiencyData_R1592_R1646_Lat17_GE11_IV.txt");
    File2.open("SWAPHV_EfficiencyData_R2065_R2123_Lat17_GE11_IV.txt");
    File3.open("SWAP_EfficiencyData_R1868_R1906_Lat18_GE11_IV.txt");
    File4.open("EfficiencyData_R1313_R1397_Lat17_GE11_IV_GIF.txt");

   // Name of Detector
   //const char*  Detector1 = "#left(i#eta,i#phi#right)=#left(5,2#right)";
   //const char*  Detector2 = "#left(i#eta,i#phi#right)=#left(1,2#right)";
   //const char*  Detector3 = "#left(i#eta,i#phi#right)=#left(8,2#right)";
   const char*  Detector1 = "#left(i#eta,i#phi#right)=#left(5,2#right); #sigma_{eff} #times 4";
   const char*  Detector2 = "#left(i#eta,i#phi#right)=#left(1,2#right); #sigma_{eff} #times 4";
   const char*  Detector3 = "#left(i#eta,i#phi#right)=#left(8,2#right); #sigma_{eff} #times 4";
   const char*  Detector4 = "#left(i#eta,i#phi#right)=#left(5,2#right); #sigma_{eff} #times 4";
   //const char*  Detector1 = "#left(i#eta,i#phi#right)=#left(5,2#right); #sigma_{eff} #times 4; Ar/CO_{2}/CF_{4} #left(45/15/40#right)";
   //const char*  Detector2 = "#left(i#eta,i#phi#right)=#left(1,2#right); #sigma_{eff} #times 4; Ar/CO_{2}/CF_{4} #left(45/15/40#right)";
   //const char*  Detector3 = "#left(i#eta,i#phi#right)=#left(8,2#right); #sigma_{eff} #times 4; Ar/CO_{2}/CF_{4} #left(45/15/40#right)";
   //const char*  Detector4 = "#left(i#eta,i#phi#right)=#left(5,2#right); #sigma_{eff} #times 4; Ar/CO_{2} #left(70/30#right)";
   //const char*  Detector1 = "Latency 21: GE11_IV_GIF";
   //const char*  Detector2 = "Latency 21: GE11_IV";
   //const char*  Detector3 = "Latency 22: GE11_V";

   const char* RunRange = "Threshold = 1.2 fC";
   //const char* RunRange = "Threshold=15 VFAT units";
   const char* BeamType = "Beam: Muon";
   const char* MSPL = "";
   //const char* MSPL = "Gas: Ar/CO_{2}/CF_{4} #left(45/15/40#right)";
   const char* Threshold = "";
   //const char* Threshold = "Errors= Error*4.0";
   const char* GasUsed = "";
   const char* ClockMode = "";
   const char* EtaPhiSector = "";

   const char* CanvasName   = "Efficiency_Vs_EGain";
   const char* pdfFile	    = "EfficiencyPlot_wrt_EGain_wError4times_2gas_3sector.pdf";
   const char* pngFile	    = "EfficiencyPlot_wrt_EGain_wError4times_2gas_3sector.png";
   TFile *f = new   TFile(    "Efficiency_Vs_EGain.root","RECREATE");

   TGaxis::SetMaxDigits(3);
//   gStyle->SetOptFit(0000);
//   gStyle->SetOptStat(0);
   //TAxis::SetDecimals(1);

   //const char* GraphTitle = "Efficiency For Run Range 306 To 407: 2014H2B";
   const char* GraphTitle = "";


   // Set TDR Style
   setTDRStyle();
   gStyle->SetOptFit(0);

   writeExtraText = true;       // if extra text
   extraText  = "#italic{Preliminary}";  // default extra text is "Preliminary"
   int iPeriod = 0;    // 1=7TeV, 2=8TeV, 3=7+8TeV, 7=7+8+13TeV, 0=free form (uses lumi_sqrtS)

   TNtuple *NT_Detector1 = new TNtuple("EtaPhi52_ArCO2CF4","Efficiency Vs EGain","EGain:Efficiency:Efficiency Error");
   TNtuple *NT_Detector2 = new TNtuple("EtaPhi12_ArCO2CF4","Efficiency Vs EGain","EGain:Efficiency:Efficiency Error");
   TNtuple *NT_Detector3 = new TNtuple("EtaPhi82_ArCO2CF4","Efficiency Vs EGain","EGain:Efficiency:Efficiency Error");
   TNtuple *NT_Detector4 = new TNtuple("EtaPhi52_ArCO2"   ,"Efficiency Vs EGain","EGain:Efficiency:Efficiency Error");

   Int_t nlines = 0;

   vector<double> NT_Detector1_HV,NT_Detector1_Eff,NT_Detector1_EffErr,NT_Detector2_HV,NT_Detector2_Eff,NT_Detector2_EffErr,NT_Detector3_HV,NT_Detector3_Eff,NT_Detector3_EffErr, NT_Detector1_Gain, NT_Detector2_Gain, NT_Detector3_Gain, NT_Detector4_Gain, NT_Detector4_HV,NT_Detector4_Eff,NT_Detector4_EffErr;
   double current, eff, efferr;
   while (1) 
   {
     File1 >> current >> eff >> efferr;
     cout<<"1==> "<<current<<"\t"<<eff<<"\t"<<efferr<<endl;
	if (!File1.good()) break;

	NT_Detector1_Gain.push_back(exp(-16.0236+0.0318232*current));
	NT_Detector1_HV.push_back(current*0.546/0.006);
	//NT_Detector1_HV.push_back(current);
	NT_Detector1_Eff.push_back(eff);
        NT_Detector1_EffErr.push_back(efferr);

	NT_Detector1->Fill(current*0.546/6.0,eff,efferr);
	nlines++;
   }
   while (1) 
   {
     File2 >> current >> eff >> efferr;
     cout<<"2==> "<<current<<"\t"<<eff<<"\t"<<efferr<<endl;
	if (!File2.good()) break;

	NT_Detector2_Gain.push_back(exp(-16.0236+0.0318232*current));
	NT_Detector2_HV.push_back(current*0.546/0.006);
	//NT_Detector2_HV.push_back(current);
	NT_Detector2_Eff.push_back(eff);
        NT_Detector2_EffErr.push_back(efferr);

	NT_Detector2->Fill(current*0.546/6.0,eff,efferr);
	nlines++;
   }
   while (1) 
   {
     File3 >> current >> eff >> efferr;
     cout<<"3==> "<<current<<"\t"<<eff<<"\t"<<efferr<<endl;
	if (!File3.good()) break;

	NT_Detector3_Gain.push_back(exp(-16.0236+0.0318232*current));
	NT_Detector3_HV.push_back(current*0.546/0.006);
	//NT_Detector3_HV.push_back(current);
	NT_Detector3_Eff.push_back(eff);
        NT_Detector3_EffErr.push_back(efferr);

	NT_Detector3->Fill(current*0.546/6.0,eff,efferr);
	nlines++;
   }
   while (1) 
   {
     File4 >> current >> eff >> efferr;
     cout<<"4==> "<<current<<"\t"<<eff<<"\t"<<efferr<<endl;
	if (!File4.good()) break;

	NT_Detector4_Gain.push_back(exp(-16.0236+0.0318232*current));
	NT_Detector4_HV.push_back(current*0.546/0.006);
	//NT_Detector3_HV.push_back(current);
	NT_Detector4_Eff.push_back(eff);
        NT_Detector4_EffErr.push_back(efferr);

	NT_Detector4->Fill(current*0.546/6.0,eff,efferr);
	nlines++;
   }

   File1.close();
   File2.close();
   File3.close();
   File4.close();
   
   TCanvas* c1 = new TCanvas(CanvasName,"",1);
   //c1->SetLogx();
   TPad *pad = new TPad("pad","",0,0,1,1);
   //pad->SetFillColor(42);
   pad->SetGrid();
   pad->Draw();
   pad->cd();

   TF1 *f1 = new TF1("f1","[0]+(0.989)/([1]+exp(-[2]*(x-63.43)))",59,73);
   TF1 *f2 = new TF1("f2","(0.968)/([1]+exp(-[2]*(x-64.9)))",59,75);
   TF1 *f3 = new TF1("f3","(0.973)/([1]+exp(-[2]*(x-66  )))",59,75);
   TF1 *f4 = new TF1("f4","(0.985)/([1]+exp(-[2]*(x-55.8  )))",51,65);

//   f3->SetParameters(1.,1.,1.);
//   f3->SetParLimits(0,2,5);
//   f3->SetParLimits(1,0,20);
//   f3->SetParLimits(2,-10,0);

      // create first graph
   TGraphErrors *gr1 = new TGraphErrors(NT_Detector1_HV.size());
   for(unsigned int i=0;i<NT_Detector1_HV.size();i++)
   {
       gr1->SetPoint(i,NT_Detector1_HV[i]/1000.,NT_Detector1_Eff[i]);
       gr1->SetPointError(i,0,4*NT_Detector1_EffErr[i]);
   }
   gr1->SetMarkerColor(kGreen+3);
   gr1->SetLineColor(kGreen+3);
   gr1->SetMarkerStyle(21);
   gr1->GetXaxis()->SetTitle("E_{gain} (kV/cm)");
   //gr1->GetXaxis()->SetTitle("Effective Gain");
   gr1->GetYaxis()->SetTitle("Efficiency");
   gr1->SetTitle(GraphTitle);
   gr1->GetYaxis()->SetRangeUser(0,1.01);
   //gr1->GetXaxis()->SetLimits(104,23211);
   gr1->GetXaxis()->SetLimits(50,85);
   gr1->GetYaxis()->SetDecimals(1);
   f1->SetLineColor(kGreen+3);
   gr1->Fit("f1","ER");
   gr1->Draw("AP");
      // create first graph
   TGraphErrors *gr5 = new TGraphErrors(NT_Detector2_HV.size());
   for(unsigned int i=0;i<NT_Detector2_HV.size();i++)
   {
       gr5->SetPoint(i,NT_Detector2_HV[i]/1000.,NT_Detector2_Eff[i]);
       gr5->SetPointError(i,0,4*NT_Detector2_EffErr[i]);
   }
   gr5->SetMarkerColor(kBlack);
   gr5->SetLineColor(kBlack);
   gr5->SetMarkerStyle(22);
   gr5->GetXaxis()->SetTitle("Current Supplied To HV Divider (uA)");
   gr5->GetYaxis()->SetTitle("Efficiency");
   gr5->SetTitle(GraphTitle);
   //gr5->GetXaxis()->SetRangeUser(500,810);
   f2->SetLineColor(kBlack);
   gr5->Fit("f2","R");
   gr5->Draw("SameP");
      // create first graph
   TGraphErrors *gr8 = new TGraphErrors(NT_Detector3_HV.size());
   for(unsigned int i=0;i<NT_Detector3_HV.size();i++)
   {
       gr8->SetPoint(i,NT_Detector3_HV[i]/1000.,NT_Detector3_Eff[i]);
       gr8->SetPointError(i,0,4*NT_Detector3_EffErr[i]);
   }
   gr8->SetMarkerColor(kBlue);
   gr8->SetLineColor(kBlue);
   gr8->SetMarkerStyle(24);
   gr8->GetXaxis()->SetTitle("Current Supplied To HV Divider (uA)");
   gr8->GetYaxis()->SetTitle("Efficiency");
   gr8->SetTitle(GraphTitle);
   //gr8->GetXaxis()->SetRangeUser(500,810);
   f3->SetLineColor(kBlue);
   gr8->Fit("f3","R");
   gr8->Draw("SameP");
      // create first graph
   TGraphErrors *gr9 = new TGraphErrors(NT_Detector4_HV.size());
   for(unsigned int i=0;i<NT_Detector4_HV.size();i++)
   {
       gr9->SetPoint(i,NT_Detector4_HV[i]/1000.,NT_Detector4_Eff[i]);
       gr9->SetPointError(i,0,4*NT_Detector4_EffErr[i]);
   }
   gr9->SetMarkerColor(kMagenta+2);
   gr9->SetLineColor(kMagenta+2);
   gr9->SetMarkerStyle(20);
   gr9->GetXaxis()->SetTitle("Current Supplied To HV Divider (uA)");
   gr9->GetYaxis()->SetTitle("Efficiency");
   gr9->SetTitle(GraphTitle);
   //gr9->GetXaxis()->SetRangeUser(500,810);
   f4->SetLineColor(kMagenta+2);
   gr9->Fit("f4","R");
   gr9->Draw("SameP");
   //Draw the Legend 
   TLegend *leg = new TLegend(0.55,0.400,0.80,0.50);
   TLegend *leg2 = new TLegend(0.55,0.150,0.80,0.30);
   leg2->SetTextSize(0.05);
   leg2->SetTextFont(42);
   leg->SetTextSize(0.05);
   leg->SetTextFont(42);
   //leg->AddEntry(gr1,"(i#eta,i#phi)=(1,2)","LPE");
   //leg->AddEntry(gr5,"(i#eta,i#phi)=(5,2)","LPE");
   //leg->AddEntry(gr8,"(i#eta,i#phi)=(8.2)","LPE");
   leg->AddEntry(gr9,Detector4,"PE");
   leg2->AddEntry(gr5,Detector2,"PE");
   leg2->AddEntry(gr1,Detector1,"PE");
   leg2->AddEntry(gr8,Detector3,"PE");

   leg->Draw("same");
   leg2->Draw("same");

   TLatex *text1 = new TLatex(70,0.74,RunRange);
   TLatex *text2 = new TLatex(70,0.66,BeamType);
   TLatex *text5 = new TLatex(70,0.58,"Gap Config: 3/1/2/1 mm");
   TLatex *text3 = new TLatex(70,0.48,"Gas: Ar/CO2 (70/30)");
   TLatex *text4 = new TLatex(70,0.28,"Gas: Ar/CO2/CF4 (45/15/40)");
//   TLatex *text5 = new TLatex(81050,0.64,ClockMode);
   TLatex *text6 = new TLatex(3150,0.56,EtaPhiSector);
   TLatex *text7 = new TLatex(3250,0.48,GasUsed);
   text1->SetTextFont(42);
   text2->SetTextFont(42);
   text3->SetTextFont(42);
   text5->SetTextFont(42);
   //text3->SetTextAngle(50);
   //text4->SetTextAngle(50);
//   text3->SetTextColor(kMagenta);
   text4->SetTextFont(42);
   text1->SetTextSize(0.04);
   text2->SetTextSize(0.04);
   text3->SetTextSize(0.04);
   text4->SetTextSize(0.04);
   text5->SetTextSize(0.04);
   TLatex *cmsprem = new TLatex(50,1.015,"CMS");
   //TLatex *cmsprem = new TLatex(58.5,1.03,"#it{Preliminary}");
   //TLatex *cmsprem = new TLatex(58.5,1.03,"CMS #it{Preliminary}");
   TLatex *gen = new TLatex(81.2,1.015,"GE1/1");
//   cmsprem->SetTextFont(42);
//   cmsprem->SetTextSize(0.05);
//   gen->SetTextFont(42);
//   gen->SetTextSize(0.05);
//   cmsprem->SetTextSize(0.04);
   text1->Draw("same");
   text2->Draw("same");
   text3->Draw("same");
   text4->Draw("same");
   text5->Draw("same");
   text6->Draw("same");
   text7->Draw("same");
   cmsprem->Draw("same");
   gen->Draw("same");
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
