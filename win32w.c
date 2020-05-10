#include "win32w.h"

VALUE mWin32;
extern VALUE mWin32;

void Init_win32( void ) {
	mWin32 = rb_define_module( "Win32" );
	Init_mouse();
	Init_keyboard();
}