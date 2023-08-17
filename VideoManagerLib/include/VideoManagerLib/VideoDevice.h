#pragma once

#include "VideoManagerLib/stdafx.h"

#include <unordered_map>

namespace VideoManagerLib
{
	/**
	* @brief Class representing a video device used for capturing video streams.
	*/
	class VideoDevice
	{
	public:
		/**
		* @brief Constructor for the VideoDevice class.
		*/
		VideoDevice();

		/**
		* @brief Destructor for the VideoDevice class.
		*/
		~VideoDevice();

		/**
		* @brief Initialize the video devices and COM.
		* @return True if initialization is successful, false otherwise.
		*/
		bool InitializeDevices();

		/**
		 * @brief Close active video devices.
		 */
		void CloseDevices();

		/**
		* @brief Select a video device by its index.
		* @brief Selects 5th device (First one after default MEdiaLooks devices) by default.
		* @param index The index of the device to select.
		* @return True if selection is successful, false otherwise.
		*/
		bool SelectDeviceByIndex(int index = 5);


		/**
		* @brief Get a pointer to the raw IMFDevice.
		* @return The pointer to the raw IMFDevice.
		*/
		const CComPtr<IMFDevice>& GetIMFDevice();

	private:
		CComPtr<IMFDevice> m_cpLive; /**< Pointer to the live video device. */
		std::unordered_map<int, std::string> m_deviceList; /**< Map of device indices and their names. */
		int m_selectedDeviceIndex = 5;  /**< Index of the currently selected device. */
	};
}