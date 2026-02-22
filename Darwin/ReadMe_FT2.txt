Decodium 3 FT2 macOS package notes
==================================

What is in this DMG
-------------------
- `ft2.app`
- `com.ft2.jtdx.sysctl.plist`
- `ReadMe_FT2_JTDX.txt`

Which installer should I use?
-----------------------------
Recommended: use the `.pkg` installer from the GitHub release page.

The PKG installer:
- installs `ft2.app` in `/Applications`;
- installs and loads `com.ft2.jtdx.sysctl.plist`;
- applies shared-memory sysctl values required by FT2/JTDX coexistence.

Manual DMG install (advanced)
-----------------------------
If you manually drag `ft2.app` from DMG, shared-memory sysctl values are not
configured automatically. If startup fails with shared-memory size errors, you
must install `com.ft2.jtdx.sysctl.plist` yourself.

For coexistence steps with JTDX, read:
- `ReadMe_FT2_JTDX.txt`
