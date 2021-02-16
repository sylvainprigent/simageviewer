/// \file SImageViewer.h
/// \brief SImageViewer class
/// \author Sylvain Prigent
/// \version 0.1
/// \date 2021

#pragma once

#include <QtWidgets>
#include "simageviewerExport.h"

/// \class SImageViewer
/// \brief Interface of a image viewer using the SImageViewer framework
class SIMAGEVIEWER_EXPORT SImageViewer : public QWidget{

    Q_OBJECT

public:
    SImageViewer();
    SImageViewer(const QString& imageFile);

protected:
    /// \brief This method must implement the initialization of the viewer when a new image is set
    virtual void render() = 0;

public:
    void setImageFile(const QString& imageFile);

protected:
    QString m_imageFile;
};
