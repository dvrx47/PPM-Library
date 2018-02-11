#ifndef colors_h
#define colors_h

#include <stdint.h>
#include <cstddef>
#include <string>
#include <iostream>
#include <fstream>

#define PPM_HEADER "P3"
#define PPM_COLORS "255"


union ColorRGB{

	#if __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
    struct{
      uint8_t offset;
      uint8_t red;
      uint8_t green;
      uint8_t blue;
    };
  	#else
    struct{
      uint8_t blue;
      uint8_t green;
      uint8_t red;
      uint8_t offset;
    };
	#endif

    //0xOORRGGBB
	uint32_t hexColor; 

  ColorRGB() : red{0}, green{0}, blue{0} {};
  ColorRGB( uint32_t color) : hexColor{ color } {};
  ColorRGB( uint8_t red, uint8_t green, uint8_t blue ) : red{red}, green{green}, blue{blue} { };

  void operator = (const uint32_t & new_color){
    hexColor = new_color;
  }

  friend std::ostream & operator << ( std::ostream & stream, ColorRGB & color ){
    stream  << "(" 
            << static_cast<uint32_t>(color.red) << ", " 
            << static_cast<uint32_t>(color.green) << ", " 
            << static_cast<uint32_t>(color.blue) << ")";
    return stream;
  }  
};


union ColorHSV{

	#if __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
    struct{
      uint16_t hue;
      uint8_t saturation;
      uint8_t value;
    };
  #else
    struct{
      uint8_t value;
      uint8_t saturation;
      uint16_t hue;
    };
	#endif

	  //0xHHHHSSVV
	uint32_t hexColor; 

  ColorHSV() : hue{0}, saturation{0}, value{0} {};
  ColorHSV( uint32_t color) : hexColor{ color } { };
  ColorHSV( uint16_t hue, uint8_t saturation, uint8_t value ) : 
    hue{hue}, 
    saturation{saturation}, 
    value{value} 
    { };

  void operator = (const uint32_t new_color){
    hexColor = new_color;
  }

  friend std::ostream & operator << ( std::ostream& stream, const ColorHSV & color){
    stream  << "(" 
            << static_cast<uint32_t>(color.hue) << ", " 
            << static_cast<uint32_t>(color.saturation) << ", "
            << static_cast<uint32_t>(color.value) << ")";
    return stream;
  }

  ColorRGB & getRgb();
};


template<class ColorType> struct Image{
  std::size_t width;
  std::size_t height;
  ColorType ** pix_map;
  
  Image(std::size_t width, std::size_t height) : width{width}, height{height} {
    pix_map = new ColorType*[width];
    for(size_t i = 0; i < width; ++i){
      pix_map[i] = new ColorType[height];
    }
  };

  ColorType * operator [](std::size_t index) const {
    return pix_map[index];
  }
};


void saveImage( const Image<ColorRGB> & picture, const std::string file_name );
void saveImage( const Image<ColorHSV> & picture, const std::string file_name );

#endif