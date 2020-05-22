#include "frame.h"

Frame::Frame(int start,
             int end,
             int current,
             const IntRect& rect): start(start),
                                   end(end),
                                   current(current),
                                   rect(rect){

}

int Frame::getStart() const {
    return this->start;
}

int Frame::getEnd() const {
    return this->end;
}

int Frame::getCurrent() const {
    return this->current;
}

IntRect Frame::getRect() const {
    return this->rect;
}

void Frame::setCurrentFrame(int current) {
    this->current = current;
}

void Frame::update() {
    if (this->current + 1 > this->end) this->current = this->start;
    this->rect = {this->current * this->rect.width,
                  this->rect.top,
                  this->rect.width,
                  this->rect.height};
}
