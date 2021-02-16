/// \file SQImageDisplay.cpp
/// \brief SQImageDisplay class
/// \author Sylvain Prigent
/// \version 0.1
/// \date 2021

#include "SQImageDisplay.h"

SQImageDisplay::SQImageDisplay(bool showZoomButtons, QWidget *parent) : QWidget(parent){

    m_isImage = false;
    m_scaleFactor = 1;

    m_imageLabel = new QLabel(this);
    m_imageLabel->setBackgroundRole(QPalette::Base);
    m_imageLabel->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    m_imageLabel->setScaledContents(true);

    m_scrollArea = new QScrollArea(this);
    m_scrollArea->setBackgroundRole(QPalette::Dark);
    m_scrollArea->setWidget(m_imageLabel);
    m_scrollArea->setWidgetResizable(false);
    m_scrollArea->setVisible(true);
    connect(m_scrollArea->horizontalScrollBar(), SIGNAL(valueChanged(int)), this, SIGNAL(scrollHorizontalChanged(int)));
    connect(m_scrollArea->verticalScrollBar(), SIGNAL(valueChanged(int)), this, SIGNAL(scrollVerticalChanged(int)));

    QVBoxLayout *layout = new QVBoxLayout();
    layout->setContentsMargins(0,0,0,0);
    layout->setSpacing(2);
    this->setLayout(layout);
    if (showZoomButtons){
        layout->addWidget(this->createToolBar());
    }
    //else{
    //    QWidget* fakeToolBar = new QWidget();
    //    fakeToolBar->setFixedHeight(50);
    //    layout->addWidget(fakeToolBar);
    //}
    layout->addWidget(m_scrollArea);

}

QWidget* SQImageDisplay::createToolBar(){

    QWidget *toolbar = new QWidget(this);
    toolbar->setFixedHeight(50);
    QHBoxLayout* layout = new QHBoxLayout();
    layout->setContentsMargins(0,0,0,0);
    layout->setSpacing(2);
    toolbar->setLayout(layout);

    QPushButton *zoomInButton = new QPushButton("Zoom In", this);
    connect(zoomInButton, SIGNAL(released()), this, SLOT(zoomIn()));
    connect(zoomInButton, SIGNAL(released()), this, SIGNAL(zoomInClicked()));
    zoomInButton->setMaximumWidth(100);

    QPushButton *zoomOutButton = new QPushButton("Zoom Out", this);
    connect(zoomOutButton, SIGNAL(released()), this, SLOT(zoomOut()));
    connect(zoomOutButton, SIGNAL(released()), this, SIGNAL(zoomOutClicked()));
    zoomOutButton->setMaximumWidth(100);

    QPushButton *normalSizeButton = new QPushButton("100%", this);
    connect(normalSizeButton, SIGNAL(released()), this, SLOT(normalSize()));
    connect(normalSizeButton, SIGNAL(released()), this, SIGNAL(normalSizeClicked()));
    normalSizeButton->setMaximumWidth(100);

    layout->addWidget(zoomInButton, 0, Qt::AlignLeft);
    layout->addWidget(zoomOutButton, 0, Qt::AlignLeft);
    layout->addWidget(normalSizeButton, 0, Qt::AlignLeft);
    layout->addWidget(new QWidget(), 1, Qt::AlignLeft);
    return toolbar;
}

void SQImageDisplay::zoomIn(){
    if (m_isImage){
        this->scaleImage(1.25);
    }
}

void SQImageDisplay::zoomOut(){
    if (m_isImage){
        this->scaleImage(0.8);
    }
}

void SQImageDisplay::normalSize(){
    if (m_isImage){
        m_imageLabel->setPixmap(QPixmap::fromImage(*m_inputImage));
        m_imageLabel->adjustSize();
        m_scaleFactor = 1.0;
    }
}

void SQImageDisplay::setImage(QImage *newImage){

    m_inputImage = newImage;
    m_imageLabel->setPixmap(QPixmap::fromImage(*newImage));
    scaleImage(1);
    m_isImage = true;
}

void SQImageDisplay::scaleImage(double factor){
    //Q_ASSERT(m_imageLabel->pixmap());
    m_scaleFactor *= factor;

    QPixmap pixmap = QPixmap::fromImage(*m_inputImage);
    m_imageLabel->setPixmap(pixmap.scaled(m_scaleFactor* pixmap.size(), Qt::KeepAspectRatio, Qt::FastTransformation));
    m_imageLabel->adjustSize();

    //m_imageLabel->resize(m_scaleFactor * m_imageLabel->pixmap()->size());

    //adjustScrollBar(m_scrollArea->horizontalScrollBar(), factor);
    //adjustScrollBar(m_scrollArea->verticalScrollBar(), factor);

}

void SQImageDisplay::adjustScrollBar(QScrollBar *scrollBar, double factor){
    scrollBar->setValue(int(factor * scrollBar->value()
                                + ((factor - 1) * scrollBar->pageStep()/2)));
}

void SQImageDisplay::scrollHorizontalValue(int value){
    m_scrollArea->horizontalScrollBar()->setValue(value);
}

void SQImageDisplay::scrollVerticalValue(int value){
    m_scrollArea->verticalScrollBar()->setValue(value);
}
