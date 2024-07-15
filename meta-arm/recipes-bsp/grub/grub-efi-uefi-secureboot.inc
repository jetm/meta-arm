FILESEXTRAPATHS:prepend := "${THISDIR}/files:"

SRC_URI += "file://grub-initial.cfg"
SRC_URI += "file://0001-verifiers-Don-t-return-error-for-deferred-image.patch"

DEPENDS += "sbsigntool-native"

GRUB_PREFIX_DIR ?= "/EFI/BOOT"
EFI_BOOT_PATH ?= "/boot/efi/EFI/BOOT"

do_mkimage() {
    install -d "${D}${EFI_BOOT_PATH}"
    install -m 0600 "${UNPACKDIR}/grub-initial.cfg" "${D}${EFI_BOOT_PATH}/grub.cfg"

    grub-mkimage --disable-shim-lock \
        --prefix="${GRUB_PREFIX_DIR}" \
        --format="${GRUB_TARGET}-efi" \
        --directory="${B}/grub-core" \
        --output="${B}/${GRUB_IMAGE_PREFIX}${GRUB_IMAGE}" \
        ${GRUB_BUILDIN}
}

fakeroot do_sign() {
    "${STAGING_BINDIR_NATIVE}/sbsign" \
        --key "${UEFI_SB_KEYS}/db.key" \
        --cert "${UEFI_SB_KEYS}/db.crt" \
        "${B}/${GRUB_IMAGE_PREFIX}${GRUB_IMAGE}" \
        --output "${B}/${GRUB_IMAGE_PREFIX}${GRUB_IMAGE}.signed"

   install -m 0644 "${B}/${GRUB_IMAGE_PREFIX}${GRUB_IMAGE}.signed" "${B}/${GRUB_IMAGE_PREFIX}${GRUB_IMAGE}"

   install -d "${D}${EFI_BOOT_PATH}"
   install -m 0644 "${B}/${GRUB_IMAGE_PREFIX}${GRUB_IMAGE}.signed" "${D}${EFI_BOOT_PATH}/${GRUB_IMAGE}"
}

addtask sign after do_install before do_deploy do_package

FILES:${PN} += "${EFI_BOOT_PATH}"

CONFFILES:${PN} += "${EFI_BOOT_PATH}/grub.cfg"
