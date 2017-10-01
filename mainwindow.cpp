#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    flag = 0;

    ui->statusBar->showMessage("Init status");

    setStartPointButton = new QToolButton(this);
    setEndPointButton = new QToolButton(this);
    startButton = new QToolButton(this);
    clearButton = new QToolButton(this);
    openFileButton = new QToolButton(this);
    view = new QGraphicsView();
    scene = new GraphicsViewDisplay();

    view->setScene(scene);
    view->centerOn(0,0);

    setStartPointButton->setIcon(QIcon(":/icon/img/start.png"));
    setEndPointButton->setIcon(QIcon(":/icon/img/end.png"));
    startButton->setIcon(QIcon(":/icon/img/play.png"));
    clearButton->setIcon(QIcon(":/icon/img/clear.png"));
    openFileButton->setIcon(QIcon(":/icon/img/openfile.png"));

    ui->toolBar->addWidget(openFileButton);
    ui->toolBar->addSeparator();
    ui->toolBar->addWidget(setStartPointButton);
    ui->toolBar->addWidget(setEndPointButton);
    ui->toolBar->addSeparator();
    ui->toolBar->addWidget(startButton);
    ui->toolBar->addWidget(clearButton);
    ui->gridLayout->addWidget(view);

    connect(setStartPointButton, SIGNAL(pressed()), this, SLOT(Slot_SetStartButtonClicked()));
    connect(setEndPointButton, SIGNAL(pressed()), this, SLOT(Slot_SetEndButtonClicked()));
    connect(startButton, SIGNAL(pressed()), this, SLOT(Slot_StartButtonClicked()));
    connect(clearButton, SIGNAL(pressed()), this, SLOT(Slot_ClearButtonClicked()));
    connect(scene, SIGNAL(SignalForClearButtonState()), this, SLOT(Slot_ClearButtonstate()));
    connect(openFileButton, SIGNAL(pressed()), this, SLOT(Slot_OpenMapImg()));
    connect(this, SIGNAL(Signal_UpdateMapImg(QImage)), scene, SLOT(SlotOfUpdateMap(QImage)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::Slot_SetStartButtonClicked()
{
    ui->statusBar->showMessage("Set Start Point");

    if(flag == 2)
    {
        setEndPointButton->setEnabled(true);
    }

    flag = 1;
    scene->flag = flag;
    setStartPointButton->setEnabled(false);
}

void MainWindow::Slot_SetEndButtonClicked()
{
    ui->statusBar->showMessage("Set End Point");

    if(flag == 1)
    {
        setStartPointButton->setEnabled(true);
    }

    flag = 2;
    scene->flag = flag;
    setEndPointButton->setEnabled(false);
}

void MainWindow::Slot_StartButtonClicked()
{
    ClearButtonSate();
    scene->RunPlan();
}

void MainWindow::Slot_ClearButtonClicked()
{
    scene->ClearPath();
    ClearButtonSate();
}

void MainWindow::Slot_ClearButtonstate()
{
    ClearButtonSate();
}

void MainWindow::ClearButtonSate()
{
    setStartPointButton->setEnabled(true);
    setEndPointButton->setEnabled(true);

    flag = 0;
    scene->flag = flag;
}

void MainWindow::Slot_OpenMapImg()
{
    QString filePath = QFileDialog::getOpenFileName(this,tr("choose image"),"",tr(("Images (*.pgm *.bmp *.jpg)")));

    qDebug() << filePath;

    if(filePath.isEmpty())
    {
        return;
    }else
    {
        QImage img;

        if(!img.load(filePath))
        {
            qDebug() << "open map error";
            return;
        }

        emit Signal_UpdateMapImg(img);
    }
}

void MainWindow::wheelEvent(QWheelEvent *event)
{
    int num = event->delta()/8/15;

    if(num > 0)
        view->scale(2, 2);
    else
        view->scale(0.5, 0.5);
}

