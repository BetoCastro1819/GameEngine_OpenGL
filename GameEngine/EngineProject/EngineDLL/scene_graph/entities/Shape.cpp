#include "Shape.h"
#include "../../components/Transform.h"
#include "../../components/Material.h"
#include "../../rendering/Renderer.h"


Shape::Shape(Renderer* renderer) : Entity(renderer) {
	_dispose = false;
	_drawMode = 0;

	_vrtxs = NULL;
	_colorVrtx = NULL;
}

Shape::~Shape() {
	Dispose();
}

void Shape::Update(float deltaTime) {
	if (_mat) {
		BindMaterial();
	}

	m_renderer->UpdateModelMatrix(GetTransform()->GetWorldMatrix());
	m_renderer->UpdateMVP();
	//_renderer->SendTransformationToShader(_matrixID);
	// Bind Vertex Buffer (Attribute index = 0)
	m_renderer->BindBuffer(_bufferData, _vrtxCount, 0, 3, _drawMode);
	// Bind Color Buffer (Attribute index = 1)
	//_renderer->BindBuffer(_colorBufferData, _colorVrtxCount, 1, _drawMode);
}

void Shape::SetVertices(float* vrtxs, const int& count) {
	_vrtxs = vrtxs;
	_vrtxCount = count;
	_dispose = true;
	_bufferData = m_renderer->GenBuffer(_vrtxs, _vrtxCount * 3 * sizeof(float));
}

void Shape::SetColorBufferData(float* colorVrtxs, const int& count) {
	_colorVrtx = colorVrtxs;
	_colorVrtxCount = count;
	_colorBufferData = m_renderer->GenBuffer(_colorVrtx, _colorVrtxCount * 3 * sizeof(float));
}

void Shape::Dispose() {
	if (_dispose) {
		std::cout << "Shape::~Shape()" << std::endl;

		m_renderer->DeleteBuffers(_bufferData);
		m_renderer->DeleteVrtxArray();
		m_renderer->DeleteProgram(_programID);

		/* TODO: Program crashes when TextureShape calls this Destructor */
		if (_vrtxs != nullptr) {
			//delete[] _vrtxs;
			_vrtxs = NULL;
		}
		if (_colorVrtx != nullptr) {
			delete[] _colorVrtx;
			_colorVrtx = NULL;
		}
		_dispose = false;
	}
}

void Shape::SetMaterial(Material* material) {
	_mat = material;
	_programID = _mat->LoadShaders("SimpleVertexShader.txt", "SimpleFragmentShader.txt");
	//_matrixID = _renderer->SetMatrixID(_programID);
}

void Shape::BindMaterial() {
	m_renderer->BindMaterial(_programID);
}