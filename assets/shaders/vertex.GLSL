#version 330
in vec3 vCol;
in vec2 vPos;
uniform mat4 mvp;
out vec3 color;
void main()
{
    gl_Position = mvp * vec4(vPos, 0.0, 1.0);
    color = vCol;
}