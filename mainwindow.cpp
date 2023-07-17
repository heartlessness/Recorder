#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),ui(new Ui::MainWindow)
{
    ui->setupUi(this);

//    QVBoxLayout *mainlayout=new QVBoxLayout(this);




    QVBoxLayout *layout=new QVBoxLayout(ui->recordwidget);
//    ui->recordwidget->setLayout(layout);
    imageLabel=new QLabel;
    layout->addWidget(imageLabel);



    QVBoxLayout *Buttonlayout=new QVBoxLayout;
    Buttonlayout->addWidget(ui->pauseButton);
    Buttonlayout->addWidget(ui->recordButton);


//    this->layout()->addChildLayout(layout);
//    this->layout()->addChildLayout(Buttonlayout);

    connect(&worker,&recorderWorker::sendPix,this,&MainWindow::appear);

    connect(&worker,&recorderWorker::sendPix,&recorder,&MyRecorder::savePix);




}

MainWindow::~MainWindow()
{
    delete ui;
    delete timer;
    delete imageLabel;
}

void MainWindow::appear(QPixmap pix)
{
//    foreach (QPixmap frame,pix) {
        imageLabel->setPixmap(pix);
        imageLabel->setScaledContents(true);
//    }
}


void MainWindow::on_recordButton_clicked()
{

    timer=new QTimer;

    timer->start(0.003);

    connect(timer,&QTimer::timeout,&worker,&recorderWorker::run);

    //worker.start();


    //audioRecorder.record();

    duration.setInterval(1000);

    duration.start();
    timeCount(duration);


}


void MainWindow::on_pauseButton_clicked()
{
    timer->stop();
    worker.pause();
    duration.stop();

}


void MainWindow::timeCount(QTimer& time)
{

    connect(&time,&QTimer::timeout,[&]{
        secondCount++;

        if(secondCount==60){
             secondCount=0;
             minuteCount++;
             if(minuteCount==60){
                 minuteCount=0;
                 hourCount++;
             }
        }
        QString timeCounts="%1:%2:%3";
        QString timesum=timeCounts.arg(hourCount, 2, 10, QChar('0')).arg(minuteCount, 2, 10, QChar('0')).arg(secondCount, 2, 10, QChar('0'));
        ui->timelabel->setText(timesum);
    });
}




void MainWindow::on_actionsave_as_triggered()
{
    timer->stop();
    worker.stop();
    duration.stop();

    outputDir=QFileDialog::getSaveFileName(nullptr,tr("save file"),QDir::homePath(),".mp4");

    if(!outputDir.isEmpty()){

        recorder.merge(outputDir);


    }
}

