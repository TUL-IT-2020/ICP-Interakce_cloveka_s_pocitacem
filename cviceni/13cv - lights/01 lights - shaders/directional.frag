#version 460 core

// Outputs colors in RGBA
out vec4 FragColor;

// Material properties
uniform vec3 ambient_intensity, diffuse_intensity, specular_intensity;
uniform vec3 ambient_material, diffuse_material, specular_material;
uniform float specular_shinines;

// active texture unit
uniform sampler2D tex0;

// Input from vertex shader
in VS_OUT {
    vec3 N;
    vec3 L;
    vec3 V;
    vec2 texCoord;
} fs_in;

void main(void) {
    // Normalize the incoming N, L and V vectors
    vec3 N = normalize(fs_in.N);
    vec3 L = normalize(fs_in.L);
    vec3 V = normalize(fs_in.V);

    // Calculate R by reflecting -L around the plane defined by N
    vec3 R = reflect(-L, N);

    // Calculate the ambient, diffuse and specular contributions
    vec3 ambient = ambient_material * ambient_intensity;
    vec3 diffuse = max(dot(N, L), 0.0) * diffuse_material * diffuse_intensity;
    vec3 specular = pow(max(dot(R, V), 0.0), specular_shinines) *
			* specular_material * specular_intensity;

    FragColor = vec4( (ambient + diffuse) * texture(tex0, texCoord) + specular, 1.0);
} 

