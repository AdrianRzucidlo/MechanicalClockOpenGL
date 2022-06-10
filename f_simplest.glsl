#version 330

uniform sampler2D textureMap0;
uniform sampler2D textureMap1;

out vec4 pixelColor; //Zmienna wyjsciowa fragment shadera. Zapisuje sie do niej ostateczny (prawie) kolor piksela

in vec4 ic; 
in vec4 n;
in vec4 l;
in vec4 l2;
in vec4 v;
in vec2 iTexCoord0;
in vec2 iTexCoord1;

void main(void) {

	//Znormalizowane interpolowane wektory
	vec4 ml = normalize(l);
	vec4 ml2 = normalize(l2);
	vec4 mn = normalize(n);
	vec4 mv = normalize(v);
	//Wektor odbity
	vec4 mr = reflect(-ml, mn);
	vec4 mr2 = reflect(-ml2, mn);

	//Parametry powierzchni
	vec4 kd = mix(texture(textureMap0,iTexCoord0),texture(textureMap1, iTexCoord1),0.3);
	vec4 ks = vec4(1,1,1,1);

	//Obliczenie modelu oświetlenia
	float nl = clamp(dot(mn, ml), 0, 1);
	float rv = pow(clamp(dot(mr, mv), 0, 1), 10);
	pixelColor= vec4(kd.rgb * nl, kd.a) + vec4(vec3(0.4,0.76,0.97)*rv,0);

	float nl2 = clamp(dot(mn, ml2), 0, 1);
	float rv2 = pow(clamp(dot(mr2, mv), 0, 1), 6);
	pixelColor += vec4(kd.rgb * nl2,kd.a) + vec4(vec3(.95,0.85,0.55)*rv2, 0);
}
