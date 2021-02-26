#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec2 textureCoord;

out vec2 outTexture;

/*
    Model View Projection Matrices (MVP)

    Model -> World
    World -> View
    View  -> Projection
*/

uniform mat4 mvp;

void main()
{
    gl_Position = mvp * vec4(position, 1.0);
    outTexture = textureCoord;
}