#include <map>
#include <Craft.h>
#include <Craft\InputHandler.h>
#include <Craft\Graphics\Renderer.h>
#include <Craft\Graphics\RendererAPI.h>
#include <Craft\Graphics\RenderCommand.h>

#include <Craft\Graphics\Cameras\Camera.h>
#include <Craft\Graphics\Cameras\FPSCamera.h>

#include <Craft\Graphics\Texture.h>
#include <Craft\Graphics\Image\ImageLoader.h>

//------ PLATFORM CODE -------
#include <Platform\OpenGL\OpenGL.h>
#include <Platform\OpenGL\OpenGLShader.h>
#include <Platform\OpenGL\OpenGLBuffer.h>
#include <Platform\OpenGL\OpenGLTexture.h>
#include <Platform\OpenGL\OpenGLVertexArray.h>
#include <Platform\OpenGL\OpenGLRendererAPI.h>
//----------------------------

using namespace Craft;
using namespace Graphics;

#define FOV				45.0f
#define ASPECT_RATIO	DEFAULT_WINDOW_WIDTH / DEFAULT_WINDOW_HEIGHT
#define NEAR_PLANE		0.1f
#define FAR_PLANE		100.0f

const char* ANGLE_STRING = "angle";
const char* TEXTURE_STRING = "texture";
const char* MIX_COEFFICIENT_STRING = "mixCoefficient";
const char* U_COLOR_STRING = "u_color";

const char* VIEW_MATRIX_STRING = "vw_matrix";
const char* MODEL_MATRIX_STRING = "ml_matrix";
const char* PROJECTION_MATRIX_STRING = "pr_matrix";

String RootSpritesFolder = "C:\\Users\\Artsiom\\Documents\\Projects\\CraftEngine\\Assets\\Sprites\\";
String PathToGrassImage = "grass.bmp";
String PathToSmileImage = "smile.bmp";
String PathToTileSheets = "lgbt.bmp";

class Vfs {
private:
	String m_Root;

public:
	Vfs(String root) : m_Root(root)
	{
	}

	Image* GetImage(String path)
	{
		return ImageLoader::LoadBMPImage(m_Root + path);
	}
};

const char* GetVertexShader()
{
	return 
R"(
#version 460 core
layout (location = 0) in vec3 pos;
layout (location = 1) in vec2 InTexCoord1;
layout (location = 2) in vec2 InTexCoord2;

uniform mat4 pr_matrix = mat4(1.0f);
uniform mat4 vw_matrix = mat4(1.0f);
uniform mat4 ml_matrix = mat4(1.0f);

out vec2 TexCoord1;
out vec2 TexCoord2;

void main()
{
	gl_Position = pr_matrix * vw_matrix * ml_matrix * vec4(pos, 1.0f);

	TexCoord1 = InTexCoord1;
	TexCoord2 = InTexCoord2;
})";
}

const char* GetFragmentShader()
{
	return 
R"(
#version 460 core

uniform float mixCoefficient = 0.5f;
uniform sampler2D texture0;
uniform sampler2D texture1;
uniform vec4 u_color = vec4(1.0f, 1.0f, 1.0f, 1.0f);

in vec2 TexCoord1;
in vec2 TexCoord2;
out vec4 color;

void main()
{
	color = u_color * texture(texture0, TexCoord1);
})";
}

class Cube : public Shape
{
public:
	Cube(v3& pos, Image& image) : 
		Shape(pos, image)
	{
		InitTextureCube();
		m_Shader = new OpenGLShader(GetVertexShader(), GetFragmentShader());
	}

	Cube(v3& pos, v4& color) :
		Shape(pos, color)
	{
	}

	virtual void BeginDraw() override
	{
		m_Shader->Use();
		m_VertexArray->Bind();

		if (m_Texture != NULL) 
		{
			m_Texture->Bind(0);
			String name(TEXTURE_STRING);
			name.append("0");
			m_Shader->SetUniform1i(name.c_str(), 0);
		}
		else 
		{
			m_Shader->SetUniform4f(U_COLOR_STRING, m_Color);
		}
		m_Shader->SetUniformMatrix4fv(MODEL_MATRIX_STRING, m_ModelMatrix);
		m_Shader->SetUniformMatrix4fv(VIEW_MATRIX_STRING, m_ViewMatrix);
		m_Shader->SetUniformMatrix4fv(PROJECTION_MATRIX_STRING, m_ProjectionMatrix);
	}

	virtual void EndDraw() override
	{
	}

private: 
	void InitTextureCube()
	{
		//m_Mesh = Mesh::GenerateCubeWithTextureCoord();
		f32 vertices[] = {
			0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
			1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
			1.0f, 1.0f, 0.0f, 1.0f, 1.0f,
			0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
			0.0f, 1.0f, 1.0f, 0.0f, 1.0f,
			1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
			1.0f, 0.0f, 1.0f, 1.0f, 0.0f,
			0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
		};

		u32 indices[] = {
			0, 2, 1, //face front
			0, 3, 2,
			2, 3, 4, //face top
			2, 4, 5,
			1, 2, 5, //face right
			1, 5, 6,
			0, 7, 4, //face left
			0, 4, 3,
			5, 4, 7, //face back
			5, 7, 6,
			0, 6, 7, //face bottom
			0, 1, 6
		};

		BufferElement pos("Position", VertexDataType::Float3);
		BufferElement textCoord1("First texture cordinates", VertexDataType::Float2);
		BufferLayout layout(std::vector<BufferElement> { pos, textCoord1 });

		VertexBuffer* vertexBuffer = VertexBuffer::Create(vertices, ArrayCount(vertices));
		vertexBuffer->SetLayout(layout);

		m_VertexArray = VertexArray::Create();
		m_VertexArray->AddVertexBuffer(vertexBuffer);
		
		m_VertexArray->SetIndexBuffer(
			IndexBuffer::Create(indices, ArrayCount(indices))
		);
	}
};

class Sprite : public Shape
{
public:
	Sprite(f32 x, f32 y, f32 w, f32 h, Image& image) : 
		Shape(v3(x, y, 0.0f), image)
	{
		SetPosition(v3(x, y, 0.0f));
		InitVertices(x, y, w, h);
		m_Shader = new OpenGLShader(GetVertexShader(), GetFragmentShader());
	}

	virtual void BeginDraw() override
	{
		m_Shader->Use();
		m_Texture->Bind(0);
		String name(TEXTURE_STRING);
		name.append("0");
		m_Shader->SetUniform1i(name.c_str(), 0);

		m_Shader->SetUniformMatrix4fv(MODEL_MATRIX_STRING, m_ModelMatrix);
		m_Shader->SetUniformMatrix4fv(VIEW_MATRIX_STRING, m_ViewMatrix);
		m_Shader->SetUniformMatrix4fv(PROJECTION_MATRIX_STRING, m_ProjectionMatrix);
		m_VertexArray->Bind();
	}

	virtual void EndDraw() override
	{
		//...unbind...
	}

	void InitVertices(f32 x, f32 y, f32 w, f32 h)
	{
		GLfloat vertices[] =
		{
			w,    0.0f, 1.0f,	1.0f, 1.0f,	// Top Right
			w,    -h,	1.0f,	1.0f, 0.0f,	// Bottom Right
			0.0f, -h,	1.0f,	0.0f, 0.0f,	// Bottom Left
			0.0f, 0.0f, 1.0f,	0.0f, 1.0f,	// Top Left 
		};

		GLuint indices[] =
		{
			0, 1, 3,
			1, 2, 3
		};

		m_VertexArray = VertexArray::Create();

		IndexBuffer* indexBuffer = IndexBuffer::Create(indices, ArrayCount(indices));
		VertexBuffer* vertexBuffer = VertexBuffer::Create(vertices, ArrayCount(vertices));

		BufferElement pos("Position", VertexDataType::Float3);
		BufferElement textCoord1("First texture cordinates", VertexDataType::Float2);

		BufferLayout layout(std::vector<BufferElement> {pos, textCoord1 });

		vertexBuffer->SetLayout(layout);
		m_VertexArray->AddVertexBuffer(vertexBuffer);
		m_VertexArray->SetIndexBuffer(indexBuffer);
	}
};


enum class RotationKind
{
	X,
	Y,
	Z
};

class ExampleScene : public Craft::Layer
{
private:
	std::vector<Shape*> m_Shapes;

	Camera* m_PerspCamera;
	Camera* m_MainCamera;
	Camera* m_FpsCamera;

	f32 timer = 0.0f;
	RotationKind rotKind;
	std::map<RotationKind, v3> rotors;

	s32 lastX, lastY;

	Vfs* m_Vfs;

public:
	ExampleScene()
	{
		rotKind = RotationKind::X;
		rotors[RotationKind::X] = v3(1.0f, 0.0f, 0.0f);
		rotors[RotationKind::Y] = v3(0.0f, 1.0f, 0.0f);
		rotors[RotationKind::Z] = v3(0.0f, 0.0f, 1.0f);
		
		m_Vfs = new Vfs(RootSpritesFolder);

		v2 pos = Input::InputHandler::GetMousePosition();
		lastX = pos.x;
		lastY = pos.y;

		glViewport(0, 0, DEFAULT_WINDOW_WIDTH, DEFAULT_WINDOW_HEIGHT);
		InitRenderable();
	}

	~ExampleScene()
	{
		for (int i = 0; i < m_Shapes.size(); ++i) 
		{
			delete m_Shapes[i];
		}
	}

	void InitRenderable()
	{
		RenderCommand::ZTest(true);
		RenderCommand::SetClearColor(v4(0.0f, 0.1f, 0.1f, 1.0f));

		v3 cameraPos = v3(0.0f, 0.0f, -5.0f);
		v3 cameraFront = v3(0.0f, 0.0f, -1.0f);
		v3 cameraUp = v3(0.0f, 1.0f, 0.0f);

		m_FpsCamera = new FPSCamera(0.005f,
			cameraPos, cameraFront, cameraUp,
			mat4::Perspective(FOV, ASPECT_RATIO, NEAR_PLANE, FAR_PLANE));

		m_PerspCamera = Camera::CreatePerspectiveCamera(FOV, ASPECT_RATIO, NEAR_PLANE, FAR_PLANE,
					v3(0.0f, 0.0f, -5.0f), 0.01f);

		Craft::Image* smile = m_Vfs->GetImage(PathToSmileImage);
		Craft::Image* image = m_Vfs->GetImage(PathToTileSheets);
		Craft::Image* grass = m_Vfs->GetImage(PathToGrassImage);

		Sprite* m_Plane = new Sprite(-5.0f, -2.0f, 10.0f, 10.0f, *grass);
		m_Plane->SetRotation(-90.0f, v3(1.0f, 0.0f, 0.0f));

		Sprite* m_Rect = new Sprite(-4.0f, 0.0f, 1.0f, 1.0f, *smile);
		m_Rect->SetRotation(45.0f, v3(0.0f, 1.0f, 0.0f));

		Cube* m_Cube = new Cube(v3(0.0f, 0.0f, 0.0f), *image);
		m_Cube->SetRotation(55.0f, v3(0.0f, 0.0f, 1.0f));

		Cube* m_Cube1 = new Cube(v3(1.0f, -1.0f, 0.0f), *smile);
		m_Cube1->SetRotation(24.0f, v3(0.0f, 0.0f, 1.0f));

		Cube* m_Cube2 = new Cube(v3(3.0f, 1.0f, 0.0f), *smile);

		m_Shapes = { 
			m_Plane, 
			m_Rect,
			m_Cube, 
			m_Cube1,
			m_Cube2 
		};

		m_MainCamera = m_FpsCamera;

		delete smile;
		delete grass;
		delete image;
	}

	virtual void OnRender() override
	{
		RenderCommand::Clear();
		Renderer::BeginScene(*m_MainCamera);

		for (Shape* shape : m_Shapes) {
			Renderer::Submit(*shape);
		}
	}

	virtual void OnEvent(Craft::Event& event) override
	{
		Craft::EventDispatcher dispatcher(event);
		dispatcher.Dispatch<Craft::MouseMovedEvent>(BIND_EVENT_FN(ExampleScene::OnMouseMove));
		dispatcher.Dispatch<Craft::WindowResizeEvent>(BIND_EVENT_FN(ExampleScene::OnResizeWindow));
		dispatcher.Dispatch<Craft::KeyPressedEvent>(BIND_EVENT_FN(ExampleScene::OnKeyDown));
	}

	virtual void OnUpdate(f32 deltaTime) override
	{
		UpdataSettings();
		UpdataCamera(deltaTime);
		UpdataShapes(deltaTime);
	}

	void UpdataSettings() 
	{
		if (Input::InputHandler::IsKeyPressed('1'))
		{
			rotKind = RotationKind::X;
		} 
		else if (Input::InputHandler::IsKeyPressed('2'))
		{
			rotKind = RotationKind::Y;
		} 
		else if (Input::InputHandler::IsKeyPressed('3'))
		{
			rotKind = RotationKind::Z;
		}
	}

	void UpdataShapes(f32 deltaTime)
	{
		timer += deltaTime;
		m_Shapes[2]->SetRotation(timer / 20.0f, v3(1.0f, 0.0f, 0.0f));
	}

	void UpdataCamera(f32 deltaTime)
	{
		UpdateCameraMove(deltaTime);
		UpdateCameraRotation(deltaTime, m_MainCamera->GetRotation(), rotors[rotKind]);
	}

	void UpdateCameraMove(f32 dt) 
	{
		if (Input::InputHandler::IsKeyPressed('W'))
		{
			m_MainCamera->Move(MoveDirection::Up, dt);
		}
		if (Input::InputHandler::IsKeyPressed('S'))
		{
			m_MainCamera->Move(MoveDirection::Down, dt);
		}

		if (Input::InputHandler::IsKeyPressed('A'))
		{
			m_MainCamera->Move(MoveDirection::Left, dt);
		}
		if (Input::InputHandler::IsKeyPressed('D'))
		{
			m_MainCamera->Move(MoveDirection::Right, dt);
		}
	}

	void UpdateCameraRotation(f32 dt, f32 angle, v3& axis)
	{
		if (Input::InputHandler::IsKeyPressed('Q'))
		{
			m_MainCamera->SetRotation(angle + 1, axis);
		}
		if (Input::InputHandler::IsKeyPressed('E'))
		{
			m_MainCamera->SetRotation(angle - 1, axis);
		}
	}

private:
	bool OnKeyDown(Craft::KeyPressedEvent& event)
	{
		if (event.GetKeyCode() == VK_F2)
		{
			ChangeCamera();
			return true;
		}

		if (event.GetKeyCode() == VK_ESCAPE)
		{		
			exit(1);
		}

		return false;
	}

	bool OnMouseMove(Craft::MouseMovedEvent& e)
	{
		s32 offsetX = lastX - e.x;
		s32 offsetY = lastY - e.y;
		return true;
	}

	bool OnResizeWindow(Craft::WindowResizeEvent& event)
	{
		glViewport(0, 0, event.GetWidth(), event.GetHeight());
		return true;
	}

	void ChangeCamera()
	{
		CR_INFO("Toogle camera type");
		m_MainCamera = m_MainCamera == m_FpsCamera ? m_PerspCamera : m_FpsCamera;
	}
};

#define CRAFT_MATH_TEST

void MathTest()
{
#ifndef CRAFT_MATH_TEST
	Craft::v3 a{ 1,2,3 };
	Craft::v3 b{ 1,2,3 };
	Craft::v3 c = a + b;
	std::cout << "A:			" << a << std::endl;
	std::cout << "B:			" << b << std::endl;
	std::cout << "Dot a*b:		" << Dot(a, b)		<< std::endl;
	std::cout << "Cross a^b:	" << Cross(a, b)	<< std::endl;
	std::cout << "Scalar a+10:	" << (a + 10.0f)	<< std::endl;
	std::cout << "c = a + b:	" << (a + b)		<< std::endl;
	std::cout << "Length(c):	" << Length(c)		<< std::endl;
	std::cout << "Normalize(c):	" << Normalize(c)	<< std::endl;

	mat4 mat0 = mat4::Identity(1.0);
	mat4 mat1 = mat4::Identity(2.0);
	mat4 mat2 = mat0 + mat1;
	mat4 mat3 = mat0 * mat2;

	std::cout << "math: " << "\n" << mat2 << std::endl;
	std::cout << "m0*m1: " << "\n" << mat3 << std::endl;
#endif
}

class Sandbox : public Craft::Application
{
public:
	Sandbox(f32 fps, Craft::WindowSetting setting) : Application(fps, setting)
	{
		MathTest();
		PushLayer(new ExampleScene());
	}

	virtual ~Sandbox()
	{
	}
};

Craft::Application* Craft::CreateApplication()
{
	WindowSetting setting;
	setting.IsVSync = false;
	return new Sandbox(60.0f, setting);
}
