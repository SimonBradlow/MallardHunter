# Mallard Hunter 
### by Simon Bradlow


- Summary of the program:
  - This program is a faux-recreation of the classic NES game Duck Hunt! Taking some inspiration from flappy bird, this game is an infinite loop, with no win condition, but only a game over condition. 
  - The sprite.h class uses the python script spriteConverter.py to turn .png files into vectors of rect objects to create a sprite grid. This allows us to draw very complex images, as opposed to the usual shapes used in the classes for previous projects.


- Operating system(s) you have run the project on:
  - macOS Catalina 10.15.7
  

- Any added installations necessary to run the program:
  - GLFW: https://www.glfw.org/download
    - Windows: see https://stackoverflow.com/questions/12886609/setting-up-glfw-with-mingw for installation guidance
    - macOS: `brew install GLFW` in the command line
  - CV2: `pip3 install opencv-python` in the command line


- Any citations:
  - sprite png files were sourced from the following site and subsequentely edited: 
    - https://www.spriters-resource.com/nes/duckhunt/
