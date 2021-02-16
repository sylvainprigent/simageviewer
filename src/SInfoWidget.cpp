/// \file SInfoWidget.cpp
/// \brief SInfoWidget class
/// \author Sylvain Prigent
/// \version 0.1
/// \date 2020

#include "SInfoWidget.h"


SInfoWidget::SInfoWidget(QWidget* parent) : QWidget(parent){

    QGridLayout* layout = new QGridLayout();
    this->setLayout(layout);

    QLabel *titleFile = new QLabel("File:", this);
    m_infoFile = new QLabel(this);

    QLabel *titleSize = new QLabel("Size (pixels):", this);
    m_infoSize = new QLabel(this);

    QLabel *titleResolution = new QLabel("Resolution:",this);
    m_infoResolution = new QLabel(this);

    QLabel *precisionTitle = new QLabel("Precision:", this);
    m_precisionInfo = new QLabel(this);

    layout->addWidget(titleFile, 0, 0);
    layout->addWidget(m_infoFile, 0, 1);
    layout->addWidget(titleSize, 1, 0);
    layout->addWidget(m_infoSize, 1, 1);
    layout->addWidget(titleResolution, 2, 0);
    layout->addWidget(m_infoResolution, 2, 1);
    layout->addWidget(precisionTitle, 3, 0);
    layout->addWidget(m_precisionInfo, 3, 1);

}

void SInfoWidget::setImage(SImage* image, QString filePath){
    m_image = image;
    m_imageFile = filePath;
    this->refreshInfo();
}

void SInfoWidget::refreshInfo(){

    QFileInfo f(m_imageFile);

    m_infoFile->setText(f.baseName());
    m_infoSize->setText( "x: " + QString::number(m_image->getSizeX()) + "\ny: "
                         + QString::number(m_image->getSizeY()) + "\nz: "
                         + QString::number(m_image->getSizeZ()) + "\nt: "
                         + QString::number(m_image->getSizeT()) + "\nc: "
                         + QString::number(m_image->getSizeC())  );
    m_infoResolution->setText( QString::number(double(m_image->getResX())) + QString("x")
                               + QString::number(double(m_image->getResY())) + "x"
                               + QString::number(double(m_image->getResZ())) + " "
                               + QString::fromStdString(m_image->getUnit()) + "\n" + QString::number(double(m_image->getResT())) + " seconds" );
    m_precisionInfo->setText(QString::number(m_image->getPrecision()) + " bits");
}

SInfoWidget::~SInfoWidget(){

}
