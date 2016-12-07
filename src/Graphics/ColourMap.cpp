// -----------------------------------------------------------------------------
// Copyright 2008 Steve Hanov. All rights reserved.
//
// For permission to use, please contact steve.hanov@gmail.com. Permission will
// usually be granted without charge.
// -----------------------------------------------------------------------------
#include <math.h>
#include "ColourMap.h"

//#include "dbg.h" // must be last.

ColourMap::~ColourMap()
{
}
/**
 * Quickly map a floating point value to a Win32 colour value.
 *
 * \param val Value to map. Must be in the range 0.0 to 1.0.
 */
QColor ColourMap::map( float val )
{
	if ( val < 0.0 ) {
		val = 0.0;
	} else if ( val > 1.0 ) {
		val = 1.0;
	}

	unsigned index = (unsigned)(val * numRegions);
    float percent = val * numRegions;
    percent -= floor(percent);

    return QColor(
            colours[index][0] + (int)(percent * (colours[index+1][0] - colours[index][0])),
            colours[index][1] + (int)(percent * (colours[index+1][1] - colours[index][1])),
            colours[index][2] + (int)(percent * (colours[index+1][2] - colours[index][2])));
}

/**
  * Returns the name of an available colour map.
  *
  * \param type Index of colour map. Use GetNumMaps() to obtain the number of
  * colour maps.
  */
const char* 
ColourMap::GetMapName( unsigned type )
{
    const char* Names[] = {
        "Spectrum (Maximum Dynamic Range)",
        "Black/Blue/Green",
        "Purple/Gold",
        "White/Black",
        "Fire"
    };

    return Names[type];
}

/**
 * Returns the number of available colour maps.
 */
unsigned
ColourMap::GetNumMaps()
{
    return 5;
}

/**
  * Create a colour map of the given type. Use GetNumMaps() and GetMapName() to
  * enumerate the valid types, and then choose one using this function.
 */
ColourMap::ColourMap( unsigned type )
{
    switch( type ) {
        default:
        // A colour map is just an array of colours. The values between
        // 0.0 and 1.0 are smoothly blended between all colours in the array.    
        case 0: {
            int Colours[8][3] = {
                {   0,   0,   0 },
                { 255,   0,   0 },
                { 255, 255,   0 },
                {   0, 255,   0 },
                {   0, 255, 255 },
                {   0,   0, 255 },
                { 255,   0, 255 },
                { 255, 255, 255 }};
            numRegions = 7;
            memcpy( &colours, Colours, sizeof(Colours) );
            break;
        }

        case 1: {
            int Colours[4][3] = {
                {   0,   0,   0 },
                {   0,   0, 255 },
                {   0, 255,   0 },
                { 255,   0,   0 }
            };
            numRegions = 3;
            memcpy( &colours, Colours, sizeof(Colours) ); 
            break;
        }

        case 2: {
            int Colours[4][3] = {
                { 255, 255, 255 },
                {  50,  27, 118 },
                { 255, 255,  35 },
                {   0,   0,   0 }
            };
            numRegions = 3;
            memcpy( &colours, Colours, sizeof(Colours) ); 
            break;
        }

        case 3: {
            int Colours[2][3] = {
                { 255, 255, 255 },
                {   0,   0,   0 },
            };
            numRegions = 1;
            memcpy( &colours, Colours, sizeof(Colours) ); 
            break;
        }

        case 4: {
            int Colours[4][3] = {
                {   0,   0,   0 },
                { 255,   0,   0 },
                { 255, 255,   0 },
                { 255, 255, 255 },
            };
            numRegions = 3;
            memcpy( &colours, Colours, sizeof(Colours) ); 
            break;
        }
    }
}
