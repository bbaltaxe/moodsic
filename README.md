# moodsic

This repo contains code and instructions for running our CM202 final project. 

### concept 

Essentially what we've done is made a latent space controller using Mageneta's Music VAE. A user can interact with our designed hardware by placing it on any object, fidgetting with the object in a variety of ways, and they will be moved through different musical states. 

### implementation 

We use adafruit's IO API to interface with out hardware and output music based on generated interpolations. New interpolations and music samples can be generated, or you can use the one's we have provided. Instructions for setup are provided below. 

## set up 

Let's dive in! 

 - First, download this repo! 

 - You'll want to unzip generated.zip
 
 - To download all the requirements, first cd to the directory you have just downloaded. you can use the following command to get the required packages: 
 '''
 pip install -r requirements.txt
 '''
 
 
