#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec2 textureCoord;

out vec3 outColor;

/*
    Model View Projection Matrices (MVP)

    Model -> World
    World -> View
    View  -> Projection
*/

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    gl_Position = projection * view * model * vec4(position, 1.0);
    outColor = position;
}