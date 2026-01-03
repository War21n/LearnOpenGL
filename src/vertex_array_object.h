#pragma once

#include "vertex_buffer_object.h"

class VertexArrayObject {
public:
    VertexArrayObject();
    ~VertexArrayObject();

    void AddBuffer(const VertexBufferObject& vbo, const VertexBufferLayout& layout);

	void Bind() const;
	void Unbind() const;

private:
    unsigned int _id;
};