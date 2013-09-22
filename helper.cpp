/****************************************************************************
**
** Copyright (C) 2012 Nokia Corporation and/or its subsidiary(-ies).
** Contact: http://www.qt-project.org/
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** You may use this file under the terms of the BSD license as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of Nokia Corporation and its Subsidiary(-ies) nor
**     the names of its contributors may be used to endorse or promote
**     products derived from this software without specific prior written
**     permission.
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include <QtGui>
#include "helper.h"

#include "microphone.h"

//! [0]
Helper::Helper()
{
    QLinearGradient gradient(QPointF(50, -20), QPointF(80, 20));
    gradient.setColorAt(0.0, Qt::white);
    gradient.setColorAt(1.0, QColor(0xa6, 0xce, 0x39));

    background = QBrush(QColor(255, 255, 255));
    circleBrush = QBrush(gradient);
    circlePen = QPen(Qt::black);
    circlePen.setWidth(1);
    textPen = QPen(Qt::black);
    textFont.setPixelSize(50);

    microphone_start();


    in = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * SAMPLES_PER_FRAME);
    out = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * SAMPLES_PER_FRAME);

    mic_sample = new float[SAMPLES_PER_FRAME];
    window_sample = new float[SAMPLES_PER_FRAME];

    windowCount = 0;

    //Skip some low frequencies which tend to be noise
    xShift = 10;

    //Scale the frequencies to be larger than a pixel
    xScale = 20;
}

Helper::~Helper()
{
    fourier_free(in, out);
    delete [] mic_sample;
    delete [] window_sample;
}

//! [0]


double find_max(fftw_complex * in, int length)
{
    int max = -999;
    for (int i=0; i < length; i++)
        if (in[length][0] > max)
            max = in[i][0];
    return max;
}

double find_min(fftw_complex * in, int length)
{
    int min = 999;
    for (int i=0; i < length; i++)
        if (in[length][0] < min)
            min = in[i][0];
    return min;
}


void Helper::find_notes(float * frequencies, float ** notes, int * numNotes)
{
    *numNotes = 1;
    *notes = new float[*numNotes];

    float max = -999;
    float position = 0;

    for (int i=xShift; i < SAMPLES_PER_FRAME/2; i++)
    {
        float val = fabs(frequencies[i]);
        if (val > max)
        {
            max = val;
            position = i;
        }
    }

    if (max < 0.1)
        *notes[0] = 0.0;
    else
        *notes[0] = position;
}

//! [1]
void Helper::paint(QPainter *painter, QPaintEvent *event, int elapsed)
{
    painter->fillRect(event->rect(), background);
    //painter->translate(100, 100);
//! [1]

//! [2]
    painter->save();
    painter->setBrush(circleBrush);
    painter->setPen(circlePen);
    //painter->rotate(elapsed * 0.030);


    run_microphone(mic_sample, SAMPLES_PER_FRAME);
    //run_playback(mic_sample, SAMPLES_PER_FRAME);


    for (int i=0; i < SAMPLES_PER_FRAME; i++)
    {
        in[i][0] = mic_sample[i];
        in[i][1] = 0.0;
    }



    run_fourier(in, out, SAMPLES_PER_FRAME);

    //Reset the summation at the first window
    if (windowCount == NUM_WINDOWS)
        windowCount == 0;

    for (int i=0; i < SAMPLES_PER_FRAME; i++)
    {
        if (windowCount == 0)
            window_sample[i] = 0.0;
        window_sample[i] += out[i][0] / NUM_WINDOWS;
    }

    //double max = find_max(in, SAMPLES_PER_FRAME);
    //double min = find_min(in, SAMPLES_PER_FRAME);
    double max = 1.0;

    //if (abs(min) > abs(max))
    //    max = abs(min);

    //Scale the graph so that it is easier to see
    //max *= 1.1;



    int n = 1024;
    for (int i = 0; i < SAMPLES_PER_FRAME/xScale-xShift; i++) {
        //painter->drawPoint(i, GRAPH_HEIGHT/2 - GRAPH_HEIGHT/2 * in[i][0] / max);
        painter->drawLine(i*xScale, GRAPH_HEIGHT/2 - GRAPH_HEIGHT/2 * window_sample[i+xShift] / max, (i+1)*xScale, GRAPH_HEIGHT/2 - GRAPH_HEIGHT/2 * window_sample[i+xShift+1] / max);
    }

    float * notes;
    int numNotes;
    find_notes(window_sample, &notes, &numNotes);

    painter->restore();
//! [2]

//! [3]
    painter->setPen(textPen);
    painter->setFont(textFont);
    char buffer[32];

    if (notes[0] != 0.0)
    {
        snprintf(buffer, 32, "%f", notes[0]);
        painter->drawText(QRect(0, 0, 300, 100), Qt::AlignCenter, buffer);
    }
}
//! [3]
