#include "Engine.hpp"

using namespace Game;


/**
 * @brief Ustawia wsp�rz�dn� X obiektu GameObject.
 *
 * @param x Nowa warto�� wsp�rz�dnej X.
 */
void Engine::GameObject::setX(float x) {
    actualPosition.x = x;
}

/**
 * @brief Ustawia wsp�rz�dn� Y obiektu GameObject.
 *
 * @param y Nowa warto�� wsp�rz�dnej Y.
 */
void Engine::GameObject::setY(float y) {
    actualPosition.y = y;
}

/**
 * @brief Pobiera wsp�rz�dn� X obiektu GameObject.
 *
 * @return Aktualna warto�� wsp�rz�dnej X.
 */
float Engine::GameObject::getX() {
    return this->actualPosition.x;
}

/**
 * @brief Pobiera wsp�rz�dn� Y obiektu GameObject.
 *
 * @return Aktualna warto�� wsp�rz�dnej Y.
 */
float Engine::GameObject::getY() {
    return this->actualPosition.y;
}