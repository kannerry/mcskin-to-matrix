import mcgrab
import rduino
import util

skinput = input("Input a Minecraft Player's Username: ")
mcgrab.grab_face(skinput)

for bool in util.convert_image_to_bool("face.png"):
    match bool:
        case True:
            rduino.procOn()
        case False:
            rduino.procOff()
        case _:
            print("?")