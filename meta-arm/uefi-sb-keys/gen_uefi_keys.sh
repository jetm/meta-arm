#!/bin/bash
#
# SPDX-License-Identifier: MIT
#

set -eux

KEYS_PATH=${1:-./}
SUBJECT="/CN=Linaro_LEDGE/"
GUID="11111111-2222-3333-4444-123456789abc"

openssl req -x509 -sha256 -newkey rsa:2048 -subj "${SUBJECT}" \
    -keyout "${KEYS_PATH}"/PK.key -out "${KEYS_PATH}"/PK.crt \
    -nodes -days 3650
cert-to-efi-sig-list -g ${GUID} \
    "${KEYS_PATH}"/PK.crt "${KEYS_PATH}"/PK.esl
sign-efi-sig-list -c "${KEYS_PATH}"/PK.crt -k "${KEYS_PATH}"/PK.key \
    "${KEYS_PATH}"/PK "${KEYS_PATH}"/PK.esl "${KEYS_PATH}"/PK.auth

for key in KEK db dbx; do
    openssl req -x509 -sha256 -newkey rsa:2048 -subj "${SUBJECT}" \
        -keyout "${KEYS_PATH}"/${key}.key -out "${KEYS_PATH}"/${key}.crt \
        -nodes -days 3650
    cert-to-efi-sig-list -g ${GUID} \
        "${KEYS_PATH}"/${key}.crt "${KEYS_PATH}"/${key}.esl
    sign-efi-sig-list -c "${KEYS_PATH}"/PK.crt -k "${KEYS_PATH}"/PK.key \
        "${KEYS_PATH}"/${key} "${KEYS_PATH}"/${key}.esl "${KEYS_PATH}"/${key}.auth
done

# Empty cert for testing
touch "${KEYS_PATH}"/noPK.esl
sign-efi-sig-list -c "${KEYS_PATH}"/PK.crt -k "${KEYS_PATH}"/PK.key \
    "${KEYS_PATH}"/PK "${KEYS_PATH}"/noPK.esl "${KEYS_PATH}"/noPK.auth
