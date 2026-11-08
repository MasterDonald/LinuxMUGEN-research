# Original environment (2002)

| Component | Most likely original | Evidence | Class |
|---|---|---|---|
| Distribution used to build | Mandrake Linux 8.1 | GCC ident "Mandrake Linux 8.1 2.96-0.62mdk"; glibc 2.2.4 RPM build paths | STRONGLY INFERRED |
| Kernel | 2.2.x or 2.4.x i386 | ABI note 2.2.5; readme mentions 2.4.X `/dev/sound/dsp` | VERIFIED (range) |
| X server | XFree86 4.x with MIT-SHM, DGA, VidMode | linked client libraries | STRONGLY INFERRED |
| Sound | OSS (kernel drivers) or ESD | readme, drivers | VERIFIED |
| Hardware | Pentium 90-200, 32-64 MB RAM, 16-bit colour display, PC keyboard, optional joystick on gameport (`/dev/js0`) | readme | VERIFIED (stated) |

Because the executable is static, the closest faithful environment is any
i386 Linux of 2001-2003 with XFree86 4 and OSS (e.g. Mandrake 8.1/8.2, Red
Hat 7.x, Debian 3.0) (STRONGLY INFERRED). A VM image with such a system is
the reference for behavioural comparison with the reconstruction.
