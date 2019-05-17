#include "GameBase.h"
#include "TypeDefs.h"

GameBase::GameBase(const int& width, const int& height, const char* name) {
	_screenWidth = width;
	_screenHeight = height;
	_windowName = name;
}

GameBase::~GameBase() {
	if (m_time != NULL)
		delete m_time;

	if (m_camera != NULL)
		delete m_camera;
}

bool GameBase::Start()
{
	m_window = new Window(_screenHeight, _screenWidth, _windowName);
	if (!m_window->Start()) {
		return false;
	}

	m_renderer = new Renderer(m_window);
	if (!m_renderer->Start()) {
		return false;
	}

	m_camera = new Camera(m_renderer, m_window);
	m_time = new Time();

	return OnStart();
}

bool GameBase::Stop()
{
	OnStop();

	if (m_renderer != NULL) {
		m_renderer->Stop();
		delete m_renderer;
	}

	if (m_window != NULL) {
		m_window->Stop();
		delete m_window;
	}
	return true;
}

void GameBase::Loop()
{
	while (!m_window->ShouldClose()) {

		m_time->UpdateTime();

		m_renderer->SetClearColor(0.2f, 0.3f, 0.3f, 0.0f);
		m_renderer->RecalculateFragmentDepth();
		m_renderer->ClearBuffer();
		OnUpdate(m_time->GetDeltaTime()); // Draws triangle... for now
		m_renderer->SwapBuffers();
		m_window->PollEvents();
	}
}
