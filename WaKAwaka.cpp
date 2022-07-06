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
            QListWidgetItem* item = new QListWidgetItem; //定义列表项
            item->setIcon(QPixmap(":/WaKAwaka/images/音符01.png")); //设置列表项图标
            item->setText(fileName);//设置显示文本，比如显示歌名
            item->setData(Qt::UserRole, filenames.at(i));
            listWidget->addItem(item);//添加列表项到列表框
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
   
    //歌曲目录
    listLayout = new QHBoxLayout;
    //播放控制;
    playControl = new QHBoxLayout();
    //主层
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
    for (int i = 0; i < listWidget->count(); i++)//遍历列表框的所有项，设置背景色和前景色，更改图标
    {
        listWidget->item(i)->setForeground(QColor(0, 0, 0));
        listWidget->item(i)->setBackground(QColor(99, 187, 207));
        listWidget->item(i)->setIcon(QPixmap(":/WaKAwaka/images/音符01.png"));
    }
    listWidget->item(playNow)->setForeground(QColor(255, 0, 0));
    listWidget->item(playNow)->setBackground(QColor(0, 255, 0));
    listWidget->item(playNow)->setIcon(QPixmap(":/WaKAwaka/images/playing.png"));
    //下面是列表显示的同步设置
    QString musicFullName = listWidget->item(playNow)->data(Qt::UserRole).toString();
    QFileInfo fileInfo(musicFullName); //创建文件信息类对象fileInfo
    QString fileName = fileInfo.fileName(); //从fileInfo中获得文件名（无路径）
    //开始按钮同步
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
    //下一曲1.末尾，转回第一曲2.不是末尾，加加
    if (playNow == listWidget->count() - 1) {
        playNow = 0;
    }
    else {
        playNow++;
    }
    QString musicFullName = listWidget->item(playNow)->data(Qt::UserRole).toString(); //获得用户数据，也就是因为文件全名，可以送到播放器播放
    player->setMedia(QUrl::fromLocalFile(musicFullName));//设置播放器的媒体文件
    player->play();//开始播放
    //列表显示同步
    changeList();
}

void WaKAwaka::playBack()
{
    //上一曲，首位置，转回最后，其他的减减
    if (playNow == 0) {
        playNow = listWidget->count() - 1;
    }
    else {
        playNow--;
    }
    QString musicFullName = listWidget->item(playNow)->data(Qt::UserRole).toString(); //获得用户数据，也就是因为文件全名，可以送到播放器播放
    player->setMedia(QUrl::fromLocalFile(musicFullName));//设置播放器的媒体文件
    player->play();//开始播放
    //列表显示同步
    changeList();//调用changeList函数
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

//利用自带的函数来做1.顺序直接用nextMusic，2.循环不改变playNow3.随机，palyNow取1-list.count的随机数
void WaKAwaka::mediaStatusChanged(QMediaPlayer::MediaStatus status)
{
    if (status == QMediaPlayer::InvalidMedia)   //无法播放媒体文件，输出错误信息
    {
        inputInformation();
    }
    else if (status == QMediaPlayer::EndOfMedia) //当前文件播放结束，播放下一首？
    {
        if (mode == 1) {
            playNext();
        }
        else if (mode == 2) {
            QString musicFullName = listWidget->item(playNow)->data(Qt::UserRole).toString(); //获得用户数据，也就是因为文件全名，可以送到播放器播放
            player->setMedia(QUrl::fromLocalFile(musicFullName));//设置播放器的媒体文件
            player->play();//开始播放
            //列表显示同步
            changeList();//调用changeList函数
        }
        else {
            playNow = generateRandomNumber();
            QString musicFullName = listWidget->item(playNow)->data(Qt::UserRole).toString(); //获得用户数据，也就是因为文件全名，可以送到播放器播放
            player->setMedia(QUrl::fromLocalFile(musicFullName));//设置播放器的媒体文件
            player->play();//开始播放
            //列表显示同步
            changeList();//调用changeList函数
        }
    }
}
void WaKAwaka::inputInformation()
{
    qDebug() << "文件无法播放" << endl;
}
//随机数产生
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
    slider->setRange(1, 100); //设定数据范围
    slider->setSingleStep(5); //设定单次步长
    slider->setPageStep(5); //设定PageUp和PageDown步长
    slider->setFixedWidth(600); //设定控件固定宽度
    slider->setOrientation(Qt::Horizontal); //设定控件显示方位
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
    totaltimeLabel->setFixedSize(100, 30);//固定大小，防止乱跑
    totaltimeLabel->setText("0:00 / 0:00");
    totaltimeLabel->setAlignment(Qt::AlignCenter | Qt::AlignHCenter);
    totaltimeLabel->setWordWrap(true);//Label内容换行
    slider_layout->addWidget(totaltimeLabel,2);
   
    play_pause_slide = new QVBoxLayout;
    play_pause_slide->addLayout(play_pause,8);
    play_pause_slide->addLayout(slider_layout,2);
    playControl->addLayout(play_pause_slide);

    
}

void WaKAwaka::sliderMovedEvent()
{
    int position = slider->value();
    int min = position / 1004.95 / 60;//分钟
    int s = (int)(position / 1004.95) % 60;//秒数
    QString positionText = QString::number(min) + ":" + QString::number(s);//进度label显示内容
    if (min == 0) {
        positionText = QString::number(s);
    }
    totaltimeLabel->setText(positionText + " / " + maxlenText); //进度显示在标签上。
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

//播放器进度改变信号以及该信号的处理函数
void WaKAwaka::videoPositionChanged(qint64 position) //播放器进度信号的处理函数
{
    slider->setValue(position); //播放器进度改变时，更改滑动条上滑块的位置显示进度。
    int min = position / 1004.95 / 60;//分钟
    int s = (int)(position / 1004.95 ) % 60;//秒数
    QString positionText = QString::number(min) + ":" + QString::number(s);//进度label显示内容
    if (min == 0) {
        positionText = QString::number(s);
    }
    totaltimeLabel->setText(positionText +" / " + maxlenText); //进度显示在标签上。
}

//打开媒体文件时，player播放器会发出媒体总长度改变信号，用此信号设置滑动条最大值
void WaKAwaka::durationChanged(qint64 duration)
{
    slider->setMaximum(duration); //设置滑动条最大值
    int min = duration / 1004.95 / 60;//分钟
    int s = duration % 60;//秒数
    maxlenText = QString::number(min) + ":" + QString::number(s);//durationlabel显示内容
}


//歌曲列表双击操作
void WaKAwaka::listWidgetItemActivated(QListWidgetItem* activatedItem)
{
    player->stop();//初始化播放状态为暂停
    for (int i = 0; i < listWidget->count(); i++)//遍历列表框的所有项，设置背景色和前景色，更改图标
    {
        listWidget->item(i)->setForeground(QColor(0, 0, 0));
        listWidget->item(i)->setBackground(QColor(99, 187, 207));
        listWidget->item(i)->setIcon(QPixmap(":/WaKAwaka/images/音符01.png"));
    }
    activatedItem->setForeground(QColor(255, 0, 0));
    activatedItem->setBackground(QColor(0, 255, 0));
    activatedItem->setIcon(QPixmap(":/WaKAwaka/images/playing.png"));
    musicFullName = activatedItem->data(Qt::UserRole).toString(); //获得用户数据，也就是因为文件全名，可以送到播放器播放
    player->setMedia(QUrl::fromLocalFile(musicFullName));//设置播放器的媒体文件
    player->play();//开始播放
    flag = 0;
    playorpause->setEnabled(true);
    playmode->setEnabled(true);
    next->setEnabled(true);
    back->setEnabled(true);
    playNow = listWidget->currentRow();
    playorpause->setIcon(QIcon(":/WaKAwaka/images/media_pause_96p.bmp"));
    //播放器的媒体状态改变信号以及该信号处理函数
    connect(player, &QMediaPlayer::mediaStatusChanged, this, &WaKAwaka::mediaStatusChanged);
    connect(player, &QMediaPlayer::durationChanged, this, &WaKAwaka::durationChanged);
    connect(player, &QMediaPlayer::positionChanged, this, &WaKAwaka::videoPositionChanged);  
}


