// -----------------------------------------------------------------------------
// Copyright 2008 Steve Hanov. All rights reserved.
//
// For permission to use, please contact steve.hanov@gmail.com. Permission will
// usually be granted without charge.
// -----------------------------------------------------------------------------
#ifndef COLOURMAP_H
#define COLOURMAP_H

//#include <windows.h>
#include <QtCore>
#include <QColor>
/**
  The ColourMap class can be used to map a floating point value between 0 and
  1.0 to a colour. It contains several predefined colour maps to choose from,
  and has functions to enumerate them.
 */ 
class ColourMap
{
public:
    ColourMap( unsigned type = 0 );
    ~ColourMap();

    QColor map( float val );

    static unsigned GetNumMaps();
    static const char* GetMapName( unsigned );

private:
    int colours[8][3];
    unsigned numRegions;
};

#endif // COLOURMAP_H
