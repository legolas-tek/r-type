/*
** EPITECH PROJECT, 2023
** B-OOP-400-PAR-4-1-arcade-marouan.bader
** File description:
** SpriteFactory
*/

#ifndef SPRITEFACTORY_HPP_
#define SPRITEFACTORY_HPP_

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

class Sprite {
    public:
        Sprite() = default;
        Sprite(Sprite const & sprite) : _Rect(sprite._Rect), _Texture(sprite._Texture), _sprite(sprite._sprite) {}
        Sprite(std::string const &path, sf::Rect<int> rect) {
            _Rect = rect;
            _Texture.loadFromFile(path);
            _Texture.setSmooth(true);
            _sprite.setTexture(_Texture);
            _sprite.setTextureRect(_Rect);
            _Texture.setRepeated(true);
            _sprite.setOrigin(16, 16);
        }
        sf::Sprite &getSprite() {
            return _sprite;
        }
        int getLeft() const {
            return _Rect.left;
        }
        void changeRect(int left) {
            _Rect.left = left;
            _sprite.setTextureRect(_Rect);
        }
        ~Sprite() = default;
    private:
        sf::Rect<int> _Rect;
        sf::Texture _Texture;
        sf::Sprite _sprite;
};

#endif /* !SPRITEFACTORY_HPP_ */
