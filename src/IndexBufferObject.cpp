#include <IndexBufferObject.hpp>

IndexBufferObject::IndexBufferObject()
{
	glGenBuffers(1, &iboID);
}

IndexBufferObject::IndexBufferObject(const std::vector<unsigned short>& indices, GLenum usage)
{
	glGenBuffers(1, &iboID);
	SetData(indices, usage);
}

IndexBufferObject::~IndexBufferObject()
{
	// TODO: confirm issues.
	glDeleteBuffers(1, &iboID);
}

void IndexBufferObject::SetData(const std::vector<unsigned short>& indices, GLenum usage)
{
	indexCount = indices.size();
	if(indexCount < 1)
		return;
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iboID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexCount * sizeof(unsigned short), &indices[0], usage);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void IndexBufferObject::ReplaceData(const std::vector<unsigned short>& indices, GLintptr offset)
{
	Bind();
	glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, offset, indices.size() * sizeof(unsigned short), &indices.front());
}

int IndexBufferObject::GetNumIndices() const
{
	return indexCount;
}

GLuint IndexBufferObject::GetIBOID() const
{
	return iboID;
}

void IndexBufferObject::Bind() const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iboID);
}

void IndexBufferObject::Unbind() const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}