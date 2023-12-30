#version 330


uniform sampler2D tex;


in vec2 tex_coord;

out vec4 frag_color;


void main(){

    vec4 original_color = texture(tex, tex_coord);
    float gray = dot(original_color.rgb, vec3(1.0/3.0, 1.0/3.0, 1.0/3.0));
    frag_color.rgb = vec3(gray);
    frag_color.r=original_color.r;

    
}