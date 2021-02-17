/// \file SInfoWidget.cpp
/// \brief SInfoWidget class
/// \author Sylvain Prigent
/// \version 0.1
/// \date 2020

#include "DemoWindow.h"

DemoWindow::DemoWindow(QWidget* parent) : QMainWindow(parent)
{
    m_viewer = new SImageViewer2d();
    this->setCentralWidget(m_viewer);

    QMenu* fileMenu = menuBar()->addMenu(tr("&File"));

    QAction* openAction = new QAction("&Open");
    QAction* quitAction = new QAction("&Quit");
    fileMenu->addAction(openAction);
    fileMenu->addAction(quitAction);

    connect(openAction, SIGNAL(triggered()), this, SLOT(openImage()));
    connect(quitAction, SIGNAL(triggered()), this, SLOT(quit()));
}

DemoWindow::~DemoWindow()
{

}

void DemoWindow::openImage()
{
    QString file = QFileDialog::getOpenFileName(this, "Open image", QString(), "Images (*.tif *.tiff)");
    m_viewer->setImageFile(file);
}

void DemoWindow::quit()
{
    qApp->quit();
}
