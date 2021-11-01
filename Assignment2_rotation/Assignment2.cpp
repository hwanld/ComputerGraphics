#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <vector>
#include <glm/glm.hpp>
#include "toys.h"
#include <cmath>
#include <glm/gtc/type_ptr.hpp>

#define PI 3.14
void init_vertex();
void render(GLFWwindow* window, GLfloat sinValue, GLfloat cosValue);

Program program;
GLuint vertBuf = 0;
GLuint triBuf = 0;
GLuint vertArray = 0;

int main(void) {
	if (!glfwInit()) return -1;
	GLFWwindow* window = glfwCreateWindow(640, 640, "LeeDongHwanAssignment2", NULL, NULL);
	glfwMakeContextCurrent(window);
	glewInit();
	init_vertex();
	GLfloat index = 0;
	while (!glfwWindowShouldClose(window)) {
		float cosValue = std::cos(PI / 180 * index);
		float sinValue = std::sin(PI / 180 * index);
		render(window, sinValue, cosValue);
		index += 5;
		if (index > 360) index = 0;
		glfwPollEvents();
	}
	glfwDestroyWindow(window);
	glfwTerminate();
}

void init_vertex() {
	program.loadShaders("shader.vert", "shader.frag");
	std::vector <glm::vec3> vert;
	vert.push_back(glm::vec3(0, 0.7, 0));
	vert.push_back(glm::vec3(-0.7, -0.7, 0));
	vert.push_back(glm::vec3(0.7, -0.7, 0));
	

	std::vector <glm::u32vec3> triangles;
	triangles.push_back(glm::u32vec3(0, 1, 2));

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

void render(GLFWwindow* window, GLfloat sinValue, GLfloat cosValue) {
	GLuint location;

	int width, height;
	glfwGetFramebufferSize(window, &width, &height);
	glViewport(0, 0, width, height);
	glClearColor(0, 0, .5, 0);
	glClear(GL_COLOR_BUFFER_BIT);

	glUseProgram(program.programID);

	glm::mat3 rotation = glm::mat3(cosValue, -1 * sinValue, 0, sinValue, cosValue, 0, 0, 0, 1);
	location = glGetUniformLocation(program.programID, "rotation");
	glUniformMatrix3fv(location, 1, false, value_ptr(rotation));

	glBindVertexArray(vertArray);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, triBuf);
	glDrawElements(GL_TRIANGLES, 3 * 1, GL_UNSIGNED_INT, 0);
	glfwSwapBuffers(window);
}
