FILESEXTRAPATHS:prepend := "${THISDIR}/${PN}:"

SRC_URI += "file://uefi-secureboot.cfg"

UBOOT_BOARDDIR = "${S}/board/emulation/qemu-arm"
UBOOT_ENV_NAME = "qemu-arm.env"

DEPENDS += 'python3-pyopenssl-native'

do_compile:prepend() {
    export CRYPTOGRAPHY_OPENSSL_NO_LEGACY=1

    "${S}"/tools/efivar.py set -i "${S}"/ubootefi.var -n pk  -d "${UEFI_SB_KEYS_DIR}"/PK.esl  -t file
    "${S}"/tools/efivar.py set -i "${S}"/ubootefi.var -n kek -d "${UEFI_SB_KEYS_DIR}"/KEK.esl -t file
    "${S}"/tools/efivar.py set -i "${S}"/ubootefi.var -n db  -d "${UEFI_SB_KEYS_DIR}"/db.esl  -t file
    "${S}"/tools/efivar.py set -i "${S}"/ubootefi.var -n dbx -d "${UEFI_SB_KEYS_DIR}"/dbx.esl -t file
    "${S}"/tools/efivar.py print -i "${S}"/ubootefi.var
}
