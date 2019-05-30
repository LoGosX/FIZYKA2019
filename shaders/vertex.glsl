#version 330 core
in vec2 aPos; // the position variable has attribute position 0
in vec2 aVel;

out vec2 vel;

void main()
{
    gl_Position = vec4(aPos, 0.0, 1.0); // see how we directly give a vec2 to vec4's constructor 
    vel = aVel;
}