import rduino
import util

for bool in util.convert_image_to_bool("face.png"):
    match bool:
        case True:
            rduino.procOn()
        case False:
            rduino.procOff()
        case _:
            print("?")