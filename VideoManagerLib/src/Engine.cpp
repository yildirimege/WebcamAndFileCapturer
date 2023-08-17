#include "VideoManagerLib/Engine.h"
#include "VideoManagerLib/Log.h"

namespace VideoManagerLib
{
	Engine* Engine::m_instance = nullptr;

	Engine::Engine() 
		: m_engineState(EngineState::DEFAULT) 
		, m_deviceManager(nullptr)
		, m_formatManager(nullptr)
		, m_ReaderDevice(nullptr)
		, m_CapturerManager(nullptr)
		, m_Reader(nullptr)
	{
	}

	Engine::~Engine()
	{
		if (m_formatManager)
		{
			delete m_formatManager;
		}

		if (m_deviceManager)
		{
			delete m_deviceManager;
		}

		if (m_CapturerManager)
		{
			delete m_CapturerManager;
		}

		if (m_Reader)
		{
			delete m_Reader;
		}

		if (m_ReaderDevice) { delete m_ReaderDevice; }

		if (m_instance) { delete m_instance; }
	}

	Engine* Engine::instance()
	{
		if (m_instance == nullptr)
		{
			m_instance = new Engine;
		}
		return m_instance;
	}

	void Engine::Init()
	{
		 //Initialize video devices
		m_deviceManager = new VideoDevice();
		m_deviceManager->InitializeDevices();


		// Initialize video format
		m_formatManager = new VideoFormat(m_deviceManager->GetIMFDevice());
		m_formatManager->PrepareFormatList();
		m_formatManager->SelectFormatByIndex(1);

		// Initialize Video Capturer.
		m_CapturerManager = new Capturer(m_deviceManager, m_formatManager);

		// Initialize Reader Device.
		m_ReaderDevice = new ReaderDevice();
		m_ReaderDevice->InitializeDevices();

		// Initialize File Reader.
		m_Reader = new Reader(m_ReaderDevice);
	}

	bool Engine::OpenCamera()
	{
		m_deviceManager->SelectDeviceByIndex();
		return true;
	}

	bool Engine::CloseCamera()
	{
		m_deviceManager->CloseDevices();
		return true;
	}

	void Engine::SetEngineState(EngineState engineState)
	{
		this->m_engineState = engineState;
	}

	EngineState Engine::GetEngineState()
	{
		return this->m_engineState;
	}

	Capturer* Engine::CapturerManager()
	{
		return this->m_CapturerManager;
	}

	VideoDevice* Engine::DeviceManager()
	{
		return m_deviceManager;
	}

	VideoFormat* Engine::FormatManager()
	{
		return m_formatManager;
	}

	Reader* Engine::ReaderManager()
	{
		return m_Reader;
	}

	ReaderDevice* Engine::ReaderDeviceManager()
	{
		return m_ReaderDevice;
	}
}