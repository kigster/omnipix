/*
 * Animations.h
 *
 *  Created on: Nov 16, 2014
 *      Author: Konstantin Gredeskoul
 *        Code: https://github.com/kigster
 *
 *  (c) 2014 All rights reserved, MIT License.
 */

#ifndef ANIMATIONS_H_
#define ANIMATIONS_H_
#include <Arduino.h>
#include <SmartMatrix_32x32.h>
#include <MatrixFontCommon.h>
#include <SimpleTimer.h>
class Animations {
public:
    Animations(SimpleTimer *t);

    void showCurrentAnimation();
    void nextAnimation();

    void intro() ;
    void drawingIntro() ;
    void drawingPixels() ;
    void drawingLines() ;
    void drawTriangles() ;
    void drawCircles() ;
    void drawingRectangles() ;
    void drawingAnimations() ;
    void filledShapes() ;
    void fillScreen() ;
    void drawCharacters() ;
    void fonts() ;
    void fontOptions() ;
    void bitmap() ;
    void star() ;
    void scrollAboveDrawing() ;
    void scrollModes() ;
    void scrollSpeed() ;
    void scrollRotation() ;
    void scrollPosition() ;
    void demoScrollReset() ;
    void brightness() ;
    void rawBitman() ;
    void colorCorrection() ;

    char scrollBuffer[120];
    SmartMatrix matrix;
    uint8_t currentBrightness;
private:
    int i, j, currentAnimation;
    unsigned long currentMillis;
    rgb24 defaultBackgroundColor;
    int defaultScrollOffset;
    int defaultScrollSpeed;
    SimpleTimer *timer;

    void pause(unsigned long delayCounter);
};


#endif /* ANIMATIONS_H_ */
