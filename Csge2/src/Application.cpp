#include <iostream>

#include <string>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Renderer.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"

#include "Utility.h"

#include "RenderingContext.h"
#include "Shader.h"
#include "ShaderProgram.h"
#include "VertexArray.h"
#include "VertexBufferLayout.h"

std::vector<std::unique_ptr<Shader>> g_Shaders;

int width = 800;
int height = 600;

void resize(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
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

void ExecuteWindow(GLFWwindow* window)
{
	Renderer renderer;

	float vertexData[] = {
		-0.5f, -0.5f,	1.0f, 0.0f, 0.0f, 1.0f, //0
		0.5f, -0.5f,	0.0f, 0.0f, 1.0f, 1.0f, // 1
		0.5f, 0.5f,		0.0f, 0.0f, 1.0f, 1.0f, // 2
		-0.5f, 0.5f,	1.0f, 1.0f, 1.0f, 1.0f // 3
	};

	unsigned int indices[] = {
		0, 1, 2,
		2, 3, 0
	};

	unsigned int vao;
	GLCall(glGenVertexArrays(1, &vao));
	GLCall(glBindVertexArray(vao));

	VertexArray va;
	VertexBuffer vb(vertexData, 4 * 2 * 4 * sizeof(float));
	VertexBufferLayout layout;
	layout.Push<float>(2);
	layout.Push<float>(4);
	va.AddBuffer(vb, layout);

	IndexBuffer ib(indices, 6);

	ShaderProgram shaderProgram(g_Shaders);
	shaderProgram.Build();

	RenderingContext square(va, ib, shaderProgram);

	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		processInput(window);

		/* Render here */
		
		renderer.Clear();
		renderer.Draw(square);

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