#include "VideoManagerLib/VideoFormat.h"

#include "VideoManagerLib/VideoDevice.h"
#include "VideoManagerLib/Log.h"
#include "VideoManagerLib/Utilities.h"

namespace VideoManagerLib
{
	VideoFormat::VideoFormat(CComPtr<IMFDevice> device)
		: m_cpFormat(device)
		, m_selectedFormatIndex(1)
	{
	}

	VideoFormat::~VideoFormat()
	{
	}

	bool VideoFormat::SelectFormatByIndex(int index)
	{
		LOG_COLOR(L_INFO, BLUE) << "Choosed video device input format by index: %i" << index;

		CComBSTR formatName;
		M_VID_PROPS vidProps = {};

		//Probe selected format
		HRESULT hr = m_cpFormat->FormatVideoGetByIndex(eMFT_Input, index - 1, &vidProps, &formatName);
		hr = m_cpFormat->FormatVideoSet(eMFT_Input, &vidProps);
		if (FAILED(hr))
		{
			LOG_COLOR(L_ERROR, RED) << "Can't  set this input format, continuing";
			return false;
		}

		return true;
	}

	bool VideoFormat::PrepareFormatList()
	{
		//Enumerate device input video formats
		int formatsCount = 0;
		HRESULT hr = m_cpFormat->FormatVideoGetCount(eMFT_Input, &formatsCount);
		if (formatsCount == 0)
		{
			LOG_COLOR(L_ERROR, RED) << "Input device doesn't support input formats.";
			return false;
		}

		CComBSTR formatName;
		M_VID_PROPS vidProps = {};

		LOG_COLOR(L_INFO, GREEN) << "Video delice input formats:";
		
		// Collect input formats
		for (int i = 0; i < formatsCount; i++)
		{
			m_cpFormat->FormatVideoGetByIndex(eMFT_Input, i, &vidProps, &formatName);
			LOG_COLOR(L_INFO, GREEN) << "%i: " << i + 1 << "%s" << Utilities::BstrToStdString(formatName);

			m_formatList[i] = Utilities::BstrToStdString(formatName);
		}

		return true;
	}
	
	const CComPtr<IMFFormat>& VideoFormat::GetIMFFormat()
	{
		return m_cpFormat;
	}
}