import pygame

#receber os dados dos pedais x, y e botões do pé
#recebendo um vetor de [x, y, z]

class Data():

    def __init__(self, x:float, y:float, z:float) -> None:
        self.x = x
        self.y = y
        self.z = z

position = [0.2, 0.2, 0.0]
button = False

def play_audio(address):
    pygame.mixer.init()
    pygame.mixer.music.load(address)
    pygame.mixer.music.play()

    while pygame.mixer.music.get_busy():
        pygame.time.Clock().tick(10)

    pygame.mixer.quit()

if position[0] >= 0.1 and position[0] <= 0.3 and position[1] >= 0.1 and position[1] <= 0.3 and  position[2] == 0:
    address = "./audio/prato_de_ataque.wav"

    play_audio(address)

if button:
    address = "./audio/tom_high.wav"

    play_audio(address)