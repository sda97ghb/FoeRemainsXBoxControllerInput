#include <iostream>
#include <thread>

#include <xinput.h>
#include <windows.h>

class ControllerIsNotConnectedException : public std::logic_error
{
public:
    ControllerIsNotConnectedException() :
        std::logic_error("Controller is not connected")
    {
        // Designed as empty
    }
};

XINPUT_GAMEPAD getGamepadState()
{
    DWORD dwResult;
    for (DWORD i = 0; i < XUSER_MAX_COUNT; i++)
    {
        XINPUT_STATE state;
        ZeroMemory(&state, sizeof(XINPUT_STATE));

        // Simply get the state of the controller from XInput.
        dwResult = XInputGetState(i, &state);

        if (dwResult == ERROR_SUCCESS)
            return state.Gamepad;
        else
            throw ControllerIsNotConnectedException();
    }
    return XINPUT_GAMEPAD();
}

enum Side
{
    Left,
    Right,
    Up,
    Down
};

enum Axis
{
    X,
    Y
};

enum Button
{
    ChangeView,
    Menu,
    LeftButton,
    RightButton,
    LeftThumb,
    RightThumb,
    DPadUp,
    DPadDown,
    DPadLeft,
    DPadRight,
    AButton,
    BButton,
    XButton,
    YButton
};

static const Button BUTTONS[] = {
    ChangeView,
    Menu,
    LeftButton,
    RightButton,
    LeftThumb,
    RightThumb,
    DPadUp,
    DPadDown,
    DPadLeft,
    DPadRight,
    AButton,
    BButton,
    XButton,
    YButton
};

class ControllerState
{
public:
    ControllerState(XINPUT_GAMEPAD&& state) :
        m_state(state)
    {
        ;
    }

    int getTrigger(Side side) const
    {
        switch (side)
        {
            case Left: return m_state.bLeftTrigger;
            case Right: return m_state.bRightTrigger;
            default: return 0;
        }
    }

    int getThumb(Side side, Axis axis) const
    {
             if (side == Left  && axis == X) return m_state.sThumbLX;
        else if (side == Left  && axis == Y) return m_state.sThumbLY;
        else if (side == Right && axis == X) return m_state.sThumbRX;
        else if (side == Right && axis == Y) return m_state.sThumbRY;
        else return 0;
    }

    bool isDown(Button button) const
    {
        switch (button)
        {
            case ChangeView:  return (m_state.wButtons & XINPUT_GAMEPAD_BACK)  != 0;
            case Menu: return (m_state.wButtons & XINPUT_GAMEPAD_START) != 0;

            case LeftButton:  return (m_state.wButtons & XINPUT_GAMEPAD_LEFT_SHOULDER)  != 0;
            case RightButton: return (m_state.wButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER) != 0;

            case LeftThumb:  return (m_state.wButtons & XINPUT_GAMEPAD_LEFT_THUMB)  != 0;
            case RightThumb: return (m_state.wButtons & XINPUT_GAMEPAD_RIGHT_THUMB) != 0;

            case DPadUp:    return (m_state.wButtons & XINPUT_GAMEPAD_DPAD_UP)    != 0;
            case DPadDown:  return (m_state.wButtons & XINPUT_GAMEPAD_DPAD_DOWN)  != 0;
            case DPadLeft:  return (m_state.wButtons & XINPUT_GAMEPAD_DPAD_LEFT)  != 0;
            case DPadRight: return (m_state.wButtons & XINPUT_GAMEPAD_DPAD_RIGHT) != 0;

            case AButton: return (m_state.wButtons & XINPUT_GAMEPAD_A) != 0;
            case BButton: return (m_state.wButtons & XINPUT_GAMEPAD_B) != 0;
            case XButton: return (m_state.wButtons & XINPUT_GAMEPAD_X) != 0;
            case YButton: return (m_state.wButtons & XINPUT_GAMEPAD_Y) != 0;

            default: return false;
        }
    }

//    friend std::ostream& operator << (std::ostream& stream, const ControllerState& state);

private:
    XINPUT_GAMEPAD m_state;
};

std::ostream& operator << (std::ostream& stream, const ControllerState& state)
{
    return stream << state.isDown(ChangeView) << " " <<
                     state.isDown(Menu) << " " <<
                     state.getTrigger(Left) << " " <<
                     state.getTrigger(Right) << " " <<
                     state.isDown(LeftButton) << " " <<
                     state.isDown(RightButton) << " " <<
                     state.getThumb(Left, X) << " " <<
                     state.getThumb(Left, Y) << " " <<
                     state.getThumb(Right, X) << " " <<
                     state.getThumb(Right, Y) << " " <<
                     state.isDown(LeftThumb) << " " <<
                     state.isDown(RightThumb) << " " <<
                     state.isDown(DPadLeft) << " " <<
                     state.isDown(DPadRight) << " " <<
                     state.isDown(DPadUp) << " " <<
                     state.isDown(DPadDown) << " " <<
                     state.isDown(AButton) << " " <<
                     state.isDown(BButton) << " " <<
                     state.isDown(XButton) << " " <<
                     state.isDown(YButton);
}

class Controller
{
public:
    Controller() :
        m_state(getGamepadState()),
        m_previousState(m_state)
    {}

    virtual void update()
    {
        m_state = ControllerState(getGamepadState());
//        std::cout << m_state << std::endl;
        for (Button button : BUTTONS) {
            if (m_state.isDown(button) != m_previousState.isDown(button))
            {
                if (m_state.isDown(button))
                    buttonDown(button);
                else
                    buttonUp(button);
            }
        }

        if (m_state.getThumb(Left, X) != m_previousState.getThumb(Left, X) ||
            m_state.getThumb(Left, Y) != m_previousState.getThumb(Left, Y))
            thumbChanged(Left);
        if (m_state.getThumb(Right, X) != m_previousState.getThumb(Right, X) ||
            m_state.getThumb(Right, Y) != m_previousState.getThumb(Right, Y))
            thumbChanged(Right);

        if (m_state.getTrigger(Left) != m_previousState.getTrigger(Left))
            triggerChanged(Left);
        if (m_state.getTrigger(Right) != m_previousState.getTrigger(Right))
            triggerChanged(Right);

        m_previousState = m_state;
    }

    ControllerState getState() const
    {
        return m_state;
    }

    virtual void triggerChanged(Side side) {}
    virtual void thumbChanged(Side side) {}

    virtual void buttonDown(Button button) {}
    virtual void buttonUp(Button button) {}

private:
    ControllerState m_previousState;
    ControllerState m_state;
};

#include "Keyboard.h"
#include "WindowsFunctions.h"

//int x = 0;
//int y = 0;

//void moveCursor()
//{
//    while (true) {
//        if (::x > 1 || ::y > 1)
//            WINFUNCTIONS::moveCursor(::x, ::y);
//        std::this_thread::sleep_for(std::chrono::milliseconds(10));
//    }
//}

//std::thread move_cursor_thread(moveCursor);

class ConcreteController : public Controller
{
    void update() {
        Controller::update();

        static int counter = 0;
        ++ counter;
        if (counter > 5000)
        {
            counter = 0;

            int x =   getState().getThumb(Right, X) / 3200;
            int y = - getState().getThumb(Right, Y) / 3200;
            int threshold = 1;
            if (x > threshold || y > threshold || x < -threshold || y < -threshold)
                WINFUNCTIONS::moveCursor(x, y);
        }
    }

    void thumbChanged(Side side)
    {
        if (side == Left)
        {
            if (getState().getThumb(Left, X) < -20000)
                Keyboard::downKey(Keyboard::A);
            else
                Keyboard::upKey(Keyboard::A);
            if (getState().getThumb(Left, X) > 20000)
                Keyboard::downKey(Keyboard::D);
            else
                Keyboard::upKey(Keyboard::D);
            if (getState().getThumb(Left, Y) < -20000)
                Keyboard::downKey(Keyboard::S);
            else
                Keyboard::upKey(Keyboard::S);
            if (getState().getThumb(Left, Y) > 20000)
                Keyboard::downKey(Keyboard::W);
            else
                Keyboard::upKey(Keyboard::W);
        }
    }

    void triggerChanged(Side side)
    {
        if (side == Right)
        {
            if (getState().getTrigger(Right) > 180)
                WINFUNCTIONS::mouseDownRight();
            else
                WINFUNCTIONS::mouseUpRight();
        }
        if (side == Left)
        {
            if (getState().getTrigger(Left) > 180)
                Keyboard::downKey(Keyboard::F);
            else
                Keyboard::upKey(Keyboard::F);
        }
    }

    void buttonDown(Button button)
    {
        if (button == LeftThumb) Keyboard::downKey(Keyboard::Shift);

        if (button == LeftButton) Keyboard::downKey(Keyboard::Space);

        if (button == AButton) Keyboard::downKey(Keyboard::E);
        if (button == BButton) Keyboard::downKey(Keyboard::R);
        if (button == XButton) Keyboard::downKey(Keyboard::F);
        if (button == YButton) Keyboard::downKey(Keyboard::V);

        if (button == RightButton) WINFUNCTIONS::mouseDownLeft();
    }

    void buttonUp(Button button)
    {
        if (button == Menu) Keyboard::downAndUpKey(Keyboard::Tab);

        if (button == ChangeView) Keyboard::downAndUpKey(Keyboard::M);

        if (button == LeftThumb) Keyboard::upKey(Keyboard::Shift);

        if (button == LeftButton) Keyboard::upKey(Keyboard::Space);

        if (button == DPadLeft)  Keyboard::downAndUpKey(Keyboard::Digit_1);
        if (button == DPadUp)    Keyboard::downAndUpKey(Keyboard::Digit_2);
        if (button == DPadRight) Keyboard::downAndUpKey(Keyboard::Digit_3);
        if (button == DPadDown)  Keyboard::downAndUpKey(Keyboard::Digit_4);

        if (button == AButton) Keyboard::upKey(Keyboard::E);
        if (button == BButton) Keyboard::upKey(Keyboard::R);
        if (button == XButton) Keyboard::upKey(Keyboard::F);
        if (button == YButton) Keyboard::upKey(Keyboard::V);

        if (button == RightButton) WINFUNCTIONS::mouseUpLeft();
    }
};

int main(int argc, char *argv[])
{
    (void) argc;
    (void) argv;

    Controller* controller;

    try
    {
        controller = new ConcreteController;

        while (true)
            controller->update();
    }
    catch (ControllerIsNotConnectedException& e)
    {
        std::cout << e.what() << std::endl;
        return 1;
    }

    delete controller;

    return 0;
}
