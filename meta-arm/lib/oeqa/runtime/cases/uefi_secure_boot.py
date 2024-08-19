#
# SPDX-License-Identifier: MIT
#

import os

from oeqa.runtime.case import OERuntimeTestCase
from oeqa.runtime.decorator.package import OEHasPackage
from oeqa.core.decorator.oetimeout import OETimeout


class UEFI_SB_TestSuite(OERuntimeTestCase):
    """
    Validate Secure Boot is Enabled
    """

    @OETimeout(1300)
    def test_uefi_secure_boot(self):
        # Validate Secure Boot is enabled by checking
        # 8be4df61-93ca-11d2-aa0d-00e098032b8c-SecureBoot.
        # The GUID '8be4df61-93ca-11d2-aa0d-00e098032b8c' is a well-known
        # identifier for the Secure Boot UEFI variable. By checking the value of
        # this variable, specifically
        # '8be4df61-93ca-11d2-aa0d-00e098032b8c-SecureBoot', we can determine
        # whether Secure Boot is enabled or not. This variable is set by the
        # UEFI firmware to indicate the current Secure Boot state. If the
        # variable is set to a value of '0x1' (or '1'), it indicates that Secure
        # Boot is enabled. If the variable is set to a value of '0x0' (or '0'),
        # it indicates that Secure Boot is disabled.
        cmd = "efivar -d -n 8be4df61-93ca-11d2-aa0d-00e098032b8c-SecureBoot"
        status, output = self.target.run(cmd, timeout=120)
        self.assertEqual(output, "1", msg="\n".join([cmd, output]))
