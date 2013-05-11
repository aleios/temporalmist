#ifndef INDEXBUFFEROBJECT_HPP
#define INDEXBUFFEROBJECT_HPP

#include <vector>

#include <GL/glew.h>
#include <SFML/OpenGL.hpp>

class IndexBufferObject
{
public:
	IndexBufferObject();
	IndexBufferObject(const std::vector<unsigned short>& indices, GLenum usage = GL_STATIC_DRAW);
	~IndexBufferObject();

	void SetData(const std::vector<unsigned short>& indices, GLenum usage = GL_STATIC_DRAW);
	void ReplaceData(const std::vector<unsigned short>& indices, GLintptr offset = 0);

	int GetNumIndices() const;

	GLuint GetIBOID() const;

	void Bind() const;
	void Unbind() const;
private:
	GLuint iboID;
	int indexCount;
};

#endif