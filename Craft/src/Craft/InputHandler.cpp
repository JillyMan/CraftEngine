#include <Craft/InputHandler.h>

namespace Craft { namespace Input { 

	v2 InputHandler::s_MousePosition;
	bool InputHandler::s_Keys[MAX_KEY_COUNT];
	bool InputHandler::s_MouseKeys[MAX_MOUSE_KEY_COUNT];

	bool InputHandler::IsKeyPressed(s32 keyCode)
	{
		if (keyCode < MAX_KEY_COUNT)
		{
			return s_Keys[keyCode];
		}

		return false;
	}

	void InputHandler::OnKeyPressed(s32 keyCode)
	{
		if (keyCode < MAX_KEY_COUNT)
		{
			s_Keys[keyCode] = true;
		}
	}

	void InputHandler::OnKeyReleased(s32 keyCode)
	{
		if (keyCode < MAX_KEY_COUNT)
		{
			s_Keys[keyCode] = false;
		}
	}

	bool InputHandler::IsMouseKeyPressed(s32 keyCode)
	{
		if (keyCode < MAX_MOUSE_KEY_COUNT)
		{
			return s_MouseKeys[keyCode];
		}

		return false;
	}

	void InputHandler::OnMouseKeyPressed(s32 keyCode)
	{
		if (keyCode < MAX_MOUSE_KEY_COUNT)
		{
			s_MouseKeys[keyCode] = true;
		}
	}

	void InputHandler::OnMouseKeyReleased(s32 keyCode)
	{
		if (keyCode < MAX_MOUSE_KEY_COUNT)
		{
			s_MouseKeys[keyCode] = false;
		}
	}

	v2 InputHandler::GetMousePosition()
	{
		return s_MousePosition;
	}

	void InputHandler::SetMousePosition(s32 x, s32 y) 
	{
		s_MousePosition.x = x;
		s_MousePosition.y = y;
	}
}}