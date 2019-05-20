#version 330 core

in vec3 interpColor;

void main() {
    vec2 pos = gl_PointCoord - vec2(0.5);
    float dist_squared = dot(pos, pos);
    gl_FragColor = mix(
        vec4(interpColor, 1.0),
        vec4(0.1, 0.1, 0.1, 0.0),
        smoothstep(0.2, 0.3, dist_squared));
}