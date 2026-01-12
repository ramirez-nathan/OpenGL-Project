#include "main.h"
#ifdef EXERCISES_CPP

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

// settings
const unsigned int SCR_WIDTH{ 800 };
const unsigned int SCR_HEIGHT{ 600 };

const char* vertexShaderSource = "#version 330 core\n" // basic vertex shader
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
// whatever this is set to will be used as output of the shader
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";
// ^ as simple as we can get, no processing whatsoever on input data
// simply fowarded it to the shaders output

const char* fragmentShaderSource = "#version 330 core\n" // basic fragment shader
"out vec4 FragColor;\n" // fragment shader needs 1 output var (FragColor), 
						// a vec4 that defines the final color output 
	"void main()\n"
	"{\n"
	"   FragColor = vec4(0.0f, 0.0f, 0.0f, 1.0f);\n"
	"}\n\0";
int main()
{
	// glfw: initialize and configure
	// ------------------------------
	glfwInit();
	// setting glfw version boundaries
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	// explicity declare only core profile to use
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	// ------------------------------

	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	// Vertex Shader -----------------------
	// shader object ref
	unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER); // int b/c we ref. shader obj by ID
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);

	// check for vertex shader compile-time errors
	int success; // define int to indicate success
	char infoLog[512]; // storage container for error msgs
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success); // check if successful compilation

	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	// Fragment Shader --------------------
	unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);

	// check for fragment shader compile errors
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
	}
	// Link Shaders ----------------------
	// shader program object ref
	unsigned int shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	// check for shader program compile time errors
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	// Vertex Data & Attributes Configuration (and Buffers) ----------------------
	// Ex1.1 - Change equilateral tri to a right tri
	float vertices[] = { // z-depth is 0 to make it look 2D
		-0.5f, -0.5f, 0.0f, // lower left corner
		 0.5f, -0.5f, 0.0f, // lower right corner
		-0.5f,  0.5f, 0.0f // upper left corner
	};
	unsigned int VBO, VAO; // vertex buffer object, referenced by ID
	glGenBuffers(1, &VBO);
	glGenVertexArrays(1, &VAO);
	// bind the Vertex Array Object first, then bind and set vertext buffer(s), and then configure vertex attributes
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO); // bind buffer to target buffer object
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	// ^ GL_STATIC_DRAW b/c position data doesn't change, is used a lot,
	// and stays the same for every render call

	// Specify how OpenGL should interpret the vertex data
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);


	// render loop
	while (!glfwWindowShouldClose(window))
	{
		// input
		processInput(window);

		// render 
		glClearColor(0.9372f, 0.8353f, 0.991f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// draw triangle
		glUseProgram(shaderProgram);
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		// glBindVertexArray(0); // no need to unbind it every time as we only have a single VAO

		// glfw business - poll IO events and swap buffers
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	// de-allocate all resources once they've outlived their purpose:
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteProgram(shaderProgram);

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