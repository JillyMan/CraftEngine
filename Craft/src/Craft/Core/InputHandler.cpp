#include <Craft\Core\InputHandler.h>

namespace Craft { namespace Input { 

	s32 InputHandler::s_MouseX;
	s32 InputHandler::s_MouseY;
	bool InputHandler::s_Keys[MAX_KEY_COUNT];
	bool InputHandler::s_MouseKeys[MAX_MOUSE_KEY_COUNT];

	bool InputHandler::IsKeyPressed(u32 keyCode)
	{
		if (keyCode < MAX_KEY_COUNT)
		{
			return s_Keys[keyCode];
		}

		return false;
	}

	void InputHandler::OnKeyPressed(u32 keyCode)
	{
		if (keyCode < MAX_KEY_COUNT)
		{
			s_Keys[keyCode] = true;
		}
	}

	void InputHandler::OnKeyReleased(u32 keyCode)
	{
		if (keyCode < MAX_KEY_COUNT)
		{
			s_Keys[keyCode] = false;
		}
	}

	bool InputHandler::IsMouseKeyPressed(u32 keyCode)
	{
		if (keyCode < MAX_MOUSE_KEY_COUNT)
		{
			return s_MouseKeys[keyCode];
		}

		return false;
	}

	void InputHandler::OnMouseKeyPressed(u32 keyCode)
	{
		if (keyCode < MAX_MOUSE_KEY_COUNT)
		{
			s_MouseKeys[keyCode] = true;
		}
	}

	void InputHandler::OnMouseKeyReleased(u32 keyCode)
	{
		if (keyCode < MAX_MOUSE_KEY_COUNT)
		{
			s_MouseKeys[keyCode] = false;
		}
	}

	void InputHandler::GetMousePosition(s32& x, s32 y)
	{
		x = s_MouseX;
		y = s_MouseY;
	}

	void InputHandler::SetMousePosition(s32 x, s32 y) 
	{
		s_MouseX = x;
		s_MouseY = y;
	}
}}