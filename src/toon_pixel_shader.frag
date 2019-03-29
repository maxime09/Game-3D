uniform sampler2D Texture0;
uniform vec3 LightDir;

varying vec3 Normal;

vec4 CelShading(vec4 color)
{
  float Intensity = dot(LightDir, normalize(Normal));
  float factor = 0.5;
  if(Intensity > 0.95) factor = 1.0;
  else if(Intensity > 0.5 ) factor = 0.7;
  else if(Intensity > 0.25) factor = 0.4;
  color *= vec4(factor, factor, factor, 1.0);
  return color;
}

void main(void)
{
  vec4 color = texture2D( Texture0, vec2(gl_TexCoord[0]));

  color = CelShading(color);

  gl_FragColor = color;
}
