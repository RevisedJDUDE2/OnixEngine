#version 330 core
layout (location = 0) in vec3 Pos;
layout (location = 1) in vec3 Color;
layout (location = 2) in vec2 INSTANCED;
out vec3 aColor;

void main() {
  gl_Position = vec4(Pos.xy + INSTANCED.xy, 0.0f, 1.0f);
  aColor = Color;
}