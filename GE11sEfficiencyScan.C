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

void GE11sEfficiencyScan()
{
   
   ifstream in;
   in.open("1375_ite2.txt");
   //in.open("1375_ite1.txt");

   TFile *f = new TFile("GE11sEfficiencyScan_1375_ite1.root","RECREATE");
   TNtuple *ntuple = new TNtuple("ntuple","data from ascii file","LC1:eff_LC1:eff_LC1_err:nevents");

   Int_t nlines = 0;

   vector<double> data_eff_LC1, data_eff_LC1_err, data_eff_LC2, data_eff_LC2_err, data_eff_LC3, data_eff_LC3_err;
   vector<unsigned int> data_LC1, data_nevents_LC1,data_nevents_LC2,data_nevents_LC3, data_LC2, data_LC3;
   unsigned int LC1, nevents_LC1,nevents_LC2,nevents_LC3;
   double eff_LC1, eff_LC1_err, eff_LC2, eff_LC2_err, eff_LC3, eff_LC3_err;
   while (1) 
   {
     in >> LC1 >> eff_LC1 >> eff_LC1_err >> eff_LC2 >> eff_LC2_err >> eff_LC3 >> eff_LC3_err >> nevents_LC1 >>  nevents_LC2 >> nevents_LC3;
	if (!in.good()) break;
	//if (nlines < 5) printf("LC1=%8i, y=%8f, z=%8f, t=%8i\n",LC1,eff_LC1,eff_LC1_err,nevents_LC1,nevents_LC2,nevents_LC3);

	data_LC1.push_back(LC1);
	data_eff_LC1.push_back(eff_LC1);
	data_eff_LC1_err.push_back(eff_LC1_err);
	data_eff_LC2.push_back(eff_LC2);
	data_eff_LC2_err.push_back(eff_LC2_err);
	data_eff_LC3.push_back(eff_LC3);
	data_eff_LC3_err.push_back(eff_LC3_err);
	data_nevents_LC1.push_back(nevents_LC1);
        data_nevents_LC2.push_back(nevents_LC2);
        data_nevents_LC3.push_back(nevents_LC3);
	ntuple->Fill(LC1,eff_LC1,eff_LC1_err,eff_LC2,eff_LC2_err,eff_LC3,eff_LC3_err,nevents_LC1,nevents_LC2,nevents_LC3);
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
   TH1F *hr = pad->DrawFrame(0,-0.5,100,1.1);
   hr->SetXTitle("Detector Position (mm)");
   hr->SetYTitle("Efficiency");
   //pad->GetFrame()->SetFillColor(21);
   pad->GetFrame()->SetBorderSize(12);

      // create first graph
   //gr1 = new TGraphErrors("data_error.dat","%lg %lg %lg");
   //TGraphErrors *gr1 = new TGraphErrors(data_LC1.size(),*data_LC1,*data_eff_LC1,*data_eff_LC1_err);   // Don't know why this is not working???
   TGraphErrors *gr1 = new TGraphErrors(data_LC1.size());
   TGraphErrors *gr3 = new TGraphErrors(data_LC1.size());
   TGraphErrors *gr4 = new TGraphErrors(data_LC1.size());
   cout<<"data size = "<<data_LC1.size()<<endl;
   for(unsigned int i=0;i<data_LC1.size();i++)
   {
       gr1->SetPoint(i,data_LC1[i],data_eff_LC1[i]);
       //gr1->SetPointError(i,0,data_eff_LC1_err[i]);

       gr3->SetPoint(i,data_LC1[i],data_eff_LC2[i]);
       //gr3->SetPointError(i,0,data_eff_LC2_err[i]);

       gr4->SetPoint(i,data_LC1[i],data_eff_LC3[i]);
       //gr4->SetPointError(i,0,data_eff_LC3_err[i]);
       /*
       gr1->SetPoint(i,data_LC1[i],data_eff_LC1[i]);
       gr1->SetPointError(i,0,data_eff_LC1_err[i]);

       gr3->SetPoint(i,data_LC1[i],data_eff_LC2[i]);
       gr3->SetPointError(i,0,data_eff_LC2_err[i]);

       gr4->SetPoint(i,data_LC1[i],data_eff_LC3[i]);
       gr4->SetPointError(i,0,data_eff_LC3_err[i]);
       */
   }
   gr1->SetMarkerColor(kBlue);
   gr1->SetLineColor(kBlue);
   gr1->SetMarkerStyle(21);
   gr1->GetXaxis()->SetTitle("dist (mm)");
   gr1->GetYaxis()->SetTitle("Efficiency");
   gr1->SetTitle("Efficiency Scan");
   gr1->Draw("ACP");
   gr3->SetMarkerColor(kGreen-6);
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
   TGraphErrors *gr2 = new TGraphErrors(data_LC1.size());
   TGraphErrors *gr5 = new TGraphErrors(data_LC1.size());
   TGraphErrors *gr6 = new TGraphErrors(data_LC1.size());

   for(unsigned int i=0;i<data_LC1.size();i++)
   {
       gr2->SetPoint(i,data_LC1[i],data_nevents_LC1[i]);
       gr5->SetPoint(i,data_LC1[i],data_nevents_LC2[i]);
       gr6->SetPoint(i,data_LC1[i],data_nevents_LC3[i]);

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

   Double_t xmin = pad->GetUxmin();
   Double_t ymin = 0;
   Double_t xmax = pad->GetUxmax();
   Double_t ymax = 1050;
   TH1F *hframe = overlay->DrawFrame(xmin,ymin,xmax,ymax);
   hframe->GetXaxis()->SetLabelOffset(99);
   hframe->GetYaxis()->SetLabelOffset(99);
   gr2->Draw("CP");
   gr5->Draw("CP");
   gr6->Draw("CP");

   //Draw the Legend 
   TLegend *leg = new TLegend(0.46,0.332,0.76,0.63);
   leg->AddEntry(gr1,"GE11_IV eff","LPE");
   leg->AddEntry(gr3,"GE11_IV_GIF eff","LPE");
   leg->AddEntry(gr4,"GE11_V eff","LPE");
   leg->AddEntry(gr2,"No of events_GE11_IV","LPE");
   leg->AddEntry(gr5,"No of events_GE11_IV_GIF","LPE");
   leg->AddEntry(gr6,"No of events_GE11_V","LPE");

   leg->Draw("same");

   TLatex *t2a = new TLatex(0.15,0.94," Run 308 Ite 1"  );
   t2a->SetNDC();
   t2a->SetTextFont(42);
   t2a->SetTextSize(0.033);
   t2a->SetTextAlign(13);
   t2a->Draw("same");
   
   
   //Draw an axis on the right side
   TGaxis *axis = new TGaxis(xmax,ymin,xmax, ymax,ymin,ymax,510,"+L");
   axis->SetLineColor(kRed);
   axis->SetLabelColor(kRed);
   axis->SetTitle("Approx. No. of Events");

   axis->Draw();

   c1->SaveAs("GE11_Efficiency_Scan_1375_ite1.pdf");
   c1->SaveAs("GE11_Efficiency_Scan_1375_ite1.png");

   c1->Write();
   f->Write();

}
