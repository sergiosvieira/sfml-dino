#ifndef CACTUS_H
#define CACTUS_H

#include <SFML/Graphics.hpp>
#include "object.h"

using sf::Texture,
    sf::Sprite,
    sf::IntRect;

/**
 * @brief The Cactus class
 */
class Cactus: public Object {
    Texture texture;
    Sprite sprite;
public:
    /**
     * @brief Cactus
     * @param filename
     * @param rect
     */
    Cactus(const std::string& filename,
           const IntRect& rect);
    /**
     * @brief update
     * @param dt
     */
    void update(float dt) override;
    /**
     * @brief render
     * @param rw
     */
    void render(RenderWindow &rw) override;
};
#endif // CACTUS_H
