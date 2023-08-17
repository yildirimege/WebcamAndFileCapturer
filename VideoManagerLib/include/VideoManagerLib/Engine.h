#pragma once

#include "VideoManagerLib/Capturer.h"
#include "VideoManagerLib/VideoFormat.h"
#include "VideoManagerLib/VideoDevice.h"
#include "VideoManagerLib/Reader.h"
#include "VideoManagerLib/ReaderDevice.h"

namespace VideoManagerLib
{
	/**
	* @brief Enumeration representing possible states of the video manager's engine.
	*/
	enum class EngineState : size_t
	{
		DEFAULT = 0,
		READ_WEBCAM,
		READ_FILE,
		STOP,
		RELEASE
	};

	/**
	* @brief Singleton Class responsible for managing the video manager's engine and associated objects.
	*/
	class Engine
	{
	public:
		/**
        * @brief Constructor.
        * Initializes the engine state and associated managers.
        */
		Engine();

		/**
		* @brief Destructor.
		* Cleans up associated resources, including managers and capturer.
		*/
		~Engine();

		/**
		* @brief Get the instance of the Engine singleton.
		* @return Pointer to the Engine instance.
		*/
		static Engine* instance();

		/**
		* @brief Initialize the engine and its associated objects.
		*/
		void Init();

		/**
		* @brief Opens Webcam.
		* 
		*/
		bool OpenCamera();

		/**
		* @brief Closes webcam.
		*/
		bool CloseCamera();

		/**
		* @brief Set the current state of the video manager's engine.
		* @param engineState The new engine state to set.
		*/
		void SetEngineState(EngineState engineState);

		/**
		* @brief Get the current state of the video manager's engine.
		* @return The current engine state.
		*/
		EngineState GetEngineState();

		/**
		* @brief Get the capturer manager responsible for video frame capture.
		* @return Pointer to the Capturer instance.
		*/
		Capturer* CapturerManager();

		/**
		* @brief Get the video device manager responsible for managing video devices.
		* @return Pointer to the VideoDevice instance.
		*/
		VideoDevice* DeviceManager();

		/**
		* @brief Get the video format manager responsible for managing video formats.
		* @return Pointer to the VideoFormat instance.
		*/
		VideoFormat* FormatManager();

		/**
		* @brief Returns a pointer to local Reader object
		* 
		* @return Pointer to local Reader object.
		*/
		Reader* ReaderManager();

		/**
		* @brief Returns a pointer to local ReaderDevice object
		* 
		* \return Pointer to local ReaderDevice object
		*/
		ReaderDevice* ReaderDeviceManager();

	private:
		Engine(const Engine&) = delete;
		Engine& operator=(const Engine&) = delete;

	private:
		static Engine* m_instance; ///< Singleton instance of the Engine.

		EngineState m_engineState; ///< Current state of the video manager's engine.

		VideoDevice* m_deviceManager; ///< Current state of the video manager's engine.
		VideoFormat* m_formatManager; ///< Pointer to the video format manager.
		ReaderDevice* m_ReaderDevice;

		Capturer* m_CapturerManager; ///< Pointer to the video capturer.
		Reader* m_Reader;
	};
}
