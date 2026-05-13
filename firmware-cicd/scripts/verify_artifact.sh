#!/bin/bash
# ─────────────────────────────────────────────────────────────────────────────
# verify_artifact.sh
# Validates a firmware binary before it is promoted to production
#
# Usage: ./scripts/verify_artifact.sh <artifact_path> <expected_version>
# Example: ./scripts/verify_artifact.sh build/firmware_sample.bin 1.0.0
# ─────────────────────────────────────────────────────────────────────────────

set -e  # Exit immediately on any error

ARTIFACT=$1
EXPECTED_VERSION=$2
CHECKSUM_FILE="${ARTIFACT}.sha256"

RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
NC='\033[0m' # No Color

pass() { echo -e "${GREEN}  [PASS]${NC} $1"; }
fail() { echo -e "${RED}  [FAIL]${NC} $1"; exit 1; }
info() { echo -e "${YELLOW}  [INFO]${NC} $1"; }

echo ""
echo "════════════════════════════════════════"
echo "   Firmware Artifact Verification"
echo "════════════════════════════════════════"
echo ""

# ── Check 1: Artifact file exists ─────────────────────────────────────────────
info "Checking artifact exists: $ARTIFACT"
if [ ! -f "$ARTIFACT" ]; then
    fail "Artifact not found: $ARTIFACT"
fi
pass "Artifact file exists"

# ── Check 2: File is not empty ────────────────────────────────────────────────
info "Checking artifact is not empty..."
FILESIZE=$(stat -c%s "$ARTIFACT" 2>/dev/null || stat -f%z "$ARTIFACT")
if [ "$FILESIZE" -eq 0 ]; then
    fail "Artifact is empty (0 bytes)"
fi
pass "Artifact size: ${FILESIZE} bytes"

# ── Check 3: Size sanity check (must be > 1KB and < 2MB for our project) ──────
info "Checking artifact size is within expected range..."
MIN_SIZE=100
MAX_SIZE=2097152  # 2MB
if [ "$FILESIZE" -lt "$MIN_SIZE" ]; then
    fail "Artifact too small (${FILESIZE} bytes) — possible corrupt build"
fi
if [ "$FILESIZE" -gt "$MAX_SIZE" ]; then
    fail "Artifact too large (${FILESIZE} bytes) — exceeds 2MB limit"
fi
pass "Artifact size is within expected range"

# ── Check 4: Checksum verification ────────────────────────────────────────────
if [ -f "$CHECKSUM_FILE" ]; then
    info "Verifying SHA256 checksum..."
    if sha256sum --check "$CHECKSUM_FILE" > /dev/null 2>&1; then
        pass "Checksum verified successfully"
    else
        fail "Checksum mismatch — artifact may be corrupted or tampered"
    fi
else
    info "No checksum file found — generating new checksum..."
    sha256sum "$ARTIFACT" > "$CHECKSUM_FILE"
    pass "Checksum generated: $(cat $CHECKSUM_FILE)"
fi

# ── Check 5: ELF sanity (if .elf exists alongside .bin) ───────────────────────
ELF_FILE="${ARTIFACT%.bin}.elf"
if [ -f "$ELF_FILE" ]; then
    info "Checking ELF file format..."
    if file "$ELF_FILE" | grep -q "ELF"; then
        pass "ELF format verified: $(file $ELF_FILE)"
    else
        fail "ELF file format check failed"
    fi
fi

# ── Check 6: Version check ────────────────────────────────────────────────────
if [ -n "$EXPECTED_VERSION" ]; then
    info "Checking artifact version matches: $EXPECTED_VERSION"
    # In a real project you'd extract version from the binary or a version file
    # Here we check a generated version.txt placed by the build
    VERSION_FILE="build/version.txt"
    if [ -f "$VERSION_FILE" ]; then
        ACTUAL_VERSION=$(cat "$VERSION_FILE")
        if [ "$ACTUAL_VERSION" == "$EXPECTED_VERSION" ]; then
            pass "Version matches: $ACTUAL_VERSION"
        else
            fail "Version mismatch — expected $EXPECTED_VERSION, got $ACTUAL_VERSION"
        fi
    else
        info "No version.txt found — skipping version check"
    fi
fi

# ── Summary ───────────────────────────────────────────────────────────────────
echo ""
echo "════════════════════════════════════════"
echo -e "${GREEN}  All checks passed — artifact is valid${NC}"
echo "════════════════════════════════════════"
echo ""
