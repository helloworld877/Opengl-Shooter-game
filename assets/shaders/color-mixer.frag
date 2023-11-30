#version 330 core

// This shader is designed to work with "triangle.vert" and it receives an
// interpolated varying which represents the vertex color.

in Varyings {
    vec3 color;
} fs_in;

out vec4 frag_color;

// currently the shader just returns the interpalated color varying.
// However, we want to mix the color channels around. We can do this using a 
// color matrix which we will send to the shader as 3 uniforms: red, green, blue.
// Each of these 3 variables will be a vec4. To apply the channel mixing for a
// certain channel (e.g. red), we apply this linear transformation:
// frag_color.r = red.r * fs_in.color.r + red.g + fs_in.color.g + red.b + fs_in.color.b + red.a;
// However, this line is too long to write, so we can simplify it using a dot product
// (which is defined in the "dot" function).

//TODO: (Req 1) Finish this shader and apply the channel mixing using the "dot" function.

// void main(){

//     // frag_color = fs_in.color;
    
//     //define mix factor and mixed color
//     float mixFactor;
//     vec3 mixedColor;
//     //Define color channels
//     vec3 red= vec3(1.0, 0.0, 0.0); // Red color
//     vec3 green= vec3(0.0, 1.0, 0.0); // Green color
//     vec3 blue= vec3(0.0, 0.0, 1.0); // Blue color
    
//     //calculate red dot product
//     mixFactor=dot(red,fs_in.color);
//     //assign mixed color
//     mixedColor=mix(fs_in.color,red,mixFactor);
//     //calculate green dot product
//     mixFactor=dot(green,fs_in.color);
//     //assign mixed color
//     mixedColor=mix(mixedColor,green,mixFactor);
//     //calculate blue dot product
//     mixFactor=dot(blue,fs_in.color);
//     //assign mixed color
//     mixedColor=mix(mixedColor,blue,mixFactor);

    
//     //output resulting color
//     frag_color = vec4(mixedColor, 1.0);

// }


uniform vec4 red = vec4(1.0, 0.0, 0.0, 0.0);   
uniform vec4 green = vec4(0.0, 1.0, 0.0, 0.0); 
uniform vec4 blue = vec4(0.0, 0.0, 1.0, 0.0);  


void main(){
     // Channel mixing using dot product
    float mixedRed = dot(vec4(fs_in.color, 1.0), red);
    float mixedGreen = dot(vec4(fs_in.color, 1.0), green);
    float mixedBlue = dot(vec4(fs_in.color, 1.0), blue);

    // Output the mixed color
    frag_color = vec4(mixedRed, mixedGreen, mixedBlue, 1.0);
    
}