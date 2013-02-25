// Import definitions for FirstAmp.h, generated by dylib_imports.sh
#include "FirstAmp.imports.h"
#include "DylibImports.h"

#if !DYNAMIC_IMPORTS

namespace Dylib { bool FirstAmp_Loaded() { return true; } }

#else // DYNAMIC_IMPORTS

extern "C" {
unsigned int (__stdcall *faGetCount)(void) = 0;
int (__stdcall *faGetId)(unsigned int Number) = 0;
int (__stdcall *faOpen)(int Id) = 0;
int (__stdcall *faClose)(int Id) = 0;
int (__stdcall *faStart)(int Id) = 0;
int (__stdcall *faStop)(int Id) = 0;
int (__stdcall *faGetData)(int Id, void *Buffer, unsigned int Size) = 0;
int (__stdcall *faGetInformation)(int Id, t_faInformation *Information) = 0;
int (__stdcall *faGetProperty)(int Id, t_faProperty *Property) = 0;
int (__stdcall *faStartImpedance)(int Id) = 0;
int (__stdcall *faStopImpedance)(int Id) = 0;
int (__stdcall *faGetImpedance)(int Id, unsigned int *Buffer, unsigned int Size) = 0;
int (__stdcall *faStartCalibration)(int Id) = 0;
int (__stdcall *faStopCalibration)(int Id) = 0;
int (__stdcall *faGetIo)(int Id, t_faIo *Io) = 0;
int (__stdcall *faSetIo)(int Id, t_faIo *Io) = 0;
int (__stdcall *faSetBitmap)(int Id, HBITMAP Bitmap) = 0;
int (__stdcall *faGetContrast)(int Id, unsigned int *Contrast) = 0;
int (__stdcall *faSetContrast)(int Id, unsigned int Contrast) = 0;
int (__stdcall *faGetBrightness)(int Id, unsigned int *Brightness) = 0;
int (__stdcall *faSetBrightness)(int Id, unsigned int Brightness) = 0;
int (__stdcall *faGetUserData)(int Id, void *Buffer, unsigned int Size,   unsigned int *Count) = 0;
int (__stdcall *faSetUserData)(int Id, void *Buffer, unsigned int Size,   unsigned int *Count) = 0;
int (__stdcall *faGetDataState)(int Id, t_faDataState *DataState) = 0;
int (__stdcall *faGetDataMode)(int Id, t_faDataMode *Mode,   t_faDataModeSettings *Settings) = 0;
int (__stdcall *faSetDataMode)(int Id, t_faDataMode Mode,   t_faDataModeSettings *Settings) = 0;
}

static const Dylib::Import imports[] =
{
  { "faGetCount", (void**)&faGetCount, Dylib::Import::cMangled },
  { "faGetId", (void**)&faGetId, Dylib::Import::cMangled },
  { "faOpen", (void**)&faOpen, Dylib::Import::cMangled },
  { "faClose", (void**)&faClose, Dylib::Import::cMangled },
  { "faStart", (void**)&faStart, Dylib::Import::cMangled },
  { "faStop", (void**)&faStop, Dylib::Import::cMangled },
  { "faGetData", (void**)&faGetData, Dylib::Import::cMangled },
  { "faGetInformation", (void**)&faGetInformation, Dylib::Import::cMangled },
  { "faGetProperty", (void**)&faGetProperty, Dylib::Import::cMangled },
  { "faStartImpedance", (void**)&faStartImpedance, Dylib::Import::cMangled },
  { "faStopImpedance", (void**)&faStopImpedance, Dylib::Import::cMangled },
  { "faGetImpedance", (void**)&faGetImpedance, Dylib::Import::cMangled },
  { "faStartCalibration", (void**)&faStartCalibration, Dylib::Import::cMangled },
  { "faStopCalibration", (void**)&faStopCalibration, Dylib::Import::cMangled },
  { "faGetIo", (void**)&faGetIo, Dylib::Import::cMangled },
  { "faSetIo", (void**)&faSetIo, Dylib::Import::cMangled },
  { "faSetBitmap", (void**)&faSetBitmap, Dylib::Import::cMangled },
  { "faGetContrast", (void**)&faGetContrast, Dylib::Import::cMangled },
  { "faSetContrast", (void**)&faSetContrast, Dylib::Import::cMangled },
  { "faGetBrightness", (void**)&faGetBrightness, Dylib::Import::cMangled },
  { "faSetBrightness", (void**)&faSetBrightness, Dylib::Import::cMangled },
  { "faGetUserData", (void**)&faGetUserData, Dylib::Import::cMangled },
  { "faSetUserData", (void**)&faSetUserData, Dylib::Import::cMangled },
  { "faGetDataState", (void**)&faGetDataState, Dylib::Import::cMangled },
  { "faGetDataMode", (void**)&faGetDataMode, Dylib::Import::cMangled },
  { "faSetDataMode", (void**)&faSetDataMode, Dylib::Import::cMangled },
  { 0, 0, 0 }
};

// Here you may specify a custom error message to be displayed when the library cannot be found.
static const char* notFoundMsg = "";
// Here you may specify an URL to some local or remote help resource.
static const char* notFoundURL = "";
RegisterDylib( FirstAmp, imports, notFoundMsg, notFoundURL );

#endif // DYNAMIC_IMPORTS
