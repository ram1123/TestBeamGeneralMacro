#include "TCanvas.h"
#include "TFrame.h"
#include "TBenchmark.h"
#include "TString.h"
#include "TF1.h"
#include "TH1.h"
#include "TFile.h"
#include "TROOT.h"
#include "TError.h"
#include "TInterpreter.h"
#include "TSystem.h"
#include "TPaveText.h"
#include <cstdio>
#include <cmath>

void GraphReader()
{
TFile *f = new TFile("ram3.root");
f->cd("Comp_GE11_IV_Gas_Comparison/timeResp");
f->pwd();
TList *l = mGraph_Comp_GE11_IV_Gas_Comparison_canvas_Comp_GE11_IV_Gas_Comparison_timeResp-> GetListOfGraphs();
  Int_t n = l->GetSize();
   printf("Number of Graphs: %d\n", n);
	
  fstream plik("values.txt", std::fstream::out);
Double_t *x, *y, *ex, *ey;
   Int_t np;
   TGraph *g = (TGraph*)l->First();
   for (Int_t i = 0; i < n; i++) {
      x  = g->GetX();
      y  = g->GetY();
     ey = g ->GetEY();
     ex = g ->GetEX();
      np = g->GetN();
      printf("\n---\n The Points in the graph number %d are:\n",i);
      for (Int_t j=0; j<np; j++) 
      {
         printf("  x[%d] = %g y[%d] =  %g ex[%d] = %g ey[%d] = %g\n", j,x[j],j,y[j],ex[j],ey[j]);
         plik<<x[j]<<"\t"<<y[j]<<"\t"<<ex[j]<<"\t"<<ey[j]<<std::endl;
      }
      g = (TGraph*)l->After(g);
   }

}

