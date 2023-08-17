#include "VideoManagerLib/ReaderDevice.h"
#include "VideoManagerLib/Log.h"


VideoManagerLib::ReaderDevice::ReaderDevice()
	: m_cpReader()
{
}

VideoManagerLib::ReaderDevice::~ReaderDevice()
{
}

bool VideoManagerLib::ReaderDevice::InitializeDevices()
{
	::CoUninitialize();

	HRESULT hr = m_cpReader.CoCreateInstance(__uuidof(MFReader));
	if (FAILED(hr))
	{
		LOG_COLOR(L_ERROR, RED) << "Can't initialize MFReader instance.";
		return false;
	}
	return true;
}

const CComPtr<IMFReader>& VideoManagerLib::ReaderDevice::GetIMFReader()
{
	return m_cpReader;
}
