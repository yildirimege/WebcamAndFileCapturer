#include "VideoManagerLib/Reader.h"
#include "VideoManagerLib/Utilities.h"
#include "VideoManagerLib/Log.h"
#include <MFormats.h>
#include <atlcomcli.h>
namespace VideoManagerLib
{
    Reader::Reader(ReaderDevice* readerDevice)
        : m_readerDevice(readerDevice)
        , m_fileName("")
        , m_atLastFrame(false)
        , m_frame()
        , m_avProps()
    {
    }

    Reader::~Reader()
    {
        ::CoUninitialize();
        m_frame = NULL;
        m_fileName = "";
    }

    bool Reader::OpenFile(const std::string& fileName)
    {
        BSTR fileName_BSTR = Utilities::ConvertToBSTR(fileName);

       
        CComBSTR cbsProps{ _T("") };
        //Open File
        HRESULT hr = m_readerDevice->GetIMFReader()->ReaderOpen(fileName_BSTR, cbsProps);
        if (FAILED(hr))
        {
            LOG_COLOR(L_ERROR, RED) << "ERROR: Can't open this media file\n";
            return false;
        }
        return true;
    }

    cv::Mat Reader::GetFrame()
    {
        HRESULT hr;
        M_TIME mTime = {};
        m_frame = NULL;

        if (!m_atLastFrame)
        {
            // If current frame is not the last frame, continue capturing the next frame.

            // Get next frame
            hr = m_readerDevice->GetIMFReader()->SourceFrameConvertedGetByTime(&m_avProps, -1, -1, &m_frame, CComBSTR(L""));
            if (FAILED(hr))
            {
                LOG_COLOR(L_ERROR, RED) << "ERROR: Couldn't get bytes of Video file.\n";
            }

            // Check if current frame is the last frame
            M_TIME mTime = {};
            m_atLastFrame = ((m_frame->MFTimeGet(&mTime)), (mTime.eFFlags & eMFF_Last) != 0);
        }
        else
        {
            // If the current frame is the last frame, rewind and start from the first frame.

            // Get the first frame
            m_readerDevice->GetIMFReader()->SourceFrameConvertedGetByNumber(&m_avProps, 0, -1, &m_frame, CComBSTR(L""));
            m_atLastFrame = false; // We are no longer in the last frame.
        }

        if (!m_frame)
        {
            return cv::Mat();
        }

        return Utilities::GetCVImageFromMFFrame(m_frame);
    }
}
