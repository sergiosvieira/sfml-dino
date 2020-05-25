#include "animation.h"

Animation::Animation (const std::string& filename,
           const Frame& frame,
           const Time& updateTime): frame(frame),
                             updateTime(updateTime) {
    this->tex.loadFromFile(filename);
    this->sprite.setTexture(tex);
}

void Animation::setFreeze(bool value) {
    this->freeze = value;
}

bool Animation::getFreeze() const {
    return this->freeze;
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
        if (!freeze) this->frame.update();
        this->frame.updateRect();
        this->sprite.setTextureRect(this->frame.getRect());
        this->elapsed -= this->updateTime;
    }
}
