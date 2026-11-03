@echo off
title Bien dich va Chay kiem thu - DT022
cd /d "%~dp0"
powershell.exe -NoProfile -ExecutionPolicy Bypass -File "%~dp0build_and_run.ps1"
echo.
pause

