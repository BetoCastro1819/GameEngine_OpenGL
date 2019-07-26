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

void Shape::Update(float deltaTime) {
	if (m_material) {
		BindMaterial();
	}

	m_renderer->UpdateModelMatrix(m_ModelMat);
	m_renderer->UpdateMVP();
}

void Shape::SetVertices(float* vrtxs, const int& count) {
	m_VtxArr = vrtxs;
	m_numberOfVertices = count;
	m_Dispose = true;
	m_vertexBuffer = m_renderer->GenBuffer(m_VtxArr, m_numberOfVertices * 3 * sizeof(float));
}

void Shape::Dispose() {
	if (m_Dispose) {
		std::cout << "Shape::~Shape()" << std::endl;

		m_renderer->DeleteBuffers(m_vertexBuffer);
		m_renderer->DeleteVrtxArray();
		m_renderer->DeleteProgram(m_programID);

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
	m_material = material;
	m_programID = m_material->LoadShaders("SimpleVertexShader.txt", "SimpleFragmentShader.txt");
}

void Shape::BindMaterial() {
	m_renderer->BindMaterial(m_programID);
}