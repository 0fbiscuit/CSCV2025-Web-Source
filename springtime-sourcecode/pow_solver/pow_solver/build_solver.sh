#!/bin/bash

echo "[*] Building C PoW solver..."

# Check if OpenSSL is installed
if ! dpkg -l | grep -q libssl-dev; then
    echo "[*] Installing libssl-dev..."
    sudo apt-get update
    sudo apt-get install -y libssl-dev
fi

# Check if GCC is installed
if ! command -v gcc &> /dev/null; then
    echo "[*] Installing GCC..."
    sudo apt-get update
    sudo apt-get install -y gcc
fi

# Check if Make is installed
if ! command -v make &> /dev/null; then
    echo "[*] Installing Make..."
    sudo apt-get update
    sudo apt-get install -y make
fi
# Build
make

if [ -f "pow_solver" ]; then
    echo "[+] C solver built successfully!"
    echo "[*] Testing solver..."
    ./pow_solver "challengeme" 6
    echo "[+] Test completed!"
else
    echo "[-] Build failed!"
    exit 1
fi