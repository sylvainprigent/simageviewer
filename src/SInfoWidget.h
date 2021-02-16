/// \file SInfoWidget.h
/// \brief SInfoWidget class
/// \author Sylvain Prigent
/// \version 0.1
/// \date 2020

#pragma once

#include <QtWidgets>

#include "simageviewerExport.h"

#include <simage>

/// \class SInfoWidget
/// \brief Class to display an image metadata
class SIMAGEVIEWER_EXPORT SInfoWidget : public QWidget{

    Q_OBJECT

public:
    SInfoWidget(QWidget* parent = nullptr);
    ~SInfoWidget();

public slots:
    void setImage(SImage* image, QString filePath);
    void refreshInfo();

protected:
    SImage* m_image;
    QString m_imageFile;

    QLabel *m_infoFile;
    QLabel *m_infoSize;
    QLabel *m_infoResolution;
    QLabel *m_precisionInfo;
};
