$binPath = "C:\Users\anhth\AppData\Local\Microsoft\WinGet\Packages\BrechtSanders.WinLibs.POSIX.UCRT.LLVM_Microsoft.Winget.Source_8wekyb3d8bbwe\mingw64\bin"
if (Test-Path "$binPath\g++.exe") {
    $env:PATH = "$binPath;$env:PATH"
}

Set-Location $PSScriptRoot

Write-Output "--- BIEN DICH VOI STATIC LINKING DE CHAY DOC LAP MOI MAY ---"
& g++ -O2 -static -std=c++14 src/main.cpp -o main.exe
& g++ -O2 -static -std=c++14 test/runtests.cpp -o test/runtests.exe

Write-Output "`n--- CHAY BO KIEM THU 14 CA DOC LAP ---"
& .\test\runtests.exe

Write-Output "`n--- CHAY VI DU 1 PHIEU GIAO ---"
& .\main.exe --vd1

Write-Output "`n--- CHAY VI DU 2 PHIEU GIAO ---"
& .\main.exe --vd2
