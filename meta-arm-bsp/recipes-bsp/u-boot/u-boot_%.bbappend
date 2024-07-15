FILESEXTRAPATHS:prepend := "${THISDIR}/${PN}:"

MACHINE_U-BOOT_REQUIRE ?= ""
MACHINE_U-BOOT_REQUIRE:corstone1000 = "u-boot-corstone1000.inc"
MACHINE_U-BOOT_REQUIRE:fvp-base = "u-boot-fvp-base.inc"
MACHINE_U-BOOT_REQUIRE:juno = "u-boot-juno.inc"
MACHINE_U-BOOT_REQUIRE:tc = "u-boot-tc.inc"
MACHINE_U-BOOT_REQUIRE:qemuarm64-secureboot = "${@bb.utils.contains('MACHINE_FEATURES', 'uefi-secureboot', 'u-boot-qemuarm64-secureboot.inc', '', d)}"

require ${MACHINE_U-BOOT_REQUIRE}

