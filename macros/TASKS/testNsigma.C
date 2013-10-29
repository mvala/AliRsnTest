#ifndef __CINT__
#include <TString.h>
#include <TFile.h>
#include <TROOT.h>
#include <TBrowser.h>
#include <AliRsnTask.h>
#include <AliRsnTaskCanvas.h>
#include <AliRsnTaskNSigma.h>
#endif

void testNsigma()
{
   Printf("Starting test ...");
   AliRsnTaskCanvas *main = new AliRsnTaskCanvas("MainCanvas","Main Canvas");

   AliRsnTaskNSigma *t1 = new AliRsnTaskNSigma("nsig01","Test 1");
//   t1->UseRooFit(kFALSE);
   main->Add(t1);

   main->Print();

   main->ExecuteTask();

   return;

   TFile *f = TFile::Open("test.root","RECREATE");
   main->Write();
   f->Close();

   gROOT->GetListOfBrowsables()->Add(main,main->GetName());

   new TBrowser;
}
