#version 330 core

// Input vertex data, different for all executions of this shader.
layout(location = 0) in vec3 vertexPositions;
layout(location = 1) in vec3 vertexColor;

// Output data ; will be interpolated for each fragment.
out vec3 fragmentColor;
// Values that stay constant for the whole mesh.
uniform mat4 MVP;
uniform mat4 MVP2;

void main(){

	// Output position of the vertex, in clip space : MVP * position
//	    gl_Position =  MVP * vec4(vertexPositions, 1);
	gl_Position = MVP * inverse(MVP2)  * vec4(vertexPositions, 1);

	// The color of each vertex will be interpolated
	// to produce the color of each fragment
	fragmentColor = vertexColor;
}
