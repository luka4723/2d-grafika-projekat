#version 330 core
layout (location = 0) in vec2 aPos;

out float w;
uniform vec2 cent;

void main()
{
    w = min(distance(aPos, cent)*3,1);
    gl_PointSize = 3.0;
    gl_Position = vec4(aPos, 0.0, 1.0);
}
