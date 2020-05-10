#include "win32w.h"

VALUE mWin32;
extern VALUE mWin32;

// KeyBoard.down?( KeyBoard::VK_CODE )
VALUE isKeyPushed( VALUE self, VALUE VK_CODE ) {
	if ( GetKeyState( NUM2INT( VK_CODE ) ) < 0 )
		return Qtrue;
	else
		return Qfalse;
}

// KeyBoard.push( KeyBoard::VK_CODE )
void pushKey( VALUE self, VALUE VK_CODE ) {
	keybd_event( NUM2INT( VK_CODE ), 0, 0, 0 );
	keybd_event( NUM2INT( VK_CODE ), 0, KEYEVENTF_KEYUP, 0 );
}

// KeyBoard.shift( KeyBoard::VK_CODE )
void pushKeyShift( VALUE self, VALUE VK_CODE ) {
	keybd_event( VK_SHIFT , 0, 0, 0 );
	keybd_event( NUM2INT( VK_CODE ), 0, 0, 0 );
	keybd_event( NUM2INT( VK_CODE ), 0, KEYEVENTF_KEYUP, 0 );
	keybd_event( VK_SHIFT, 0, KEYEVENTF_KEYUP, 0 );
}

// KeyBoard.type( str )
void typeSent( VALUE self, VALUE str ) {
	char *cstr = StringValuePtr( str );
	long len = RSTRING_LEN( RSTRING( str ) );
	char *pattern = "!\"#$%&'()", *ptr;
	for ( long i = 0; i < len; ++i ) {
		if ( '0' <= cstr[i] && cstr[i] <= '9' ) {
			pushKey( self, INT2FIX( cstr[i] ) );
		} else if ( 'a' <= cstr[i] && cstr[i] <= 'z' ) {
			pushKey( self, INT2FIX( ( cstr[i] - 32 ) ) ); // 'a' - 'A' = 32
		} else if ( 'A' <= cstr[i] && cstr[i] <= 'Z' ) {
			pushKeyShift( self, INT2FIX( cstr[i] ) );
		} else if ( ( ptr = strchr( pattern, cstr[i] ) ) ) {
			pushKeyShift( self, INT2FIX( '1' + ptr - pattern ) );
		} else if ( cstr[i] == ' ' ) {
			pushKey( self, INT2FIX( VK_SPACE ) );
		}
	}
}
// [ENTER][TAB][BACKSPACE]等も追加予定

// KeyBoard.keys()
VALUE getPushKey( VALUE self ) {
	unsigned char buf[256];
	VALUE ary[256];
	int i, j;
	GetKeyState( 0 ); // メッセージキューを取得
	GetKeyboardState( buf );
	for ( i = 0, j = 0; i < 256; ++i ) {
		if ( buf[i] & 0x80 )
			ary[j++] = INT2FIX( i );
	}
	return rb_ary_new4( j, ary );
}

void Init_keyboard( void ) {
	VALUE mKeyBoard = rb_define_module_under( mWin32, "KeyBoard" );

	rb_define_singleton_method( mKeyBoard, "down?", isKeyPushed, 1 );
	rb_define_singleton_method( mKeyBoard, "push", RUBY_METHOD_FUNC( pushKey ), 1 );
	rb_define_singleton_method( mKeyBoard, "shift", RUBY_METHOD_FUNC( pushKeyShift ), 1 );
	rb_define_singleton_method( mKeyBoard, "type", RUBY_METHOD_FUNC( typeSent ), 1 );
	rb_define_singleton_method( mKeyBoard, "keys", getPushKey, 0 );

	rb_define_const( mKeyBoard, "K_0", INT2FIX( '0' ) );
	rb_define_const( mKeyBoard, "K_1", INT2FIX( '1' ) );
	rb_define_const( mKeyBoard, "K_2", INT2FIX( '2' ) );
	rb_define_const( mKeyBoard, "K_3", INT2FIX( '3' ) );
	rb_define_const( mKeyBoard, "K_4", INT2FIX( '4' ) );
	rb_define_const( mKeyBoard, "K_5", INT2FIX( '5' ) );
	rb_define_const( mKeyBoard, "K_6", INT2FIX( '6' ) );
	rb_define_const( mKeyBoard, "K_7", INT2FIX( '7' ) );
	rb_define_const( mKeyBoard, "K_8", INT2FIX( '8' ) );
	rb_define_const( mKeyBoard, "K_9", INT2FIX( '9' ) );
	rb_define_const( mKeyBoard, "K_A", INT2FIX( 'A' ) );
	rb_define_const( mKeyBoard, "K_B", INT2FIX( 'B' ) );
	rb_define_const( mKeyBoard, "K_C", INT2FIX( 'C' ) );
	rb_define_const( mKeyBoard, "K_D", INT2FIX( 'D' ) );
	rb_define_const( mKeyBoard, "K_E", INT2FIX( 'E' ) );
	rb_define_const( mKeyBoard, "K_F", INT2FIX( 'F' ) );
	rb_define_const( mKeyBoard, "K_G", INT2FIX( 'G' ) );
	rb_define_const( mKeyBoard, "K_H", INT2FIX( 'H' ) );
	rb_define_const( mKeyBoard, "K_I", INT2FIX( 'I' ) );
	rb_define_const( mKeyBoard, "K_J", INT2FIX( 'J' ) );
	rb_define_const( mKeyBoard, "K_K", INT2FIX( 'K' ) );
	rb_define_const( mKeyBoard, "K_L", INT2FIX( 'L' ) );
	rb_define_const( mKeyBoard, "K_M", INT2FIX( 'M' ) );
	rb_define_const( mKeyBoard, "K_N", INT2FIX( 'N' ) );
	rb_define_const( mKeyBoard, "K_O", INT2FIX( 'O' ) );
	rb_define_const( mKeyBoard, "K_P", INT2FIX( 'P' ) );
	rb_define_const( mKeyBoard, "K_Q", INT2FIX( 'Q' ) );
	rb_define_const( mKeyBoard, "K_R", INT2FIX( 'R' ) );
	rb_define_const( mKeyBoard, "K_S", INT2FIX( 'S' ) );
	rb_define_const( mKeyBoard, "K_T", INT2FIX( 'T' ) );
	rb_define_const( mKeyBoard, "K_U", INT2FIX( 'U' ) );
	rb_define_const( mKeyBoard, "K_V", INT2FIX( 'V' ) );
	rb_define_const( mKeyBoard, "K_W", INT2FIX( 'W' ) );
	rb_define_const( mKeyBoard, "K_X", INT2FIX( 'X' ) );
	rb_define_const( mKeyBoard, "K_Y", INT2FIX( 'Y' ) );
	rb_define_const( mKeyBoard, "K_Z", INT2FIX( 'Z' ) );
	rb_define_const( mKeyBoard, "K_BACKSPACE", INT2FIX( VK_BACK ) );
	rb_define_const( mKeyBoard, "K_TAB", INT2FIX( VK_TAB ) );
	rb_define_const( mKeyBoard, "K_CLEAR", INT2FIX( VK_CLEAR ) );
	rb_define_const( mKeyBoard, "K_ENTER", INT2FIX( VK_RETURN ) );
	rb_define_const( mKeyBoard, "K_RETURN", INT2FIX( VK_RETURN ) );
	rb_define_const( mKeyBoard, "K_SHIFT", INT2FIX( VK_SHIFT ) );
	rb_define_const( mKeyBoard, "K_CONTROL", INT2FIX( VK_CONTROL ) );
	rb_define_const( mKeyBoard, "K_ALT", INT2FIX( VK_MENU ) );
	rb_define_const( mKeyBoard, "K_PAUSE", INT2FIX( VK_PAUSE ) );
	rb_define_const( mKeyBoard, "K_CAPSLOCK", INT2FIX( VK_CAPITAL ) );
	rb_define_const( mKeyBoard, "K_ESCAPE", INT2FIX( VK_ESCAPE ) );
	rb_define_const( mKeyBoard, "K_SPACE", INT2FIX( VK_SPACE ) );
	rb_define_const( mKeyBoard, "K_PAGEUP", INT2FIX( VK_PRIOR ) );
	rb_define_const( mKeyBoard, "K_PAGEDOWN", INT2FIX( VK_NEXT ) );
	rb_define_const( mKeyBoard, "K_END", INT2FIX( VK_END ) );
	rb_define_const( mKeyBoard, "K_HOME", INT2FIX( VK_HOME ) );
	rb_define_const( mKeyBoard, "K_LEFT", INT2FIX( VK_LEFT ) );
	rb_define_const( mKeyBoard, "K_UP", INT2FIX( VK_UP ) );
	rb_define_const( mKeyBoard, "K_RIGHT", INT2FIX( VK_RIGHT ) );
	rb_define_const( mKeyBoard, "K_DOWN", INT2FIX( VK_DOWN ) );
	rb_define_const( mKeyBoard, "K_SELECT", INT2FIX( VK_SELECT ) );
	rb_define_const( mKeyBoard, "K_PRINTSCREEN", INT2FIX( VK_SNAPSHOT ) );
	rb_define_const( mKeyBoard, "K_INSERT", INT2FIX( VK_INSERT ) );
	rb_define_const( mKeyBoard, "K_DELETE", INT2FIX( VK_DELETE ) );
	rb_define_const( mKeyBoard, "K_LWIN", INT2FIX( VK_LWIN ) );
	rb_define_const( mKeyBoard, "K_RWIN", INT2FIX( VK_RWIN ) );
	rb_define_const( mKeyBoard, "K_APPS", INT2FIX( VK_APPS ) );
	rb_define_const( mKeyBoard, "K_SLEEP", INT2FIX( VK_SLEEP ) );
	rb_define_const( mKeyBoard, "K_NUMPAD0", INT2FIX( VK_NUMPAD0 ) );
	rb_define_const( mKeyBoard, "K_NUMPAD1", INT2FIX( VK_NUMPAD1 ) );
	rb_define_const( mKeyBoard, "K_NUMPAD2", INT2FIX( VK_NUMPAD2 ) );
	rb_define_const( mKeyBoard, "K_NUMPAD3", INT2FIX( VK_NUMPAD3 ) );
	rb_define_const( mKeyBoard, "K_NUMPAD4", INT2FIX( VK_NUMPAD4 ) );
	rb_define_const( mKeyBoard, "K_NUMPAD5", INT2FIX( VK_NUMPAD5 ) );
	rb_define_const( mKeyBoard, "K_NUMPAD6", INT2FIX( VK_NUMPAD6 ) );
	rb_define_const( mKeyBoard, "K_NUMPAD7", INT2FIX( VK_NUMPAD7 ) );
	rb_define_const( mKeyBoard, "K_NUMPAD8", INT2FIX( VK_NUMPAD8 ) );
	rb_define_const( mKeyBoard, "K_NUMPAD9", INT2FIX( VK_NUMPAD9 ) );
	rb_define_const( mKeyBoard, "K_ADD", INT2FIX( VK_ADD ) );
	rb_define_const( mKeyBoard, "K_SEPARATOR", INT2FIX( VK_SEPARATOR ) );
	rb_define_const( mKeyBoard, "K_SUBTRACT", INT2FIX( VK_SUBTRACT ) );
	rb_define_const( mKeyBoard, "K_DECIMAL", INT2FIX( VK_DECIMAL ) );
	rb_define_const( mKeyBoard, "K_DIVIDE", INT2FIX( VK_DIVIDE ) );
	rb_define_const( mKeyBoard, "K_F1", INT2FIX( VK_F1 ) );
	rb_define_const( mKeyBoard, "K_F2", INT2FIX( VK_F2 ) );
	rb_define_const( mKeyBoard, "K_F3", INT2FIX( VK_F3 ) );
	rb_define_const( mKeyBoard, "K_F4", INT2FIX( VK_F4 ) );
	rb_define_const( mKeyBoard, "K_F5", INT2FIX( VK_F5 ) );
	rb_define_const( mKeyBoard, "K_F6", INT2FIX( VK_F6 ) );
	rb_define_const( mKeyBoard, "K_F7", INT2FIX( VK_F7 ) );
	rb_define_const( mKeyBoard, "K_F8", INT2FIX( VK_F8 ) );
	rb_define_const( mKeyBoard, "K_F9", INT2FIX( VK_F9 ) );
	rb_define_const( mKeyBoard, "K_F10", INT2FIX( VK_F10 ) );
	rb_define_const( mKeyBoard, "K_F11", INT2FIX( VK_F11 ) );
	rb_define_const( mKeyBoard, "K_F12", INT2FIX( VK_F12 ) );
	rb_define_const( mKeyBoard, "K_F13", INT2FIX( VK_F13 ) );
	rb_define_const( mKeyBoard, "K_F14", INT2FIX( VK_F14 ) );
	rb_define_const( mKeyBoard, "K_F15", INT2FIX( VK_F15 ) );
	rb_define_const( mKeyBoard, "K_F16", INT2FIX( VK_F16 ) );
	rb_define_const( mKeyBoard, "K_F17", INT2FIX( VK_F17 ) );
	rb_define_const( mKeyBoard, "K_F18", INT2FIX( VK_F18 ) );
	rb_define_const( mKeyBoard, "K_F19", INT2FIX( VK_F19 ) );
	rb_define_const( mKeyBoard, "K_F20", INT2FIX( VK_F20 ) );
	rb_define_const( mKeyBoard, "K_F21", INT2FIX( VK_F21 ) );
	rb_define_const( mKeyBoard, "K_F22", INT2FIX( VK_F22 ) );
	rb_define_const( mKeyBoard, "K_F23", INT2FIX( VK_F23 ) );
	rb_define_const( mKeyBoard, "K_F24", INT2FIX( VK_F24 ) );
	rb_define_const( mKeyBoard, "K_NUMLOCK", INT2FIX( VK_NUMLOCK ) );
	rb_define_const( mKeyBoard, "K_SCROLLLOCK", INT2FIX( VK_SCROLL ) );
	rb_define_const( mKeyBoard, "K_LSHIFT", INT2FIX( VK_LSHIFT ) );
	rb_define_const( mKeyBoard, "K_RSHIFT", INT2FIX( VK_RSHIFT ) );
	rb_define_const( mKeyBoard, "K_LCONTROL", INT2FIX( VK_LCONTROL ) );
	rb_define_const( mKeyBoard, "K_RCONTROL", INT2FIX( VK_RCONTROL ) );
	rb_define_const( mKeyBoard, "K_LMENU", INT2FIX( VK_LMENU ) );
	rb_define_const( mKeyBoard, "K_RMENU", INT2FIX( VK_RMENU ) );
	rb_define_const( mKeyBoard, "K_BROWSER_BACK", INT2FIX( VK_BROWSER_BACK ) );
	rb_define_const( mKeyBoard, "K_BROWSER_FORWARD", INT2FIX( VK_BROWSER_FORWARD ) );
	rb_define_const( mKeyBoard, "K_BROWSER_REFRESH", INT2FIX( VK_BROWSER_REFRESH ) );
	rb_define_const( mKeyBoard, "K_BROWSER_STOP", INT2FIX( VK_BROWSER_STOP ) );
	rb_define_const( mKeyBoard, "K_BROWSER_SEARCH", INT2FIX( VK_BROWSER_SEARCH ) );
	rb_define_const( mKeyBoard, "K_BROWSER_FAVORITES", INT2FIX( VK_BROWSER_FAVORITES ) );
	rb_define_const( mKeyBoard, "K_BROWSER_HOME", INT2FIX( VK_BROWSER_HOME ) );
	rb_define_const( mKeyBoard, "K_VOLUME_MUTE", INT2FIX( VK_VOLUME_MUTE ) );
	rb_define_const( mKeyBoard, "K_VOLUME_DOWN", INT2FIX( VK_VOLUME_DOWN ) );
	rb_define_const( mKeyBoard, "K_VOLUME_UP", INT2FIX( VK_VOLUME_UP ) );
	rb_define_const( mKeyBoard, "K_MEDIA_NEXT_TRACK", INT2FIX( VK_MEDIA_NEXT_TRACK ) );
	rb_define_const( mKeyBoard, "K_MEDIA_PREV_TRACK", INT2FIX( VK_MEDIA_PREV_TRACK ) );
	rb_define_const( mKeyBoard, "K_MEDIA_STOP", INT2FIX( VK_MEDIA_STOP ) );
	rb_define_const( mKeyBoard, "K_MEDIA_PLAY_PAUSE", INT2FIX( VK_MEDIA_PLAY_PAUSE ) );
}