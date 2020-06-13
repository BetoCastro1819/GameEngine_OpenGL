#pragma once
#include "../../misc/Exports.h"
#include "Shape.h"


class ENGINEDLL_API TextureShape : public Shape {
private:
	float* _uvVrtxs;
	int _uvVrtxCount;
	int _uvBufferData;
	unsigned int _textureID;
	unsigned int  _texture;
public:
	void DrawTextureShape();
	void SetUVBufferData(float* vrtxs, const int& count);
	TextureShape(Renderer* renderer);
	~TextureShape();
};