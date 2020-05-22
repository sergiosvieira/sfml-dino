#include "cloud.h"

#include "game-consts.h"
#include "game-random.h"

Cloud::Cloud() {
    this->pos = {kWidth, kHeight - 215.f};
    this->speed = 200.f;
    this->texture.loadFromFile("cloud.png");
    this->sprite.setTexture(this->texture);
    this->sprite.setTextureRect({0, 0, 46, 13});
}

void Cloud::update(float dt) {
    pos.x -= speed * dt;
    if (pos.x + 46.f < 0.f) {
        pos.x = kWidth;
        if (urd(mt) > 1.) {
            pos.y = kHeight - 215.f;
        } else {
            pos.y = kHeight - 210.f;
        }
    }
    sprite.setPosition(pos);
}
void Cloud::render(RenderWindow& rw) {
    rw.draw(sprite);
}
