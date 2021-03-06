#version 150

in  vec3 pass_Normal;
in vec3 WorldPosition;
in vec3 WorldNormal;
out vec4 out_Color;

uniform float LightIntensity;
uniform vec3 LightColor;
uniform vec3 LightPosition;
uniform vec3 Color;
uniform vec3 CameraPosition;
uniform sampler2D MyTexture;

void main() {
  // distance between World and Light
  float distance = length(LightPosition - WorldPosition);
  //normal on point
  vec3 normal = normalize(WorldNormal);
  //vec3 diffuseColor = LightIntensity * LightColor  / distance;

  // apply inverse mercator projection from lecture
  vec2 TexCoord = vec2((atan(-normal.z, normal.x) / 3.1415926 + 1.0) * 0.5,
                                (asin(normal.y) / 3.1415926 + 0.5));

  // load color from 2D texture
  vec4 colourfromtex = texture2D(MyTexture, TexCoord);

  // ambient component
  vec3 ambient_part = LightColor * 0.1;

  vec3 lightDirection = normalize(LightPosition - WorldPosition);
  vec3 beta = (LightColor * LightIntensity) * (1/(4*3.141*pow(distance,0.8)));

  // diffuse component
  float reflectivity = 10;
  vec3 diffuse_part = colourfromtex.xyz * dot(lightDirection, normal) * (reflectivity/3.141);

  // specular component
  vec3 cameraDirection = normalize(CameraPosition - WorldPosition);
  float shininess = 260;
  //vec3 h = (lightDirection + cameraDirection) / length(lightDirection + cameraDirection);
  //vec3 specular_part = Color * pow(max(dot(h, cameraDirection),0),4*shininess);

  //source: Wikipedia @ https://en.wikipedia.org/wiki/Blinn%E2%80%93Phong_reflection_model
  vec3 halfDir = normalize(lightDirection + cameraDirection);
  float specAngle = max(dot(halfDir, normal), 0.0);
  vec3 specular_part = 5 * colourfromtex.xyz * pow(specAngle, shininess);

  vec3 combinedColor = ambient_part + beta*(diffuse_part + specular_part);
  out_Color = vec4(combinedColor, 1.0);
}
