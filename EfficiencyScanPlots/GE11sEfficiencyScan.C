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
 *
 *  BUG: 
 *	1. X-axis of the two y-axis does not match.
 *
 *  Things to implement:
 *	1. Put the Ntuples in a directory named according to run Number
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
#include "setTDRStyle.C"


void GE11sEfficiencyScan(int RunNumber, string RunName, string path)
{
setTDRStyle();

   ifstream InGE11_IV_GIF, InGE11_IV, InGE11_V;

   //string path = "/home/ramkrishna/TEMP/LogFiles_TB/LogFiles306To407";	    

   string gif	= path+"/Efficiency_LC1_"+std::to_string(RunNumber)+".log";
   string IV	= path+"/Efficiency_LC2_"+std::to_string(RunNumber)+".log";
   string V	= path+"/Efficiency_LC3_"+std::to_string(RunNumber)+".log";

   cout<<"gif = "<<gif<<endl;
   InGE11_IV_GIF.open(gif);
   InGE11_IV.open(IV);
   InGE11_V.open(V);

   string rootFile = "Efficiency_Run"+std::to_string(RunNumber)+".root";
   const char *CharrootFile = rootFile.c_str();
   TFile *f = new TFile(CharrootFile,"RECREATE");
   //TTree *tree = new TTree("Run306", "Detector info for Run 306");
   TNtuple *GE11_IV_GIF = new TNtuple("GE11_IV_GIF","data from text file LC1","MeanPosOfSector:Efficiency:EfficiencyError:Nevents");
   TNtuple *GE11_IV = new TNtuple("GE11_IV","data from text file LC2","MeanPosOfSector:Efficiency:EfficiencyError:Nevents");
   TNtuple *GE11_V = new TNtuple("GE11_V","data from text file LC3","MeanPosOfSector:Efficiency:EfficiencyError:Nevents");

   Int_t nlines = 0;

   vector<double> GIF_MeanPosOfSector, GIF_Efficiency, GIF_EfficiencyError;
   vector<unsigned int> GIF_Nevents;
   unsigned int temp_Nevents;
   double temp_MeanPosOfSector, temp_Efficiency, temp_EfficiencyError;

   vector<double> IV_MeanPosOfSector, IV_Efficiency, IV_EfficiencyError;
   vector<unsigned int> IV_Nevents;

   vector<double> V_MeanPosOfSector, V_Efficiency, V_EfficiencyError;
   vector<unsigned int> V_Nevents;

   string NameOfDet, xRange;

   while (1) 
   {
     InGE11_IV_GIF >> NameOfDet >> xRange >> temp_MeanPosOfSector >> temp_Efficiency >> temp_EfficiencyError >> temp_Nevents;
	if (!InGE11_IV_GIF.good()) break;

     GIF_MeanPosOfSector.push_back(temp_MeanPosOfSector/*+(nlines*5)*/);
     GIF_Efficiency.push_back(temp_Efficiency);
     GIF_EfficiencyError.push_back(temp_EfficiencyError);
     GIF_Nevents.push_back(temp_Nevents);
    	GE11_IV_GIF->Fill(temp_MeanPosOfSector/*+(nlines*5)*/,temp_Efficiency,temp_EfficiencyError,temp_Nevents);
	nlines++;
	if (nlines > 20) 
	{
	    cout<<"Check the input text file for run number "<< RunNumber << endl;
	    exit(EXIT_SUCCESS);
	}
   }

   InGE11_IV_GIF.close();
   nlines=0;
   while (1) 
   {
     InGE11_IV >> NameOfDet >> xRange >> temp_MeanPosOfSector >> temp_Efficiency >> temp_EfficiencyError >> temp_Nevents;
	if (!InGE11_IV.good()) break;

     IV_MeanPosOfSector.push_back(temp_MeanPosOfSector+(nlines*5));
     IV_Efficiency.push_back(temp_Efficiency);
     IV_EfficiencyError.push_back(temp_EfficiencyError);
     IV_Nevents.push_back(temp_Nevents);
    	GE11_IV->Fill(temp_MeanPosOfSector/*+(nlines*5)*/,temp_Efficiency,temp_EfficiencyError,temp_Nevents);
	nlines++;
   }

   InGE11_IV.close();
   nlines=0;
   while (1) 
   {
     InGE11_V >> NameOfDet >> xRange >> temp_MeanPosOfSector >> temp_Efficiency >> temp_EfficiencyError >> temp_Nevents;
	if (!InGE11_V.good()) break;

     V_MeanPosOfSector.push_back(temp_MeanPosOfSector+(nlines*5));
     V_Efficiency.push_back(temp_Efficiency);
     V_EfficiencyError.push_back(temp_EfficiencyError);
     V_Nevents.push_back(temp_Nevents);
    	GE11_V->Fill(temp_MeanPosOfSector/*+(nlines*5)*/,temp_Efficiency,temp_EfficiencyError,temp_Nevents);
	nlines++;
   }

   InGE11_V.close();
   string CanvasName = "RunNumber"+std::to_string(RunNumber);
   const char * CharCanvasName = CanvasName.c_str();
   TCanvas* c1 = new TCanvas(CharCanvasName,"Efficiency Scan Plot",200,10,700,500);
   TPad *pad = new TPad("pad","",0,0,1,1);
   //pad->SetFillColor(42);
   pad->SetGrid();
   pad->Draw();
   pad->cd();

      // draw a frame to define the range
   TH1F *hr = pad->DrawFrame(0,0.0,100,1.1);
   hr->SetXTitle("Detector Position (mm)");
   hr->SetYTitle("Efficiency");
   //pad->GetFrame()->SetFillColor(21);
   pad->GetFrame()->SetBorderSize(12);

      // create first graph
   TGraphErrors *gr_GIF = new TGraphErrors(V_Efficiency.size());
   TGraphErrors *gr_IV = new TGraphErrors(V_Efficiency.size());
   TGraphErrors *gr_V = new TGraphErrors(V_Efficiency.size());
   for(unsigned int i=0;i<V_Efficiency.size();i++)
   {
       gr_GIF->SetPoint(i, GIF_MeanPosOfSector[i], GIF_Efficiency[i]);
       gr_GIF->SetPointError(i,0, GIF_EfficiencyError[i]);
       
       gr_IV->SetPoint(i, IV_MeanPosOfSector[i], IV_Efficiency[i]);
       gr_IV->SetPointError(i,0, IV_EfficiencyError[i]);

       gr_V->SetPoint(i, V_MeanPosOfSector[i], V_Efficiency[i]);
       gr_V->SetPointError(i,0, V_EfficiencyError[i]);
   }
   gr_GIF->SetMarkerColor(kBlack);
   gr_GIF->SetLineColor(kBlack);
   gr_GIF->SetMarkerStyle(23);
   gr_GIF->GetXaxis()->SetTitle("dist (mm)");
   gr_GIF->GetYaxis()->SetTitle("Efficiency");
   gr_GIF->GetYaxis()->SetRangeUser(0,1.1);
   gr_GIF->SetTitle("Efficiency Scan");
//   gr_GIF->Draw("AP");
   gr_IV->GetYaxis()->SetTitle("Efficiency");
   gr_IV->GetXaxis()->SetTitle("Position (mm) of selected patch of 5mm");
   //gr_IV->GetXaxis()->SetTitle("Distance (mm) of selected patch of 5mm in #left(i#eta, i#phi#right) = #left(5,2#right) sector");
   gr_IV->SetMarkerColor(kBlack);
   gr_IV->SetLineColor(kBlack);
   gr_IV->SetMarkerStyle(22);
   gr_IV->GetYaxis()->SetRangeUser(0,1.1);
   gr_IV->GetXaxis()->SetLimits(0,100);
   gr_IV->GetYaxis()->SetDecimals(1);
   gr_IV->GetYaxis()->SetTickLength(0.0);
   gr_IV->SetTitle("");
   gr_IV->Draw("AP");
//   gr_IV->Draw("sameP");
   gr_V->SetMarkerColor(kBlack);
   gr_V->SetLineColor(kBlack);
   gr_V->SetMarkerStyle(21);
//   gr_V->Draw("sameP");

   //create a transparent pad drawn on top of the main pad
   c1->cd();
   TPad *overlay = new TPad("overlay","",0,0,1,1);
   overlay->SetFillStyle(4000);
   overlay->SetFillColor(0);
   overlay->SetFrameFillStyle(4000);
   overlay->Draw();
   overlay->cd();
   // create second graph
   //TGraphErrors* gr_GIF_Num = new TGraphErrors("data_noerror.dat","%lg %lg");
   TGraphErrors *gr_GIF_Num = new TGraphErrors(GIF_Nevents.size());
   TGraphErrors *gr_IV_Num = new TGraphErrors(IV_Nevents.size());
   TGraphErrors *gr_V_Num = new TGraphErrors(V_Nevents.size());

   for(unsigned int i=0;i<V_MeanPosOfSector.size();i++)
   {
       gr_GIF_Num->SetPoint(i,GIF_MeanPosOfSector[i],GIF_Nevents[i]);
       gr_IV_Num->SetPoint(i,IV_MeanPosOfSector[i],IV_Nevents[i]);
       gr_V_Num->SetPoint(i,V_MeanPosOfSector[i],V_Nevents[i]);

   }
   gr_GIF_Num->SetMarkerColor(kRed);
   gr_GIF_Num->SetLineColor(kRed);
   gr_GIF_Num->SetLineStyle(2);
   gr_GIF_Num->SetLineWidth(3);
   gr_GIF_Num->SetMarkerStyle(23);
   gr_GIF_Num->SetName("gr_GIF_Num");

   gr_IV_Num->SetMarkerColor(kRed);
   gr_IV_Num->SetLineColor(kRed);
   gr_IV_Num->SetMarkerStyle(22);
   gr_IV_Num->SetLineStyle(2);
   gr_IV_Num->SetLineWidth(3);
   gr_IV_Num->SetName("gr_IV_Num");

   gr_V_Num->SetMarkerColor(kRed);
   gr_V_Num->SetLineColor(kRed);
   gr_V_Num->SetMarkerStyle(21);
   gr_V_Num->SetLineStyle(2);
   gr_V_Num->SetLineWidth(3);
   gr_V_Num->SetName("gr_V_Num");

   Double_t xmin = pad->GetUxmin();
   Double_t ymin = 0;
   Double_t xmax = pad->GetUxmax();
   Double_t ymax = 1550;
   TH1F *hframe = overlay->DrawFrame(xmin,ymin,xmax,ymax);
   hframe->GetXaxis()->SetLabelOffset(99);
   hframe->GetYaxis()->SetLabelOffset(99);
//   hframe->Draw("Y+");
   
//   gr_GIF_Num->Draw("PY+");
   gr_IV_Num->Draw("PY+");
//   gr_V_Num->Draw("PY+");

   //Draw the Legend 
   TLegend *leg = new TLegend(0.59,0.650,0.90,0.75);
   leg->SetTextFont(42);
   leg->SetTextSize(0.04);
//   leg->AddEntry(gr_GIF,"GE11_IV_GIF eff","PE");
   leg->AddEntry(gr_IV,"GE1/1: efficiency","PE");
//   leg->AddEntry(gr_V,"GE11_V eff","PE");
//   leg->AddEntry(gr_GIF_Num,"No of events_GE11_IV_GIF","P");
   leg->AddEntry(gr_IV_Num,"GE1/1: No. of events ","PE");
//   leg->AddEntry(gr_V_Num,"No of events_GE11_V","P");

   leg->Draw("same");

   const char *runnum = RunName.c_str();
   
   TLatex *t2a = new TLatex(0.10,0.94, runnum  );
   t2a->SetNDC();
   t2a->SetTextFont(42);
   t2a->SetTextSize(0.033);
   t2a->SetTextAlign(13);
//   t2a->Draw("same");
   
   TLatex *cmsprem = new TLatex(0,1570,"#it{Preliminary}");
   //TLatex *cmsprem = new TLatex(0,1570,"CMS #it{Preliminary}");
   cmsprem->Draw("same");
   TLatex *cmsprem1 = new TLatex(90,1570,"GE1/1");
   cmsprem1->Draw("same");

   TLatex *txt1 = new TLatex(7.5,1200,"Threshold = 1.6fC");
   TLatex *txt2 = new TLatex(7.5,1100,"Beam: Muon");
   TLatex *txt3 = new TLatex(7.5,1000,"Gap Config: 3/1/2/1 mm");
   TLatex *txt4 = new TLatex(7.5,900,"Gas: Ar/CO_{2} (70/30)");
   TLatex *txt5 = new TLatex(7.5,800,"E_{gain} = 77.4 kV/cm");
   txt1->SetTextFont(42);
   txt1->SetTextSize(0.04);
   txt1->Draw("same");
   txt2->SetTextFont(42);
   txt2->SetTextSize(0.04);
   txt2->Draw("same");
   txt3->SetTextFont(42);
   txt3->SetTextSize(0.04);
   txt3->Draw("same");
   txt4->SetTextFont(42);
   txt4->SetTextSize(0.04);
   txt4->Draw("same");
   txt5->SetTextFont(42);
   txt5->SetTextSize(0.04);
   txt5->Draw("same");
   
   
   //Draw an axis on the right side
   TGaxis *axis = new TGaxis(xmax,ymin,xmax, ymax,ymin,1200,10,"+L");
   axis->SetLineColor(kRed);
   axis->SetLabelColor(kRed);
   axis->SetTitle("Number of events");
   axis->SetTitleOffset(1.1);

   axis->Draw();

   string OutputFileName = "GE11_Efficiency_Scan_"+std::to_string(RunNumber)+".pdf";
   string OutputFileNamepng = "GE11_Efficiency_Scan_"+std::to_string(RunNumber)+".png";
   const char *CharOutputFileName = OutputFileName.c_str();
   const char *CharOutputFileNamepng = OutputFileNamepng.c_str();
   c1->SaveAs(CharOutputFileName);
   c1->SaveAs(CharOutputFileNamepng);

   c1->Write();
   //tree->Write();
   //tree->Write("", TObject::kOverwrite);
   f->Write();

}
