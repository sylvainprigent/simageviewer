/// \file SQImageDisplay.h
/// \brief SQImageDisplay class
/// \author Sylvain Prigent
/// \version 0.1
/// \date 2021

#pragma once

#include <QtWidgets>

#include "simageviewerExport.h"

#include <simage>
#include <simageio>

/// \class sciSlicesView
/// \brief Widget to display 5D image slice by slice using sliders
class SIMAGEVIEWER_EXPORT SQImageDisplay : public QWidget{
    Q_OBJECT

public:
    SQImageDisplay(bool showZoomButtons = true, QWidget *parent = nullptr);

signals:
    void zoomInClicked();
    void zoomOutClicked();
    void normalSizeClicked();
    void scrollHorizontalChanged(int);
    void scrollVerticalChanged(int);

public slots:
    void scrollHorizontalValue(int value);
    void scrollVerticalValue(int value);

public slots:
    void zoomIn();
    void zoomOut();
    void normalSize();

public:
    void setImage(QImage *newImage);

private:
    void scaleImage(double factor);
    void adjustScrollBar(QScrollBar *scrollBar, double factor);

private:
    QWidget *createToolBar();

private:
    bool m_isImage;
    QLabel *m_imageLabel;
    QScrollArea *m_scrollArea;
    double m_scaleFactor;
    QImage* m_inputImage;

};
