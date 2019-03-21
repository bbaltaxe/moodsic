import pygame 
import glob 
from Adafruit_IO import Client

#aio = Client('YOUR ADAFRUIT IO USERNAME', 'YOUR ADAFRUIT IO KEY')
aio = Client('jamescfey', 'faaaea08b041425ba38191ac40b3c691')

path_to_midi = '/Users/breanna/Documents/Classes/cm202_final/generated/*'

def play_step(mid):
    pygame.mixer.music.load(mid)
    pygame.mixer.music.play()
    while pygame.mixer.music.get_busy():
        # check if playback has finished
        clock.tick(50)
        

def midi_init():
    freq = 44100    # audio CD quality
    bitsize = -16   # unsigned 16 bit
    channels = 2    # 1 is mono, 2 is stereo
    buffer = 1024    # number of samples
    pygame.mixer.init(freq, bitsize, channels, buffer)

def get_val(): 
    val = aio.receive('motion')
    split = val.value.split('.')
    return split[0] 

if __name__ == '__main__': 
    midi_init()
    clock = pygame.time.Clock()    
            
    #get and sort list of files        
    midlist = glob.glob(path_to_midi) 
    midlist = sorted(midlist) 
    

    #iterate through them according to hardware
    while True: 
        try:  
            print(midlist[int(get_val())])
            play_step(midlist[int(get_val())])
        
        #end when asked :) 
        except KeyboardInterrupt:
            pygame.quit()
            break


