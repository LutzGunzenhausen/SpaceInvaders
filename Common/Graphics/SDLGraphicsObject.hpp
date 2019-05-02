#ifndef SDLGRAPHICSOBJECT_HPP_INCLUDED
#define SDLGRAPHICSOBJECT_HPP_INCLUDED

#include <SDL.h>
#include "Common/Graphics/GraphicsObject.h"

namespace Game {

class SDLGraphicsObject : public GraphicsObject {
private:
    SDL_Renderer *renderer = NULL;
    SDL_Texture *texture = NULL;
    SDL_Rect *sourceRect = NULL;
    SDL_Rect *displayRect = NULL;

public:
    SDLGraphicsObject(SDL_Texture *texture_, SDL_Renderer *renderer_)
     : GraphicsObject(0, 0), renderer(renderer_), texture(texture_) {
         SDL_QueryTexture(texture, NULL, NULL, &imageWidth, &height);
         width = imageWidth;
         displayRect = new SDL_Rect();
         displayRect->w = width;
         displayRect->h = height;
         sourceRect = new SDL_Rect();
         sourceRect->w = width;
         sourceRect->h = height;
         sourceRect->x = 0;
         sourceRect->y = 0;
    }

    ~SDLGraphicsObject() {
        SDL_DestroyTexture(texture);
        texture = NULL;
        delete sourceRect;
        delete displayRect;
        sourceRect = NULL;
        displayRect = NULL;
    }

    void updateTileWidth(int width_) {
        sourceRect->w = width_;
        displayRect->w = width_;
        width = width_;
    }

    void renderObject(int xCoord, int yCoord, int index) {
        displayRect->x = xCoord;
        displayRect->y = yCoord;
        sourceRect->x = index * width;
        SDL_RenderCopy(renderer, texture, sourceRect, displayRect);
    }
};

}

#endif // SDLGRAPHICSOBJECT_HPP_INCLUDED
