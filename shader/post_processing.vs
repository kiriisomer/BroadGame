#version 330 core
layout (location = 0) in vec4 vertex; // <vec2 position, vec2 texCoords>

out vec2 TexCoords;

// effect switch
uniform bool  chaos;
uniform bool  confuse;
uniform bool  shake;
uniform float time;

void main()
{
    gl_Position = vec4(vertex.xy, 0.0f, 1.0f); 
    vec2 texture = vertex.zw;
    
    if(chaos)
    {
        float strength = 0.2f;
        vec2 pos = vec2( (texture.x*2-1.0) + sin(time) * strength, (texture.y*2-1.0) + cos(time) * strength);
        
        // vec2 pos = vec2((texture.xy * 2) -1.0);
        TexCoords = pos;
        gl_Position.xy = pos;
    }
    else if(confuse)
    {
        TexCoords = vec2(1.0 - texture.x, 1.0 - texture.y);
        gl_Position.y = -gl_Position.y;
    }
    else
    {
        TexCoords = texture;
    }

    TexCoords = texture;
    if (shake)
    {
        float strength = 0.01;
        gl_Position.x += cos(time * 10) * strength;        
        gl_Position.y += cos(time * 15) * strength;        
    }
}  