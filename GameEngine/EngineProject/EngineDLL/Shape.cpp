#include "Shape.h"

Shape::Shape(Renderer* renderer) : Entity(renderer) {
	_dispose = false;
	_drawMode = 0;
}


Shape::~Shape() {
	Dispose();
}

void Shape::Draw() {
	if (_mat) {
		BindMaterial();
	}

	_renderer->UpdateModelMatrix(_modelMatrix);
	_renderer->UpdateMVP();
	_renderer->SendTransformationToShader(_matrixID);
	// Bind Vertex Buffer (Attribute index = 0)
	_renderer->BindBuffer(_bufferData, _vrtxCount, 0, _drawMode);
	// Bind Color Buffer (Attribute index = 1)
	_renderer->BindBuffer(_colorBufferData, _colorVrtxCount, 1, _drawMode);
}

void Shape::SetVertices(float* vrtxs, const int& count) {
	_vrtxs = vrtxs;
	_vrtxCount = count;
	_dispose = true;
	_bufferData = _renderer->GenBuffer(_vrtxs, _vrtxCount * 3 * sizeof(float));
}

void Shape::SetColorBufferData(float* colorVrtxs, const int& count) {
	_colorVrtx = colorVrtxs;
	_colorVrtxCount = count;
	_colorBufferData = _renderer->GenBuffer(_colorVrtx, _colorVrtxCount * 3 * sizeof(float));
}

void Shape::Dispose() {
	if (_dispose) {
		_renderer->DeleteBuffers(_bufferData);

		if (_vrtxs) {
			delete[] _vrtxs;
			_vrtxs = NULL;
		}
		if (_colorVrtx) {
			delete[] _colorVrtx;
			_colorVrtx = NULL;
		}
		_dispose = false;
	}
}

void Shape::SetMaterial(Material* material) {
	_mat = material;
	_programID = _mat->LoadShaders("SimpleVertexShader.txt", "SimpleFragmentShader.txt");
	_matrixID = _renderer->SetMatrixID(_programID);
}

void Shape::BindMaterial() {
	_renderer->BindMaterial(_programID);
}