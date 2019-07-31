#include "LevelCompleteScreen.h"

LevelCompleteScreen::LevelCompleteScreen(Renderer* renderer, Material* material) : Entity(renderer) {
	m_texture = new Texture("levelComplete.bmp");
	m_texture->SetTextureDimensions(640, 480);
	m_texture->SetFrameDimensions(640, 480);
	m_texture->SetNumberOfFramesPerRow(1);
	m_texture->SetNumberOfFramesPerColumn(1);

	m_sprite = new Sprite(renderer, material, m_texture);
	m_sprite->SetFrameID(0);
}


LevelCompleteScreen::~LevelCompleteScreen() {
	if (m_texture != nullptr) delete m_texture;
	if (m_sprite != nullptr) delete m_sprite;
}

void LevelCompleteScreen::Display() {
	m_sprite->SetModelMatrix(m_ModelMat);
	m_sprite->Update(.0f);
}
