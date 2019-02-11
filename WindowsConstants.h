#ifndef WINDOWSCONSTANTS_H
#define WINDOWSCONSTANTS_H

#ifdef WIN32

namespace MouseButton
{
    static constexpr int Left  = 1; // real numbers have no matter
    static constexpr int Right = 2; // they just must be different
}

namespace Key {
    static constexpr int N0 = 0x30;
    static constexpr int N1 = 0x31;
    static constexpr int N2 = 0x32;
    static constexpr int N3 = 0x33;
    static constexpr int N4 = 0x34;
    static constexpr int N5 = 0x35;
    static constexpr int N6 = 0x36;
    static constexpr int N7 = 0x37;
    static constexpr int N8 = 0x38;
    static constexpr int N9 = 0x39;
    static constexpr int A = 0x41;
    static constexpr int B = 0x42;
    static constexpr int C = 0x43;
    static constexpr int D = 0x44;
    static constexpr int E = 0x45;
    static constexpr int F = 0x46;
    static constexpr int G = 0x47;
    static constexpr int H = 0x48;
    static constexpr int I = 0x49;
    static constexpr int J = 0x4A;
    static constexpr int K = 0x4B;
    static constexpr int L = 0x4C;
    static constexpr int M = 0x4D;
    static constexpr int N = 0x4E;
    static constexpr int O = 0x4F;
    static constexpr int P = 0x50;
    static constexpr int Q = 0x51;
    static constexpr int R = 0x52;
    static constexpr int S = 0x53;
    static constexpr int T = 0x54;
    static constexpr int U = 0x55;
    static constexpr int V = 0x56;
    static constexpr int W = 0x57;
    static constexpr int X = 0x58;
    static constexpr int Y = 0x59;
    static constexpr int Z = 0x5A;
    static constexpr int Space   = 0x20; // VK_SPACE;
    static constexpr int Escape  = 0x1B; // VK_ESCAPE;
    static constexpr int Shift   = 0xA0; // VK_LSHIFT;
    static constexpr int Control = 0xA2; // VK_LCONTROL;
    static constexpr int Alt     = 0xA4; // VK_LMENU;
    static constexpr int Enter   = 0x0D; // VK_RETURN;
}

static int getScancode(int key)
{
    switch (key)
    {
    case Key::N0 : return 0x0B;
    case Key::N1 : return 0x02;
    case Key::N2 : return 0x03;
    case Key::N3 : return 0x04;
    case Key::N4 : return 0x05;
    case Key::N5 : return 0x06;
    case Key::N6 : return 0x07;
    case Key::N7 : return 0x08;
    case Key::N8 : return 0x09;
    case Key::N9 : return 0x0A;
    case Key::Q : return 0x10;
    case Key::W : return 0x11;
    case Key::E : return 0x12;
    case Key::R : return 0x13;
    case Key::T : return 0x14;
    case Key::Y : return 0x15;
    case Key::U : return 0x16;
    case Key::I : return 0x17;
    case Key::O : return 0x18;
    case Key::P : return 0x19;
    case Key::A : return 0x1E;
    case Key::S : return 0x1F;
    case Key::D : return 0x20;
    case Key::F : return 0x21;
    case Key::G : return 0x22;
    case Key::H : return 0x23;
    case Key::J : return 0x24;
    case Key::K : return 0x25;
    case Key::L : return 0x26;
    case Key::Z : return 0x2C;
    case Key::X : return 0x2D;
    case Key::C : return 0x2E;
    case Key::V : return 0x2F;
    case Key::B : return 0x30;
    case Key::N : return 0x31;
    case Key::M : return 0x32;
    }
}

static constexpr int KEYEVENTF_KEYDOWN = 0x0;

#endif // WIN32

#endif // WINDOWSCONSTANTS_H
