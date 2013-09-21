#include "notesgrid.h"

#include <QPainter>

NotesGrid::NotesGrid(QWidget *parent)
    : QWidget(parent)
{
    elapsed = 0;
    setFixedSize(1024, 200);

    textPen = QPen(Qt::white);
    textFont.setPixelSize(50);

    //Create our master layout (it may contain sub layouts)
    layout = new QGridLayout;

    //Make our first text box
    text = new QLabel(tr("GridLayout"));

    QLabel * newLabel = new QLabel(tr("Hello world"));

    //Adds the text object to the grid layout at position 0,0
    layout->addWidget(text, 0, 0);
    layout->addWidget(newLabel, 0, 1);

    //This only needs to happen once you have filled your layout
    setLayout(layout);
}

void NotesGrid::animate()
{
    repaint();
}

void NotesGrid::paintEvent(QPaintEvent *event)
{
    QPainter painter;
    painter.begin(this);
    painter.setRenderHint(QPainter::Antialiasing);

    /*
    painter.setPen(textPen);
    painter.setFont(textFont);
    painter.drawText(QRect(0, 0, 400, 100), Qt::AlignCenter, "NotesGrid");
    */

    painter.end();
}
