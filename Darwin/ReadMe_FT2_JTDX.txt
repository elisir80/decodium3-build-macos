FT2 + JTDX shared-memory coexistence on macOS
=============================================

Problem
-------
If both applications install their own LaunchDaemon, each can overwrite
kern.sysv.shmmax at boot. If JTDX sets shmmax=20971520 (20MB), FT2 fails
to start because it needs about 48MB.

Use one daemon only
-------------------
Disable existing per-app daemons, then enable the shared FT2/JTDX daemon:

  sudo launchctl bootout system /Library/LaunchDaemons/com.jtdx.sysctl.plist 2>/dev/null || true
  sudo launchctl bootout system /Library/LaunchDaemons/com.wsjtx.sysctl.plist 2>/dev/null || true

  sudo mv /Library/LaunchDaemons/com.jtdx.sysctl.plist /Library/LaunchDaemons/com.jtdx.sysctl.plist.disabled 2>/dev/null || true
  sudo mv /Library/LaunchDaemons/com.wsjtx.sysctl.plist /Library/LaunchDaemons/com.wsjtx.sysctl.plist.disabled 2>/dev/null || true

  sudo cp /Volumes/WSJT-X/com.ft2.jtdx.sysctl.plist /Library/LaunchDaemons/
  sudo chown root:wheel /Library/LaunchDaemons/com.ft2.jtdx.sysctl.plist
  sudo chmod 644 /Library/LaunchDaemons/com.ft2.jtdx.sysctl.plist
  sudo launchctl bootstrap system /Library/LaunchDaemons/com.ft2.jtdx.sysctl.plist

Reboot and verify
-----------------
After reboot, check:

  sysctl kern.sysv.shmmax kern.sysv.shmall

Expected values:
  kern.sysv.shmmax: 104857600
  kern.sysv.shmall: 51200

Notes
-----
- `shmmax` is the maximum size for one shared-memory segment.
- `shmall` is total shared-memory capacity in pages (4096 bytes/page).
- Using a single daemon avoids non-deterministic "last writer wins" behavior.
