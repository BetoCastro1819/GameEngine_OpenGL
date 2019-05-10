#pragma once
#include "Entity.h"
#include "Material.h"

class ENGINEDLL_API Shape : public Entity {
protected:
	Material* m_material;
	unsigned int m_programID;

	unsigned int m_vertexBuffer;
	float* m_VtxArr;
	int m_numberOfVertices;

	float* m_ColorVtxArr;
	int m_ColorVtxCount;

	bool m_Dispose;
	int m_DrawMode;
	void SetDrawMode(int drawMode) { m_DrawMode = drawMode; }

public:
	Shape(Renderer* renderer);
	~Shape();
	virtual void SetMaterial(Material* material);
	void Draw() override;

	void SetVertices(float* vertices, const int& numberOfVertices);
	void BindMaterial();
	void Dispose();
};

