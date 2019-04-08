#include "Shape.h"

Shape::Shape(Renderer* renderer) : Entity(renderer) {
	m_Dispose = false;
	m_DrawMode = 0;

	m_VtxArr = NULL;
	m_ColorVtxArr = NULL;
}


Shape::~Shape() {
	Dispose();
}

void Shape::Draw() {
	if (m_Material) {
		BindMaterial();
	}

	m_Renderer->UpdateModelMatrix(m_ModelMat);
	m_Renderer->UpdateMVP();
	//_renderer->SendTransformationToShader(_matrixID);
	// Bind Vertex Buffer (Attribute index = 0)
	m_Renderer->BindBuffer(m_BufferData, m_VtxCount, 0, 3, m_DrawMode);
	// Bind Color Buffer (Attribute index = 1)
	//_renderer->BindBuffer(_colorBufferData, _colorVrtxCount, 1, _drawMode);
}

void Shape::SetVertices(float* vrtxs, const int& count) {
	m_VtxArr = vrtxs;
	m_VtxCount = count;
	m_Dispose = true;
	m_BufferData = m_Renderer->GenBuffer(m_VtxArr, m_VtxCount * 3 * sizeof(float));
}

void Shape::SetColorBufferData(float* colorVrtxs, const int& count) {
	m_ColorVtxArr = colorVrtxs;
	m_ColorVtxCount = count;
	m_ColorBufferData = m_Renderer->GenBuffer(m_ColorVtxArr, m_ColorVtxCount * 3 * sizeof(float));
}

void Shape::Dispose() {
	if (m_Dispose) {
		std::cout << "Shape::~Shape()" << std::endl;

		m_Renderer->DeleteBuffers(m_BufferData);
		m_Renderer->DeleteVrtxArray();
		m_Renderer->DeleteProgram(m_ProgramID);

		/* TODO: Program crashes when TextureShape calls this Destructor */
		if (m_VtxArr != nullptr) {
			//delete[] _vrtxs;
			m_VtxArr = NULL;
		}
		if (m_ColorVtxArr != nullptr) {
			delete[] m_ColorVtxArr;
			m_ColorVtxArr = NULL;
		}
		m_Dispose = false;
	}
}

void Shape::SetMaterial(Material* material) {
	m_Material = material;
	m_ProgramID = m_Material->LoadShaders("SimpleVertexShader.txt", "SimpleFragmentShader.txt");
	//_matrixID = _renderer->SetMatrixID(_programID);
}

void Shape::BindMaterial() {
	m_Renderer->BindMaterial(m_ProgramID);
}