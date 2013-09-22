#ifndef NOTESGRID_H
#define NOTESGRID_H

#include <QWidget>
#include <QBrush>
#include <QFont>
#include <QPen>
#include <QGridLayout>
#include <QLabel>


QT_BEGIN_NAMESPACE
class QPaintEvent;
QT_END_NAMESPACE

class NotesGrid : public QWidget
{
    Q_OBJECT

public:
    NotesGrid(QWidget *parent);

public slots:
    void animate();

protected:
    void paintEvent(QPaintEvent *event);

private:
    QFont textFont;
    QPen textPen;
    QGridLayout * layout;
    QGridLayout * gridhead;
    QGridLayout * grid;
    QLabel * text;
    int elapsed;
};

#endif // NOTESGRID_H
