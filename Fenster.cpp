#include "Fenster.h"
#include "Text.h"
#include "MausEreignis.h"
#include "TastaturEreignis.h"
#include "Bildschirm.h"
#include "AlphaFeld.h"
#include "Bild.h"
#include "Rahmen.h"
#include "TextFeld.h"
#include "Scroll.h"
#include "Maus.h"
#include "ToolTip.h"
#include "Globals.h"

using namespace Framework;

// Fensterklasse erzeugen
WNDCLASS Framework::F_Normal( HINSTANCE hInst )// Erzeugen einer normalen Fensterklasse
{
	WNDCLASS ret;
	ret.cbClsExtra = 0;
	ret.cbWndExtra = 0;
	ret.hbrBackground = (HBRUSH)GetStockObject( WHITE_BRUSH );
	ret.hCursor = LoadCursor( NULL, IDC_ARROW );
	ret.hIcon = LoadIcon( NULL, IDI_APPLICATION );
	ret.hInstance = hInst;
	ret.lpszMenuName = "";
	ret.lpfnWndProc = WindowProc;
	ret.style = CS_HREDRAW | CS_VREDRAW;
	return ret;
}

WNDCLASSEX Framework::F_NormalEx( HINSTANCE hInst )
{
	WNDCLASSEX ret;
	ret.cbSize = sizeof( WNDCLASSEX );
	ret.cbClsExtra = 0;
	ret.cbWndExtra = 0;
	ret.hbrBackground = (HBRUSH)GetStockObject( WHITE_BRUSH );
	ret.hCursor = LoadCursor( NULL, IDC_ARROW );
	ret.hIcon = LoadIcon( NULL, IDI_APPLICATION );
	ret.hInstance = hInst;
	ret.lpszMenuName = "";
	ret.lpfnWndProc = WindowProc;
	ret.style = CS_HREDRAW | CS_VREDRAW;
	ret.hIconSm = 0;
	return ret;
}

// WinAPI
LRESULT CALLBACK Framework::WindowProc( HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam )
{
	if( msgExit )
		return ( DefWindowProc( hwnd, message, wparam, lparam ) );
	switch( message )
	{
		// Maus Zeiger 
	case WM_SETCURSOR:
		MausZeiger.update();
		return 0;
		// Fenster 
	case WM_SIZE:
		if( wparam == SIZE_RESTORED )
			WFensterA.sendRestoreMessage( hwnd );
		break;
		// Schlie�en 
	case WM_CLOSE:
		if( WFensterA.sendVSchlie�Message( hwnd ) )
			return 0;
		else
			break;
	case WM_DESTROY:
		if( WFensterA.sendNSchlie�Message( hwnd ) )
			return 0;
		else
			break;
		// Maus 
	case WM_LBUTTONDOWN: // Linksklick
		if( 1 )
		{
			MausStand[ M_Links ] = 1;
			MausEreignis me = { ME_PLinks, (int)LOWORD( lparam ), (int)HIWORD( lparam ), 0, 0, 0 };
			me.rmx = me.mx;
			me.rmy = me.my;
			WFensterA.sendMausMessage( hwnd, me );
			break;
		}
	case WM_RBUTTONDOWN: // Rechtsklick
		if( 1 )
		{
			MausStand[ M_Rechts ] = 1;
			MausEreignis me = { ME_PRechts, (int)LOWORD( lparam ), (int)HIWORD( lparam ), 0, 0, 0 };
			me.rmx = me.mx;
			me.rmy = me.my;
			WFensterA.sendMausMessage( hwnd, me );
			break;
		}
	case WM_MBUTTONDOWN: // Mittelklick
		if( 1 )
		{
			MausStand[ M_Mitte ] = 1;
			MausEreignis me = { ME_PMitte, (int)LOWORD( lparam ), (int)HIWORD( lparam ), 0, 0, 0 };
			me.rmx = me.mx;
			me.rmy = me.my;
			WFensterA.sendMausMessage( hwnd, me );
			break;
		}
	case WM_LBUTTONUP: // Linksrelease
		if( 1 )
		{
			MausStand[ M_Links ] = 0;
			MausEreignis me = { ME_RLinks, (int)LOWORD( lparam ), (int)HIWORD( lparam ), 0, 0, 0 };
			me.rmx = me.mx;
			me.rmy = me.my;
			WFensterA.sendMausMessage( hwnd, me );
			break;
		}
	case WM_RBUTTONUP: // Rechtsrelease
		if( 1 )
		{
			MausStand[ M_Rechts ] = 0;
			MausEreignis me = { ME_RRechts, (int)LOWORD( lparam ), (int)HIWORD( lparam ), 0, 0, 0 };
			me.rmx = me.mx;
			me.rmy = me.my;
			WFensterA.sendMausMessage( hwnd, me );
			break;
		}
	case WM_MBUTTONUP: // Mittelrelease
		if( 1 )
		{
			MausStand[ M_Mitte ] = 0;
			MausEreignis me = { ME_RMitte, (int)LOWORD( lparam ), (int)HIWORD( lparam ), 0, 0, 0 };
			me.rmx = me.mx;
			me.rmy = me.my;
			WFensterA.sendMausMessage( hwnd, me );
			break;
		}
	case WM_LBUTTONDBLCLK: // Linksdoppelklick
		if( 1 )
		{
			MausEreignis me = { ME_DKLinks, (int)LOWORD( lparam ), (int)HIWORD( lparam ), 0, 0, 0 };
			me.rmx = me.mx;
			me.rmy = me.my;
			WFensterA.sendMausMessage( hwnd, me );
			break;
		}
	case WM_RBUTTONDBLCLK: // Rechtsdoppelklick
		if( 1 )
		{
			MausEreignis me = { ME_DKRechts, (int)LOWORD( lparam ), (int)HIWORD( lparam ), 0, 0, 0 };
			me.rmx = me.mx;
			me.rmy = me.my;
			WFensterA.sendMausMessage( hwnd, me );
			break;
		}
	case WM_MBUTTONDBLCLK: // Mitteldoppelklick
		if( 1 )
		{
			MausEreignis me = { ME_DKMitte, (int)LOWORD( lparam ), (int)HIWORD( lparam ), 0, 0, 0 };
			me.rmx = me.mx;
			me.rmy = me.my;
			WFensterA.sendMausMessage( hwnd, me );
			break;
		}
	case WM_MOUSEHOVER: // Maus betritt Fenster
		if( 1 )
		{
			MausTrack = 1;
			MausEreignis me = { ME_Betritt, (int)LOWORD( lparam ), (int)HIWORD( lparam ), 0, 0, 0 };
			me.rmx = me.mx;
			me.rmy = me.my;
			WFensterA.sendMausMessage( hwnd, me );
			break;
		}
	case WM_MOUSELEAVE: // Maus verl�sst Fenster
		if( 1 )
		{
			MausTrack = 1;
			MausEreignis me = { ME_Verl�sst, (int)LOWORD( lparam ), (int)HIWORD( lparam ), 0, 0, 0 };
			me.rmx = me.mx;
			me.rmy = me.my;
			WFensterA.sendMausMessage( hwnd, me );
			break;
		}
	case WM_MOUSEMOVE: // Maus wird bewegt
		if( 1 )
		{
			if( mausPos.x == (int)LOWORD( lparam ) && mausPos.y == (int)HIWORD( lparam ) )
				break;
			mausPos.x = (int)LOWORD( lparam );
			mausPos.y = (int)HIWORD( lparam );
			if( MausTrack )
			{
				TRACKMOUSEEVENT lptme;
				lptme.cbSize = sizeof( TRACKMOUSEEVENT );
				lptme.dwFlags = TME_HOVER | TME_LEAVE;
				lptme.dwHoverTime = 0;
				lptme.hwndTrack = hwnd;
				TrackMouseEvent( &lptme );
				MausTrack = 0;
			}
			MausEreignis me = { ME_Bewegung, mausPos.x, mausPos.y, 0, 0, 0 };
			me.rmx = me.mx;
			me.rmy = me.my;
			WFensterA.sendMausMessage( hwnd, me );
			break;
		}
	case WM_MOUSEWHEEL: // Maus scroll
		if( 1 )
		{
			MausEreignis me = { 0, mausPos.x, mausPos.y, 0, 0, 0 };
			if( (int)(short)HIWORD( wparam ) < 0 )
				me.id = !getTastenStand( T_Shift ) ? ME_DScroll : ME_RScroll;
			else
				me.id = !getTastenStand( T_Shift ) ? ME_UScroll : ME_LScroll;
			me.rmx = me.mx;
			me.rmy = me.my;
			WFensterA.sendMausMessage( hwnd, me );
			break;
		}
		// Tastatur 
	case WM_KEYDOWN:
		if( 1 )
		{
			TastaturEreignis te = { TE_Press, VirtualZuChar( (int)wparam ), 0 };
			if( te.taste == T_Alt_Gr )
				TastenStand[ T_Strg ] = 0;
			TastenStand[ te.taste ] = 1;
			WFensterA.sendTastaturMessage( hwnd, te );
			break;
		} // Taste wird gedr�ckt
	case WM_KEYUP:
		if( 1 )
		{
			TastaturEreignis te = { TE_Release, VirtualZuChar( (int)wparam ), 0 };
			TastenStand[ te.taste ] = 0;
			WFensterA.sendTastaturMessage( hwnd, te );
			break;
		} // Taste wird losgelassen
	}
	return ( DefWindowProc( hwnd, message, wparam, lparam ) );
}

void Framework::StartNachrichtenSchleife()
{
	MSG msg;
	while( GetMessage( &msg, NULL, 0, 0 ) > 0 && !msgExit )
	{
		if( !msgExit )
		{
			TranslateMessage( &msg );
			DispatchMessage( &msg );
		}
	}
	msgExit = 0;
}

void Framework::StopNachrichtenSchleife( HWND hwnd )
{
	msgExit = 1;
	PostMessage( hwnd, WM_MOUSELEAVE, 0, 0 );
}

unsigned char Framework::VirtualZuChar( int Virtual )
{
	UINT vk = MapVirtualKey( Virtual, 2 );
	if( !vk )
	{
		switch( Virtual )
		{
		case VK_CAPITAL:
			return T_Caps_Lock;
		case VK_SHIFT:
			return T_Shift;
		case VK_CONTROL:
			return T_Strg;
		case VK_F1:
			return T_F1;
		case VK_F2:
			return T_F2;
		case VK_F3:
			return T_F3;
		case VK_F4:
			return T_F4;
		case VK_F5:
			return T_F5;
		case VK_F6:
			return T_F6;
		case VK_F7:
			return T_F7;
		case VK_F8:
			return T_F8;
		case VK_F9:
			return T_F9;
		case VK_F10:
			return T_F10;
		case VK_F11:
			return T_F11;
		case VK_F12:
			return T_F12;
		case VK_PAUSE:
			return T_Pause;
		case VK_SNAPSHOT:
			return T_Druck;
		case VK_INSERT:
			return T_Einfg;
		case VK_DELETE:
			return T_Entf;
		case VK_LEFT:
			return T_Links;
		case VK_UP:
			return T_Oben;
		case VK_RIGHT:
			return T_Rechts;
		case VK_DOWN:
			return T_Unten;
		case VK_MENU:
			return T_Alt_Gr;
		case VK_NUMLOCK:
			return T_Num;
		case VK_HOME:
			return T_Pos1;
		case VK_PRIOR:
			return T_BildO;
		case VK_NEXT:
			return T_BildU;
		case VK_END:
			return T_Ende;
		case VK_TAB:
			return T_Tab;
		}
	}
	if( vk == VK_TAB )
		return T_Tab;
	char ret = (char)(short)LOWORD( vk );
	short SHIFT = GetKeyState( VK_SHIFT );
	short CAPSLOCK = GetKeyState( VK_CAPITAL );
	short ALTGR = TastenStand[ T_Alt_Gr ];
	if( ALTGR )
	{
		switch( ret )
		{
		case 'q':
			return '@';
		case 'Q':
			return '@';
		case '<':
			return '|';
		case '>':
			return '|';
		case '7':
			return '{';
		case '/':
			return '{';
		case '8':
			return '[';
		case '(':
			return '[';
		case '9':
			return ']';
		case ')':
			return ']';
		case '0':
			return '}';
		case '=':
			return '}';
		case '�':
			return '\\';
		case '?':
			return '\\';
		case '+':
			return '~';
		case '*':
			return '~';
		case 'e':
			return '�';
		case 'E':
			return '�';
		case 'm':
			return '�';
		case 'M':
			return '�';
		case '2':
			return '�';
		case '"':
			return '�';
		case '3':
			return '�';
		case '�':
			return '�';
		}
	}
	SHIFT = HIWORD( SHIFT );
	CAPSLOCK = LOWORD( CAPSLOCK );
	bool up = 0;
	if( SHIFT && !CAPSLOCK )
		up = 1;
	if( CAPSLOCK && !SHIFT )
		up = 1;
	ret = KleinOrGro�( ret, up );
	return ret;
}

// Inhalt der WFenster Klasse aus Fenster.h
// Konstruktor 
WFenster::WFenster()
	: hWnd( 0 ),
	  style( 0 ),
	  makParam( 0 ),
	  sakParam( 0 ),
	  takParam( 0 ),
	  MausAktion( 0 ),
	  VSchlie�Aktion( 0 ),
	  NSchlie�Aktion( 0 ),
	  TastaturAktion( 0 ),
	  screen( 0 ),
	  mx( -1 ),
	  my( -1 ),
	  verschiebbar( 0 ),
	  ref( 1 ),
	  rahmen( 0 ),
	  bitmap( 0 ),
	  hdc( 0 )
{
	WFensterA.addFenster( this );
}

WFenster::WFenster( HWND hwnd )
	: WFenster()
{
	hWnd = hwnd;
}

// Destruktor 
WFenster::~WFenster()
{
	if( WFensterA.removeFenster( this ) )
	{
		WFensterA.del();
	}
    if( hWnd )
        zerst�ren();
	if( screen )
		screen->release();
}

// nicht constant 
void WFenster::erstellen( int style, WNDCLASS wc ) // Erstellt ein Fenster in Windows
{
	if( !GetClassInfo( wc.hInstance, wc.lpszClassName, &wc ) )
	{
#pragma warning(suppress: 6102)
		if( !RegisterClass( &wc ) ) // Register Fensterklasse
		{
			MessageBox( hWnd, "Fehler beim Registrieren der Fensterklasse!", "Error", MB_ICONERROR ); // Fehlermeldung bei Fehler
			return;
		}
	}

	hWnd = CreateWindow( wc.lpszClassName, wc.lpszClassName, style, 0, 0, 0, 0, 0, 0, wc.hInstance, 0 ); // Fenster Erstellen

	if( hWnd == 0 )
	{
		MessageBox( hWnd, "Fehler beim erstellen des Fensters!", "Error", MB_ICONERROR ); // Fehlermeldung bei Fehler
		return;
	}
	this->style = style;
}

void WFenster::erstellenEx( int exStyle, int style, WNDCLASSEX wc ) // Das Fenster Erstellen
{
	if( !GetClassInfoEx( wc.hInstance, wc.lpszClassName, &wc ) )
	{
#pragma warning(suppress: 6102)
		if( !RegisterClassEx( &wc ) ) // Register Fensterklasse
		{
			MessageBox( hWnd, "Fehler beim Registrieren der Fensterklasse!", "Error", MB_ICONERROR ); // Fehlermeldung bei Fehler
			return;
		}
	}

	hWnd = CreateWindowEx( exStyle, wc.lpszClassName, wc.lpszClassName, style, 0, 0, 0, 0, 0, 0, wc.hInstance, 0 ); // Fenster Erstellen

	if( hWnd == 0 )
	{
		MessageBox( hWnd, "Fehler beim erstellen des Fensters!", "Error", MB_ICONERROR ); // Fehlermeldung bei Fehler
		return;
	}
	this->style = style;
}

void WFenster::setAnzeigeModus( int mod )// Fenster Anzeigen
{
	if( rahmen )
	{
		if( mod == 2 )
			ShowWindow( rahmen, 0 );
		else
			ShowWindow( rahmen, mod );
	}
	ShowWindow( hWnd, mod );
}

bool WFenster::setFokus() // Setzt den Fokus auf das Fenster
{
	DWORD dwCurrentThread = GetCurrentThreadId();
	DWORD dwFGThread = GetWindowThreadProcessId( GetForegroundWindow(), NULL );
	AttachThreadInput( dwCurrentThread, dwFGThread, TRUE );
	SetFocus( hWnd );
	AttachThreadInput( dwCurrentThread, dwFGThread, FALSE );
	SetWindowPos( hWnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_SHOWWINDOW );
	SetWindowPos( hWnd, HWND_NOTOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_SHOWWINDOW );
	return GetFocus() == hWnd;
}

void WFenster::setPosition( Punkt &p )// Fenster Position
{
	RECT r;
	GetWindowRect( hWnd, &r ); // Vorherige Position herausfinden
	RECT res;
	res.left = p.x, res.top = p.y, res.right = r.right - r.left, res.bottom = r.bottom - r.top;
	AdjustWindowRect( &res, style, 0 );
	if( res.top < 0 )
	{
		res.bottom -= res.top;
		res.top = 0;
	}
	if( res.left < 0 )
	{
		res.right -= res.left;
		res.left = 0;
	}
	SetWindowPos( hWnd, 0, res.left, res.top, res.right, res.bottom, 0 ); // Position �ndern
}

void WFenster::setGr��e( Punkt &g )// Fenster Gr��e
{
	RECT r;
	GetWindowRect( hWnd, &r ); // vorherige Gr��e herausfinden
	RECT res;
	res.left = r.left, res.top = r.top, res.right = g.x, res.bottom = g.y;
	AdjustWindowRect( &res, style, 0 );
	if( res.top < 0 )
	{
		res.bottom -= res.top;
		res.top = 0;
	}
	if( res.left < 0 )
	{
		res.right -= res.left;
		res.left = 0;
	}
	SetWindowPos( hWnd, 0, res.left, res.top, res.right, res.bottom, 0 ); // Gr��e �ndern
}

void WFenster::setGr��e( int breite, int h�he )
{
	RECT r;
	GetWindowRect( hWnd, &r ); // vorherige Gr��e herausfinden
	RECT res;
	res.left = r.left, res.top = r.top, res.right = breite, res.bottom = h�he;
	AdjustWindowRect( &res, style, 0 );
	if( res.top < 0 )
	{
		res.bottom -= res.top;
		res.top = 0;
	}
	if( res.left < 0 )
	{
		res.right -= res.left;
		res.left = 0;
	}
	SetWindowPos( hWnd, 0, res.left, res.top, res.right, res.bottom, 0 ); // Gr��e �ndern
}

void WFenster::setBounds( Punkt &p, Punkt &g ) // setzt gr��e und Position
{
	SetWindowPos( hWnd, 0, p.x, p.y, g.x, g.y, 0 ); // Gr��e und Position �ndern
}

void WFenster::setBildschirm( Bildschirm *screen )
{
	if( this->screen )
		this->screen->release();
	this->screen = screen;
}

void WFenster::zerst�ren()
{
	DestroyWindow( hWnd );
    hWnd = 0;
	if( rahmen )
		DestroyWindow( rahmen );
    rahmen = 0;
	if( bitmap )
		DeleteObject( bitmap );
    bitmap = 0;
	if( hdc )
		DeleteDC( hdc );
    hdc = 0;
}

void WFenster::doMausAktion( MausEreignis &me )
{
	if( !MausAktion || !MausAktion( makParam, this, me ) )
		return;
	if( screen && me.id != ME_Betritt && me.id != ME_Verl�sst )
	{
		screen->doMausEreignis( me );
		if( !me.verarbeitet && verschiebbar )
		{
			if( mx != -1 && my != -1 ) // verschieben
			{
				RECT r;
				if( rahmen )
				{
					GetWindowRect( rahmen, &r );
					r.right -= r.left, r.bottom -= r.top;
					r.left += me.mx - mx;
					r.top += me.my - my;
					SetWindowPos( rahmen, 0, r.left, r.top, r.right, r.bottom, 0 ); // Position setzen
				}
				GetWindowRect( hWnd, &r ); // Vorherige Position herausfinden
				r.right -= r.left, r.bottom -= r.top; // Position updaten
				r.left += me.mx - mx;
				r.top += me.my - my;
				SetWindowPos( hWnd, 0, r.left, r.top, r.right, r.bottom, 0 ); // Position setzen

			}
			else if( me.id == ME_PLinks ) // verschieben starten
				mx = me.mx, my = me.my;
			if( me.id == ME_RLinks ) // verschieben beenden
				mx = -1, my = -1;
			me.verarbeitet = 1;
		}
	}
}

void WFenster::doVSchlie�Aktion()
{
	if( !VSchlie�Aktion )
		return;
	VSchlie�Aktion( sakParam, this );
}

void WFenster::doNSchlie�Aktion()
{
	if( !NSchlie�Aktion )
		return;
	NSchlie�Aktion( sakParam, this );
}

void WFenster::doTastaturAktion( TastaturEreignis &te )
{
	if( !TastaturAktion || !TastaturAktion( takParam, this, te ) )
		return;
	if( screen )
		screen->doTastaturEreignis( te );
}

void WFenster::doRestoreMessage() // macht den Rahmen sichtbar
{
	if( rahmen )
		ShowWindow( rahmen, 1 );
	ShowWindow( hWnd, 1 );
}

void WFenster::setMausEreignisParameter( void *p ) // setzt den Parameter vom Maus Ereignis
{
	makParam = p;
}

void WFenster::setSchlie�EreignisParameter( void *p ) // setzt den Parameter vom Schlie� Ereignis
{
	sakParam = p;
}

void WFenster::setTastaturEreignisParameter( void *p ) // setzt den Parameter vom Tastatur Ereignis
{
	takParam = p;
}

void WFenster::setMausAktion( bool( *MausAk )( void *, void *, MausEreignis ) )
{
	MausAktion = MausAk;
}

void WFenster::setVSchlie�Aktion( void( *vSchlie�Ak )( void *, void * ) )
{
	VSchlie�Aktion = vSchlie�Ak;
}

void WFenster::setNSchlie�Aktion( void( *nSchlie�Ak )( void *, void * ) )
{
	NSchlie�Aktion = nSchlie�Ak;
}

void WFenster::setTastaturAktion( bool( *TastaturAk )( void *, void *, TastaturEreignis ) )
{
	TastaturAktion = TastaturAk;
}

void WFenster::setFensterHandle( HWND hWnd ) // setzt das operationsfenster
{
	this->hWnd = hWnd;
}

void WFenster::setVerschiebbar( bool verschiebbar ) // legt fest, ob das Fenster durch ziehen mit Maus verschoben werden kann
{
	this->verschiebbar = verschiebbar;
}

void WFenster::ladeRahmenFenster( Bild *zBild, HINSTANCE hinst ) // setzt einen Transpatenten Rahmen um das Fenster
{
	if( !zBild )
		return;
	// Fenster erstellen
	WNDCLASSEX wcl = { 0 };
	wcl.cbSize = sizeof( wcl );
	wcl.style = CS_HREDRAW | CS_VREDRAW;
	wcl.lpfnWndProc = WindowProc;
	wcl.cbClsExtra = 0;
	wcl.cbWndExtra = 0;
	wcl.hInstance = hinst;
	wcl.hIcon = LoadIcon( NULL, IDI_APPLICATION );
	wcl.hCursor = LoadCursor( NULL, IDC_ARROW );
	wcl.hbrBackground = NULL;
	wcl.lpszMenuName = NULL;
	wcl.lpszClassName = TEXT( "LayeredWindowClass" );
	wcl.hIconSm = NULL;

	// Bitmap erstellen
	hdc = CreateCompatibleDC( NULL );
	if( !hdc )
		return;
	BITMAPINFO info;
	info.bmiHeader.biSize = sizeof( info.bmiHeader );
	info.bmiHeader.biBitCount = 32;
	info.bmiHeader.biWidth = zBild->getBreite();
	info.bmiHeader.biHeight = -zBild->getH�he();
	info.bmiHeader.biCompression = BI_RGB;
	info.bmiHeader.biPlanes = 1;
	unsigned char *pPixels = 0;
	bitmap = CreateDIBSection( hdc, &info, DIB_RGB_COLORS, (void**)&pPixels, 0, 0 );
	if( !bitmap )
		DeleteDC( hdc );
	GdiFlush();
	// bitmap f�llen
	int pitch = ( ( zBild->getBreite() * 32 + 31 ) & ~31 ) >> 3;
	unsigned char *pRow = 0;
	int *buffer = zBild->getBuffer();
	for( int i = 0; i < zBild->getH�he(); ++i )
	{
		pRow = &pPixels[ i * pitch ];
		for( int i2 = 0; i2 < zBild->getBreite(); ++i2 )
		{
			pRow[ i2 * 4 ] = (unsigned char)( ( buffer[ i2 + i * zBild->getBreite() ] >> 16 ) & 0xFF );
			pRow[ i2 * 4 + 1 ] = (unsigned char)( ( buffer[ i2 + i * zBild->getBreite() ] >> 8 ) & 0xFF );
			pRow[ i2 * 4 + 2 ] = (unsigned char)( ( buffer[ i2 + i * zBild->getBreite() ] ) & 0xFF );
			pRow[ i2 * 4 + 3 ] = (unsigned char)( ( buffer[ i2 + i * zBild->getBreite() ] >> 24 ) & 0xFF );
		}
	}
	// alpha berechnen
	unsigned char *pPixel = 0;
	if( zBild->getBreite() * 4 == pitch )
	{
		int i = 0;
		int totalBytes = zBild->getBreite() * zBild->getH�he() * 4;

		for( i = 0; i < totalBytes; i += 4 )
		{
			pPixel = &pPixels[ i ];
			pPixel[ 0 ] *= (unsigned char)( (float)pPixel[ 3 ] / 255.0f );
			pPixel[ 1 ] *= (unsigned char)( (float)pPixel[ 3 ] / 255.0f );
			pPixel[ 2 ] *= (unsigned char)( (float)pPixel[ 3 ] / 255.0f );
		}
	}
	else
	{
		int x = 0;
		int y = 0;

		for( y = 0; y < zBild->getH�he(); ++y )
		{
			for( x = 0; x < zBild->getBreite(); ++x )
			{
				pPixel = &pPixels[ ( y * pitch ) + ( x * 4 ) ];
				pPixel[ 0 ] *= (unsigned char)( (float)pPixel[ 3 ] / 255.0f );
				pPixel[ 1 ] *= (unsigned char)( (float)pPixel[ 3 ] / 255.0f );
				pPixel[ 2 ] *= (unsigned char)( (float)pPixel[ 3 ] / 255.0f );
			}
		}
	}
	// Fenster erstellen fortsetzen
	if( RegisterClassEx( &wcl ) )
	{
		rahmen = CreateWindowEx( WS_EX_TOOLWINDOW | WS_EX_LAYERED,
								 wcl.lpszClassName,
								 TEXT( "Transparentes Fenster" ),
								 WS_POPUP,
								 0,
								 0,
								 zBild->getBreite(),
								 zBild->getH�he(),
								 0,
								 0,
								 wcl.hInstance,
								 0
								 );
		if( rahmen )
		{
			// zeichnen
			HDC h = 0;
			if( ( h = GetDC( rahmen ) ) && bitmap )
			{
				HGDIOBJ hPrevObj = NULL;
				POINT ptDest = { 0, 0 };
				POINT ptSrc = { 0, 0 };
				SIZE client = { zBild->getBreite(), zBild->getH�he() };
				BLENDFUNCTION blendFunc = { AC_SRC_OVER, 0, 255, AC_SRC_ALPHA };

				hPrevObj = SelectObject( hdc, bitmap );
				ClientToScreen( rahmen, &ptDest );

				UpdateLayeredWindow( rahmen, h, &ptDest, &client, hdc, &ptSrc, 0, &blendFunc, ULW_ALPHA );

				SelectObject( hdc, hPrevObj );
				ReleaseDC( rahmen, h );
			}
			UpdateWindow( rahmen );
			Punkt pos = getPosition() + ( getGr��e() - zBild->getGr��e() ) / 2;
			SetWindowPos( rahmen, 0, pos.x, pos.y, zBild->getBreite(), zBild->getH�he(), 0 );
		}
	}
}

// constant 
Punkt WFenster::getPosition() const // gibt die Position zur�ck
{
	RECT r;
	GetWindowRect( hWnd, &r ); // Position herausfinden
	return{ r.left, r.top };
}

Punkt WFenster::getGr��e() const // gibt die Gr��e zur�ck
{
	RECT r;
	GetWindowRect( hWnd, &r ); // Gr��e herausfinden
	return{ r.right - r.left, r.bottom - r.top };
}

Punkt WFenster::getK�rperGr��e() const // gibt die Fenster K�rpergr��e zur�ck
{
	RECT r;
	GetClientRect( hWnd, &r ); // Gr��e herausfinden
	return{ r.right - r.left, r.bottom - r.top };
}

int WFenster::getK�rperBreite() const // gibt die Fenster K�rperbreite zur�ck
{
	RECT r;
	GetClientRect( hWnd, &r ); // Gr��e herausfinden
	return r.right;
}

int WFenster::getK�rperH�he() const // gibt die Fenster K�rperh�he zur�ck
{
	RECT r;
	GetClientRect( hWnd, &r ); // Gr��e herausfinden
	return r.bottom;
}

HWND WFenster::getFensterHandle() const // gibt ein Handle zum Fenster zur�ck
{
	return hWnd;
}

bool WFenster::hatMausAktion() const
{
	return MausAktion != 0;
}

bool WFenster::hatVSchlie�Aktion() const
{
	return VSchlie�Aktion != 0;
}

bool WFenster::hatNSchlie�Aktion() const
{
	return NSchlie�Aktion != 0;
}

bool WFenster::hatTastaturAktion() const
{
	return TastaturAktion != 0;
}

Bildschirm *WFenster::getBildschirm() const
{
	if( !screen )
		return 0;
	return screen->getThis();
}

Bildschirm *WFenster::zBildschirm() const
{
	return screen;
}

bool WFenster::istVerschiebbar() const // pr�ft, ob das Fenster durch ziehen mit Maus verschoben werden kann
{
	return verschiebbar;
}

// Reference Counting
WFenster *WFenster::getThis()
{
	++ref;
	return this;
}

WFenster *WFenster::release()
{
	--ref;
	if( ref < 1 )
		delete this;
	return 0;
}

// Inhalt der WFensterArray Klasse aus Fenster.h
// Konstruktor 
WFensterArray::WFensterArray()
	: next( 0 ),
	  This( 0 )
{
}

// Destruktor 
WFensterArray::~WFensterArray()
{
	if( next )
		delete next;
}

// add und remove 
bool WFensterArray::addFenster( WFenster *fenster )
{
	if( fenster == This )
		return 0;
	if( !This )
	{
		This = fenster;
		return 1;
	}
	if( !next )
		next = new WFensterArray();
	return next->addFenster( fenster );
}

bool WFensterArray::removeFenster( WFenster *fenster )
{
	if( fenster == This )
		return 1;
	if( !next )
		return 0;
	if( next->removeFenster( fenster ) )
	{
		WFensterArray *tmp = next->getNext();
		next->setNext0();
		delete next;
		next = tmp;
	}
	return 0;
}

WFensterArray *WFensterArray::getNext()
{
	return next;
}

void WFensterArray::setNext0()
{
	next = 0;
}

void WFensterArray::del()
{
	if( next )
	{
		This = next->getThis();
		WFensterArray *tmp = next->getNext();
		next->setNext0();
		delete next;
		next = tmp;
	}
	else
		This = 0;
}

// Messages 
bool WFensterArray::sendVSchlie�Message( HWND hwnd )
{
	if( !This )
		return 0;
	bool ret = 0;
	if( This->getFensterHandle() == hwnd && This->hatVSchlie�Aktion() )
	{
		This->doVSchlie�Aktion();
		ret = 1;
	}
	if( !next )
		return ret;
	return ret | next->sendVSchlie�Message( hwnd );
}

bool WFensterArray::sendNSchlie�Message( HWND hwnd )
{
	if( !This )
		return 0;
	bool ret = 0;
	if( This->getFensterHandle() == hwnd && This->hatNSchlie�Aktion() )
	{
		This->doNSchlie�Aktion();
		ret = 1;
	}
	if( !next )
		return ret;
	return ret | next->sendNSchlie�Message( hwnd );
}

bool WFensterArray::sendMausMessage( HWND hwnd, MausEreignis &me )
{
	if( !This )
		return 0;
	bool ret = 0;
	if( This->getFensterHandle() == hwnd && This->hatMausAktion() )
	{
		This->doMausAktion( me );
		ret = 1;
	}
	if( !next )
		return ret;
	return ret | next->sendMausMessage( hwnd, me );
}

bool WFensterArray::sendTastaturMessage( HWND hwnd, TastaturEreignis &te )
{
	if( !This )
		return 0;
	bool ret = 0;
	if( This->getFensterHandle() == hwnd && This->hatTastaturAktion() )
	{
		This->doTastaturAktion( te );
		ret = 1;
	}
	if( !next )
		return ret;
	return ret | next->sendTastaturMessage( hwnd, te );
}

bool WFensterArray::sendRestoreMessage( HWND hwnd )
{
	if( !This )
		return 0;
	bool ret = 0;
	if( This->getFensterHandle() == hwnd && This->hatMausAktion() )
	{
		This->doRestoreMessage();
		ret = 1;
	}
	if( !next )
		return ret;
	return ret | next->sendRestoreMessage( hwnd );
}

WFenster *WFensterArray::getThis()
{
	return This;
}

// WMessageBox
void Framework::WMessageBox( HWND hWnd, Text *titel, Text *meldung, UINT style )
{
	MessageBox( hWnd, meldung->getText(), titel->getText(), style ); // Message Box
	titel->release();
	meldung->release();
}

// Inhalt der Fenster Klasse aus Fenster.h
// Konstruktor 
Fenster::Fenster()
	: Zeichnung(),
	schlie�enMe( 0 ),
	schlie�enMeParam( 0 ),
	rahmen( 0 ),
	titel( 0 ),
	members( 0 ),
	bgK�rperFarbe( 0xFF000000 ),
	bgK�rperBild( 0 ),
	k�rperBuffer( 0 ),
	bgSchlie�Farbe( 0xFF000000 ),
	bgSchlie�Bild( 0 ),
	schlie�Buffer( 0 ),
	schlie�KlickBuffer( 0 ),
	vScroll( 0 ),
	hScroll( 0 ),
	kMin( 0, 0 ),
	kMax( 0, 0 ),
	schlie�Klick( 0 ),
	klick( 0 ),
	mx( 0 ),
	my( 0 ),
	ref( 1 )
{
    style = 0;
	this->setMausEreignis( _ret1ME );
	this->setTastaturEreignis( _ret1TE );
	min = Punkt( 0, 0 ), max = Punkt( 0, 0 );
}

// Destruktor 
Fenster::~Fenster()
{
	if( rahmen )
		rahmen->release();
	if( titel )
		titel->release();
	if( members )
		delete members;
	if( k�rperBuffer )
		k�rperBuffer->release();
	if( bgK�rperBild )
		bgK�rperBild->release();
	if( bgSchlie�Bild )
		bgSchlie�Bild->release();
	if( schlie�Buffer )
		schlie�Buffer->release();
	if( schlie�KlickBuffer )
		schlie�KlickBuffer->release();
	if( vScroll )
		vScroll->release();
	if( hScroll )
		hScroll->release();
}

// nicht const 
// -- Rahmen -- 
void Fenster::setRahmenZ( LRahmen *ram ) // setzt den rahmen
{
	if( rahmen )
		rahmen->release();
	rahmen = ram;
	rend = 1;
}

void Fenster::setRFarbe( int f ) // setzt die Rahmen Farbe
{
	if( !rahmen )
		rahmen = new LRahmen();
	rahmen->setFarbe( f );
	rend = 1;
}

void Fenster::setRBreite( int br ) // setzt die Breite des Rahmens
{
	if( !rahmen )
		rahmen = new LRahmen();
	rahmen->setRamenBreite( br );
	rend = 1;
}

// -- Titel -- 
void Fenster::setTitel( Text *txt ) // setzt den Titel
{
	if( !titel )
		titel = new TextFeld();
	titel->setText( txt );
	rend = 1;
}

void Fenster::setTitelZ( Text *txt )
{
	if( !titel )
		titel = new TextFeld();
	titel->setTextZ( txt );
	rend = 1;
}

void Fenster::setTitel( const char *txt )
{
	if( !titel )
		titel = new TextFeld();
	titel->setText( txt );
	rend = 1;
}

void Fenster::setTTextFeldZ( TextFeld *tf ) // setzt das Titel TextFeld
{
	if( titel )
		titel->release();
	titel = tf;
	rend = 1;
}

// -- Schrift -- 
void Fenster::setTSchriftZ( Schrift *schrift ) // setzt die Titel Schrift
{
	if( !titel )
		titel = new TextFeld();
	titel->setSchriftZ( schrift );
	rend = 1;
}

void Fenster::setTSFarbe( int f ) // setzt die Titel Schrift Farbe
{
	if( !titel )
		titel = new TextFeld();
	titel->setSchriftFarbe( f );
	rend = 1;
}

void Fenster::setTSGr��e( int gr ) // setzt die Titel Schrift Gr��e
{
	if( !titel )
		titel = new TextFeld();
	titel->setSchriftGr��e( gr );
	rend = 1;
}

// -- Titel Hintergrund -- 
void Fenster::setTBgFarbe( int f ) // setzt Titel Hintergrund farbe
{
	if( !titel )
		titel = new TextFeld();
	titel->setHintergrundFarbe( f );
	rend = 1;
}

// -- Titel AlphaFeld -- 
void Fenster::setTAlphaFeldZ( AlphaFeld *af ) // setzt das Titel AlphaFeld
{
	if( !titel )
		titel = new TextFeld();
	titel->setAlphaFeldZ( af );
	rend = 1;
}

void Fenster::setTAfFarbe( int f ) // setzt die Titel AlphFeld Farbe
{
	if( !titel )
		titel = new TextFeld();
	titel->setAlphaFeldFarbe( f );
	rend = 1;
}

void Fenster::setTAfSt�rke( int st ) // setzt die St�rke des Titel AlphaFeldes
{
	if( !titel )
		titel = new TextFeld();
	titel->setAlphaFeldSt�rke( st );
	rend = 1;
}

// -- Titel Hintergrund Bild -- 
void Fenster::setTBgBild( Bild *b ) // setzt das Titel Hintergrund Bild
{
	if( !titel )
		titel = new TextFeld();
	titel->setHintergrundBild( b );
	rend = 1;
}

void Fenster::setTBgBildZ( Bild *b )
{
	if( !titel )
		titel = new TextFeld();
	titel->setHintergrundBildZ( b );
	rend = 1;
}

// -- Titel Rahmen -- 
void Fenster::setTRahmenZ( LRahmen *ram ) // set Titel Rahmen
{
	if( !titel )
		titel = new TextFeld();
	titel->setLinienRahmenZ( ram );
	rend = 1;
}

void Fenster::setTRFarbe( int f ) // setzt die Titel Rahmen Farbe
{
	if( !titel )
		titel = new TextFeld();
	titel->setLinienRahmenFarbe( f );
	rend = 1;
}

void Fenster::setTRBreite( int br ) // setzt die Titel Rahmen Breite
{
	if( !titel )
		titel = new TextFeld();
	titel->setLinienRahmenBreite( br );
	rend = 1;
}

// -- K�rper Hintergrund -- 
void Fenster::setKBgFarbe( int f ) // setzt die K�rper Hintergrund Farbe
{
	bgK�rperFarbe = f;
	rend = 1;
}

// -- K�rper Hintergrund Bild -- 
void Fenster::setKBgBild( Bild *b ) // setzt das K�rper Hintergrund Bild
{
	if( !bgK�rperBild )
		bgK�rperBild = new Bild();
	bgK�rperBild->neuBild( b->getBreite(), b->getH�he(), 0 );
	int *buff1 = bgK�rperBild->getBuffer();
	int *buff2 = b->getBuffer();
	int gr = bgK�rperBild->getBreite() * bgK�rperBild->getH�he();
	for( int i = 0; i < gr; ++i )
		buff1[ i ] = buff2[ i ];
	b->release();
	rend = 1;
}

void Fenster::setKBgBildZ( Bild *b )
{
	if( bgK�rperBild )
		bgK�rperBild->release();
	bgK�rperBild = b;
	rend = 1;
}

// -- K�rper AlphaFeld -- 
void Fenster::setKAlphaFeldZ( AlphaFeld *af ) // setzt das K�rper AlphaFeld
{
	if( k�rperBuffer )
		k�rperBuffer->release();
	k�rperBuffer = af;
	rend = 1;
}

void Fenster::setKAfFarbe( int f ) // setzt K�rper AlphaFeld Farbe
{
	if( !k�rperBuffer )
		k�rperBuffer = new AlphaFeld();
	k�rperBuffer->setFarbe( f );
	rend = 1;
}

void Fenster::setKAfSt�rke( int st ) // setzt die St�rke des K�rper AlphaFeldes
{
	if( !k�rperBuffer )
		k�rperBuffer = new AlphaFeld();
	k�rperBuffer->setSt�rke( st );
	rend = 1;
}

// -- Schlie�en --
void Fenster::setSchlie�enMeParam( void *param )
{
	schlie�enMeParam = param;
}

void Fenster::setSchlie�enMe( bool( *schlie�enMe )( void *, void *, MausEreignis ) ) // setzt das Schlie�en Mausereignis
{
	this->schlie�enMe = schlie�enMe;
}

// -- Schlie�en Hintergrund -- 
void Fenster::setSBgFarbe( int f ) // setzt die Schlie� Hintergrund Farbe
{
	bgSchlie�Farbe = f;
	rend = 1;
}

// -- Schlie�en Hintergrund Bild -- 
void Fenster::setSBgBild( Bild *b ) // setzt das Schlie� Hintergrund Bild
{
	if( !bgSchlie�Bild )
		bgSchlie�Bild = new Bild();
	bgSchlie�Bild->neuBild( b->getBreite(), b->getH�he(), 0 );
	int *buff1 = bgSchlie�Bild->getBuffer();
	int *buff2 = b->getBuffer();
	int gr = bgSchlie�Bild->getBreite() * bgSchlie�Bild->getH�he();
	for( int i = 0; i < gr; ++i )
		buff1[ i ] = buff2[ i ];
	b->release();
	rend = 1;
}

void Fenster::setSBgBildZ( Bild *b )
{
	if( bgSchlie�Bild )
		bgSchlie�Bild->release();
	bgSchlie�Bild = b;
	rend = 1;
}

// -- Schlie�en AlphaFeld -- 
void Fenster::setSAlphaFeldZ( AlphaFeld *af ) // setzt das Schlie� AlphaFeld
{
	if( schlie�Buffer )
		schlie�Buffer->release();
	schlie�Buffer = af;
	rend = 1;
}

void Fenster::setSAfFarbe( int f ) // setzt die Farbe des Schlie� AlphaFeldes
{
	if( !schlie�Buffer )
		schlie�Buffer = new AlphaFeld();
	schlie�Buffer->setFarbe( f );
	rend = 1;
}

void Fenster::setSAfSt�rke( int st ) // setzt die St�rke des Schlie� AlphaFeldes
{
	if( !schlie�Buffer )
		schlie�Buffer = new AlphaFeld();
	schlie�Buffer->setSt�rke( st );
	rend = 1;
}

// -- Schlie�en Klick AlphaFeld -- 
void Fenster::setSKAlphaFeldZ( AlphaFeld *af ) // setzt das Schlie� klick AlphaFeld
{
	if( schlie�KlickBuffer )
		schlie�KlickBuffer->release();
	schlie�KlickBuffer = af;
	rend = 1;
}

void Fenster::setSKAfFarbe( int f ) // setzt die Farbe des Schlie� klick AlphaFeldes
{
	if( !schlie�KlickBuffer )
		schlie�KlickBuffer = new AlphaFeld();
	schlie�KlickBuffer->setFarbe( f );
	rend = 1;
}

void Fenster::setSKAfSt�rke( int st ) // setzt die St�rke des Schlie� klick AlphaFeldes
{
	if( !schlie�KlickBuffer )
		schlie�KlickBuffer = new AlphaFeld();
	schlie�KlickBuffer->setSt�rke( st );
	rend = 1;
}

// -- min max -- 
void Fenster::setMin( int mx, int my ) // setzt die Mindest Fenster Gr��e
{
	min.x = mx;
	min.y = my;
}

void Fenster::setMin( const Punkt &min )
{
	this->min = min;
}

void Fenster::setMax( int mx, int my ) // setzt die Maximale Fenster Gr��e
{
	max.x = mx;
	max.y = my;
}

void Fenster::setMax( const Punkt &max )
{
	this->max = max;
}

void Fenster::setKMin( int mx, int my ) // setzt die Mindest K�rper Gr��e
{
	kMin.x = mx;
	kMin.y = my;
}

void Fenster::setKMin( const Punkt &min )
{
	kMin = min;
}

void Fenster::setKMax( int mx, int my ) // setzt die Maximale K�rper Gr��e
{
	kMax.x = mx;
	kMax.y = my;
}

void Fenster::setKMax( const Punkt &max )
{
	kMax = max;
}

// -- scroll -- 
void Fenster::setHScrollBarZ( HScrollBar *hScroll ) // setzt die Horizontale Scroll Bar
{
	if( this->hScroll )
		this->hScroll->release();
	this->hScroll = hScroll;
	rend = 1;
}

void Fenster::setVScrollBarZ( VScrollBar *vScroll ) // setzt die Vertikale Scroll BAr
{
	if( this->vScroll )
		this->vScroll->release();
	this->vScroll = vScroll;
	rend = 1;
}

void Fenster::setHSBMax( int max ) // setzt das Scroll Maximum
{
	if( !hScroll )
		hScroll = new HScrollBar();
	int rbr = 0;
	if( hatStyle( Style::Rahmen ) && rahmen )
		rbr = rahmen->getRBreite();
	int vsh = 0;
	if( hatStyle( Style::VScroll ) && vScroll )
		vsh = 15;
	hScroll->update( max, gr.x - rbr * 2 - vsh );
	rend = 1;
}

void Fenster::setVSBMax( int max )
{
	if( !vScroll )
		vScroll = new VScrollBar();
	int rbr = 0;
	int th = 0;
	if( hatStyle( Style::Rahmen ) && rahmen )
		rbr = rahmen->getRBreite();
	if( hatStyle( Style::Titel ) && titel )
		th = titel->getH�he();
	int hsh = 0;
	if( hatStyle( Style::HScroll ) && hScroll )
		hsh = 15;
	vScroll->update( max, gr.y - rbr * 2 - th - hsh );
	rend = 1;
}

void Fenster::setHSBScroll( int scroll ) // setzt die momentane Scroll Position
{
	if( !hScroll )
		hScroll = new HScrollBar();
	hScroll->scroll( scroll );
	rend = 1;
}

void Fenster::setVSBScroll( int scroll )
{
	if( !vScroll )
		vScroll = new VScrollBar();
	vScroll->scroll( scroll );
	rend = 1;
}

// -- Members -- 
void Fenster::addMember( Zeichnung *obj ) // f�gt einen Member hinzu
{
	if( !members )
		members = new ZeichnungArray();
	members->addZeichnung( obj );
	members->updateIndex( 0 );
	rend = 1;
}

void Fenster::removeMember( Zeichnung *obj ) // entfernt einen Member
{
	if( !members )
		return;
	members->removeZeichnung( obj );
	members->updateIndex( 0 );
	rend = 1;
}

// -- Messages -- 
bool Fenster::tick( double tickval ) // tick
{
	if( members && hatStyle( Style::Sichtbar ) )
		rend |= members->tick( tickval );
	else if( members )
		members->tick( tickval );
	if( vScroll && hatStyle( Style::VScroll ) )
		rend |= vScroll->getRend();
	if( hScroll && hatStyle( Style::HScroll ) )
		rend |= hScroll->getRend();
	bool ret = rend;
	rend = 0;
	return ret;
}

void Fenster::doMausEreignis( MausEreignis &me )
{
    bool nmakc = !me.verarbeitet;
	if( me.verarbeitet || ( me.mx < pos.x || me.mx > pos.x + gr.x || me.my < pos.y || me.my > pos.y + gr.y ) )
	{
		if( mausIn )
		{
			mausIn = 0;
			MausEreignis me2;
			me2.id = ME_Verl�sst;
			me2.mx = me.mx;
			me2.my = me.my;
			me2.verarbeitet = 0;
			doMausEreignis( me2 );
			return;
		}
	}
	else if( !mausIn && me.id != ME_Verl�sst )
	{
		mausIn = 1;
		MausEreignis me2;
		me2.id = ME_Betritt;
		me2.mx = me.mx;
		me2.my = me.my;
		me2.verarbeitet = 0;
		doMausEreignis( me2 );
	}
	if( hatStyle( Style::Sichtbar ) )
	{
		bool mvtmp = me.verarbeitet;
		if( !Mak )
			return;
		if( hatStyleNicht( Style::Erlaubt ) )
			me.verarbeitet = 1;
		bool mpr = 0;
		me.mx -= pos.x;
		me.my -= pos.y;
		int rbr = 0;
		if( hatStyle( Style::Rahmen ) && rahmen )
			rbr = rahmen->getRBreite();
		int th = 0;
		if( hatStyle( Style::Titel ) && titel )
			th = titel->getH�he();
		bool hSc = hatStyle( Style::HScroll ) && hScroll;
		bool vSc = hatStyle( Style::VScroll ) && vScroll;
		if( !me.verarbeitet && me.id == ME_Bewegung && klick )
		{
			if( hatStyle( Style::Beweglich ) || hatStyle( Style::H�he�nderbar ) || hatStyle( Style::Breite�nderbar ) || hatStyle( Style::TitelH�he�nderbar ) )
			{
				if( Mak( makParam, this, me ) )
				{
					mpr = 1;
					bool ret1 = 0;
					bool mset = 0;
					int sch� = 0;
					int scbr = 0;
					if( hSc )
					{
						sch� = 15;
						scbr = 40;
					}
					if( vSc )
					{
						scbr += 15;
						sch� = 40;
					}
					bool minXb, maxXb, minYb, maxYb;
					bool kMinXb, kMaxXb, kMinYb, kMaxYb;
					minXb = hatStyle( Style::MinBr );
					maxXb = hatStyle( Style::MaxBr );
					minYb = hatStyle( Style::MinH� );
					maxYb = hatStyle( Style::MaxH� );
					kMinXb = hatStyle( Style::K�rper_minBr );
					kMaxXb = hatStyle( Style::K�rper_maxBr );
					kMinYb = hatStyle( Style::K�rper_minH� );
					kMaxYb = hatStyle( Style::K�rper_maxH� );
					int fMinBr = rbr * 2 + scbr;
					if( minXb )
						fMinBr = fMinBr < min.x ? min.x : fMinBr;
					if( kMinXb )
						fMinBr = fMinBr < ( rbr * 2 + kMin.x + scbr ) ? ( rbr * 2 + kMin.x + scbr ) : fMinBr;
					int fMinH� = rbr * 2 + th + sch�;
					if( minYb )
						fMinH� = fMinH� < min.y ? min.y : fMinH�;
					if( kMinYb )
						fMinH� = fMinH� < ( rbr * 2 + kMin.y + th + sch� ) ? ( rbr * 2 + kMin.y + th + sch� ) : fMinH�;
					int fMaxBr = 0;
					if( maxXb )
						fMaxBr = max.x;
					if( kMaxXb )
						fMaxBr = fMaxBr < ( rbr * 2 + kMax.x + scbr ) ? ( rbr * 2 + kMax.x + scbr ) : fMaxBr;
					int fMaxH� = 0;
					if( maxYb )
						fMaxH� = max.y;
					if( kMaxYb )
						fMaxH� = fMaxH� < ( rbr * 2 + kMax.y + th + sch� ) ? ( rbr * 2 + kMax.y + th + sch� ) : fMaxH�;
					minXb |= kMinXb, maxXb |= kMaxXb, minYb |= kMinYb, maxYb |= kMaxYb;
					if( hatStyle( Style::H�he�nderbar ) )
					{
						if( mx > -5 && mx < gr.x + 5 && my > -5 && my < rbr )
						{
							pos.y -= my - me.my;
							gr.y += my - me.my;
							if( gr.y < fMinH� )
							{
								pos.y += fMinH� - gr.y;
								gr.y = fMinH�;
							}
							else if( maxYb && gr.y > fMaxH� )
							{
								pos.y += gr.y - fMaxH�;
								gr.y = fMaxH�;
							}
							else if( vSc )
								vScroll->getScrollData()->anzeige = gr.y;
							rend = 1;
							ret1 = 1;
						}
						else if( mx > -5 && mx < gr.x + 5 && my > gr.y - rbr && my < gr.y + 5 )
						{
							gr.y += me.my - my;
							if( gr.y < fMinH� )
								gr.y = fMinH�;
							else if( maxYb && gr.y > fMaxH� )
								gr.y = fMaxH�;
							else
							{
								mset = 1;
								if( vSc )
									vScroll->getScrollData()->anzeige = gr.y;
							}
							rend = 1;
							ret1 = 1;
						}
					}
					if( hatStyle( Style::Breite�nderbar ) )
					{
						if( mx > -5 && mx < rbr && my > -5 && my < gr.y + 5 )
						{
							pos.x -= mx - me.mx;
							gr.x += mx - me.mx;
							if( gr.x < fMinBr )
							{
								pos.x += fMinBr - gr.x;
								gr.x = fMinBr;
							}
							else if( maxXb && gr.x > fMaxBr )
							{
								pos.x += gr.x - fMaxBr;
								gr.x = fMaxBr;
							}
							else if( hSc )
								hScroll->getScrollData()->anzeige = gr.x;
							rend = 1;
							ret1 = 1;
						}
						else if( mx > gr.x - rbr && mx < gr.x + 5 && my > -5 && my < gr.y + 5 )
						{
							gr.x += me.mx - mx;
							if( gr.x < rbr * 2 + fMinBr )
								gr.x = rbr * 2 + fMinBr;
							else if( maxXb && gr.x > fMaxBr )
								gr.x = fMaxBr;
							else
							{
								mset = 1;
								if( hSc )
									hScroll->getScrollData()->anzeige = gr.x;
							}
							rend = 1;
							ret1 = 1;
						}
					}
					if( hatStyle( Style::TitelH�he�nderbar ) && titel && mx > -5 && mx < gr.x + 5 && my < rbr + th + 5 && my > rbr + th )
					{
						int maxTh = gr.y - rbr * 2 - sch�;
						if( kMaxYb )
							maxTh = maxTh < ( gr.x - rbr * 2 - kMin.y ) ? maxTh : ( gr.x - rbr * 2 - kMin.y );
						if( hatStyle( Style::Schlie�bar ) )
							maxTh = ( gr.x - th - 5 - rbr * 2 - me.my + my ) < 0 ? th : maxTh;
						titel->setGr��e( titel->getBreite(), titel->getH�he() + me.my - my );
						if( titel->getH�he() > maxTh )
							titel->setGr��e( titel->getBreite(), maxTh );
						else if( titel->getH�he() < 5 )
							titel->setGr��e( titel->getBreite(), 5 );
						else
							mset = 1;
						rend = 1;
						ret1 = 1;
					}
					if( ret1 )
					{
						if( mset )
							mx = me.mx, my = me.my;
						me.verarbeitet = 1;
					}
					if( hatStyle( Style::Beweglich ) && mx > rbr && mx < gr.x - th - rbr && my > rbr && my < rbr + th )
					{
						pos.x += me.mx - mx;
						pos.y += me.my - my;
						rend = 1;
						ret1 = 1;
					}
					if( ret1 )
						me.verarbeitet = 1;
				}
			}
		}
		bool inside = me.mx >= 0 && me.mx <= gr.x && me.my >= 0 && me.my <= gr.y;
		if( mpr || me.verarbeitet || ( !inside || Mak( makParam, this, me ) ) )
		{
			if( me.id == ME_RLinks )
			{
				if( schlie�Klick )
					rend = 1;
				schlie�Klick = 0, klick = 0;
				mx = -1, my = -1;
			}
			if( me.id == ME_Verl�sst )
			{
				if( schlie�Klick != 0 )
					rend = 1;
				schlie�Klick = 0, klick = 0;
				mx = -1, my = -1;
			}
			if( !me.verarbeitet )
			{
				if( me.id == ME_PLinks )
				{
					klick = 1;
					mx = me.mx, my = me.my;
				}
				if( hatStyle( Style::Schlie�bar ) && me.my <= th + rbr && me.mx >= gr.x + rbr - th && me.my >= rbr && me.mx <= gr.x - rbr )
				{
					if( !schlie�enMe || schlie�enMe( schlie�enMeParam, this, me ) )
					{
						if( me.id == ME_PLinks )
						{
							schlie�Klick = 1;
							rend = 1;
						}
						if( !schlie�Klick && MausStand[ M_Links ] )
						{
							schlie�Klick = 1;
							rend = 1;
						}
						me.verarbeitet = 1;
					}
				}
				else if( schlie�Klick )
				{
					schlie�Klick = 0;
					rend = 1;
				}
			}
			if( members && me.id != ME_Betritt && me.id != ME_Verl�sst )
			{
				if( vSc )
				{
					vScroll->doMausMessage( gr.x - rbr - 16, rbr + th, 15, gr.y - rbr * 2 - th - 1, me );
					if( hSc )
						hScroll->doMausMessage( rbr, gr.y - rbr - 16, gr.x - rbr * 2 - 16, 15, me );
				}
				else
				if( hSc )
					hScroll->doMausMessage( rbr, gr.y - rbr - 16, gr.x - rbr * 2 - 1, 15, me );
				me.mx -= rbr;
				me.my -= rbr + th;
				if( hatStyle( Style::VScroll ) && vScroll )
					me.my += vScroll->getScroll();
				if( hatStyle( Style::HScroll ) && hScroll )
					me.mx += hScroll->getScroll();
				members->sendMausAll( me );
				me.mx += rbr;
				me.my += rbr + th;
                if( hatStyle( Style::VScroll ) && vScroll )
                    me.my -= vScroll->getScroll();
				if( hatStyle( Style::HScroll ) && hScroll )
					me.mx -= hScroll->getScroll();
			}
			if( inside && hatStyleNicht( Style::METransparenz ) )
				me.verarbeitet = 1;
		}
        if( nmakc && me.verarbeitet && nMak )
            me.verarbeitet = nMak( nmakParam, this, me );
		me.mx += pos.x;
		me.my += pos.y;
		if( hatStyleNicht( Style::Erlaubt ) )
			me.verarbeitet = mvtmp;
	}
	else if( members )
	{
		MausEreignis me;
		me.verarbeitet = 1;
		me.id = 0;
		me.mx = -1000000;
		me.my = -1000000;
		members->sendMausAll( me );
	}
}

void Fenster::doTastaturEreignis( TastaturEreignis &te )
{
    bool ntakc = !te.verarbeitet;
	if( hatStyle( Style::Sichtbar ) )
	{
		if( te.verarbeitet )
		{
			if( members )
				members->sendTastaturAll( te );
		}
		else
		{
			if( Tak && Tak( takParam, this, te ) )
			{
				if( members )
					members->sendTastaturAll( te );
			}
		}
	}
    if( ntakc && te.verarbeitet && nTak )
        te.verarbeitet = nTak( ntakParam, this, te );
}

// -- Render -- 
void Fenster::render( Bild &zRObj ) // zeichent nach zRObj
{
	if( hatStyle( Style::Sichtbar ) )
	{
		lockZeichnung();
		if( !zRObj.setDrawOptions( pos, gr ) )
		{
			unlockZeichnung();
			return;
		}
        __super::render( zRObj );
		int rbr = 0;
		if( hatStyle( Style::Rahmen ) && rahmen )
		{
			rahmen->setGr��e( gr );
			rahmen->render( zRObj );
			rbr = rahmen->getRBreite();
		}
		int th = 0;
		if( hatStyle( Style::Titel ) && titel )
		{
			titel->setStyle( TextFeld::Style::Hintergrund, hatStyle( Style::TitelHintergrund ) );
			titel->setStyle( TextFeld::Style::HAlpha, hatStyle( Style::TitelHAlpha ) );
			titel->setStyle( TextFeld::Style::HBild, hatStyle( Style::TitelHBild ) );
			titel->setStyle( TextFeld::Style::Buffered, hatStyle( Style::TitelBuffered ) );
			th = titel->getH�he();
			if( !zRObj.setDrawOptions( rbr, rbr, gr.x - rbr * 2, th ) )
			{
				zRObj.releaseDrawOptions();
				unlockZeichnung();
				return;
			}
			int sbr = 0;
			if( hatStyle( Style::Schlie�bar ) )
			{
				sbr = th;
				if( hatStyle( Style::Schlie�Hintergrund ) )
				{
					if( hatStyle( Style::Schlie�HAlpha ) )
						zRObj.alphaRegion( gr.x - th - rbr * 2, 0, th, th, bgSchlie�Farbe );
					else
						zRObj.f�llRegion( gr.x - th - rbr * 2, 0, th, th, bgSchlie�Farbe );
					if( hatStyle( Style::Schlie�HBild ) && bgSchlie�Bild )
					{
						if( hatStyle( Style::Schlie�HAlpha ) )
							zRObj.alphaBild( gr.x - th - rbr * 2, 0, th, th, *bgSchlie�Bild );
						else
							zRObj.drawBild( gr.x - th - rbr * 2, 0, th, th, *bgSchlie�Bild );
					}
				}
				if( !hatStyle( Style::Schlie�HBild ) || !bgSchlie�Bild )
				{
					zRObj.drawLinie( Punkt( gr.x - th - rbr * 2, 0 ), Punkt( gr.x - rbr * 2, th ), 0xFFFFFFFF );
					zRObj.drawLinie( Punkt( gr.x - rbr * 2, 0 ), Punkt( gr.x - th - rbr * 2, th ), 0xFFFFFFFF );
				}
				if( hatStyle( Style::Schlie�Buffer ) && schlie�Buffer )
				{
					schlie�Buffer->setPosition( gr.x - th - rbr * 2, 0 );
					schlie�Buffer->setGr��e( th, th );
					schlie�Buffer->render( zRObj );
				}
				if( hatStyle( Style::Schlie�KlickBuffer ) && schlie�KlickBuffer && schlie�Klick )
				{
					schlie�KlickBuffer->setPosition( gr.x - th - rbr * 2, 0 );
					schlie�KlickBuffer->setGr��e( th, th );
					schlie�KlickBuffer->render( zRObj );
				}
			}
			titel->setGr��e( gr.x - rbr * 2 - sbr, th );
			titel->render( zRObj );
			zRObj.releaseDrawOptions();
		}
		bool vSc = hatStyle( Style::VScroll ) && vScroll;
		bool hSc = hatStyle( Style::HScroll ) && hScroll;
		if( vSc )
		{
			vScroll->render( gr.x - rbr - 16, rbr + th, 15, gr.y - rbr * 2 - th - 1, zRObj );
			if( hSc )
				hScroll->render( rbr, gr.y - rbr - 16, gr.x - rbr * 2 - 16, 15, zRObj );
		}
		else
		if( hSc )
			hScroll->render( rbr, gr.y - rbr - 16, gr.x - rbr * 2 - 1, 15, zRObj );
		int x = rbr;
		int y = rbr + th;
		int br = gr.x - rbr * 2;
		int h� = gr.y - rbr * 2 - th;
		if( vSc )
			br -= 16;
		if( hSc )
			h� -= 16;
		if( !zRObj.setDrawOptions( x, y, br, h� ) )
		{
			zRObj.releaseDrawOptions();
			unlockZeichnung();
			return;
		}
		if( hatStyle( Style::K�rperHintergrund ) )
		{
			if( hatStyle( Style::K�rperHAlpha ) )
				zRObj.alphaRegion( 0, 0, br, h�, bgK�rperFarbe );
			else
				zRObj.f�llRegion( 0, 0, br, h�, bgK�rperFarbe );
			if( hatStyle( Style::K�rperHBild ) && bgK�rperBild )
			{
				int *bgBuff = bgK�rperBild->getBuffer();
				int bgBr = bgK�rperBild->getBreite();
				if( hatStyle( Style::K�rperHAlpha ) )
					zRObj.alphaBild( 0, 0, br, h�, *bgK�rperBild );
				else
					zRObj.drawBild( 0, 0, br, h�, *bgK�rperBild );
			}
		}
		if( hatStyle( Style::K�rperBuffered ) && k�rperBuffer )
		{
			k�rperBuffer->setGr��e( br, h� );
			k�rperBuffer->render( zRObj );
		}
		if( members )
		{
			if( !vSc && !hSc )
				members->render( zRObj );
			else
			{
				zRObj.addScrollOffset( hSc ? hScroll->getScroll() : 0, vSc ? vScroll->getScroll() : 0 );
				members->render( zRObj );
			}
		}
		zRObj.releaseDrawOptions();
		zRObj.releaseDrawOptions();
		unlockZeichnung();
	}
}

// constant 
// -- Rahmen -- 
LRahmen *Fenster::getRahmen() const // gibt den Rahmen zur�ck
{
	if( !rahmen )
		return 0;
	return rahmen->getThis();
}

LRahmen *Fenster::zRahmen() const
{
	return rahmen;
}

int Fenster::getRFarbe() const // gibt die Farbe des Rahmens zur�ck
{
	if( !rahmen )
		return 0;
	return rahmen->getFarbe();
}

int Fenster::getRBreite() const // gibt die breite des Rahmens zur�ck
{
	if( !rahmen )
		return 0;
	return rahmen->getRBreite();
}

// -- Titel  -- 
Text *Fenster::getTitel() const // gibt den Titel zur�ck
{
	if( !titel )
		return 0;
	return titel->getText();
}

Text *Fenster::zTitel() const
{
	if( !titel )
		return 0;
	return titel->zText();
}

TextFeld *Fenster::getTTextFeld() const // gibt das Titel TextFeld zur�ck
{
	if( !titel )
		return 0;
	return titel->getThis();
}

TextFeld *Fenster::zTTextFeld() const
{
	return titel;
}

// -- Titel Schrift -- 
Schrift *Fenster::getTSchrift() const // gibt die Titel Schrift zur�ck
{
	if( !titel )
		return 0;
	return titel->getSchrift();
}

Schrift *Fenster::zTSchrift() const
{
	if( !titel )
		return 0;
	return titel->zSchrift();
}

int Fenster::getTSFarbe() const // gibt die Titel Schrift Farbe zur�ck
{
	if( !titel )
		return 0;
	return titel->getSchriftFarbe();
}

int Fenster::getTSGr��e() const // gibt die Titel Schrift Gr��e zur�ck
{
	if( !titel )
		return 0;
	return titel->getSchriftGr��e();
}

// -- Titel Hintergrund -- 
int Fenster::getTBgFarbe() const // gibt die Titel Hintergrund Farbe zur�ck
{
	if( !titel )
		return 0;
	return titel->getHintergrundFarbe();
}

// -- Titel AlphaFeld -- 
AlphaFeld *Fenster::getTAlphaFeld() const // gibt das Titel AlphaFeld zur�ck
{
	if( !titel )
		return 0;
	return titel->getAlphaFeld();
}

AlphaFeld *Fenster::zTAlphaFeld() const
{
	if( !titel )
		return 0;
	return titel->zAlphaFeld();
}

int Fenster::getTAfFarbe() const // gibt die Farbe des Titel AlphaFeldes zur�ck
{
	if( !titel )
		return 0;
	return titel->getAlphaFeldFarbe();
}

int Fenster::getTAfSt�rke() const // gibt die St�rke des TitelAlphaFeldes zur�ck
{
	if( !titel )
		return 0;
	return titel->getAlphaFeldSt�rke();
}

// -- Titel Hintergrund Bild -- 
Bild *Fenster::getTBgBild() const // gibt das Titel Hintergrund Bild zur�ck
{
	if( !titel )
		return 0;
	return titel->getHintergrundBild();
}

Bild *Fenster::zTBgBild() const
{
	if( !titel )
		return 0;
	return titel->zHintergrundBild();
}

// -- Titel Rahmen -- 
LRahmen *Fenster::getTRahmen() const // gibt den Titel Rahmen zur�ck
{
	if( !titel )
		return 0;
	return titel->getLinienRahmen();
}

LRahmen *Fenster::zTRahmen() const
{
	if( !titel )
		return 0;
	return titel->zLinienRahmen();
}

int Fenster::getTRFarbe() const // gibt die Farbe des Titel Rahmens zur�ck
{
	if( !titel )
		return 0;
	return titel->getLinienRahmenFarbe();
}

int Fenster::getTRBreite() const // gibt die Breite des Titel Rahmens zur�ck
{
	if( !titel )
		return 0;
	return titel->getLinienRahmenBreite();
}

// -- K�rper Hintergrund -- 
int Fenster::getKBgFarbe() const // gibt die K�rper Hintergrund Farbe zur�ck
{
	return bgK�rperFarbe;
}

// -- K�rper Hintergrund Bild -- 
Bild *Fenster::getKBgBild() const // gibt das K�rper Hintergrund Bild zur�ck
{
	if( !bgK�rperBild )
		return 0;
	return bgK�rperBild->getThis();
}

Bild *Fenster::zKBgBild() const
{
	return bgK�rperBild;
}

// -- K�rper AlphaFeld -- 
AlphaFeld *Fenster::getKAlphaFeld() const // gibt das K�rper AlphaFeld zur�ck
{
	if( !k�rperBuffer )
		return 0;
	return k�rperBuffer->getThis();
}

AlphaFeld *Fenster::zKAlphaFeld() const
{
	return k�rperBuffer;
}

int Fenster::getKAfFarbe() const // gibt die Farbe des K�rper AlphaFeldes zur�ck
{
	if( !k�rperBuffer )
		return 0;
	return k�rperBuffer->getFarbe();
}

int Fenster::getKAfSt�rke() const // gibt die St�rke des K�rper AlphaFeldes zur�ck
{
	if( !k�rperBuffer )
		return 0;
	return k�rperBuffer->getSt�rke();
}

// -- Schlie�en Hintergrund -- 
int Fenster::getSBgFarbe() const // gibt die Schlie� Hintergrund Farbe zur�ck
{
	return bgSchlie�Farbe;
}

// -- Schlie�en Hintergrund Bild -- 
Bild *Fenster::getSBgBild() const // gibt das Schlie� Hintergrund Bild zur�ck
{
	if( !bgSchlie�Bild )
		return 0;
	return bgSchlie�Bild->getThis();
}

Bild *Fenster::zSBgBild() const
{
	return bgSchlie�Bild;
}

// -- Schlie�en AlphaFeld -- 
AlphaFeld *Fenster::getSAlphaFeld() const // gibt das Schlie� AlphaFeld zur�ck
{
	if( !schlie�Buffer )
		return 0;
	return schlie�Buffer->getThis();
}

AlphaFeld *Fenster::zSAlphaFeld() const
{
	return schlie�Buffer;
}

int Fenster::getSAfFarbe() const // gibt die Farbe des Schlie� AlphaFeldes zur�ck
{
	if( !schlie�Buffer )
		return 0;
	return schlie�Buffer->getFarbe();
}

int Fenster::getSAfSt�rke() const // gibt die St�rke des Schlie� AlphaFeldes zur�ck
{
	if( !schlie�Buffer )
		return 0;
	return schlie�Buffer->getSt�rke();
}

// -- Schlie�en Klick AlphaFeld -- 
AlphaFeld *Fenster::getSKAlphaFeld() const // gibt das Schlie� Klick AlphaFeld zur�ck
{
	if( !schlie�KlickBuffer )
		return 0;
	return schlie�KlickBuffer->getThis();
}

AlphaFeld *Fenster::zSKAlphaFeld() const
{
	return schlie�KlickBuffer;
}

int Fenster::getSKAfFarbe() const // gibt die Farbe des Schlie� Klick AlphaFeldes zur�ck
{
	if( !schlie�KlickBuffer )
		return 0;
	return schlie�KlickBuffer->getFarbe();
}

int Fenster::getSKAfSt�rke() const // gibt die St�rke des Schlie� Klick AlphaFeldes zur�ck
{
	if( !schlie�KlickBuffer )
		return 0;
	return schlie�KlickBuffer->getSt�rke();
}

// -- min max -- 
const Punkt &Fenster::getMin() const // gibt die minimale Fenstergr��e zur�ck
{
	return min;
}

const Punkt &Fenster::getMax() const // gibt die maximale Fenstergr��e zur�ck
{
	return max;
}

const Punkt &Fenster::getKMin() const // gibt die minimale Fenstergr��e zur�ck
{
	return kMin;
}

const Punkt &Fenster::getKMax() const // gibt die maximale Fenstergr��e zur�ck
{
	return kMax;
}

// -- scroll -- 
VScrollBar *Fenster::getVScrollBar() const // gibt die Vertikale Scroll Bar zur�ck
{
	if( !vScroll )
		return 0;
	return (VScrollBar*)vScroll->getThis();
}

VScrollBar *Fenster::zVScrollBar() const
{
	return vScroll;
}

HScrollBar *Fenster::getHScrollBar() const // gibt die Horizontale Scroll Bar zur�ck
{
	if( !hScroll )
		return 0;
	return (HScrollBar*)hScroll->getThis();
}

HScrollBar *Fenster::zHScrollBar() const
{
	return hScroll;
}

// -- Members -- 
ZeichnungArray *Fenster::getMembers() const // gibt die Members zur�ck
{
	return members;
}

// -- Kopie --
Zeichnung *Fenster::dublizieren() const // Erzeugt eine Kopie des Fensters
{
	Fenster *ret = new Fenster();
	ret->setPosition( pos );
	ret->setGr��e( gr );
	ret->setMausEreignisParameter( makParam );
	ret->setTastaturEreignisParameter( takParam );
	ret->setMausEreignis( Mak );
	ret->setTastaturEreignis( Tak );
	if( toolTip )
		ret->setToolTipText( toolTip->zText()->getText(), toolTip->zBildschirm() );
	ret->setStyle( style );
	ret->setSchlie�enMeParam( schlie�enMeParam );
	ret->setSchlie�enMe( schlie�enMe );
	if( rahmen )
	{
		ret->setRBreite( rahmen->getRBreite() );
		ret->setRFarbe( rahmen->getFarbe() );
	}
	if( titel )
		ret->setTTextFeldZ( (TextFeld*)titel->dublizieren() );
	ret->setKBgFarbe( bgK�rperFarbe );
	if( bgK�rperBild )
		ret->setKBgBild( bgK�rperBild->getThis() );
	if( k�rperBuffer )
	{
		ret->setKAfFarbe( k�rperBuffer->getFarbe() );
		ret->setKAfSt�rke( k�rperBuffer->getSt�rke() );
	}
	ret->setSBgFarbe( bgSchlie�Farbe );
	if( bgSchlie�Bild )
		ret->setSBgBild( bgSchlie�Bild->getThis() );
	if( schlie�Buffer )
	{
		ret->setSAfFarbe( schlie�Buffer->getFarbe() );
		ret->setSAfSt�rke( schlie�Buffer->getSt�rke() );
	}
	if( schlie�KlickBuffer )
	{
		ret->setSKAfFarbe( schlie�KlickBuffer->getFarbe() );
		ret->setSKAfSt�rke( schlie�KlickBuffer->getSt�rke() );
	}
	if( vScroll )
	{
		ret->setVSBMax( vScroll->getScrollData()->max );
		ret->setVSBScroll( vScroll->getScroll() );
	}
	if( hScroll )
	{
		ret->setHSBMax( hScroll->getScrollData()->max );
		ret->setHSBScroll( hScroll->getScroll() );
	}
	ret->setMin( min );
	ret->setMax( max );
	ret->setKMin( kMin );
	ret->setKMax( kMax );
	return ret;
}

// Reference Counting 
Fenster *Fenster::getThis()
{
	++ref;
	return this;
}

Fenster *Fenster::release()
{
	--ref;
	if( ref == 0 )
		delete this;
	return 0;
}