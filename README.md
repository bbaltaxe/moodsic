# moodsic

This repo contains code and instructions for running our CM202 final project. 

### concept 

Essentially what we've done is made a latent space controller using Mageneta's Music VAE. A user can interact with our designed hardware by placing it on any object, fidgetting with the object in a variety of ways, and they will be moved through different musical states. 

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
 
 ## Generating your own midi samples and interpolations
 
 # Generate a sample from a pretrained model 
 - [Download](https://storage.googleapis.com/magentadata/models/music_vae/checkpoints/cat-mel_2bar_big.tar) this pretrained model. (you can also train your own if you would like! Instructions can be found [here]( https://github.com/tensorflow/magenta/tree/master/magenta/models/music_vae))
 
 
