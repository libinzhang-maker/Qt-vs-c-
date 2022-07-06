#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_WaKAwaka.h"
#include <QHBoxLayout>
#include <QListWidget>
#include <QtMultimedia/QMediaPlayer>	// VS向.pro文件添加代码的方式
#include <QLabel>
#include <qpushbutton.h>

class WaKAwaka : public QMainWindow
{
    Q_OBJECT

public:
    WaKAwaka(QWidget *parent = nullptr);
    ~WaKAwaka();
private:
    QMenu* file_menu;//文件按钮
    QAction* act;//监听import指令
    QMenuBar* menuBar;//按钮栏
    QHBoxLayout* listLayout;//存放歌曲列表
    QVBoxLayout* mainLayout;//主层
    QWidget* mainWidget;//
    QListWidget* listWidget;//列表窗
    QMediaPlayer* player; //定义一个播放器对象指针
    QStringList filenames;//导入文件时使用
    QHBoxLayout* playControl;//播放控制区域，暂停开始等等
    QVBoxLayout* play_pause_slide;
    QHBoxLayout* play_pause;
    QHBoxLayout* slider_layout;
    QPushButton* playorpause;
    QPushButton* playmode;
    QPushButton* next;
    QPushButton* back;
    QLabel* totaltimeLabel;//曲长标签
    QSlider* slider;//进度条
    QWidget* playControlWidget;//播放控制窗
    QString musicFullName;
    QString maxlenText;
    QString nowlenText;

    int flag = 1;
    int playNow = 0;//正在播放曲目控制
    int mode = 1;
    Ui::WaKAwakaClass ui;
    void creatMenu();
    void createLayout();
    void addListWidget();
    void  addPlayControl();
    void changeList();
    void inputInformation();//错误提示
    int generateRandomNumber();
    void videoPositionChanged(qint64 position);
    void durationChanged(qint64 duration);
private slots:
    void listWidgetItemActivated(QListWidgetItem* activatedItem);
    void trigerImportMenu(QAction* act);
    void controlPlay_pause();
    void playNext();
    void playBack();
    void controlPlayMode();
    void mediaStatusChanged(QMediaPlayer::MediaStatus status);
    void sliderMovedEvent();
    void sliderPressedEvent();
    void sliderReleasedEvent();
};


