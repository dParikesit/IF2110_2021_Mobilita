@echo off
if "%~1"=="clean" (
    goto CLEAN
) else (
    goto MAIN
)

:CLEAN
echo [0] Deleting older cmake cache...
@rd /s /q build
@rd /s /q bin

:MAIN
echo [1] Building Makefiles...
@cmake.exe -G "MinGW Makefiles" -H. -B./build
echo [2] Running Make...
@cd build
@make.exe
goto END

:END
@cd ..
echo [3] Done!
