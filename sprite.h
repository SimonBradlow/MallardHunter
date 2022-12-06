// sprite.h
// Created by Simon Bradlow on 12/5/22.
#ifndef DUCKHUNT_SPRITE_H
#define DUCKHUNT_SPRITE_H

#include "rect.h"
#include <vector>

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
        scale = s;
    }
    void setVec(std::vector<std::vector<color>> &v) {
        vec = v;
        setWidth(v[0].size()*scale);
        setHeight(v.size()*scale);
    }
    void draw() const {
        for (int i=0; i<(getWidth()/scale); ++i) {
            for (int j=0; j<(getHeight()/scale); ++j) {
                Rect temp;
                temp.setSize(scale, scale);
                temp.setColor(vec[j][i]);
                temp.setCenter(getLeftX()+(i*scale)+(scale/2), getTopY()+(j*scale)+(scale/2));
                if (temp.getOpacity() != 0) {
                    temp.draw();
                }
            }
        }
    }
};

#endif //DUCKHUNT_SPRITE_H