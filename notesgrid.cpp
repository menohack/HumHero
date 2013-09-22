#include "notesgrid.h"

#include <QPainter>

NotesGrid::NotesGrid(QWidget *parent)
    : QWidget(parent)
{
    elapsed = 0;
    setFixedSize(800, 200);

    textPen = QPen(Qt::white);
    textFont.setPixelSize(50);

    //Create our master layout (it may contain sub layouts)
    layout = new QGridLayout;
    gridhead = new QGridLayout;
    grid = new QGridLayout;

    //Make our first text box
    QLabel * G = new QLabel(tr("G"));
    QLabel * F = new QLabel(tr("F"));
    QLabel * E = new QLabel(tr("E"));
    QLabel * D = new QLabel(tr("D"));
    QLabel * C = new QLabel(tr("C"));
    QLabel * B = new QLabel(tr("B"));
    QLabel * A = new QLabel(tr("A"));

    //Adds the text object to the grid layout at position 0,0
    //layout->addWidget(text, 0, 0);
    gridhead->addWidget(G, 0, 0);
    layout->addWidget(F, 1, 0);
    layout->addWidget(E, 2, 0);
    layout->addWidget(D, 3, 0);
    layout->addWidget(C, 4, 0);
    layout->addWidget(B, 5, 0);
    layout->addWidget(A, 6, 0);

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
