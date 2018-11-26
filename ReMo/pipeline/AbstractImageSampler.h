#ifndef __DESKTOPSTREAMER_ABSTRACTIMAGESAMPLER_H__
#define __DESKTOPSTREAMER_ABSTRACTIMAGESAMPLER_H__

#include <cstdint>

namespace remo
{
	class AbstractImageSampler
	{
		public:
			AbstractImageSampler();
			~AbstractImageSampler();

			virtual void samplePixels(
				std::uint8_t ** srcBuffer,
				int srcWidth,
				int srcHeight,
				int i, 
				int j, 
				std::uint8_t & r, 
				std::uint8_t & g, 
				std::uint8_t & b) = 0;
	};

	class NearImageSampler : public AbstractImageSampler
	{
		public:
			void samplePixels(
				std::uint8_t ** srcBuffer,
				int srcWidth,
				int srcHeight,
				int i, 
				int j, 
				std::uint8_t & r, 
				std::uint8_t & g, 
				std::uint8_t & b);
	};

	class LinearImageSampler : public AbstractImageSampler
	{
		public:
			void samplePixels(
				std::uint8_t ** srcBuffer,
				int srcWidth,
				int srcHeight,
				int i, 
				int j, 
				std::uint8_t & r, 
				std::uint8_t & g, 
				std::uint8_t & b);
	};
}

#endif
