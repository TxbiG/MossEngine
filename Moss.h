//                        MIT License
//
//                  Copyright (c) 2024 Toby
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:

// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.

// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
//
//     /$$      /$$                                    /$$$$$$$$                     /$$                    
//    | $$$    /$$$                                   | $$_____/                    |__/                    
//    | $$$$  /$$$$  /$$$$$$   /$$$$$$$ /$$$$$$$      | $$       /$$$$$$$   /$$$$$$  /$$ /$$$$$$$   /$$$$$$ 
//    | $$ $$/$$ $$ /$$__  $$ /$$_____//$$_____/      | $$$$$   | $$__  $$ /$$__  $$| $$| $$__  $$ /$$__  $$
//    | $$  $$$| $$| $$  \ $$|  $$$$$$|  $$$$$$       | $$__/   | $$  \ $$| $$  \ $$| $$| $$  \ $$| $$$$$$$$
//    | $$\  $ | $$| $$  | $$ \____  $$\____  $$      | $$      | $$  | $$| $$  | $$| $$| $$  | $$| $$_____/
//    | $$ \/  | $$|  $$$$$$/ /$$$$$$$//$$$$$$$/      | $$$$$$$$| $$  | $$|  $$$$$$$| $$| $$  | $$|  $$$$$$$
//    |__/     |__/ \______/ |_______/|_______/       |________/|__/  |__/ \____  $$|__/|__/  |__/ \_______/
//                                                                         /$$  \ $$                        
//                                                                       |  $$$$$$/                        
//                                                                        \______/                         


// Todo - 
// Display Window   ./
// Get Inputs
// Display OpenGL in the window
// Display UI
// ////////////////// v1
// Render 2D stuff
// ////////////////// v2
// Render 3D stuff
// ////////////////// v3
// Clean up
////////////////////////////////////////////////////////////////////////////
/*                                  Moss.h

                        Moss handles all the front-end.
                Also used for presenting crossplatform functions
            Window - creating/destorying, inputs, cursor, flags, time, threads

            UI -

            2D -

            3D -

*/
///////////////////////////////////////////////////////////////////////////
#ifndef MOSS_ENGINE_H
#define MOSS_ENGINE_H

#include "platform/window.h" /* <-- Remove */
//#include "Math.h"
//#include "UI.h"
//#include "2D.h"
//#include "3D.h"
//#include "Variants.h"
//#include "Resources.h"

#ifndef MOSS_API
#define MOSS_API
#endif
#ifndef MOSS_IMPL_API
#define MOSS_IMPL_API MOSS_API
#endif


#define MOUSE_MODE_VISIBLE          0
#define MOUSE_MODE_HIDDEN           1
#define MOUSE_MODE_CAPTURED         2
#define MOUSE_MODE_CONFINED         3
#define MOUSE_MODE_CONFINED_HIDDEN  4

// Focus modes
#define FOCUS_NONE   0
#define FOCUS_CLICK  1
#define FOCUS_ALL    2

// Window modes
#define WINDOW_FULLSCREEN   0
#define WINDOW_BORDERLESS   1
#define WINDOW_MINIMIZE     2
#define WINDOW_MAXIMIZE     3

// Window flags (using bitwise operations)
#define WindowFlags_None                        0
#define WindowFlags_NoTitleBar                  (1 << 0)
#define WindowFlags_NoResize                    (1 << 1)
#define WindowFlags_NoMove                      (1 << 2)
#define WindowFlags_NoScrollbar                 (1 << 3)
#define WindowFlags_NoScrollWithMouse           (1 << 4)
#define WindowFlags_NoCollapse                  (1 << 5)
#define WindowFlags_AlwaysAutoResize            (1 << 6)
#define WindowFlags_NoBackground                (1 << 7)
#define WindowFlags_NoSavedSettings             (1 << 8)
#define WindowFlags_NoMouseInputs               (1 << 9)
#define WindowFlags_MenuBar                     (1 << 10)
#define WindowFlags_HorizontalScrollbar         (1 << 11)
#define WindowFlags_NoFocusOnAppearing          (1 << 12)
#define WindowFlags_NoBringToFrontOnFocus       (1 << 13)
#define WindowFlags_AlwaysVerticalScrollbar     (1 << 14)
#define WindowFlags_AlwaysHorizontalScrollbar   (1 << 15)
#define WindowFlags_NoNavInputs                 (1 << 16)
#define WindowFlags_NoNavFocus                  (1 << 17)
#define WindowFlags_UnsavedDocument             (1 << 18)

#define WindowFlags_NoNav         (WindowFlags_NoNavInputs | WindowFlags_NoNavFocus)
#define WindowFlags_NoDecoration  (WindowFlags_NoTitleBar | WindowFlags_NoResize | WindowFlags_NoScrollbar | WindowFlags_NoCollapse)
#define WindowFlags_NoInputs      (WindowFlags_NoMouseInputs | WindowFlags_NoNavInputs | WindowFlags_NoNavFocus)


#define InputConfig_Keyboard    0
#define InputConfig_Mouse       1
#define InputConfig_JoyStick    2

#define CURSOR_ARROW            0
#define CURSOR_IBEAM            1
#define CURSOR_POINTING_HAND    2
#define CURSOR_CROSS            3
#define CURSOR_WAIT             4
#define CURSOR_FORBIDDEN        5
#define CURSOR_VSIZE            6
#define CURSOR_HSIZE            7


#define KEY_0 0
#define KEY_1 2
#define KEY_2 3
#define KEY_3 4
#define KEY_4 5
#define KEY_5 6
#define KEY_6 7
#define KEY_7 8
#define KEY_8 9
#define KEY_9 10
#define KEY_A 11
#define KEY_B 12
#define KEY_C 13
#define KEY_D 14
#define KEY_E 15
#define KEY_F 16
#define KEY_G 17
#define KEY_H 18
#define KEY_I 19
#define KEY_J 20
#define KEY_K 21
#define KEY_L 22
#define KEY_M 23
#define KEY_N 24
#define KEY_O 25
#define KEY_P 26
#define KEY_Q 27
#define KEY_R 28
#define KEY_S 29
#define KEY_T 30
#define KEY_U 31
#define KEY_V 32
#define KEY_W 33
#define KEY_X 34
#define KEY_Y 35
#define KEY_Z 36

#define KEY_APOSTROPHE      37
#define KEY_BACKSLASH       38
#define KEY_COMMA           39
#define KEY_EQUAL           40
#define KEY_GRAVE_ACCENT    41
#define KEY_LEFT_BRACKET    42
#define KEY_MINUS           43
#define KEY_PERIOD          44
#define KEY_RIGHT_BRACKET   45
#define KEY_SEMICOLON       46
#define KEY_SLASH           47
#define KEY_WORLD_2         48

#define KEY_BACKSPACE       49
#define KEY_DELETE          50
#define KEY_END             51
#define KEY_ENTER           52
#define KEY_ESCAPE          53
#define KEY_HOME            54
#define KEY_INSERT          55
#define KEY_MENU            56
#define KEY_PAGE_DOWN       57
#define KEY_PAGE_UP         58
#define KEY_PAUSE           59
#define KEY_SPACE           60
#define KEY_TAB             61
#define KEY_CAPS_LOCK       62
#define KEY_NUM_LOCK        63
#define KEY_SCROLL_LOCK     64

#define KEY_F1  65
#define KEY_F2  66
#define KEY_F3  67
#define KEY_F4  68
#define KEY_F5  69
#define KEY_F6  70
#define KEY_F7  71
#define KEY_F8  72
#define KEY_F9  73
#define KEY_F10 74
#define KEY_F11 75
#define KEY_F12 76
#define KEY_F13 77
#define KEY_F14 78
#define KEY_F15 79
#define KEY_F16 80
#define KEY_F17 81
#define KEY_F18 82
#define KEY_F19 83
#define KEY_F20 84
#define KEY_F21 85
#define KEY_F22 86
#define KEY_F23 87
#define KEY_F24 88

#define KEY_LEFT_ALT        89
#define KEY_LEFT_CONTROL    90
#define KEY_LEFT_SHIFT      91
#define KEY_LEFT_SUPER      92

#define KEY_PRINT_SCREEN    93
#define KEY_RIGHT_ALT       94
#define KEY_RIGHT_CONTROL   95
#define KEY_RIGHT_SHIFT     96
#define KEY_RIGHT_SUPER     97

#define KEY_DOWN    98
#define KEY_LEFT    99
#define KEY_RIGHT   100
#define KEY_UP      101

#define KEY_KP_0        102
#define KEY_KP_1        103
#define KEY_KP_2        104
#define KEY_KP_3        105
#define KEY_KP_4        106
#define KEY_KP_5        107
#define KEY_KP_6        108
#define KEY_KP_7        109
#define KEY_KP_8        110
#define KEY_KP_9        111
#define KEY_KP_ADD      112
#define KEY_KP_DECIMAL  113
#define KEY_KP_DIVIDE   114
#define KEY_KP_ENTER    115
#define KEY_KP_EQUAL    116
#define KEY_KP_MULTIPLY 117
#define KEY_KP_SUBTRACT 118

// Mouse
#define MOUSE_BUTTON_LEFT       0
#define MOUSE_BUTTON_RIGHT      1
#define MOUSE_BUTTON_MIDDLE     2
#define MOUSE_BUTTON_THUMB_1    3
#define MOUSE_BUTTON_THUMB_1    4
#define MOUSE_WHEEL_UP          5
#define MOUSE_WHEEL_DOWN        6
#define MOUSE_WHEEL_LEFT        7
#define MOUSE_WHEEL_RIGHT       8 

// Joystick/joypad buttons
#define GAMEPAD_BUTTON_A    0       // Xbox A, Sony X
#define GAMEPAD_BUTTON_B    1       // Xbox B Sony O
#define GAMEPAD_BUTTON_X    2       // Xbox X, Sony *Square*
#define GAMEPAD_BUTTON_Y    3       // Xbox Y, Sony *Triangle*
#define JOY_BUTTON_LB       4
#define JOY_BUTTON_RB       5
#define JOY_BUTTON_BACK     6
#define JOY_BUTTON_START    7
#define JOY_BUTTON_LS       8       // Left Stick Press
#define JOY_BUTTON_RS       9       // Right Stick Press

// Joystick axes
#define GAMEPAD_AXIS_LX     0       // Left Stick X Axis
#define GAMEPAD_AXIS_LY     1       // Left Stick Y Axis
#define GAMEPAD_AXIS_RX     2       // Right Stick X Axis
#define GAMEPAD_AXIS_RY     3       // Right Stick Y Axis
#define GAMEPAD_AXIS_LT     4       // Left Trigger
#define GAMEPAD_AXIS_RT     5       // Right Trigger


// Later -
// Need to find an audio lib

// Signed integer
typedef signed char      int8;	// 8-bit
typedef signed short     int16;	// 16-bit
typedef signed int       int32;	// 32-bit
typedef signed long long int64;	// 64-bit

// Unsigned integer
typedef unsigned char      uint8;  // 8-bit
typedef unsigned short     uint16; // 16-bit
typedef unsigned int       uint32; // 32-bit
typedef unsigned long long uint64; // 64-bit

typedef unsigned int   Wchar32; // A single decoded U32 character/code point. We encode them as multi bytes UTF-8 when used in strings.
typedef unsigned short Wchar16; // A single decoded U16 character/code point. We encode them as multi bytes UTF-8 when used in strings.

#ifdef USE_WCHAR32
typedef Wchar32 Wchar;
#else
typedef Wchar16 Wchar;
#endif

struct Moss_window;

/* Engine */
class Engine;
class OS;
class ResourceManager;

// Display and inputs

typedef struct InputMap;
typedef struct Input;
typedef struct InputEvent;
typedef struct InputEventKey;
typedef struct InputEventMouseButton;
typedef struct InputEventMouseMotion;
typedef struct InputEventJoypadMotion;
typedef struct InputEventJoypadButton;

/* Classes */
typedef class Viewport;
typedef class SubViewport;

typedef class CanvasLayer;              // Staticly place the UI on screen
typedef class WorldEnvironment;
typedef class Audio;
typedef class Timer;

// 2D
typedef class AudioStreamPlayer2D;
typedef class AudioListener2D;
typedef class Area2D;
typedef class Camera2D;
typedef class Collision2D;
typedef class CPUParticle2D;
typedef class GPUParticle2D;
typedef class CharacterBody2D;
typedef class RigidBody2D;
typedef class StaticBody2D;
typedef class Raycast2D;
typedef class Tilemap;
typedef class Sprite2D;
typedef class PointLight2D;
typedef class DirectionalLight2D;
typedef class SpringArm2D;
typedef class GroveJoint2D;
typedef class PinJoint2D;
typedef class RemoteTransform2D;
typedef class Parallax2D;
typedef class Bone2D;
typedef class Skeleton2D;

// 3D
typedef class AudioStreamPlayer3D;
typedef class AudioListener3D;
typedef class Area3D;
typedef class Camera3D;
typedef class Collision3D;
typedef class CPUParticle3D;
typedef class GPUParticle3D;
typedef class CharacterBody3D;
typedef class RigidBody3D;
typedef class StaticBody3D;
typedef class Raycast3D;
typedef class Gridmap;
typedef class SpringArm3D;
typedef class OmniLight2D;
typedef class SpotLight2D;
typedef class DirectionalLight2D;
typedef class Terrain;
typedef class Decal;
typedef class MeshInstance;
typedef class Skeleton3D;
typedef class Bone3D;
typedef class Sprite3D;

// GUI
typedef class GUI;
typedef class Container;
typedef class AspectRatioContainer;
typedef class BoxContainer;
typedef class VBoxContainer;
typedef class HBoxContainer;
typedef class FlowContainer;
typedef class VFlowContainer;
typedef class HFlowContainer;
typedef class CenterContainer;
typedef class GraphElement;
typedef class GraphFrame;
typedef class GraphNode;
typedef class GridContainer;
typedef class SplitContainer;
typedef class HSplitContainer;
typedef class VSplitContainer;
typedef class MarginContainer;
typedef class PanelContainer;
typedef class SubViewportContainer;
typedef class TabContainer;

typedef class Button;
typedef class CheckBox;
typedef class CheckButton;
typedef class ColorPickerButton;
typedef class MenuButton;
typedef class OptionButton;
typedef class LinkButton;
typedef class TextureButton;

typedef class TextEdit;
typedef class CodeEdit;
typedef class ColorRect;
typedef class TextureRect;
typedef class GraphEdit;
typedef class LineEdit;

typedef class Seperator;
typedef class HSeperator;
typedef class VSeperator;

typedef class ItemList;                 // Table list
typedef class Label;
typedef class RichTextLabel;
typedef class Panel;
typedef class TabBar;
typedef class Tree;
typedef class VideoStreamPlayer;
typedef class FileDialog;
typedef class ColorPicker;
typedef class Table;
typedef class Selectable;

typedef class Range;
typedef class Progressbar;
typedef class Spinbox;
typedef class TextureProgressbar;
typedef class Scrollbar;
typedef class HScrollbar;
typedef class VScrollbar;
typedef class Slider;
typedef class HSlider;
typedef class VSlider;

// IO
typedef struct Print;


// Window Flags
typedef int Window_WindowFlag;          // -> enum Window_WindowFlag_
typedef int Window_WindowModeFlag;      // -> enum Window_WindowMode_
typedef int Window_CursorShapeFlag;     // -> enum Window_CursorShape_
typedef int Window_MouseModeFlag;       // -> enum Window_MouseMode_
typedef int Window_FocusModeFlag;       // -> enum Window_FocusMode_


/*! @brief Creates a window.
 *  @ingroup window
 */
Moss_window* Moss_CreateWindow(int width, int height, const char* title, int flags, Moss_window* share);

/*! @brief Creates a window popup.
 *  @ingroup window
 */
Moss_window* Moss_CreatePopup(int width, int height, const char* title, int flags, window* share);
/*! @brief Sets window as current.
 *  @ingroup window
 */
void Moss_MakeContextCurrent(Moss_window* window);

/*! @brief Used in while loop if window should close.
 *  @ingroup window
 */
bool Moss_ShouldWindowClose(Moss_window* window);

/*! @brief Pollevents.
 *  @ingroup window
 */
void PollEvents(void);

/*! @brief Swapbuffers.
 *  @ingroup window
 */
void SwapBuffers(Moss_window* window);

/*! @brief Window Input Config.
 *  @ingroup window
 */
void setWindowInputConfig(int mode);

/*! @brief Change Window Mode.
 *  @ingroup window
 */
void setWindowMode(int mode);

/*! @brief Change Window Flags.
 *  @ingroup window
 */
void setWindowFlag(int mode);

/*! @brief Window Cursor shape.
 *  @ingroup window
 */
void setWindowCursorShape(int mode);

/*! @brief Window Cursor Mode.
 *  @ingroup window
 */
void setWindowCursorMode(int mode);


void Moss_setKeyCallbacks();
void Moss_setMouseCallbacks();
void Moss_setCursorCallbacks();
void Moss_setJoyStickCallbacks();

/*











typedef struct Moss_window {
    int width;
    int height;
    const char* title;
    int flags;
    // Add other window-specific properties (e.g., OpenGL context, window state, etc.)
} Moss_window;

// Function to create a window
Moss_window* Moss_CreateWindow(int width, int height, const char* title, int flags, Moss_window* share) {
    // Allocate memory for the new window
    Moss_window* window = (Moss_window*)malloc(sizeof(Moss_window));
    if (!window) {
        fprintf(stderr, "Failed to allocate memory for the window.\n");
        return NULL;
    }

    // Initialize the window struct
    window->width = width;
    window->height = height;
    window->title = title;
    window->flags = flags;

    // Check if the flags are valid (optional: validate if no unsupported flags are passed)
    if (flags & ~(MOSS_WINDOW_FULLSCREEN | MOSS_WINDOW_BORDERLESS | MOSS_WINDOW_RESIZABLE | 
                  MOSS_WINDOW_VISIBLE | MOSS_WINDOW_HIDDEN | MOSS_WINDOW_TRANSPARENT | 
                  MOSS_WINDOW_ALWAYS_ON_TOP | MOSS_WINDOW_MAXIMIZED)) {
        fprintf(stderr, "Invalid window flag(s) detected!\n");
        free(window);
        return NULL;
    }

    // Platform-specific window creation logic can go here.
    // Example pseudocode:
    #ifdef _WIN32
        // Windows-specific window creation code
        // Use flags to configure window properties (fullscreen, borderless, etc.)
        if (flags & MOSS_WINDOW_FULLSCREEN) {
            // Create a fullscreen window
        }
        if (flags & MOSS_WINDOW_BORDERLESS) {
            // Create a borderless window
        }
    #elif defined(__APPLE__)
        // macOS-specific window creation code
    #elif defined(__linux__)
        // Linux-specific window creation code
    #endif

    // If sharing resources with another window, perform context sharing logic
    if (share != NULL) {
        // Share OpenGL context, for example, if using OpenGL
    }

    // Return the newly created window
    return window;
}

*/
#endif // MOSS_ENGINE_H