#version 460 core

// Vertex attributes
in vec4 aPosition;
in vec3 aNormal;
in vec2 aTexCoord;

// Matrices 
uniform mat4 m_m, v_m, p_m;

// Light properties
uniform vec3 light_position;

// Outputs to the fragment shader
out VS_OUT {
    vec3 N;
    vec3 L;
    vec3 V;
    vec2 texCoord;
} vs_out;

void main(void) {
    // Create Model-View matrix
    mat4 mv_m = v_m * m_m;

    // Calculate view-space coordinate - in P point 
    // we are computing the color
    vec4 P = mv_m * aPosition;

    // Calculate normal in view space
    vs_out.N = mat3(mv_m) * aNormal;
     // Calculate view-space light vector
    vs_out.L = light_position - P.xyz;
    // Calculate view vector (negative of the view-space position)
    vs_out.V = -P.xyz;

    // Assigns the texture coordinates from the Vertex Data to "texCoord"
    vs_out.texCoord = aTexCoord;

    // Calculate the clip-space position of each vertex
    gl_Position = p_m * P;
} 

