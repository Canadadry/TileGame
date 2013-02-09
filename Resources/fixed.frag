uniform sampler2D texture;
uniform float factor;
uniform vec2 center;


void main(void)
{
    gl_FragColor = texture2D(texture,gl_TexCoord[0].xy);
}
 