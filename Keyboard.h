#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <map>

#include <windows.h>

class Keyboard
{
public:
    // DirectInput scan codes
    // More info: https://gist.github.com/tracend/912308
    static const WORD A = 0x1e;
    static const WORD B = 0x30;
    static const WORD C = 0x2e;
    static const WORD D = 0x20;
    static const WORD E = 0x12;
    static const WORD F = 0x21;
    static const WORD H = 0x23;
    static const WORD I = 0x17;
    static const WORD J = 0x24;
    static const WORD K = 0x25;
    static const WORD L = 0x26;
    static const WORD M = 0x32;
    static const WORD P = 0x19;
    static const WORD Q = 0x10;
    static const WORD R = 0x13;
    static const WORD S = 0x1f;
    static const WORD T = 0x14;
    static const WORD U = 0x16;
    static const WORD V = 0x2f;
    static const WORD W = 0x11;
    static const WORD X = 0x2d;
    static const WORD Y = 0x15;
    static const WORD Z = 0x2c;

    static const WORD Digit_1 = 0x02;
    static const WORD Digit_2 = 0x03;
    static const WORD Digit_3 = 0x04;
    static const WORD Digit_4 = 0x05;

    static const WORD Control = 0x1d;
    static const WORD Shift = 0x2a;
    static const WORD Tab = 0x0f;

    static const WORD Space = 0x39;
    static const WORD Backspace = 0x0e;

    static const WORD Up = 0xe048;
    static const WORD Down = 0x50;
    static const WORD Left = 0xe04b;
    static const WORD Right = 0xe04d;

    static const WORD Escape = 0x01;
    static const WORD End = 0x4f;
    static const WORD Enter = 0x1c;
    static const WORD Delete = 0x53;

    static void downKey(WORD key);
    static void upKey(WORD key);
    static void downAndUpKey(WORD key);

    static void setDownAndUpDelay(int msecs);

private:
    static int downAndUpDelay;

    static std::map<WORD, bool> pressedKeys;
};

#endif // KEYBOARD_H
