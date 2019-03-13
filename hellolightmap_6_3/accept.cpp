#include <glad\glad.h>
#include <GLFW\glfw3.h>

#include "my_shader.h"
#include "my_camera.h"
#include "my_materia.h"

#include <iostream>
using namespace std;

extern GLuint loadTexture(const char *, int, int, unsigned int);

const int WIDTH = 800;
const int HEIGHT = 600;

int cubeNum = 10;
glm::vec3 cubePos[] = {
	glm::vec3(0.0f,  0.0f,  0.0f),
	glm::vec3(2.0f,  5.0f, -15.0f),
	glm::vec3(-1.5f, -2.2f, -2.5f),
	glm::vec3(-3.8f, -2.0f, -12.3f),
	glm::vec3(2.4f, -0.4f, -3.5f),
	glm::vec3(-1.7f,  3.0f, -7.5f),
	glm::vec3(1.3f, -2.0f, -2.5f),
	glm::vec3(1.5f,  2.0f, -2.5f),
	glm::vec3(1.5f,  0.2f, -1.5f),
	glm::vec3(-1.3f,  1.0f, -1.5f)
};

float vertices[] = {
	// positions          // normals           // texture coords
	-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,
	0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  0.0f,
	0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
	0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
	-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,

	-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,
	0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  0.0f,
	0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
	0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
	-0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,

	-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
	-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
	-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
	-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
	-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
	-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

	0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
	0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
	0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
	0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
	0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
	0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

	-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,
	0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  1.0f,
	0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
	0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  0.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,

	-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f,
	0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  1.0f,
	0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
	0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
	-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  0.0f,
	-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f
};

//MyCamera cam = MyCamera(glm::vec3(.0f, .0f, 3.f), glm::vec3(.0f, .0f, .0f));
MyCamera cam = MyCamera(glm::vec3(.0f, .0f, 3.f), .0f, -90.f);
float camSpeed = 2.5f;
double lastXPos, lastYpos;
bool mouseFistTime = true;
double deltaTime, lastFrameTime;
float MAX_PITCH = 50.f;


void framebufferCallback(GLFWwindow*, int, int);
void mouseCallback(GLFWwindow*, double, double);
void inputProcessHandler(GLFWwindow*);

int main()
{
	#pragma region init opengl info
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	#pragma endregion

	#pragma region create window
	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Learn OpenGL", NULL, NULL);
	if (window == NULL)
	{
		cout << "create window fail!" << endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	#pragma endregion

	#pragma region process func address with glad
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		cout << "glad fail!" << endl;
		glfwTerminate();
		return -1;
	}
	#pragma endregion

	#pragma region set frame_buffer callback
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetCursorPosCallback(window, mouseCallback);
	glfwSetFramebufferSizeCallback(window, framebufferCallback);
	#pragma endregion

	// vertex shader program
	MyShader *myShader = new MyShader(
		"..\\shaders\\texture_triangle_vertex.vert",
		"..\\shaders\\texture_triangle_fragment.frag"
	);

	MyMateria myMateria = MyMateria(myShader,
		loadTexture("container2.png", 0, GL_RGBA, GL_RGBA),
		loadTexture("container2_specular.png", 1, GL_RGBA, GL_RGBA),
		.4f,
		32.f);

	
	GLuint VAO;
	glGenVertexArrays(1, &VAO);

	GLuint VBO;
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	// read translate position matrix
	glm::mat4* transMat4 = new glm::mat4[cubeNum];
	for (int i = 0; i < 10; i++)
	{
		glm::mat4 model;
		model = glm::translate(model, cubePos[i]);
		float _angle = 20.f * i;
		model = glm::rotate(model, glm::radians(_angle), glm::vec3(1.f, .3f, .5f));
		transMat4[i] = model;
	}
	GLuint TRANS_VBO;
	glGenBuffers(1, &TRANS_VBO);
	glBindBuffer(GL_ARRAY_BUFFER, TRANS_VBO);
	glBufferData(GL_ARRAY_BUFFER, cubeNum * sizeof(glm::mat4), &transMat4[0], GL_STATIC_DRAW);
	// passing 4 * vec4 instead of mat4
	int attrOffset = 3;
	for (int i = 0; i < 4; i++)
	{
		glVertexAttribPointer(i + attrOffset, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(glm::vec4), (void*)(i * sizeof(glm::vec4)));
		glEnableVertexAttribArray(i + attrOffset);
		glVertexAttribDivisor(i + attrOffset, 1);
	}

	// clear
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glEnable(GL_DEPTH_TEST);

	myMateria.getShader()->use();
	glm::mat4 projection = glm::perspective(glm::radians(45.f), (float)WIDTH / (float)HEIGHT, .1f, 100.f);
	myMateria.getShader()->setMaxtrix("projection", glm::value_ptr(projection));

	glm::vec3 lightColor = glm::vec3(1.f, 1.f, 1.f);
	glm::vec3 lightPos = glm::vec3(0.f, 10.f, -5.f);

	#pragma region render loop
	while (!glfwWindowShouldClose(window))
	{
		double curFrameTime = glfwGetTime();
		deltaTime = curFrameTime - lastFrameTime;
		lastFrameTime = curFrameTime;
		inputProcessHandler(window);

		glClearColor(0.f, 0.f, 0.f, 0.1f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		myMateria.getShader()->use();
		glm::mat4 view;
		view = cam.getViewMat4();
		myMateria.getShader()->setMaxtrix("view", glm::value_ptr(view));

		myMateria.getShader()->setInt("objMaterial.diffuse", 0);
		myMateria.getShader()->setInt("objMaterial.specular", 1);
		myMateria.getShader()->setFloat("objMaterial.ambientCoe", myMateria.getAmbientCoe());
		myMateria.getShader()->setFloat("objMaterial.shinness", myMateria.getShininess());

		myMateria.getShader()->setVec3("lightPos", lightPos);
		myMateria.getShader()->setVec3("lightColor", lightColor);
		myMateria.getShader()->setVec3("camPos", cam.getCamPosition());

		glBindVertexArray(VAO);
		glDrawArraysInstanced(GL_TRIANGLES, 0, 36, cubeNum);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	#pragma endregion

	#pragma region clear and stop
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glfwTerminate();
	return 0;
	#pragma endregion
}

#pragma region callback implement
void mouseCallback(GLFWwindow* window, double xPos, double yPos)
{
	if (mouseFistTime == true)
	{
		lastXPos = xPos;
		lastYpos = yPos;
		mouseFistTime = false;
		//cout << xPos << "\t" << yPos << endl;
		return;
	}

	double deltaX = (xPos - lastXPos) * deltaTime; // yaw
	double deltaY = (lastYpos - yPos) * deltaTime; // pitch
	float yaw = cam.getYaw() + deltaX;
	float pitch = cam.getPitch() + deltaY;
	if (pitch > MAX_PITCH)
		pitch = MAX_PITCH;
	else if (pitch < -MAX_PITCH)
		pitch = -MAX_PITCH;

	cam.updateCamDirection(pitch, yaw);
	lastXPos = xPos;
	lastYpos = yPos;

}

void framebufferCallback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void inputProcessHandler(GLFWwindow* window)
{
	// close application
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}


	// handle moving camera
	float realSpeed = camSpeed * deltaTime;
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
		cam.updateCamPosition(GLFW_KEY_W, realSpeed);
	}
	else if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		cam.updateCamPosition(GLFW_KEY_S, realSpeed);
	}

	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		cam.updateCamPosition(GLFW_KEY_A, realSpeed);
	}
	else if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		cam.updateCamPosition(GLFW_KEY_D, realSpeed);
	}

	if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
	{
		cam.updateCamPosition(GLFW_KEY_Q, realSpeed);
	}
	else if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
	{
		cam.updateCamPosition(GLFW_KEY_E, realSpeed);
	}

}
#pragma endregion