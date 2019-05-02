#ifndef INPUTMASK_HPP_INCLUDED
#define INPUTMASK_HPP_INCLUDED

namespace Game {
class InputMask {
private:
    static const int DOWN_MASK = 1;
    static const int UP_MASK = 1 << 1;
    static const int LEFT_MASK = 1 << 2;
    static const int RIGHT_MASK = 1 << 3;
    static const int ENTER_MASK = 1 << 4;
    static const int SPACE_MASK = 1 << 5;
    static const int ESC_MASK = 1 << 6;
    static const int PAUSE_MASK = 1 << 7;
    static const int F2_MASK = 1 << 8;

    int mask = 0;
    void inline activateValue(const int activeMask) {
        mask |= activeMask;
    }

    void inline deactivateValue(const int inactiveMask) {
        mask -= inactiveMask;
    }

    bool inline isActive(const int checkedMask) {
        return (mask & checkedMask) != 0;
    }
public:
    void reset() {
        mask = 0;
    }

    void activateDown() {
        activateValue(DOWN_MASK);
    }

    void deactivateDown() {
        deactivateValue(DOWN_MASK);
    }

    bool isDownActive() {
        return isActive(DOWN_MASK);
    }

    void activateUp() {
        activateValue(UP_MASK);
    }

    void deactivateUp() {
        deactivateValue(UP_MASK);
    }

    bool isUpActive() {
        return isActive(UP_MASK);
    }

    void activateLeft() {
        activateValue(LEFT_MASK);
    }

    void deactivateLeft() {
        deactivateValue(LEFT_MASK);
    }

    bool isLeftActive() {
        return isActive(LEFT_MASK);
    }

    void activateRight() {
        activateValue(RIGHT_MASK);
    }

    void deactivateRight() {
        deactivateValue(RIGHT_MASK);
    }

    bool isRightActive() {
        return isActive(RIGHT_MASK);
    }

    void activateEnter() {
        activateValue(ENTER_MASK);
    }

    void deactivateEnter() {
        deactivateValue(ENTER_MASK);
    }

    bool isEnterActive() {
        return isActive(ENTER_MASK);
    }

    void activateSpace() {
        activateValue(SPACE_MASK);
    }

    void deactivateSpace() {
        deactivateValue(SPACE_MASK);
    }

    bool isSpaceActive() {
        return isActive(SPACE_MASK);
    }

    void activateESC() {
        activateValue(ESC_MASK);
    }

    void deactivateESC() {
        deactivateValue(ESC_MASK);
    }

    bool isESCActive() {
        return isActive(ESC_MASK);
    }

    void activatePause() {
        activateValue(PAUSE_MASK);
    }

    void deactivatePause() {
        deactivateValue(PAUSE_MASK);
    }

    bool isPauseActive() {
        return isActive(PAUSE_MASK);
    }

    void activateF2() {
        activateValue(F2_MASK);
    }

    void deactivateF2() {
        deactivateValue(F2_MASK);
    }

    bool isF2Active() {
        return isActive(F2_MASK);
    }
};
}

#endif // INPUTMASK_HPP_INCLUDED
