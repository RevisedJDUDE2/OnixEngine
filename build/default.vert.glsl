#version 330 core
layout (location = 0) in vec3 Pos;
layout (location = 1) in vec3 Color;
layout (location = 2) in mat4 INSTANCED;
out vec3 aColor;

uniform mat4 view;
uniform mat4 proj;

void main() {
  gl_Position = proj * view * INSTANCED * vec4(Pos, 1.0f);
  aColor = Color;
}