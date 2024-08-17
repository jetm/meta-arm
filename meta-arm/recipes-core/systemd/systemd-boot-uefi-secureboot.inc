DEPENDS += 'gen-uefi-sb-keys'
DEPENDS += "sbsigntool-native"

inherit sbsign

SBSIGN_KEY = "${UEFI_SB_KEYS_DIR}/db.key"
SBSIGN_CERT = "${UEFI_SB_KEYS_DIR}/db.crt"
SBSIGN_TARGET_BINARY = "${B}/src/boot/efi/systemd-boot${EFI_ARCH}.efi"

do_compile:append() {
    do_sbsign
}
