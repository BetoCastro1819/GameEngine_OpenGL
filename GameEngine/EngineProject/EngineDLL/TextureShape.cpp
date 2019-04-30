#include "TextureShape.h"
#include <GL\glew.h>
#include <GLFW\glfw3.h>

TextureShape::TextureShape(Renderer* renderer):Shape(renderer) {
	
	GLfloat vertexBuffer[] = {
		/* 1ST TRIANGLE */
		-1.0f,-1.0f, 0.0f,
		-1.0f,1.0f, 0.0f,
		1.0f, -1.0f, 0.0f,
		1.0f, 1.0f, 0.0f,

		/* 2ND TRIANGLE */
		/*
		-1.0f,1.0f, 0.0f,
		1.0f, -1.0f, 0.0f,
		1.0f, 1.0f, 0.0f,
		*/

		/*
		-1.0f,-1.0f, 0.0f,
		-1.0f, 1.0f, 0.0f,
		1.0f,-1.0f, 1.0f,
		-1.0f,-1.0f,-1.0f,
		1.0f,-1.0f,-1.0f,
		1.0f, 1.0f,-1.0f,
		1.0f,-1.0f,-1.0f,
		-1.0f,-1.0f,-1.0f,
		-1.0f,-1.0f,-1.0f,
		-1.0f, 1.0f, 1.0f,
		-1.0f, 1.0f,-1.0f,
		1.0f,-1.0f, 1.0f,
		-1.0f,-1.0f, 1.0f,
		-1.0f,-1.0f,-1.0f,
		-1.0f, 1.0f, 1.0f,
		-1.0f,-1.0f, 1.0f,
		1.0f,-1.0f, 1.0f,
		1.0f, 1.0f, 1.0f,
		1.0f,-1.0f,-1.0f,
		1.0f, 1.0f,-1.0f,
		1.0f,-1.0f,-1.0f,
		1.0f, 1.0f, 1.0f,
		1.0f,-1.0f, 1.0f,
		1.0f, 1.0f, 1.0f,
		1.0f, 1.0f,-1.0f,
		-1.0f, 1.0f,-1.0f,
		1.0f, 1.0f, 1.0f,
		-1.0f, 1.0f,-1.0f,
		-1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f,
		-1.0f, 1.0f, 1.0f,
		1.0f,-1.0f, 1.0f
		*/
	};


	// Two UV coordinatesfor each vertex. They were created with Blender.
	GLfloat UV_Buffer[] = {

		/* 1ST TRIANGLE */
		0.0f, 0.0f,
		0.0f, 1.0f,
		1.0f, 0.0f,
		1.0f, 1.0f,

		//0.000103f, 1.0f - 0.336048f,
		//0.335973f, 1.0f - 0.335903f,
		
		/* 2ND TRIANGLE */
		/*
		0.0f, 1.0f,
		1.0f, 0.0f,
		1.0f, 1.0f,
		*/
		//1.000023f, 1.0f - 0.000013f,
		//0.667979f, 1.0f - 0.335851f,
		//0.999958f, 1.0f - 0.336064f,
		
		/*
		0.667979f, 1.0f - 0.335851f,
		0.336024f, 1.0f - 0.671877f,
		0.667969f, 1.0f - 0.671889f,
		1.000023f, 1.0f - 0.000013f,
		0.668104f, 1.0f - 0.000013f,
		0.667979f, 1.0f - 0.335851f,
		0.000059f, 1.0f - 0.000004f,
		0.335973f, 1.0f - 0.335903f,
		0.336098f, 1.0f - 0.000071f,
		0.667979f, 1.0f - 0.335851f,
		0.335973f, 1.0f - 0.335903f,
		0.336024f, 1.0f - 0.671877f,
		1.000004f, 1.0f - 0.671847f,
		0.999958f, 1.0f - 0.336064f,
		0.667979f, 1.0f - 0.335851f,
		0.668104f, 1.0f - 0.000013f,
		0.335973f, 1.0f - 0.335903f,
		0.667979f, 1.0f - 0.335851f,
		0.335973f, 1.0f - 0.335903f,
		0.668104f, 1.0f - 0.000013f,
		0.336098f, 1.0f - 0.000071f,
		0.000103f, 1.0f - 0.336048f,
		0.000004f, 1.0f - 0.671870f,
		0.336024f, 1.0f - 0.671877f,
		0.000103f, 1.0f - 0.336048f,
		0.336024f, 1.0f - 0.671877f,
		0.335973f, 1.0f - 0.335903f,
		0.667969f, 1.0f - 0.671889f,
		1.000004f, 1.0f - 0.671847f,
		0.667979f, 1.0f - 0.335851f
		*/
	};
	_texture = _mat->Load_BMP("uvtemplate.bmp");
	_textureID = m_renderer->SetTextureID(_programID);

	SetVertices(vertexBuffer, 4);
	SetUVBufferData(UV_Buffer, 4);
}


TextureShape::~TextureShape() {
	//Dispose();
	m_renderer->DeleteBuffers(_uvBufferData);
	m_renderer->DeleteTextures(_texture);
	

	/* TODO: program crashes when it has to delete THESE vertices*/
	if (_uvVrtxs != nullptr) {
		//delete[] _uvVrtxs;
		_uvVrtxs = NULL;
	}
	
	std::cout << "TextureShape::~TextureShape()" << std::endl;
}

void TextureShape::DrawTextureShape() {
	Draw();
	m_renderer->BindTexture(_texture);
	m_renderer->SetTextureSampler(_textureID);
	m_renderer->BindBuffer(_uvBufferData, _uvVrtxCount, 1, 2, _drawMode);

}

void TextureShape::SetUVBufferData(float* vrtxs, const int& count) {
	_uvVrtxs = vrtxs;
	_uvVrtxCount = count;
	_uvBufferData = m_renderer->GenBuffer(_uvVrtxs, _uvVrtxCount * 2 * sizeof(float));
}