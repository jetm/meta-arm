require ${@bb.utils.contains('MACHINE_FEATURES', 'uefi-secureboot', 'core-image-minimal-uefi-secureboot.inc', '', d)}