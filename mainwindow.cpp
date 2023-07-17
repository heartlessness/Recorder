#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QVBoxLayout *layout=new QVBoxLayout;
    ui->recordwidget->setLayout(layout);
    imageLabel=new QLabel;
    layout->addWidget(imageLabel);

    recorder.settings();
//    settings();
//    timeCount(duration);

}

MainWindow::~MainWindow()
{
    delete ui;
//    delete timer;
    delete imageLabel;
}

//void MainWindow::recordScreen()
//{


//    QList<QScreen *>screens=QGuiApplication::screens();
//    foreach (QScreen *screen, screens){
//        QPixmap screenshot=screen->grabWindow(0);

//        lock.lockForWrite();
//        frames.append(screenshot);
//        lock.unlock();

//        imageLabel->setPixmap(screenshot);
//        imageLabel->setScaledContents(true);

//    }
//    screens.clear();

//}

//void MainWindow::savePi()
//{

//    QString tempDir = "/pub/records/";
//    QDir().mkpath(tempDir);
//    QString outputTemp=tempDir+"/frame_%04.png";
//    lock.lockForRead();
//    if(!frames.empty()){
//    for (int i = 0; i < frames.size(); ++i) {
//            QString frameFileName = outputTemp.arg(i, 4, 10, QChar('0'));
//            frames.at(i).save(frameFileName,"PNG");
//        }
//}
//    lock.unlock();


//    frames.clear();
//    QDir(tempDir).removeRecursively();

//}


void MainWindow::on_recordButton_clicked()
{


    recorder.recordScreen();
    frames=recorder.getFrames();
    foreach (QPixmap frame,frames) {
        imageLabel->setPixmap(frame);
        imageLabel->setScaledContents(true);

    }

//    timer=new QTimer;
//    connect(timer,&QTimer::timeout,this,&MainWindow::recordScreen);
//    timer->start(30);
//    audioRecorder.record();

//    duration.setInterval(1000);

//    duration.start();

}


void MainWindow::on_pauseButton_clicked()
{
    timer->stop();
    audioRecorder.pause();

}


void MainWindow::on_saveButton_clicked()
{

    timer->stop();
    audioRecorder.stop();
    outputDir=QFileDialog::getSaveFileName(nullptr,tr("save file"),QDir::homePath(),".mp4");

    if(!outputDir.isEmpty()){
       QFile file(outputDir);
       if(file.open(QIODevice::WriteOnly)){
           file.close();
       }
       //savePi();
       QString tempDir = "/pub/records/";
       QDir().mkpath(tempDir);
       QString outputTemp=tempDir+"/frame_%04.png";
        lock.lockForRead();
       if(!frames.empty()){
       for (int i = 0; i < frames.size(); ++i) {
               QString frameFileName = outputTemp.arg(i, 4, 10, QChar('0'));
               frames.at(i).save(frameFileName,"PNG");
           }
   }
       lock.unlock();
           // 使用 FFmpeg 将帧图片合成为视频
           QString ffmpegCommand = QString("/usr/bin/ffmpeg");
           QStringList arguments;
           arguments<<"-framerate"<<"30"<<"-i"<<"/pub/records/frame_%04d.png"<<"-i"<<"/pub/audiorecord/test.m4a"<<"-c:v"<<"libx264"<<"-pix_fmt"<<"yuv420p"<<"-c:a"<<"aac"<<"-y"<<outputDir+".mp4";

           QProcess recordProcess;
           recordProcess.execute(ffmpegCommand,arguments);
           if(recordProcess.state()==QProcess::Running){
               if(recordProcess.waitForFinished()){
                   qDebug()<<"ok";
               }
               else
                   qDebug()<<"no";
           }

    }

        frames.clear();
        QDir("/pub/records/").removeRecursively();
        QDir("/pub/audiorecord/").removeRecursively();

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

void MainWindow::settings()
{
    QString tempDir = "/pub/audiorecord/";
    QDir().mkpath(tempDir);
    session.setAudioInput(&audioInput);
    session.setRecorder(&audioRecorder);
    audioRecorder.setQuality(QMediaRecorder::VeryHighQuality);
    audioRecorder.setOutputLocation(QUrl::fromLocalFile(tempDir+"/test"));


}


