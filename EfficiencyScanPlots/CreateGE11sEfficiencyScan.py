import sys
import os
for b in (308, 1375):
    for a in range(0, 3):
        FileName = 'GE11s_Run'+str(b)+'_Ite'+str(a)
        sys.stdout = open(FileName+'.C','w')
        print '/*'
        print ' * ====================================================================================='
        print ' *'
        print ' *       Filename:  GE11sEfficiencyScan.C'
        print ' *'
        print ' *    Description:  '
        print ' *'
        print ' *        Version:  1.0'
        print ' *        Created:  Sunday 02 August 2015 11:33:33  CEST'
        print ' *       Revision:  none'
        print ' *       Compiler:  gcc'
        print ' *'
        print ' *         Author:  Ramkrishna Sharma (Ram), ramkrishna.sharma71@gmail.com'
        print ' *   Organization:  CERN'
        print ' *'
        print ' * ====================================================================================='
        print ' */'
        print ''
        print '#include <iostream>'
        print '#include <fstream>'
        print '#include "TFile.h"'
        print '#include "TNtuple.h"'
        print '#include <vector>'
        print '#include "TCanvas.h"'
        print '#include "TPad.h"'
        print '#include "TH1F.h"'
        print '#include "TGraphErrors.h"'
        print '#include "TGaxis.h"'
        print '#include "TFrame.h"'
        print '#include "TLegend.h"'
        print '//#include ".h"'
        print ''
        print 'void %s()'%FileName
        print '{'
        print '   '
        print '   ifstream in;'
        print '   in.open("%i_ite%i.txt");'%(b, a)
        print '   //in.open("1375_ite1.txt");'
        print ''
        print '   TFile *f = new TFile("GE11sEfficiencyScan_%i_ite%i.root","RECREATE");'%(b,a)
        print '   TNtuple *ntuple = new TNtuple("ntuple","data from ascii file","LC1:eff_LC1:eff_LC1_err:nevents");'
        print ''
        print '   Int_t nlines = 0;'
        print ''
        print '   vector<double> data_eff_LC1, data_eff_LC1_err, data_eff_LC2, data_eff_LC2_err, data_eff_LC3, data_eff_LC3_err;'
        print '   vector<unsigned int> data_LC1, data_nevents_LC1,data_nevents_LC2,data_nevents_LC3, data_LC2, data_LC3;'
        print '   unsigned int LC1, nevents_LC1,nevents_LC2,nevents_LC3;'
        print '   double eff_LC1, eff_LC1_err, eff_LC2, eff_LC2_err, eff_LC3, eff_LC3_err;'
        print '   while (1) '
        print '   {'
        print '     in >> LC1 >> eff_LC1 >> eff_LC1_err >> eff_LC2 >> eff_LC2_err >> eff_LC3 >> eff_LC3_err >> nevents_LC1 >>  nevents_LC2 >> nevents_LC3;'
        print '	if (!in.good()) break;'
        print ''
        print '	data_LC1.push_back(LC1);'
        print '	data_eff_LC1.push_back(eff_LC1);'
        print '	data_eff_LC1_err.push_back(eff_LC1_err);'
        print '	data_eff_LC2.push_back(eff_LC2);'
        print '	data_eff_LC2_err.push_back(eff_LC2_err);'
        print '	data_eff_LC3.push_back(eff_LC3);'
        print '	data_eff_LC3_err.push_back(eff_LC3_err);'
        print '	data_nevents_LC1.push_back(nevents_LC1);'
        print '        data_nevents_LC2.push_back(nevents_LC2);'
        print '        data_nevents_LC3.push_back(nevents_LC3);'
        print '	ntuple->Fill(LC1,eff_LC1,eff_LC1_err,eff_LC2,eff_LC2_err,eff_LC3,eff_LC3_err,nevents_LC1,nevents_LC2,nevents_LC3);'
        print '	nlines++;'
        print '   }'
        print ''
        print '   in.close();'
        print '   '
        print '   TCanvas* c1 = new TCanvas("c1","gerrors2",200,10,700,500);'
        print '   TPad *pad = new TPad("pad","",0,0,1,1);'
        print '   //pad->SetFillColor(42);'
        print '   pad->SetGrid();'
        print '   pad->Draw();'
        print '   pad->cd();'
        print ''
        print '      // draw a frame to define the range'
        print '   TH1F *hr = pad->DrawFrame(0,-0.5,100,1.1);'
        print '   hr->SetXTitle("Detector Position (mm)");'
        print '   hr->SetYTitle("Efficiency");'
        print '   //pad->GetFrame()->SetFillColor(21);'
        print '   pad->GetFrame()->SetBorderSize(12);'
        print ''
        print '      // create first graph'
        print '   //gr1 = new TGraphErrors("data_error.dat","%lg %lg %lg");'
        print '   //TGraphErrors *gr1 = new TGraphErrors(data_LC1.size(),*data_LC1,*data_eff_LC1,*data_eff_LC1_err);'
        #print '   //TGraphErrors *gr1 = new TGraphErrors(data_LC1.size(),*data_LC1,*data_eff_LC1,*data_eff_LC1_err);   // Don't know why this is not working???'
        print '   TGraphErrors *gr1 = new TGraphErrors(data_LC1.size());'
        print '   TGraphErrors *gr3 = new TGraphErrors(data_LC1.size());'
        print '   TGraphErrors *gr4 = new TGraphErrors(data_LC1.size());'
        print '   cout<<"data size = "<<data_LC1.size()<<endl;'
        print '   for(unsigned int i=0;i<data_LC1.size();i++)'
        print '   {'
        print '       gr1->SetPoint(i,data_LC1[i],data_eff_LC1[i]);'
        print '       //gr1->SetPointError(i,0,data_eff_LC1_err[i]);'
        print ''
        print '       gr3->SetPoint(i,data_LC1[i],data_eff_LC2[i]);'
        print '       //gr3->SetPointError(i,0,data_eff_LC2_err[i]);'
        print ''
        print '       gr4->SetPoint(i,data_LC1[i],data_eff_LC3[i]);'
        print '       //gr4->SetPointError(i,0,data_eff_LC3_err[i]);'
        print '       /*'
        print '       gr1->SetPoint(i,data_LC1[i],data_eff_LC1[i]);'
        print '       gr1->SetPointError(i,0,data_eff_LC1_err[i]);'
        print ''
        print '       gr3->SetPoint(i,data_LC1[i],data_eff_LC2[i]);'
        print '       gr3->SetPointError(i,0,data_eff_LC2_err[i]);'
        print ''
        print '       gr4->SetPoint(i,data_LC1[i],data_eff_LC3[i]);'
        print '       gr4->SetPointError(i,0,data_eff_LC3_err[i]);'
        print '       */'
        print '   }'
        print '   gr1->SetMarkerColor(kBlue);'
        print '   gr1->SetLineColor(kBlue);'
        print '   gr1->SetMarkerStyle(21);'
        print '   gr1->GetXaxis()->SetTitle("dist (mm)");'
        print '   gr1->GetYaxis()->SetTitle("Efficiency");'
        print '   gr1->SetTitle("Efficiency Scan");'
        print '   gr1->Draw("ACP");'
        print '   gr3->SetMarkerColor(kGreen-6);'
        print '   gr3->SetLineColor(kGreen);'
        print '   gr3->SetMarkerStyle(21);'
        print '   gr3->Draw("sameCP");'
        print '   gr4->SetMarkerColor(kBlack);'
        print '   gr4->SetLineColor(kBlack);'
        print '   gr4->SetMarkerStyle(21);'
        print '   gr4->Draw("sameCP");'
        print ''
        print '   //create a transparent pad drawn on top of the main pad'
        print '   c1->cd();'
        print '   TPad *overlay = new TPad("overlay","",0,0,1,1);'
        print '   overlay->SetFillStyle(4000);'
        print '   overlay->SetFillColor(0);'
        print '   overlay->SetFrameFillStyle(4000);'
        print '   overlay->Draw();'
        print '   overlay->cd();'
        print '   // create second graph'
        print '   //TGraphErrors* gr2 = new TGraphErrors("data_noerror.dat","%lg %lg");'
        print '   TGraphErrors *gr2 = new TGraphErrors(data_LC1.size());'
        print '   TGraphErrors *gr5 = new TGraphErrors(data_LC1.size());'
        print '   TGraphErrors *gr6 = new TGraphErrors(data_LC1.size());'
        print ''
        print '   for(unsigned int i=0;i<data_LC1.size();i++)'
        print '   {'
        print '       gr2->SetPoint(i,data_LC1[i],data_nevents_LC1[i]);'
        print '       gr5->SetPoint(i,data_LC1[i],data_nevents_LC2[i]);'
        print '       gr6->SetPoint(i,data_LC1[i],data_nevents_LC3[i]);'
        print ''
        print '   }'
        print '   gr2->SetMarkerColor(kBlue);'
        print '   gr2->SetLineColor(kBlue);'
        print '   gr2->SetLineStyle(2);'
        print '   gr2->SetLineWidth(3);'
        print '   gr2->SetMarkerStyle(22);'
        print '   gr2->SetName("gr2");'
        print ''
        print '   gr5->SetMarkerColor(kGreen-6);'
        print '   gr5->SetLineColor(kGreen);'
        print '   gr5->SetMarkerStyle(22);'
        print '   gr5->SetLineStyle(2);'
        print '   gr5->SetLineWidth(3);'
        print '   gr5->SetName("gr5");'
        print ''
        print '   gr6->SetMarkerColor(kBlack);'
        print '   gr6->SetLineColor(kBlack);'
        print '   gr6->SetMarkerStyle(22);'
        print '   gr6->SetLineStyle(2);'
        print '   gr6->SetLineWidth(3);'
        print '   gr6->SetName("gr6");'
        print ''
        print '   Double_t xmin = pad->GetUxmin();'
        print '   Double_t ymin = 0;'
        print '   Double_t xmax = pad->GetUxmax();'
        print '   Double_t ymax = 1050;'
        print '   TH1F *hframe = overlay->DrawFrame(xmin,ymin,xmax,ymax);'
        print '   hframe->GetXaxis()->SetLabelOffset(99);'
        print '   hframe->GetYaxis()->SetLabelOffset(99);'
        print '   gr2->Draw("CP");'
        print '   gr5->Draw("CP");'
        print '   gr6->Draw("CP");'
        print ''
        print '   //Draw the Legend '
        print '   TLegend *leg = new TLegend(0.46,0.332,0.76,0.63);'
        print '   leg->AddEntry(gr1,"GE11_IV eff","LPE");'
        print '   leg->AddEntry(gr3,"GE11_IV_GIF eff","LPE");'
        print '   leg->AddEntry(gr4,"GE11_V eff","LPE");'
        print '   leg->AddEntry(gr2,"No of events_GE11_IV","LPE");'
        print '   leg->AddEntry(gr5,"No of events_GE11_IV_GIF","LPE");'
        print '   leg->AddEntry(gr6,"No of events_GE11_V","LPE");'
        print ''
        print '   leg->Draw("same");'
        print ''
        print '   TLatex *t2a = new TLatex(0.15,0.94," Run %i Ite %i"  );'%(b,a)
        print '   t2a->SetNDC();'
        print '   t2a->SetTextFont(42);'
        print '   t2a->SetTextSize(0.033);'
        print '   t2a->SetTextAlign(13);'
        print '   t2a->Draw("same");'
        print '   '
        print '   '
        print '   //Draw an axis on the right side'
        print '   TGaxis *axis = new TGaxis(xmax,ymin,xmax, ymax,ymin,ymax,510,"+L");'
        print '   axis->SetLineColor(kRed);'
        print '   axis->SetLabelColor(kRed);'
        print '   axis->SetTitle("Approx. No. of Events");'
        print ''
        print '   axis->Draw();'
        print ''
        print '   c1->SaveAs("GE11_Efficiency_Scan_%i_ite%i.pdf");'%(b,a)
        print '   c1->SaveAs("GE11_Efficiency_Scan_%i_ite%i.png");'%(b,a)
        print ''
        print '   c1->Write();'
        print '   f->Write();'
        print ''
        print '}'
        sys.stdout.close()
        os.system('root -l -b -q '+FileName+'.C')

