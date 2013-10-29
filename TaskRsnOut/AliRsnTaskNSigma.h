//
// *** Class AliRsnTaskNSigma ***
//
//  Empty AliRsnTask
//
// authors: Martin Vala (martin.vala@cern.ch)
//

#ifndef ALIRSNTASKNSIGMA_H
#define ALIRSNTASKNSIGMA_H

#include <Rtypes.h>
#include "AliRsnTask.h"

class AliRsnTaskNSigma : public AliRsnTask
{
public:

   AliRsnTaskNSigma(const char *name="empty", const char *title="Empty Task");
   AliRsnTaskNSigma(const AliRsnTaskNSigma &copy);
   AliRsnTaskNSigma &operator=(const AliRsnTaskNSigma &copy);
   virtual ~AliRsnTaskNSigma();

   virtual void   Exec(Option_t *option);

   void UseRooFit(Bool_t useRooFit=kTRUE) { fUseRooFit = useRooFit;}
   TObject *MyExec(Int_t binf = 1, Int_t binl = 2, Double_t fitMin = -2.0, Double_t fitMax = 2.0, Double_t min = -4.0, Double_t max = 4.0);

private:

   Bool_t fUseRooFit;

   ClassDef(AliRsnTaskNSigma, 1)
};

#endif
