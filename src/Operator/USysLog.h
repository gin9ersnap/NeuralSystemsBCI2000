//---------------------------------------------------------------------------

#ifndef USysLogH
#define USysLogH
//---------------------------------------------------------------------------

#include <ComCtrls.hpp>
#include <SyncObjs.hpp>

#define SYSLOGENTRYMODE_NORMAL  0
#define SYSLOGENTRYMODE_WARNING 1
#define SYSLOGENTRYMODE_ERROR   2

class SYSLOG
{
private:	// User declarations
        TForm       *form;
        TRichEdit   *log;
        TCriticalSection *critsec;
public:		// User declarations
        SYSLOG::SYSLOG();
        SYSLOG::~SYSLOG();
        void    SYSLOG::ShowSysLog();
        void    SYSLOG::AddSysLogEntry(char *text);
        void    SYSLOG::AddSysLogEntry(char *text, int mode);
};
#endif

