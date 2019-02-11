#include "Keyboard.h"

#include <thread>

int Keyboard::downAndUpDelay = 50;

std::map<WORD, bool> Keyboard::pressedKeys;

void Keyboard::downKey(WORD key)
{
    if (pressedKeys.find(key) != pressedKeys.end())
        if (pressedKeys.at(key))
            return;

    pressedKeys[key] = true;

    INPUT input;
    input.type = INPUT_KEYBOARD;
    input.ki.time = 0;
    input.ki.wVk = 0;
    input.ki.dwExtraInfo = 0;
    input.ki.dwFlags = KEYEVENTF_SCANCODE;
    input.ki.wScan = key;
    SendInput(1, &input, sizeof(INPUT));
}

void Keyboard::upKey(WORD key)
{
    if (pressedKeys.find(key) != pressedKeys.end())
        if (!pressedKeys.at(key))
            return;

    pressedKeys[key] = false;

    INPUT input;
    input.type = INPUT_KEYBOARD;
    input.ki.time = 0;
    input.ki.wVk = 0;
    input.ki.dwExtraInfo = 0;
    input.ki.dwFlags = KEYEVENTF_SCANCODE | KEYEVENTF_KEYUP;
    input.ki.wScan = key;
    SendInput(1, &input, sizeof(INPUT));
}

void Keyboard::downAndUpKey(WORD key)
{
    downKey(key);
    std::this_thread::sleep_for(std::chrono::milliseconds(Keyboard::downAndUpDelay));
    upKey(key);
}

void Keyboard::setDownAndUpDelay(int msecs)
{
    Keyboard::downAndUpDelay = msecs;
}
