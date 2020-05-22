#ifndef PTERODACTYL_H
#define PTERODACTYL_H

#include "object.h"
#include "animation.h"

/**
 * @brief The Pterodactyl class
 */
class Pterodactyl : public Object
{
    Animation animation{"ptero.png", {0, 1, 0, {0, 0, 46, 35}}, sf::seconds(1.f/5.f)};
public:
    /**
     * @brief Pterodactyl
     */
    Pterodactyl();
    /**
     * @brief update
     * @param dt
     */
    void update(float dt) override;
    /**
     * @brief render
     * @param rw
     */
    void render(RenderWindow& rw) override;
};

#endif // PTERODACTYL_H
