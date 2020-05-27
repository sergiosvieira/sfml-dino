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
    IntRect rect;
public:
    /**
     * @brief Cactus
     * @param filename
     * @param rect
     * @param py
     */
    Cactus(const std::string& filename,
           const IntRect& rect,
           float py);
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
    /**
     * @brief randomize
     */
    void randomize();
};
#endif // CACTUS_H
