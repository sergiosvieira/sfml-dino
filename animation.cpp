#include "animation.h"

Animation::Animation (const std::string& filename,
           const Frame& frame,
           const Time& updateTime): frame(frame),
                             updateTime(updateTime) {
    this->tex.loadFromFile(filename);
    this->sprite.setTexture(tex);
}

Sprite& Animation::getSprite() {
    return this->sprite;
}

Frame& Animation::getFrame() {
    return this->frame;
}

void Animation::update() {
    this->elapsed += this->clock.restart();
    if (this->elapsed >= this->updateTime) {
        this->frame.update();
        this->sprite.setTextureRect(this->frame.getRect());
        this->elapsed -= this->updateTime;
    }
}
