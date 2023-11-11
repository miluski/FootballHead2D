#include "Engine.hpp"

using namespace Game;

void Engine::GameObject::setX(float x) {
    actualPosition.x = x;
}

void Engine::GameObject::setY(float y) {
    actualPosition.y = y;
}

float Engine::GameObject::getX() {
    return this->actualPosition.x;
}

float Engine::GameObject::getY() {
    return this->actualPosition.y;
}