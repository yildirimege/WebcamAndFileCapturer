#pragma once

#include <opencv2/opencv.hpp>
#include <MFormats.h>
#include <atlcomcli.h>

namespace VideoManagerLib
{
	/**
	* @brief Class responsible for managing frames and frame properties.
	*/
	class FrameManager
	{
	public:
		/**
		* @brief Constructor for the FrameManager class.
		* Initializes frame properties and the current COM frame.
		*/
		FrameManager();

		/**
		* @brief Get the width of the frames.
		* @return Width of the frames.
		*/
		int getWidth() const;

		/**
		* @brief Get the height of the frames.
		* @return Height of the frames.
		*/
		int getHeight() const;

		/**
		* @brief Set the width of the frames.
		* @param frameWidth The width to set.
		*/
		void setWidth(const int frameWidth);

		/**
		* @brief Set the height of the frames.
		* @param frameHeight The height to set.
		*/
		void setHeight(const int frameHeight);

		/*void GetOutputMat();
		cv::Mat SetOutputMat(cv::Mat);*/

		/**
		* @brief Convert the current frame to an OpenCV cv::Mat.
		* @return The OpenCV cv::Mat representation of the current frame.
		*/
		cv::Mat toCvMat();

		/**
		* @brief Get the reference to the current COM frame.
		* @return Reference to the current COM frame.
		*/
		CComPtr<IMFFrame>& GetCurrentFrame();

		/**
		* @brief Reset the current COM frame to nullptr.
		* @note Needs to be called after capturing each frame.
		*/
		void ResetCurrentFrame();

	private:
		int m_frameWidth;
		int m_frameHeight;
		CComPtr<IMFFrame> m_currentFrameCOM;
		cv::Mat outputMat;
	};
}