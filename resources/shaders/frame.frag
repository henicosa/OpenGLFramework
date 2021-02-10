
#version 330 core
out vec4 FragColor;
  
in vec2 TexCoords;

uniform sampler2D screenTexture;
uniform vec2 windowSize;
uniform bool mirrorV;
uniform bool mirrorH;
uniform bool luminance;
uniform bool blur;
uniform bool negation;

void main()
{ 
  float width = 640;
  float height = 480;
  vec2 myTexCoords = TexCoords;
  // mirroring vertical
  if (mirrorV) {
    myTexCoords = vec2(1 - TexCoords.x, TexCoords.y);
  } 
  // mirroring horizontal
  if (mirrorH) {
    myTexCoords = vec2(TexCoords.x, 1-TexCoords.y);
  } 
  vec4 color = texture(screenTexture, myTexCoords);
  // custom negation effect
  if (negation) {
      color = vec4(1 - color.x, 1 - color.y, 1- color.z, 1);
  } 
  FragColor = color;
  // luminance preserving grayscale
  if (luminance) {
    float luminance = 0.2126 * color.x + 0.7152 * color.y + 0.0722 * color.z;
    FragColor = vec4(luminance, luminance, luminance,1);
  } 
  // blur
  if (blur) {
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
}