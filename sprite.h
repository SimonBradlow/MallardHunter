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
    Sprite();
    Sprite(double s);
    void setScale(double s);
    void setVec(std::vector<std::vector<color>> &v);
    void draw() const override;
};

#endif //DUCKHUNT_SPRITE_H