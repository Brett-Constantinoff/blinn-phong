##shader vertexShader
#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform mat4 normal_matrix;
uniform vec3 camera_position;

out vec3 oNormal;
out vec3 oCameraPosition;
out vec3 oFragPosition;

void main()
{
   gl_Position = projection * view * model * vec4(aPos, 1.0);
   oFragPosition = (model * vec4(aPos, 1.0)).xyz;
   oNormal = (normal_matrix * vec4(aNormal, 0.0)).xyz;
   oCameraPosition = camera_position;
}

#shader fragmentShader
#version 330 core
uniform vec3 diffuseVal;
uniform vec3 ambientVal;
uniform vec3 specularVal;
uniform float light_strength;
uniform float n;
uniform vec3 light_color;
uniform vec3 light_position;

in vec3 oNormal;
in vec3 oCameraPosition;
in vec3 oFragPosition;

out vec4 colour;

void main()
{
   vec3 normal = normalize(oNormal);
   vec3 light_direction = normalize(light_position - oFragPosition);
   vec3 view_direction = normalize(oCameraPosition - oFragPosition);
   vec3 ambient = ambientVal * light_color * light_strength;

   float diff = max(dot(light_direction, normal), 0.0);
   vec3 diffuse = diffuseVal * light_color * diff;

   vec3 halfVec = normalize(light_direction + view_direction);
   float spec = max(dot(halfVec, normal), 0.0);
   vec3 specular = specularVal * light_color * pow(spec, n);

   colour = vec4(ambient + diffuse + specular, 1.0);
}
