#ifndef VERTEXBUFFEROBJECT_HPP
#define VERTEXBUFFEROBJECT_HPP

#include <vector>

#include <GL/glew.h>
#include <SFML/OpenGL.hpp>

#include <Vertex.hpp>
#include <IndexBufferObject.hpp>

class VertexBufferObject
{
public:
	VertexBufferObject();
	VertexBufferObject(const std::vector<Vertex>& vertices, GLenum usage = GL_STATIC_DRAW);
	~VertexBufferObject();

	void Clear(GLenum usage = GL_STATIC_DRAW);
	void SetData(const std::vector<Vertex>& vertices, GLenum usage = GL_STATIC_DRAW);
	void ReplaceData(const std::vector<Vertex>& vertices, GLintptr offset = 0);

	void Bind() const;
	void Unbind() const;

	int GetNumVertices() const;

	GLuint GetVAOID() const;
	GLuint GetVBOID() const;

	void Draw(int offset = 0) const;
	void DrawIndexed(const IndexBufferObject& ibo) const;
private:
	GLuint vaoID, vboID;
	int vertexCount;
};

#endif