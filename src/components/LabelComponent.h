#ifndef LABEL_COMPONENT_H
#define LABEL_COMPONENT_H

#include <SDL2/SDL_ttf.h>

#include <utility>
#include "../FontManager.h"
#include "../EntityManager.h"
#include "../AssetManager.h"
#include "../Game.h"

class TextLabelComponent : public Component {
    public:
        SDL_Rect position;
        std::string text;
        std::string fontFamily;
        SDL_Color color;
        SDL_Texture* texture;

    public:
        TextLabelComponent(int _x, int _y, std::string _text, std::string _fontFamily, SDL_Color _color)
            : text(std::move(_text)), fontFamily(std::move(_fontFamily)), color(_color) {
            position.x = _x;
            position.y = _y;
            setLabelText(text, fontFamily);
        }

        ~TextLabelComponent() override { SDL_DestroyTexture(texture); }

        void setLabelText(const std::string& _text, const std::string& _fontFamily) {
            SDL_Surface* surface = TTF_RenderText_Blended(Game::assetManager->getFont(fontFamily), text.c_str(), color);
            texture = SDL_CreateTextureFromSurface(Game::renderer, surface);
            SDL_FreeSurface(surface);
            SDL_QueryTexture(texture, nullptr, nullptr, &position.w, &position.h);
        }

        void render() override {
            FontManager::draw(texture, position);
        }
};

#endif