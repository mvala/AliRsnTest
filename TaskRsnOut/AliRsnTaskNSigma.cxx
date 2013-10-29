//
// *** Class AliRsnTaskNSigma ***
//
// Empty AliRsnTask
//
// authors: Martin Vala (martin.vala@cern.ch)
//

#include <TH2.h>
#include <TFile.h>
#include <TList.h>
#include <TSystem.h>
#include <TFolder.h>
#include <RooFit.h>
#include <RooRealVar.h>
#include <RooPlot.h>
#include <RooDataHist.h>
#include <RooGaussian.h>
#include <RooFitResult.h>

#include "AliRsnTaskNSigma.h"

ClassImp(AliRsnTaskNSigma)

//______________________________________________________________________________
AliRsnTaskNSigma::AliRsnTaskNSigma(const char *name, const char *title) :
      AliRsnTask(name, title), fUseRooFit(kTRUE)
{
   //
   // Defauult constructor
   //

   // We need that current task is executed after sub-tasks
   fExecTaskBefore = kFALSE;
}

//______________________________________________________________________________
AliRsnTaskNSigma::AliRsnTaskNSigma(const AliRsnTaskNSigma &copy) :
      AliRsnTask(copy), fUseRooFit(copy.fUseRooFit)
{
   //
   // Copy constructor
   //

}

//______________________________________________________________________________
AliRsnTaskNSigma &AliRsnTaskNSigma::operator=(const AliRsnTaskNSigma &copy)
{
   //
   // Assignment constructor
   //

   TTask::operator=(copy);
   if (this == &copy) return *this;
   fUseRooFit = copy.fUseRooFit;

   return (*this);
}

//______________________________________________________________________________
AliRsnTaskNSigma::~AliRsnTaskNSigma()
{
   //
   // Destructor
   //
}

void AliRsnTaskNSigma::Exec(Option_t* /*option*/)
{

   Printf("Testing Nsigma task");
   TFolder *folder = new TFolder("nsig", "Nsigma folder");
//   folder->Add(MyExec(1, 2));
   folder->Add(MyExec(2, 3));
//   folder->Add(MyExec(3, 4));
//   folder->Add(MyExec(4, 5));
//   folder->Add(MyExec(5, 6));
//   folder->Add(MyExec(6, 7));
//   folder->Add(MyExec(7, 8, 0.0));
//   folder->Add(MyExec(8, 9, 0.0));
   fParent->GetInput()->Add(folder);
//   folder = new TFolder("nsig2", "Nsigma folder");
//   folder->Add(MyExec(2, 3));
//   folder->Add(MyExec(3, 4));
//   folder->Add(MyExec(4, 5));
//   folder->Add(MyExec(5, 6));
//   fParent->GetInput()->Add(folder);
//
//   fParent->GetInput()->Add(MyExec(2, 3));
//   fParent->GetInput()->Add(MyExec(3, 4));
//   fParent->GetInput()->Add(MyExec(4, 5));
}

TObject* AliRsnTaskNSigma::MyExec(Int_t binf, Int_t binl, Double_t fitMin, Double_t fitMax, Double_t min, Double_t max)
{

   TFile::SetCacheFileDir(gSystem->HomeDirectory());
   const char *fn = "root://eos.saske.sk//eos/saske.sk/alice/rsn/PHIKK/LHC11a/ESD_pass4_without_SDD/RSN_20131015/Merged/All/STD2010/00_DEFAULT/qualityonly/RsnOutput.root";
   TFile* f = TFile::Open(fn, "CACHEREAD");
   f->ls();
   TList *l = (TList*) f->Get("ExtraInfo");

   TH2D *hNSigmaP = (TH2D*) l->FindObject("K_Phi_qualityonly_STD2010_PRIMARY_mon.TPC_nsigma_p_K");
   Double_t minVal = hNSigmaP->GetXaxis()->GetBinLowEdge(binf);
   Double_t maxVal = hNSigmaP->GetXaxis()->GetBinLowEdge(binl);


   TH1D *hNsigma = hNSigmaP->ProjectionY(TString::Format("[%.2f,%.2f]", minVal,maxVal).Data(), binf, binl);
   hNsigma->GetXaxis()->SetRangeUser(min, max);

   if (fUseRooFit) {
      using namespace RooFit;
      RooRealVar x("x", "x [nsigma]", min, max);
      RooRealVar mean("mean", "Mean", -1.0, 1.0);
      RooRealVar sigma("sigma", "Sigma", 0.0, 3.0);
      RooGaussian gauss("gauss", "Gauss PDF", x, mean, sigma);

      RooDataHist *data = new RooDataHist("hNsig", "Hist Nsigma", x, hNsigma);

//   RooFitResult *r = gauss.fitTo(*data, Range(fitMin, fitMax), Save());
      RooPlot *frame = x.frame();
      data->plotOn(frame,Name("data"));
//      mean = 0.0;
//      sigma = 1.0;
////      gauss.plotOn(frame, Range(-3, 3), LineColor(kRed),FillColor(kRed),FillStyle(3001),DrawOption("F"));
//      gauss.plotOn(frame, Range(-3, 3), LineColor(kRed));
//      gauss.fitTo(*data,Range(fitMin, fitMax),Extended());
      gauss.fitTo(*data,Range(fitMin, fitMax));
      gauss.plotOn(frame, Name("model"), Range(min, max));
      gauss.paramOn(frame, data);

      frame->Print();
      mean.Print();
      sigma.Print();
      x.Print();
      gauss.chi2FitTo(*data);

      frame->SetTitle(TString::Format("[%.2f,%.2f]", minVal,maxVal).Data());
//   r->Print();

//      Double_t chi2 = frame->chiSquare("gauss_Norm", "h_hNsig", 3);
//      Double_t chi2 = frame->chiSquare(2);
      Double_t chi2 = frame->chiSquare("model","data",2);
      Printf("Chi2 = %f", chi2);
      return frame;

   } else {
      hNsigma->Fit("gaus", "", "", fitMin, fitMax);
      return hNsigma;
   }

   return 0;
}
