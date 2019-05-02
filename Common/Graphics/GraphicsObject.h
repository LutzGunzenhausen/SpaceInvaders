#ifndef GRAPHICSOBJECT_H_INCLUDED
#define GRAPHICSOBJECT_H_INCLUDED

namespace Game {

class GraphicsObject {
public:
    int imageWidth;
    int width;
    int height;
    GraphicsObject(int width_, int height_) : width(width_), height(height_) {}
    virtual void renderObject(int xCoord, int yCoord, int index) = 0;
    virtual ~GraphicsObject() {
    }
    virtual void updateTileWidth(int width_) {
        width = width_;
    }

    int getTileCount() {
        return imageWidth / width;
    }
};

}

#endif // GRAPHICSOBJECT_H_INCLUDED
