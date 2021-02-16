/// \file SHistogramView.cpp
/// \brief SHistogramView class
/// \author Sylvain Prigent
/// \version 0.1
/// \date 2020

#include "SHistogramWidget.h"


SHistogramWidget::SHistogramWidget(QWidget* parent) : QWidget(parent){

    m_histImage = new QImage(256, 100, QImage::Format_RGB32);

    m_histLabel = new QLabel(this);
    m_histLabel->setMinimumWidth(100);

    // sliders
    m_minSlider = new QSlider(Qt::Horizontal, this);
    m_minSlider->setRange(0, 255);
    m_minSlider->setFixedWidth(256);
    m_maxSlider = new QSlider(Qt::Horizontal, this);
    m_maxSlider->setRange(0, 255);
    m_maxSlider->setValue(255);
    m_maxSlider->setFixedWidth(256);


    this->setMaximumWidth(256);

    QGridLayout *layout = new QGridLayout();
    layout->setContentsMargins(0,0,0,0);
    layout->addWidget(m_histLabel, 0, 0, 1, 2);
    m_minLabel = new QLabel(this);
    m_maxLabel = new QLabel(this);
    layout->addWidget(m_minLabel, 1, 0, 1, 1, Qt::AlignLeft);
    layout->addWidget(m_maxLabel, 1, 1, 1, 1, Qt::AlignRight);

    layout->addWidget(m_minSlider, 2, 0, 1, 2);
    layout->addWidget(m_maxSlider, 3, 0, 1, 2);

    connect(m_minSlider, SIGNAL(valueChanged(int)), this, SLOT(sliderChanged(int)));
    connect(m_maxSlider, SIGNAL(valueChanged(int)), this, SLOT(sliderChanged(int)));

    this->setLayout(layout);

}

SHistogramWidget::~SHistogramWidget(){

}

void SHistogramWidget::setHistogram(int* histogram, float min, float max){
    m_min = min;
    m_max = max;
    m_hist = histogram;

    drawHistogram(histogram, min, max);
}

void SHistogramWidget::drawHistogram(int* histogram, float min, float max){

    // draw labels
    m_minLabel->setText(QString::number(double(m_min)));
    m_maxLabel->setText(QString::number(double(m_max)));

    // get the hitogram max to normalize
    int vmax = histogram[0];
    for (int i = 1 ; i < 256 ; i++){
        if (histogram[i] > vmax){
            vmax = histogram[i];
        }
    }

    int v;
    for (int i = 0 ; i < 256 ; i++){

        v = 100*histogram[i]/vmax;
        v = 100-v;
        for (int j = 0 ; j < v ; j++){
            m_histImage->setPixel(i,j, qRgb(40,40,40));
        }
        for (int j = v ; j < 100 ; j++){

            m_histImage->setPixel(i,j, qRgb(200,200,200));
        }
    }


    int minNorm = int(255*min/m_max);
    int maxNorm = int(255*max/m_max);
    for (int j = 0 ; j < 100 ; j++){
        m_histImage->setPixel(minNorm,j, qRgb(0,0,200));
        m_histImage->setPixel(maxNorm,j, qRgb(200,0,0));
    }

    m_histLabel->setPixmap(QPixmap::fromImage(*m_histImage));

}

void SHistogramWidget::sliderChanged(int){

    if (m_minSlider->value() > m_maxSlider->value()){
        m_minSlider->setValue(m_maxSlider->value());
    }
    if (m_maxSlider->value() < m_minSlider->value()){
        m_maxSlider->setValue(m_minSlider->value());
    }

    this->drawHistogram(m_hist, m_minSlider->value()*m_max/255, m_maxSlider->value()*m_max/255);

    emit minMaxChanged(m_minSlider->value()*m_max/255, m_maxSlider->value()*m_max/255);
}

void SHistogramWidget::setSliders(float minVal, float maxVal){
    qDebug() << "set min slider to " << int(255*minVal/m_max);
    qDebug() << "set max slider to " << int(255*maxVal/m_max);
    m_minSlider->setValue(int(255*minVal/m_max));
    m_maxSlider->setValue(int(255*maxVal/m_max));
}

float SHistogramWidget::min(){
    return m_minSlider->value()*m_max/255;
}

float SHistogramWidget::max(){
    return m_maxSlider->value()*m_max/255;
}
