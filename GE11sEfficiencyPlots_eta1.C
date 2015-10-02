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
#include <vector>
#include "TCanvas.h"
#include "TPad.h"
#include "TH1F.h"
#include "TGraphErrors.h"
#include "TGaxis.h"
#include "TFrame.h"
#include "TLegend.h"
//#include ".h"

void GE11sEfficiencyPlots_eta1()
{
   
   ifstream eta1, eta5, eta8;
   eta1.open("EfficiencyTxtFile_Eta8_GE11-IV-GIF.dat");
   eta5.open("EfficiencyTxtFile_Eta8_GE11-IV.dat");
   eta8.open("EfficiencyTxtFile_Eta8_GE11-IV-GIF.dat");
   //eta1.open("1375_ite1.txt");

   TFile *f = new TFile("GE11sEfficiencyData","RECREATE");
   TNtuple *GE11_IV_Eta1 = new TNtuple("GE11_IV_Eta1","data from ascii file","GE11_IV_Eta1_HV:GE11_IV_Eta1_Eff:GE11_IV_Eta1_EffErr");
   TNtuple *GE11_IV_Eta5 = new TNtuple("GE11_IV_Eta5","data from ascii file","GE11_IV_Eta5_HV:GE11_IV_Eta5_Eff:GE11_IV_Eta5_EffErr");
   TNtuple *GE11_IV_Eta8 = new TNtuple("GE11_IV_Eta8","data from ascii file","GE11_IV_Eta8_HV:GE11_IV_Eta8_Eff:GE11_IV_Eta8_EffErr");

   Int_t nlines = 0;

   vector<double> GE11_IV_Eta1_HV,GE11_IV_Eta1_Eff,GE11_IV_Eta1_EffErr,GE11_IV_Eta5_HV,GE11_IV_Eta5_Eff,GE11_IV_Eta5_EffErr,GE11_IV_Eta8_HV,GE11_IV_Eta8_Eff,GE11_IV_Eta8_EffErr;
   double current, eff, efferr;
   while (1) 
   {
     eta1 >> current >> eff >> efferr;
     cout<<"==> "<<current<<"\t"<<eff<<"\t"<<efferr<<endl;
	if (!eta1.good()) break;

	GE11_IV_Eta1_HV.push_back(current);
	GE11_IV_Eta1_Eff.push_back(eff);
        GE11_IV_Eta1_EffErr.push_back(efferr);

	GE11_IV_Eta1->Fill(current,eff,efferr);
	nlines++;
   }
   while (1) 
   {
     eta5 >> current >> eff >> efferr;
     cout<<"==> "<<current<<"\t"<<eff<<"\t"<<efferr<<endl;
	if (!eta5.good()) break;

	GE11_IV_Eta5_HV.push_back(current);
	GE11_IV_Eta5_Eff.push_back(eff);
        GE11_IV_Eta5_EffErr.push_back(efferr);

	GE11_IV_Eta5->Fill(current,eff,efferr);
	nlines++;
   }
   while (1) 
   {
     eta8 >> current >> eff >> efferr;
     cout<<"==> "<<current<<"\t"<<eff<<"\t"<<efferr<<endl;
	if (!eta8.good()) break;

	GE11_IV_Eta8_HV.push_back(current);
	GE11_IV_Eta8_Eff.push_back(eff);
        GE11_IV_Eta8_EffErr.push_back(efferr);

	GE11_IV_Eta8->Fill(current,eff,efferr);
	nlines++;
   }

   eta1.close();
   eta5.close();
   eta8.close();
   
   TCanvas* c1 = new TCanvas("c1","gerrors2",200,10,700,500);
   TPad *pad = new TPad("pad","",0,0,1,1);
   //pad->SetFillColor(42);
   pad->SetGrid();
   pad->Draw();
   pad->cd();

      // create first graph
   TGraphErrors *gr1 = new TGraphErrors(GE11_IV_Eta1_HV.size());
   for(unsigned int i=0;i<GE11_IV_Eta1_HV.size();i++)
   {
       gr1->SetPoint(i,GE11_IV_Eta1_HV[i],GE11_IV_Eta1_Eff[i]);
       gr1->SetPointError(i,0,GE11_IV_Eta1_EffErr[i]);
   }
   gr1->SetMarkerColor(kBlue);
   gr1->SetLineColor(kBlue);
   gr1->SetMarkerStyle(21);
   gr1->GetXaxis()->SetTitle("Current Supplied To HV Divider (uA)");
   gr1->GetYaxis()->SetTitle("Efficiency");
   //gr1->SetTitle("Efficiency for GE1/1-IV-GIF");
   gr1->Draw("ACP");
      // create first graph
   TGraphErrors *gr5 = new TGraphErrors(GE11_IV_Eta5_HV.size());
   for(unsigned int i=0;i<GE11_IV_Eta5_HV.size();i++)
   {
       gr5->SetPoint(i,GE11_IV_Eta5_HV[i],GE11_IV_Eta5_Eff[i]);
       gr5->SetPointError(i,0,GE11_IV_Eta5_EffErr[i]);
   }
   gr5->SetMarkerColor(kRed);
   gr5->SetLineColor(kRed);
   gr5->SetMarkerStyle(21);
   gr5->GetXaxis()->SetTitle("Current Supplied To HV Divider (uA)");
   gr5->GetYaxis()->SetTitle("Efficiency");
   //gr5->SetTitle("Efficiency for GE1/1-IV");
   gr5->Draw("SameCP");
      // create first graph
   TGraphErrors *gr8 = new TGraphErrors(GE11_IV_Eta8_HV.size());
   for(unsigned int i=0;i<GE11_IV_Eta8_HV.size();i++)
   {
       gr8->SetPoint(i,GE11_IV_Eta8_HV[i],GE11_IV_Eta8_Eff[i]);
       gr8->SetPointError(i,0,GE11_IV_Eta8_EffErr[i]);
   }
   gr8->SetMarkerColor(kGreen);
   gr8->SetLineColor(kGreen);
   gr8->SetMarkerStyle(21);
   gr8->GetXaxis()->SetTitle("Current Supplied To HV Divider (uA)");
   gr8->GetYaxis()->SetTitle("Efficiency");
   //gr8->SetTitle("Efficiency for GE1/1-IV");
   //gr8->Draw("SameCP");
   //Draw the Legend 
   TLegend *leg = new TLegend(0.46,0.332,0.76,0.63);
   leg->AddEntry(gr1,"GE1/1-IV-GIF, (i#eta,i#phi)=(8,2)","LPE");
   leg->AddEntry(gr5,"GE1/1-IV, (i#eta,i#phi)=(8,2)","LPE");
   //leg->AddEntry(gr8,"(i#eta,i#phi)=(8.2)","LPE");

   leg->Draw("same");
   
   
   c1->SaveAs("GE11_Efficiency_Scan_1375_ite1.pdf");
   c1->SaveAs("GE11_Efficiency_Scan_1375_ite1.png");

   c1->Write();
   f->Write();

}
