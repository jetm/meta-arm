# SPDX-License-Identifier: MIT

SUMMARY = "Generate UEFI keys for secure boot"
LICENSE = "MIT"
LIC_FILES_CHKSUM = "file://${COMMON_LICENSE_DIR}/MIT;md5=0835ade698e0bcf8506ecda2f7b4f302"

DEPENDS += "bash-native"
DEPENDS += "coreutils-native"
DEPENDS += "efitools-native"
DEPENDS += "openssl-native"

SRC_URI = "file://${UEFI_SB_KEYS_DIR}/gen_uefi_keys.sh"

UNPACKDIR = "${S}"

do_fetch[noexec] = "1"
do_patch[noexec] = "1"
do_compile[noexec] = "1"
do_configure[noexec] = "1"

do_install() {
    ${UEFI_SB_KEYS_DIR}/gen_uefi_keys.sh ${UEFI_SB_KEYS_DIR}
}

FILES:${PN} = "${UEFI_SB_KEYS_DIR}/*.key"
FILES:${PN} += "${UEFI_SB_KEYS_DIR}/*.crt"
