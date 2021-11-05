@echo off
if "%~1"=="clean" (
    goto CLEAN
) else (
    goto MAIN
)

:CLEAN
echo [0] Deleting older cmake cache...
@rd /s /q CMakeFiles
del cmake_install.cmake /q
del CMakeCache.txt /q
del Makefile /q

:MAIN
echo [1] Building Makefiles...
@cmake.exe -G "MinGW Makefiles" -H. -B.
echo [2] Running Make...
@make.exe
goto END

:END
echo [3] Done building binary in bin/main.exe
