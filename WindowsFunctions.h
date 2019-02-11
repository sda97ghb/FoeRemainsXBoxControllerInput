#ifndef WINDOWSFUNCTIONS_H
#define WINDOWSFUNCTIONS_H

#ifdef WIN32

#include <windows.h>

#include "windowsconstants.h"

struct Point2D
{
    int x;
    int y;
};

namespace WINFUNCTIONS
{
    static constexpr int SCREEN_WIDTH = 1600;
    static constexpr int SCREEN_HEIGHT = 900;

    static INPUT buffer[1];

    void mouseSetup();

    Point2D getCursorPos();
    void setCursorPos(int x, int y);
    void moveCursor(int dx, int dy);

    void mouseDownLeft();
    void mouseUpLeft();

    void mouseDownRight();
    void mouseUpRight();

    void mouseScrollUp();
    void mouseScrollDown();

    void downKey(int key);
    void upKey(int key);
}

#endif // WIN32

#endif // WINDOWSFUNCTIONS_H
