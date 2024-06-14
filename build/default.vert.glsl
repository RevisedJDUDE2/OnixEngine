#version 330 core
layout (location = 0) in vec3 Pos;
layout (location = 1) in vec3 Color;
layout (location = 2) in vec3 INSTANCED;
out vec3 aColor;

void main() {
  vec3 POS = Pos + INSTANCED;
  gl_Position = vec4(POS, 1.0f);
  aColor = Color;
}