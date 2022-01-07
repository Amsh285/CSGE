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

#include "Utility.h"

#include "RenderingContext.h"
#include "Shader.h"
#include "ShaderProgram.h"
#include "VertexArray.h"
#include "VertexBufferLayout.h"

#include "geometry/Quad.h"

std::vector<Quad> quads;

IndexedVertexSet* quadSet;

std::vector<Shader> g_Shaders;

std::map<std::string, ShaderProgram*> g_ShaderPrograms;
std::map<std::string, Texture*> g_textures;

Matrix4x4f g_mvp;

int g_width = 1024;
int g_height = 768;
//
//void ErrorCallback(int error_code, const char* description)
//{
//	std::cout << "Error: Code: " << error_code << " - " << description << std::endl;
//}
//
void LoadMvp()
{
	g_mvp = Matrix4x4f::Perspective(45.0f, (float)g_width / g_height, 0.1f, 100.0f);
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

void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
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
	quad1.Transform().Position() = Vector3f(10.0f, -10.0f, -50.0f);
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
	quad3.Transform().Rotation() = Vector3f(0.0f, -45.0f, 0.0f);
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
		processInput(window);

		/* Render here */
		renderer.Clear();
		renderer.SetPerspective(g_mvp);

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

	ExecuteWindow(window);

	/*glfwSetErrorCallback(ErrorCallback);*/
	
	glfwTerminate();

	return 0;
}
