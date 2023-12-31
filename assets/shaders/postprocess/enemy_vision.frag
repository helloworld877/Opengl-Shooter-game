#version 330


uniform sampler2D tex;


in vec2 tex_coord;

out vec4 frag_color;


void main(){

    vec4 original_color = texture(tex, tex_coord);
    float gray = dot(original_color.rgb, vec3(1.0/3.0, 1.0/3.0, 1.0/3.0));
    frag_color.rgb = vec3(gray);
    frag_color.r=original_color.r;

    float squareSize = 0.007; // Change the size as needed
    vec2 center = vec2(0.5, 0.5); // Center of the screen

    // Check if the fragment is within the square bounds
    if (abs(tex_coord.x - center.x) < squareSize && abs(tex_coord.y - center.y) < squareSize) {
        frag_color.rgb = vec3(1.0); // Set color to white
    }

    
}