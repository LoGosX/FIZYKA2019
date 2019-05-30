#version 330 core
out vec4 FragColor;
  
in vec2 fvel; // the input variable from the vertex shader (same name and same type)  

void main()
{
    // vel /= (vel.x * vel.x + vel.y * vel.y);
    FragColor = vec4(fvel, 0.0, 1.0);
} 