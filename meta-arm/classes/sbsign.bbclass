# Sign binaries for UEFI secure boot
# Usage in recipes:
#
# Set key and cert files in recipe or machine/distro config:
# SBSIGN_KEY = "db.key"
# SBSIGN_CERT = "db.crt"
#
# Set binary to sign per recipe:
# SBSIGN_TARGET_BINARY = "${B}/binary_to_sign"
#
# Then call do_sbsign() in correct stage of the build
# do_compile:append() {
#     do_sbsign
# }

DEPENDS += "sbsigntool-native"

SBSIGN_KEY ?= "db.key"
SBSIGN_CERT ?= "db.crt"
SBSIGN_TARGET_BINARY ?= "binary_to_sign"

# makes sure changed keys trigger rebuild/re-signing
SRC_URI += "\
    file://${SBSIGN_KEY} \
    file://${SBSIGN_CERT} \
"

# not adding as task since recipes may need to sign binaries at different
# stages. Instead they can call this function when needed by calling this function
do_sbsign() {
    bbnote "Signing ${PN} binary ${SBSIGN_TARGET_BINARY} with ${SBSIGN_KEY} and ${SBSIGN_CERT}"
    ${STAGING_BINDIR_NATIVE}/sbsign \
        --key "${UNPACKDIR}/${SBSIGN_KEY}" \
        --cert "${UNPACKDIR}/${SBSIGN_CERT}" \
        --output  "${SBSIGN_TARGET_BINARY}.signed" \
        "${SBSIGN_TARGET_BINARY}"
    cp "${SBSIGN_TARGET_BINARY}" "${SBSIGN_TARGET_BINARY}.unsigned"
    cp "${SBSIGN_TARGET_BINARY}.signed" "${SBSIGN_TARGET_BINARY}"
}