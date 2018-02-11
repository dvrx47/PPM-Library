#include "colors.h"


void saveImage( const Image<ColorRGB> & picture, const std::string file_name ){
    std::ofstream file;
    file.open( file_name );
    file << PPM_HEADER << std::endl;
    file << picture.width << " " << picture.height << std::endl;
    file << PPM_COLORS << std::endl;
    for(int h = picture.height-1; h >= 0; --h ){
        for(int w = 0; w < picture.width; ++w){
            file << static_cast<uint32_t>( picture[w][h].red ) << " ";
            file << static_cast<uint32_t>( picture[w][h].green) << " ";
            file << static_cast<uint32_t>( picture[w][h].blue) << " ";
        }
        file << std::endl;
    }
    file.close();
}


ColorRGB & ColorHSV::getRgb(){
    ColorRGB & res = *(new ColorRGB());

    int i;
    int f, p, q, t;
    if( saturation == 0 ) {
        res.red = res.green = res.blue = 255*value/100;
        return res;
    }
    
    int h = hue*100/60;  
    i = h - h%100;
    f = h - i;
    p = value * ( 100 - saturation )/100;
    q = value * ( 100 - saturation*f/100)/100;
    t = value * ( 100 - saturation * ( 100 - f )/100 )/100;
    i /= 100;

    switch( i ) {
        case 0:
                res.red = 255*value/100;
                res.green = 255*t/100;
                res.blue = 255*p/100;
            break;
        
        case 1:
                res.red = 255*q/100;
                res.green = 255*value/100;
                res.blue = 255*p/100;
            break;
        
        case 2:
                res.red = 255*p/100;
                res.green = 255*value/100;
                res.blue = 255*t/100;
            break;
        
        case 3:
                res.red = 255*p/100;
                res.green = 255*q/100;
                res.blue = 255*value/100;
            break;
        
        case 4:
                res.red = 255*t/100;
                res.green = 255*p/100;
                res.blue = 255*value/100;
            break;
        
        case 5:
                res.red = 255*value/100;
                res.green = 255*p/100;
                res.blue = 255*q/100;
            break;
    }

    return res;
}