KERNEL_FEATURES += "cfg/efi-ext.scc"

DEPENDS += 'gen-uefi-sb-keys'

inherit sbsign

SBSIGN_KEY = "${UEFI_SB_KEYS_DIR}/db.key"
SBSIGN_CERT = "${UEFI_SB_KEYS_DIR}/db.crt"

# shell variable set inside do_compile task
SBSIGN_TARGET_BINARY = "$KERNEL_IMAGE"

do_compile:append() {
    KERNEL_IMAGE=$(find ${B} -name ${KERNEL_IMAGETYPE} -print -quit)
    do_sbsign
}

RRECOMMENDS:${PN} += "kernel-module-efivarfs"
RRECOMMENDS:${PN} += "kernel-module-efivars"
