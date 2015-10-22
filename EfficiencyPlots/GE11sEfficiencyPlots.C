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

void GE11sEfficiencyPlots()
{
   
   // Input Files 
   ifstream File1, File2, File3;
   File1.open("EfficiencyData_R1592_R1646_Lat16_GE11_IV_GIF.txt");
   File2.open("EfficiencyData_R1592_R1646_Lat17_GE11_IV_GIF.txt");
   File3.open("EfficiencyData_R1592_R1646_Lat17_GE11_IV.txt");

   // Name of Detector
   const char*  Detector1 = "Latency 16: GE11_IV_GIF";
   const char*  Detector2 = "Latency 17: GE11_IV_GIF";
   const char*  Detector3 = "Latency 17: GE11_IV";

   const char* RunRange = "Runs 1592-1646";
   const char* BeamType = "Beam: Muon";
   const char* MSPL = "MSPL 4";
   const char* Threshold = "Threshold=15 VFAT units";
   const char* ClockMode = "Async Mode";
   const char* EtaPhiSector = "(i#eta,i#phi)=(5,2)";

   const char* CanvasName   = "Efficiency_R1592_R1646";
   const char* pdfFile	    = "Efficiency_R1592_R1646.pdf";
   TFile *f = new   TFile(    "Efficiency_R1592_R1646.root","RECREATE");

   //const char* GraphTitle = "Efficiency For Run Range 306 To 407: 2014H2B";
   const char* GraphTitle = "";


   // Set TDR Style
   setTDRStyle();

   writeExtraText = true;       // if extra text
   extraText  = "Preliminary";  // default extra text is "Preliminary"
   int iPeriod = 0;    // 1=7TeV, 2=8TeV, 3=7+8TeV, 7=7+8+13TeV, 0=free form (uses lumi_sqrtS)

   TNtuple *NT_Detector1 = new TNtuple(Detector1,"data from text file","NT_Detector1_CurrentToHVDivider:NT_Detector1_Eff:NT_Detector1_EffErr");
   TNtuple *NT_Detector2 = new TNtuple(Detector2,"data from text file","NT_Detector2_CurrentToHVDivider:NT_Detector2_Eff:NT_Detector2_EffErr");
   TNtuple *NT_Detector3 = new TNtuple(Detector3,"data from text file","NT_Detector3_CurrentToHVDivider:NT_Detector3_Eff:NT_Detector3_EffErr");

   Int_t nlines = 0;

   vector<double> NT_Detector1_HV,NT_Detector1_Eff,NT_Detector1_EffErr,NT_Detector2_HV,NT_Detector2_Eff,NT_Detector2_EffErr,NT_Detector3_HV,NT_Detector3_Eff,NT_Detector3_EffErr;
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
   while (1) 
   {
     File2 >> current >> eff >> efferr;
     cout<<"==> "<<current<<"\t"<<eff<<"\t"<<efferr<<endl;
	if (!File2.good()) break;

	NT_Detector2_HV.push_back(current);
	NT_Detector2_Eff.push_back(eff);
        NT_Detector2_EffErr.push_back(efferr);

	NT_Detector2->Fill(current,eff,efferr);
	nlines++;
   }
   while (1) 
   {
     File3 >> current >> eff >> efferr;
     cout<<"==> "<<current<<"\t"<<eff<<"\t"<<efferr<<endl;
	if (!File3.good()) break;

	NT_Detector3_HV.push_back(current);
	NT_Detector3_Eff.push_back(eff);
        NT_Detector3_EffErr.push_back(efferr);

	NT_Detector3->Fill(current,eff,efferr);
	nlines++;
   }

   File1.close();
   File2.close();
   File3.close();
   
   TCanvas* c1 = new TCanvas(CanvasName,"",200,10,700,500);
   TPad *pad = new TPad("pad","",0,0,1,1);
   //pad->SetFillColor(42);
   pad->SetGrid();
   pad->Draw();
   pad->cd();

      // create first graph
   TGraphErrors *gr1 = new TGraphErrors(NT_Detector1_HV.size());
   for(unsigned int i=0;i<NT_Detector1_HV.size();i++)
   {
       gr1->SetPoint(i,NT_Detector1_HV[i],NT_Detector1_Eff[i]);
       gr1->SetPointError(i,0,NT_Detector1_EffErr[i]);
   }
   gr1->SetMarkerColor(kBlue);
   gr1->SetLineColor(kBlue);
   gr1->SetMarkerStyle(21);
   gr1->GetXaxis()->SetTitle("Current Supplied To HV Divider (uA)");
   gr1->GetYaxis()->SetTitle("Efficiency");
   gr1->SetTitle(GraphTitle);
   gr1->GetXaxis()->SetRangeUser(500,810);
   gr1->Draw("ACP");
      // create first graph
   TGraphErrors *gr5 = new TGraphErrors(NT_Detector2_HV.size());
   for(unsigned int i=0;i<NT_Detector2_HV.size();i++)
   {
       gr5->SetPoint(i,NT_Detector2_HV[i],NT_Detector2_Eff[i]);
       gr5->SetPointError(i,0,NT_Detector2_EffErr[i]);
   }
   gr5->SetMarkerColor(kRed);
   gr5->SetLineColor(kRed);
   gr5->SetMarkerStyle(21);
   gr5->GetXaxis()->SetTitle("Current Supplied To HV Divider (uA)");
   gr5->GetYaxis()->SetTitle("Efficiency");
   gr5->SetTitle(GraphTitle);
   gr5->GetXaxis()->SetRangeUser(500,810);
   gr5->Draw("SameCP");
      // create first graph
   TGraphErrors *gr8 = new TGraphErrors(NT_Detector3_HV.size());
   for(unsigned int i=0;i<NT_Detector3_HV.size();i++)
   {
       gr8->SetPoint(i,NT_Detector3_HV[i],NT_Detector3_Eff[i]);
       gr8->SetPointError(i,0,NT_Detector3_EffErr[i]);
   }
   gr8->SetMarkerColor(kGreen);
   gr8->SetLineColor(kGreen);
   gr8->SetMarkerStyle(21);
   gr8->GetXaxis()->SetTitle("Current Supplied To HV Divider (uA)");
   gr8->GetYaxis()->SetTitle("Efficiency");
   gr8->SetTitle(GraphTitle);
   gr8->GetXaxis()->SetRangeUser(500,810);
   gr8->Draw("SameCP");
   //Draw the Legend 
   TLegend *leg = new TLegend(0.65,0.150,0.94,0.38);
   //leg->AddEntry(gr1,"(i#eta,i#phi)=(1,2)","LPE");
   //leg->AddEntry(gr5,"(i#eta,i#phi)=(5,2)","LPE");
   //leg->AddEntry(gr8,"(i#eta,i#phi)=(8.2)","LPE");
   leg->AddEntry(gr1,Detector1,"LPE");
   leg->AddEntry(gr5,Detector2,"LPE");
   leg->AddEntry(gr8,Detector3,"LPE");

   leg->Draw("same");

   TLatex *text1 = new TLatex(560,0.95,RunRange);
   TLatex *text2 = new TLatex(560,0.88,BeamType);
   TLatex *text3 = new TLatex(560,0.80,MSPL);
   TLatex *text4 = new TLatex(560,0.72,Threshold);
   TLatex *text5 = new TLatex(560,0.64,ClockMode);
   TLatex *text6 = new TLatex(560,0.56,EtaPhiSector);
   //TLatex *text4 = new TLatex(540,0.72,ClockMode);
   text1->Draw("same");
   text2->Draw("same");
   text3->Draw("same");
   text4->Draw("same");
   text5->Draw("same");
   text6->Draw("same");

   CMS_lumi( c1, iPeriod, 0 );
   

   c1->SaveAs(pdfFile);
   //c1->SaveAs();

   c1->Write();
   f->Write();

}
