@echo off

REM 保存当前路径
set pre=%CD%

REM 进入run.bat所在目录
cd %~dp0

call "C:\Program Files (x86)\Microsoft Visual Studio 12.0\VC\bin\amd64\vcvars64.bat"

mkdir build

cmake -S . -B ./build/ -GNinja

cmake --build ./build/

REM 回到运行run.bat前目录
cd %pre%

