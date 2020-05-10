require 'mkmf'

have_header("winsock2.h")
have_header("ruby.h")
have_header("string.h")

create_makefile('win32')