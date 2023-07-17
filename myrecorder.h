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

class MyRecorder : public QObject
{
    Q_OBJECT
public:
    explicit MyRecorder(QObject *parent = nullptr);

    void recordScreen();
    void savePi();
    void timeCount(QTimer&);
    void settings();
    void merge();

    QList getFrames();
signals:


private:
    QReadWriteLock lock;


    QTimer* timer;
    QTimer duration;

   // QScreen *screen;
    QList<QPixmap> frames;

    QMediaCaptureSession session;
    QAudioInput audioInput;
    QMediaRecorder audioRecorder;

    int mpcount;
    QString outputDir;
//    QString tempDir;
    QPoint startPos;

    int secondCount=0;
    int minuteCount=0;
    int hourCount=0;
};

#endif // MYRECORDER_H
