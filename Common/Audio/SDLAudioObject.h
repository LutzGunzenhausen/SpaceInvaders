#ifndef SDLAUDIOOBJECT_H_INCLUDED
#define SDLAUDIOOBJECT_H_INCLUDED

#include <SDL_mixer.h>
#include "Common/Audio/AudioObject.h"
namespace Game {
class SDLAudioObject : public AudioObject {
private:
    Mix_Chunk *chunk = NULL;
public:
    SDLAudioObject(Mix_Chunk *chunk_) : chunk(chunk_) {
    }

    ~SDLAudioObject() {
        Mix_FreeChunk(chunk);
        chunk = NULL;
    }

    void play() {
        //Mix_PlayChannel(-1, chunk, 0);
    }
};

}

#endif // SDLAUDIOOBJECT_H_INCLUDED
