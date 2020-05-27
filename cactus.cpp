#include "cactus.h"

#include "game-consts.h"
#include "game-random.h"

Cactus::Cactus(const std::string& filename,
               const IntRect& rect,
               float py) {
    this->texture.loadFromFile(filename);
    this->sprite.setTexture(this->texture);
    this->rect = rect;
    randomize();
    pos = {kWidth - 25, py};
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

void Cactus::randomize() {
    int count = ceil(nor(mt) * 3);
    if (count == 0) count = 1;
    int index = ceil(nor(mt) * count);
    IntRect newRect = this->rect;
    newRect.left = index * rect.width;
    newRect.width = count * rect.width;
    this->sprite.setTextureRect(newRect);
}
