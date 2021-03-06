////////////////////////////////////////////////////////////////////////////////
// $Id$
// Author: juergen.mellinger@uni-tuebingen.de
// Description: Implementation of bcierr and bciout message handlers for a
//              BCI2000 module.
//
// $BEGIN_BCI2000_LICENSE$
//
// This file is part of BCI2000, a platform for real-time bio-signal research.
// [ Copyright (C) 2000-2012: BCI2000 team and many external contributors ]
//
// BCI2000 is free software: you can redistribute it and/or modify it under the
// terms of the GNU General Public License as published by the Free Software
// Foundation, either version 3 of the License, or (at your option) any later
// version.
//
// BCI2000 is distributed in the hope that it will be useful, but
//                         WITHOUT ANY WARRANTY
// - without even the implied warranty of MERCHANTABILITY or FITNESS FOR
// A PARTICULAR PURPOSE.  See the GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License along with
// this program.  If not, see <http://www.gnu.org/licenses/>.
//
// $END_BCI2000_LICENSE$
////////////////////////////////////////////////////////////////////////////////
#include "BCIStream.h"
#include "MessageChannel.h"
#include "Status.h"
#include "FileUtils.h"
#include "EncodedString.h"
#include "ProcessUtils.h"
#include "RedirectIO.h"

using namespace std;

static MessageChannel* spChannel = NULL;

void
BCIStream::SetOutputChannel( MessageChannel* pChannel )
{
  spChannel = pChannel;
}

bool
BCIStream::CompressMessages()
{
  return true;
}

#if _WIN32
static void
ShowMessageBox( const string& inText, const string& inTitle, unsigned int inFlags )
{
  string executable = FileUtils::InstallationDirectory() + "MessageBox.exe";
  ostringstream args;
  args << EncodedString( inText ) << " " << EncodedString( inTitle ) << " " << inFlags;
  int resultCode;
  if( !ProcessUtils::ExecuteAsynchronously( executable, args.str(), resultCode ) )
    ::MessageBoxA( NULL, inText.c_str(), inTitle.c_str(), inFlags );
}
#endif // _WIN32

void
StatusMessage( const string& inText, int inCode )
{
  // If the connection to the operator does not work, fall back to a local
  // error display.
  if( spChannel )
  {
    spChannel->Output().clear();
    spChannel->Send( Status( inText, inCode ) );
  }
  if( !spChannel || !spChannel->Output() )
  {
    if( inCode >= 400 )
    {
# if !defined( _WIN32 ) || defined( __CONSOLE__ )
      Tiny::Cerr() << inText << endl;
# else
      ShowMessageBox( inText, "BCI2000 Error", MB_OK | MB_ICONHAND | MB_SYSTEMMODAL | MB_SETFOREGROUND );
# endif
    }
    else
    {
#if !defined( _WIN32 ) || defined( __CONSOLE__ )
      Tiny::Cout() << inText << endl;
#else
      ShowMessageBox( inText, "BCI2000", MB_OK | MB_ICONINFORMATION | MB_SYSTEMMODAL | MB_SETFOREGROUND );
#endif
    }
  }
}

void
BCIStream::DebugMessage( const string& s )
{
  StatusMessage( s, Status::debugMessage );
}

void
BCIStream::PlainMessage( const string& s )
{
  StatusMessage( s, Status::plainMessage );
}

void
BCIStream::Warning( const string& s )
{
  StatusMessage( s, Status::warningMessage );
}

void
BCIStream::ConfigurationError( const string& s )
{
  StatusMessage( s, Status::configurationError );
}

void
BCIStream::RuntimeError( const string& s )
{
  StatusMessage( s, Status::runtimeError );
}

void
BCIStream::LogicError( const string& s )
{
  StatusMessage( s, Status::logicError );
}

