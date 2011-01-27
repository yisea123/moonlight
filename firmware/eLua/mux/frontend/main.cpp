// -*- C++ -*- generated by wxGlade 0.6.3 on Sun Feb 28 15:10:07 2010

#include <wx/wx.h>
#include <wx/image.h>
#include <wx/debug.h>
#include "MuxFrontendDialog.h"
#include "ListPorts.h"
#include "wxs.h"

// A struct to convert from pointer to chars to wxstrings, too lazy to edit listports.c
struct PortInfo
{
  wxString PortName;
  wxString FriendlyName;
  wxString Technology;
  
  PortInfo( LISTPORTS_PORTINFO* pInfo ):
    PortName( pInfo->lpPortName ),
    FriendlyName( pInfo->lpFriendlyName ),
    Technology( pInfo->lpTechnology ) {}
};

class MuxFrontendApp: public wxApp {
public:
    bool OnInit();
};

IMPLEMENT_APP(MuxFrontendApp)         

DEFINE_EVENT_TYPE( wxEVT_TEXTCTRL_DATA )                   

#ifdef WIN32_BUILD
// Serial enumeration callback
extern "C" BOOL CALLBACK ser_callback( LPVOID lpCallbackValue, LISTPORTS_PORTINFO* lpPortInfo )
{
  wxArrayString* ports = ( wxArrayString* )lpCallbackValue;
  ports->Add( wxString( lpPortInfo->lpPortName ) );
  return TRUE;
}
#endif

bool MuxFrontendApp::OnInit()
{
  wxInitAllImageHandlers();
    
  // List all serial ports in the system
  wxArrayString ports;
#ifdef WIN32_BUILD
  ListPorts( ser_callback, &ports );
#endif    
  if( ports.GetCount() == 0 )
  {
    wxMessageBox( _( "Unable to find a serial port" ), _( "Error" ) );
    return false;
  }
    
  MuxFrontendDialog dialog_fe( NULL, wxID_ANY, wxEmptyString, ports );
  //SetTopWindow(dialog_fe);
  dialog_fe.ShowModal();
  return false;
}
