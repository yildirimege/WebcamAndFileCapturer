#pragma once

#include "VideoManagerLib/IStream.h"
#include "VideoManagerLib/stdafx.h"
#include "VideoManagerLib/VideoDevice.h"
#include "VideoManagerLib/VideoFormat.h"

namespace VideoManagerLib
{
	/**
	* @brief Class responsible for capturing video frames from a video device.
	*/
	class Capturer : IStream
	{
	public:
		/**
		* @brief Constructor.
		* Initializes the capturer and associated resources.
		* @param device Pointer to the VideoDevice instance to capture from.
		* @param format Pointer to the VideoFormat instance specifying the capture format.
		*/
		Capturer(VideoDevice* device, VideoFormat* format);

		/**
		* @brief Destructor.
		* Releases resources associated with the capturer and uninitializes COM.
		*/
		~Capturer() override;

		/**
		* @brief Initializes the capturer by obtaining the IMFSource interface from the VideoDevice.
		*/
		void Init() override;

		/**
		* @brief Releases resources associated with the capturer and closes devices.
		*/
		void Release() override;

		/**
		* @brief Captures a single video frame from the source.
		* @note The captured frame is converted to a cv::Mat.
		* @return cv::Mat containing the captured video frame, or an empty cv::Mat if no frame is captured.
		*/
		cv::Mat GetFrame() override;

	private:
		VideoDevice* m_videoDevice; ///< Pointer to the VideoDevice instance.
		VideoFormat* m_videoFormat; ///< Pointer to the VideoFormat instance.

		CComQIPtr<IMFSource> m_cpSource;  ///< COM interface pointer for the video source.
		CComQIPtr<IMFReceiver> m_cpReceiverPreview; ///< COM interface pointer for the preview receiver.
		CComPtr<IMFFrame> m_frame; ///< COM interface pointer for the video frame.
		
	};
}