#ifndef RECORDERWORKER_H
#define RECORDERWORKER_H

#include <QThread>
#include <QObject>
#include <QMutex>
#include <QReadWriteLock>
#include <QtMultimedia>
#include <QScreen>
#include <QPixmap>
#include <QList>
#include <QTimer>


class recorderWorker:public QThread
{
    Q_OBJECT
public:
    recorderWorker(QObject* parent=nullptr);
    void run() override;
    void pause();
    void stop();

signals:
    void sendPix(QPixmap);


private:
    QReadWriteLock locker;
    QMutex mutex;

    QList<QPixmap> frames;

    QMediaCaptureSession session;
    QAudioInput audioInput;
    QMediaRecorder audioRecorder;

    QTimer timer;


};

#endif // RECORDERWORKER_H
