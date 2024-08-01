#version 330 core
layout (location = 0) in vec2 pos;
layout (location = 1) in vec2 texcoord;
layout (location = 2) in vec2 instanced;

out vec2 outCoord;
uniform mat4 view;
uniform mat4 proj;

void main() {
  gl_Position = proj * view * vec4(pos + instanced, 0.0, 1.0);
  outCoord = texcoord;
}