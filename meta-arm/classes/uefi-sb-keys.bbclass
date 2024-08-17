# Validate UEFI keys
python __anonymous () {
    if d.getVar("UEFI_SB_KEYS_DIR", False) is None:
        raise bb.parse.SkipRecipe("UEFI_SB_KEYS_DIR is not set.")

    # keys used for UEFI secure boot
    uefi_sb_keys = d.getVar("UEFI_SB_KEYS_DIR")

    keys_to_check = [
        uefi_sb_keys + "/PK.esl",
        uefi_sb_keys + "/KEK.esl",
        uefi_sb_keys + "/dbx.esl",
        uefi_sb_keys + "/db.esl",
        uefi_sb_keys + "/db.key",
        uefi_sb_keys + "/db.crt",
    ]

    missing_keys = [f for f in keys_to_check if not os.path.exists(f)]

    if missing_keys:
        raise bb.parse.SkipRecipe("Required missing keys: %s" % (", ".join(missing_keys), )
            + ".\nRun %s/gen_uefi_keys.sh to generate missing keys." % uefi_sb_keys)

}
