
#include "VideoManagerLib/VideoDevice.h"
#include "VideoManagerLib/Log.h"
#include "VideoManagerLib/Utilities.h"

namespace VideoManagerLib
{
	VideoDevice::VideoDevice()
		: m_cpLive()
		, m_selectedDeviceIndex(5)
	{
	}

	VideoDevice::~VideoDevice()
	{
		CloseDevices();
	}

	bool VideoDevice::InitializeDevices()
	{
		::CoUninitialize();

		//Initialize COM
		HRESULT hr = CoInitializeEx(NULL, COINIT_MULTITHREADED);
		if (FAILED(hr))
		{
			LOG_COLOR(L_ERROR, RED) << "Can't initialize COM.";
			return false;
		}

		// Create MFLive instance
		hr = m_cpLive.CoCreateInstance(__uuidof(MFLive));
		if (FAILED(hr))
		{
			LOG_COLOR(L_ERROR, RED) << "Can't create MFLive instance.";
			return false;
		}

		return true;
	}

	void VideoDevice::CloseDevices()
	{
		m_cpLive->DeviceClose();
	}

	bool VideoDevice::SelectDeviceByIndex(int index)
	{
		// Search device by index
		std::unordered_map<int, std::string>::const_iterator deviceListIterator = m_deviceList.find(index);

		if (deviceListIterator == m_deviceList.end()) 
		{
			LOG_COLOR(L_ERROR, RED) << "Device not found by index: %i " << index;
		}

		// Update Selected Index
		m_selectedDeviceIndex = index;

		//Probe selected live device
		HRESULT hr = m_cpLive->DeviceSet(eMFDT_Video, m_selectedDeviceIndex - 1, CComBSTR(L""));
		if (FAILED(hr))
		{
			LOG_COLOR(L_ERROR, RED) << "Can't use this input device for capturing: %s" << m_deviceList[m_selectedDeviceIndex];
			return false;
		}

		LOG_COLOR(L_INFO, GREEN) << "Device selected: %s." << m_deviceList[m_selectedDeviceIndex];
		return true;
	}

	const CComPtr<IMFDevice>& VideoDevice::GetIMFDevice()
	{
		return m_cpLive;
	}
}