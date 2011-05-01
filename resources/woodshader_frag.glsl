const vec4 wood_color = vec4(0.52, 0.36, 0.25, 1.0);
const vec4 dark_wood_color = vec4(0.54 * 0.4, 0.36 * 0.4, 0.25 * 0.4, 1.0);
//
const float pi = 3.14;
uniform float wavelength = 0.1;
uniform float excentricity = 0.4;
uniform float twist = 0.5 * pi;
//
varying vec3 position;

void main(void) {
	// optionally add tilt:
	// rotate position around y axis
	
	float radius = length(position.xy);
	float angle = atan(position.y, position.x);
	float height = position.z;
	//
	//// add twist
	angle += twist * height;
	//// add excentricity
	radius *= 1.0 + excentricity * sin(angle);
	//
	float intensity = 0.5 + 0.5 * sin((radius / wavelength) * 2  *pi);
	gl_FragColor = mix(wood_color, dark_wood_color, intensity);
}
/*
#version 120

uniform sampler2D tex;
uniform vec2 center;
uniform float scale;
uniform int iter;

void main() {
    vec2 z, c;

    c.x = 1.3333 * (gl_TexCoord[0].x - 0.5) * scale - center.x;
    c.y = (gl_TexCoord[0].y - 0.5) * scale - center.y;

    int i;
    z = c;
    for( i=0; i<iter; i++ ){
        float x = (z.x * z.x - z.y * z.y) + c.x;
        float y = (z.y * z.x + z.x * z.y) + c.y;

        if( ( x * x + y * y ) > 4.0 ) break;
        z.x = x;
        z.y = y;
    }
	vec2 texCoord = vec2( (i == iter ? 0.0 : float(i)) / 100.0, 0.0 );
	vec3 color = texture2D( tex, texCoord ).rgb;

    gl_FragColor.rgb = color;
	gl_FragColor.a = 1.0;
}
*/