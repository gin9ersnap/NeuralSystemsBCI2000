#include "PCHIncludes.h"
#pragma hdrstop
#include <vcl.h>
//---------------------------------------------------------------------------
USEFORM("..\UMain.cpp", fMain);
USEFORM("..\..\shared\UVisConfig.cpp", fVisConfig);
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
        try
        {
                 Application->Initialize();
                 Application->Title = "MXSignalProcessing";
                 Application->CreateForm(__classid(TfMain), &fMain);
         Application->CreateForm(__classid(TfVisConfig), &fVisConfig);
         Application->Run();
        }
        catch (Exception &exception)
        {
                 Application->ShowException(&exception);
        }
        return 0;
}
//---------------------------------------------------------------------------
