
#version 330 core
out vec4 FragColor;
  
in vec2 TexCoords;

uniform sampler2D screenTexture;
uniform vec2 windowSize;

void main()
{ 
  float width = 640;
  float height = 480;
  int mode = 5;
  vec4 color = texture(screenTexture, TexCoords);
  if (mode == 0) {
    FragColor = color;
  } 
  // luminance preserving grayscale
  else if (mode == 1) {
    float luminance = 0.2126 * color.x + 0.7152 * color.y + 0.0722 * color.z;
    FragColor = vec4(luminance, luminance, luminance,1);
  } 
  // mirroring vertical
  else if (mode == 2) {
    vec2 mirrorTexCoords = vec2(1 - TexCoords.x, TexCoords.y);
    FragColor = texture(screenTexture, mirrorTexCoords);
  } 
  // mirroring horizontal
  else if (mode == 5) {
    vec2 mirrorTexCoords = vec2(TexCoords.x, 1-TexCoords.y);
    FragColor = texture(screenTexture, mirrorTexCoords);
  } 
  // blur
  else if (mode == 3) {
    if ((gl_FragCoord.x > 0) && (gl_FragCoord.y > 0) && (gl_FragCoord.x < width-1) && (gl_FragCoord.y < height-1)) {
      float x = gl_FragCoord.x;
      float y = gl_FragCoord.y;
      vec4 colorLeft = texture(screenTexture, vec2((x-1)/width,y/height));
      vec4 colorUp = texture(screenTexture, vec2(x/width,(y-1)/height));
      vec4 colorUpLeft = texture(screenTexture, vec2((x-1)/width,(y-1)/height));
      vec4 colorRight = texture(screenTexture, vec2((x+1)/width,y/height));
      vec4 colorDown = texture(screenTexture, vec2(x/width,(y+1)/height));
      vec4 colorDownRight = texture(screenTexture, vec2((x+1)/width,(y+1)/height));
      vec4 colorUpRight = texture(screenTexture, vec2((x+1)/width,(y-1)/height));
      vec4 colorDownLeft = texture(screenTexture, vec2((x+1)/width,(y+1)/height));
      vec4 NewColor = (0.0625) * (colorDownLeft + colorDownRight + colorUpLeft);
      NewColor = NewColor + (0.125) * (colorUp + colorLeft + colorRight + colorDown);
      NewColor = NewColor + (0.25) * color;
      FragColor = vec4(NewColor.x, NewColor.y, NewColor.z, 1);
    }
  }
  // custom negation effect
  else if (mode == 10) {
      if (gl_FragCoord.x < 400) {
        FragColor = vec4(1 - color.x, 1 - color.y, 1- color.z, 1);
      } else {
        FragColor = color;
      }
  } 
}