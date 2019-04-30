#include "GameBase.h"
#include "TypeDefs.h"

GameBase::GameBase(const int& width, const int& height, const char* name) {
	_screenWidth = width;
	_screenHeight = height;
	_windowName = name;
}

GameBase::~GameBase() {
	if (_time != NULL)
		delete _time;
}

bool GameBase::Start()
{
	cout << "GameBase::Start()" << endl;	
	_window = new Window(_screenHeight, _screenWidth, _windowName);
	if (!_window->Start())
		return false;
	m_renderer = new Renderer(_window);

	if (!m_renderer->Start())
		return false;

	_time = new Time();

	return OnStart();
}

bool GameBase::Stop()
{
	cout << "GameBase::Stop()" << endl;
	OnStop();
	if (m_renderer != NULL)
	{
		m_renderer->Stop();
		delete m_renderer;
	}
	if (_window != NULL)
	{
		_window->Stop();
		delete _window;
	}
	return true;
}

void GameBase::Loop()
{
	cout << "GameBase::Loop()" << endl;

	while (!_window->ShouldClose()) {

		_time->UpdateTime();

		m_renderer->SetClearColor(0.2f, 0.3f, 0.3f, 0.0f);
		m_renderer->RecalculateFragmentDepth();
		m_renderer->ClearBuffer();
		OnUpdate(_time->GetDeltaTime()); // Draws triangle... for now
		m_renderer->SwapBuffers();
		_window->PollEvents();
	}
}
