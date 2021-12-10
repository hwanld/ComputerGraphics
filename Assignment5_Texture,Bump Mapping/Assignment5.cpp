#define GLEW_STATIC
#define STB_IMAGE_IMPLEMENTATION
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "j3a.hpp"
#include "toys.h"
#include "stb_image.h"

using namespace glm;

void init();
void render(GLFWwindow* window);

Program program;
GLuint vertBuf = 0;
GLuint normBuf = 0;
GLuint tcoordBuf = 0;
GLuint triBuf = 0;
GLuint vertArray = 0;
GLuint texID = 0;
GLuint bumpID = 0;

const float PI = 3.141592;

float theta = 0;
float phi = 0;
float fov = 60;
float cameraDistance = 1;

vec3 cameraPosition = vec3(0, 0, 5);
vec3 lightPos = vec3(3, 5, 5);
vec3 lightInt = vec3(1, 1, 1);
vec3 ambInt = vec3(.1, .1, .1);
float shin = 20;

double oldX;
double oldY;

void cursorCallback(GLFWwindow* window, double xpos, double ypos) {
	int width, height;
	glfwGetWindowSize(window, &width, &height);
	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_1)) {
		theta -= (xpos - oldX) / width * PI;
		phi -= (ypos - oldY) / height * PI;
		if (phi < -PI / 2) phi = -PI / 2;
		if (phi > PI / 2) phi = PI / 2;
		if (theta < -PI / 2) theta = -PI / 2;
		if (theta > PI / 2) theta = PI / 2;
	}
	oldX = xpos;
	oldY = ypos;
}

void scrollCallback(GLFWwindow* window, double xoffset, double yoffset) {
	//cameraDistance = cameraDistance * pow(1,01, yoffset);
	fov = fov * pow(1.1, yoffset);
	if (fov < 10) fov = 10;
	if (fov > 170) fov = 170;
}

int main(void) {
	if (!glfwInit()) return -1;
	GLFWwindow* window = glfwCreateWindow(640, 640, "LeeDongHwanAssignment5", NULL, NULL);

	glfwSetCursorPosCallback(window, cursorCallback);
	glfwSetScrollCallback(window, scrollCallback);

	glfwMakeContextCurrent(window);
	glewInit();
	init();
	while (!glfwWindowShouldClose(window)) {
		glfwPollEvents();
		render(window);
	}
	glfwDestroyWindow(window);
	glfwTerminate();
}

void init() {
	program.loadShaders("shader.vert", "shader.frag");
	loadJ3A("Resources/dwarf.j3a");
	int w, h, n;
	stbi_set_flip_vertically_on_load(true);
	void* buf = stbi_load(("Resources/"+diffuseMap[0]).c_str(), &w, &h, &n, 4);

	glGenTextures(1, &texID);
	glBindTexture(GL_TEXTURE_2D, texID);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_SRGB8_ALPHA8, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, buf);
	stbi_image_free(buf);

	buf = stbi_load(("Resources/" + bumpMap[0]).c_str(), &w, &h, &n, 4);
	glGenTextures(1, &bumpID);
	glBindTexture(GL_TEXTURE_2D, bumpID);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_SRGB8_ALPHA8, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, buf);
	stbi_image_free(buf);

	glGenBuffers(1, &vertBuf);
	glBindBuffer(GL_ARRAY_BUFFER, vertBuf);
	glBufferData(GL_ARRAY_BUFFER, nVertices[0] * sizeof(glm::vec3), vertices[0], GL_STATIC_DRAW);

	glGenBuffers(1, &normBuf);
	glBindBuffer(GL_ARRAY_BUFFER, normBuf);
	glBufferData(GL_ARRAY_BUFFER, nVertices[0] * sizeof(glm::vec3), normals[0], GL_STATIC_DRAW);

	glGenBuffers(1, &tcoordBuf);
	glBindBuffer(GL_ARRAY_BUFFER, tcoordBuf);
	glBufferData(GL_ARRAY_BUFFER, nVertices[0] * sizeof(glm::vec2), texCoords[0], GL_STATIC_DRAW);

	glGenVertexArrays(1, &vertArray);
	glBindVertexArray(vertArray);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vertBuf);
	glVertexAttribPointer(0, 3, GL_FLOAT, 0, 0, 0);

	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, normBuf);
	glVertexAttribPointer(1, 3, GL_FLOAT, 0, 0, 0);

	glEnableVertexAttribArray(2);
	glBindBuffer(GL_ARRAY_BUFFER, tcoordBuf);
	glVertexAttribPointer(2, 2, GL_FLOAT, 0, 0, 0);

	glGenBuffers(1, &triBuf);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, triBuf);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, nTriangles[0] * sizeof(glm::u32vec3), triangles[0], GL_STATIC_DRAW);

}

void render(GLFWwindow* window) {

	int width, height;
	glfwGetFramebufferSize(window, &width, &height);

	vec3 cameraPos = vec3(rotate(theta, vec3(0, 1, 0)) * rotate(phi, vec3(1, 0, 0)) * vec4(cameraPosition, 1)); // *cameraDistance

	mat4 viewMat = lookAt(cameraPos, vec3(0, 0, 0), vec3(0, 1, 0));
	mat4 projMat = perspective(fov * PI / 180, width / (float)height, 0.1f, 100.f);
	mat4 modelMat = mat4(1);

	glViewport(0, 0, width, height);
	glClearColor(0, 0, .3, 0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_FRAMEBUFFER_SRGB);

	glUseProgram(program.programID);

	GLuint loc;
	loc = glGetUniformLocation(program.programID, "modelMat");
	glUniformMatrix4fv(loc, 1, false, glm::value_ptr(modelMat));
	loc = glGetUniformLocation(program.programID, "viewMat");
	glUniformMatrix4fv(loc, 1, false, glm::value_ptr(viewMat));
	loc = glGetUniformLocation(program.programID, "projMat");
	glUniformMatrix4fv(loc, 1, false, glm::value_ptr(projMat));

	loc = glGetUniformLocation(program.programID, "lightPos");
	glUniform3fv(loc, 1, glm::value_ptr(lightPos));
	loc = glGetUniformLocation(program.programID, "lightInt");
	glUniform3fv(loc, 1, glm::value_ptr(lightInt));
	loc = glGetUniformLocation(program.programID, "ambInt");
	glUniform3fv(loc, 1, glm::value_ptr(ambInt));
	loc = glGetUniformLocation(program.programID, "color");
	glUniform3fv(loc, 1, glm::value_ptr(diffuseColor[0]));
	loc = glGetUniformLocation(program.programID, "specularColor");
	glUniform3fv(loc, 1, glm::value_ptr(specularColor[0]));
	loc = glGetUniformLocation(program.programID, "shininess");
	glUniform1f(loc, shininess[0]);

	loc = glGetUniformLocation(program.programID, "cameraPos");
	glUniform3fv(loc, 1, glm::value_ptr(cameraPos));

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texID);
	loc = glGetUniformLocation(program.programID, "colorTexture");
	glUniform1i(loc, 0);

	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, bumpID);
	loc = glGetUniformLocation(program.programID, "bumpTexture");
	glUniform1i(loc, 1);

	glBindVertexArray(vertArray);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, triBuf);
	glDrawElements(GL_TRIANGLES, nTriangles[0] * 3, GL_UNSIGNED_INT, 0);
	glfwSwapBuffers(window);
}
