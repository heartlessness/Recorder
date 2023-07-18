#include "myrecorder.h"

MyRecorder::MyRecorder(QObject *parent)
    : QObject(parent)
{
}


void MyRecorder::merge(QString outputDir)
{
           // 使用 FFmpeg 将帧图片合成为视频
           QString ffmpegCommand = QString("/usr/bin/ffmpeg");
           QStringList arguments;
           arguments<<"-framerate"<<"10"<<"-i"<<"/pub/records/frame_%04d.png"<<"-i"<<"/pub/audiorecord/test.m4a"<<"-c:v"<<"libx264"<<"-pix_fmt"<<"yuv420p"<<"-c:a"<<"aac"<<"-y"<<outputDir+".mp4";

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

void MyRecorder::savePix(QPixmap framelist)
{

    QString tempDir = "/pub/records/";
    QDir().mkpath(tempDir);
    QString outputTemp=tempDir+"/frame_%04.png";

    QMutexLocker locker(&mutex);
    lock.lockForRead();

    QString frameFileName = outputTemp.arg(countPix, 4, 10, QChar('0'));
    framelist.save(frameFileName,"PNG");
    countPix++;
    lock.unlock();

}

QList<QPixmap> MyRecorder::getFrames()
{
    return frames;
}
