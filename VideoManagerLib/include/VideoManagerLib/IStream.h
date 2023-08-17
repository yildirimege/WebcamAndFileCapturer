#pragma once

#include <opencv2/opencv.hpp>
#include <MFormats.h>
#include <atlcomcli.h>

namespace VideoManagerLib
{
    /**
    * @brief Abstract interface for capturing frames from a video source.
    */
    class IStream
    {
    public:
        IStream() = default;

        /**
        * @brief Destructor for the ICapturer interface.
        */
        virtual ~IStream() {}

        /**
        * @brief Initialize the frame capturer.
        */
        virtual void Init() = 0;

        /**
        * @brief Release resources used by the frame capturer.
        */
        virtual void Release() = 0;

        /**
        * @brief Get a single frame from the video source.
        * @return The captured frame as a cv::Mat.
        */
        virtual cv::Mat GetFrame() = 0;
    };
}
