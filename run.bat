@echo off
echo --- Building...
g++ main/main.cpp -o output/build -std=c++17 -g

REM Stop if the build failed
if %errorlevel% neq 0 (
    echo --- Build failed!
    exit /b %errorlevel%
)

echo --- Running...
REM This line is the change.
REM It runs your compiler and passes all arguments from the script (%*)
REM to the executable.
.\output\build.exe .\src\%*