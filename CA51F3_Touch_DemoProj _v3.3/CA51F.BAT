SET C51INC=F:\Keil\C51\Inc;F:\Keil\C51\Inc\Cast
SET C51LIB=F:\Keil\C51\Lib
SET CPU_TYPE=R8051XC2
SET CPU_VENDOR=CAST, Inc.
SET UV2_TARGET=CA51F
SET CPU_XTAL=0x016E3600
"F:\Keil\C51\BIN\C51.EXE" @".\hex\main.__i"
"F:\Keil\C51\BIN\C51.EXE" @".\hex\delay.__i"
"F:\Keil\C51\BIN\C51.EXE" @".\hex\system_clock.__i"
"F:\Keil\C51\BIN\C51.EXE" @".\hex\uart.__i"
"F:\Keil\C51\BIN\C51.EXE" @".\hex\interrupt.__i"
"F:\Keil\C51\BIN\C51.EXE" @".\hex\debug.__i"
"F:\Keil\C51\BIN\C51.EXE" @".\hex\ts_api.__i"
"F:\Keil\C51\BIN\A51.EXE" @".\hex\STARTUP._ia"
"F:\Keil\C51\BIN\LX51.EXE" @".\hex\ca51f3.lnp"
"F:\Keil\C51\BIN\OHX51.EXE" ".\hex\ca51f3" HEX
