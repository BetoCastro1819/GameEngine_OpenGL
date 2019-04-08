#pragma once
#include "Entity.h"
#include "Material.h"

class ENGINEDLL_API Shape : public Entity {
protected:
	Material* m_Material;
	
	unsigned int m_ProgramID;

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

	void SetMaterial(Material* material);
	void Dispose();
	void BindMaterial();
	void SetDrawMode(int drawMode) { m_DrawMode = drawMode; }
};

