#pragma once
#ifndef QDLGLOGIN_H
#define QDLGLOGIN_H
#pragma execution_character_set("utf-8")
#include <QDialog>
#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include "QTextToSpeech"
namespace Ui {
    class dlgLogin;
}

class QDlgLogin : public QDialog
{
    Q_OBJECT

private:
    bool    m_moving = false;//��ʾ�����Ƿ������������ƶ�
    QPoint  m_lastPos;  //��һ�ε����λ��

    QString m_user = "user"; //��ʼ���û���
    QString m_pswd = "12345";//��ʼ�����룬δ���ܵ�

    int m_tryCount = 0; //�Դ����

    void    readSettings(); //��ȡ����,��ע���
    void    writeSettings();//д�����ã���ע���

    QString encrypt(const QString& str);//�ַ�������
    QTextToSpeech* m_speech;
protected:
    //��������϶����ڵ�����¼�����
    void mousePressEvent(QMouseEvent* event);
    void mouseMoveEvent(QMouseEvent* event);
    void mouseReleaseEvent(QMouseEvent* event);

public:
    explicit QDlgLogin(QWidget* parent = 0);
    ~QDlgLogin();

private slots:
    void on_btnOK_clicked(); //OK����

private:
    Ui::dlgLogin* ui;
};

#endif // DLGLOGIN_H
