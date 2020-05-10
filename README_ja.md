# Win32-mouse-keyboard
Win32apiのマウス、キーボード関係の関数をRuby用に移植

## ビルド
$ ruby extconf.rb  
Makefileが生成されるので  
$ make install  

## Rubyスクリプト内での使い方
require 'win32'  

## モジュール
Win32::Mouse  
Win32::KeyBoard  
include Win32した方が使いやすいかもしれません
