inherit uefi-sb-keys

WKS_FILE = "efi-disk-no-swap.wks.in"

# Detected by passing kernel parameter
QB_KERNEL_ROOT = ""

# kernel is in the image, should not be loaded separately
QB_DEFAULT_KERNEL = "none"

KERNEL_IMAGETYPE = "Image"

IMAGE_INSTALL += "systemd"
