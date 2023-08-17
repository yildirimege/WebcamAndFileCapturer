#include "VideoManagerLib/Frame.h"

namespace VideoManagerLib
{
	FrameManager::FrameManager() : m_frameHeight(0), m_frameWidth(0), m_currentFrameCOM(nullptr)
	{
		_tprintf(_T("Created FrameManager.\n"));
	}

	int FrameManager::getWidth() const
	{
		return this->m_frameWidth;
	}

	int FrameManager::getHeight() const
	{
		return this->m_frameHeight;
	}

	void FrameManager::setWidth(const int frameWidth)
	{
		this->m_frameWidth = frameWidth;
	}

	void FrameManager::setHeight(const int frameHeight)
	{
		this->m_frameHeight = frameHeight;
	}

	cv::Mat FrameManager::toCvMat()
	{
		return cv::Mat();
	}

	CComPtr<IMFFrame>& FrameManager::GetCurrentFrame()
	{
		return m_currentFrameCOM;
	}

	void FrameManager::ResetCurrentFrame()
	{
		m_currentFrameCOM = NULL;
	}
}