#include <iostream>

#include <map>
#include <string>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Renderer.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"

#include "infrastructure/MathHelper.h"
#include "data/Matrix4x4f.h"
#include "data/Texture.h"
#include "scene/Camera.h"
#include "ui/MousePosition.h"

#include "Utility.h"

#include "RenderingContext.h"
#include "Shader.h"
#include "ShaderProgram.h"
#include "VertexArray.h"
#include "VertexBufferLayout.h"

#include "geometry/Quad.h"

#include "data/Matrix3x3f.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

Camera tfc;

std::vector<Quad> quads;

IndexedVertexSet* quadSet;

std::vector<Shader> g_Shaders;

std::map<std::string, ShaderProgram*> g_ShaderPrograms;
std::map<std::string, Texture*> g_textures;

Matrix4x4f g_mvp;
glm::mat4 g_mvp_glm;

int g_width = 1024;
int g_height = 768;

MousePosition mouseDown, mouseUp;

const std::pair<float, float> thresholdDeltaY(30.0f, -30.0f);
const std::pair<float, float> thresholdDeltaX(30.0f, -30.0f);

void LoadMvp()
{
	g_mvp = Matrix4x4f::Perspective(45.0f, (float)g_width / g_height, 0.1f, 150.0f);
	g_mvp_glm = glm::perspective(45.0f, (float)g_width / g_height, 0.1f, 150.0f);
}

void resize(GLFWwindow* window, int width, int height)
{
	if (height == 0)
		height = 1;

	g_width = width;
	g_height = height;

	glViewport(0, 0, width, height);
	LoadMvp();
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
	else if (key == 89 && action == GLFW_PRESS)
		tfc.Reset();
	else if (key == GLFW_KEY_W && action == GLFW_PRESS)
	{
		Vector3f newPosition = tfc.GetPosition() + tfc.GetDirection();
		tfc.SetPosition(newPosition);

		Vector3f pos = tfc.GetPosition();
		Vector3f dir = tfc.GetDirection();

		std::cout << "direction: x" << dir.X() << " y: " << dir.Y() << " z: " << dir.Y() << std::endl;
		std::cout << "newPosition: x: " << pos.X() << " y: " << pos.Y() << " z: " << pos.Z() << std::endl;
	}
	else if (key == GLFW_KEY_S && action == GLFW_PRESS)
	{
		Vector3f direction = tfc.GetDirection();
		Vector3f position = tfc.GetPosition();
		Vector3f backwards = position - direction;
		tfc.SetPosition(backwards);
	}
	else if (key == GLFW_KEY_D && action == GLFW_PRESS)
	{

	}
	else if (key == GLFW_KEY_A && action == GLFW_PRESS)
	{
	}
}

void OnMouseButtonLeftUp(const MousePosition& down, const MousePosition& up)
{
	int deltaY = up.X - down.X;
	int deltaX = down.Y - up.Y;

	bool insideYThreshold = deltaY <= thresholdDeltaY.first && deltaY >= thresholdDeltaY.second;
	bool insideXThreshold = deltaX <= thresholdDeltaX.first && deltaX >= thresholdDeltaX.second;

	if (insideYThreshold)
		deltaY = 0;

	if (insideXThreshold)
		deltaX = 0;

	float ratioY = g_width / 90;
	float ratioX = g_height / 60;

	float angleY = std::fmod(tfc.GetRotationAngleY() + deltaY / ratioY, 360.0f);
	std::cout << "angleY: " << angleY << std::endl;
	float angleX = tfc.GetRotationAngleX() + deltaX / ratioX;

	if (angleX > 89.0f)
		angleX = 89.0f;
	else if (angleX < -89.0f)
		angleX = -89.0f;

	std::cout << "Pitch: " << std::to_string(angleX) << " - Yaw: " << std::to_string(angleY) << std::endl;
	tfc.SetAngles(angleX, angleY);

	Vector3f direction = tfc.GetDirection();

	std::cout << "Camera direction x: " << direction.X() << " y: " << direction.Y() << " z: " << direction.Z() << std::endl;
}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
	if (button == GLFW_MOUSE_BUTTON_1)
	{
		if (action == GLFW_PRESS)
			glfwGetCursorPos(window, &mouseDown.X, &mouseDown.Y);
		else if (action == GLFW_RELEASE)
		{
			glfwGetCursorPos(window, &mouseUp.X, &mouseUp.Y);
			OnMouseButtonLeftUp(mouseDown, mouseUp);
		}
	}
}

void LoadVertexSets()
{
	quadSet = Quad::GetVertices();
}

void LoadTextures()
{
	g_textures["wall"] = new Texture("Assets/wall.jpg");
	g_textures["badgers"] = new Texture("Assets/Badgers.jpg");
	g_textures["texarray"] = new Texture("Assets/texturesArray.png");
	g_textures["awesomeface"] = new Texture("Assets/awesomeface.png");
}

void LoadShaders()
{
	Shader vertexShader = Shader::LoadFromFile(
		"src/shaders/vertexshaders/vertexshader.shader",
		GL_VERTEX_SHADER,
		"vertexshader"
	);
	vertexShader.Compile();

	Shader textureColorMultiplyFragmentShader = Shader::LoadFromFile(
		"src/shaders/fragmentshaders/texture_color_multiplyfragmenshader.shader",
		GL_FRAGMENT_SHADER,
		"texture_color_multiplyfragmenshader"
	);
	textureColorMultiplyFragmentShader.Compile();

	Shader vertexColorFragmentShader = Shader::LoadFromFile(
		"src/shaders/fragmentshaders/vertexcolor_fragmentshader.shader",
		GL_FRAGMENT_SHADER,
		"vertexcolor_fragmentshader"
	);
	vertexColorFragmentShader.Compile();

	g_Shaders.push_back(vertexShader);
	g_Shaders.push_back(textureColorMultiplyFragmentShader);
	g_Shaders.push_back(vertexColorFragmentShader);

	g_ShaderPrograms["texcolmultiply"] = new ShaderProgram({ vertexShader, textureColorMultiplyFragmentShader });
	g_ShaderPrograms["texcolmultiply"]->Build();

	g_ShaderPrograms["default"] = new ShaderProgram({ vertexShader, vertexColorFragmentShader });
	g_ShaderPrograms["default"]->Build();
}

void BuildGeometries()
{
	Quad quad1;
	quad1.Transform().Position() = Vector3f(15.0f, -10.0f, -50.0f);
	quad1.Transform().Rotation() = Vector3f(0.0f, 0.0f, 0.0f);
	quad1.Transform().Scale() = Vector3f(5.0f, 5.0f, 5.0f);

	quads.push_back(quad1);

	Quad quad2;
	quad2.Transform().Position() = Vector3f(-5.0f, 5.0f, -50.0f);
	quad2.Transform().Rotation() = Vector3f(0.0f, -45.0f, 0.0f);
	quad2.Transform().Scale() = Vector3f(5.0f, 5.0f, 5.0f);
	quad2.UseTexture("badgers", "texcolmultiply");

	quads.push_back(quad2);

	Quad quad3;
	quad3.Transform().Position() = Vector3f(-5.0f, -5.0f, -50.0f);
	quad3.Transform().Rotation() = Vector3f(0.0f, 45.0f, 0.0f);
	quad3.Transform().Scale() = Vector3f(5.0f, 5.0f, 5.0f);
	quad3.UseTexture("texarray", "texcolmultiply");

	quads.push_back(quad3);

	Quad quad4;
	quad4.Transform().Position() = Vector3f(-15.0f, -5.0f, -50.0f);
	quad4.Transform().Rotation() = Vector3f(45.0f, 0.0f, 0.0f);
	quad4.Transform().Scale() = Vector3f(5.0f, 20.0f, 5.0f);
	quad4.UseTexture("awesomeface", "texcolmultiply");

	quads.push_back(quad4);
}

void init(GLFWwindow* window, int width, int height)
{
	if (height == 0)
		g_height = 1;

	// Farbe mit der das bild bereinigt wird
	GLCall(glClearColor(0.3f, 0.3f, 0.3f, 0.0f));

	//initiale tiefenwerte für den z- buffer 1.0 wegen einheitswürfel?
	GLCall(glClearDepth(1.0));
	/*gluPerspective(,)*/

	//wenn ein eingehender tiefenwert kleiner als der wert an der entsprechenden stelle des z-buffers ist wird überschrieben
	//und die farbe im frame buffer an der entsprechenden stelle übernommen
	GLCall(glDepthFunc(GL_LESS));
	GLCall(glEnable(GL_DEPTH_TEST));
	GLCall(glShadeModel(GL_SMOOTH));
	resize(window, width, height);
}

RenderingContext GetRenderingContext(Quad& quad)
{
	VertexArray va;

	std::vector<float> v_VertexData;

	std::vector<Vertex>& testQuadvertices = quadSet->GetVertices();
	std::vector<unsigned int>& testQuadindices = quadSet->GetIndices();

	for (size_t i = 0; i < testQuadvertices.size(); i++)
	{
		Vertex& current = testQuadvertices.at(i);
		std::vector<float> buffer = current.GetVertexBuffer();

		v_VertexData.insert(v_VertexData.end(), buffer.begin(), buffer.end());
	}

	VertexBuffer vb(&v_VertexData[0], v_VertexData.size() * sizeof(float));

	VertexBufferLayout layout;
	layout.Push<float>(3);
	layout.Push<float>(4);
	layout.Push<float>(2);

	va.AddBuffer(vb, layout);

	IndexBuffer indexBuffer(&testQuadindices[0], testQuadindices.size());
	return { quad, va, indexBuffer, vb, *g_ShaderPrograms[quad.GetShaderProgram()]};
}

void ExecuteWindow(GLFWwindow* window)
{
	init(window, g_width, g_height);

	LoadTextures();
	LoadShaders();

	Renderer renderer;
	std::vector<RenderingContext> contexts;

	for (auto it = quads.begin(); it != quads.end(); ++it)
		contexts.push_back(GetRenderingContext(*it));

	while (!glfwWindowShouldClose(window))
	{
		/* Render here */
		renderer.Clear();

		// https://www.youtube.com/watch?v=mpTl003EXCY&t=2s&ab_channel=UCDavisAcademics
		Vector3f direction = tfc.GetPosition() + tfc.GetDirection();
		Vector3f position = tfc.GetPosition();
		Matrix4x4f cameraProjection = Matrix4x4f::LookAt(position, direction, Vector3f::Up());;

		glm::mat4 matCam_glm = glm::lookAt(glm::vec3(position.X(), position.Y(), position.Z()), glm::vec3(direction.X(), direction.Y(), direction.Z()), glm::vec3(0.0f, 1.0f, 0.0f));

		Matrix4x4f projection = g_mvp * cameraProjection;
		glm::mat4 projection_glm = g_mvp_glm * matCam_glm;

		renderer.SetPerspective(projection);
		renderer.SetPerspectivef(&projection_glm[0][0]);

		for (auto it = contexts.begin(); it != contexts.end(); ++it)
			renderer.Draw(*it, g_textures);

		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();
	}

	//Todo: proper cleanup

	delete quadSet;

	for (auto it = g_textures.begin(); it != g_textures.end(); ++it)
		delete it->second;

	for (auto it = g_Shaders.begin(); it != g_Shaders.end(); ++it)
		it->DeleteShader();

	for (auto it = g_ShaderPrograms.begin(); it != g_ShaderPrograms.end(); ++it)
	{
		it->second->DeleteProgram();
		delete it->second;
	}
}

int main(void)
{
	LoadMvp();
	LoadVertexSets();
	BuildGeometries();

	GLFWwindow* window;

	/* Initialize the library */
	if (!glfwInit())
		return -1;

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(g_width, g_height, "Hello World", NULL, NULL);

	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);

	if (glewInit() != GLEW_OK)
	{
		std::cout << "error initializing glew." << std::endl;
		return -1;
	}

	glfwSetFramebufferSizeCallback(window, resize);
	glfwSetKeyCallback(window, key_callback);
	glfwSetMouseButtonCallback(window, mouse_button_callback);

	ExecuteWindow(window);
	glfwTerminate();

	return 0;
}
