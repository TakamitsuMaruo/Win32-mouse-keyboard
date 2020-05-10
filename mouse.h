VALUE getCursorX( VALUE self  );
VALUE getCursorY( VALUE self  );
void setCursorPos( VALUE self , VALUE x, VALUE y );
void setX( VALUE self, VALUE x );
void setY( VALUE self, VALUE y );
VALUE getLeftClick( VALUE self );
VALUE getRightClick( VALUE self );
VALUE clicked( VALUE self, VALUE VK_CODE );
void rightClick( VALUE self );
void leftClick( VALUE self );
void middleClick( VALUE self );
void moveWheel( VALUE self, VALUE amount );
void rollWheelUp( VALUE self, VALUE amount );
void rollWheelDown( VALUE self, VALUE amount );
VALUE isCursorMoving( VALUE self, VALUE wait );

void Init_mouse();