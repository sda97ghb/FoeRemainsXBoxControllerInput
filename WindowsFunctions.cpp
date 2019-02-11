#include "WindowsFunctions.h"

#ifdef WIN32

void WINFUNCTIONS::mouseSetup()
{
    buffer->type = INPUT_MOUSE;
    buffer->mi.dx = (0 * (0xFFFF / SCREEN_WIDTH));
    buffer->mi.dy = (0 * (0xFFFF / SCREEN_HEIGHT));
    buffer->mi.mouseData = 0;
    buffer->mi.dwFlags = MOUSEEVENTF_ABSOLUTE;
    buffer->mi.time = 0;
    buffer->mi.dwExtraInfo = 0;
}

Point2D WINFUNCTIONS::getCursorPos()
{
    POINT pos;
    GetCursorPos(&pos);
    return Point2D{pos.x, pos.y};
}

void WINFUNCTIONS::setCursorPos(int x, int y)
{
    SetCursorPos(x, y);
}

void WINFUNCTIONS::moveCursor(int dx, int dy)
{
    Point2D cursorPos = getCursorPos();
    setCursorPos(cursorPos.x + dx, cursorPos.y + dy);
}

void WINFUNCTIONS::mouseDownLeft()
{
    buffer->mi.dwFlags = (MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_LEFTDOWN);
    SendInput(1, buffer, sizeof(INPUT));
}

void WINFUNCTIONS::mouseUpLeft()
{
    buffer->mi.dwFlags = (MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_LEFTUP);
    SendInput(1, buffer, sizeof(INPUT));
}

void WINFUNCTIONS::mouseDownRight()
{
    buffer->mi.dwFlags = (MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_RIGHTDOWN);
    SendInput(1, buffer, sizeof(INPUT));
}

void WINFUNCTIONS::mouseUpRight()
{
    buffer->mi.dwFlags = (MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_RIGHTUP);
    SendInput(1, buffer, sizeof(INPUT));
}

void WINFUNCTIONS::downKey(int key)
{
    keybd_event(key, getScancode(key),
        KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYDOWN, 0);
}

void WINFUNCTIONS::upKey(int key)
{
    keybd_event(key, getScancode(key),
        KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP, 0);
}

void WINFUNCTIONS::mouseScrollUp()
{
    mouse_event(MOUSEEVENTF_WHEEL, 0, 0, 120, 0);
}

void WINFUNCTIONS::mouseScrollDown()
{
    mouse_event(MOUSEEVENTF_WHEEL, 0, 0, -120, 0);
}

#endif // WIN32
