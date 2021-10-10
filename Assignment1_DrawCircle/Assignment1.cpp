#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <vector>
#include <glm/glm.hpp>
#include "toys.h"
#include <cmath>

#define howMuchTriUseForCircle 100000
#define PI 3.14159
#define RADUIS 0.8


void render(GLFWwindow* window);
void init();

Program program;
GLuint vertBuf = 0;
GLuint triBuf = 0;
GLuint vertArray = 0;

int main(void) {
	if (!glfwInit()) return -1;
	GLFWwindow* window = glfwCreateWindow(640, 640, "LeeDongHwanAssignment1", NULL, NULL);
	glfwMakeContextCurrent(window);
	glewInit();
	init();
	while (!glfwWindowShouldClose(window)) {
		render(window);
		glfwPollEvents();
	}
	glfwDestroyWindow(window);
	glfwTerminate();
}

void init() {
	program.loadShaders("shader.vert", "shader.frag");
	std::vector <glm::vec3> vert;
	vert.push_back(glm::vec3(0, 0, 0));
	for (int i = 1; i <= howMuchTriUseForCircle; i++) {
		GLfloat x = 0;
		GLfloat y = 0;
		GLfloat theta = (GLfloat)(2 * PI) / howMuchTriUseForCircle * i;
		if (theta == 2 * PI) theta = 0;
		x = (GLfloat)RADUIS * std::cos(theta);
		y = (GLfloat)RADUIS * std::sin(theta);
		vert.push_back(glm::vec3(x, y, 0));
	}

	std::vector <glm::u32vec3> triangles;
	for (int i = 1; i <= howMuchTriUseForCircle; i++) {
		if (i == howMuchTriUseForCircle) triangles.push_back(glm::u32vec3(0, i, 1));
		else triangles.push_back(glm::u32vec3(0, i, i+1));
	}

	glGenBuffers(1, &vertBuf);
	glBindBuffer(GL_ARRAY_BUFFER, vertBuf);
	glBufferData(GL_ARRAY_BUFFER, vert.size() * sizeof(glm::vec3), vert.data(), GL_STATIC_DRAW);

	glGenVertexArrays(1, &vertArray);
	glBindVertexArray(vertArray);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vertBuf);
	glVertexAttribPointer(0, 3, GL_FLOAT, 0, 0, 0);

	glGenBuffers(1, &triBuf);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, triBuf);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, triangles.size() * sizeof(glm::u32vec3), triangles.data(), GL_STATIC_DRAW);
}

void render(GLFWwindow* window) {
	int width, height;
	glfwGetFramebufferSize(window, &width, &height);
	glViewport(0, 0, width, height);
	glClearColor(0, 0, .5, 0);
	glClear(GL_COLOR_BUFFER_BIT);
	glUseProgram(program.programID);
	glBindVertexArray(vertArray);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, triBuf);
	glDrawElements(GL_TRIANGLES, 3*howMuchTriUseForCircle, GL_UNSIGNED_INT, 0); //»ï°¢Çü °¹¼ö * 3
	glfwSwapBuffers(window);
}
