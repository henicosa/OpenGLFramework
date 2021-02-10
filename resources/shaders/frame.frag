
#version 330 core
out vec4 FragColor;
  
in vec2 TexCoords;

uniform sampler2D screenTexture;

void main()
{ 
  vec4 color = texture(screenTexture, TexCoords);
  if (gl_FragCoord.x < 400) {
    FragColor = vec4(1 - color.x, 1 - color.y, 1- color.z, 1);
  } else {
    FragColor = color;
  }
}