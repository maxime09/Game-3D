varying vec3 Normal;

void main(void)
{

gl_FrontColor = gl_Color;

Normal = gl_NormalMatrix * gl_Normal;

gl_TexCoord[0] = gl_MultiTexCoord0;

gl_Position = ftransform();

}
