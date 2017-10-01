#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QToolButton>
#include <QGraphicsView>
#include <QWheelEvent>
#include "graphicsviewdisplay.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

signals:
    void Signal_UpdateMapImg(QImage img);

private slots:
    void Slot_SetStartButtonClicked();
    void Slot_SetEndButtonClicked();
    void Slot_StartButtonClicked();
    void Slot_ClearButtonClicked();
    void Slot_ClearButtonstate(); 
    void Slot_OpenMapImg();

private:
    void ClearButtonSate();
    void wheelEvent(QWheelEvent* event);

    Ui::MainWindow *ui;

    QToolButton *setStartPointButton;
    QToolButton *setEndPointButton;
    QToolButton *startButton;
    QToolButton *clearButton;
    QToolButton *openFileButton;

    QGraphicsView *view;
    GraphicsViewDisplay *scene;

    int flag;
};

#endif // MAINWINDOW_H
