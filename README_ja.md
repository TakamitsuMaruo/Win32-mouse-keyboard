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

## メソッド  
### Win32::Mouse  
#### Mouse.x()  
マウスカーソルのx座標を返します。  
#### Mouse.y()  
マウスカーソルのy座標を返します。  
#### Mouse.x=( val )  
マウスカーソルのx座標にvalを代入します。  
#### Mouse.y=( val )  
マウスカーソルのy座標にvalを代入します。
#### Mouse.setPos( x, y )
マウスカーソルを(x,y)に移動します。
#### Mouse.leftClick?()
左クリックされていれば真を、されていなければ偽を返します。
#### Mouse.rightClick?()
右クリックされていれば真を、されていなければ偽を返します。
#### Mouse.click?( VK_CODE )
定数VK_CODEに対応するキーが押しこまれていれば真を、押しこまれていなければ偽を返します。  
#### Mouse.leftClick()
左クリックを発生させます。
#### Mouse.rightClick()
右クリックを発生させます。
#### Mouse.middleClick()
マウスホイール押し込みを発生させます。
#### Mouse.rollWheel( amount )
マウスホイールをamountだけ回転させます。
amountの値が正の時は上方向にスクロールし、そうでなければ下方向にスクロールします。
#### Mouse.rollWheelUp( amount ), Mouse.rollWheelDown( amount )
amountの絶対値分だけ上または下方向にスクロールします。
#### Mouse.moving?( wait )
waitミリ秒ごとにカーソルの座標を比較し、動いているかどうかの判定を行います。

### Win32::KeyBoard
工事中

## 定数
### Win32::Mouse
#### M_LBUTTON_UP  
マウス左ボタンが押されていない状態を表します。
#### M_LBUTTON_DOWN  
マウス左ボタンが押されている状態を表します。
#### M_RBUTTON_UP  
マウス右ボタンが押されていない状態を表します。
#### M_RBUTTON_DOWN  
マウス右ボタンが押されている状態を表します。
#### M_MBUTTON_UP  
マウスホイールが押しこまれていない状態を表します。
#### M_MBUTTON_DOWN  
マウスホイールが押しこまれている状態を表します。
