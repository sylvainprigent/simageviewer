/// \file SImageMapper.cpp
/// \brief SImageMapper class
/// \author Sylvain Prigent
/// \version 0.1
/// \date 2019

#include "SImageMapper.h"

#include <QDebug>

SImageMapper::SImageMapper()
{

}

void SImageMapper::setImage(SImage* image)
{
    m_image = image;
    m_mappedImage = new QImage(int(m_image->getSizeX()), int(m_image->getSizeY()), QImage::Format_RGB32);
}

QImage* SImageMapper::mappedImage()
{
    return m_mappedImage;
}

void SImageMapper::map2DGray(int* colormap, float minVal, float maxVal)
{
    float value;
    int intVal;
    unsigned int sx = unsigned(m_image->getSizeX());
    unsigned int sy = unsigned(m_image->getSizeY());
    float* buffer = dynamic_cast<SImageFloat*>(m_image)->getBuffer();

    for ( unsigned y  = 0 ; y < sy ; y++){
        for ( unsigned x  = 0 ; x < sx ; x++){

            value = buffer[ y + sy*x];
            intVal = int(255*(value-minVal)/(maxVal-minVal));
            if (intVal > 255){
                intVal = 255;
            }
            if (intVal < 0){
                intVal = 0;
            }

            QRgb color = qRgb(colormap[3*intVal+0], colormap[3*intVal+1], colormap[3*intVal+2]);
            m_mappedImage->setPixel(int(x), int(y), color);
        }
    }
}
