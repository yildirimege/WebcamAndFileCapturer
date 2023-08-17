#pragma once

#include "VideoManagerLib/stdafx.h"
#include "VideoManagerLib/VideoDevice.h"

namespace VideoManagerLib
{
	/**
	* @brief Class representing video format selection and management.
	*/
	class VideoFormat
	{
	public:
		/**
		* @brief Constructor for the VideoFormat class.
		* @param device The pointer to the IMFDevice associated with the format.
		*/
		VideoFormat(CComPtr<IMFDevice> device);

		/**
		* @brief Destructor for the VideoFormat class.
		*/
		~VideoFormat();

		/**
		* @brief Select a video format by its index.
		* @param index The index of the format to select.
		* @return True if selection is successful, false otherwise.
		*/
		bool SelectFormatByIndex(int index = 1);

		/**
		* @brief Populate the list of available video formats.
		* @return True if format list preparation is successful, false otherwise.
		*/
		bool PrepareFormatList();

		/**
		* @brief Get a pointer to the raw IMFFormat.
		* @return The pointer to the raw IMFFormat.
		*/
		const CComPtr<IMFFormat>& GetIMFFormat();

	private:
		CComQIPtr<IMFFormat> m_cpFormat; /**< Pointer to the video format. */
		std::unordered_map<int, std::string> m_formatList;  /**< Map of format indices and their names. */
		int m_selectedFormatIndex = 1;  /**< Map of format indices and their names. */

	};
}