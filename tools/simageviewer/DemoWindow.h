/// \file DemoWindow.h
/// \brief DemoWindow class
/// \author Sylvain Prigent
/// \version 0.1
/// \date 2020

#pragma once

#include <QtWidgets>

#include <simageviewer>

/// \class DemoWindow
/// \brief Main window to demonstrate the 2D viewer
class DemoWindow : public QMainWindow{

    Q_OBJECT

public:
    DemoWindow(QWidget* parent = nullptr);
    ~DemoWindow();

protected slots:
    void openImage();
    void quit();

private:
    SImageViewer2d* m_viewer;

};
