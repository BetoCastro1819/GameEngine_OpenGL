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
	_renderer = new Renderer(_window);

	if (!_renderer->Start())
		return false;

	_time = new Time();

	return OnStart();
}

bool GameBase::Stop()
{
	cout << "GameBase::Stop()" << endl;
	OnStop();
	if (_renderer != NULL)
	{
		_renderer->Stop();
		delete _renderer;
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

		_renderer->SetClearColor(0.2f, 0.3f, 0.3f, 0.0f);
		_renderer->RecalculateFragmentDepth();
		_renderer->ClearBuffer();
		OnUpdate(_time->GetDeltaTime()); // Draws triangle... for now
		_renderer->SwapBuffers();
		_window->PollEvents();
	}
}
