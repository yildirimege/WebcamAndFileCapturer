#pragma once

#include <type_traits>
#include <opencv2/opencv.hpp>
#include <VideoManagerLib/Engine.h>


using namespace System;
using namespace System::Drawing;
using namespace System::Windows::Forms;
using namespace VideoManagerLib;

ref class EventSource;
ref class EventReceiver;

namespace VideoManagerWrapper 
{
	/**
	* @brief: Enum class which states Engine States.	
	*/
	public enum class EngineState : size_t
	{
		DEFAULT = 0,
		READ_WEBCAM,
		READ_FILE,
		STOP,
		RELEASE
	};

	/**
	* @brief: Wraps VideoManagerLib as a Managed Library. Used in Upper level Threading and Drawing to Picture Box.
	*/
	public ref class VideoManagerInterface
	{
    public:
		/**
		* @brief Default constructor of VideoManagerInterface.
		* @brief Initializes EventSource and EventReceiver Observer objects.
		*/
		VideoManagerInterface();

		/**
		* @brief Default Destructor of VideoManagerInterface.
		* @brief Invokes a finalizer and cleans up managed resources.
		*/
		~VideoManagerInterface();

		/**
		* @brief: Finalizer to clean up managed resources.
		*/
		!VideoManagerInterface() {}

		/**
		* @brief Gets engine's current state.
		* 
		* @return currentEngineState
		*/
		EngineState GetEngineState();

		/**
		* @brief Sets engine's current state.
		* @param newEngineState: new Engine State.
		*/
		void SetEngineState(EngineState newEngineState);

		/**
		* Initializes Engine (Creates Capturer, device manager and format manager.)
		*/
		void InitEngine();

		/**
		* @brief Sets Engine's State to RELEASE, which will stop all threads.
		* @brief WARNING: Only meant to be called at the end of the program.
		*/
		void ReleaseEngine();

		/**
		* @brief Craetes new event handler (OnEngineStateChanged) and subscribes the EventSource to it.
		*/
		void InitEnvents();

		/**
		* @brief Gives control of the given form to the Interface.
		* 
		* @param control: Control of the current form.
		*/
		void GetOwnerShipControl(System::Windows::Forms::Control^ control);

		/**
		* @brief Draws given image to the current controlled Form's picturebox.
		* 
		* @param colorImage: cv::Mat object retrieved from a source. (In our case; webcam or video file)
		*/
		void DrawCVImageToControl(cv::Mat& colorImage);

		/**
		* @brief Opens a file for further operations (readi write etc.)
		* 
		* @param filePath Path of the file (given by FileDialogBox)
		* 
		* @return boolean value corresponding to success of opening the file.
		*/
		bool OpenFile(String^ filePath);

		/**
		* @brief Opens Webcam (Called each time Capture From Webcam Button is called.
		* 
		* @return Boolean value corresponding to success of opening the webcam.
		*/
		bool OpenCamera();

		/**
		* @brief Closes webcam
		* 
		* @return Boolean  value corresponding to success of closing the webcam.
		*/
		bool CloseCamera();

		/**
		* @brief Template function to statically cast the source type to destination type.
		* @brief This function calls static_cast. Any undefined behaviour will lead to runtime errors.
		* 
		* @param val: Object of SOURCE type
		* 
		* @return input object converted to DESTINATION type.
		*/
		template<typename E_SOURCE, typename E_DESTINATION>
		constexpr auto CastToNativeState(E_SOURCE val)
		{
			return static_cast<E_DESTINATION>(val);
		}

	private:
		System::Windows::Forms::Control^ m_control;
		EventSource^ m_eventSource;
		EventReceiver^ m_eventReceiver;

	};
}
