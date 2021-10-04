#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

class windowType {
private:
	GLFWwindow* window;
public:
	void render(GLFWwindow* window) {
		int width, height;
		glfwGetFramebufferSize(this->window, &width, &height);
		glViewport(0, 0, width, height);
		glClearColor(0, 0, 0, 0);
		glClear(GL_COLOR_BUFFER_BIT);
		glfwSwapBuffers(window);
	}

	void setWindow(GLFWwindow* window) {
		this->window = window;
	}

	GLFWwindow* getWindow() {
		return window;
	}
};

class practiceWindowType : public windowType {
private:
	double RED = 0;
	double GREEN = 0;
	double BLUE = 0;
public:
	void render() {
		int width, height;
		glfwGetFramebufferSize(getWindow(), &width, &height);
		glViewport(0, 0, width, height);
		glClearColor(RED, GREEN, BLUE, 0);
		glClear(GL_COLOR_BUFFER_BIT);
		glfwSwapBuffers(getWindow());
	}
	void addBLUE(double n) {
		BLUE += n;
		if (BLUE >= 255) BLUE = 0;
	}
};

int main(void) {
	if (!glfwInit()) return -1;
	GLFWwindow* window = glfwCreateWindow(640, 480, "LeeDongHwan", NULL, NULL);
	glfwMakeContextCurrent(window);
	glewInit();
	practiceWindowType practiceWindow;
	practiceWindow.setWindow(window);
	while (!glfwWindowShouldClose(practiceWindow.getWindow())) {
		practiceWindow.render();
		glfwPollEvents();
		practiceWindow.addBLUE(15.5);
	}
	glfwDestroyWindow(window);
	glfwTerminate();
}