#include<iostream>
#include <fstream>
#include<vector>
#include<string>
#include<TROOT.h>
#include "TString.h"
#include "TFile.h"
#include "TTree.h"
#include "TCanvas.h"
#include "TH1F.h"
#include "TH2F.h"
#include "TAxis.h"
#include "TLegend.h"
void macro()
{
  TFile *f1 = TFile::Open("/home/ramkrishna/TEMP/GEM_TB/TurboSoftware/DumpTextFromCRC/CRC-Run0411_Muon_10k_MSPL2_HVScan_710pt1_710pt1_710pt0_T20_T20_T20_Lat22-141011_013955-0.root");
  TFile *f2 = TFile::Open("/home/ramkrishna/TEMP/FNAL-Beam-Test-Scripts/CoarseAligned.root"); 
  //TFile *f2 = TFile::Open("/home/ramkrishna/TEMP/FNAL-BT_Ram/CoarseAligned.root"); 
  TTree * tmpTree = (TTree*)f1->Get("rd51tbgeo");
  TH1D *h_Pos_g1xcl = (TH1D*)f2->Get("h_Pos_g1xcl");

  TCanvas *c1= new TCanvas("c1", "c1",700, 700);
  //  c1->Divide(2,1);

  //c1->cd(1);
  TH1F* h_Pos_g1xcl_T=new TH1F("h_Pos_g1xcl_T","", 100, -10, 110);

  tmpTree->Draw("g1xcl.geoposX>>h_Pos_g1xcl_T","g1ycl@.GetEntries()==1 && g1xcl@.GetEntries()==1 && g2ycl@.GetEntries()==1 && g2xcl@.GetEntries()==1 && g3ycl@.GetEntries()==1 && g3xcl@.GetEntries()==1");

  h_Pos_g1xcl_T->GetXaxis()->SetTitle("Cluster position [mm]");
  h_Pos_g1xcl_T->GetYaxis()->SetTitle("Number of event");
  h_Pos_g1xcl_T->SetTitleSize(0.04, "XY");
  h_Pos_g1xcl_T->SetLabelSize(0.04, "XY");
  // h_Pos_g1xcl_T->SetTitle("Using Turbosoftware");
  h_Pos_g1xcl_T->SetStats(0);
  h_Pos_g1xcl_T->SetLineColor(kRed);
  h_Pos_g1xcl_T->SetLineWidth(2);
  h_Pos_g1xcl->SetLineColor(kBlue);
  h_Pos_g1xcl->SetLineWidth(2);
 
  //c1->Update();

  //c1->cd(2);

  //  h_Pos_g1xcl->SetTitle("From Aiwu's Code");

  h_Pos_g1xcl_T->Draw();
  h_Pos_g1xcl->Draw("sames");
  h_Pos_g1xcl->SetStats(0);

  // c1->Update();

  TLegend *legend=new TLegend(0.55, 0.80, 0.69, 0.75);//0.5560345,0.7004219,0.6997126,0.850211);
  legend->SetTextFont(72);
  legend->SetLineColor(0);
  legend->SetTextSize(0.03);
  legend->SetFillColor(0);
  legend->AddEntry(h_Pos_g1xcl_T,"TurboSoftware","l");
  legend->AddEntry(h_Pos_g1xcl,"From Aiwu's Code","l");
  legend->Draw();
  c1->Draw();
  c1->SaveAs("plots/pos_g1xcl.pdf");

  //********************************************************************



  //********************************************************************

  TH1D *h_Pos_g1ycl = (TH1D*)f2->Get("h_Pos_g1ycl");

  TCanvas *c2= new TCanvas("c2", "c2",700, 700);
  TH1F* h_Pos_g1ycl_T=new TH1F("h_Pos_g1ycl_T","", 100, -10, 110);

  tmpTree->Draw("g1ycl.geoposY>>h_Pos_g1ycl_T","g1ycl@.GetEntries()==1 && g1xcl@.GetEntries()==1 && g2ycl@.GetEntries()==1 && g2xcl@.GetEntries()==1 && g3ycl@.GetEntries()==1 && g3xcl@.GetEntries()==1");

  h_Pos_g1ycl_T->GetXaxis()->SetTitle("Cluster position [mm]");
  h_Pos_g1ycl_T->GetYaxis()->SetTitle("Number of event");
  h_Pos_g1ycl_T->SetTitleSize(0.04, "XY");
  h_Pos_g1ycl_T->SetLabelSize(0.04, "XY");
  // h_Pos_g1xcl_T->SetTitle("Using Turbosoftware");                                                                                             
  h_Pos_g1ycl_T->SetStats(0);
  h_Pos_g1ycl_T->SetLineColor(kRed);
  h_Pos_g1ycl_T->SetLineWidth(2);
  h_Pos_g1ycl->SetLineColor(kBlue);
  h_Pos_g1ycl->SetLineWidth(2);

  h_Pos_g1ycl_T->Draw();
  h_Pos_g1ycl->Draw("sames");
  h_Pos_g1ycl->SetStats(0);

  TLegend *t=new TLegend(0.55, 0.80, 0.69, 0.75);//0.5560345,0.7004219,0.6997126,0.850211);                                                
  t->SetTextFont(72);
  t->SetLineColor(0);
  t->SetTextSize(0.03);
  t->SetFillColor(0);
  t->AddEntry(h_Pos_g1ycl_T,"TurboSoftware","l");
  t->AddEntry(h_Pos_g1ycl,"From Aiwu's Code","l");
  t->Draw();
  c2->Draw();
  c2->SaveAs("plots/pos_g1ycl.pdf");
  //**********************************************************


  //**************************************************************
  TH1D *h_Pos_g2xcl = (TH1D*)f2->Get("h_Pos_g2xcl");

  TCanvas *c3= new TCanvas("c3", "c3",700, 700);
  TH1F* h_Pos_g2xcl_T=new TH1F("h_Pos_g2xcl_T","", 100, -10, 110);

  tmpTree->Draw("g2xcl.geoposX>>h_Pos_g2xcl_T","g1ycl@.GetEntries()==1 && g1xcl@.GetEntries()==1 && g2ycl@.GetEntries()==1 && g2xcl@.GetEntries()==1 && g3ycl@.GetEntries()==1 && g3xcl@.GetEntries()==1");

  h_Pos_g2xcl_T->GetXaxis()->SetTitle("Cluster position [mm]");
  h_Pos_g2xcl_T->GetYaxis()->SetTitle("Number of event");
  h_Pos_g2xcl_T->SetTitleSize(0.04, "XY");
  h_Pos_g2xcl_T->SetLabelSize(0.04, "XY");
  // h_Pos_g1xcl_T->SetTitle("Using Turbosoftware");                                                                                             
  h_Pos_g2xcl_T->SetStats(0);
  h_Pos_g2xcl_T->SetLineColor(kRed);
  h_Pos_g2xcl_T->SetLineWidth(3);
  h_Pos_g2xcl->SetLineColor(kBlue);
  h_Pos_g2xcl->SetLineWidth(2);
  h_Pos_g2xcl_T->Draw();
  h_Pos_g2xcl->Draw("sames");
  h_Pos_g2xcl->SetStats(0);

  // c1->Update();                                                                                                                               

  TLegend *b=new TLegend(0.55, 0.80, 0.69, 0.75);//0.5560345,0.7004219,0.6997126,0.850211);                                                 
  b->SetTextFont(72);
  b->SetLineColor(0);
  b->SetTextSize(0.03);
  b->SetFillColor(0);
  b->AddEntry(h_Pos_g2xcl_T,"TurboSoftware","l");
  b->AddEntry(h_Pos_g2xcl,"From Aiwu's Code","l");
  b->Draw();
  c3->Draw();
  c3->SaveAs("plots/pos_g2xcl.pdf");
  //*******************************************************


  //**********************************************************

  TH1D *h_Pos_g2ycl = (TH1D*)f2->Get("h_Pos_g2ycl");

  TCanvas *c4= new TCanvas("c4", "c4",700, 700);
  TH1F* h_Pos_g2ycl_T=new TH1F("h_Pos_g2ycl_T","", 100, -10, 110);

  tmpTree->Draw("g2ycl.geoposY>>h_Pos_g2ycl_T","g1ycl@.GetEntries()==1 && g1xcl@.GetEntries()==1 && g2ycl@.GetEntries()==1 && g2xcl@.GetEntries()==1 && g3ycl@.GetEntries()==1 && g3xcl@.GetEntries()==1");

  h_Pos_g2ycl_T->GetXaxis()->SetTitle("Cluster position [mm]");
  h_Pos_g2ycl_T->GetYaxis()->SetTitle("Number of event");
  h_Pos_g2ycl_T->SetTitleSize(0.04, "XY");
  h_Pos_g2ycl_T->SetLabelSize(0.04, "XY");
  // h_Pos_g1xcl_T->SetTitle("Using Turbosoftware");                                                                                        
  h_Pos_g2ycl_T->SetStats(0);
  h_Pos_g2ycl_T->SetLineColor(kRed);
  h_Pos_g2ycl_T->SetLineWidth(3);
  h_Pos_g2ycl->SetLineColor(kBlue);
  h_Pos_g2ycl->SetLineWidth(2);

  h_Pos_g2ycl_T->Draw();
  h_Pos_g2ycl->Draw("sames");
  h_Pos_g2ycl->SetStats(0);

  TLegend *d=new TLegend(0.55, 0.80, 0.69, 0.75);//0.5560345,0.7004219,0.6997126,0.850211);                                                      
  d->SetTextFont(72);
  d->SetLineColor(0);
  d->SetTextSize(0.03);
  d->SetFillColor(0);
  d->AddEntry(h_Pos_g2ycl_T,"TurboSoftware","l");
  d->AddEntry(h_Pos_g2ycl,"From Aiwu's Code","l");
  d->Draw();
  c4->Draw();
  c4->SaveAs("plots/pos_g2ycl.pdf");

  //******************************************************



  //****************************************************************

  TH1D *h_Pos_g3xcl = (TH1D*)f2->Get("h_Pos_g3xcl");

  TCanvas *c5= new TCanvas("c5", "c5",700, 700);
  TH1F* h_Pos_g3xcl_T=new TH1F("h_Pos_g3xcl_T","", 100, -10, 110);

  tmpTree->Draw("g3xcl.geoposX>>h_Pos_g3xcl_T","g1ycl@.GetEntries()==1 && g1xcl@.GetEntries()==1 && g2ycl@.GetEntries()==1 && g2xcl@.GetEntries()==1 && g3ycl@.GetEntries()==1 && g3xcl@.GetEntries()==1");

  h_Pos_g3xcl_T->GetXaxis()->SetTitle("Cluster position [mm]");
  h_Pos_g3xcl_T->GetYaxis()->SetTitle("Number of event");
  h_Pos_g3xcl_T->SetTitleSize(0.04, "XY");
  h_Pos_g3xcl_T->SetLabelSize(0.04, "XY");
  // h_Pos_g1xcl_T->SetTitle("Using Turbosoftware");                                                                                    
  h_Pos_g3xcl_T->SetStats(0);
  h_Pos_g3xcl_T->SetLineColor(kRed);
  h_Pos_g3xcl_T->SetLineWidth(3);
  h_Pos_g3xcl->SetLineColor(kBlue);
  h_Pos_g3xcl->SetLineWidth(2);
  h_Pos_g3xcl_T->Draw();
  h_Pos_g3xcl->Draw("sames");
  h_Pos_g3xcl->SetStats(0);

  TLegend *n=new TLegend(0.55, 0.80, 0.69, 0.75);//0.5560345,0.7004219,0.6997126,0.850211);                                                      
  n->SetTextFont(72);
  n->SetLineColor(0);
  n->SetTextSize(0.03);
  n->SetFillColor(0);
  n->AddEntry(h_Pos_g3xcl_T,"TurboSoftware","l");
  n->AddEntry(h_Pos_g3xcl,"From Aiwu's Code","l");
  n->Draw();
  c5->Draw();
  c5->SaveAs("plots/pos_g3xcl.pdf");

  //****************************************************



  //***********************************************************
  TH1D *h_Pos_g3ycl = (TH1D*)f2->Get("h_Pos_g3ycl");

  TCanvas *c6= new TCanvas("c6", "c6",700, 700);
  TH1F* h_Pos_g3ycl_T=new TH1F("h_Pos_g3ycl_T","", 100, -10, 110);

  tmpTree->Draw("g3ycl.geoposY>>h_Pos_g3ycl_T","g1ycl@.GetEntries()==1 && g1xcl@.GetEntries()==1 && g2ycl@.GetEntries()==1 && g2xcl@.GetEntries()==1 && g3ycl@.GetEntries()==1 && g3xcl@.GetEntries()==1");

  h_Pos_g3ycl_T->GetXaxis()->SetTitle("Cluster position [mm]");
  h_Pos_g3ycl_T->GetYaxis()->SetTitle("Number of event");
  h_Pos_g3ycl_T->SetTitleSize(0.04, "XY");
  h_Pos_g3ycl_T->SetLabelSize(0.04, "XY");
  // h_Pos_g1xcl_T->SetTitle("Using Turbosoftware");                                                                                             
  h_Pos_g3ycl_T->SetStats(0);
  h_Pos_g3ycl_T->SetLineColor(kRed);
  h_Pos_g3ycl_T->SetLineWidth(3);
  h_Pos_g3ycl->SetLineColor(kBlue);
  h_Pos_g3ycl->SetLineWidth(2);

  h_Pos_g3ycl_T->Draw();
  h_Pos_g3ycl->Draw("sames");
  h_Pos_g3ycl->SetStats(0);

  TLegend *p=new TLegend(0.55, 0.80, 0.69, 0.75);//0.5560345,0.7004219,0.6997126,0.850211);                                            
  p->SetTextFont(72);
  p->SetLineColor(0);
  p->SetTextSize(0.03);
  p->SetFillColor(0);
  p->AddEntry(h_Pos_g3ycl_T,"TurboSoftware","l");
  p->AddEntry(h_Pos_g3ycl,"From Aiwu's Code","l");
  p->Draw();
  c6->Draw();
  c6->SaveAs("plots/pos_g3ycl.pdf");
  //*****************************************************


  //************************************************************
  TH1D *h_Pos_sCMSNS2LC1 = (TH1D*)f2->Get("h_Pos_sCMSNS2LC1");
  TCanvas *c7= new TCanvas("c7", "c7",700, 700);
  TH1F* h_Pos_sCMSNS2LC1_T=new TH1F("h_Pos_sCMSNS2LC1_T","", 100, -10, 110);

  tmpTree->Draw("sCMSNS2LC1.geoposY>>h_Pos_sCMSNS2LC1_T","g1ycl@.GetEntries()==1 && g1xcl@.GetEntries()==1 && g2ycl@.GetEntries()==1 && g2xcl@.GetEntries()==1 && g3ycl@.GetEntries()==1 && g3xcl@.GetEntries()==1 && sCMSNS2LC1@.GetEntries()>0 ");
  //tmpTree->Draw("sCMSNS2LC1.geoposY>>h_Pos_sCMSNS2LC1_T","g1ycl@.GetEntries()==1 && g1xcl@.GetEntries()==1 && g2ycl@.GetEntries()==1 && g2xcl@.GetEntries()==1 && g3ycl@.GetEntries()==1 && g3xcl@.GetEntries()==1 && sCMSNS2LC1@.GetEntries()==1 && sCMSNS2LC2@.GetEntries()==1 && sCMSNS2LC3@.GetEntries()==1");

  //    tmpTree->Draw("sCMSNS2LC1.geoposY>>h_Pos_sCMSNS2LC1_T");
	// tmpTree->Draw("sCMSNS2LC1.geoposY>>h_Pos_sCMSNS2LC1_T", "sCMSNS2LC1@.GetEntries()==1 && sCMSNS2LC2@.GetEntries()==1 && sCMSNS2LC3@.GetEntries()==1 ");
  h_Pos_sCMSNS2LC1_T->GetXaxis()->SetTitle("Cluster position [mm]");
  h_Pos_sCMSNS2LC1_T->GetYaxis()->SetTitle("Number Of Events");
  h_Pos_sCMSNS2LC1_T->SetTitleSize(0.04, "XY");
  h_Pos_sCMSNS2LC1_T->SetLabelSize(0.04, "XY");

  h_Pos_sCMSNS2LC1_T->SetStats(0);
  h_Pos_sCMSNS2LC1_T->SetLineColor(kRed);
  h_Pos_sCMSNS2LC1_T->SetLineWidth(3);
  h_Pos_sCMSNS2LC1->SetLineColor(kBlue);
  h_Pos_sCMSNS2LC1->SetLineWidth(2);

  h_Pos_sCMSNS2LC1_T->Draw();
  h_Pos_sCMSNS2LC1->Draw("sames");
  //  h_Pos_sCMSNS2LC1->SetStats(0);
    h_Pos_sCMSNS2LC1_T->SetStats();
  TLegend *m=new TLegend(0.55, 0.80, 0.69, 0.75);//0.5560345,0.7004219,0.6997126,0.850211);                                                      
  m->SetTextFont(72);
  m->SetLineColor(0);
  m->SetTextSize(0.03);
  m->SetFillColor(0);
  m->AddEntry(h_Pos_sCMSNS2LC1_T,"TurboSoftware","l");
  m->AddEntry(h_Pos_sCMSNS2LC1,"From Aiwu's Code","l");
  m->Draw();
  c7->Draw();
  c7->SaveAs("plots/pos_sCMSNS2LC1.pdf");
  //******************************************************


  //*******************************************************

  TH1D *h_Pos_sCMSNS2LC2 = (TH1D*)f2->Get("h_Pos_sCMSNS2LC2");
  TCanvas *c8= new TCanvas("c8", "c8",700, 700);
  TH1F* h_Pos_sCMSNS2LC2_T=new TH1F("h_Pos_sCMSNS2LC2_T","", 100, -10, 110);

  tmpTree->Draw("sCMSNS2LC2.geoposY>>h_Pos_sCMSNS2LC2_T","g1ycl@.GetEntries()==1 && g1xcl@.GetEntries()==1 && g2ycl@.GetEntries()==1 && g2xcl@.GetEntries()==1 && g3ycl@.GetEntries()==1 && g3xcl@.GetEntries()==1 && sCMSNS2LC2@.GetEntries()>0 ");
  //    tmpTree->Draw("sCMSNS2LC1.geoposY>>h_Pos_sCMSNS2LC1_T");                                                                                 
  // tmpTree->Draw("sCMSNS2LC1.geoposY>>h_Pos_sCMSNS2LC1_T", "sCMSNS2LC1@.GetEntries()==1 && sCMSNS2LC2@.GetEntries()==1 && sCMSNS2LC3@.GetEntries()==1 ");                                                                                                                                
  h_Pos_sCMSNS2LC2_T->GetXaxis()->SetTitle("Cluster position [mm]");
  h_Pos_sCMSNS2LC2_T->GetYaxis()->SetTitle("Number Of Events");
  h_Pos_sCMSNS2LC2_T->SetTitleSize(0.04, "XY");
  h_Pos_sCMSNS2LC2_T->SetLabelSize(0.04, "XY");

  h_Pos_sCMSNS2LC2_T->SetStats(0);
  h_Pos_sCMSNS2LC2_T->SetLineColor(kRed);
  h_Pos_sCMSNS2LC2_T->SetLineWidth(3);
  h_Pos_sCMSNS2LC2->SetLineColor(kBlue);
  h_Pos_sCMSNS2LC2->SetLineWidth(2);

  h_Pos_sCMSNS2LC2_T->Draw();
  h_Pos_sCMSNS2LC2->Draw("sames");
  //  h_Pos_sCMSNS2LC1->SetStats(0);                                                                                                             
    h_Pos_sCMSNS2LC2_T->SetStats();
  TLegend *l=new TLegend(0.55, 0.80, 0.69, 0.75);//0.5560345,0.7004219,0.6997126,0.850211);                                               
  l->SetTextFont(72);
  l->SetLineColor(0);
  l->SetTextSize(0.03);
  l->SetFillColor(0);
  l->AddEntry(h_Pos_sCMSNS2LC2_T,"TurboSoftware","l");
  l->AddEntry(h_Pos_sCMSNS2LC2,"From Aiwu's Code","l");
  l->Draw();
  c8->Draw();
  c8->SaveAs("plots/pos_sCMSNS2LC2.pdf");
  //***********************************************


  //*************************************************************

  TH1D *h_Pos_sCMSNS2LC3 = (TH1D*)f2->Get("h_Pos_sCMSNS2LC3");
  TCanvas *c9= new TCanvas("c9", "c9",700, 700);
  TH1F* h_Pos_sCMSNS2LC3_T=new TH1F("h_Pos_sCMSNS2LC3_T","", 100, -10, 110);

  tmpTree->Draw("sCMSNS2LC3.geoposY>>h_Pos_sCMSNS2LC3_T","g1ycl@.GetEntries()==1 && g1xcl@.GetEntries()==1 && g2ycl@.GetEntries()==1 && g2xcl@.GetEntries()==1 && g3ycl@.GetEntries()==1 && g3xcl@.GetEntries()==1 && sCMSNS2LC3@.GetEntries()>0 ");
  //    tmpTree->Draw("sCMSNS2LC1.geoposY>>h_Pos_sCMSNS2LC1_T");                                                                               
  // tmpTree->Draw("sCMSNS2LC1.geoposY>>h_Pos_sCMSNS2LC1_T", "sCMSNS2LC1@.GetEntries()==1 && sCMSNS2LC2@.GetEntries()==1 && sCMSNS2LC3@.GetEntries()==1 ");                                                                                                                                    
 
  h_Pos_sCMSNS2LC3_T->GetXaxis()->SetTitle("Cluster position [mm]");
  h_Pos_sCMSNS2LC3_T->GetYaxis()->SetTitle("Number Of Events");
  h_Pos_sCMSNS2LC3_T->SetTitleSize(0.04, "XY");
  h_Pos_sCMSNS2LC3_T->SetLabelSize(0.04, "XY");

  h_Pos_sCMSNS2LC3_T->SetStats(0);
  h_Pos_sCMSNS2LC3_T->SetLineColor(kRed);
  h_Pos_sCMSNS2LC3_T->SetLineWidth(3);
  h_Pos_sCMSNS2LC3->SetLineColor(kBlue);
  h_Pos_sCMSNS2LC3->SetLineWidth(2);

  h_Pos_sCMSNS2LC3_T->Draw();
  h_Pos_sCMSNS2LC3->Draw("sames");
  //  h_Pos_sCMSNS2LC1->SetStats(0);                                                                                                           
                                                                                                                                               
  h_Pos_sCMSNS2LC3_T->SetStats();
  TLegend *r=new TLegend(0.55, 0.80, 0.69, 0.75);//0.5560345,0.7004219,0.6997126,0.850211);                                                     
  r->SetTextFont(72);
  r->SetLineColor(0);
  r->SetTextSize(0.03);
  r->SetFillColor(0);
  r->AddEntry(h_Pos_sCMSNS2LC3_T,"TurboSoftware","l");
  r->AddEntry(h_Pos_sCMSNS2LC3,"From Aiwu's Code","l");
  r->Draw();
  c9->Draw();
  c9->SaveAs("plots/pos_sCMSNS2LC3.pdf");
  //************************************************************************


  //****************************************************************************

  TH1D * h_Strip_g1xcl=(TH1D*)f2->Get("h_Strip_g1xcl");
  TCanvas *c10= new TCanvas("c10", "c10",700, 700);
 
  TH1F* h_Strip_g1xcl_T=new TH1F("h_Strip_g1xcl_T","",100, -10, 275);

  tmpTree->Draw("g1xcl.geoposch>>h_Strip_g1xcl_T","g1ycl@.GetEntries()==1 && g1xcl@.GetEntries()==1 && g2ycl@.GetEntries()==1 && g2xcl@.GetEntries()==1 && g3ycl@.GetEntries()==1 && g3xcl@.GetEntries()==1");

  h_Strip_g1xcl_T->SetXTitle("Cluster position in terms of strip");
  h_Strip_g1xcl_T->SetYTitle("Number of Events");
  h_Strip_g1xcl_T->SetTitleSize(0.04,"XY");
  h_Strip_g1xcl_T->SetLabelSize(0.04,"XY");

  h_Strip_g1xcl_T->SetStats(0);
  h_Strip_g1xcl_T->SetLineColor(kRed);
  h_Strip_g1xcl_T->SetLineWidth(3);
  h_Strip_g1xcl->SetLineColor(kBlue);
  h_Strip_g1xcl->SetLineWidth(2);

  h_Strip_g1xcl_T->Draw();
  h_Strip_g1xcl->Draw("sames");
  h_Strip_g1xcl->SetStats(0);

  TLegend *a=new TLegend(0.55, 0.80, 0.69, 0.75);//0.5560345,0.7004219,0.6997126,0.850211);                                                     
  a->SetTextFont(72);
  a->SetLineColor(0);
  a->SetTextSize(0.03);
  a->SetFillColor(0);
  a->AddEntry(h_Strip_g1xcl_T,"TurboSoftware","l");
  a->AddEntry(h_Strip_g1xcl,"From Aiwu's Code","l");
  a->Draw();
  c10->Draw();
  c10->SaveAs("plots/Strip_g1xcl.pdf");
  //**********************************************************

  //**********************************************************

  TH1D * h_Strip_g1ycl=(TH1D*)f2->Get("h_Strip_g1ycl");
  TCanvas *c11= new TCanvas("c11", "c11",700, 700);

  TH1F* h_Strip_g1ycl_T=new TH1F("h_Strip_g1ycl_T","",100, -10, 275);

  tmpTree->Draw("g1ycl.geoposch>>h_Strip_g1ycl_T","g1ycl@.GetEntries()==1 && g1xcl@.GetEntries()==1 && g2ycl@.GetEntries()==1 && g2xcl@.GetEntries()==1 && g3ycl@.GetEntries()==1 && g3xcl@.GetEntries()==1");

  h_Strip_g1ycl_T->SetXTitle("Cluster position in terms of strip");
  h_Strip_g1ycl_T->SetYTitle("Number of Events");
  h_Strip_g1ycl_T->SetTitleSize(0.04,"XY");
  h_Strip_g1ycl_T->SetLabelSize(0.04,"XY");

  h_Strip_g1ycl_T->SetStats(0);
  h_Strip_g1ycl_T->SetLineColor(kRed);
  h_Strip_g1ycl_T->SetLineWidth(3);
  h_Strip_g1ycl->SetLineColor(kBlue);
  h_Strip_g1ycl->SetLineWidth(2);

  h_Strip_g1ycl_T->Draw();
  h_Strip_g1ycl->Draw("sames");
  h_Strip_g1ycl->SetStats(0);

  TLegend *s=new TLegend(0.55, 0.80, 0.69, 0.75);//0.5560345,0.7004219,0.6997126,0.850211);                                                     
  s->SetTextFont(72);
  s->SetLineColor(0);
  s->SetTextSize(0.03);
  s->SetFillColor(0);
  s->AddEntry(h_Strip_g1ycl_T,"TurboSoftware","l");
  s->AddEntry(h_Strip_g1ycl,"From Aiwu's Code","l");
  s->Draw();
  c11->Draw();
  c11->SaveAs("plots/Strip_g1ycl.pdf");
  //*****************************************************************


  //*****************************************************************

  TH1D * h_Strip_g2xcl=(TH1D*)f2->Get("h_Strip_g2xcl");
  TCanvas *c12= new TCanvas("c12", "c12",700, 700);

  TH1F* h_Strip_g2xcl_T=new TH1F("h_Strip_g2xcl_T","",100, -10, 275);

  tmpTree->Draw("g2xcl.geoposch>>h_Strip_g2xcl_T","g1ycl@.GetEntries()==1 && g1xcl@.GetEntries()==1 && g2ycl@.GetEntries()==1 && g2xcl@.GetEntries()==1 && g3ycl@.GetEntries()==1 && g3xcl@.GetEntries()==1");

  h_Strip_g2xcl_T->SetXTitle("Cluster position in terms of strip");
  h_Strip_g2xcl_T->SetYTitle("Number of Events");
  h_Strip_g2xcl_T->SetTitleSize(0.04,"XY");
  h_Strip_g2xcl_T->SetLabelSize(0.04,"XY");

  h_Strip_g2xcl_T->SetStats(0);
  h_Strip_g2xcl_T->SetLineColor(kRed);
  h_Strip_g2xcl_T->SetLineWidth(3);
  h_Strip_g2xcl->SetLineColor(kBlue);
  h_Strip_g2xcl->SetLineWidth(2);

  h_Strip_g2xcl_T->Draw();
  h_Strip_g2xcl->Draw("sames");
  h_Strip_g2xcl->SetStats(0);

  TLegend *g=new TLegend(0.55, 0.80, 0.69, 0.75);//0.5560345,0.7004219,0.6997126,0.850211);                                                     
  g->SetTextFont(72);
  g->SetLineColor(0);
  g->SetTextSize(0.03);
  g->SetFillColor(0);
  g->AddEntry(h_Strip_g2xcl_T,"TurboSoftware","l");
  g->AddEntry(h_Strip_g2xcl,"From Aiwu's Code","l");
  g->Draw();
  c12->Draw();
  c12->SaveAs("plots/Strip_g2xcl.pdf");
  //******************************************************


  //**********************************************************

  TH1D * h_Strip_g2ycl=(TH1D*)f2->Get("h_Strip_g2ycl");
  TCanvas *c13= new TCanvas("c13", "c13",700, 700);

  TH1F* h_Strip_g2ycl_T=new TH1F("h_Strip_g2ycl_T","",100, -10, 275);

  tmpTree->Draw("g2ycl.geoposch>>h_Strip_g2ycl_T","g1ycl@.GetEntries()==1 && g1xcl@.GetEntries()==1 && g2ycl@.GetEntries()==1 && g2xcl@.GetEntries()==1 && g3ycl@.GetEntries()==1 && g3xcl@.GetEntries()==1");

  h_Strip_g2ycl_T->SetXTitle("Cluster position in terms of strip");
  h_Strip_g2ycl_T->SetYTitle("Number of Events");
  h_Strip_g2ycl_T->SetTitleSize(0.04,"XY");
  h_Strip_g2ycl_T->SetLabelSize(0.04,"XY");

  h_Strip_g2ycl_T->SetStats(0);
  h_Strip_g2ycl_T->SetLineColor(kRed);
  h_Strip_g2ycl_T->SetLineWidth(3);
  h_Strip_g2ycl->SetLineColor(kBlue);
  h_Strip_g2ycl->SetLineWidth(2);

  h_Strip_g2ycl_T->Draw();
  h_Strip_g2ycl->Draw("sames");
  h_Strip_g2ycl->SetStats(0);

  TLegend *c=new TLegend(0.55, 0.80, 0.69, 0.75);//0.5560345,0.7004219,0.6997126,0.850211);                                                     
  c->SetTextFont(72);
  c->SetLineColor(0);
  c->SetTextSize(0.03);
  c->SetFillColor(0);
  c->AddEntry(h_Strip_g2ycl_T,"TurboSoftware","l");
  c->AddEntry(h_Strip_g2ycl,"From Aiwu's Code","l");
  c->Draw();
  c13->Draw();
  c13->SaveAs("plots/Strip_g2ycl.pdf");
  //**************************************************


  //***************************************************

  TH1D * h_Strip_g3xcl=(TH1D*)f2->Get("h_Strip_g3xcl");
  TCanvas *c14= new TCanvas("c14", "c14",700, 700);

  TH1F* h_Strip_g3xcl_T=new TH1F("h_Strip_g3xcl_T","",100, -10, 275);

  tmpTree->Draw("g3xcl.geoposch>>h_Strip_g3xcl_T","g1ycl@.GetEntries()==1 && g1xcl@.GetEntries()==1 && g2ycl@.GetEntries()==1 && g2xcl@.GetEntries()==1 && g3ycl@.GetEntries()==1 && g3xcl@.GetEntries()==1");

  h_Strip_g3xcl_T->SetXTitle("Cluster position in terms of strip");
  h_Strip_g3xcl_T->SetYTitle("Number of Events");
  h_Strip_g3xcl_T->SetTitleSize(0.04,"XY");
  h_Strip_g3xcl_T->SetLabelSize(0.04,"XY");

  h_Strip_g3xcl_T->SetStats(0);
  h_Strip_g3xcl_T->SetLineColor(kRed);
  h_Strip_g3xcl_T->SetLineWidth(3);
  h_Strip_g3xcl->SetLineColor(kBlue);
  h_Strip_g3xcl->SetLineWidth(2);

  h_Strip_g3xcl_T->Draw();
  h_Strip_g3xcl->Draw("sames");
  h_Strip_g3xcl->SetStats(0);

  TLegend *f=new TLegend(0.55, 0.80, 0.69, 0.75);//0.5560345,0.7004219,0.6997126,0.850211);                                                     
  f->SetTextFont(72);
  f->SetLineColor(0);
  f->SetTextSize(0.03);
  f->SetFillColor(0);
  f->AddEntry(h_Strip_g2xcl_T,"TurboSoftware","l");
  f->AddEntry(h_Strip_g2xcl,"From Aiwu's Code","l");
  f->Draw();
  c14->Draw();
  c14->SaveAs("plots/Strip_g3xcl.pdf");
  //****************************************************

  //****************************************************

  TH1D * h_Strip_g3ycl=(TH1D*)f2->Get("h_Strip_g3ycl");
  TCanvas *c15= new TCanvas("c15", "c15",700, 700);

  TH1F* h_Strip_g3ycl_T=new TH1F("h_Strip_g3ycl_T","",100, -10, 275);

  tmpTree->Draw("g3ycl.geoposch>>h_Strip_g3ycl_T","g1ycl@.GetEntries()==1 && g1xcl@.GetEntries()==1 && g2ycl@.GetEntries()==1 && g2xcl@.GetEntries()==1 && g3ycl@.GetEntries()==1 && g3xcl@.GetEntries()==1");

  h_Strip_g3ycl_T->SetXTitle("Cluster position in terms of strip");
  h_Strip_g3ycl_T->SetYTitle("Number of Events");
  h_Strip_g3ycl_T->SetTitleSize(0.04,"XY");
  h_Strip_g3ycl_T->SetLabelSize(0.04,"XY");

  h_Strip_g3ycl_T->SetStats(0);
  h_Strip_g3ycl_T->SetLineColor(kRed);
  h_Strip_g3ycl_T->SetLineWidth(3);
  h_Strip_g3ycl->SetLineColor(kBlue);
  h_Strip_g3ycl->SetLineWidth(2);

  h_Strip_g3ycl_T->Draw();
  h_Strip_g3ycl->Draw("sames");
  h_Strip_g3ycl->SetStats(0);

  TLegend *q=new TLegend(0.55, 0.80, 0.69, 0.75);//0.5560345,0.7004219,0.6997126,0.850211);                                                     
  q->SetTextFont(72);
  q->SetLineColor(0);
  q->SetTextSize(0.03);
  q->SetFillColor(0);
  q->AddEntry(h_Strip_g3ycl_T,"TurboSoftware","l");
  q->AddEntry(h_Strip_g3ycl,"From Aiwu's Code","l");
  q->Draw();
  c15->Draw();
  c15->SaveAs("plots/Strip_g3ycl.pdf");
  //**********************************************************************


  //************************************************************

  TH1D *h_Strip_sCMSNS2LC1 = (TH1D*)f2->Get("h_Strip_sCMSNS2LC1");
  TCanvas *c16= new TCanvas("c16", "c16",700, 700);
  TH1F* h_Strip_sCMSNS2LC1_T=new TH1F("h_Strip_sCMSNS2LC1_T","", 100, -10, 275);

    tmpTree->Draw("sCMSNS2LC1.geoposch>>h_Strip_sCMSNS2LC1_T","g1ycl@.GetEntries()==1 && g1xcl@.GetEntries()==1 && g2ycl@.GetEntries()==1 && g2xcl@.GetEntries()==1 && g3ycl@.GetEntries()==1 && g3xcl@.GetEntries()==1 ");

  //     tmpTree->Draw("sCMSNS2LC1.geoposch>>h_Strip_sCMSNS2LC1_T");                                                                                 
  //  tmpTree->Draw("sCMSNS2LC1.geoposch>>h_Strip_sCMSNS2LC1_T", "sCMSNS2LC1@.GetEntries()==1 && sCMSNS2LC2@.GetEntries()==1 && sCMSNS2LC3@.GetEntries()==1 ");                                                                                                                               

  h_Strip_sCMSNS2LC1_T->GetXaxis()->SetTitle("Cluster position in terms of strip");
  h_Strip_sCMSNS2LC1_T->GetYaxis()->SetTitle("Number Of Events");
  h_Strip_sCMSNS2LC1_T->SetTitleSize(0.04, "XY");
  h_Strip_sCMSNS2LC1_T->SetLabelSize(0.04, "XY");

  h_Strip_sCMSNS2LC1_T->SetStats(0);
  h_Strip_sCMSNS2LC1_T->SetLineColor(kRed);
  h_Strip_sCMSNS2LC1_T->SetLineWidth(3);
  h_Strip_sCMSNS2LC1->SetLineColor(kBlue);
  h_Strip_sCMSNS2LC1->SetLineWidth(2);

  h_Strip_sCMSNS2LC1_T->Draw();
  h_Strip_sCMSNS2LC1->Draw("sames");
  h_Strip_sCMSNS2LC1->SetStats(0);

  TLegend *z=new TLegend(0.55, 0.80, 0.69, 0.75);//0.5560345,0.7004219,0.6997126,0.850211);                                                     
  z->SetTextFont(72);
  z->SetLineColor(0);
  z->SetTextSize(0.03);
  z->SetFillColor(0);
  z->AddEntry(h_Strip_sCMSNS2LC1_T,"TurboSoftware","l");
  z->AddEntry(h_Strip_sCMSNS2LC1,"From Aiwu's Code","l");
  z->Draw();
  c16->Draw();
  c16->SaveAs("plots/Strip_sCMSNS2LC1.pdf");
  //************************************************************


  TH1D *h_Strip_sCMSNS2LC2 = (TH1D*)f2->Get("h_Strip_sCMSNS2LC2");
  TCanvas *c17= new TCanvas("c17", "c17",700, 700);
  TH1F* h_Strip_sCMSNS2LC2_T=new TH1F("h_Strip_sCMSNS2LC2_T","", 100, -10, 275);

  tmpTree->Draw("sCMSNS2LC2.geoposch>>h_Strip_sCMSNS2LC2_T","g1ycl@.GetEntries()==1 && g1xcl@.GetEntries()==1 && g2ycl@.GetEntries()==1 && g2xcl@.GetEntries()==1 && g3ycl@.GetEntries()==1 && g3xcl@.GetEntries()==1 ");

  //     tmpTree->Draw("sCMSNS2LC1.geoposch>>h_Strip_sCMSNS2LC1_T");                                                                            
  //  tmpTree->Draw("sCMSNS2LC1.geoposch>>h_Strip_sCMSNS2LC1_T", "sCMSNS2LC1@.GetEntries()==1 && sCMSNS2LC2@.GetEntries()==1 && sCMSNS2LC3@.Getentries()==1 ");                                                                                                                                

  h_Strip_sCMSNS2LC2_T->GetXaxis()->SetTitle("Cluster position in terms of strip");
  h_Strip_sCMSNS2LC2_T->GetYaxis()->SetTitle("Number Of Events");
  h_Strip_sCMSNS2LC2_T->SetTitleSize(0.04, "XY");
  h_Strip_sCMSNS2LC2_T->SetLabelSize(0.04, "XY");

  h_Strip_sCMSNS2LC2_T->SetStats(0);                                                                                                          
  h_Strip_sCMSNS2LC2_T->SetLineColor(kRed);
  h_Strip_sCMSNS2LC2_T->SetLineWidth(3);
  h_Strip_sCMSNS2LC2->SetLineColor(kBlue);
  h_Strip_sCMSNS2LC2->SetLineWidth(2);

  h_Strip_sCMSNS2LC2_T->Draw();
  h_Strip_sCMSNS2LC2->Draw("sames");
  h_Strip_sCMSNS2LC2->SetStats(0);                                                                                                            

  TLegend *j=new TLegend(0.55, 0.80, 0.69, 0.75);//0.5560345,0.7004219,0.6997126,0.850211);                                                     
  j->SetTextFont(72);
  j->SetLineColor(0);
  j->SetTextSize(0.03);
  j->SetFillColor(0);
  j->AddEntry(h_Strip_sCMSNS2LC2_T,"TurboSoftware","l");
  j->AddEntry(h_Strip_sCMSNS2LC2,"From Aiwu's Code","l");
  j->Draw();
  c17->Draw();
  c17->SaveAs("plots/Strip_sCMSNS2LC2.pdf");
  //********************************************************

  TH1D *h_Strip_sCMSNS2LC3 = (TH1D*)f2->Get("h_Strip_sCMSNS2LC3");
  TCanvas *c18= new TCanvas("c18", "c18",700, 700);
  TH1F* h_Strip_sCMSNS2LC3_T=new TH1F("h_Strip_sCMSNS2LC3_T","", 100, -10, 275);

  tmpTree->Draw("sCMSNS2LC3.geoposch>>h_Strip_sCMSNS2LC3_T","g1ycl@.GetEntries()==1 && g1xcl@.GetEntries()==1 && g2ycl@.GetEntries()==1 && g2xcl@.GetEntries()==1 && g3ycl@.GetEntries()==1 && g3xcl@.GetEntries()==1 ");

  //     tmpTree->Draw("sCMSNS2LC1.geoposch>>h_Strip_sCMSNS2LC1_T");                                                                            
  //  tmpTree->Draw("sCMSNS2LC1.geoposch>>h_Strip_sCMSNS2LC1_T", "sCMSNS2LC1@.GetEntries()==1 && sCMSNS2LC2@.GetEntries()==1 && sCMSNS2LC3@.GetEntries()==1 ");                                                                                                                                

  h_Strip_sCMSNS2LC3_T->GetXaxis()->SetTitle("Cluster position in terms of strip");
  h_Strip_sCMSNS2LC3_T->GetYaxis()->SetTitle("Number Of Events");
  h_Strip_sCMSNS2LC3_T->SetTitleSize(0.04, "XY");
  h_Strip_sCMSNS2LC3_T->SetLabelSize(0.04, "XY");
             
  h_Strip_sCMSNS2LC3_T->SetStats(0);
  h_Strip_sCMSNS2LC3_T->SetLineColor(kRed);
  h_Strip_sCMSNS2LC3_T->SetLineWidth(3);
  h_Strip_sCMSNS2LC3->SetLineColor(kBlue);
  h_Strip_sCMSNS2LC3->SetLineWidth(2);

  h_Strip_sCMSNS2LC3_T->Draw();
  h_Strip_sCMSNS2LC3->Draw("sames");
  h_Strip_sCMSNS2LC3->SetStats(0);

  TLegend *o=new TLegend(0.55, 0.80, 0.69, 0.75);//0.5560345,0.7004219,0.6997126,0.850211);                                                     
  o->SetTextFont(72);
  o->SetLineColor(0);
  o->SetTextSize(0.03);
  o->SetFillColor(0);
  o->AddEntry(h_Strip_sCMSNS2LC3_T,"TurboSoftware","l");
  o->AddEntry(h_Strip_sCMSNS2LC3,"From Aiwu's Code","l");
  o->Draw();
  c18->Draw();
  c18->SaveAs("plots/Strip_sCMSNS2LC3.pdf");

  


}
