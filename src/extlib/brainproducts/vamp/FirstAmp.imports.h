// Import declarations for FirstAmp.h, generated by dylib_imports.sh
#ifndef FirstAmp_IMPORTS_H
#define FirstAmp_IMPORTS_H

#include "Win32Defs.h"

#if DYNAMIC_IMPORTS
#define faGetCount faGetCount_630b
#define faGetId faGetId_7670
#define faOpen faOpen_3b69
#define faClose faClose_2294
#define faStart faStart_ed0a
#define faStop faStop_aca1
#define faGetData faGetData_6eb1
#define faGetInformation faGetInformation_292a
#define faGetProperty faGetProperty_d897
#define faStartImpedance faStartImpedance_d4e3
#define faStopImpedance faStopImpedance_9fcc
#define faGetImpedance faGetImpedance_17c0
#define faStartCalibration faStartCalibration_48ce
#define faStopCalibration faStopCalibration_888e
#define faGetIo faGetIo_602e
#define faSetIo faSetIo_0708
#define faSetBitmap faSetBitmap_8004
#define faGetContrast faGetContrast_0aa0
#define faSetContrast faSetContrast_0dfb
#define faGetBrightness faGetBrightness_7cf9
#define faSetBrightness faSetBrightness_2857
#define faGetUserData faGetUserData_5e28
#define faSetUserData faSetUserData_3233
#define faGetDataState faGetDataState_22e2
#define faGetDataMode faGetDataMode_af2d
#define faSetDataMode faSetDataMode_ba21
#endif // DYNAMIC_IMPORTS

#include "FirstAmp.h"

#if DYNAMIC_IMPORTS
#undef faGetCount
#undef faGetId
#undef faOpen
#undef faClose
#undef faStart
#undef faStop
#undef faGetData
#undef faGetInformation
#undef faGetProperty
#undef faStartImpedance
#undef faStopImpedance
#undef faGetImpedance
#undef faStartCalibration
#undef faStopCalibration
#undef faGetIo
#undef faSetIo
#undef faSetBitmap
#undef faGetContrast
#undef faSetContrast
#undef faGetBrightness
#undef faSetBrightness
#undef faGetUserData
#undef faSetUserData
#undef faGetDataState
#undef faGetDataMode
#undef faSetDataMode

extern "C" {
extern unsigned int (__stdcall *faGetCount)(void);
extern int (__stdcall *faGetId)(unsigned int Number);
extern int (__stdcall *faOpen)(int Id);
extern int (__stdcall *faClose)(int Id);
extern int (__stdcall *faStart)(int Id);
extern int (__stdcall *faStop)(int Id);
extern int (__stdcall *faGetData)(int Id, void *Buffer, unsigned int Size);
extern int (__stdcall *faGetInformation)(int Id, t_faInformation *Information);
extern int (__stdcall *faGetProperty)(int Id, t_faProperty *Property);
extern int (__stdcall *faStartImpedance)(int Id);
extern int (__stdcall *faStopImpedance)(int Id);
extern int (__stdcall *faGetImpedance)(int Id, unsigned int *Buffer, unsigned int Size);
extern int (__stdcall *faStartCalibration)(int Id);
extern int (__stdcall *faStopCalibration)(int Id);
extern int (__stdcall *faGetIo)(int Id, t_faIo *Io);
extern int (__stdcall *faSetIo)(int Id, t_faIo *Io);
extern int (__stdcall *faSetBitmap)(int Id, HBITMAP Bitmap);
extern int (__stdcall *faGetContrast)(int Id, unsigned int *Contrast);
extern int (__stdcall *faSetContrast)(int Id, unsigned int Contrast);
extern int (__stdcall *faGetBrightness)(int Id, unsigned int *Brightness);
extern int (__stdcall *faSetBrightness)(int Id, unsigned int Brightness);
extern int (__stdcall *faGetUserData)(int Id, void *Buffer, unsigned int Size,   unsigned int *Count);
extern int (__stdcall *faSetUserData)(int Id, void *Buffer, unsigned int Size,   unsigned int *Count);
extern int (__stdcall *faGetDataState)(int Id, t_faDataState *DataState);
extern int (__stdcall *faGetDataMode)(int Id, t_faDataMode *Mode,   t_faDataModeSettings *Settings);
extern int (__stdcall *faSetDataMode)(int Id, t_faDataMode Mode,   t_faDataModeSettings *Settings);
}
#endif // DYNAMIC_IMPORTS

namespace Dylib { bool FirstAmp_Loaded(); }

#endif // FirstAmp_IMPORTS_H
