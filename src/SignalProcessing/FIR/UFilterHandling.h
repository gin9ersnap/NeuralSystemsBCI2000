//---------------------------------------------------------------------------

#ifndef UFilterHandlingH
#define UFilterHandlingH
//---------------------------------------------------------------------------

#include <Scktcomp.hpp>

#include "CalibrationFilter.h"
#include "SpatialFilter.h"
#include "FIRFilter.h"
#include "FIRClassFilter.h"
#include "NormalFilter.h"
#include "FIRStatFilter.h"

class FILTERS
{
protected:
       GenericSignal *CreateGenericSignal(int transmitchannels, int samples, char *buf);
       int  MA, MB, MC, MD, ME, MF;  // spatial dimensions of the signals
       int NA, NB, NC, ND, NE, NF;   // temporal dimensions of the signals
public:
       FILTERS(PARAMLIST *ParamList, STATELIST *StateList);
       ~FILTERS();
       int      Initialize(PARAMLIST *plist, STATEVECTOR *svector, CORECOMM *);
       int      Process(char *buf);
       int      Resting(char *buf);
       bool     was_error;
       CalibrationFilter  *calfilter;
       SpatialFilter      *spatfilter;
       FIRFilter          *tempfilter;
       FIRClassFilter     *classfilter;
       NormalFilter       *normalfilter;
       FIRStatFilter      *statfilter;
       GenericSignal  *SignalA, *SignalB, *SignalC, *SignalD, *SignalE, *SignalF;
};
#endif
