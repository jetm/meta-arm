inherit uefi-sb-keys

# Detected by passing kernel parameter
QB_KERNEL_ROOT = ""

# kernel is in the image, should not be loaded separately
QB_DEFAULT_KERNEL = "none"

KERNEL_IMAGETYPE = "Image"

WKS_FILE = "efi-disk-no-swap.wks.in"

MACHINE_FEATURES += "efi"

EFI_PROVIDER = "grub-efi"
IMAGE_INSTALL += "grub-efi"

IMAGE_INSTALL += "systemd util-linux bash coreutils efivar"

EXTRA_IMAGE_FEATURES += "empty-root-password allow-root-login"