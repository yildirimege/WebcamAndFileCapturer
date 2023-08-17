#pragma once

#include "stdafx.h"

namespace VideoManagerLib
{
    /**
    * @brief Utility class containing various helper functions for video management.
    */
	class Utilities
	{
    public:
        /**
        * @brief Get an OpenCV image (cv::Mat) from an MFFrame.
        * @param frame The input MFFrame.
        * @return The corresponding OpenCV image.
        */
        static cv::Mat GetCVImageFromMFFrame(const CComPtr<IMFFrame>& frame)
        {
            M_AV_PROPS avProps;
            long lAudioSamples;
            frame->MFAVPropsGet(&avProps, &lAudioSamples);
            int frameWidth = avProps.vidProps.nWidth;
            int frameHeight = std::abs(avProps.vidProps.nHeight);

            // Clone frame to RGB32
            CComPtr<IMFFrame> cloneFrame;
            frame->MFClone(&cloneFrame, eMFrameClone::eMFC_Reference, eMFCC::eMFCC_RGB32);

            // Get bytes from frame
            MF_VID_PTR _pVidPtr;
            cloneFrame->MFVideoGetBytesEx(&_pVidPtr);

            // Get plane 0 (Colored Channel for RGB32)
            LPBYTE pbVideo0 = (LPBYTE)_pVidPtr.lpVideoPlanes[0];
            cv::Mat outputImage(frameHeight, frameWidth, CV_8UC4, pbVideo0);

            return outputImage;
        }

        /**
        * @brief Convert a BSTR to a std::string.
        * @param bstr The input BSTR to be converted.
        * @param dst The destination std::string to store the converted result.
        * @param cp The code page for the conversion (default is CP_UTF8).
        * @return The destination std::string.
        */
        static std::string& BstrToStdString(const BSTR bstr, std::string& dst, int cp = CP_UTF8)
        {
            if (!bstr)
            {
                // Define NULL functionality. Clear the target string..
                dst.clear();
                return dst;
            }

            // Request content length in single-chars through a terminating
            // nullchar in the BSTR. Note: BSTRs support embedded nullchars,
            // so this will only convert through the first nullchar.
            int res = WideCharToMultiByte(cp, 0, bstr, -1, NULL, 0, NULL, NULL);
            if (res > 0)
            {
                dst.resize(res);
                WideCharToMultiByte(cp, 0, bstr, -1, &dst[0], res, NULL, NULL);
            }
            else
            {    // No content. Clear the target string.
                dst.clear();
            }
            return dst;
        }

        /**
        * @brief Convert a BSTR to a std::string with temporary storage.
        * @param bstr The input BSTR to be converted.
        * @param cp The code page for the conversion (default is CP_UTF8).
        * @return The converted std::string.
        */
        static std::string BstrToStdString(BSTR bstr, int cp = CP_UTF8)
        {
            std::string str;
            BstrToStdString(bstr, str, cp);
            return str;
        }

        /**
        * @brief Converts a UTF-8 encoded string to a BSTR (OLE string).
        *
        * This function converts a UTF-8 encoded C++ string to a BSTR (OLE string),
        * which is suitable for use with COM interfaces.
        *
        * @param str The UTF-8 encoded C++ string to convert.
        * @return A BSTR containing the converted string, or nullptr on failure.
        * @note The caller is responsible for freeing the returned BSTR using `SysFreeString`.
        * @note It is the caller's responsibility to handle memory allocation errors.
        */
        static BSTR ConvertToBSTR(const std::string& str)
        {
            int len = MultiByteToWideChar(CP_UTF8, 0, str.c_str(), -1, nullptr, 0);
            if (len == 0) {
                // Handle error
                return nullptr;
            }

            BSTR bstr = SysAllocStringLen(nullptr, len - 1);
            if (!bstr) {
                // Handle memory allocation error
                return nullptr;
            }

            MultiByteToWideChar(CP_UTF8, 0, str.c_str(), -1, bstr, len);
            return bstr;
        }
	};
}