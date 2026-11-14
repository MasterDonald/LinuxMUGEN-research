#Code made by MasterDonald (MD)
#Unpack Linux MUGEN + Modify page 0x08048000~0x08287000 to RWX
#Run: python LinuxMUGEN_unprotectory.py <input_binary> <output_binary>
import shutil
import struct
import subprocess
import sys

def unpack_upx(input_path, temp_unpacked_path):
    print(f"[*] Attempting to unpack UPX binary: {input_path}")
    try:
        # Run upx -d to decompress/unpack the binary
        result = subprocess.run(
            ["upx", "-d", "-o", temp_unpacked_path, input_path],
            stdout=subprocess.PIPE,
            stderr=subprocess.PIPE,
            text=True
        )
        if result.returncode != 0:
            print(f"[-] UPX unpack notice: File might not be packed or requires manual handling. Output:\n{result.stderr.strip()}")
            # Fallback: just copy the file if it wasn't packed
            shutil.copyfile(input_path, temp_unpacked_path)
        else:
            print(f"[+] Successfully unpacked to: {temp_unpacked_path}")
    except FileNotFoundError:
        print("[-] Warning: 'upx' command not found on system PATH. Proceeding with file copy...")
        shutil.copyfile(input_path, temp_unpacked_path)

def patch_elf_permissions(input_path, output_path, target_start, target_end):
    temp_unpacked = output_path + ".tmp"

    # Step 1: Unpack UPX (if applicable) into a temporary destination
    unpack_upx(input_path, temp_unpacked)

    # Step 2: Move the unpacked file to the final output target for patching
    shutil.move(temp_unpacked, output_path)

    with open(output_path, "r+b") as f:
        # Verify ELF magic bytes
        ident = f.read(16)
        if ident[:4] != b"\x7fELF":
            raise ValueError("The provided file is not a valid ELF file.")

        # Check ELF class (1 = 32-bit, 2 = 64-bit)
        elf_class = ident[4]

        if elf_class == 1:
            print("Detected 32-bit ELF file.")
            f.seek(28)
            e_phoff = struct.unpack("<I", f.read(4))[0]
            f.seek(42)
            e_phentsize = struct.unpack("<H", f.read(2))[0]
            f.seek(44)
            e_phnum = struct.unpack("<H", f.read(2))[0]
        elif elf_class == 2:
            print("Detected 64-bit ELF file.")
            f.seek(32)
            e_phoff = struct.unpack("<Q", f.read(8))[0]
            f.seek(54)
            e_phentsize = struct.unpack("<H", f.read(2))[0]
            f.seek(56)
            e_phnum = struct.unpack("<H", f.read(2))[0]
        else:
            raise ValueError(f"Unknown ELF class: {elf_class}")

        print(f"Scanning {e_phnum} program headers...")

        patched_count = 0
        for i in range(e_phnum):
            phdr_offset = e_phoff + (i * e_phentsize)
            f.seek(phdr_offset)
            phdr_data = f.read(e_phentsize)

            if elf_class == 1:
                p_type, p_offset, p_vaddr, p_paddr, p_filesz, p_memsz, p_flags, p_align = struct.unpack("<8I", phdr_data[:32])
                flags_offset = 24  # Correct 32-bit p_flags offset
            else:
                p_type, p_flags, p_offset, p_vaddr, p_paddr, p_filesz, p_memsz, p_align = struct.unpack("<2I6Q", phdr_data[:56])
                flags_offset = 4   # Correct 64-bit p_flags offset

            seg_start = p_vaddr
            seg_end = p_vaddr + p_memsz

            # Check if segment overlaps with the target virtual address range
            if not (seg_end <= target_start or seg_start >= target_end):
                print(f"[*] Found overlapping Segment {i}:")
                print(f"    Virtual Address: 0x{p_vaddr:x} - 0x{seg_end:x}")
                print(f"    Old Flags: 0x{p_flags:x}")

                # New flags: PF_R (4) | PF_W (2) | PF_X (1) = 7 (RWE)
                new_flags = 4 | 2 | 1

                f.seek(phdr_offset + flags_offset)
                f.write(struct.pack("<I", new_flags))
                print(f"    -> Patched new flags to 0x{new_flags:x} (RWE)")
                patched_count += 1

        if patched_count > 0:
            print(f"\nSuccessfully unpacked and patched {patched_count} segment(s) into {output_path}")
        else:
            print("\nWarning: No segments overlapped the specified memory range.")

if __name__ == "__main__":
    if len(sys.argv) < 3:
        print("Usage: python patch_elf.py <input_binary> <output_binary>")
        sys.exit(1)

    input_file = sys.argv[1]
    output_file = sys.argv[2]

    # Target region specified
    TARGET_START = 0x08048000
    TARGET_END = 0x08287000

    patch_elf_permissions(input_file, output_file, TARGET_START, TARGET_END)
