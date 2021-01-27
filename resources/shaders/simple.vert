#version 150
#extension GL_ARB_explicit_attrib_location : require
// vertex attributes of VAO
layout(location = 0) in vec3 in_Position;
layout(location = 1) in vec3 in_Normal;

//Matrix Uniforms as specified with glUniformMatrix4fv
uniform mat4 ModelMatrix;
uniform mat4 ViewMatrix;
uniform mat4 ProjectionMatrix;
uniform mat4 NormalMatrix;
//uniform vec3 Color;
//uniform vec3 ambient_color;
//uniform vec3 in_light;

out vec3 WorldPosition;
out vec3 WorldNormal;

out vec3 pass_Normal;
// source for texture: https://learnopengl.com/Getting-started/Textures

void main(void)
{
	// normal in world space
	WorldNormal = inverse(transpose(mat3(ModelMatrix))) * in_Normal;

	// position in world space
	WorldPosition = vec3(ModelMatrix * vec4(in_Position, 1.0));
	pass_Normal = normalize(pass_Normal);

	gl_Position = (ProjectionMatrix  * ViewMatrix * ModelMatrix) * vec4(in_Position, 1.0);

}
