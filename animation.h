#ifndef ANIMATION_H
#define ANIMATION_H

#include <SFML/Graphics.hpp>
#include "frame.h"

using sf::Clock,
    sf::Time,
    sf::Texture,
    sf::Sprite,
    sf::Vector2i,
    sf::IntRect;

/**
 * @brief The Animation class
 */
class Animation {
    Clock clock;
    Time elapsed;
    Time updateTime;
    Texture tex;
    Sprite sprite;
    Frame frame;
    bool freeze = false;
public:
    /**
     * @brief Animation - Cuida da animação dos sprites
     * @param filename
     * @param frame
     * @param updateTime
     */
    Animation (const std::string& filename,
               const Frame& frame,
               const Time& updateTime);
    /**
     * @brief getSprite - Retorna o sprite atual da animação
     * @return
     */
    Sprite& getSprite();
    /**
     * @brief getFrame - Retorna a classe de controle de frames
     * @return
     */
    Frame& getFrame();
    /**
     * @brief update - Atualiza a posição do próximo frame que será exibido na tela
     */
    void update();
    /**
     * @brief setFreeze
     * @param value
     */
    void setFreeze(bool value);
    /**
     * @brief getFreeze
     * @return
     */
    bool getFreeze() const;
};


#endif // ANIMATION_H
