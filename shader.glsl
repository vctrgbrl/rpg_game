#shader vertex

#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTexCoord;

out vec2 vTexCoord;

void main() {
	gl_Position = vec4(aPos, 1.0);
	vTexCoord = aTexCoord;
};

#shader fragment

#version 330 core
out vec4 FragColor;

in vec2 vTexCoord;

uniform sampler2D texture_1;

void main() {
	FragColor = texture(texture_1, vTexCoord);
}