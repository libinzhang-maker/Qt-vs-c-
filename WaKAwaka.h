#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_WaKAwaka.h"
#include <QHBoxLayout>
#include <QListWidget>
#include <QtMultimedia/QMediaPlayer>	// VS��.pro�ļ���Ӵ���ķ�ʽ
#include <QLabel>
#include <qpushbutton.h>

class WaKAwaka : public QMainWindow
{
    Q_OBJECT

public:
    WaKAwaka(QWidget *parent = nullptr);
    ~WaKAwaka();
private:
    QMenu* file_menu;//�ļ���ť
    QAction* act;//����importָ��
    QMenuBar* menuBar;//��ť��
    QHBoxLayout* listLayout;//��Ÿ����б�
    QVBoxLayout* mainLayout;//����
    QWidget* mainWidget;//
    QListWidget* listWidget;//�б�
    QMediaPlayer* player; //����һ������������ָ��
    QStringList filenames;//�����ļ�ʱʹ��
    QHBoxLayout* playControl;//���ſ���������ͣ��ʼ�ȵ�
    QVBoxLayout* play_pause_slide;
    QHBoxLayout* play_pause;
    QHBoxLayout* slider_layout;
    QPushButton* playorpause;
    QPushButton* playmode;
    QPushButton* next;
    QPushButton* back;
    QLabel* totaltimeLabel;//������ǩ
    QSlider* slider;//������
    QWidget* playControlWidget;//���ſ��ƴ�
    QString musicFullName;
    QString maxlenText;
    QString nowlenText;

    int flag = 1;
    int playNow = 0;//���ڲ�����Ŀ����
    int mode = 1;
    Ui::WaKAwakaClass ui;
    void creatMenu();
    void createLayout();
    void addListWidget();
    void  addPlayControl();
    void changeList();
    void inputInformation();//������ʾ
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


