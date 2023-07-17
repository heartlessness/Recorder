#include "myrecorder.h"

MyRecorder::MyRecorder(QObject *parent)
    : QObject{parent}
{

    QString tempDir = "/pub/audiorecord/";
    QDir().mkpath(tempDir);
    session.setAudioInput(&audioInput);
    session.setRecorder(&audioRecorder);
    audioRecorder.setQuality(QMediaRecorder::VeryHighQuality);
    audioRecorder.setOutputLocation(QUrl::fromLocalFile(tempDir+"/test"));
}


void MyRecorder::recordScreen()
{


    audioRecorder.record();
        QList<QScreen *>screens=QGuiApplication::screens();
        foreach (QScreen *screen, screens){
            QPixmap screenshot=screen->grabWindow(0);

            lock.lockForWrite();
            frames.append(screenshot);
            lock.unlock();
        }
        screens.clear();
    emit sendPixmap(frames);



}


void MyRecorder::merge(QString outputDir)
{

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



        frames.clear();
        QDir("/pub/records/").removeRecursively();
        QDir("/pub/audiorecord/").removeRecursively();
}

void MyRecorder::pause()
{
    audioRecorder.pause();
}

void MyRecorder::stop()
{
    audioRecorder.stop();
}


QList<QPixmap> MyRecorder::getFrames()
{
    return frames;
}
