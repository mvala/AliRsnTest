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
   t1->SetParameters(1,2);
//   t1->UseRooFit(kFALSE);
   AliRsnTaskNSigma *t2 = new AliRsnTaskNSigma("nsig02","Test 2");
   t2->SetParameters(2,3);
   AliRsnTaskNSigma *t3 = new AliRsnTaskNSigma("nsig03","Test 3");
   t3->SetParameters(3,4);
   AliRsnTaskNSigma *t4 = new AliRsnTaskNSigma("nsig04","Test 4");
   t4->SetParameters(4,5);
   AliRsnTaskNSigma *t5 = new AliRsnTaskNSigma("nsig05","Test 5");
   t5->SetParameters(5,6);

   main->Add(t1);
   main->Add(t2);
   main->Add(t3);
   main->Add(t4);
   main->Add(t5);


   main->Print();

   main->ExecuteTask();

   return;

   TFile *f = TFile::Open("test.root","RECREATE");
   main->Write();
   f->Close();

   gROOT->GetListOfBrowsables()->Add(main,main->GetName());

   new TBrowser;
}
