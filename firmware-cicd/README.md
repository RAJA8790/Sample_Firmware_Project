# Firmware CI/CD Sample Project

A complete sample CI/CD pipeline for embedded/firmware development using
GitHub Actions, ARM cross-compilation, QEMU emulation, and Unity unit tests.

---

## Project Structure

```
firmware-cicd/
├── src/
│   ├── main.c          # Main firmware entry point
│   ├── led.c / led.h   # LED control module
│   ├── button.h        # Button interface
│   ├── system.h        # System tick interface
│   └── stubs.c         # Hardware stubs for testing
├── tests/
│   └── test_led.c      # Unit tests for LED module (Unity framework)
├── unity/
│   └── unity.h         # Minimal Unity test framework
├── scripts/
│   └── verify_artifact.sh  # Artifact verification script
├── .github/
│   └── workflows/
│       └── firmware-ci.yml  # GitHub Actions pipeline
├── Makefile
└── README.md
```

---

## Pipeline Stages

```
Push / PR
    │
    ▼
[1] Static Analysis   ← cppcheck scans all C source files
    │
    ▼
[2] Unit Tests        ← build and run tests natively with gcc
    │
    ▼
[3] Cross Compile     ← arm-none-eabi-gcc builds for ARM Cortex-M4
    │                    Output: firmware_sample.bin + .elf
    ▼
[4] Artifact Verify   ← checksum, size, version checks
    │
    ▼
[5] QEMU Simulate     ← boots firmware on ARM emulator
    │
    ▼
[6] Release           ← GitHub Release created (main branch only)
```

---

## Local Setup

### Prerequisites

```bash
# Ubuntu/Debian
sudo apt-get install gcc gcc-arm-none-eabi binutils-arm-none-eabi cppcheck qemu-system-arm

# macOS (Homebrew)
brew install arm-none-eabi-gcc cppcheck qemu
```

### Commands

```bash
# Run unit tests (no ARM toolchain needed)
make test

# Cross-compile for ARM
make all

# Verify artifact
make checksum
./scripts/verify_artifact.sh build/firmware_sample.bin 1.0.0

# Run on QEMU emulator
qemu-system-arm \
  -machine lm3s6965evb \
  -kernel build/firmware_sample.elf \
  -nographic \
  -semihosting-config enable=on,target=native

# Clean build
make clean
```

---

## How to Push to GitHub

```bash
cd firmware-cicd
git init
git add .
git commit -m "Initial firmware CI/CD project"
git remote add origin https://github.com/<your-username>/firmware-cicd.git
git push -u origin main
```

The GitHub Actions pipeline will trigger automatically on push.

---

## Key Concepts Demonstrated

| Concept | Where |
|---|---|
| Cross-compilation | Makefile, Stage 3 in pipeline |
| Artifact verification | scripts/verify_artifact.sh, Stage 4 |
| Unit testing (embedded) | tests/test_led.c, Stage 2 |
| Static analysis | cppcheck, Stage 1 |
| QEMU emulation | Stage 5 in pipeline |
| Artifact storage | GitHub Actions artifacts |
| Release management | GitHub Releases, Stage 6 |
| Self-hosted runners | Can swap `ubuntu-latest` with `self-hosted` |
