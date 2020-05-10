#include "win32w.h"

VALUE mWin32;
extern VALUE mWin32;

// Mouse.x
VALUE getCursorX( VALUE self ) {
	POINT p;
	GetCursorPos( &p );
	return INT2NUM( p.x );
}

// Mouse.y
VALUE getCursorY( VALUE self ) {
	POINT p;
	GetCursorPos( &p );
	return INT2NUM( p.y );
}

// Mouse.setPos( x, y )
void setCursorPos( VALUE self, VALUE x, VALUE y ) {
	POINT p;
	SetCursorPos( NUM2INT( x ), NUM2INT( y ) );
}

// Mouse.x = val
void setX( VALUE self, VALUE x ) {
	POINT p;
	GetCursorPos( &p );
	SetCursorPos( NUM2INT( x ), p.y );
}

// Mouse.y = val
void setY( VALUE self, VALUE y ) {
	POINT p;
	GetCursorPos( &p );
	SetCursorPos( p.x, NUM2INT( y ) );
}

// Mouse.leftClick?()
VALUE getLeftClick( VALUE self ) {
	if ( GetKeyState( VK_LBUTTON ) < 0 )
		return Qtrue;
	else
		return Qfalse;
}

// Mouse.rightClick?()
VALUE getRightClick( VALUE self ) {
	if ( GetKeyState( VK_RBUTTON ) < 0 )
		return Qtrue;
	else
		return Qfalse;
}

// Mouse.click?( Mouse::VK_CODE )
VALUE clicked( VALUE self, VALUE VK_CODE ) {
	if ( GetKeyState( NUM2INT( VK_CODE ) ) < 0 )
		return Qtrue;
	else
		return Qfalse;
}

// Mouse.rightClick()
void rightClick( VALUE self ) {
	mouse_event( MOUSEEVENTF_RIGHTDOWN, 0, 0, 0, 0 );
	mouse_event( MOUSEEVENTF_RIGHTUP, 0, 0, 0, 0 );
}

// Mouse.leftClick()
void leftClick( VALUE self ) {
	mouse_event( MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0 );
	mouse_event( MOUSEEVENTF_LEFTUP, 0, 0, 0, 0 );
}

// Mouse.middleClick()
void middleClick( VALUE self ) {
	mouse_event( MOUSEEVENTF_MIDDLEDOWN, 0, 0, 0, 0 );
	mouse_event( MOUSEEVENTF_MIDDLEUP, 0, 0, 0, 0 );
}

// Mouse.rollWhell( val )
void moveWheel( VALUE self, VALUE amount ) {
	mouse_event( MOUSEEVENTF_WHEEL, 0, 0, NUM2INT( amount ), 0 );
}

// Mouse.rollWhellUp( val )
void rollWheelUp( VALUE self, VALUE amount ) {
	int a = ( NUM2INT( amount ) >= 0 ? NUM2INT( amount ) : -NUM2INT( amount ) );
	mouse_event( MOUSEEVENTF_WHEEL, 0, 0, a, 0 );
}

// Mouse.rollWheelDown( val )
void rollWheelDown( VALUE self, VALUE amount ) {
	int a = ( NUM2INT( amount ) >= 0 ? NUM2INT( amount ) : -NUM2INT( amount ) );
	mouse_event( MOUSEEVENTF_WHEEL, 0, 0, -a, 0 );
}

VALUE isCursorMoving( VALUE self, VALUE wait ) {
	POINT p1,p2;
	GetCursorPos( &p1 );
	Sleep( NUM2INT( wait ) );
	GetCursorPos( &p2 );
	if ( ( p1.x - p2.x != 0 ) || ( p1.y - p2.y != 0 ) )
		return Qtrue;
	else
		return Qfalse;
}


void Init_mouse( void ) {
	VALUE mMouse = rb_define_module_under( mWin32, "Mouse" );

	rb_define_singleton_method( mMouse, "x", getCursorX, 0 );
	rb_define_singleton_method( mMouse, "y", getCursorY, 0 );
	rb_define_singleton_method( mMouse, "x=", RUBY_METHOD_FUNC(setX), 1 );
	rb_define_singleton_method( mMouse, "y=", RUBY_METHOD_FUNC(setY), 1 );
	rb_define_singleton_method( mMouse, "setPos", RUBY_METHOD_FUNC(setCursorPos), 2 );
	rb_define_singleton_method( mMouse, "leftClick?", getLeftClick, 0 );
	rb_define_singleton_method( mMouse, "rightClick?", getRightClick, 0 );
	rb_define_singleton_method( mMouse, "click?", clicked, 1 );
	rb_define_singleton_method( mMouse, "rightClick", RUBY_METHOD_FUNC(rightClick), 0 );
	rb_define_singleton_method( mMouse, "leftClick", RUBY_METHOD_FUNC(leftClick), 0 );
	rb_define_singleton_method( mMouse, "middleClick", RUBY_METHOD_FUNC(middleClick), 0 );
	rb_define_singleton_method( mMouse, "rollWheel", RUBY_METHOD_FUNC(moveWheel), 1 );
	rb_define_singleton_method( mMouse, "rollWheelUp", RUBY_METHOD_FUNC(rollWheelUp), 1 );
	rb_define_singleton_method( mMouse, "rollWheelDown", RUBY_METHOD_FUNC(rollWheelDown), 1 );
	rb_define_singleton_method( mMouse, "moving?", isCursorMoving, 1 );

	rb_define_const( mMouse, "M_LBUTTON_DOWN", INT2FIX( MOUSEEVENTF_LEFTDOWN ) );
	rb_define_const( mMouse, "M_LBUTTON_UP", INT2FIX( MOUSEEVENTF_LEFTUP ) );
	rb_define_const( mMouse, "M_RBUTTON_DOWN", INT2FIX( MOUSEEVENTF_RIGHTDOWN ) );
	rb_define_const( mMouse, "M_RBUTTON_UP", INT2FIX( MOUSEEVENTF_RIGHTUP ) );
	rb_define_const( mMouse, "M_MBUTTON_DOWN", INT2FIX( MOUSEEVENTF_MIDDLEDOWN ) );
	rb_define_const( mMouse, "M_MBUTTON_UP", INT2FIX( MOUSEEVENTF_MIDDLEUP ) );
}