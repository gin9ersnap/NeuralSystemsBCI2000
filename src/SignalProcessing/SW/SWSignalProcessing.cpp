//---------------------------------------------------------------------------
#include "PCHIncludes.h"
#pragma hdrstop
#include <vcl.h>
USEFORM("..\UMain.cpp", fMain);
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
        try
        {
                 Application->Initialize();
                 Application->Title = "SignalProcessing";
                 Application->CreateForm(__classid(TfMain), &fMain);
         Application->Run();
        }
        catch (Exception &exception)
        {
                 Application->ShowException(&exception);
        }
        return 0;
}
//---------------------------------------------------------------------------
