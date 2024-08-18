#version 330 core

in vec3 oColor;
out vec4 FragColor;
uniform float alpha;

vec3 applySepia(in vec3 color) {
    // Define the sepia tone transformation
    vec3 sepia;
    sepia.r = dot(color, vec3(0.393, 0.769, 0.189));
    sepia.g = dot(color, vec3(0.349, 0.686, 0.168));
    sepia.b = dot(color, vec3(0.272, 0.534, 0.131));
    return sepia;
}

void main() {
  vec3 func_rets = applySepia(oColor);
  //vec3 func_rets = noise3(0.1);
  FragColor = vec4(oColor, alpha);
}