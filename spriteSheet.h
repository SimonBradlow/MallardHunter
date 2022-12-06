// spriteSheet.h
// Created by Simon Bradlow on 12/6/22.
#ifndef DUCKHUNT_SPRITESHEET_H
#define DUCKHUNT_SPRITESHEET_H

#include "sprite.h"
#include <vector>

// Colors
const color clear (0, 0, 0, 0);
const color white(1, 1, 1);
const color black(0, 0, 0);
const color magenta(1, 0, 1);
const color cyan (0, 1, 1);
const color skyBlue(77/255.0, 213/255.0, 240/255.0);
const color grassGreen(26/255.0, 176/255.0, 56/255.0);
const color darkGreen(0/255.0, 70/255.0, 0/255.0);
const color brickRed(201/255.0, 20/255.0, 20/255.0);
const color darkBlue(1/255.0, 110/255.0, 214/255.0);
const color purple(119/255.0, 11/255.0, 224/255.0);
const color orange(1, 163/255.0, 22/255.0);



// Sprites
std::vector<std::vector<color>> duck1 = {
        {clear, black, clear, clear, darkGreen, darkGreen, darkGreen, clear},
        {clear, black, black, clear, darkGreen, white, orange, orange},
        {clear, black, black, black, darkGreen, darkGreen, darkGreen, clear,},
        {clear, clear, black, black, black, black, black, black,},
        {clear, clear, black, black, black, black, black, clear,},
        {clear, orange, black, orange, black, clear, clear, clear,},
        {clear, orange, clear, orange, clear, clear, clear, clear,},
        {clear, clear, clear, clear, clear, clear, clear, clear,},
};
std::vector<std::vector<color>> duck2 = {
        {clear, clear, clear, clear, darkGreen, darkGreen, darkGreen, clear},
        {clear, clear, clear, clear, darkGreen, white, orange, orange},
        {black, black, black, black, darkGreen, darkGreen, darkGreen, clear,},
        {clear, black, black, black, black, black, black, clear,},
        {clear, clear, black, black, black, black, black, black,},
        {clear, orange, black, orange, black, black, clear, clear,},
        {clear, orange, clear, orange, clear, clear, clear, clear,},
        {clear, clear, clear, clear, clear, clear, clear, clear,},
};
std::vector<std::vector<color>> duck3 = {
        {clear, clear, clear, clear, darkGreen, darkGreen, darkGreen, clear},
        {clear, clear, clear, clear, darkGreen, white, orange, orange},
        {clear, black, black, black, darkGreen, darkGreen, darkGreen, clear,},
        {black, black, black, black, black, black, clear, clear,},
        {clear, clear, black, black, black, black, black, clear,},
        {clear, orange, black, orange, black, black, black, clear,},
        {clear, orange, clear, orange, clear, black, black, clear,},
        {clear, clear, clear, clear, clear, clear, black, clear,},
};
std::vector<std::vector<color>> duck4 = {
        {black, clear, clear, darkGreen, darkGreen, darkGreen, clear, clear,},
        {black, black, clear, darkGreen, white, orange, orange, black,},
        {black, black, black, darkGreen, darkGreen, darkGreen, black, black,},
        {clear, black, black, black, black, black, black, black,},
        {clear, clear, black, black, brickRed, black, black, clear,},
        {clear, clear, black, black, black, black, clear, clear,},
        {black, clear, orange, black, orange, clear, clear, clear,},
        {clear, clear, orange, clear, orange, clear, black, clear,},
};
std::vector<std::vector<color>> duck5 = {
        {clear, black, clear, orange, clear, orange, clear, black},
        {clear, black, black, orange, clear, orange, black, black},
        {clear, black, black, black, black, black, black, black,},
        {clear, clear, black, black, black, black, black, clear,},
        {clear, clear, clear, black, black, black, clear, clear,},
        {clear, clear, clear, darkGreen, darkGreen, darkGreen, clear, clear,},
        {clear, clear, clear, darkGreen, white, orange, orange, clear,},
        {clear, clear, clear, darkGreen, darkGreen, darkGreen, clear, clear,},
};

#endif //DUCKHUNT_SPRITESHEET_H