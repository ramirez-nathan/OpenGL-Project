#include "Exercises.h"
#ifdef MAIN_CPP
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "shaderClass.h"
#include "VAO.h"
#include "EBO.h"

#include <iostream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);
// settings
const unsigned int SCR_WIDTH{ 800 };
const unsigned int SCR_HEIGHT{ 600 };

// Vertex Data & Attributes Configuration (and Buffers) ----------------------
GLfloat vertices[] = // z-depth is 0 to make it look 2D
{ //               COORDINATES                  /     COLORS           //
	-0.5f, -0.5f * float(sqrt(3)) * 1 / 3, 0.0f,     1.0f, 0.0f,  0.00f, // Lower left corner
	 0.5f, -0.5f * float(sqrt(3)) * 1 / 3, 0.0f,     1.0f, 0.0f,  0.00f, // Lower right corner
	 0.0f,  0.5f * float(sqrt(3)) * 2 / 3, 0.0f,     1.0f, 0.0f,  0.00f, // Upper corner
	-0.25f, 0.5f * float(sqrt(3)) * 1 / 6, 0.0f,     0.8372f, 0.7353f, 0.891f, // Inner left
	 0.25f, 0.5f * float(sqrt(3)) * 1 / 6, 0.0f,     0.8372f, 0.7353f, 0.891f, // Inner right
	 0.0f, -0.5f * float(sqrt(3)) * 1 / 3, 0.0f,     0.8372f, 0.7353f, 0.891f, // Inner down
};

// Indices for vertices order
GLuint indices[] =
{
	0, 3, 5, // Lower left triangle
	3, 2, 4, // Lower right triangle
	5, 4, 1 // Upper triangle
};

int main()
{
	// Initialize GLFW
	glfwInit();


	// Tell GLFW what version of OpenGL we are using 
	// In this case we are using OpenGL 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	// Tell GLFW we are using the CORE profile
	// So that means we only have the modern functions
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);



	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "OpenGL", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	// Introduce the window into the current context
	glfwMakeContextCurrent(window);


	//Load GLAD so it configures OpenGL
	gladLoadGL();
	// Specify the viewport of OpenGL in the Window
	// In this case the viewport goes from x = 0, y = 0, to x = 800, y = 800
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	
	// Generates Shader object using shaders defualt.vert and default.frag
	Shader shaderProgram("default.vert", "default.frag");

	// Generates Vertex Array Object and binds it
	VAO VAO1;
	VAO1.Bind();

	// Generates Vertex Buffer Object and links it to vertices
	VBO VBO1(vertices, sizeof(vertices));
	// Generates Element Buffer Object and links it to indices
	EBO EBO1(indices, sizeof(indices));

	// Links VBO to VAO
	VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 6 * sizeof(float), (void*)0);
	VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	// Unbind so we cant accidentally modify these
	VAO1.Unbind();
	VBO1.Unbind();
	EBO1.Unbind();

	// render loop
	while (!glfwWindowShouldClose(window))
	{
		// input
		processInput(window);

		// Specify the new color of the background before clearing
		glClearColor(0.9372f, 0.8353f, 0.991f, 1.0f);
		// Clean the back buffer and assign the new color to it
		glClear(GL_COLOR_BUFFER_BIT);
		// Tell OpenGL which Shader Program we want to use
		shaderProgram.Activate();
		// Bind the VAO so OpenGL knows to use it
		VAO1.Bind();
		//  Draw primitives, number of indices, datatype of indices, index of indices
		glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);
		// glfw business - poll IO events and swap buffers
		glfwSwapBuffers(window);
		// take care of all GLFW events
		glfwPollEvents();
	}
	

	// Delete all the objects we've created
	VAO1.Delete();
	VBO1.Delete();
	EBO1.Delete();
	shaderProgram.Delete();

	// Delete window before ending the program
	glfwDestroyWindow(window);
	// terminate, clearing all prev. allocated glfw resources
	glfwTerminate();
	return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}
#endif