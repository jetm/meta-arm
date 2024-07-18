require ${@bb.utils.contains('MACHINE_FEATURES', 'uefi-secureboot', 'systemd-uefi-secureboot.inc', '', d)}
