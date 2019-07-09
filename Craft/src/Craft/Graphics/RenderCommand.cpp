#include "crpch.h"
#include "RenderCommand.h"

#include "Platform\OpenGL\OpenGLRendererAPI.h"

namespace Craft 
{
	RendererAPI* RenderCommand::s_RendererAPI = new OpenGLRendererAPI;
}