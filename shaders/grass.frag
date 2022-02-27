#version 330 core

out vec4 FragColor;

in vec3 crntPos;
in vec3 Normal;
in vec3 color;
in vec2 texCoord;

uniform sampler2D diffuse0;
uniform sampler2D specular0;
uniform vec4 lightColor;
uniform vec3 lightPos;
uniform vec3 camPos;

vec4 pointLight()
{
  vec3 lightVec = lightPos - crntPos;
  float dist = length(lightVec);
  float a = 1.0f;
  float b = 0.5f;
  float intensity = 1.0f / (a * dist * dist + b * dist + 1.0f);

  float ambient = 0.20f;

  vec3 normal = normalize(Normal);
  vec3 lightDirection = normalize(lightVec);
  float diffuse = max(dot(normal, lightDirection), 0.0f);

  float specularLight = 0.50f;
  vec3 viewDirection = normalize(camPos - crntPos);
  vec3 reflectionDirection = reflect(-lightDirection, normal);
  float specAmount = pow(max(dot(viewDirection, reflectionDirection), 0.0f), 16);
  float specular = specAmount * specularLight;

  return (texture(diffuse0, texCoord) * (diffuse * intensity + ambient) + texture(specular0, texCoord).r * specular * intensity) * lightColor;
}

vec4 directionalLight()
{
  float ambient = 0.20f;

  vec3 normal = normalize(Normal);
  vec3 lightDirection = normalize(vec3(1.0f, 1.0f, 0.0f));
  float diffuse = max(dot(normal, lightDirection), 0.0f);

  float specularLight = 0.50f;
  vec3 viewDirection = normalize(camPos - crntPos);
  vec3 reflectionDirection = reflect(-lightDirection, normal);
  float specAmount = pow(max(dot(viewDirection, reflectionDirection), 0.0f), 16);
  float specular = specAmount * specularLight;

  if (texture(diffuse0, texCoord).a < 0.1f)
    discard;

  return (texture(diffuse0, texCoord) * (diffuse + ambient) + texture(specular0, texCoord).r * specular) * lightColor;
}

vec4 spotLight()
{
  float outerCone = 0.90f;
  float innerCone = 0.95f;

  float ambient = 0.20f;

  vec3 normal = normalize(Normal);
  vec3 lightDirection = normalize(lightPos - crntPos);
  float diffuse = max(dot(normal, lightDirection), 0.0f);

  float specularLight = 0.50f;
  vec3 viewDirection = normalize(camPos - crntPos);
  vec3 reflectionDirection = reflect(-lightDirection, normal);
  float specAmount = pow(max(dot(viewDirection, reflectionDirection), 0.0f), 16);
  float specular = specAmount * specularLight;

  float angle = dot(vec3(0.0f, -1.0f, 0.0f), -lightDirection);
  float intensity = clamp((angle - outerCone) / (innerCone - outerCone), 0.0f, 1.0f);

  return (texture(diffuse0, texCoord) * (diffuse * intensity + ambient) + texture(specular0, texCoord).r * specular * intensity) * lightColor;
}

void main()
{
  FragColor = directionalLight();
}