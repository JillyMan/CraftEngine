#pragma once 
#include <Craft/Math/Vectors.h>

namespace Craft { namespace Input {

#define MAX_KEY_COUNT 256
#define MAX_MOUSE_KEY_COUNT 12

#define MOUSE_BUTTON_1 1
#define MOUSE_BUTTON_2 2
#define MOUSE_BUTTON_3 3
#define MOUSE_BUTTON_4 4
#define MOUSE_BUTTON_5 5

	class InputHandler 
	{
	private:
		static bool s_Keys[MAX_KEY_COUNT];
		static bool s_MouseKeys[MAX_MOUSE_KEY_COUNT];
		static v2 s_MousePosition;

	public:
		static bool IsKeyPressed(s32 keyCode);
		void OnKeyPressed(s32 keyCode);
		void OnKeyReleased(s32 keyCode);

		static bool IsMouseKeyPressed(s32 keyCode);
		void OnMouseKeyPressed(s32 keyCode);
		void OnMouseKeyReleased(s32 keyCode);

		static v2 GetMousePosition();
		void SetMousePosition(s32 x, s32 y);
};
} }