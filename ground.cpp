#include "ground.h"

Ground::Ground() {
    texture.loadFromFile("ground.png");
    sprite.setTexture(texture);
    sprite.setTextureRect({0, 0, 1200, 12});
    sprite.setPosition(0, kHeight - 50);
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
