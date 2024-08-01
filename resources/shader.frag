#version 330 core

out vec4 FragColor;
in vec2 outCoord;

uniform sampler2D tex;

void main() {
  FragColor = texture(tex, outCoord) * vec4(1.0, 1.0, 1.0, 1.0);
}