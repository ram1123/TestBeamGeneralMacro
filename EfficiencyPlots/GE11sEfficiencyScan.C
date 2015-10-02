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

void GE11sEfficiencyScan(int RunNumber, string RunName)
{
   
   ifstream InGE11_IV_GIF, InGE11_IV, InGE11_V;
   string gif = "/home/ramkrishna/TEMP/LogFiles_TB/LogFiles306To407/Efficiency_LC1_"+std::to_string(RunNumber)+".log";
   string IV = "/home/ramkrishna/TEMP/LogFiles_TB/LogFiles306To407/Efficiency_LC2_"+std::to_string(RunNumber)+".log";
   string V = "/home/ramkrishna/TEMP/LogFiles_TB/LogFiles306To407/Efficiency_LC3_"+std::to_string(RunNumber)+".log";
   //cout<<"gif = "<<gif<<endl;
   InGE11_IV_GIF.open(gif);
   InGE11_IV.open(IV);
   InGE11_V.open(V);
   //InGE11_IV_GIF.open("/home/ramkrishna/TEMP/LogFiles_TB/LogFiles306To407/Efficiency_LC1_306.log");
   //InGE11_IV.open("/home/ramkrishna/TEMP/LogFiles_TB/LogFiles306To407/Efficiency_LC2_306.log");
   //InGE11_V.open("/home/ramkrishna/TEMP/LogFiles_TB/LogFiles306To407/Efficiency_LC3_306.log");
   //in.open("1375_ite1.txt");

   string rootFile = "Efficiency_Run"+std::to_string(RunNumber)+".root";
   const char *CharrootFile = rootFile.c_str();
   TFile *f = new TFile(CharrootFile,"RECREATE");
   TNtuple *GE11_IV_GIF = new TNtuple("GE11_IV_GIF","data from ascii file LC1","MeanPosOfSector:Efficiency:EfficiencyError:Nevents");
   TNtuple *GE11_IV = new TNtuple("GE11_IV","data from ascii file LC2","MeanPosOfSector:Efficiency:EfficiencyError:Nevents");
   TNtuple *GE11_V = new TNtuple("GE11_V","data from ascii file LC3","MeanPosOfSector:Efficiency:EfficiencyError:Nevents");

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
     //cout<<temp_MeanPosOfSector+(nlines*5)<<"\t"<<temp_Efficiency<<"\t"<<temp_EfficiencyError<<"\t"<<temp_Nevents<<endl;
	//if (nlines < 5) printf("LC1=%8i, y=%8f, z=%8f, t=%8i\n",LC1,eff_LC1,eff_LC1_err,nevents_LC1,nevents_LC2,nevents_LC3);

     GIF_MeanPosOfSector.push_back(temp_MeanPosOfSector+(nlines*5));
     GIF_Efficiency.push_back(temp_Efficiency);
     GIF_EfficiencyError.push_back(temp_EfficiencyError);
     GIF_Nevents.push_back(temp_Nevents);
    	GE11_IV_GIF->Fill(temp_MeanPosOfSector+(nlines*5),temp_Efficiency,temp_EfficiencyError,temp_Nevents);
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
     //cout<<temp_MeanPosOfSector+(nlines*5)<<"\t"<<temp_Efficiency<<"\t"<<temp_EfficiencyError<<"\t"<<temp_Nevents<<endl;
	//if (nlines < 5) printf("LC1=%8i, y=%8f, z=%8f, t=%8i\n",LC1,eff_LC1,eff_LC1_err,nevents_LC1,nevents_LC2,nevents_LC3);

     IV_MeanPosOfSector.push_back(temp_MeanPosOfSector+(nlines*5));
     IV_Efficiency.push_back(temp_Efficiency);
     IV_EfficiencyError.push_back(temp_EfficiencyError);
     IV_Nevents.push_back(temp_Nevents);
    	GE11_IV->Fill(temp_MeanPosOfSector+(nlines*5),temp_Efficiency,temp_EfficiencyError,temp_Nevents);
	nlines++;
   }

   InGE11_IV.close();
   nlines=0;
   while (1) 
   {
     InGE11_V >> NameOfDet >> xRange >> temp_MeanPosOfSector >> temp_Efficiency >> temp_EfficiencyError >> temp_Nevents;
	if (!InGE11_V.good()) break;
     //cout<<temp_MeanPosOfSector+(nlines*5)<<"\t"<<temp_Efficiency<<"\t"<<temp_EfficiencyError<<"\t"<<temp_Nevents<<endl;
	//if (nlines < 5) printf("LC1=%8i, y=%8f, z=%8f, t=%8i\n",LC1,eff_LC1,eff_LC1_err,nevents_LC1,nevents_LC2,nevents_LC3);

     V_MeanPosOfSector.push_back(temp_MeanPosOfSector+(nlines*5));
     V_Efficiency.push_back(temp_Efficiency);
     V_EfficiencyError.push_back(temp_EfficiencyError);
     V_Nevents.push_back(temp_Nevents);
    	GE11_V->Fill(temp_MeanPosOfSector+(nlines*5),temp_Efficiency,temp_EfficiencyError,temp_Nevents);
	nlines++;
   }

   InGE11_V.close();
   string CanvasName = "RunNumber"+std::to_string(RunNumber);
   const char * CharCanvasName = CanvasName.c_str();
   TCanvas* c1 = new TCanvas(CharCanvasName,"gerrors2",200,10,700,500);
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
   //gr_GIF = new TGraphErrors("data_error.dat","%lg %lg %lg");
   //TGraphErrors *gr_GIF = new TGraphErrors(data_LC1.size(),*data_LC1,*data_eff_LC1,*data_eff_LC1_err);   // Don't know why this is not working???
   TGraphErrors *gr_GIF = new TGraphErrors(V_Efficiency.size());
   TGraphErrors *gr_IV = new TGraphErrors(V_Efficiency.size());
   TGraphErrors *gr_V = new TGraphErrors(V_Efficiency.size());
   //cout<<"data size = "<<V_Efficiency.size()<<endl;
   for(unsigned int i=0;i<V_Efficiency.size();i++)
   {
       gr_GIF->SetPoint(i, GIF_MeanPosOfSector[i], GIF_Efficiency[i]);
       gr_GIF->SetPointError(i,0, GIF_EfficiencyError[i]);
       
       gr_IV->SetPoint(i, IV_MeanPosOfSector[i], IV_Efficiency[i]);
       gr_IV->SetPointError(i,0, IV_EfficiencyError[i]);

       gr_V->SetPoint(i, V_MeanPosOfSector[i], V_Efficiency[i]);
       gr_V->SetPointError(i,0, V_EfficiencyError[i]);
   }
   gr_GIF->SetMarkerColor(kBlue);
   gr_GIF->SetLineColor(kBlue);
   gr_GIF->SetMarkerStyle(21);
   gr_GIF->GetXaxis()->SetTitle("dist (mm)");
   gr_GIF->GetYaxis()->SetTitle("Efficiency");
   gr_GIF->GetYaxis()->SetRangeUser(0,1.2);
   gr_GIF->SetTitle("Efficiency Scan");
   gr_GIF->Draw("ACP");
   gr_IV->SetMarkerColor(kGreen-6);
   gr_IV->SetLineColor(kGreen);
   gr_IV->SetMarkerStyle(21);
   gr_IV->Draw("sameCP");
   gr_V->SetMarkerColor(kBlack);
   gr_V->SetLineColor(kBlack);
   gr_V->SetMarkerStyle(21);
   gr_V->Draw("sameCP");

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
   gr_GIF_Num->SetMarkerColor(kBlue);
   gr_GIF_Num->SetLineColor(kBlue);
   gr_GIF_Num->SetLineStyle(2);
   gr_GIF_Num->SetLineWidth(3);
   gr_GIF_Num->SetMarkerStyle(22);
   gr_GIF_Num->SetName("gr_GIF_Num");

   gr_IV_Num->SetMarkerColor(kGreen-6);
   gr_IV_Num->SetLineColor(kGreen);
   gr_IV_Num->SetMarkerStyle(22);
   gr_IV_Num->SetLineStyle(2);
   gr_IV_Num->SetLineWidth(3);
   gr_IV_Num->SetName("gr_IV_Num");

   gr_V_Num->SetMarkerColor(kBlack);
   gr_V_Num->SetLineColor(kBlack);
   gr_V_Num->SetMarkerStyle(22);
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
   hframe->Draw("Y+");
   
   gr_GIF_Num->Draw("CPY+");
   gr_IV_Num->Draw("CPY+");
   gr_V_Num->Draw("CPY+");

   //Draw the Legend 
   TLegend *leg = new TLegend(0.10,0.732,0.40,0.90);
   leg->AddEntry(gr_GIF,"GE11_IV_GIF eff","LPE");
   leg->AddEntry(gr_IV,"GE11_IV eff","LPE");
   leg->AddEntry(gr_V,"GE11_V eff","LPE");
   leg->AddEntry(gr_GIF_Num,"No of events_GE11_IV_GIF","LPE");
   leg->AddEntry(gr_IV_Num,"No of events_GE11_IV","LPE");
   leg->AddEntry(gr_V_Num,"No of events_GE11_V","LPE");

   leg->Draw("same");

   const char *runnum = RunName.c_str();
   
   TLatex *t2a = new TLatex(0.10,0.94, runnum  );
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

   string OutputFileName = "GE11_Efficiency_Scan_"+std::to_string(RunNumber)+".pdf";
   const char *CharOutputFileName = OutputFileName.c_str();
   c1->SaveAs(CharOutputFileName);

   c1->Write();
   f->Write();

}
