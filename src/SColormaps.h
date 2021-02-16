/// \file SColormaps.h
/// \brief SColormaps class
/// \author Sylvain Prigent
/// \version 0.1
/// \date 2021

#pragma once

#include <QString>
#include <QList>
#include <QLabel>

#include "simageviewerExport.h"

/// \class sciColormaps
/// \brief Class load image into Qt data structures
class SIMAGEVIEWER_EXPORT SColormaps{

public:
    static const QString Gray;
    static const QString Red;
    static const QString Green;
    static const QString Blue;
    static const QString Bone;
    static const QString Copper;
    static const QString Pink;
    static const QString Jet;
    static const QString Hot;
    static const QString Cool;
    static const QString Spring;
    static const QString Summer;
    static const QString Autumn;
    static const QString Winter;
    static const QString HiLo;

public:
    SColormaps();
    ~SColormaps();

public:
    int* getColorMap(QString name); // 3*i+j
    QImage getView(QString colormap, int height = 32);
    QStringList getList();

public:
    int* getGray();
    int* getRed();
    int* getGreen();
    int* getBlue();
    int* getBone();
    int* getCopper();
    int* getPink();
    int* getjet();
    int* getHot();
    int* getCool();
    int* getSpring();
    int* getSummer();
    int* getAutumn();
    int* getWinter();
    int* getHiLo();

};
