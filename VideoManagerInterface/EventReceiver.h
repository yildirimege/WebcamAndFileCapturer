#pragma once
#include "VideoManagerInterface.h"

using namespace System;
using namespace System::Drawing;
using namespace System::Threading;
using namespace VideoManagerLib;

/**
 * @brief Class that defines methods to handle events and manage threads.
 */
ref class EventReceiver
{
public:
	/**
	 * @brief Constructor for the EventReceiver class.
	 * @param videoManagerInterface The VideoManagerInterface instance to interact with the video manager.
	 */
	EventReceiver(VideoManagerWrapper::VideoManagerInterface^ videoManagerInterface)
		:m_videoManagerInterface(videoManagerInterface)
	{
		// Initialize web cam thread
		backgroundWorker_ReadWebCam = gcnew Thread(gcnew ThreadStart(this, &EventReceiver::task_ReadWebCam));
		backgroundWorker_ReadWebCam->Name = "ThreadReadWebCam";

		// Initialize read file thread 
		backgroundWorker_ReadFile = gcnew Thread(gcnew ThreadStart(this, &EventReceiver::task_ReadFile));
		backgroundWorker_ReadFile->Name = "ThreadReadFile";
	}

	/**
	* @brief Destructor for the EventReceiver class.
	* Aborts and cleans up the web cam and read file threads.
	*/
	~EventReceiver() {
		backgroundWorker_ReadWebCam->Abort();
		backgroundWorker_ReadFile->Abort();
	}

	/**
	 * @brief Task for reading frames from the web camera and drawing them to the control.
	 */
	void task_ReadWebCam()
	{
		while (true)
		{
			cv::Mat frame = Engine::instance()->CapturerManager()->GetFrame();
			m_videoManagerInterface->DrawCVImageToControl(frame);
		}
	}

	/**
	 * @brief Task for reading frames from a file and drawing them to the control.
	 */
	void task_ReadFile()
	{
		while (true)
		{
			cv::Mat frame = Engine::instance()->ReaderManager()->GetFrame();
			m_videoManagerInterface->DrawCVImageToControl(frame);
		}
	}

	/**
	 * @brief Event handler for changes in the engine state.
	 * @param newEngineState The new state of the video manager's engine.
	 */
	void OnEngineStateChanged(VideoManagerLib::EngineState newEngineState)
	{
		Console::WriteLine("Engine State Chnaged: {0}", (int)newEngineState);

		switch (Engine::instance()->GetEngineState())
		{
		case(VideoManagerLib::EngineState::READ_WEBCAM):
		{
			// Start Web Cam Thread
			if (backgroundWorker_ReadWebCam->ThreadState == ThreadState::Unstarted) {
				backgroundWorker_ReadWebCam->Start();
			}
			else if (backgroundWorker_ReadWebCam->ThreadState == ThreadState::Suspended) {
				backgroundWorker_ReadWebCam->Resume();
			}

			// Stop Read File Thread
			if (backgroundWorker_ReadFile->ThreadState == ThreadState::Running) {
				backgroundWorker_ReadFile->Suspend();
			}
			break;
		}
		case(VideoManagerLib::EngineState::STOP):
			// Stop Web Cam Thread
			if (backgroundWorker_ReadWebCam->ThreadState == ThreadState::Running)
			{
				backgroundWorker_ReadWebCam->Suspend();
			}

			// Stop Read File Thread
			if (backgroundWorker_ReadFile->ThreadState == ThreadState::Running)
			{
				backgroundWorker_ReadFile->Suspend();
			}
			break;

		case(VideoManagerLib::EngineState::READ_FILE):
			// Start Read File Thread
			if (backgroundWorker_ReadFile->ThreadState == ThreadState::Unstarted) {
				backgroundWorker_ReadFile->Start();
			}
			else if (backgroundWorker_ReadFile->ThreadState == ThreadState::Suspended) {
				backgroundWorker_ReadFile->Resume();
			}

			// Stop Web Cam Thread
			if (backgroundWorker_ReadWebCam->ThreadState == ThreadState::Running)
			{
				backgroundWorker_ReadWebCam->Suspend();
			}
			break;

		case(VideoManagerLib::EngineState::RELEASE):
			// Release threads
			if (backgroundWorker_ReadWebCam->ThreadState == ThreadState::Suspended) {
				backgroundWorker_ReadWebCam->Resume();
			}
			if (backgroundWorker_ReadWebCam->ThreadState == ThreadState::Running) {
				backgroundWorker_ReadWebCam->Abort();
			}

			// Release threads
			if (backgroundWorker_ReadFile->ThreadState == ThreadState::Suspended) {
				backgroundWorker_ReadFile->Resume();
			}
			if (backgroundWorker_ReadFile->ThreadState == ThreadState::Running) {
				backgroundWorker_ReadFile->Abort();
			}
			break;
		}
	}
private:
	VideoManagerWrapper::VideoManagerInterface^ m_videoManagerInterface; ///< The VideoManagerInterface instance.
	Thread^ backgroundWorker_ReadWebCam; ///< Thread for reading frames from the web camera.
	Thread^ backgroundWorker_ReadFile; ///< Thread for reading frames from a file.
};