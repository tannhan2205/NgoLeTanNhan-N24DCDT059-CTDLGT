$binPath = "C:\Users\anhth\AppData\Local\Microsoft\WinGet\Packages\BrechtSanders.WinLibs.POSIX.UCRT.LLVM_Microsoft.Winget.Source_8wekyb3d8bbwe\mingw64\bin"
$env:PATH = "$binPath;$env:PATH"

Set-Location $PSScriptRoot

Write-Output "--- BIEN DICH VOI STATIC LINKING DE CHAY DOC LAP MOI MAY ---"
& "$binPath\g++.exe" -O2 -static -std=c++14 src/main.cpp -o main.exe
& "$binPath\g++.exe" -O2 -static -std=c++14 test/runtests.cpp -o test/runtests.exe

Write-Output "`n--- CHAY BO KIEM THU ---"
& .\test\runtests.exe

Write-Output "`n--- CHAY VI DU 1 ---"
& .\main.exe --vd1

Write-Output "`n--- CHAY VI DU 2 ---"
& .\main.exe --vd2
