#include "recorderworker.h"

recorderWorker::recorderWorker(QObject *parent):
    QThread(parent)
{
    QString tempDir = "/pub/audiorecord/";
    QDir().mkpath(tempDir);
    session.setAudioInput(&audioInput);
    session.setRecorder(&audioRecorder);
    audioRecorder.setQuality(QMediaRecorder::VeryHighQuality);
    audioRecorder.setOutputLocation(QUrl::fromLocalFile(tempDir+"/test"));

}

void recorderWorker::run()
{

    audioRecorder.record();

    QList<QScreen *>screens=QGuiApplication::screens();
    QMutexLocker lock(&mutex);
    foreach (QScreen *screen, screens){
        QPixmap screenshot=screen->grabWindow(0);

        locker.lockForWrite();
        frames.append(screenshot);
        emit sendPix(screenshot);
        locker.unlock();

    }
        screens.clear();
}
void recorderWorker::pause()
{
    audioRecorder.pause();
}

void recorderWorker::stop()
{
    audioRecorder.stop();
}

