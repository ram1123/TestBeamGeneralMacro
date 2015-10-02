#include "TCanvas.h"
#include "TFile.h"
#include "TNtuple.h"
#include "TProfile.h"
#include "TBenchmark.h"
#include "TStyle.h"
#include "TPaveText.h"
#include "TFrame.h"
#include "TF1.h"
#include "TROOT.h"
#include "TSystem.h"
#include "TInterpreter.h"
#include "TTree.h"
#include "TH1.h"
#include "time.h"
#include <TCut.h>
#include <iostream>
#include <iomanip>
#include <algorithm>
#include "TMultiGraph.h"
#include <string>
#include <sstream>
#include "TPaveText.h"
#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

std::string OutDir = "tmp_GEM/";


void graphplotter(){
  TCanvas *Canv = new TCanvas("Canv"," ",0,0,500,500);
  gROOT->ProcessLine(".L tdrstyle.C");
  setTDRStyle();
  Int_t m = 17;
  Float_t x , y1, y2, y3;

  Float_t xx[17] = 0.0;
  Float_t yy1[17] = 0.0;
  Float_t yy2[17] = 0.0;
  Float_t yy3[17] = 0.0;
  
  ifstream inputfile("Cluster_test.txt");
  if(!inputfile)cout<<" Data File not found"<<endl;
  for (Int_t i = 0; i <17 ; i++){
    
    inputfile >>  x >> y1 >> y2 >> y3;
    xx[i] = x;
    yy1[i] = y1;
    yy2[i] = y2;
    yy3[i] = y3;
  }
  inputfile.close();
  /*
  float x[20]={710,700,690,680,670,660,650,640,630,620,610,600,590,580,570,560,550};
  float y1[20]={2.815,2.494,2.162,1.812,1.638,1.487,1.472,1.372,1.354,1.311,1.426,1.437,1.581,1.51,1.304,1.139,1.294};
  float y2[20]={4.604,3.949,3.336,2.801,2.316,1.981,1.666,1.550,1.440,1.386,1.425,1.448,1.467,1.20,1.276,1.018,1.057};
  float y3[20]={2.277,2.152,2.027,1.900,1.804,1.689,1.576,1.460,1.345,1.333,1.239,1.253,1.272,1.246,1.307,1.323,1.451};
  */

  TMultiGraph *mg=new TMultiGraph();
  TGraph *graphTight= new TGraph(17,xx,yy3);
  graphTight->SetMarkerStyle(29);
  graphTight->SetMarkerColor(kGreen);
  graphTight->SetMarkerSize(1.0);
  graphTight->SetLineColor(kGreen);

  mg->Add(graphTight);

  TGraph *graphMedium= new TGraph(17,xx,yy2);
  graphMedium->SetMarkerStyle(33);
  graphMedium->SetMarkerColor(kRed);
  graphMedium->SetMarkerSize(1.0);
  graphMedium->SetLineColor(kRed);

  mg->Add(graphMedium);

  TGraph *graphLoose= new TGraph(17,xx,yy1);
  graphLoose->SetMarkerStyle(23);
  graphLoose->SetMarkerColor(kBlue);
  graphLoose->SetLineColor(kBlue);

  graphLoose->SetMarkerSize(1.0);
  mg->Add(graphLoose);
 
  graphLoose->Draw("AP");
  mg->Add(graphLoose);
  mg->Draw("P");

  graphLoose->GetYaxis()->SetTitleOffset(1.10);
  graphLoose->GetYaxis()->SetTitleSize(0.045);
  graphLoose->GetXaxis()->SetTitleSize(0.045);
  graphLoose->GetYaxis()->SetLabelSize(0.04);
  graphLoose->GetXaxis()->SetLabelSize(0.04);
  graphLoose->GetYaxis()->SetTitleOffset(1.10);
  graphLoose->GetYaxis()->SetTitle("Cluster size");
  graphLoose->GetXaxis()->SetTitle("Current");
  graphLoose->GetYaxis()->SetRangeUser(1.0,5.0);
  //  graphLoose->SetTitle("GE11_V");


  TLegend* legend = new TLegend(0.11, 0.50, 0.375, 0.68);
  legend->SetTextSize(0.030);
  legend->SetFillColor(0);
  legend->SetTextFont(42);
  legend->AddEntry(graphTight, "Latency 22: GE11_V","lp");
  legend->AddEntry(graphLoose, "Latency 21: GE11_IV_GIF","lp");
  legend->AddEntry(graphMedium, "Latency 21: GE11_IV","lp");
  legend->Draw("same");




  TLatex *t2a = new TLatex(0.115,0.94,"   CMS Preliminary"  );
  t2a->SetNDC();
  t2a->SetTextFont(42);
  t2a->SetTextSize(0.033);
  t2a->SetTextAlign(13);
  t2a->Draw("same");
  
  TPaveText *pt = new TPaveText(0.12, 0.71, 0.40, 0.88,"NDC");
  //  pt->SetNDC();
  pt->AddText("Runs 308-405");
  pt->AddText("Beam: Muons");
  pt->AddText("MSPL4");
  pt->AddText("ASyncMode");
  //  pt->SetFillColor(42);
  pt->Draw("same");
  
  Canv->Print((OutDir + std::string("GEM.root")).c_str(),"root");
  Canv->Print((OutDir + std::string("GEM.pdf") ).c_str(),"pdf");
}
