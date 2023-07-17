#ifndef MYRECORDER_H
#define MYRECORDER_H

#include <QObject>
#include <QtMultimedia>
#include <QScreen>
#include <QPixmap>
#include <QTimer>
#include <QLabel>
#include <QVBoxLayout>
#include <QFile>
#include <QProcess>
#include <QFileDialog>
#include <QMutex>
#include <atomic>

#include "recorderworker.h"

class MyRecorder : public QObject
{
    Q_OBJECT
public:
    explicit MyRecorder(QObject *parent = nullptr);


    void recordScreen();

    void merge(QString);
    void pause();
    void stop();

    void savePix(QPixmap);
    QList<QPixmap> getFrames();
signals:

    void sendPixmap(QPixmap);

private:

    QReadWriteLock lock;


    QTimer* timer;
    QTimer duration;


    std::atomic<int> countPix=0;
    QList<QPixmap> frames;
    QMutex mutex;

    QMediaCaptureSession session;
    QAudioInput audioInput;
    QMediaRecorder audioRecorder;

    int secondCount=0;
    int minuteCount=0;
    int hourCount=0;
};

#endif // MYRECORDER_H
