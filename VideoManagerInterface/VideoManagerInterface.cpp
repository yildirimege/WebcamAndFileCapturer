#include "pch.h"

#include "VideoManagerInterface.h"
#include "EventSource.h"
#include "EventReceiver.h"
#include <VideoManagerLib/Capturer.h>

#include <msclr\marshal_cppstd.h>

namespace VideoManagerWrapper
{
	VideoManagerInterface::VideoManagerInterface()
		: m_eventSource(gcnew EventSource())
		, m_eventReceiver(gcnew EventReceiver(this))
	{
	}

	VideoManagerInterface::~VideoManagerInterface()
	{ 
		this->!VideoManagerInterface();
	}

	EngineState VideoManagerInterface::GetEngineState()
	{
		return CastToNativeState<VideoManagerLib::EngineState, EngineState >(Engine::instance()->GetEngineState());
	}

	void VideoManagerInterface::SetEngineState(EngineState newEngineState)
	{
		auto CastedState  = CastToNativeState<EngineState, VideoManagerLib::EngineState >(newEngineState);
		Engine::instance()->SetEngineState(CastedState);
		m_eventSource->ChangeState(CastedState);
	}

	void VideoManagerInterface::InitEngine()
	{
		Engine::instance()->Init();
	}

	void VideoManagerInterface::ReleaseEngine()
	{
		m_eventSource->ChangeState(VideoManagerLib::EngineState::RELEASE);
	}

	void VideoManagerInterface::InitEnvents()
	{
		m_eventSource->OnEngineStateChanged += gcnew EngineStateChangedEventHandler(m_eventReceiver, &EventReceiver::OnEngineStateChanged);
	}

	inline void VideoManagerInterface::GetOwnerShipControl(System::Windows::Forms::Control^ control)
	{
		m_control = control;
	}

	inline void VideoManagerInterface::DrawCVImageToControl(cv::Mat& colorImage)
	{ 
		if (!colorImage.empty())
		{
			System::Drawing::Graphics^ graphics = m_control->CreateGraphics();
			System::IntPtr ptr(colorImage.ptr());
			System::Drawing::Bitmap^ b = gcnew System::Drawing::Bitmap(colorImage.cols, colorImage.rows, colorImage.step, System::Drawing::Imaging::PixelFormat::Format32bppRgb, ptr);
			System::Drawing::RectangleF rect(0, 0, m_control->Width, m_control->Height);
			graphics->DrawImage(b, rect);
			delete graphics;
		}
	}

	bool VideoManagerInterface::OpenFile(String^ filePath)
	{
		std::string standardString = msclr::interop::marshal_as<std::string>(filePath);
		return Engine::instance()->ReaderManager()->OpenFile(standardString);
	}

	bool VideoManagerInterface::OpenCamera()
	{
		return Engine::instance()->OpenCamera();
	}

	bool VideoManagerInterface::CloseCamera()
	{
		return Engine::instance()->CloseCamera();
	}
}
