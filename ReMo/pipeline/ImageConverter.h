#ifndef __DESKTOPSTREAMER_IMAGECONVERTER_H__
#define __DESKTOPSTREAMER_IMAGECONVERTER_H__

#include <vector>
#include <cstdint>
#include <memory>
#include <iostream>

#include "AbstractImageSampler.h"

namespace remo
{
	class ImageConverter
	{
		private:
			std::vector<char> dstBuffer;
			int dstWidth;
			int dstHeight;

			std::unique_ptr<AbstractImageSampler> sampler;
		public:
			ImageConverter(
				int targetWidth,
				int targetHeight);

			void convert(
				std::uint8_t ** srcBuffer, 
				int srcWidth, 
				int srcHeight);

			std::vector<char> & getImage ( void );

			template<class ImgSamplerType>
			void setImageSampler ( void )
			{
				if(!std::is_base_of<AbstractImageSampler, ImgSamplerType>::value)
				{
					std::cerr << "ImageConverter: Invalid image sampler type used. Sampler not changed" << std::endl;
					return;
				}

				sampler = std::make_unique<ImgSamplerType>();
			}

		private:
			void remapIndexes(
				int i, int j, 
				int dstWidth_, int dstHeight_, 
				int originalWidth, int originalHeight, 
				int &iResult, int &jResult);
	};
}

#endif
