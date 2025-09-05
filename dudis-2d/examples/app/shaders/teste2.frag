#version 330

out vec4 fragColor;
uniform vec2 iResolution;
uniform sampler2D uTexture;
uniform float time;

in vec2 fragTexCoord;     // coordenadas UV (Raylib já fornece)

void main(){

    vec2 uv = fragTexCoord;

    float mask = smoothstep(0.4, 0.5, fract(uv.y * 10.0 +time));
    uv.x += mask * 0.2;
    // uv.y += 0.5 * pow(time + uv.y, 1.f) + 20.0f;

    vec3 texColor = texture(uTexture, uv).rgb;

   // vec3 color = texColor * (0.5 + 0.5*cos(time + vec3(0,2,4)));

    //vec3 color = vec3(fragTexCoord.x - 0.4f, 0.0,0.0);


    fragColor = vec4(texColor, 1.0);
}