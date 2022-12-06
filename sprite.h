// sprite.h
// Created by Simon Bradlow
#ifndef DUCKHUNT_SPRITE_H
#define DUCKHUNT_SPRITE_H

#include "rect.h"
#include <fstream>
#include <vector>
#include <memory>
#include <optional>
using std::optional;
using std::nullopt;
using std::make_optional;

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
    std::vector<std::vector<optional<color>>> vec;

    Sprite() {
        scale = 1;
    }

    explicit Sprite(double s) {
        if (s > 0) scale = s;
        else scale = 1;
    }

    void setScale(double s){
        if (s > 0) scale = s;
    }

    void setVec(std::vector<std::vector<optional<color>>> &v) {
        vec = v;
        setWidth(v[0].size()*scale);
        setHeight(v.size()*scale);
    }

    void setVec(Sprite &o) {
        std::vector<std::vector<optional<color>>> v = o.vec;
        vec = v;
        setWidth(v[0].size()*scale);
        setHeight(v.size()*scale);
    }

    void draw() const override {
        for (int i=0; i<(getWidth()/scale); ++i) {
            for (int j=0; j<(getHeight()/scale); ++j) {
                if (vec[j][i] != nullopt) {
                    Rect tmp;
                    tmp.setSize(scale, scale);
                    tmp.setColor(*vec[j][i]);
                    tmp.setCenter(((getLeftX() + (scale/2)) + (i*scale)),
                                  ((getTopY() + (scale/2)) + (j*scale)));
                    tmp.draw();
                }
            }
        }
    }
};

Sprite initSprite(const std::string& filename) {
    Sprite tmp;

    std::string command;
    command = python + " ../spriteConverter.py " + filename;
    system(command.c_str());

    std::ifstream inFile("spriteData.txt");
    int w, h, r, g, b, a;
    inFile >> w;
    inFile >> h;
    for (int i=0; i<w; ++i) {
        std::vector<optional<color>> tempVec = {};
        for (int j=0; j<h; ++j) {
            inFile >> r;
            inFile >> g;
            inFile >> b;
            // if (a == 0);
            if (r == 149) tempVec.push_back(nullopt);
            else tempVec.push_back(make_optional(color(r/255.0, g/255.0, b/255.0)));
        }
        tmp.vec.push_back(tempVec);
    }
    inFile.close();
    return tmp;
}

#endif //DUCKHUNT_SPRITE_H