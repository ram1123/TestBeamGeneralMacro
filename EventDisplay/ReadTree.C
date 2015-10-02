/*
 * =====================================================================================
 *
 *       Filename:  ReadTree.C
 *
 *    Description:  ReadTree
 *
 *        Version:  1.0
 *        Created:  Saturday 01 August 2015 07:17:46  CEST
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Ramkrishna Sharma (Ram), ramkrishna.sharma71@gmail.com
 *   Organization:  CERN
 *
 * =====================================================================================
 */

#include <iostream>
#include "TH1F.h"
#include "TTree.h"
#include "TCanvas.h"
#include "TFile.h"
#include "TParallelCoordVar.h"
#include "TParallelCoord.h"
#include "TParallelCoordRange.h"
#include "TCut.h"


void ReadTree(){
    
    // Read file
    //TFile* f1 = new TFile("CRC-Run1393_Muon_10k_MSPL4_Async_HVScan_640pt3_640pt6_640pt1_T15_T15_T15_Lat15-141023_022733-0.root","READ");
    TFile* f1 = new TFile("/home/ramkrishna/TEMP/TestBeamGeneralMacro/CRC-Run0308_Muon_10k_MSPL4_HVScan_710pt7_710pt1_710pt0_T20_T20_T20_Lat21-141010_224141-0.root","READ");
    if ( !f1 || f1->IsZombie() )
    {
	cout<<"ERROR1:: Either file does not exists or file is corupted."<<endl;
	return;
    }
    TTree* rd51tbgeo = (TTree*)f1->Get("rd51tbgeo");
    if ( !rd51tbgeo || rd51tbgeo->IsZombie() )
    {
	cout<<"ERROR2:: This tree does not exits"<<endl;
	return;
    }

    // Add friend to the previous tree rd51tbgeo.
    //rd51tbgeo->AddFriend("trackertree","RECO-CRC-Run1393_Muon_10k_MSPL4_Async_HVScan_640pt3_640pt6_640pt1_T15_T15_T15_Lat15-141023_022733-0.root");

    //TH1F* h1 = new TH1F("h1","cluster position",256,0,256);
    

    TCanvas* canvas = new TCanvas("canvas","cluster position",1);

    // Define few cuts
    TCut cut_entries_g1 = "g1ycl@.GetEntries()==1 && g1xcl@.GetEntries()==1";
    TCut cut_entries_g2 = "g2ycl@.GetEntries()==1 && g2xcl@.GetEntries()==1";
    TCut cut_entries_g3 = "g3ycl@.GetEntries()==1 && g3xcl@.GetEntries()==1";
    //TCut cut_entries	= cut_entries_g1 && cut_entries_g2 && cut_entries_g3;
    TCut cut_entries	= "";
    //TCut cut_chi2	= "tracky.chi2 < 10 && trackx.chi2 < 10";
    //TCut cut_residual	= "residualx < 2. && residualy < 2.";
    //TCut cut_all	= cut_entries && cut_chi2 && cut_residual;


    int entries = rd51tbgeo->GetEntries();
    cout<<"Entries = "<<entries<<endl;

    // Loop over events.
    for(int event = 0; event<entries;event+=9000)
    //for(int event = 0; event<40;event+=50)
    {
    //rd51tbgeo->Draw("g1xcl.geoposch:g2xcl.geoposch:g3xcl.geoposch",cut_entries_g1 && cut_entries_g2 && cut_entries_g3 && cut_chi2 && cut_residual ,"PARA",50,event);
    //rd51tbgeo->Draw("g1xcl.geoposch:g2xcl.geoposch:g3xcl.geoposch",cut_entries_g1 && cut_entries_g2 && cut_entries_g3 ,"PARA",50,event);
    rd51tbgeo->Draw("g1xcl.geoposX:g2xcl.geoposX:g3xcl.geoposX",cut_entries ,"PARA",400,event);
    TParallelCoord* para = (TParallelCoord*)gPad->GetListOfPrimitives()->FindObject("ParaCoord");
    //TColor *col26 = gROOT->GetColor(26); col26->SetAlpha(0.01);
    //para->SetLineColor(26);
    //TParallelCoordVar* g1xcl = (TParallelCoordVar*)para->GetVarList()->FindObject("g1xcl.geoposch");
    //g1xcl->AddRange(new TParallelCoordRange(g1xcl,60,180));
    para->SetGlobalMin(0);
    para->SetGlobalMax(100);
    para->SetLineWidth(2);
    canvas->Update();

    //canvas->SaveAs(Form("cluster_position_%d.pdf",event));
    //canvas->Clear();
    }
    
    cout<<"Done successfully... :D "<<endl;
}
