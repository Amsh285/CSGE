#include <iostream>

#include <string>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Renderer.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"

#include "infrastructure/MathHelper.h"
#include "data/Matrix4x4f.h"

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

int width = 1024;
int height = 768;

void resize(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);

	// Wechsel auf den Projektionsmatrix- stack
	glMatrixMode(GL_PROJECTION);

	// Initialisieren mit der Einheitsmatrix
	glLoadIdentity();

	// Wieder auf den Modelview stack wechseln
	glMatrixMode(GL_MODELVIEW);
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

void LoadShaders()
{
	Shader vertexShader = Shader::LoadFromFile("src/vertexshader.txt", GL_VERTEX_SHADER, "vertexshader");
	Shader fragmentShader = Shader::LoadFromFile("src/fragmentshader.txt", GL_FRAGMENT_SHADER, "fragmentshader");

	g_Shaders.push_back(vertexShader);
	g_Shaders.push_back(fragmentShader);
}

void BuildGeometries()
{
	Quad testQuad;
	testQuad.Transform().Position() = Vector3f(10.0f, -10.0f, -50.0f);
	testQuad.Transform().Rotation() = Vector3f(0.0f, 45.0f, 0.0f);
	testQuad.Transform().Scale() = Vector3f(5.0f, 5.0f, 5.0f);

	quads.push_back(testQuad);

	Quad quad2;
	quad2.Transform().Position() = Vector3f(-5.0f, 5.0f, -50.0f);
	quad2.Transform().Rotation() = Vector3f(0.0f, -45.0f, 0.0f);
	quad2.Transform().Scale() = Vector3f(5.0f, 5.0f, 5.0f);

	quads.push_back(quad2);

	Quad quad3;
	quad3.Transform().Position() = Vector3f(-5.0f, -5.0f, -50.0f);
	quad3.Transform().Rotation() = Vector3f(0.0f, -45.0f, 0.0f);
	quad3.Transform().Scale() = Vector3f(5.0f, 5.0f, 5.0f);

	quads.push_back(quad3);

	Quad quad4;
	quad4.Transform().Position() = Vector3f(-15.0f, -5.0f, -50.0f);
	quad4.Transform().Rotation() = Vector3f(45.0f, 0.0f, 0.0f);
	quad4.Transform().Scale() = Vector3f(5.0f, 20.0f, 5.0f);

	quads.push_back(quad4);
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

	ShaderProgram shaderProgram(g_Shaders);
	shaderProgram.Build();
	shaderProgram.Bind();

	Matrix4x4f perspective = Matrix4x4f::Perspective(45.0f, width / height, 0.1f, 100.0f);
	std::vector<float> mvp = perspective.GetOpenGlRepresentation();

	Matrix4x4f transformations = quad.Transform().GetTransformationMatrix();
	std::vector<float> transform = transformations.GetOpenGlRepresentation();

	shaderProgram.SetUniformMat4f("u_MVP", &mvp[0]);
	shaderProgram.SetUniformMat4f("u_Transform", &transform[0]);

	shaderProgram.Unbind();

	return { va, indexBuffer, shaderProgram };
}

void ExecuteWindow(GLFWwindow* window)
{
	init(window, width, height);

	Renderer renderer;

	std::vector<RenderingContext> contexts;

	for (size_t i = 0; i < quads.size(); i++)
		contexts.push_back(GetRenderingContext(quads[i]));
	/*contexts.push_back(testQuadContext);*/

	/*contexts.push_back(GetRenderingContext(quads[0]));*/

	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		processInput(window);

		/* Render here */
		renderer.Clear();
		/*renderer.Draw(square);*/

		for (size_t i = 0; i < contexts.size(); i++)
			renderer.Draw(contexts[i]);

		/* Swap front and back buffers */
		glfwSwapBuffers(window);
		/* Poll for and process events */
		glfwPollEvents();
	}

	delete quadSet;
}

int main(void)
{
	LoadVertexSets();
	LoadShaders();
	BuildGeometries();

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