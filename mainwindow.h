#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QThread>

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

    void timeCount(QTimer&);

    void sliderMove(QTimer&);

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

    QTimer* timer;
    QTimer duration;

    QList<QPixmap> frames;

    QString outputDir;
    QString tempDir;

    int secondCount=0;
    int minuteCount=0;
    int hourCount=0;




};
#endif // MAINWINDOW_H
