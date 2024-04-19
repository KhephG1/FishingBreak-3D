#version 120 core
//must have the same name as out in the fragment shader
out vec4 vert_pos;

void main()
{
//Vertex shader runs first then fragment shader
	//transform the vertex position

	
	vert_pos = gl_ModelViewProjectionMatrix * gl_Vertex;
	gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;

	//transform the texture coordinates

	gl_TexCoord[0] = gl_TextureMatrix[0] * gl_MultiTexCoord0;

	//forward the vertex color

	gl_FrontColor = gl_Color;

}