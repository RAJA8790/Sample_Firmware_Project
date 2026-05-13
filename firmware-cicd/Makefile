# ─────────────────────────────────────────────────────────────────────────────
# Firmware CI/CD Sample — Makefile
#
# Targets:
#   make all        — cross-compile firmware for ARM (needs arm-none-eabi-gcc)
#   make native     — build native binary (for local dev/testing)
#   make test       — build and run unit tests (native gcc)
#   make verify     — verify artifact checksum
#   make clean      — remove build outputs
# ─────────────────────────────────────────────────────────────────────────────

# ── Project config ────────────────────────────────────────────────────────────
PROJECT     := firmware_sample
VERSION     := 1.0.0
BUILD_DIR   := build
SRC_DIR     := src
TEST_DIR    := tests
UNITY_DIR   := unity

# ── Source files ──────────────────────────────────────────────────────────────
SRCS        := $(SRC_DIR)/main.c \
               $(SRC_DIR)/led.c  \
               $(SRC_DIR)/stubs.c

TEST_SRCS   := $(TEST_DIR)/test_led.c \
               $(SRC_DIR)/led.c

# ── Cross-compiler (ARM) ──────────────────────────────────────────────────────
CC_ARM      := arm-none-eabi-gcc
CFLAGS_ARM  := -mcpu=cortex-m4 \
               -mthumb         \
               -O2             \
               -Wall           \
               -Wextra         \
               -I$(SRC_DIR)    \
               -DTARGET_ARM

LDFLAGS_ARM := --specs=nosys.specs

# ── Native compiler (for tests) ───────────────────────────────────────────────
CC_NATIVE   := gcc
CFLAGS_NATIVE := -O0 -g -Wall -Wextra -I$(SRC_DIR) -I$(UNITY_DIR) -DTARGET_NATIVE

# ── Output artifacts ──────────────────────────────────────────────────────────
ELF_OUT     := $(BUILD_DIR)/$(PROJECT).elf
BIN_OUT     := $(BUILD_DIR)/$(PROJECT).bin
TEST_BIN    := $(BUILD_DIR)/test_runner
CHECKSUM    := $(BUILD_DIR)/$(PROJECT).sha256

# ─────────────────────────────────────────────────────────────────────────────
# Default target — cross-compile for ARM
# ─────────────────────────────────────────────────────────────────────────────
all: $(BUILD_DIR) $(BIN_OUT)

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(ELF_OUT): $(SRCS) | $(BUILD_DIR)
	@echo "[BUILD] Cross-compiling for ARM Cortex-M4..."
	$(CC_ARM) $(CFLAGS_ARM) $(LDFLAGS_ARM) $(SRCS) -o $@
	@echo "[BUILD] ELF artifact: $@"

$(BIN_OUT): $(ELF_OUT)
	@echo "[BUILD] Converting ELF to binary..."
	arm-none-eabi-objcopy -O binary $< $@
	@echo "[BUILD] Firmware binary: $@"
	arm-none-eabi-size $<

# ─────────────────────────────────────────────────────────────────────────────
# Native build — useful for local development without ARM toolchain
# ─────────────────────────────────────────────────────────────────────────────
native: $(BUILD_DIR)
	@echo "[BUILD] Building native binary..."
	$(CC_NATIVE) $(CFLAGS_NATIVE) $(SRCS) -o $(BUILD_DIR)/$(PROJECT)_native
	@echo "[BUILD] Native binary: $(BUILD_DIR)/$(PROJECT)_native"

# ─────────────────────────────────────────────────────────────────────────────
# Unit tests — build and run with native gcc
# ─────────────────────────────────────────────────────────────────────────────
test: $(BUILD_DIR)
	@echo "[TEST] Building test runner..."
	$(CC_NATIVE) $(CFLAGS_NATIVE) $(TEST_SRCS) -o $(TEST_BIN)
	@echo "[TEST] Running unit tests..."
	@echo "────────────────────────────────"
	./$(TEST_BIN)
	@echo "────────────────────────────────"

# ─────────────────────────────────────────────────────────────────────────────
# Artifact verification — generate or verify SHA256 checksum
# ─────────────────────────────────────────────────────────────────────────────
checksum: $(BIN_OUT)
	@echo "[VERIFY] Generating checksum..."
	sha256sum $(BIN_OUT) > $(CHECKSUM)
	@cat $(CHECKSUM)
	@echo "[VERIFY] Checksum saved: $(CHECKSUM)"

verify: $(CHECKSUM)
	@echo "[VERIFY] Verifying artifact integrity..."
	sha256sum --check $(CHECKSUM)
	@echo "[VERIFY] Artifact OK"

# ─────────────────────────────────────────────────────────────────────────────
# Clean
# ─────────────────────────────────────────────────────────────────────────────
clean:
	@echo "[CLEAN] Removing build artifacts..."
	rm -rf $(BUILD_DIR)
	@echo "[CLEAN] Done"

.PHONY: all native test checksum verify clean
