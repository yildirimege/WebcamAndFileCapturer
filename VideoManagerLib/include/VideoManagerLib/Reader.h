#pragma once

#include "VideoManagerLib/stdafx.h"
#include "VideoManagerLib/ReaderDevice.h"
#include <MFormats.h>

namespace VideoManagerLib
{
    /**
    * @brief Reader class for capturing frames from a media file.
    */
    class Reader
    {
    public:
        /**
        * @brief Constructor.
        * @param readerDevice Pointer to the ReaderDevice instance to use for reading frames.
        */
        Reader(ReaderDevice* readerDevice);

        /**
        * @brief Destructor.
        */
        ~Reader();

        /**
        * @brief Opens a media file for reading frames.
        * @param fileName The path to the media file to open.
        * @return `true` if the file was successfully opened, otherwise `false`.
        */
        bool OpenFile(const std::string& fileName);

        /**
        * @brief Retrieves a frame from the opened media file.
        * @return A cv::Mat containing the retrieved frame data, or an empty cv::Mat if no frame is available.
        */
        cv::Mat GetFrame();

    private:
        ReaderDevice* m_readerDevice;   // Pointer to the ReaderDevice instance

        CComPtr<IMFFrame> m_frame;      // Pointer to the captured frame

        std::string m_fileName;         // Path to the currently opened media file

        M_AV_PROPS m_avProps;           // Video props structure for frame capture

        bool m_atLastFrame;
    };
}
