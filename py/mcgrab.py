import requests
import base64
import json 
import os
import urllib.request
from PIL import Image

def grab_face(player_username):
    response = requests.get(f"https://api.mojang.com/users/profiles/minecraft/{player_username}")
    if response.status_code == 200:
        player_data = response.json()
        player_uuid = player_data["id"]
    else:
        print("Failed to retrieve player data. Check the username or API availability.")
        exit()
        
    response = requests.get(f"https://sessionserver.mojang.com/session/minecraft/profile/{player_uuid}")
    if response.status_code == 200:
        profile_data = response.json()
        textures = profile_data["properties"][0]["value"]
    else:
        print("Failed to retrieve player profile data. Check the player UUID or API availability.")
        exit()

    decoded_textures = base64.b64decode(textures)
    json_data = json.loads(decoded_textures)
    skin_dir = json_data['textures']['SKIN']['url']

    urllib.request.urlretrieve(skin_dir, "player_skin.png")

    image = Image.open("player_skin.png")
    crop_bounds = (8, 8, 16, 16)
    cropped_image = image.crop(crop_bounds)
    black_and_white_image = cropped_image.convert("L").point(lambda x: 0 if x < 85 else 255, mode="1")
    black_and_white_image.save("face.png")
    os.remove("player_skin.png")

