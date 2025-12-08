import struct
import zlib
import os

BINARY_PATH = "app.bin"
PATCHED_PATH = "app_patched.bin"
MAGIC = 0xDEADBEEF

def patch_binary():
    
    try:
        with open(BINARY_PATH, "rb") as f:
            data = bytearray(f.read())
    except FileNotFoundError:
        print(f"Error: Could not find {BINARY_PATH}")
        return

    
    magic_bytes = struct.pack("<I", MAGIC)
    header_offset = data.find(magic_bytes)

    if header_offset == -1:
        print("Error: Magic Number 0xDEADBEEF not found in binary!")
        return

    print(f"Found Header at offset: {header_offset}")


    header_size = 16
    body_start = header_offset + header_size
    body_data = data[body_start:]
    
    
    calculated_crc = zlib.crc32(body_data) & 0xFFFFFFFF
    body_length = len(body_data)

    print(f"Calculated CRC: 0x{calculated_crc:08X}")
    print(f"Body Length:    {body_length} bytes")

    
    original_version = struct.unpack_from("<I", data, header_offset + 12)[0]

    
    new_header = struct.pack("<IIII", 
                             MAGIC, 
                             body_length, 
                             calculated_crc, 
                             original_version)

    
    data[header_offset : header_offset + 16] = new_header

    
    with open(PATCHED_PATH, "wb") as f:
        f.write(data)
    
    print(f"Success! Created {PATCHED_PATH} ready for flashing.")

if __name__ == "__main__":
    patch_binary()