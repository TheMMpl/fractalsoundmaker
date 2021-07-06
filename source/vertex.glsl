#version 400 compatibility
uniform vec2 res;
void main() {
  vec2 pos = (gl_Vertex.xy / res) * 2.0 - vec2(1.0, 1.0);
  gl_Position = vec4(pos, 0.0, 1.0);
}