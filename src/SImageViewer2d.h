/// \file SImageViewer2d.h
/// \brief SImageViewer2d class
/// \author Sylvain Prigent
/// \version 0.1
/// \date 2021

#pragma once

#include "SImageViewer.h"
#include "simageviewerExport.h"

#include "SColormaps.h"
#include "SInfoWidget.h"
#include "SQImageDisplay.h"
#include "SHistogramWidget.h"
#include "SImageMapper.h"

/// \class SImageViewer2d
/// \brief 2D image viewer. Higher dimensions are displayed using a slider
class SIMAGEVIEWER_EXPORT SImageViewer2d : public SImageViewer{

    Q_OBJECT

public:
    SImageViewer2d();
    SImageViewer2d(const QString& image_file);

protected:
    /// \brief This method must implement the initialization of the viewer when a new image is set
    void render();

protected slots:
    void zoomIn();
    void zoomOut();
    void zoomOriginal();
    void showHideImageInfo();
    void adjust(float minVal, float maxVal);
    void updateColorMap(const QString colormap);

private:
    void createWidget();
    QWidget* createToolBar();
    QWidget* buildOptionsWidget();
    void refresh(int* colormap, float minVal, float maxVal);

protected:
    // options bar
    QWidget *m_optionWidget;
    QComboBox *m_colormapBox;
    SColormaps m_colormaps;
    QLabel* m_colormapLabel;
    SHistogramWidget* m_histView;
    SInfoWidget *m_infoView;

private:
    // toolbar
    bool m_imageEditorVisible;
    QPushButton* m_editorButton;

protected:
    // display area
    SImage* m_image;
    SQImageDisplay* m_imageDisplay;
    SImageMapper* m_imageMapper;

protected:
    // histogram info
    int* m_hist;
    float m_minVal;
    float m_maxVal;
    QString m_colormap;

};
