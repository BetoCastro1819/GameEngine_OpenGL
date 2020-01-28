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

	m_physicsManager = PhysicsManager::getInstance();
	m_physicsManager->start(glm::vec3(0.0f, GRAVITY, 0.0f), 8u);

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

	if (m_physicsManager != NULL) {
		m_physicsManager->stop();
		m_physicsManager->deleteInstance();
	}

	return true;
}

void GameBase::Loop()
{
	m_renderer->SetClearColor(0.8f, 0.8f, 0.8f, 0.0f);
	
	while (!m_window->ShouldClose()) {

		m_time->UpdateTime();
		float deltaTime = m_time->GetDeltaTime();

		m_renderer->RecalculateFragmentDepth();
		m_renderer->ClearBuffer();
		m_window->PollEvents();

		OnUpdate(deltaTime);
		m_renderer->SwapBuffers();

		m_physicsManager->simulate(deltaTime);
		m_physicsManager->fetchSimulationResults();
	}
}
