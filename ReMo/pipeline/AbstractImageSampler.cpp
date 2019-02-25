#include "AbstractImageSampler.h"

#include <algorithm>

namespace remo
{
  AbstractImageSampler::AbstractImageSampler( )
  {

  }

  AbstractImageSampler::~AbstractImageSampler( )
  {

  }

  void NearImageSampler::samplePixels(
    std::uint8_t** srcBuffer,
    int srcWidth,
    int srcHeight,
    int i,
    int j,
    std::uint8_t& r,
    std::uint8_t& g,
    std::uint8_t& b )
  {
    int index = (( i * srcWidth ) + j ) * 4;
    r = srcBuffer[0][index + 2];
    g = srcBuffer[0][index + 1];
    b = srcBuffer[0][index];
    //### Not used here but necessary for the others samplers
    ( void ) srcHeight;
  }

  void LinearImageSampler::samplePixels(
    std::uint8_t** srcBuffer,
    int srcWidth,
    int srcHeight,
    int i,
    int j,
    std::uint8_t& r,
    std::uint8_t& g,
    std::uint8_t& b )
  {
    int topI = std::min < int >( std::max < int >( 0, i - 1 ), srcHeight );
    int topJ = j;
    int topIndex = (( topI * srcWidth ) + topJ ) * 4;

    int bottomI = std::min < int >( std::max < int >( 0, i + 1 ), srcHeight );
    int bottomJ = j;
    int botIndex = (( bottomI * srcWidth ) + bottomJ ) * 4;

    int leftI = i;
    int leftJ = std::min < int >( std::max < int >( 0, j - 1 ), srcWidth );
    int lefIndex = (( leftI * srcWidth ) + leftJ ) * 4;

    int rightI = i;
    int rightJ = std::min < int >( std::max < int >( 0, j + 1 ), srcWidth );
    int rigIndex = (( rightI * srcWidth ) + rightJ ) * 4;

    int cenIndex = (( i * srcWidth ) + j ) * 4;

    std::uint8_t topR, topG, topB;
    std::uint8_t botR, botG, botB;
    std::uint8_t lefR, lefG, lefB;
    std::uint8_t rigR, rigG, rigB;
    std::uint8_t cenR, cenG, cenB;

    topR = srcBuffer[0][topIndex + 2];
    topG = srcBuffer[0][topIndex + 1];
    topB = srcBuffer[0][topIndex];
    botR = srcBuffer[0][botIndex + 2];
    botG = srcBuffer[0][botIndex + 1];
    botB = srcBuffer[0][botIndex];
    lefR = srcBuffer[0][lefIndex + 2];
    lefG = srcBuffer[0][lefIndex + 1];
    lefB = srcBuffer[0][lefIndex];
    rigR = srcBuffer[0][topIndex + 2];
    rigG = srcBuffer[0][rigIndex + 1];
    rigB = srcBuffer[0][rigIndex];
    cenR = srcBuffer[0][topIndex + 2];
    cenG = srcBuffer[0][cenIndex + 1];
    cenB = srcBuffer[0][cenIndex];

    r = static_cast<std::uint8_t>
    (
      static_cast<float>(topR + botR + lefR + rigR + cenR) / 5.0f
    );

    g = static_cast<std::uint8_t>
    (
      static_cast<float>(topG + botG + lefG + rigG + cenG) / 5.0f
    );

    b = static_cast<std::uint8_t>
    (
      static_cast<float>(topB + botB + lefB + rigB + cenB) / 5.0f
    );
  }
}
