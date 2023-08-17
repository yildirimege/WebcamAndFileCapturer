#pragma once

#include "VideoManagerLib/stdafx.h"


namespace VideoManagerLib
{
	/**
	* @brief The ReaderDevice class represents a device for reading media files.
	*
	* This class is responsible for initializing and managing the media file reader.
	*/
	class ReaderDevice
	{
	public:
		/**
		* @brief Constructor.
		*/
		ReaderDevice();

		/**
		* @brief Destructor.
		*/
		~ReaderDevice();

		/**
		* @brief Initializes the devices for media file reading.
		*
		* This function initializes the media file reader device.
		*
		* @return True if the initialization is successful, false otherwise.
		*/
		bool InitializeDevices();

		/**
		* @brief Get the underlying IMFReader instance.
		*
		* This function returns a reference to the underlying IMFReader instance used for reading media files.
		*
		* @return A const reference to the IMFReader instance.
		*/
		const CComPtr<IMFReader>& GetIMFReader();

	private:
		CComPtr<IMFReader> m_cpReader;	/*!< A pointer to the IMFReader instance. */
	};
}