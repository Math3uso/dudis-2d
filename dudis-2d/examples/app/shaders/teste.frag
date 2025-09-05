#version 330

out vec4 fragColor;

uniform vec2 iResolution;
uniform float time;
uniform sampler2D texture0;


// void main(){

//    vec2 uv = gl_FragCoord.xy / iResolution;

//    vec3 uv3 = vec3(uv,0.0);

//    vec3 texColor = texture(texture0, uv).rgb;

//    vec3 col = texColor * (0.5 + 0.5*cos(time + vec3(0,2,4)));

//    // vec3 col = vec3(uv.x, 0.0,0.0);

//     fragColor = vec4(col, 1.0f);
// }

void main() {
  vec2 uv = gl_FragCoord.xy / iResolution;

  vec2 center = vec2(0.5, 0.5); // centro do impacto (pode ser passado como uniform)
  vec2 dir = uv - center;
  float dist = length(dir);

  float ripple = sin(dist * 20.0 - time * 10.0) * 0.02; // intensidade da onda
  vec2 offset = normalize(dir) * ripple; 

  vec3 texColor = texture(texture0, uv + offset).rgb;

  // vec3 texColor = texture(texture0, uv).rgb;

  vec3 pulsating = 0.5 + 0.5 * cos(time + vec3(0, 2, 4));

  float verticalFactor = 0.3 + 0.7 * uv.y; // nunca chega a 0, vai de 0.3 (embaixo) a 1 (topo)

  vec3 col = texColor * pulsating * verticalFactor;


  fragColor = vec4(col, 1.0);
}