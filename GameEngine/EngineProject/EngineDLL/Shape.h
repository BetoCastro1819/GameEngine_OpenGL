#pragma once
#include "Entity.h"
#include "Material.h"

class ENGINEDLL_API Shape : public Entity {
protected:
	Material* m_material;
	
	unsigned int m_programID;

	// Verices
	int m_VtxCount;
	int m_ColorVtxCount;
	float* m_VtxArr;
	float* m_ColorVtxArr;

	// Buffers
	unsigned int m_BufferData;
	unsigned int m_ColorBufferData;

	bool m_Dispose;
	int m_DrawMode;

public:
	Shape(Renderer* renderer);
	~Shape();
	void Draw() override;
	void SetVertices(float* vrtxs, const int& count);
	void SetColorBufferData(float* colorVrtxs, const int& count);

	virtual void SetMaterial(Material* material);
	void BindMaterial();
	void SetDrawMode(int drawMode) { m_DrawMode = drawMode; }
	void Dispose();
};

