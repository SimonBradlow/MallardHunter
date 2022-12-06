// sprite.cpp
// Created by Simon Bradlow on 12/5/22.
#include "sprite.h"

Sprite::Sprite() {
    scale = 1;
}
Sprite::Sprite(double s) {
    if (s > 0) scale = s;
    else scale = 1;
}
void Sprite::setScale(double s){
    scale = s;
}
void Sprite::setVec(std::vector<std::vector<color>> &v) {
    vec = v;
}
void Sprite::draw() const {
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