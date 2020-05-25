#include "ground.h"

Ground::Ground() {
    texture.loadFromFile("ground.png");
    sprite.setTexture(texture);
    sprite.setTextureRect({0, 0, 1200, 12});
    pos = {0.f, kHeight - 50.f};
    sprite.setPosition(pos);
    speed = 200.f;
}

void Ground::update(float dt) {
    pos.x -= speed * dt;
    if (pos.x < -kWidth) {
        pos.x = 0.f;
    }
    sprite.setPosition(pos);
}

void Ground::render(RenderWindow& rw) {
    rw.draw(sprite);
}
