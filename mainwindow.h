#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QThread>
//#include <QtMultimedia>
//#include <QScreen>
//#include <QPixmap>
//#include <QTimer>
//#include <QLabel>
//#include <QVBoxLayout>
//#include <QFile>
//#include <QProcess>
//#include <QFileDialog>
//#include <QMutex>

#include "myrecorder.h"
#include "recorderworker.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
//    void recordScreen();
//    void savePi();
    void timeCount(QTimer&);
//    void settings();


    void appear(QPixmap);
public slots:
    void on_recordButton_clicked();

    void on_pauseButton_clicked();


private slots:
    void on_actionsave_as_triggered();

private:
    Ui::MainWindow *ui;
    QLabel *imageLabel;

    MyRecorder recorder;
    recorderWorker worker;


//    QReadWriteLock lock;


    QTimer* timer;
    QTimer duration;

//   // QScreen *screen;
    QList<QPixmap> frames;

//    QMediaCaptureSession session;
//    QAudioInput audioInput;
//    QMediaRecorder audioRecorder;

//    int mpcount;
    QString outputDir;
    QString tempDir;
//    QPoint startPos;

    int secondCount=0;
    int minuteCount=0;
    int hourCount=0;




};
#endif // MAINWINDOW_H
