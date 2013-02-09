uniform sampler2D texture;
uniform float factor;
uniform vec2 center;


void main(void)
{
	float radius = factor;
	vec2 distance =  abs(center - gl_TexCoord[0].xy );
	float clamp = 1.0 - step(radius,length(distance));
    gl_FragColor = clamp *  texture2D(texture,gl_TexCoord[0].xy);
}
 