#include "VideoManagerLib/Capturer.h"
#include "VideoManagerLib/Log.h"
#include "VideoManagerLib/Utilities.h"

#include <MFormats.h>

#include <string>
#include <iostream>

namespace VideoManagerLib
{
	Capturer::Capturer(VideoDevice* device, VideoFormat* format)
		: m_videoDevice(device)
		, m_videoFormat(format)
		, m_cpSource{}
		, m_cpReceiverPreview{}
		, m_frame{}
	{	
		Init();
	}

	Capturer::~Capturer()
	{
		Release();
		::CoUninitialize();
	}

	void Capturer::Init()
	{
		//Initialize source
		m_cpSource = CComQIPtr<IMFSource>(m_videoDevice->GetIMFDevice());
	}

	void Capturer::Release()
	{
		
	}

	cv::Mat Capturer::GetFrame()
	{
		m_frame = NULL;
		M_AV_PROPS avProps = {};

		//Get frames one by one 
		HRESULT hr = m_cpSource->SourceFrameConvertedGet(&avProps, -1, &m_frame, CComBSTR(L""));

		if (!m_frame)
		{
			return cv::Mat();
		}
		
		// Convet to cv::Mat
		return Utilities::GetCVImageFromMFFrame(m_frame);
	}

}