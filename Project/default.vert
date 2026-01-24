#version 330 core

// Positions/Coordinates
layout (location = 0) in vec3 aPos; // the position variable has attribute position 0
// Colors
layout (location = 1) in vec3 aColor; // the color variable has attribute postion 1
// Textures
layout (location = 2) in vec2 aTex;

// Outputs the color for the Fragment Shader
out vec3 ourColor; // specify a color output to the fragment shader

out vec2 texCoord;

// Controls the scale of the vertices
uniform float scale; 

uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;


void main() // specify a color output to the fragment shader
{
	gl_Position = proj * view * model * vec4(aPos, 1.0); // see how we directly give a vec3 to vec4's constructor
	ourColor = aColor; // set ourColor to the input color we got from the vertex data
	texCoord = vec2(aTex.x, aTex.y);
}	
