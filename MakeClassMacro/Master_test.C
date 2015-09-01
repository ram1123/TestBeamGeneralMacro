#include "TFile.h"
#include "TH1F.h"
#include "TH2F.h"
#include "ClassReadTree.cc"
#include "TChain.h"
#include "TString.h"
#include "TLorentzVector.h"
#include "TGraphErrors.h"
#include <vector>
#include <iostream>
using namespace std;
void Master_test( ){//main programme
    TChain* t = new TChain("rd51tbgeo");
    t->Add("CRC-Run0308_Muon_10k_MSPL4_HVScan_710pt7_710pt1_710pt0_T20_T20_T20_Lat21-141010_224141-0.root");
    
    ClassReadTree CRC(t);

    TCanvas * c1 = new TCanvas("c1","",1);
    TGraphErrors *gr1 = new TGraphErrors(t->GetEntries());
    TGraphErrors *gr2 = new TGraphErrors(t->GetEntries());
    TGraphErrors *gr3 = new TGraphErrors(t->GetEntries());

    for( int iEv = 0 ; iEv < t->GetEntries() ; iEv++){//
    //for( int iEv = 0 ; iEv < 10 ; iEv++){//	Event Loop Starts
	t->GetEntry(iEv);

	//cout<<"===>  "<<CRC.g1xcl_geoposX[0]<<endl;
	//cout<<"===>  "<<CRC.g2xcl_geoposX[0]<<endl;
	//cout<<"===>  "<<CRC.g3xcl_geoposX[0]<<endl;
	if (CRC.g1xcl_geoposX[0]>0)
	    gr1->SetPoint(iEv, 100, CRC.g1xcl_geoposX[0]);
	else
	    gr1->SetPoint(iEv, 100, -10);
	if (CRC.g2xcl_geoposX[0]>0)
	    gr2->SetPoint(iEv, 380, CRC.g2xcl_geoposX[0]);
	else
	    gr2->SetPoint(iEv, 380, -10);
	if (CRC.g3xcl_geoposX[0]>0)
	    gr3->SetPoint(iEv, 830, CRC.g3xcl_geoposX[0]);
	else
	    gr3->SetPoint(iEv, 830, -10);

	
    }// End Event Loop
    gr1->SetMarkerColor(kBlue);
    gr1->SetMarkerStyle(21);
    gr2->SetMarkerColor(kRed);
    gr2->SetMarkerStyle(21);
    gr3->SetMarkerColor(kGreen);
    gr3->SetMarkerStyle(21);
    gr1->GetXaxis()->SetRangeUser(50., 900.);
    gr2->GetXaxis()->SetRangeUser(50., 900.);
    gr3->GetXaxis()->SetRangeUser(50., 900.);
    //gr1->Draw("AP*");
    //gr3->Draw("AP");
    //gr2->Draw("samesP*");
    //gr3->Draw("samesP*");
    TMultiGraph *mg = new TMultiGraph();
    mg->Add(gr1);
    mg->Add(gr2);
    mg->Add(gr3);
    mg->Draw("AP");
    c1->SaveAs("Hit_Distribution.pdf");
}
