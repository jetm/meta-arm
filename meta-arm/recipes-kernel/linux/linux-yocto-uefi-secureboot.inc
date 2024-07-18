KERNEL_FEATURES += "cfg/efi-ext.scc"

DEPENDS += "sbsigntool-native"

do_compile:append() {
	KERNEL_IMAGE=$(find "${B}" -name "${KERNEL_IMAGETYPE}" -print -quit)

    "${STAGING_BINDIR_NATIVE}/sbsign" \
        --key "${UEFI_SB_KEYS_DIR}/db.key" \
        --cert "${UEFI_SB_KEYS_DIR}/db.crt" \
        "${KERNEL_IMAGE}" \
        --output "${KERNEL_IMAGETYPE}.signed"

	install -m 0644 "${KERNEL_IMAGETYPE}.signed" "${KERNEL_IMAGE}"
}

RRECOMMENDS:${PN} += "kernel-module-efivarfs"
RRECOMMENDS:${PN} += "kernel-module-efivars"