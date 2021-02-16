/// \file SHistogramWidget.h
/// \brief SHistogramWidget class
/// \author Sylvain Prigent
/// \version 0.1
/// \date 2020

#pragma once

#include <QtWidgets>

#include "simageviewerExport.h"

/// \class SHistogramWidget
/// \brief Class to display an image histogram
class SIMAGEVIEWER_EXPORT SHistogramWidget : public QWidget{

    Q_OBJECT

public:
    SHistogramWidget(QWidget* parent = nullptr);
    ~SHistogramWidget();

signals:
    void minMaxChanged(float min, float max);

public:
    void setHistogram(int* histogram, float min, float max);
    void drawHistogram(int* histogram, float min, float max);
    float min();
    float max();
    void setSliders(float minVal, float maxVal);

protected slots:
    void sliderChanged(int);

protected:
    QImage* m_histImage;
    QLabel *m_histLabel;
    QSlider *m_minSlider;
    QSlider *m_maxSlider;
    int* m_hist;
    float m_min;
    float m_max;
    QLabel *m_minLabel;
    QLabel *m_maxLabel;

};
