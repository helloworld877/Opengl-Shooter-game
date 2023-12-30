#version 330 core

in Varyings{
    vec4 color;
    vec2 tex_coord;
    vec3 world;
    vec3 view;
    vec3 normal;
} fsin;

#define TYPE_DIRECTIONAL 0
#define TYPE_POINT 1
#define TYPE_SPOT 2

struct Light {
    int type;
    vec3 diffuse;
    vec3 specular;
    vec3 ambient;
    vec3 position;
    vec3 direction;
    float attenuation_constant;
    float attenuation_linear;
    float attenuation_quadratic;
    float inner_angle, outer_angle;
};

struct Material {
    vec3 diffuse;
    vec3 specular;
    vec3 ambient;
    float shininess;
};

uniform Material material;

#define MAX_LIGHT_COUNT 16

uniform Light lights[MAX_LIGHT_COUNT];
uniform int light_count;
uniform sampler2D tex;
out vec4 frag_color;

void main() {

    vec3 normal = normalize(fsin.normal);
    vec3 view = normalize(fsin.view);

    int count = min (light_count, MAX_LIGHT_COUNT);


    vec3 accumlated_light = vec3(0.0);

    for (int i=0 ; i< count; i++)
    {
        Light light = lights[i];
        vec3 light_direction;
        float attenuation =1;
        
        if (light.type == 0)
        {
            light_direction= light.direction;
            
        }
        else
        {
            light_direction = fsin.world - light.position;
            float distance = length(light_direction);
            light_direction /= distance;
            attenuation *= 1.0f / (light.attenuation_constant+light.attenuation_linear*distance + light.attenuation_quadratic*distance*distance);

            if (light.type==TYPE_SPOT)
            {
                float angle = acos(dot(light.direction,light_direction));
                attenuation *= smoothstep(light.outer_angle, light.inner_angle,angle);

            }
        }
        vec3 reflected = reflect(light_direction, normal);
        float lambert = max(0.0f,dot(normal,-light_direction));
        float phong = pow (max(0.0f,dot(view,reflected)),material.shininess);
        vec3 diffuse = material.diffuse * light.diffuse * lambert;
        // frag_color = vec4 (diffuse,1.0);
        // return;
        vec3 specular = material.specular * light.specular * phong;
        vec3 ambient = material.ambient * light.ambient;
        accumlated_light += (diffuse+specular+ambient) * attenuation ;   
    }
    
    vec4 texture_color = texture(tex, fsin.tex_coord); 
    frag_color = fsin.color * vec4(accumlated_light,1.0f);

}