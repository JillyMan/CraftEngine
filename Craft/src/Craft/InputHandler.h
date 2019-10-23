#pragma once 

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
		
		static s32 s_MouseX;
		static s32 s_MouseY;
	
	public:
		static bool IsKeyPressed(u32 keyCode);
		void OnKeyPressed(u32 keyCode);
		void OnKeyReleased(u32 keyCode);

		static bool IsMouseKeyPressed(u32 keyCode);
		void OnMouseKeyPressed(u32 keyCode);
		void OnMouseKeyReleased(u32 keyCode);

		static void GetMousePosition(s32& x, s32 y);
		void SetMousePosition(s32 x, s32 y);
};
} }