from PIL import Image

# Converts a 16x8 png to hex for LED display
def image_to_hex(image_path):
    img = Image.open(image_path).convert('1')
    
    if img.size != (16, 8):
        raise ValueError("Image is not 16x8 pixels")

    hex_values = []
    
    for x in range(16):
        byte = 0
        for y in range(8):
            pixel = img.getpixel((x, y))
            if pixel == 255:
                byte |= 1 << (7 - y)
        hex_values.append(f"0x{byte:02X}")

    return ",".join(hex_values)

image_path = "right.png"
result = image_to_hex(image_path)
print(result)