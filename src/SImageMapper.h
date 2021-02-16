/// \file SImageMapper.h
/// \brief SImageMapper class
/// \author Sylvain Prigent
/// \version 0.1
/// \date 2019

#pragma once

#include "simageviewerExport.h"

#include <QImage>
#include <simage>

/// \class SImageMapper
/// \brief Class load image into Qt data structures
class SIMAGEVIEWER_EXPORT SImageMapper{

public:
    SImageMapper();

public:
    void map2DGray(int* colormap, float minVal, float maxVal);

public:
    void setImage(SImage* image);
    QImage* mappedImage();

protected:
    SImage* m_image;
    QImage* m_mappedImage;
};
