#pragma once

#include "Craft\Window\WindowHandle.h"
#include "Craft\Window\WindowManager.h"

namespace Craft
{
	enum class DrawType
	{
		Points = 0,
		Triangles = 1
	};

	enum class BufferType
	{
		Array = 0
	};

	struct BackBuffer
	{
		s32 Width;
		s32 Height;
		u32 BytesPerPixel;
		void* Pixels;

#ifdef CRAFT_PLATFORM_WINDOWS
		BITMAPINFO bitmapInfo;
#endif
	};

	static BackBuffer* CurrentBackBuffer;

	void InitGLContext(WindowHandle handle);
	void BindVertexBuffer(u32& bufferId, f32* verticies, u32 size);
	void UnbindVertexBuffer(u32 bufferId, f32* verticies, u32 size);
	void BindIndicesBuffer(u32& bufferId, f32* verticies, u32 size);
	void UnbindIndicesBuffer(f32* verticies, u32 size);
	void DrawArrays(DrawType mode, u32 first, u32 count);


	static void WindowsContextInit(BackBuffer* screenBuffer, u32 width, u32 height)
	{
		if (screenBuffer->Pixels != NULL)
		{
			VirtualFree(screenBuffer->Pixels, 0, MEM_RELEASE);
		}

		int BytesPerPixel = 4;
		screenBuffer->BytesPerPixel = BytesPerPixel;
		screenBuffer->Width = width;
		screenBuffer->Height = height;

		auto& bitmapInfo = screenBuffer->bitmapInfo;
		bitmapInfo.bmiHeader.biSize = sizeof(bitmapInfo.bmiHeader);
		bitmapInfo.bmiHeader.biWidth = screenBuffer->Width;
		bitmapInfo.bmiHeader.biHeight = -screenBuffer->Height;
		bitmapInfo.bmiHeader.biPlanes = 1;
		bitmapInfo.bmiHeader.biBitCount = 32;
		bitmapInfo.bmiHeader.biCompression = BI_RGB;

		int BitmapMemorySize = (width * height) * BytesPerPixel;
		screenBuffer->Pixels = VirtualAlloc(0, BitmapMemorySize, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
	}
	static void DrawTriangles();
	static void DrawPoints();

	void Win32DisplayBufferInWindow(BackBuffer* screenBuffer, WindowHandle window)
	{
#ifdef CRAFT_PLATFORM_WINDOWS
		HDC DeviceContext = GetDC(window);

		StretchDIBits(DeviceContext,
			0, 0,
			screenBuffer->Width,
			screenBuffer->Height,
			0, 0,
			screenBuffer->Width,
			screenBuffer->Height,
			screenBuffer->Pixels,
			&screenBuffer->bitmapInfo,
			DIB_RGB_COLORS,
			SRCCOPY);
		ReleaseDC(window, DeviceContext);
#else
		#error only windows support
#endif
	}
}