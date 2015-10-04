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


// Modigy GE11_IV_GIF => Detector Sector
void bigraph()
{
   
   ifstream in;
   in.open("data2.dat");

   TFile *f = new TFile("bigraph","RECREATE");
   TNtuple *ntuple = new TNtuple("ntuple","data from ascii file","Sector:eff_GE11_IV_GIF:eff_GE11_IV:eff_GE11_V:nevents_GE11_IV_GIF:nevents_GE11_IV:nevents_GE11_V");

   Int_t nlines = 0;

   vector<int> data_eff_GE11_IV_GIF, data_eff_GE11_IV, data_eff_GE11_V;
   vector<double> data_GE11_IV_GIF, data_nevents_GE11_IV_GIF,data_nevents_GE11_IV,data_nevents_GE11_V, data_GE11_IV, data_GE11_V;
   double GE11_IV_GIF, nevents_GE11_IV_GIF,nevents_GE11_IV,nevents_GE11_V;
   int eff_GE11_IV_GIF, eff_GE11_IV, eff_GE11_V;
   while (1) 
   {
     in >> GE11_IV_GIF >> eff_GE11_IV_GIF >> eff_GE11_IV  >> eff_GE11_V  >> nevents_GE11_IV_GIF >>  nevents_GE11_IV >> nevents_GE11_V;
	if (!in.good()) break;
	printf("GE11_IV_GIF=%3f, %8i, %8i, %8i, %8f, %8f, %8f \n",GE11_IV_GIF,eff_GE11_IV_GIF,eff_GE11_IV  ,eff_GE11_V  , nevents_GE11_IV_GIF ,  nevents_GE11_IV ,nevents_GE11_V);

	data_GE11_IV_GIF.push_back(GE11_IV_GIF);
	data_eff_GE11_IV_GIF.push_back(eff_GE11_IV_GIF);
	//data_eff_GE11_IV_GIF_err.push_back(eff_GE11_IV_GIF_err);
	data_eff_GE11_IV.push_back(eff_GE11_IV);
	//data_eff_GE11_IV_err.push_back(eff_GE11_IV_err);
	data_eff_GE11_V.push_back(eff_GE11_V);
	//data_eff_GE11_V_err.push_back(eff_GE11_V_err);
	data_nevents_GE11_IV_GIF.push_back(nevents_GE11_IV_GIF);
        data_nevents_GE11_IV.push_back(nevents_GE11_IV);
        data_nevents_GE11_V.push_back(nevents_GE11_V);

	ntuple->Fill(GE11_IV_GIF,eff_GE11_IV_GIF,eff_GE11_IV,eff_GE11_V,nevents_GE11_IV_GIF,nevents_GE11_IV,nevents_GE11_V);
	nlines++;
   }

   in.close();
   
   TCanvas* c1 = new TCanvas("c1","gerrors2",200,10,700,500);
   TPad *pad = new TPad("pad","",0,0,1,1);
   //pad->SetFillColor(42);
   pad->SetGrid();
   pad->Draw();
   pad->cd();

      // draw a frame to define the range
   TH1F *hr = pad->DrawFrame(9.6,0,11.2,100);
   hr->SetXTitle("Voltage (kV)");
   hr->GetXaxis()->CenterTitle();
   hr->GetYaxis()->CenterTitle();
   hr->SetYTitle("Efficiency (%)");
   //pad->GetFrame()->SetFillColor(21);
   pad->GetFrame()->SetBorderSize(16);

      // create first graph
   //gr1 = new TGraphErrors("data_error.dat","%lg %lg %lg");
   //TGraphErrors *gr1 = new TGraphErrors(data_GE11_IV_GIF.size(),*data_GE11_IV_GIF,*data_eff_GE11_IV_GIF,*data_eff_GE11_IV_GIF_err);   // Don't know why this is not working???
   TGraphErrors *gr1 = new TGraphErrors(data_GE11_IV_GIF.size());
   TGraphErrors *gr3 = new TGraphErrors(data_GE11_IV_GIF.size());
   TGraphErrors *gr4 = new TGraphErrors(data_GE11_IV_GIF.size());
   cout<<"data size = "<<data_GE11_IV_GIF.size()<<endl;
   for(unsigned int i=0;i<data_GE11_IV_GIF.size();i++)
   {
       gr1->SetPoint(i,data_GE11_IV_GIF[i],data_eff_GE11_IV_GIF[i]);
       //gr1->SetPointError(i,0,data_eff_GE11_IV_GIF_err[i]);

       gr3->SetPoint(i,data_GE11_IV_GIF[i],data_eff_GE11_IV[i]);
       //gr3->SetPointError(i,0,data_eff_GE11_IV_err[i]);

       gr4->SetPoint(i,data_GE11_IV_GIF[i],data_eff_GE11_V[i]);
       //gr4->SetPointError(i,0,data_eff_GE11_V_err[i]);
   }
   gr1->SetMarkerColor(kBlue);
   gr1->SetLineColor(kBlue);
   gr1->SetMarkerStyle(21);
   
   gr1->GetXaxis()->SetTitle("(Voltage (kV))");
  
   gr1->GetYaxis()->SetTitle("Efficiency (%)");
  // gr1->SetTitle("Efficiency Scan For Run No. 1375");
   gr1->Draw("CP");
   gr3->SetMarkerColor(kGreen);
   gr3->SetLineColor(kGreen);
   gr3->SetMarkerStyle(21);
   gr3->Draw("sameCP");
   gr4->SetMarkerColor(kBlack);
   gr4->SetLineColor(kBlack);
   gr4->SetMarkerStyle(21);
   gr4->Draw("sameCP");

   //create a transparent pad drawn on top of the main pad
   c1->cd();
   TPad *overlay = new TPad("overlay","",0,0,1,1);
   overlay->SetFillStyle(4000);
   overlay->SetFillColor(0);
   overlay->SetFrameFillStyle(4000);
   overlay->Draw();
   overlay->cd();
   // create second graph
   //TGraphErrors* gr2 = new TGraphErrors("data_noerror.dat","%lg %lg");
   TGraphErrors *gr2 = new TGraphErrors(data_GE11_IV_GIF.size());
   TGraphErrors *gr5 = new TGraphErrors(data_GE11_IV_GIF.size());
   TGraphErrors *gr6 = new TGraphErrors(data_GE11_IV_GIF.size());

   for(unsigned int i=0;i<data_GE11_IV_GIF.size();i++)
   {
       gr2->SetPoint(i,data_GE11_IV_GIF[i],data_nevents_GE11_IV_GIF[i]);
       gr5->SetPoint(i,data_GE11_IV_GIF[i],data_nevents_GE11_IV[i]);
       gr6->SetPoint(i,data_GE11_IV_GIF[i],data_nevents_GE11_V[i]);

   }
   gr2->SetMarkerColor(kBlue);
   gr2->SetLineColor(kBlue);
   gr2->SetLineStyle(2);
   gr2->SetLineWidth(3);
   gr2->SetMarkerStyle(22);
   gr2->SetName("gr2");

   gr5->SetMarkerColor(kGreen-6);
   gr5->SetLineColor(kGreen);
   gr5->SetMarkerStyle(22);
   gr5->SetLineStyle(2);
   gr5->SetLineWidth(3);
   gr5->SetName("gr5");

   gr6->SetMarkerColor(kBlack);
   gr6->SetLineColor(kBlack);
   gr6->SetMarkerStyle(22);
   gr6->SetLineStyle(2);
   gr6->SetLineWidth(3);
   gr6->SetName("gr6");
//set range for another y axis
   Double_t xmin = pad->GetUxmin();
   Double_t ymin = 0;
   Double_t xmax = pad->GetUxmax();
   Double_t ymax = 2;
cout<<"xmin = "<<xmin<<"\tymin = "<<ymin<<"\txmax = "<<xmax<<"\tymax = "<<ymax<<endl;
   TH1F *hframe = overlay->DrawFrame(xmin,ymin,xmax,ymax);
hframe->Draw("Y+");
hframe->GetYaxis()->CenterTitle();
hframe->GetYaxis()->SetTitle("Charge(pC)");

// TH1F *hframe = overlay->DrawFrame(0,0,0,0);
   //hframe->GetXaxis()->SetLabelOffset(99);
   //hframe->GetYaxis()->SetLabelOffset(99);
   gr2->Draw("CPY+");
  gr5->Draw("CPY+");
   gr6->Draw("CPY+");

   //Draw the Legend 
   TLegend *leg = new TLegend(0.46,0.132,0.76,0.43);
   leg->AddEntry(gr1,"R134a (95.0%), C4 H10 (4%), SF6 (1%).
","l");
   leg->AddEntry(gr3,"R134a (95.0%), C4 H10 (4.5%), SF6 (0.5%).
","l");
   leg->AddEntry(gr4,"R134a (95.0%), C4 H10 (9%), SF6 (1%).
","l");
   leg->AddEntry(gr2,"charge(R134a (95.0%), C4 H10 (4%), SF6 (1%).
","l");
   leg->AddEntry(gr5,"charge(R134a (95.0%), C4 H10 (4.5%), SF6 (0.5%).
","l");
   leg->AddEntry(gr6,"charge(R134a (90.0%), C4 H10 (9%), SF6 (1%).
","l");

   leg->Draw("same");
   
   
   //Draw an axis on the right side
   TGaxis *axis = new TGaxis(/*xmax,ymin,xmax, ymax,ymin,ymax,510,"+L"*/);
   axis->SetLineColor(kRed);
   axis->SetLabelColor(kRed);
 
   axis->SetTitle("Charge(pC)");

  //axis->Draw();

   c1->SaveAs("GE11_Efficiency_Scan.pdf");
   c1->Write();
   f->Write();

}
