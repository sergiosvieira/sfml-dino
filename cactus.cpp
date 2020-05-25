#include "cactus.h"

#include "game-consts.h"

Cactus::Cactus(const std::string& filename,
               const IntRect& rect) {
    this->texture.loadFromFile(filename);
    this->sprite.setTexture(this->texture);
    this->sprite.setTextureRect(rect);
    pos = {kWidth - 25, static_cast<float>(kHeight - rect.height*2)};
    sprite.setPosition(pos);
    speed = 200.f;
}

void Cactus::update(float dt) {
    pos.x -= speed * dt;
    if (pos.x + 25.f < 0.f) pos.x = kWidth;
    sprite.setPosition(pos);
}

void Cactus::render(RenderWindow &rw) {
    rw.draw(this->sprite);
}
