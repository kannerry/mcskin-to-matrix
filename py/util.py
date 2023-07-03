from PIL import Image

def convert_image_to_bool(image_path):
    image = Image.open(image_path).convert("1")  # Convert to black and white
    width, height = image.size
    bool_values = []

    for y in range(height):
        for x in range(width):
            pixel = image.getpixel((x, y))
            bool_value = True if pixel == 0 else False
            bool_values.append(bool_value)

    return bool_values
