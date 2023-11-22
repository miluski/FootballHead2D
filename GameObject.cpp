#include "Engine.hpp"

using namespace Game;


/**
 * @brief Ustawia wspó³rzêdn¹ X obiektu GameObject.
 *
 * @param x Nowa wartoœæ wspó³rzêdnej X.
 */
void Engine::GameObject::setX(float x) {
    actualPosition.x = x;
}

/**
 * @brief Ustawia wspó³rzêdn¹ Y obiektu GameObject.
 *
 * @param y Nowa wartoœæ wspó³rzêdnej Y.
 */
void Engine::GameObject::setY(float y) {
    actualPosition.y = y;
}

/**
 * @brief Pobiera wspó³rzêdn¹ X obiektu GameObject.
 *
 * @return Aktualna wartoœæ wspó³rzêdnej X.
 */
float Engine::GameObject::getX() {
    return this->actualPosition.x;
}

/**
 * @brief Pobiera wspó³rzêdn¹ Y obiektu GameObject.
 *
 * @return Aktualna wartoœæ wspó³rzêdnej Y.
 */
float Engine::GameObject::getY() {
    return this->actualPosition.y;
}