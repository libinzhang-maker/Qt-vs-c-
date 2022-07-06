#include "WaKAwaka.h"
#pragma execution_character_set("utf-8")
#include <Qt>
#include <QtDebug>
#include <QHBoxLayout>
#include <QListWidget>
#include <qfiledialog.h>
#include <qpushbutton.h>
#include <QSlider>
#include <QRandomGenerator>
#include <qtimer.h>
#include <QTime>
#include<QPainter>
#include <qthread.h>

WaKAwaka::WaKAwaka(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);

    this->resize(1500, 900);
;   this->setWindowTitle("wakawaka");
    this->setWindowIcon(QIcon(":/WaKAwaka/images/exeicon.png"));
    //this->setStyleSheet("#mainWindow{border-image:url(:/new/prefix1/images/mainwindowImage.jpg);}");
    this->setStyleSheet("QWidget{background-color:rgb(99,187,207);}");
    creatMenu();
    createLayout();
    addListWidget();
    addPlayControl();

}



WaKAwaka::~WaKAwaka()
{}

void WaKAwaka::trigerImportMenu(QAction* act) {
    if (act->text() == "import") {
        player = new QMediaPlayer;
        filenames = QFileDialog::getOpenFileNames(this, "Open File", "", "Music(*.mp3 *.flac *.ape);;All files (*.*)");
        for (int i = 0; i < filenames.count(); i++) {
            QFileInfo fileInfo(filenames.at(i));
            QString fileName = fileInfo.fileName();
            QListWidgetItem* item = new QListWidgetItem; //�����б���
            item->setIcon(QPixmap(":/WaKAwaka/images/����01.png")); //�����б���ͼ��
            item->setText(fileName);//������ʾ�ı���������ʾ����
            item->setData(Qt::UserRole, filenames.at(i));
            listWidget->addItem(item);//����б���б��
        }
    }
}

void WaKAwaka::creatMenu() {
    file_menu = new QMenu("File");

    act = new QAction(QIcon(":/WaKAwaka/images/file.png"),"import", this);

    file_menu->addAction(act);

    menuBar = new QMenuBar(this);

    menuBar->addMenu(file_menu);

    this->setMenuBar(menuBar);
    connect(menuBar, SIGNAL(triggered(QAction*)), this, SLOT(trigerImportMenu(QAction*)));
}

void WaKAwaka::createLayout() {
    mainWidget = new QWidget;
    this->setCentralWidget(mainWidget);
   
    //����Ŀ¼
    listLayout = new QHBoxLayout;
    //���ſ���;
    playControl = new QHBoxLayout();
    //����
    mainLayout = new QVBoxLayout;
    mainLayout->addLayout(listLayout,8);
    mainLayout->addLayout(playControl,2);
    mainWidget->setLayout(mainLayout);
}

void WaKAwaka::addListWidget() {
    listWidget =  new QListWidget;
    connect(listWidget, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(listWidgetItemActivated(QListWidgetItem*)));
    listLayout->addWidget(listWidget);
}
void WaKAwaka::changeList() {
    for (int i = 0; i < listWidget->count(); i++)//�����б�����������ñ���ɫ��ǰ��ɫ������ͼ��
    {
        listWidget->item(i)->setForeground(QColor(0, 0, 0));
        listWidget->item(i)->setBackground(QColor(99, 187, 207));
        listWidget->item(i)->setIcon(QPixmap(":/WaKAwaka/images/����01.png"));
    }
    listWidget->item(playNow)->setForeground(QColor(255, 0, 0));
    listWidget->item(playNow)->setBackground(QColor(0, 255, 0));
    listWidget->item(playNow)->setIcon(QPixmap(":/WaKAwaka/images/playing.png"));
    //�������б���ʾ��ͬ������
    QString musicFullName = listWidget->item(playNow)->data(Qt::UserRole).toString();
    QFileInfo fileInfo(musicFullName); //�����ļ���Ϣ�����fileInfo
    QString fileName = fileInfo.fileName(); //��fileInfo�л���ļ�������·����
    //��ʼ��ťͬ��
    playorpause->setIcon(QPixmap(":/WaKAwaka/images/media_pause_96p.bmp"));
    flag = 1;
}

void WaKAwaka::controlPlay_pause() {
    if (flag == 1) {
        flag = 0;
        player->play();
        playorpause->setIcon(QPixmap(":/WaKAwaka/images/media_pause_96p.bmp"));
    }
    else {
        flag = 1;
        player->pause();
        playorpause->setIcon(QPixmap(":/WaKAwaka/images/media_play_96p.bmp"));
    }
}

void WaKAwaka::playNext()
{
    //��һ��1.ĩβ��ת�ص�һ��2.����ĩβ���Ӽ�
    if (playNow == listWidget->count() - 1) {
        playNow = 0;
    }
    else {
        playNow++;
    }
    QString musicFullName = listWidget->item(playNow)->data(Qt::UserRole).toString(); //����û����ݣ�Ҳ������Ϊ�ļ�ȫ���������͵�����������
    player->setMedia(QUrl::fromLocalFile(musicFullName));//���ò�������ý���ļ�
    player->play();//��ʼ����
    //�б���ʾͬ��
    changeList();
}

void WaKAwaka::playBack()
{
    //��һ������λ�ã�ת����������ļ���
    if (playNow == 0) {
        playNow = listWidget->count() - 1;
    }
    else {
        playNow--;
    }
    QString musicFullName = listWidget->item(playNow)->data(Qt::UserRole).toString(); //����û����ݣ�Ҳ������Ϊ�ļ�ȫ���������͵�����������
    player->setMedia(QUrl::fromLocalFile(musicFullName));//���ò�������ý���ļ�
    player->play();//��ʼ����
    //�б���ʾͬ��
    changeList();//����changeList����
}


void WaKAwaka::controlPlayMode()
{
    if (mode == 1)
    {
        mode++;
        playmode->setIcon(QPixmap(":/WaKAwaka/images/media_repeat_96px.bmp"));
    }
    else if (mode == 2)
    {
        mode++;
        playmode->setIcon(QPixmap(":/WaKAwaka/images/media_shuffle_96px.bmp"));
    }
    else if(mode == 3) {
        mode = 1;
        playmode->setIcon(QPixmap(":/WaKAwaka/images/order.png"));
        
    }
}

//�����Դ��ĺ�������1.˳��ֱ����nextMusic��2.ѭ�����ı�playNow3.�����palyNowȡ1-list.count�������
void WaKAwaka::mediaStatusChanged(QMediaPlayer::MediaStatus status)
{
    if (status == QMediaPlayer::InvalidMedia)   //�޷�����ý���ļ������������Ϣ
    {
        inputInformation();
    }
    else if (status == QMediaPlayer::EndOfMedia) //��ǰ�ļ����Ž�����������һ�ף�
    {
        if (mode == 1) {
            playNext();
        }
        else if (mode == 2) {
            QString musicFullName = listWidget->item(playNow)->data(Qt::UserRole).toString(); //����û����ݣ�Ҳ������Ϊ�ļ�ȫ���������͵�����������
            player->setMedia(QUrl::fromLocalFile(musicFullName));//���ò�������ý���ļ�
            player->play();//��ʼ����
            //�б���ʾͬ��
            changeList();//����changeList����
        }
        else {
            playNow = generateRandomNumber();
            QString musicFullName = listWidget->item(playNow)->data(Qt::UserRole).toString(); //����û����ݣ�Ҳ������Ϊ�ļ�ȫ���������͵�����������
            player->setMedia(QUrl::fromLocalFile(musicFullName));//���ò�������ý���ļ�
            player->play();//��ʼ����
            //�б���ʾͬ��
            changeList();//����changeList����
        }
    }
}
void WaKAwaka::inputInformation()
{
    qDebug() << "�ļ��޷�����" << endl;
}
//���������
int WaKAwaka::generateRandomNumber()
{
    int playRandom;
    QRandomGenerator(QTime(0, 0, 0).secsTo(QTime::currentTime()));
    do {
        playRandom = qrand() % listWidget->count();
    } while (playNow == playRandom);
    return playRandom;
}

void WaKAwaka::addPlayControl()
{
    int size = 50;
    playorpause = new QPushButton;
    playorpause->setIcon(QPixmap(":/WaKAwaka/images/media_play_96p.bmp"));
    playorpause->setFixedSize(size, size);
    playorpause->setEnabled(false);
    connect(playorpause, &QPushButton::clicked, this, &WaKAwaka::controlPlay_pause);
    playmode = new QPushButton;
    playmode->setIcon(QPixmap(":/WaKAwaka/images/order.png"));
    playmode->setFixedSize(size,size);
    playmode->setEnabled(false);
    connect(playmode, &QPushButton::clicked, this, &WaKAwaka::controlPlayMode);
    next = new QPushButton;
    next->setIcon(QPixmap(":/WaKAwaka/images/media_end_96px.bmp"));
    next->setFixedSize(size, size);
    next->setEnabled(false);
    connect(next, &QPushButton::clicked, this, &WaKAwaka::playNext);
    back = new QPushButton;
    back->setIcon(QPixmap(":/WaKAwaka/images/media_back_96px.bmp"));
    back->setFixedSize(size, size);
    back->setEnabled(false);
    connect(back, &QPushButton::clicked, this, &WaKAwaka::playBack);
    play_pause = new QHBoxLayout;
    play_pause->addWidget(playmode,2.5);
    play_pause->addWidget(back,2.5);
    play_pause->addWidget(playorpause,2.5);
    play_pause->addWidget(next,2.5);

    slider = new QSlider;
    slider->setRange(1, 100); //�趨���ݷ�Χ
    slider->setSingleStep(5); //�趨���β���
    slider->setPageStep(5); //�趨PageUp��PageDown����
    slider->setFixedWidth(600); //�趨�ؼ��̶����
    slider->setOrientation(Qt::Horizontal); //�趨�ؼ���ʾ��λ
    slider->setStyleSheet("  \
     QSlider::add-page:Horizontal\
     {     \
        background-color: rgb(87, 97, 106);\
        height:4px;\
     }\
     QSlider::sub-page:Horizontal \
    {\
        background-color:qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(231,80,229, 255), stop:1 rgba(7,208,255, 255));\
        height:4px;\
     }\
    QSlider::groove:Horizontal \
    {\
        background:transparent;\
        height:6px;\
    }\
    QSlider::handle:Horizontal \
    {\
        height: 30px;\
        width:8px;\
        border-image: url(:/images/ic_music_thumb.png);\
        margin: -8 0px; \
    }\
    ");
    connect(slider, &QSlider::sliderMoved, this, &WaKAwaka::sliderMovedEvent);
    connect(slider, &QSlider::sliderPressed, this, &WaKAwaka::sliderPressedEvent);
    connect(slider, &QSlider::sliderReleased, this, &WaKAwaka::sliderReleasedEvent);
    slider_layout = new QHBoxLayout;
    slider_layout->addWidget(slider,8);
    totaltimeLabel = new QLabel("wakawaka");
    totaltimeLabel->setFixedSize(100, 30);//�̶���С����ֹ����
    totaltimeLabel->setText("0:00 / 0:00");
    totaltimeLabel->setAlignment(Qt::AlignCenter | Qt::AlignHCenter);
    totaltimeLabel->setWordWrap(true);//Label���ݻ���
    slider_layout->addWidget(totaltimeLabel,2);
   
    play_pause_slide = new QVBoxLayout;
    play_pause_slide->addLayout(play_pause,8);
    play_pause_slide->addLayout(slider_layout,2);
    playControl->addLayout(play_pause_slide);

    
}

void WaKAwaka::sliderMovedEvent()
{
    int position = slider->value();
    int min = position / 1004.95 / 60;//����
    int s = (int)(position / 1004.95) % 60;//����
    QString positionText = QString::number(min) + ":" + QString::number(s);//����label��ʾ����
    if (min == 0) {
        positionText = QString::number(s);
    }
    totaltimeLabel->setText(positionText + " / " + maxlenText); //������ʾ�ڱ�ǩ�ϡ�
}
void WaKAwaka::sliderPressedEvent()
{
    disconnect(player, &QMediaPlayer::positionChanged, this, &WaKAwaka::videoPositionChanged);
}
void WaKAwaka::sliderReleasedEvent()
{
    player->setPosition(slider->value());
    connect(player, &QMediaPlayer::positionChanged, this, &WaKAwaka::videoPositionChanged);
}

//���������ȸı��ź��Լ����źŵĴ�����
void WaKAwaka::videoPositionChanged(qint64 position) //�����������źŵĴ�����
{
    slider->setValue(position); //���������ȸı�ʱ�����Ļ������ϻ����λ����ʾ���ȡ�
    int min = position / 1004.95 / 60;//����
    int s = (int)(position / 1004.95 ) % 60;//����
    QString positionText = QString::number(min) + ":" + QString::number(s);//����label��ʾ����
    if (min == 0) {
        positionText = QString::number(s);
    }
    totaltimeLabel->setText(positionText +" / " + maxlenText); //������ʾ�ڱ�ǩ�ϡ�
}

//��ý���ļ�ʱ��player�������ᷢ��ý���ܳ��ȸı��źţ��ô��ź����û��������ֵ
void WaKAwaka::durationChanged(qint64 duration)
{
    slider->setMaximum(duration); //���û��������ֵ
    int min = duration / 1004.95 / 60;//����
    int s = duration % 60;//����
    maxlenText = QString::number(min) + ":" + QString::number(s);//durationlabel��ʾ����
}


//�����б�˫������
void WaKAwaka::listWidgetItemActivated(QListWidgetItem* activatedItem)
{
    player->stop();//��ʼ������״̬Ϊ��ͣ
    for (int i = 0; i < listWidget->count(); i++)//�����б�����������ñ���ɫ��ǰ��ɫ������ͼ��
    {
        listWidget->item(i)->setForeground(QColor(0, 0, 0));
        listWidget->item(i)->setBackground(QColor(99, 187, 207));
        listWidget->item(i)->setIcon(QPixmap(":/WaKAwaka/images/����01.png"));
    }
    activatedItem->setForeground(QColor(255, 0, 0));
    activatedItem->setBackground(QColor(0, 255, 0));
    activatedItem->setIcon(QPixmap(":/WaKAwaka/images/playing.png"));
    musicFullName = activatedItem->data(Qt::UserRole).toString(); //����û����ݣ�Ҳ������Ϊ�ļ�ȫ���������͵�����������
    player->setMedia(QUrl::fromLocalFile(musicFullName));//���ò�������ý���ļ�
    player->play();//��ʼ����
    flag = 0;
    playorpause->setEnabled(true);
    playmode->setEnabled(true);
    next->setEnabled(true);
    back->setEnabled(true);
    playNow = listWidget->currentRow();
    playorpause->setIcon(QIcon(":/WaKAwaka/images/media_pause_96p.bmp"));
    //��������ý��״̬�ı��ź��Լ����źŴ�����
    connect(player, &QMediaPlayer::mediaStatusChanged, this, &WaKAwaka::mediaStatusChanged);
    connect(player, &QMediaPlayer::durationChanged, this, &WaKAwaka::durationChanged);
    connect(player, &QMediaPlayer::positionChanged, this, &WaKAwaka::videoPositionChanged);  
}


