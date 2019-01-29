#include "ImageConverter.h"

namespace remo
{
	ImageConverter::ImageConverter(
		int targetWidth,
		int targetHeight)
	: dstWidth(targetWidth)
	, dstHeight(targetHeight)
	{
		int imgSize = dstHeight * (((dstWidth * 3) + 3) / 4) * 4;
		dstBuffer.resize(imgSize);

		setImageSampler<NearImageSampler>();
	}

	void ImageConverter::convert(
		std::uint8_t ** srcBuffer, 
		int srcWidth, 
		int srcHeight)
	{
		// Build webstreamer readable image		
		#pragma omp parallel
		{
			#pragma omp for schedule(static)
		  for (int i = 0; i < dstHeight; i++) 
			{
		    for (int j = 0; j < dstWidth; j++) 
				{
		      int tempI = ((i * dstWidth) + j);
		      int index = tempI * 3;

					int frameI, frameJ;
					remapIndexes(i, j, dstWidth, dstHeight, srcWidth, srcHeight, frameI, frameJ);

					std::uint8_t r, g, b;

					sampler->samplePixels(srcBuffer, srcWidth, srcHeight, frameI, frameJ, r, g, b);

					dstBuffer[index] = r;
					dstBuffer[index + 1] = g;
					dstBuffer[index + 2] = b;
		    }
		  }
		}
	}

	void ImageConverter::remapIndexes(
		int i, int j, 
		int distWidth, int distHeight,
		int originalWidth, int originalHeight, 
		int &iResult, int &jResult)
	{
		float iFlt = static_cast<float>(i);
		float jFlt = static_cast<float>(j);
	
		float dstWFlt = static_cast<float>(distWidth);
		float dstHFlt = static_cast<float>(distHeight);

		float srcWFlt = static_cast<float>(originalWidth);
		float srcHFlt = static_cast<float>(originalHeight);

		float fltIRsult = (iFlt * srcHFlt) / dstHFlt;
		float fltJRsult = (jFlt * srcWFlt) / dstWFlt;

		iResult = static_cast<int>(fltIRsult);
		jResult = static_cast<int>(fltJRsult);

		iResult = std::min<int>(std::max<int>(0, iResult), originalHeight);
		jResult = std::min<int>(std::max<int>(0, jResult), originalWidth);
	}

	std::vector<char> & ImageConverter::getImage()
	{
		return dstBuffer;
	}
}
