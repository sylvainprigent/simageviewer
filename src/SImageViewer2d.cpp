/// \file SImageViewer.cpp
/// \brief SImageViewer class
/// \author Sylvain Prigent
/// \version 0.1
/// \date 2021

#include <SImageViewer2d.h>

SImageViewer2d::SImageViewer2d() : SImageViewer()
{
    createWidget();
}

SImageViewer2d::SImageViewer2d(const QString& image_file) : SImageViewer()
{
    createWidget();
    this->setImageFile(image_file);
}

void SImageViewer2d::render()
{
    qDebug() << "render";

    SImageFloat* image = dynamic_cast<SImageFloat*>(SImageReader::read(m_imageFile.toStdString(), 32));

    m_infoView->setImage(image, m_imageFile);

    // fill the option bar
    qDebug() << "fill the option bar";
    SHistogram hist;
    hist.setInput(image);
    hist.run();
    m_hist = hist.getCount();
    m_minVal = image->getMin();
    m_maxVal = image->getMax();
    m_histView->setHistogram(m_hist, m_minVal, m_maxVal);

    // fill the image data
    qDebug() << "fill the image data";
    qDebug() << "image info: sx=" << image->getSizeX() << ", sy=" << image->getSizeY();
    m_imageMapper->setImage(image);
    m_colormap = SColormaps::Gray;

    // refresh widgets
    qDebug() << "refresh widgets";
    this->refresh(m_colormaps.getGray(), m_minVal, m_maxVal);
}

void SImageViewer2d::refresh(int* colormap, float minVal, float maxVal)
{
    m_imageMapper->map2DGray(colormap, minVal, maxVal);
    m_imageDisplay->setImage(m_imageMapper->mappedImage());
}

void SImageViewer2d::createWidget()
{
    QVBoxLayout* layout = new QVBoxLayout();
    this->setLayout(layout);

    // toolbar
    layout->addWidget(this->createToolBar(), 0, Qt::AlignTop);

    // image display with options tool
    QSplitter *splitter = new QSplitter(this);
    layout->addWidget(splitter, 1);

    m_imageDisplay = new SQImageDisplay(false, this);

    splitter->addWidget(m_imageDisplay);
    splitter->addWidget(this->buildOptionsWidget());

    m_imageMapper = new SImageMapper();
}

QWidget* SImageViewer2d::createToolBar()
{
    QWidget* toolbarWidget = new QWidget(this);
    QHBoxLayout *layout = new QHBoxLayout();
    layout->setContentsMargins(0,0,0,0);
    toolbarWidget->setLayout(layout);

    QWidget *zoomWidget = new QWidget(this);
    QHBoxLayout *zoomLayout = new QHBoxLayout();
    zoomLayout->setContentsMargins(0,0,0,0);
    zoomLayout->setSpacing(0);
    zoomWidget->setLayout(zoomLayout);
    QPushButton* zoomInButton = new QPushButton(tr("Zoom in"));
    connect(zoomInButton, SIGNAL(released()), this, SLOT(zoomIn()));
    zoomInButton->setObjectName("SLeftButton");
    zoomInButton->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Ignored);
    QPushButton* zoomOutButton = new QPushButton(tr("Zoom out"));
    connect(zoomOutButton, SIGNAL(released()), this, SLOT(zoomOut()));
    zoomOutButton->setObjectName("SCenterButton");
    QPushButton* normalSizeButton = new QPushButton(tr("100%"));
    connect(normalSizeButton, SIGNAL(released()), this, SLOT(zoomOriginal()));
    normalSizeButton->setObjectName("SRightButton");

    zoomLayout->addWidget(zoomInButton);
    zoomLayout->addWidget(zoomOutButton);
    zoomLayout->addWidget(normalSizeButton);

    QWidget *editionWidget = new QWidget(this);
    QHBoxLayout *editionLayout = new QHBoxLayout();
    editionLayout->setContentsMargins(0,0,0,0);
    editionLayout->setSpacing(0);
    editionWidget->setLayout(editionLayout);
    m_editorButton = new QPushButton(tr("Display settings"));
    m_editorButton->setObjectName("SButton");
    m_editorButton->setCheckable(true);
    m_editorButton->setChecked(true);
    connect(m_editorButton, SIGNAL(released()), this, SLOT(showHideImageInfo()));
    editionLayout->addWidget(m_editorButton);

    layout->addWidget(zoomWidget, 0, Qt::AlignLeft);
    layout->addWidget(editionWidget, 0, Qt::AlignLeft);
    layout->addWidget(new QWidget(), 1, Qt::AlignLeft);
    return toolbarWidget;
}

QWidget* SImageViewer2d::buildOptionsWidget()
{
    //  ------ Widget 1: colormap
    QGroupBox *colormapWidget = new QGroupBox("Colormap", this);
    QVBoxLayout* colormapLayout = new QVBoxLayout();
    colormapWidget->setLayout(colormapLayout);

    // colormaps list
    m_colormapBox = new QComboBox();
    m_colormapBox->setMaximumWidth(256);
    m_colormapBox->addItems(m_colormaps.getList());
    connect(m_colormapBox, SIGNAL(currentTextChanged(const QString)), this, SLOT(updateColorMap(const QString)));
    colormapLayout->addWidget(m_colormapBox);

    // get colormap
    m_colormapLabel = new QLabel();
    QImage image = m_colormaps.getView("Gray", 24);
    m_colormapLabel->setPixmap(QPixmap::fromImage(image));
    colormapLayout->addWidget(m_colormapLabel);

    // ------ Widget2: adjust
    QGroupBox *adjustWidget = new QGroupBox("Adjust", this);
    QVBoxLayout *adjustLayout = new QVBoxLayout();
    adjustLayout->setContentsMargins(7,12,7,7);
    adjustWidget->setLayout(adjustLayout);

    m_histView = new SHistogramWidget(this);
    connect(m_histView, SIGNAL(minMaxChanged(float, float)), this, SLOT(adjust(float, float)));
    adjustLayout->addWidget(m_histView);

    // ------ Widget 3: info
    QGroupBox *infoWidget = new QGroupBox("Informations", this);
    QVBoxLayout* infoLayout = new QVBoxLayout();
    infoWidget->setLayout(infoLayout);

    m_infoView = new SInfoWidget();
    infoLayout->addWidget(m_infoView);

    // widget
    m_optionWidget = new QWidget(this);
    QVBoxLayout *layout = new QVBoxLayout();
    layout->setContentsMargins(0,0,0,0);
    layout->setSpacing(2);
    m_optionWidget->setLayout(layout);

    // add widgets
    layout->addWidget(colormapWidget, 0, Qt::AlignTop);
    layout->addWidget(adjustWidget, 0, Qt::AlignTop);
    layout->addWidget(infoWidget, 0, Qt::AlignTop);
    layout->addWidget(new QWidget(), 1, Qt::AlignTop);

    m_optionWidget->setFixedWidth(270);
    return m_optionWidget;
}

void SImageViewer2d::zoomIn(){
    m_imageDisplay->zoomIn();
}

void SImageViewer2d::zoomOut(){
    m_imageDisplay->zoomOut();
}

void SImageViewer2d::zoomOriginal(){
    m_imageDisplay->normalSize();
}

void SImageViewer2d::showHideImageInfo(){
    if (m_imageEditorVisible){
        m_optionWidget->setVisible(false);
        m_imageEditorVisible = false;
    }
    else{
        m_optionWidget->setVisible(true);
        m_imageEditorVisible = true;
    }
}

void SImageViewer2d::adjust(float minVal, float maxVal)
{
    m_minVal = minVal;
    m_maxVal = maxVal;
    this->refresh(m_colormaps.getColorMap(m_colormapBox->currentText()), minVal, maxVal);
}

void SImageViewer2d::updateColorMap(const QString colormap){

    m_colormap = colormap;
    this->refresh(m_colormaps.getColorMap(colormap), m_minVal, m_maxVal);

    QImage image = m_colormaps.getView(colormap, 24);
    m_colormapLabel->setPixmap(QPixmap::fromImage(image));
}
