#pragma once
#include "Entity.h"
#include "Material.h"

class ENGINEDLL_API Shape : public Entity {
protected:
	Material * _mat;
	int _vrtxCount;
	int _colorVrtxCount;
	int _drawMode;
	float* _vrtxs;
	float* _colorVrtx;
	bool _dispose;
	unsigned int _bufferData;
	unsigned int _colorBufferData;
	unsigned int _programID;
public:
	Shape(Renderer* renderer);
	~Shape();
	void Draw() override;
	void SetVertices(float* vrtxs, const int& count);
	void SetColorBufferData(float* colorVrtxs, const int& count);

	void SetMaterial(Material* material);
	void Dispose();
	void BindMaterial();
	void SetDrawMode(int drawMode) { _drawMode = drawMode; }
};

