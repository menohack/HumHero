#include "notesgrid.h"

#include <QPainter>
#include <QPushButton>

NotesGrid::NotesGrid(QWidget *parent)
    : QWidget(parent)
{
    elapsed = 0;
    setFixedSize(800, 200);

    textPen = QPen(Qt::white);
    textFont.setPixelSize(50);

    //Create our master layout (it may contain sub layouts)
    layout = new QGridLayout;

    //Create the grid for the labels
    labels = new QGridLayout;

    //Create the grid for the notes
    notes = new QGridLayout;

    //Make our first text box
    QLabel * G = new QLabel(tr("G"));
    QLabel * F = new QLabel(tr("F"));
    QLabel * E = new QLabel(tr("E"));
    QLabel * D = new QLabel(tr("D"));
    QLabel * C = new QLabel(tr("C"));
    QLabel * B = new QLabel(tr("B"));
    QLabel * A = new QLabel(tr("A"));

    //Add the labels to the left labels layout
    labels->addWidget(G, 0, 0);
    labels->addWidget(F, 1, 0);
    labels->addWidget(E, 2, 0);
    labels->addWidget(D, 3, 0);
    labels->addWidget(C, 4, 0);
    labels->addWidget(B, 5, 0);
    labels->addWidget(A, 6, 0);

    notes->setHorizontalSpacing(20);
    notes->setVerticalSpacing(20);
    notes->addWidget(new QPushButton(tr("H")), 4, 2);
    notes->addWidget(new QPushButton(tr("Q")), 4, 10);

    //Add the two layouts to our master layout
    layout->addLayout(labels, 0, 0);
    layout->addLayout(notes, 0, 1);

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
