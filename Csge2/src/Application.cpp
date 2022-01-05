#include <iostream>

#include <string>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Renderer.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"

#include "infrastructure/MathHelper.h"
#include "infrastructure/Matrix4x4f.h"

#include "Utility.h"

#include "RenderingContext.h"
#include "Shader.h"
#include "ShaderProgram.h"
#include "VertexArray.h"
#include "VertexBufferLayout.h"

std::vector<std::unique_ptr<Shader>> g_Shaders;

int width = 1024;
int height = 768;

void resize(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);

	// Wechsel auf den Projektionsmatrix- stack
	glMatrixMode(GL_PROJECTION);

	// Initialisieren mit der Einheitsmatrix
	glLoadIdentity();

	// Anpassung des Frustum an den neuen Aspect ratio von Resize(width, height)
	/*gluPerspective(45.0f, (GLfloat)width / (GLfloat)height, 0.1f, 150.0f);*/

	// Wieder auf den Modelview stack wechseln
	glMatrixMode(GL_MODELVIEW);
}

void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

void LoadShaders()
{
	Shader* vertexShader = Shader::LoadFromFile("src/vertexshader.txt", GL_VERTEX_SHADER, "vertexshader");
	Shader* fragmentShader = Shader::LoadFromFile("src/fragmentshader.txt", GL_FRAGMENT_SHADER, "fragmentshader");

	g_Shaders.push_back(std::unique_ptr<Shader>(vertexShader));
	g_Shaders.push_back(std::unique_ptr<Shader>(fragmentShader));
}

void init(GLFWwindow* window, int width, int height)
{
	if (height == 0)
		height = 1;

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

void ExecuteWindow(GLFWwindow* window)
{
	init(window, width, height);

	Renderer renderer;

	//float vertexData[] = {
	//	-0.5f, -0.5f, -0.5f,	1.0f, 0.0f, 0.0f, 1.0f, //0
	//	0.5f, -0.5f, -0.5f,		0.0f, 0.0f, 1.0f, 1.0f, // 1
	//	0.5f, 0.5f, -0.5f,		0.0f, 0.0f, 1.0f, 1.0f, // 2
	//	-0.5f, 0.5f, -0.5f,		1.0f, 1.0f, 1.0f, 1.0f // 3
	//};

	float vertexData[] = {
		-7.0f, -1.0f, -50.0f,		1.0f, 0.0f, 0.0f, 1.0f, //0
		-5.0f, -1.0f, -50.0f,		0.0f, 0.0f, 1.0f, 1.0f, // 1
		-5.0f, 1.0f, -50.0f,		0.0f, 0.0f, 1.0f, 1.0f, // 2
		-7.0f, 1.0f, -50.0f,		1.0f, 1.0f, 1.0f, 1.0f // 3

		- 5.0f, -1.0f, -52.0f,		0.0f, 0.0f, 1.0f, 1.0f // 4
	};

	unsigned int indices[] = {
		0, 1, 2,
		2, 3, 0,

		1, 4, 2
	};

	unsigned int vao;
	GLCall(glGenVertexArrays(1, &vao));
	GLCall(glBindVertexArray(vao));

	VertexArray va;
	VertexBuffer vb(vertexData, 4 * 2 * 4 * sizeof(float));
	VertexBufferLayout layout;
	layout.Push<float>(3);
	layout.Push<float>(4);
	va.AddBuffer(vb, layout);

	IndexBuffer ib(indices, 6);

	ShaderProgram shaderProgram(g_Shaders);
	shaderProgram.Build();

	shaderProgram.Bind();

	Matrix4x4f perspective = Matrix4x4f::Perspective(45.0f, width / height, 0.1f, 100.0f);
	std::vector<float> mvp = perspective.GetOpenGlRepresentation();

	Matrix4x4f translation = Matrix4x4f::Translate(5.0f, .0f, 30.0f);
	std::vector<float> transform = translation.GetOpenGlRepresentation();

	shaderProgram.SetUniformMat4f("u_MVP", &mvp[0]);
	shaderProgram.SetUniformMat4f("u_Transform", &transform[0]);


	shaderProgram.Unbind();

	RenderingContext squarePart1(va, ib, shaderProgram);

	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		processInput(window);

		/* Render here */
		renderer.Clear();
		renderer.Draw(squarePart1);

		/* Swap front and back buffers */
		glfwSwapBuffers(window);
		/* Poll for and process events */
		glfwPollEvents();
	}
}

int main(void)
{
	LoadShaders();

	GLFWwindow* window;

	/* Initialize the library */
	if (!glfwInit())
		return -1;

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(width, height, "Hello World", NULL, NULL);

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

	glViewport(0, 0, width, height);
	glfwSetFramebufferSizeCallback(window, resize);

	ExecuteWindow(window);

	glfwTerminate();
	return 0;
}