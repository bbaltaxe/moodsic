![Alt](/design_folder/design.png "concept of look")

# moodsic

This repo contains code and instructions for running our CM202 final project. 

### concept 

Essentially what we've done is made a latent space controller using Mageneta's Music VAE. A user can interact with our designed hardware by placing it on any object, fidgetting with the object in a variety of ways, and they will be moved through different musical states. 

![Alt](/design_folder/interaction_design.png "design concept")

### implementation 

We use adafruit's IO API to interface with out hardware and output music based on generated interpolations. New interpolations and music samples can be generated, or you can use the one's we have provided. Instructions for setup are provided below. 

## hardware set up 

- some things james will add here 
- specifically on what needs to be soldered, and how to set up a feed in adafruit io 

## software set up 

Let's dive in! 

 - First, download this repo! 

 - You'll want to unzip generated.zip
 
 - To download all the requirements, first cd to the directory you have just downloaded. You can then use the following command to get the required packages: 
 
 ```
 pip install -r requirements.txt
 ```
 
 - Next, you will need to input your Adafruit_IO ID and Key into line 6 of 'play.py'
 
 - Also, add the path of your unzipped generated/ file to line 8
 
 - To use the music snippets we have already generated you can just run 
 
 ```
 python play.py 
 ```
 
 ## generating your own midi samples and interpolations
 
 ### generate a sample from a pretrained model 
 - [Download](https://storage.googleapis.com/magentadata/models/music_vae/checkpoints/cat-mel_2bar_big.tar) this pretrained model. (you can also train your own if you would like! Instructions can be found [here]( https://github.com/tensorflow/magenta/tree/master/magenta/models/music_vae))
 
 - untar the file using 
 ```
 tar -C /checkpoints -zxvf cat-mel_2bar_big.tar
 ```
 
 - generate samples by using: 
 ```
 music_vae_generate \
--config=cat-mel_2bar_big \
--checkpoint_file=/path/to/music_vae/checkpoints/cat-mel_2bar_big.tar \
--mode=sample \
--num_outputs=5 \
--output_dir=/tmp/music_vae/generated
```
This will generate 5 samples, but that can be changed! Please change the paths to files as necessary

### generate interpolations from a pretrained model 

- generate interpolations by using:
```
music_vae_generate \
--config=cat-mel_2bar_big \
--checkpoint_file=/path/to/music_vae/checkpoints/cat-mel_2bar.ckpt \
--mode=interpolate \
--num_outputs=100 \
--input_midi_1=/path/to/input/1.mid \
--input_midi_2=/path/to/input/2.mid \
--output_dir=/tmp/music_vae/generated
```
This will generate 100 samoles to interpolate over. This is what the hardware is configured to work with, so don't go any less than 100 without changing that! Again, please change the paths as needed

- you can now use your newly generated midi for this project! 

## closing 
That's it! Please feel free to reach out with any questions or comments. 
