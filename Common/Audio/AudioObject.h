#ifndef AUDIOOBJECT_H_INCLUDED
#define AUDIOOBJECT_H_INCLUDED

namespace Game {
class AudioObject {
public:
    virtual ~AudioObject() {
    }
    virtual void play() = 0;
};
}
#endif // AUDIOOBJECT_H_INCLUDED
