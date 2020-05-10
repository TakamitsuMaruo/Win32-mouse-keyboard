VALUE isKeyPushed( VALUE self, VALUE VK_CODE );
void pushKey( VALUE self, VALUE VK_CODE );
void pushKeyShift( VALUE self, VALUE VK_CODE );
void typeSent( VALUE self, VALUE str );
VALUE getPushKey( VALUE self );
void Init_keyboard( void );
