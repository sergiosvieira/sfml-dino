#ifndef FRAME_H
#define FRAME_H

#include <SFML/Graphics.hpp>

using sf::IntRect;

/**
 * @brief The Frame class
 */
class Frame {
    int start = 0;
    int end = 0;
    int current = 0;
    IntRect rect = {};
public:
    /**
     * @brief Frame
     * @param start
     * @param end
     * @param current
     * @param rect
     */
    Frame(int start,
          int end,
          int current,
          const IntRect& rect);
    /**
     * @brief getStart
     * @return
     */
    int getStart() const;
    /**
     * @brief getEnd
     * @return
     */
    int getEnd() const;
    /**
     * @brief getCurrent
     * @return
     */
    int getCurrent() const;
    /**
     * @brief getRect
     * @return
     */
    IntRect getRect();
    /**
     * @brief setCurrentFrame
     * @param current
     */
    void setCurrentFrame(int current);
    /**
     * @brief update
     */
    void update();
    /**
     * @brief updateRect
     */
    void updateRect();
};

#endif // FRAME_H
