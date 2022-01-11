#include <iostream>

#include <map>
#include <string>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Renderer.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"

#include "infrastructure/DeltaTime.h"
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
#include "geometry/Triangle.h"

#include "data/Matrix3x3f.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

DeltaTime delta_time;
Camera tfc;

std::vector<Quad*> g_quads;

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

std::vector<Triangle> windowTriangles;
std::vector<float> windowVertices;

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
		Vector3f backwards = tfc.GetPosition() - tfc.GetDirection();
		tfc.SetPosition(backwards);
	}
	else if (key == GLFW_KEY_D && action == GLFW_PRESS)
	{
		/*tfc.SetPosition(tfc.GetPosition() + Vector3f(1.0f, 0.0f, 0.0f));*/
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
	/*quadSet = Quad::GetVertices();*/
	quadSet = Quad::GetVertices24();
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
	Quad* quad1 = new Quad();
	quad1->Transform().Position() = Vector3f(15.0f, -10.0f, -50.0f);
	quad1->Transform().Rotation() = Vector3f(0.0f, 0.0f, 0.0f);
	quad1->Transform().Scale() = Vector3f(5.0f, 5.0f, 5.0f);

	g_quads.push_back(quad1);

	Quad* quad2 = new Quad();
	quad2->Transform().Position() = Vector3f(-5.0f, 5.0f, -50.0f);
	quad2->Transform().Rotation() = Vector3f(0.0f, 0.0f, 0.0f);
	quad2->Transform().Scale() = Vector3f(5.0f, 5.0f, 5.0f);
	quad2->UseTexture("badgers", "texcolmultiply");

	g_quads.push_back(quad2);

	Quad* quad3 = new Quad();
	quad3->Transform().Position() = Vector3f(-5.0f, -5.0f, -50.0f);
	quad3->Transform().Rotation() = Vector3f(0.0f, 90.0f, 0.0f);
	quad3->Transform().Scale() = Vector3f(5.0f, 5.0f, 5.0f);
	quad3->UseTexture("texarray", "texcolmultiply");

	g_quads.push_back(quad3);

	Quad* quad4 = new Quad();
	quad4->Transform().Position() = Vector3f(-15.0f, -5.0f, -50.0f);
	quad4->Transform().Rotation() = Vector3f(45.0f, 0.0f, 0.0f);
	quad4->Transform().Scale() = Vector3f(5.0f, 20.0f, 5.0f);
	quad4->UseTexture("awesomeface", "texcolmultiply");

	g_quads.push_back(quad4);
}

int comparer(const void* a, const void* b)
{
	Vector3f pos = tfc.GetPosition();
	glm::vec3 cameraPosition(pos.X(), pos.Y(), pos.Z());

	glm::vec3 centroidA = (*(Triangle*)a).GetCentroid();
	glm::vec3 centroidB = (*(Triangle*)b).GetCentroid();

	float lengthA = glm::length(cameraPosition - centroidA);
	float lengthB = glm::length(cameraPosition - centroidB);

	return lengthB - lengthA;
}

std::vector<float> GetWindowVertices(const glm::vec3& cameraPosition)
{
	std::vector<float> vertices;

	std::qsort(windowTriangles.data(), windowTriangles.size(), sizeof(Triangle), comparer);

	for (size_t i = 0; i < windowTriangles.size(); i++)
	{
		Triangle& current = windowTriangles.at(i);

		vertices.push_back(current.p1.x); vertices.push_back(current.p1.y); vertices.push_back(current.p1.z);
		vertices.push_back(current.c1.r); vertices.push_back(current.c1.g); vertices.push_back(current.c1.b); vertices.push_back(current.c1.a);
		vertices.push_back(current.tx1.x); vertices.push_back(current.tx1.y);

		vertices.push_back(current.p2.x); vertices.push_back(current.p2.y); vertices.push_back(current.p2.z);
		vertices.push_back(current.c2.r); vertices.push_back(current.c2.g); vertices.push_back(current.c2.b); vertices.push_back(current.c2.a);
		vertices.push_back(current.tx2.x); vertices.push_back(current.tx2.y);

		vertices.push_back(current.p3.x); vertices.push_back(current.p3.y); vertices.push_back(current.p3.z);
		vertices.push_back(current.c3.r); vertices.push_back(current.c3.g); vertices.push_back(current.c3.b); vertices.push_back(current.c3.a);
		vertices.push_back(current.tx3.x); vertices.push_back(current.tx3.y);
	}

	return vertices;
}

void BuildWindows()
{
	Triangle t1(
		glm::vec3(-20.0f, -20.0f, -10.0f), glm::vec3(20.0f, -20.0f, -10.0f), glm::vec3(20.0f, 20.0f, -10.0f),
		glm::vec4(1.0f, 0.0f, 0.0f, 0.4f), glm::vec4(1.0f, 0.0f, 0.0f, 0.4f), glm::vec4(1.0f, 0.0f, 0.0f, 0.4f),
		glm::vec2(0.0f, 0.0f), glm::vec2(0.0f, 0.0f), glm::vec2(0.0f, 0.0f)
	);
	t1.SetTag("t1");

	Triangle t2(
		glm::vec3(20.0f, 20.0f, -10.0f), glm::vec3(-20.0f, 20.0f, -10.0f), glm::vec3(-20.0f, -20.0f, -10.0f),
		glm::vec4(0.0f, 1.0f, 0.0f, 0.4f), glm::vec4(0.0f, 1.0f, 0.0f, 0.4f), glm::vec4(0.0f, 1.0f, 0.0f, 0.4f),
		glm::vec2(0.0f, 0.0f), glm::vec2(0.0f, 0.0f), glm::vec2(0.0f, 0.0f)
	);
	t2.SetTag("t2");

	Triangle t3(
		glm::vec3(-20.0f, -20.0f, -20.0f), glm::vec3(20.0f, -20.0f, -20.0f), glm::vec3(20.0f, 20.0f, -20.0f),
		glm::vec4(0.0f, 0.0f, 1.0f, 0.4f), glm::vec4(0.0f, 0.0f, 1.0f, 0.4f), glm::vec4(0.0f, 0.0f, 1.0f, 0.4f),
		glm::vec2(0.0f, 0.0f), glm::vec2(0.0f, 0.0f), glm::vec2(0.0f, 0.0f)
	);
	t3.SetTag("t3");

	Triangle t4(
		glm::vec3(20.0f, 20.0f, -20.0f), glm::vec3(-20.0f, 20.0f, -20.0f), glm::vec3(-20.0f, -20.0f, -20.0f),
		glm::vec4(0.0f, 0.0f, 1.0f, 0.4f), glm::vec4(0.0f, 0.0f, 1.0f, 0.4f), glm::vec4(0.0f, 0.0f, 1.0f, 0.4f),
		glm::vec2(0.0f, 0.0f), glm::vec2(0.0f, 0.0f), glm::vec2(0.0f, 0.0f)
	);
	t4.SetTag("t4");

	windowTriangles.push_back(t4);
	windowTriangles.push_back(t3);
	windowTriangles.push_back(t2);
	windowTriangles.push_back(t1);

	//windowVertices = {
	//	/*positions */				/*colors*/						/*tex coords: wont use*/
	//	-20.0f, -20.0f, -10.0f		, 1.0f, 0.0f, 0.0, 0.4f,		0.0f, 0.0f,
	//	20.0f, -20.0f, -10.0f		, 1.0f, 0.0f, 0.0, 0.4f,		0.0f, 0.0f,
	//	20.0f, 20.0f, -10.0f		, 1.0f, 0.0f, 0.0, 0.4f,		0.0f, 0.0f,

	//	20.0f, 20.0f, -10.0f		, 0.0f, 1.0f, 0.0, 0.4f,		0.0f, 0.0f,
	//	-20.0f, 20.0f, -10.0f		, 0.0f, 1.0f, 0.0, 0.4f,		0.0f, 0.0f,
	//	-20.0f, -20.0f, -10.0f		, 0.0f, 1.0f, 0.0, 0.4f,		0.0f, 0.0f
	//};

	/*To make blending work for multiple objects we have to draw the most distant object first
	and the closest object last.*/
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

RenderingContext GetRenderingContext(Quad* quad)
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
	return { quad, va, indexBuffer, vb, *g_ShaderPrograms[quad->GetShaderProgram()]};
}

void Animations()
{
	TimeStep delta = delta_time.GetStepForCurrentFrame();
	float addRotation = -45.0f * delta;

	Quad* badger = g_quads.at(1);
	Vector3f bRotation = badger->Transform().Rotation();
	float newRotationX = std::fmod(bRotation.X() + addRotation, 360.0f);
	badger->Transform().Rotation().X() = newRotationX;

	Quad* texcolMult = g_quads.at(2);
	Vector3f txRotation = texcolMult->Transform().Rotation();
	float newRotationY = std::fmod(txRotation.Y() + addRotation, 360.0f);
	texcolMult->Transform().Rotation().Y() = newRotationY;
}

void ExecuteWindow(GLFWwindow* window)
{
	init(window, g_width, g_height);

	LoadTextures();
	LoadShaders();

#pragma region blending refactor
	Vector3f cameraPosition = tfc.GetPosition();
	std::vector<float> wv = GetWindowVertices(glm::vec3(cameraPosition.X(), cameraPosition.Y(), cameraPosition.Z()));

	VertexArray vaWindow;
	VertexBuffer vbWindow(&wv[0], wv.size() * sizeof(float));
	VertexBufferLayout vbLayoutWindow;
	vbLayoutWindow.Push<float>(3);
	vbLayoutWindow.Push<float>(4);
	vbLayoutWindow.Push<float>(2);
#pragma endregion

	Renderer renderer;
	std::vector<RenderingContext> contexts;

	for (size_t i = 0; i < g_quads.size(); i++)
	{
		Quad* current = g_quads.at(i);
		contexts.push_back(GetRenderingContext(current));
	}

	while (!glfwWindowShouldClose(window))
	{
		/* Render here */
		renderer.Clear();

		Animations();

		Vector3f direction = tfc.GetPosition() + tfc.GetDirection();
		Vector3f position = tfc.GetPosition();

		glm::mat4 matCam_glm = glm::lookAt(glm::vec3(position.X(), position.Y(), position.Z()), glm::vec3(direction.X(), direction.Y(), direction.Z()), glm::vec3(0.0f, 1.0f, 0.0f));
		glm::mat4 projection_glm = g_mvp_glm * matCam_glm;

		renderer.SetPerspectivef(&projection_glm[0][0]);

		for (auto it = contexts.begin(); it != contexts.end(); ++it)
			renderer.Draw(*it, g_textures);

#pragma region blending refactor
		cameraPosition = tfc.GetPosition();
		wv = GetWindowVertices(glm::vec3(cameraPosition.X(), cameraPosition.Y(), cameraPosition.Z()));

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC1_ALPHA);

		ShaderProgram* windowProgram = g_ShaderPrograms["default"];
		glm::mat4 transform(1.0f);

		vaWindow.Bind();
		vbWindow.Bind();

		GLCall(glBufferData(GL_ARRAY_BUFFER, wv.size() * sizeof(float), &wv[0], GL_STATIC_DRAW));
		vaWindow.AddBuffer(vbWindow, vbLayoutWindow);

		windowProgram->Bind();
		windowProgram->SetUniformMat4f("u_MVP", &projection_glm[0][0]);
		windowProgram->SetUniformMat4f("u_Transform", &transform[0][0]);

		GLCall(glDrawArrays(GL_TRIANGLES, 0, 3));
		GLCall(glDrawArrays(GL_TRIANGLES, 3, 6));
		GLCall(glDrawArrays(GL_TRIANGLES, 6, 9));
		GLCall(glDrawArrays(GL_TRIANGLES, 9, 12));
		glDisable(GL_BLEND);
#pragma endregion

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

	for (size_t i = 0; i < g_quads.size(); i++)
		delete g_quads[i];
}

int main(void)
{
	LoadMvp();
	LoadVertexSets();
	BuildGeometries();

	BuildWindows();

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
