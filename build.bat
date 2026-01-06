@echo off
setlocal EnableDelayedExpansion

set OUT_FILE=rnd_tests.generated.h

echo Generating %OUT_FILE% ...

:: Header
(
echo #pragma once
echo #include ^<cstddef^>
echo #include ^<cstdint^>
echo.
) > %OUT_FILE%

:: Include all *_rand.h files
set COUNT=0
for %%F in (*_rand.h) do (
    echo #include "%%F" >> %OUT_FILE%
    set NAME=%%~nF
    if "!NAME:~-5!"=="_rand" set NAME=!NAME:~0,-5!
    set NAMES[!COUNT!]=!NAME!
    set /a COUNT+=1
)

echo. >> %OUT_FILE%
set /a LAST_INDEX=COUNT-1

:: Generate static instances
for /L %%I in (0,1,%LAST_INDEX%) do (
    echo static !NAMES[%%I]! inst_%%I; >> %OUT_FILE%
)
echo. >> %OUT_FILE%

:: GetRndTestCount
(
echo inline size_t GetRndTestCount^(^) {
echo   return %COUNT%;
echo }
echo.
) >> %OUT_FILE%

:: GetRndTestName
(
echo inline char const* GetRndTestName^(size_t index^) {
echo   static char const* names[] = {
) >> %OUT_FILE%

for /L %%I in (0,1,%LAST_INDEX%) do (
    echo     "!NAMES[%%I]!", >> %OUT_FILE%
)

(
echo   };
echo   return index ^< %COUNT% ? names[index] : "";
echo }
echo.
) >> %OUT_FILE%

:: RunRndTestInit
(
echo inline void RunRndTestInit^(size_t index, int32_t seed^) {
echo   switch ^(index^) {
) >> %OUT_FILE%

for /L %%I in (0,1,%LAST_INDEX%) do (
    echo     case %%I: { inst_%%I.Init^(seed^); break; } >> %OUT_FILE%
)

(
echo     default: break;
echo   }
echo }
echo.
) >> %OUT_FILE%

:: RunRndTestBody
(
echo inline int32_t RunRndTestBody^(size_t index^) {
echo   switch ^(index^) {
) >> %OUT_FILE%

for /L %%I in (0,1,%LAST_INDEX%) do (
    echo     case %%I: { return inst_%%I.Run^(^); } >> %OUT_FILE%
)

(
echo     default: return 0;
echo   }
echo }
) >> %OUT_FILE%

echo Compiling the code.

g++ main.cpp -o rnd_test.exe

echo Done.
