#pragma once
#include "Exports.h"

class ENGINEDLL_API Texture {
private:
	unsigned int m_textureID;
	unsigned int m_textureWidth;
	unsigned int m_textureHeight;
	unsigned int m_frameWidth;
	unsigned int m_frameHeight;
	unsigned int m_framesPerRow;
	unsigned int m_framesPerColumn;

	unsigned int Load_BMP(const char* filePath);

public:
	Texture(const char* filePath);
	~Texture();

	void SetTextureDimensions(unsigned int textureWidth, unsigned int textureHeight);
	void SetFrameDimensions(unsigned int frameWidth, unsigned int frameHeight);
	void SetNumberOfFramesPerRow(unsigned int numOfFrames);
	void SetNumberOfFramesPerColumn(unsigned int numOfFrames);

	unsigned int GetTextureID() { return m_textureID; }
	unsigned int GetWidth() { return m_textureWidth; }
	unsigned int GetHeight() { return m_textureHeight; }
	unsigned int GetFrameWidth() { return m_frameWidth; }
	unsigned int GetFrameHeight() { return m_frameHeight; }
	unsigned int GetFramesPerRow() { return m_framesPerRow; }
	unsigned int GetFramesPerColumn() { return m_framesPerColumn; }
};

