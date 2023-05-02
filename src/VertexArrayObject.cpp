#include <glad/glad.h>
#include "VertexArrayObject.hpp"

using namespace Lone;

VertexArrayObject::VertexArrayObject(uint32_t size_vertices, float* vertices, std::vector<Attribute>& attributes, uint32_t size_indices, uint32_t* indices) {
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, size_vertices, vertices, GL_STATIC_DRAW);

	glGenBuffers(1, &ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, size_indices, indices, GL_STATIC_DRAW);

	int stride = 0;
	int location = 0;
	int index = 0;
	
	for (auto it = attributes.begin(); it != attributes.end(); it++)
	{
		stride += it->size * it->count;
	}
	
	for (auto it = attributes.begin(); it != attributes.end(); it++) {
		glVertexAttribPointer(location, it->count, it->type, GL_FALSE, stride, (void*)(index));
		glEnableVertexAttribArray(location);
		location++;
		index += it->size * it->count;
	}
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

VertexArrayObject::~VertexArrayObject() {
	glDeleteVertexArrays(1, &vao);
	glDeleteBuffers(1, &vbo);
}

void VertexArrayObject::Bind() {
	glBindVertexArray(vao);
}