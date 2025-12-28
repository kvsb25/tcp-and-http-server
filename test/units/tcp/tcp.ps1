# test.ps1

# Compile the C++ files
g++ "..\..\..\src\tcp\tcpServer.cpp" "..\..\..\src\tcp\clientSession.cpp" "tcp.cpp" -o test.exe -lws2_32

# Check if compilation succeeded
if ($LASTEXITCODE -eq 0) {
    Write-Host "Compilation succeeded, running program..."
    .\test.exe
} else {
    Write-Host "Compilation failed. See errors above."
}

# Set-ExecutionPolicy -Scope Process -ExecutionPolicy Bypass; .\tcp.ps1