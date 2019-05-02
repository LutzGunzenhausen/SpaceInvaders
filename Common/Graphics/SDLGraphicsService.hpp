#ifndef SDLGRAPHICSSERVICE_HPP_INCLUDED
#define SDLGRAPHICSSERVICE_HPP_INCLUDED

#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <string>
#include "Common/StaticServiceLocator.h"
#include "Common/Constants.h"
#include "Common/Graphics/SDLGraphicsObject.hpp"
#include "Game/ObjectState/EventTriggeringState.h"
#include "Common/Audio/SDLAudioObject.h"

#define LOG_SDL_ERROR(x) LOG_MESSAGE(x); LOG_MESSAGE(SDL_GetError())

namespace Game {

class SDLGraphicsService : public GraphicsService {
private:
    bool gameRunning;;
    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;
    TTF_Font *gFont = NULL;
    SDL_Event *event = NULL;

public:
    SDLGraphicsService() {
        if (SDL_Init(SDL_INIT_VIDEO) == -1) {
            LOG_SDL_ERROR("Initialization failed:");
            return;
        }
        window = SDL_CreateWindow("Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                   WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
        if (window == NULL) {
            LOG_SDL_ERROR("Initialization of Window failed: ");
        }
        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
        if (renderer == NULL) {
            LOG_SDL_ERROR("Initialization of Renderer failed: ");
        }

        if (IMG_Init(IMG_INIT_PNG) != IMG_INIT_PNG) {
            LOG_SDL_ERROR("Initialization of Image failed:");
        }

        if( TTF_Init() == -1 ) {
            LOG_SDL_ERROR("Initialization TTF failed: ");
            return;
        }
        LOG_MESSAGE("Initialize Audio");
        if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 ){
            LOG_SDL_ERROR("Initializing Audio failed!");
            return;
        }
        LOG_MESSAGE("Initialized Audio");

        gFont = TTF_OpenFont( "font/font.ttf", 28 );
        if( gFont == NULL ) {
            LOG_SDL_ERROR("Failed to load lazy font! SDL_ttf Error:");
            return;
        }
        event = new SDL_Event();
        gameRunning = true;
        LOG_MESSAGE("Graphics Service Initialized");
    }

    void updateInputMask(InputMask *inputMask) {
        //inputMask->reset();
        while (SDL_PollEvent(event) != 0) {
            if( event->type == SDL_QUIT ) {
                gameRunning = false;
            } else if (event->type == SDL_KEYDOWN) {
                switch (event->key.keysym.sym) {
                case SDLK_UP:
                    inputMask->activateUp();
                    break;
                case SDLK_DOWN:
                    inputMask->activateDown();
                    break;
                case SDLK_LEFT:
                    inputMask->activateLeft();
                    break;
                case SDLK_RIGHT:
                    inputMask->activateRight();
                    break;
                case SDLK_RETURN:
                    inputMask->activateEnter();
                    break;
                case SDLK_SPACE:
                    inputMask->activateSpace();
                    break;
                case SDLK_ESCAPE:
                    inputMask->activateESC();
                    break;
                case SDLK_PAUSE:
                    inputMask->activatePause();
                    break;
                case SDLK_F2:
                    inputMask->activateF2();
                    break;
                }
            } else if (event->type == SDL_KEYUP) {
                switch (event->key.keysym.sym) {
                case SDLK_UP:
                    inputMask->deactivateUp();
                    break;
                case SDLK_DOWN:
                    inputMask->deactivateDown();
                    break;
                case SDLK_LEFT:
                    inputMask->deactivateLeft();
                    break;
                case SDLK_RIGHT:
                    inputMask->deactivateRight();
                    break;
                case SDLK_RETURN:
                    inputMask->deactivateEnter();
                    break;
                case SDLK_SPACE:
                    inputMask->deactivateSpace();
                    break;
                case SDLK_ESCAPE:
                    inputMask->deactivateESC();
                    break;
                case SDLK_PAUSE:
                    inputMask->deactivatePause();
                    break;
                case SDLK_F2:
                    inputMask->deactivateF2();
                    break;
                }
            }
        }
    }

    GraphicsObject *createTriggeringAnimatedObjectFromFile(
            const std::string &path, int tileWidth, int delay, Event *event) {
        GraphicsObject *graphicsObject = createSDLGraphicsObject(path);
        graphicsObject->updateTileWidth(tileWidth);
        return graphicsObject;
    }

    GraphicsObject *createAnimatedObjectFromFile(const std::string &path, int tileWidth) {
        GraphicsObject *graphicsObject = createSDLGraphicsObject(path);
        graphicsObject->updateTileWidth(tileWidth);

        return graphicsObject;
    }

    GraphicsObject *createObjectFromFile(const std::string &path) {
        return createSDLGraphicsObject(path);
    }

    SDLGraphicsObject *createSDLGraphicsObject(const std::string &path) {
        SDL_Surface *surface = IMG_Load(path.c_str());
        if (surface == NULL) {
            LOG_SDL_ERROR("Image not loaded!");
            return NULL;
        }
        SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
        if (texture == NULL) {
            LOG_SDL_ERROR("Error creating Texture:");
            return NULL;
        }
        SDL_FreeSurface(surface);
        return new SDLGraphicsObject(texture, renderer);
    }

    GraphicsObject *createTextObject(const std::string &message, uint8_t r, uint8_t g, uint8_t b) {
        SDL_Color textColor = { r, g, b };
        SDL_Surface *textSurface = TTF_RenderText_Solid( gFont, message.c_str(), textColor );
        if (textSurface == NULL) {
            LOG_MESSAGE("Textsurface not loaded!");
        }

        SDL_Texture *textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
        if (textTexture == NULL) {
            LOG_MESSAGE("Texttexture not loaded!");
        }
        SDL_FreeSurface(textSurface);
        return new SDLGraphicsObject(textTexture, renderer);
    }

    AudioObject *getAudioObject(const std::string &message) {
        LOG_MESSAGE("Try to load audio");
        Mix_Chunk *chunk = Mix_LoadWAV(message.c_str());
        if (chunk == NULL) {
            LOG_SDL_ERROR("AudioObject could not be loaded:");
        }
        LOG_MESSAGE("Try to load audio");
        return new SDLAudioObject(chunk);
    }

    void flipBuffer() {
        SDL_RenderPresent(renderer);
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
        SDL_RenderClear(renderer);
    }

    void delay(uint32_t delay) {
        SDL_Delay(delay);
    }

    void quitGame() {
        gameRunning = false;
    }

    bool isGameRunning() {
        return gameRunning;
    }
};

}

#endif // SDLGRAPHICSSERVICE_HPP_INCLUDED
