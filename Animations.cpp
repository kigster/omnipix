/*
 * Animations.cpp
 *
 *  Created on: Nov 16, 2014
 *      Author: Konstantin Gredeskoul
 *        Code: https://github.com/kigster
 *
 *  (c) 2014 All rights reserved, MIT License.
 */

#include "Animations.h"
#include "bitmaps/colorwheel.c"
#include "bitmaps/pixelmatix.c"

Animations::Animations(SimpleTimer *t) {
    timer = t;
    j = i = 0;
    currentBrightness = 127;
    currentMillis = millis();
    matrix = SmartMatrix();
    currentAnimation = 1;

    defaultBackgroundColor = { 0x40, 0, 0 };
    defaultScrollOffset = 10;
    defaultScrollSpeed = 60;
}

void Animations::nextAnimation() {
    currentAnimation++;
    currentAnimation = currentAnimation % 19;

}
void Animations::showCurrentAnimation() {
    sprintf(scrollBuffer, "#%d", currentAnimation);
    matrix.setScrollColor( { 0x70 + random(128), 0x70 + random(128), 0x70 + random(128)});
    matrix.setScrollMode(wrapForward);
    matrix.setScrollSpeed(60);
    matrix.setScrollFont(font6x10);
    matrix.scrollText(scrollBuffer, 1);
    delay(1500);
    switch(currentAnimation + 1 ) {
        case 1:   sprintf(scrollBuffer, "intro"); intro(); break;
        case 2:   sprintf(scrollBuffer, "drawingIntro");drawingIntro(); break;
        case 3:   sprintf(scrollBuffer, "drawingPixels");drawingPixels(); break;
        case 4:   sprintf(scrollBuffer, "drawingLines");drawingLines(); break;
        case 5:   sprintf(scrollBuffer, "drawTriangles");drawTriangles(); break;
        case 6:   sprintf(scrollBuffer, "drawCircles");drawCircles(); break;
        case 7:   sprintf(scrollBuffer, "drawingRectangles");drawingRectangles(); break;
        case 8:   sprintf(scrollBuffer, "drawingAnimations");drawingAnimations(); break;
        case 9:   sprintf(scrollBuffer, "filledShapes");filledShapes(); break;
        case 10:  sprintf(scrollBuffer, "fillScreen");fillScreen(); break;
        case 11:  sprintf(scrollBuffer, "rawBitman"); rawBitman(); break;
        case 12:  sprintf(scrollBuffer, "star");star(); break;
        case 13:  sprintf(scrollBuffer, "bitmap");bitmap(); break;
        case 14:  sprintf(scrollBuffer, "scrollAboveDrawing");scrollAboveDrawing(); break;
        case 15:  sprintf(scrollBuffer, "colorCorrection");colorCorrection(); break;
        case 16:  sprintf(scrollBuffer, "scrollSpeed");scrollSpeed(); break;
        case 17:  sprintf(scrollBuffer, "scrollRotation");scrollRotation(); break;
        case 18:  sprintf(scrollBuffer, "demoScrollReset");demoScrollReset(); break;
        case 19:  sprintf(scrollBuffer, "brightness");brightness(); break;
    }
}
//
void Animations::bitmap() {
    int i;
    rgb24 *buffer;

    buffer = matrix.backBuffer();
    if ((pixelmatixlogo. width <= matrix.getScreenWidth()) &&
      (pixelmatixlogo.height <= matrix.getScreenHeight()))
        for (i = 0; i < matrix.getScreenWidth() * matrix.getScreenHeight(); i++) {
            buffer[i].red = pixelmatixlogo.pixel_data[i * 3 + 0];
            buffer[i].green = pixelmatixlogo.pixel_data[i * 3 + 1];
            buffer[i].blue = pixelmatixlogo.pixel_data[i * 3 + 2];
        }

    matrix.swapBuffers(true);

    delay(2000);

    buffer = matrix.backBuffer();

    if ((colorwheel.width <= matrix.getScreenWidth()) &&
      (colorwheel.height <= matrix.getScreenHeight()))
        for (i = 0; i < matrix.getScreenWidth() * matrix.getScreenHeight(); i++) {
            buffer[i].red = colorwheel.pixel_data[i * 3 + 0];
            buffer[i].green = colorwheel.pixel_data[i * 3 + 1];
            buffer[i].blue = colorwheel.pixel_data[i * 3 + 2];
        }

    matrix.swapBuffers(true);


    delay(2000);
}


void Animations::intro() {
    // clear screen
    matrix.fillScreen(defaultBackgroundColor);
    matrix.swapBuffers(true);

    matrix.setScrollColor( { 0xff, 0xff, 0xff });
    matrix.setScrollMode(wrapForward);
    matrix.setScrollSpeed(60);
    matrix.setScrollFont(font6x10);
    matrix.scrollText(scrollBuffer, 1);

}

void Animations::drawingIntro() {
    {
        matrix.setScrollColor( { 0xff, 0xff, 0xff });
        matrix.setScrollMode(wrapForward);
        matrix.setScrollSpeed(defaultScrollSpeed);

        matrix.setScrollFont(font6x10);
        matrix.scrollText(scrollBuffer, 1);

        const int delayBetweenShapes = 300;

        for (i = 0; i < 5000; i += delayBetweenShapes) {
            // draw for 100ms, then update frame, repeat
            currentMillis = millis();
            int x0, y0, x1, y1, x2, y2, radius;
            // x0,y0 pair is always on the screen
            x0 = random(matrix.getScreenWidth());
            y0 = random(matrix.getScreenHeight());

#if 0
            // x1,y1 pair can be off screen;
            x1 = random(-matrix.getScreenWidth(), 2 * matrix.getScreenWidth());
            y1 = random(-matrix.getScreenHeight(), 2 * matrix.getScreenHeight());
#else
            x1 = random(matrix.getScreenWidth());
            y1 = random(matrix.getScreenHeight());
#endif
            // x2,y2 pair is on screen;
            x2 = random(matrix.getScreenWidth());
            y2 = random(matrix.getScreenHeight());

            // radius is positive, up to screen width size
            radius = random(matrix.getScreenWidth());

            rgb24 fillColor = { (uint8_t) random(192), (uint8_t) random(192),
                    (uint8_t) random(192) };
            rgb24 outlineColor = { (uint8_t) random(192), (uint8_t) random(192),
                    (uint8_t) random(192) };

            switch (random(14)) {
            case 0:
                matrix.drawPixel(x0, y0, outlineColor);
                break;

            case 1:
                matrix.drawLine(x0, y0, x1, y1, outlineColor);
                break;

            case 2:
                matrix.drawCircle(x0, y0, radius, outlineColor);
                break;

            case 3:
                matrix.drawTriangle(x0, y0, x1, y1, x2, y2, outlineColor);
                break;

            case 4:
                matrix.drawRectangle(x0, y0, x1, y1, outlineColor);
                break;

            case 5:
                matrix.drawRoundRectangle(x0, y0, x1, y1, radius, outlineColor);
                break;

            case 6:
                matrix.fillCircle(x0, y0, radius, fillColor);
                break;

            case 7:
                matrix.fillTriangle(x0, y0, x1, y1, x2, y2, fillColor);
                break;

            case 8:
                matrix.fillRectangle(x0, y0, x1, y1, fillColor);
                break;

            case 9:
                matrix.fillRoundRectangle(x0, y0, x1, y1, radius, fillColor);
                break;

            case 10:
                matrix.fillCircle(x0, y0, radius, outlineColor, fillColor);
                break;

            case 11:
                matrix.fillTriangle(x0, y0, x1, y1, x2, y2, outlineColor,
                        fillColor);
                break;

            case 12:
                matrix.fillRectangle(x0, y0, x1, y1, outlineColor, fillColor);
                break;

            case 13:
                matrix.fillRoundRectangle(x0, y0, x1, y1, radius, outlineColor,
                        fillColor);
                break;

            default:
                break;
            }
            matrix.swapBuffers(true);
            //matrix.fillScreen({0,0,0});
            while (millis() < currentMillis + delayBetweenShapes)
                ;
        }
    }
}

void Animations::drawingPixels() {
    // "Drawing Functions"
    matrix.setScrollColor( { 0xff, 0xff, 0xff });
    matrix.setScrollMode(wrapForward);
    matrix.setScrollSpeed(defaultScrollSpeed);

    matrix.setScrollFont(font6x10);
    matrix.scrollText(scrollBuffer, 1);

    const uint transitionTime = 3000;

    matrix.fillScreen( { 0, 0, 0 });
    matrix.swapBuffers(true);

    currentMillis = millis();

    while (millis() - currentMillis < transitionTime) {
        int x0, y0;

        rgb24 color;
        float fraction = ((float) millis() - currentMillis)
                / ((float) transitionTime / 2);

        if (millis() - currentMillis < transitionTime / 2) {
            color.red = 255 - 255.0 * fraction;
            color.green = 255.0 * fraction;
            color.blue = 0;
        } else {
            color.red = 0;
            color.green = 255 - 255.0 / 2 * (fraction - 1.0);
            color.blue = 255.0 * (fraction - 1.0);
        }

        for (i = 0; i < 20; i++) {
            x0 = random(matrix.getScreenWidth());
            y0 = random(matrix.getScreenHeight());

            matrix.drawPixel(x0, y0, color);
        }
        matrix.swapBuffers(true);
    }
}

void Animations::drawingLines() {
    matrix.setScrollColor( { 0xff, 0xff, 0xff });
    matrix.setScrollMode(wrapForward);
    matrix.setScrollSpeed(defaultScrollSpeed);

    matrix.setScrollFont(font6x10);
    matrix.scrollText(scrollBuffer, 1);

    int transitionTime = 6000;

    //matrix.fillScreen({0, 0, 0});
    //matrix.swapBuffers(true);

    currentMillis = millis();
    unsigned long delayCounter = currentMillis;

    for (i = 0; i < matrix.getScreenWidth(); i++) {
        rgb24 color;
        float fraction = ((float) millis() - currentMillis)
                / ((float) transitionTime / 2);

        color.red = 255 - 255.0 * fraction;
        color.green = 255.0 * fraction;
        color.blue = 0;

        matrix.drawFastVLine(i, 0, matrix.getScreenHeight(), color);
        matrix.swapBuffers(true);
        delayCounter += transitionTime / 2 / matrix.getScreenWidth();
        pause(delayCounter)
            ;
    }

    for (i = 0; i < matrix.getScreenHeight(); i++) {
        rgb24 color;
        float fraction = ((float) millis() - currentMillis)
                / ((float) transitionTime / 2);
        fraction -= 1.0;
        if (fraction < 0)
            fraction = 0.0;

        color.red = 0;
        color.green = 255 - 255.0 / 2 * (fraction);
        color.blue = 255.0 * (fraction);

        matrix.drawFastHLine(0, matrix.getScreenWidth(), i, color);
        matrix.swapBuffers(true);
        delayCounter += transitionTime / 2 / matrix.getScreenHeight();
        pause(delayCounter)
            ;
    }

    matrix.scrollText(scrollBuffer, 1);

    transitionTime = 4000;
    currentMillis = millis();
    delayCounter = currentMillis;

    for (i = 0; i < matrix.getScreenWidth() * 2; i++) {
        rgb24 color;
        float fraction = ((float) millis() - currentMillis)
                / ((float) transitionTime / 2);

        color.red = 255 - 255.0 * fraction;
        color.green = 255.0 * fraction;
        color.blue = 0;

        matrix.drawLine(i, 0, 0, i, color);
        matrix.swapBuffers(true);
        delayCounter += transitionTime / 2 / (matrix.getScreenWidth() * 2);
        pause(delayCounter)
            ;
    }

    for (i = 0; i < matrix.getScreenWidth() * 2; i++) {
        rgb24 color;
        float fraction = ((float) millis() - currentMillis)
                / ((float) transitionTime / 2);
        fraction -= 1.0;
        if (fraction < 0)
            fraction = 0.0;

        color.red = 0;
        color.green = 255 - 255.0 / 2 * (fraction);
        color.blue = 255.0 * (fraction);

        matrix.drawLine(0, matrix.getScreenHeight() - i,
                matrix.getScreenWidth(), i, color);
        matrix.swapBuffers(true);
        delayCounter += transitionTime / 2 / (matrix.getScreenWidth() * 2);
        pause(delayCounter)
            ;
    }
}

void Animations::drawTriangles() {
    matrix.setScrollColor( { 0xff, 0xff, 0xff });
    matrix.setScrollMode(wrapForward);
    matrix.setScrollSpeed(defaultScrollSpeed);

    matrix.setScrollFont(font6x10);
    matrix.scrollText(scrollBuffer, 1);

    int transitionTime = 3000;

//matrix.fillScreen({0, 0, 0});
//matrix.swapBuffers(true);

    currentMillis = millis();
    unsigned long delayCounter = currentMillis;

    for (i = 0; i < matrix.getScreenWidth(); i++) {
        rgb24 color;
        float fraction = ((float) millis() - currentMillis)
                / ((float) transitionTime / 2);

        color.red = 255 - 255.0 * fraction;
        color.green = 255.0 * fraction;
        color.blue = 0;

        matrix.drawTriangle(i, 0, matrix.getScreenWidth(), i,
                matrix.getScreenWidth() - i, matrix.getScreenHeight(), color);
        matrix.swapBuffers(true);
        delayCounter += transitionTime / 2 / matrix.getScreenWidth();
        pause(delayCounter)
            ;
    }

    for (i = 0; i < matrix.getScreenHeight(); i++) {
        rgb24 color;
        float fraction = ((float) millis() - currentMillis)
                / ((float) transitionTime / 2);
        fraction -= 1.0;
        if (fraction < 0)
            fraction = 0.0;

        color.red = 0;
        color.green = 255 - 255.0 / 2 * (fraction);
        color.blue = 255.0 * (fraction);

        matrix.drawTriangle(matrix.getScreenWidth() - i,
                matrix.getScreenHeight(), 0, matrix.getScreenHeight() - i,
                matrix.getScreenWidth(), i, color);
        matrix.swapBuffers(true);
        delayCounter += transitionTime / 2 / matrix.getScreenHeight();
        pause(delayCounter)
            ;
    }
}

void Animations::pause(unsigned long delayCounter) {
    while (millis() < delayCounter) {
        timer->run();
    }

}

void Animations::drawCircles() {
    matrix.setScrollColor( { 0xff, 0xff, 0xff });
    matrix.setScrollMode(wrapForward);
    matrix.setScrollSpeed(defaultScrollSpeed);

    matrix.setScrollFont(font6x10);
    matrix.scrollText(scrollBuffer, 1);

    int transitionTime = 6000;

//matrix.fillScreen({0, 0, 0});
//matrix.swapBuffers(true);

    currentMillis = millis();
    unsigned long delayCounter = currentMillis;

    for (i = 0; i < matrix.getScreenWidth() * 2; i++) {
        rgb24 color;
        float fraction = ((float) millis() - currentMillis)
                / ((float) transitionTime / 2);

        color.red = 255 - 255.0 * fraction;
        color.green = 255.0 * fraction;
        color.blue = 0;

        int radius = i / 2;
        if (radius > matrix.getScreenWidth())
            radius = matrix.getScreenWidth();

        matrix.drawCircle(i, matrix.getScreenHeight() / 2, radius, color);
        matrix.swapBuffers(true);
        delayCounter += transitionTime / 2 / (matrix.getScreenWidth() * 2);
        pause(delayCounter)
            ;
    }

    for (i = matrix.getScreenWidth() * 2 / 3; i >= 0; i--) {
        rgb24 color;
        float fraction = ((float) millis() - currentMillis)
                / ((float) transitionTime / 2);
        fraction -= 1.0;
        if (fraction < 0)
            fraction = 0.0;

        color.red = 0;
        color.green = 255 - 255.0 / 2 * (fraction);
        color.blue = 255.0 * (fraction);

        matrix.drawCircle(matrix.getScreenWidth() / 2,
                matrix.getScreenHeight() / 2, i, color);
        matrix.swapBuffers(true);
        delayCounter += transitionTime / 2 / (matrix.getScreenWidth() * 2 / 3);
        pause(delayCounter);
    }
}

void Animations::drawingRectangles() {
    matrix.setScrollColor( { 0xff, 0xff, 0xff });
    matrix.setScrollMode(wrapForward);
    matrix.setScrollSpeed(defaultScrollSpeed);

    matrix.setScrollFont(font6x10);
    matrix.scrollText(scrollBuffer, 1);

    int transitionTime = 3000;

//matrix.fillScreen({0, 0, 0});
//matrix.swapBuffers(true);

    currentMillis = millis();
    unsigned long delayCounter = currentMillis;

    for (i = 0; i < matrix.getScreenWidth() / 2; i++) {
        rgb24 color;
        float fraction = ((float) millis() - currentMillis)
                / ((float) transitionTime / 2);

        color.red = 255 - 255.0 * fraction;
        color.green = 255.0 * fraction;
        color.blue = 0;

        matrix.drawRectangle(matrix.getScreenWidth() / 2 - i - 1,
                matrix.getScreenHeight() / 2 - i - 1,
                matrix.getScreenWidth() / 2 + i,
                matrix.getScreenHeight() / 2 + i, color);
        matrix.swapBuffers(true);
        delayCounter += transitionTime / 2 / (matrix.getScreenWidth() / 2);
        pause(delayCounter)
            ;
    }
    for (i = 0; i < matrix.getScreenWidth(); i++) {
        rgb24 color;
        float fraction = ((float) millis() - currentMillis)
                / ((float) transitionTime / 2);
        fraction -= 1.0;
        if (fraction < 0)
            fraction = 0.0;

        color.red = 0;
        color.green = 255 - 255.0 / 2 * (fraction);
        color.blue = 255.0 * (fraction);

        matrix.drawRectangle(i / 4, i / 2, i, i, color);
        matrix.swapBuffers(true);
        delayCounter += transitionTime / 2 / matrix.getScreenHeight();
        pause(delayCounter)
            ;
    }
}

void Animations::drawingAnimations() {
    matrix.setScrollColor( { 0xff, 0xff, 0xff });
    matrix.setScrollMode(wrapForward);
    matrix.setScrollSpeed(defaultScrollSpeed);

    matrix.setScrollFont(font6x10);
    matrix.scrollText(scrollBuffer, 1);

    int transitionTime = 7000;

//matrix.fillScreen({0, 0, 0});
//matrix.swapBuffers(true);

    currentMillis = millis();
    unsigned long delayCounter = currentMillis;

    for (i = 0; i < matrix.getScreenWidth() / 2; i++) {
        rgb24 color;
        float fraction = ((float) millis() - currentMillis)
                / ((float) transitionTime / 2);

        color.red = 255 - 255.0 * fraction;
        color.green = 255.0 * fraction;
        color.blue = 0;

        matrix.drawRoundRectangle(matrix.getScreenWidth() / 2 - i - 1,
                matrix.getScreenHeight() / 2 - i - 1,
                matrix.getScreenWidth() / 2 + i,
                matrix.getScreenHeight() / 2 + i, i / 2, color);
        matrix.swapBuffers(true);
        delayCounter += transitionTime / 2 / (matrix.getScreenWidth() / 2);
        pause(delayCounter)
            ;
    }
    for (i = 0; i < matrix.getScreenWidth(); i++) {
        rgb24 color;
        float fraction = ((float) millis() - currentMillis)
                / ((float) transitionTime / 2);
        fraction -= 1.0;
        if (fraction < 0)
            fraction = 0.0;

        color.red = 0;
        color.green = 255 - 255.0 / 2 * (fraction);
        color.blue = 255.0 * (fraction);

        matrix.drawRoundRectangle(i / 4, i / 2, i, i, i / 2, color);
        matrix.swapBuffers(true);
        delayCounter += transitionTime / 2 / matrix.getScreenHeight();
        pause(delayCounter)
            ;
    }
}

void Animations::filledShapes() {
    matrix.setScrollColor( { 0xff, 0xff, 0xff });
    matrix.setScrollMode(wrapForward);
    matrix.setScrollSpeed(defaultScrollSpeed);

    matrix.setScrollFont(font6x10);
    matrix.scrollText(scrollBuffer, 1);

    uint transitionTime = 8500;
    int delayBetweenShapes = 50;

//matrix.fillScreen({0, 0, 0});
//matrix.swapBuffers(true);

    currentMillis = millis();
    unsigned long delayCounter = currentMillis;

    while (millis() - currentMillis < transitionTime) {
        rgb24 color;
        float fraction = ((float) millis() - currentMillis)
                / ((float) transitionTime);

        color.red = random(256);
        color.green = random(256);
        color.blue = 0;

        if (fraction < 1.0 / 3) {
            matrix.drawRectangle(random(matrix.getScreenWidth() / 4),
                    random(matrix.getScreenHeight() / 4),
                    random(matrix.getScreenWidth() / 4)
                            + matrix.getScreenWidth() / 4,
                    random(matrix.getScreenHeight() / 4)
                            + matrix.getScreenHeight() / 4, color);
            matrix.drawRoundRectangle(
                    random(matrix.getScreenWidth() / 4)
                            + matrix.getScreenWidth() / 2,
                    random(matrix.getScreenHeight() / 4),
                    random(matrix.getScreenWidth() / 4)
                            + matrix.getScreenWidth() * 3 / 4,
                    random(matrix.getScreenHeight() / 4)
                            + matrix.getScreenHeight() / 4,
                    random(matrix.getScreenWidth() / 4), color);
            matrix.drawCircle(
                    random(matrix.getScreenWidth() / 4)
                            + matrix.getScreenWidth() / 8,
                    random(matrix.getScreenHeight() / 4)
                            + matrix.getScreenHeight() * 5 / 8,
                    random(matrix.getScreenHeight() / 8), color);
            matrix.drawTriangle(
                    random(matrix.getScreenWidth() / 2)
                            + matrix.getScreenWidth() / 2,
                    random(matrix.getScreenHeight() / 2)
                            + matrix.getScreenHeight() / 2,
                    random(matrix.getScreenWidth() / 2)
                            + matrix.getScreenWidth() / 2,
                    random(matrix.getScreenHeight() / 2)
                            + matrix.getScreenHeight() / 2,
                    random(matrix.getScreenWidth() / 2)
                            + matrix.getScreenWidth() / 2,
                    random(matrix.getScreenHeight() / 2)
                            + matrix.getScreenHeight() / 2, color);
        } else if (fraction < 2.0 / 3) {
            matrix.fillRectangle(random(matrix.getScreenWidth() / 4),
                    random(matrix.getScreenHeight() / 4),
                    random(matrix.getScreenWidth() / 4)
                            + matrix.getScreenWidth() / 4,
                    random(matrix.getScreenHeight() / 4)
                            + matrix.getScreenHeight() / 4, color);
            matrix.fillRoundRectangle(
                    random(matrix.getScreenWidth() / 4)
                            + matrix.getScreenWidth() / 2,
                    random(matrix.getScreenHeight() / 4),
                    random(matrix.getScreenWidth() / 4)
                            + matrix.getScreenWidth() * 3 / 4,
                    random(matrix.getScreenHeight() / 4)
                            + matrix.getScreenHeight() / 4,
                    random(matrix.getScreenWidth() / 4), color);
            matrix.fillCircle(
                    random(matrix.getScreenWidth() / 4)
                            + matrix.getScreenWidth() / 8,
                    random(matrix.getScreenHeight() / 4)
                            + matrix.getScreenHeight() * 5 / 8,
                    random(matrix.getScreenHeight() / 8), color);
            matrix.fillTriangle(
                    random(matrix.getScreenWidth() / 2)
                            + matrix.getScreenWidth() / 2,
                    random(matrix.getScreenHeight() / 2)
                            + matrix.getScreenHeight() / 2,
                    random(matrix.getScreenWidth() / 2)
                            + matrix.getScreenWidth() / 2,
                    random(matrix.getScreenHeight() / 2)
                            + matrix.getScreenHeight() / 2,
                    random(matrix.getScreenWidth() / 2)
                            + matrix.getScreenWidth() / 2,
                    random(matrix.getScreenHeight() / 2)
                            + matrix.getScreenHeight() / 2, color);
        } else {
            matrix.fillRectangle(random(matrix.getScreenWidth() / 4),
                    random(matrix.getScreenHeight() / 4),
                    random(matrix.getScreenWidth() / 4)
                            + matrix.getScreenWidth() / 4,
                    random(matrix.getScreenHeight() / 4)
                            + matrix.getScreenHeight() / 4, { 0, 0, 0xff },
                    color);
            matrix.fillRoundRectangle(
                    random(matrix.getScreenWidth() / 4)
                            + matrix.getScreenWidth() / 2,
                    random(matrix.getScreenHeight() / 4),
                    random(matrix.getScreenWidth() / 4)
                            + matrix.getScreenWidth() * 3 / 4,
                    random(matrix.getScreenHeight() / 4)
                            + matrix.getScreenHeight() / 4,
                    random(matrix.getScreenWidth() / 4), { 0, 0, 0xff }, color);
            matrix.fillCircle(
                    random(matrix.getScreenWidth() / 4)
                            + matrix.getScreenWidth() / 8,
                    random(matrix.getScreenHeight() / 4)
                            + matrix.getScreenHeight() * 5 / 8,
                    random(matrix.getScreenHeight() / 8), { 0, 0, 0xff },
                    color);
            matrix.fillTriangle(
                    random(matrix.getScreenWidth() / 2)
                            + matrix.getScreenWidth() / 2,
                    random(matrix.getScreenHeight() / 2)
                            + matrix.getScreenHeight() / 2,
                    random(matrix.getScreenWidth() / 2)
                            + matrix.getScreenWidth() / 2,
                    random(matrix.getScreenHeight() / 2)
                            + matrix.getScreenHeight() / 2,
                    random(matrix.getScreenWidth() / 2)
                            + matrix.getScreenWidth() / 2,
                    random(matrix.getScreenHeight() / 2)
                            + matrix.getScreenHeight() / 2, { 0, 0, 0xff },
                    color);
        }

        matrix.swapBuffers(true);
        delayCounter += delayBetweenShapes;
        pause(delayCounter)
            ;
    }
}

void Animations::fillScreen() {
    matrix.setScrollColor( { 0xff, 0xff, 0xff });
    matrix.setScrollMode(wrapForward);
    matrix.setScrollSpeed(defaultScrollSpeed);

    matrix.setScrollFont(font6x10);
    matrix.scrollText(scrollBuffer, 1);

    const uint transitionTime = 3000;

    matrix.fillScreen( { 0, 0, 0 });
    matrix.swapBuffers(true);

    currentMillis = millis();

    while (millis() - currentMillis < transitionTime) {
        rgb24 color;
        float fraction = ((float) millis() - currentMillis)
                / ((float) transitionTime / 2);

        if (millis() - currentMillis < transitionTime / 2) {
            color.red = 255 - 255.0 * fraction;
            color.green = 255.0 * fraction;
            color.blue = 0;
        } else {
            color.red = 0;
            color.green = 255 - 255.0 / 2 * (fraction - 1.0);
            color.blue = 255.0 * (fraction - 1.0);
        }

        for (i = 0; i < 20; i++) {
            matrix.fillScreen(color);
        }
        matrix.swapBuffers(true);
    }
}
void Animations::drawCharacters() {
    matrix.setScrollColor( { 0xff, 0xff, 0xff });
    matrix.setScrollMode(wrapForward);
    matrix.setScrollSpeed(defaultScrollSpeed);

    matrix.setScrollFont(font6x10);
    matrix.scrollText(scrollBuffer, 1);

    const uint transitionTime = 5500;
    const int delayBetweenCharacters = 500;
    const int leftEdgeOffset = 2;
    const int spaceBetweenCharacters = 6;

    currentMillis = millis();

    matrix.fillScreen( { 0, 0x80, 0x80 });
    matrix.swapBuffers(true);

    matrix.setFont(font5x7);
    matrix.drawChar(leftEdgeOffset + 0 * spaceBetweenCharacters,
            matrix.getScreenHeight() / 2, { 0xff, 0, 0 }, 'H');
    delay(delayBetweenCharacters);
    matrix.swapBuffers(true);
    matrix.drawChar(leftEdgeOffset + 1 * spaceBetweenCharacters,
            matrix.getScreenHeight() / 2, { 0xff, 0, 0 }, 'E');
    delay(delayBetweenCharacters);
    matrix.swapBuffers(true);
    matrix.drawChar(leftEdgeOffset + 2 * spaceBetweenCharacters,
            matrix.getScreenHeight() / 2, { 0xff, 0, 0 }, 'L');
    delay(delayBetweenCharacters);
    matrix.swapBuffers(true);
    matrix.drawChar(leftEdgeOffset + 3 * spaceBetweenCharacters,
            matrix.getScreenHeight() / 2, { 0xff, 0, 0 }, 'L');
    delay(delayBetweenCharacters);
    matrix.swapBuffers(true);
    matrix.drawChar(leftEdgeOffset + 4 * spaceBetweenCharacters,
            matrix.getScreenHeight() / 2, { 0xff, 0, 0 }, 'O');
    delay(delayBetweenCharacters);
    matrix.swapBuffers(true);

    delay(delayBetweenCharacters);

    matrix.fillScreen( { 0, 0x80, 0x80 });
    matrix.swapBuffers(true);

    matrix.drawString(leftEdgeOffset, matrix.getScreenHeight() / 2,
            { 0, 0xff, 0 }, "Hello!");

    delay(delayBetweenCharacters);
    matrix.swapBuffers(true);

    while (millis() < currentMillis + transitionTime)
        ;
}
void Animations::fontOptions() {
    matrix.setScrollColor( { 0xff, 0xff, 0xff });
    matrix.setScrollMode(wrapForward);
    matrix.setScrollSpeed(defaultScrollSpeed);

    matrix.setScrollFont(font6x10);
    matrix.scrollText(scrollBuffer, 1);

    const uint transitionTime = 5500;
    const int delayBetweenCharacters = 1000;
    const int leftEdgeOffset = 1;

    currentMillis = millis();

    matrix.fillScreen( { 0, 0x80, 0x80 });
    matrix.swapBuffers(true);

    matrix.setFont(font3x5);
    matrix.fillScreen( { 0, 0x80, 0x80 });
    matrix.drawString(leftEdgeOffset, matrix.getScreenHeight() / 2,
            { 0xff, 0, 0 }, "3x5");
    delay(delayBetweenCharacters);
    matrix.swapBuffers(true);

    matrix.setFont(font5x7);
    matrix.fillScreen( { 0, 0x80, 0x80 });
    matrix.drawString(leftEdgeOffset, matrix.getScreenHeight() / 2,
            { 0xff, 0, 0 }, "5x7");
    delay(delayBetweenCharacters);
    matrix.swapBuffers(true);

    matrix.setFont(font6x10);
    matrix.fillScreen( { 0, 0x80, 0x80 });
    matrix.drawString(leftEdgeOffset, matrix.getScreenHeight() / 2,
            { 0xff, 0, 0 }, "6x10");
    delay(delayBetweenCharacters);
    matrix.swapBuffers(true);

    matrix.setFont(font8x13);
    matrix.fillScreen( { 0, 0x80, 0x80 });
    matrix.drawString(leftEdgeOffset, matrix.getScreenHeight() / 2,
            { 0xff, 0, 0 }, "8x13");
    delay(delayBetweenCharacters);
    matrix.swapBuffers(true);

    while (millis() < currentMillis + transitionTime)
        ;
}

void Animations::star() {
    const int testBitmapWidth = 15;
    const int testBitmapHeight = 15;
    uint8_t testBitmap[] =
            { _______X, ________,
              ______XX, X_______,
              ______XX, X_______,
              ______XX, X_______,
              _____XXX, XX______,
              XXXXXXXX, XXXXXXX_,
              _XXXXXXX, XXXXXX__,
              __XXXXXX, XXXXX___,
              ___XXXXX, XXXX____,
              ____XXXX, XXX_____,
              ___XXXXX, XXXX____,
              ___XXXX_, XXXX____,
              __XXXX__, _XXXX___,
              __XX____, ___XX___,
              __X_____, ____X___, };

// "Drawing Functions"
    matrix.setScrollColor( { 0xff, 0xff, 0xff });
    matrix.setScrollMode(wrapForward);
    matrix.setScrollSpeed(defaultScrollSpeed);

    matrix.setScrollFont(font6x10);
    matrix.scrollText(scrollBuffer, 1);

    const uint transitionTime = 5500;
    currentMillis = millis();

    matrix.fillScreen( { 0, 0x80, 0x80 });
    matrix.swapBuffers(true);

    while (millis() < currentMillis + transitionTime) {
        matrix.drawMonoBitmap(
                random(matrix.getScreenWidth() + testBitmapWidth)
                        - testBitmapWidth,
                random(matrix.getScreenHeight() + testBitmapHeight)
                        - testBitmapHeight, testBitmapWidth, testBitmapHeight, {
                        (uint8_t) random(256), (uint8_t) random(256), 0 },
                testBitmap);
        matrix.swapBuffers(true);
        delay(100);
    }
}

void Animations::scrollAboveDrawing() {
    matrix.setScrollColor( { 0xff, 0xff, 0xff });
    matrix.setScrollMode(wrapForward);
    matrix.setScrollSpeed(defaultScrollSpeed);

    matrix.setScrollFont(font6x10);
    matrix.scrollText(scrollBuffer, 1);

    matrix.fillScreen(defaultBackgroundColor);
    matrix.swapBuffers(true);

    const uint transitionTime = 8000;

    currentMillis = millis();

    while (millis() - currentMillis < transitionTime) {
        rgb24 color;
        float fraction = ((float) millis() - currentMillis)
                / ((float) transitionTime / 2);

        if (millis() - currentMillis < transitionTime / 2) {
            color.red = 255 - 255.0 * fraction;
            color.green = 255.0 * fraction;
            color.blue = 0;
        } else {
            color.red = 0;
            color.green = 255 - 255.0 / 2 * (fraction - 1.0);
            color.blue = 255.0 * (fraction - 1.0);
        }

        matrix.setScrollColor(color);
    }
}

void Animations::scrollModes() {
    matrix.fillScreen(defaultBackgroundColor);
    matrix.swapBuffers(true);

    matrix.setScrollColor( { 0xff, 0xff, 0xff });
    matrix.setScrollMode(wrapForward);
    matrix.setScrollSpeed(defaultScrollSpeed);


    matrix.scrollText(scrollBuffer, 2);
    matrix.setFont(font3x5);
    matrix.drawString(0, matrix.getScreenHeight() / 2, { 0xff, 0xff, 0xff },
            "Modes");
    matrix.swapBuffers(true);

    uint transitionTime = 6000;
    currentMillis = millis();
    while (millis() - currentMillis < transitionTime)
        ;

    matrix.setScrollMode(bounceForward);
    matrix.scrollText(scrollBuffer, 2);

    transitionTime = 4500;
    currentMillis = millis();
    while (millis() - currentMillis < transitionTime)
        ;

    matrix.setScrollMode(stopped);
    matrix.scrollText(scrollBuffer, 1);

    transitionTime = 4500;
    currentMillis = millis();
    while (millis() - currentMillis < transitionTime)
        ;

    matrix.fillScreen(defaultBackgroundColor);
    matrix.swapBuffers(true);
}

void Animations::scrollSpeed() {
    matrix.setScrollColor( { 0xff, 0xff, 0xff });
    matrix.setScrollMode(wrapForward);
    matrix.setScrollSpeed(1);

    matrix.scrollText(scrollBuffer, 3);
    matrix.swapBuffers(true);

    const int maxScrollSpeed = 100;

    uint transitionTime = 7500;
    currentMillis = millis();
    while (millis() - currentMillis < transitionTime) {
        matrix.setScrollSpeed(
                /*maxScrollSpeed -*/maxScrollSpeed
                        * ((float) millis() - currentMillis) / transitionTime);
    }
}

void Animations::fonts() {
    matrix.setScrollColor( { 0xff, 0xff, 0xff });
    matrix.setScrollMode(wrapForward);
    matrix.setScrollSpeed(defaultScrollSpeed);

    matrix.setScrollOffsetFromEdge(1);

    matrix.setScrollFont(font3x5);
    matrix.scrollText(scrollBuffer, 1);
    while (matrix.getScrollStatus())
        ;

    matrix.setScrollFont(font5x7);
    matrix.scrollText(scrollBuffer, 1);
    while (matrix.getScrollStatus())
        ;

    matrix.setScrollFont(font6x10);
    matrix.scrollText(scrollBuffer, 1);
    while (matrix.getScrollStatus())
        ;

    matrix.setScrollFont(font8x13);
    matrix.scrollText(scrollBuffer, 1);
    while (matrix.getScrollStatus())
        ;

    matrix.setScrollOffsetFromEdge(defaultScrollOffset);
}

void  Animations::scrollPosition() {
    matrix.setScrollColor( { 0xff, 0xff, 0xff });
    matrix.setScrollMode(wrapForward);
    matrix.setScrollSpeed(defaultScrollSpeed);


    matrix.setScrollFont(font5x7);
    matrix.scrollText(scrollBuffer, 1);

    for (i = 0; i < 6; i++) {
        matrix.setScrollOffsetFromEdge(i * (matrix.getScreenHeight() / 6));
        delay(1000);
    }
    matrix.setScrollOffsetFromEdge(defaultScrollOffset);
}

void Animations::scrollRotation() {
    matrix.setFont(font3x5);
    matrix.setScrollFont(font5x7);

    matrix.setScrollColor( { 0xff, 0xff, 0xff });
    matrix.setScrollMode(wrapForward);
    matrix.setScrollSpeed(defaultScrollSpeed);


// rotate 90
    matrix.setRotation(rotation90);
    matrix.scrollText(scrollBuffer, 1);
    matrix.fillScreen(defaultBackgroundColor);
    matrix.drawString(1, matrix.getScreenHeight() / 2, { 0xff, 0xff, 0xff },
            "BACKGND");
    matrix.swapBuffers(true);
    while (matrix.getScrollStatus())
        ;

    matrix.setRotation(rotation180);
    matrix.scrollText(scrollBuffer, 1);
    matrix.fillScreen(defaultBackgroundColor);
    matrix.drawString(1, matrix.getScreenHeight() / 2, { 0xff, 0xff, 0xff },
            "BACKGND");
    matrix.swapBuffers(true);
    while (matrix.getScrollStatus())
        ;

    matrix.setRotation(rotation270);
    matrix.scrollText(scrollBuffer, 1);
    matrix.fillScreen(defaultBackgroundColor);
    matrix.drawString(1, matrix.getScreenHeight() / 2, { 0xff, 0xff, 0xff },
            "BACKGND");
    matrix.swapBuffers(true);
    while (matrix.getScrollStatus())
        ;

    matrix.scrollText(scrollBuffer, 1);
    matrix.setRotation(rotation0);
    matrix.fillScreen(defaultBackgroundColor);
    matrix.drawString(1, matrix.getScreenHeight() / 2, { 0xff, 0xff, 0xff },
            "BACKGND");
    matrix.swapBuffers(true);
    while (matrix.getScrollStatus())
        ;
}

void Animations::demoScrollReset() {
    matrix.setFont(font3x5);
    matrix.setScrollFont(font5x7);

    matrix.setScrollColor( { 0xff, 0xff, 0xff });
    matrix.setScrollMode(wrapForward);
    matrix.setScrollSpeed(defaultScrollSpeed);


    matrix.drawString(0, 0, { 0xff, 0xff, 0xff }, scrollBuffer);
    matrix.drawString(0, 6, { 0xff, 0xff, 0xff }, scrollBuffer);
    matrix.swapBuffers();

// rotate 90
    for (i = 3; i >= 0; i--) {
        char number = '0' + i % 10;
        char numberString[] = "0...";
        numberString[0] = number;
        matrix.scrollText(numberString, 1);
        delay(500);
        matrix.stopScrollText();
        delay(500);
    }
}

void Animations::brightness() {
    // "Drawing Functions"
    matrix.setScrollColor( { 0, 0, 0 });
    matrix.setScrollMode(wrapForward);
    matrix.setScrollSpeed(defaultScrollSpeed);

    matrix.setScrollFont(font6x10);
    matrix.scrollText(scrollBuffer, 1);

    const uint transitionTime = 6000;

    matrix.fillScreen( { 0xff, 0xff, 0xff });
    matrix.swapBuffers(true);

    matrix.setFont(font5x7);

    currentMillis = millis();

    while (millis() - currentMillis < transitionTime) {
        float fraction = ((float) millis() - currentMillis)
                / ((float) transitionTime / 2);

        if (fraction > 1.0)
            fraction = 2.0 - fraction;
        int brightness = fraction * 255.0;
        matrix.setBrightness(brightness);

        char value[] = "000";
        char percent[] = "100%";
        value[0] = '0' + brightness / 100;
        value[1] = '0' + (brightness % 100) / 10;
        value[2] = '0' + brightness % 10;
        percent[0] = '0' + (brightness * 100.0 / 255) / 100;
        percent[1] = '0' + (int) (brightness * 100.0 / 255) % 100 / 10;
        percent[2] = '0' + (int) (brightness * 100.0 / 255) % 10;

        matrix.fillScreen( { 0xff, 0xff, 0xff });
        matrix.drawString(0, 16, { 0, 0, 0 }, value);
        matrix.drawString(0, 24, { 0, 0, 0 }, percent);
        matrix.swapBuffers(true);
    }

    matrix.setBrightness(currentBrightness);
}

void Animations::rawBitman() {
    matrix.setScrollColor( { 0xff, 0, 0 });
    matrix.setScrollMode(wrapForward);
    matrix.setScrollSpeed(defaultScrollSpeed);

    matrix.setScrollFont(font6x10);
    matrix.scrollText(scrollBuffer, 1);

    const uint transitionTime = 7000;

    matrix.setFont(font5x7);

    currentMillis = millis();

    while (millis() - currentMillis < transitionTime) {
        float fraction = ((float) millis() - currentMillis)
                / ((float) transitionTime / 2);

        if (fraction > 1.0)
            fraction = 2.0 - fraction;
        int brightness = fraction * 255.0;
        matrix.setBrightness(brightness);

        char value[] = "000";
        char percent[] = "100%";
        value[0] = '0' + brightness / 100;
        value[1] = '0' + (brightness % 100) / 10;
        value[2] = '0' + brightness % 10;
        percent[0] = '0' + (brightness * 100.0 / 255) / 100;
        percent[1] = '0' + (int) (brightness * 100.0 / 255) % 100 / 10;
        percent[2] = '0' + (int) (brightness * 100.0 / 255) % 10;

        rgb24 *buffer = matrix.backBuffer();

        extern const bitmap_font weathericon;

        for (i = 0; i < 32 * matrix.getScreenHeight(); i++) {
            buffer[i].red = weathericon.Bitmap[i * 3 + 0];
            buffer[i].green = weathericon.Bitmap[i * 3 + 1];
            buffer[i].blue = weathericon.Bitmap[i * 3 + 2];
        }

        matrix.drawString(12, 16, { 0xff, 0, 0 }, value);
        matrix.drawString(12, 24, { 0xff, 0, 0 }, percent);
        matrix.swapBuffers(true);
    }

    matrix.setBrightness(currentBrightness);
}

void Animations::colorCorrection() {
    matrix.setScrollColor( { 0xff, 0, 0 });
    matrix.setScrollMode(wrapForward);
    matrix.setScrollSpeed(defaultScrollSpeed);

    matrix.setScrollFont(font6x10);
    matrix.scrollText(scrollBuffer, 1);

    const uint transitionTime = 10000;

    matrix.setFont(font5x7);

    currentMillis = millis();

    for (j = 0; j < 4; j++) {
        rgb24 *buffer = matrix.backBuffer();

        extern const bitmap_font weathericon;

        for (i = 0; i < 32 * matrix.getScreenHeight(); i++) {
            buffer[i].red = weathericon.Bitmap[i * 3 + 0];
            buffer[i].green = weathericon.Bitmap[i * 3 + 1];
            buffer[i].blue = weathericon.Bitmap[i * 3 + 2];
        }

        if (j % 2) {
            matrix.drawString(1, 16, { 0xff, 0, 0 }, scrollBuffer);
            matrix.setColorCorrection(cc24);
        } else {
            matrix.drawString(1, 16, { 0xff, 0, 0 }, scrollBuffer);
            matrix.setColorCorrection(ccNone);
        }
        // use swapBuffers(false) as background bitmap is fully drawn each time
        matrix.swapBuffers(false);
        delay(transitionTime / 4);
    }
    matrix.setColorCorrection(cc24);
}
