// sprite.h
// Created by Simon Bradlow
#ifndef DUCKHUNT_SPRITE_H
#define DUCKHUNT_SPRITE_H

#include "rect.h"
#include <fstream>
#include <vector>

#ifdef _WIN32
// If your Windows machine runs Python in CLI with "python" instead of "py", update this line.
const std::string python = "py";
#else
// If your Mac/Linux machine runs Python in CLI with "python3" instead of "python", update this line.
const std::string python = "python3";
#endif

class Sprite : public Rect {
private:
    double scale;
public:
    std::vector<std::vector<color>> vec;
    Sprite() {
        scale = 1;
    }
    Sprite(double s) {
        if (s > 0) scale = s;
        else scale = 1;
    }
    void setScale(double s){
        if (s > 0) scale = s;
    }
    void setVec(std::vector<std::vector<color>> &v) {
        vec = v;
        setWidth(v[0].size()*scale);
        setHeight(v.size()*scale);
    }
    void setVec(Sprite &o) {
        std::vector<std::vector<color>> v = o.vec;
        vec = v;
        setWidth(v[0].size()*scale);
        setHeight(v.size()*scale);
    }
    void draw() const {
        this->draw();
        for (int i=0; i<(getWidth()/scale); ++i) {
            for (int j=0; j<(getHeight()/scale); ++j) {
                Rect tmp;
                tmp.setSize(scale, scale);
                tmp.setColor(vec[j][i]);
                tmp.setCenter(((getLeftX() + (scale/2)) + (i*scale)),
                               ((getTopY() + (scale/2)) + (j*scale)));
                if (tmp.getRed() != 149.0/255.0) {
                //if (tmp.getOpacity() != 0) {
                    tmp.draw();
                }
            }
        }
    }
};

Sprite initSprite(std::string filename) {
    Sprite tmp;

    std::string command;
    command = python + " ../spriteConverter.py " + filename;
    system(command.c_str());

    std::ifstream inFile("spriteData.txt");
    int w, h, r, g, b, a;
    inFile >> w;
    inFile >> h;
    for (int i=0; i<w; ++i) {
        std::vector<color> tempVec = {};
        for (int j=0; j<h; ++j) {
            inFile >> r;
            inFile >> g;
            inFile >> b;
            tempVec.push_back(color(r/255.0, g/255.0, b/255.0));
        }
        tmp.vec.push_back(tempVec);
    }
    inFile.close();
    return tmp;
}

#endif //DUCKHUNT_SPRITE_H