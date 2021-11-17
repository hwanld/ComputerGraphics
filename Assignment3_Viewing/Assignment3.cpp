#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "j3a.hpp"
#include "toys.h"

using namespace glm;

void init();
void render(GLFWwindow* window);

Program program;
GLuint vertBuf = 0;
GLuint triBuf = 0;
GLuint vertArray = 0;

const float PI = 3.141592;

float theta = 0;
float phi = 0;

vec3 cameraPosition = vec3(0,0,5);

double oldX;
double oldY;

void cursorCallback(GLFWwindow* window, double xpos, double ypos) {
	int width, height;
	glfwGetWindowSize(window, &width, &height);
	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_1)) {
		theta -= (xpos - oldX)/width * PI;
		phi -= (ypos - oldY) / height * PI;
	}
	oldX = xpos;
	oldY = ypos;
}

int main(void) {
	if (!glfwInit()) return -1;
	GLFWwindow* window = glfwCreateWindow(640, 640, "LeeDongHwanAssignment3", NULL, NULL);

	glfwSetCursorPosCallback(window, cursorCallback);

	glfwMakeContextCurrent(window);
	glewInit();
	init();
	while (!glfwWindowShouldClose(window)) {
		render(window);
	}
	glfwDestroyWindow(window);
	glfwTerminate();
}

void init() {
	program.loadShaders("shader.vert", "shader.frag");
	loadJ3A("Resources/dragon.j3a");

	glGenBuffers(1, &vertBuf);
	glBindBuffer(GL_ARRAY_BUFFER, vertBuf);
	glBufferData(GL_ARRAY_BUFFER, nVertices[0] * sizeof(glm::vec3), vertices[0], GL_STATIC_DRAW);

	glGenVertexArrays(1, &vertArray);
	glBindVertexArray(vertArray);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vertBuf);
	glVertexAttribPointer(0, 3, GL_FLOAT, 0, 0, 0);

	glGenBuffers(1, &triBuf);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, triBuf);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, nTriangles[0] * sizeof(glm::u32vec3), triangles[0], GL_STATIC_DRAW);
}

void render(GLFWwindow* window) {

	int width, height;
	glfwGetFramebufferSize(window, &width, &height);

	vec3 cameraPos = vec3(rotate(theta, vec3(0, 1, 0)) * rotate(phi, vec3(1, 0, 0)) * vec4(cameraPosition, 1));

	mat4 viewMat = lookAt(cameraPosition, vec3(0, 0, 0), vec3(0, 1, 0));
	mat4 projMat = perspective(60 * 3.141592f / 180, width / (float)height, 0.1f, 100.f);
	mat4 modelMat = mat4(1);

	glViewport(0, 0, width, height);
	glClearColor(0, 0, .5, 0);
	glClear(GL_COLOR_BUFFER_BIT);

	glUseProgram(program.programID);

	GLuint loc;
	loc = glGetUniformLocation(program.programID, "modelMat");
	glUniformMatrix4fv(loc, 1, false, glm::value_ptr(modelMat));
	loc = glGetUniformLocation(program.programID, "viewMat");
	glUniformMatrix4fv(loc, 1, false, glm::value_ptr(viewMat));
	loc = glGetUniformLocation(program.programID, "projMat");
	glUniformMatrix4fv(loc, 1, false, glm::value_ptr(projMat));

	glBindVertexArray(vertArray);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, triBuf);
	glDrawElements(GL_TRIANGLES, nTriangles[0] * 3, GL_UNSIGNED_INT, 0);
	glfwSwapBuffers(window);
}
