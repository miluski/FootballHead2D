#include "Engine.hpp"

void GameObject::setX(float x) {
    actualPosition.x = x;
}

void GameObject::setY(float y) {
    actualPosition.y = y;
}

float GameObject::getX() {
    return this->actualPosition.x;
}

float GameObject::getY() {
    return this->actualPosition.y;
}