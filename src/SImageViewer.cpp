/// \file SImageViewer.cpp
/// \brief SImageViewer class
/// \author Sylvain Prigent
/// \version 0.1
/// \date 2021

#include <SImageViewer.h>

SImageViewer::SImageViewer() : QWidget()
{

}

SImageViewer::SImageViewer(const QString& imageFile) : QWidget()
{
    this->setImageFile(imageFile);
}

void SImageViewer::setImageFile(const QString& imageFile)
{
    m_imageFile = imageFile;
    this->render();
}
