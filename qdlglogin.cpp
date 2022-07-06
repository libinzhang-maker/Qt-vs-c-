#include "qdlglogin.h"
#include "ui_qdlglogin.h"

#include    <QMouseEvent>
#include    <QSettings>
//#include    "qwmisc.h"
#include    <QMessageBox>
#include    <QByteArray>
#include    <QCryptographicHash>
#include <QSound>


void QDlgLogin::readSettings()
{//��ȡ�洢���û���������, �����Ǿ������ܵ�
    QString organization = "WWB-Qt";//����ע���
    QString appName = "samp6_5"; //HKEY_CURRENT_USER/Software/WWB-Qt/amp6_5

    QSettings   settings(organization, appName);//����

    bool saved = settings.value("saved", false).toBool();//��ȡ saved����ֵ
    m_user = settings.value("Username", "user").toString();//��ȡ Username ����ֵ��ȱʡΪ��user��

    QString defaultPSWD = encrypt("12345"); //ȱʡ����"12345"���ܺ������

    m_pswd = settings.value("PSWD", defaultPSWD).toString();//��ȡPSWD ����ֵ��

    if (saved)
        ui->editUser->setText(m_user);

    ui->chkBoxSave->setChecked(saved);
}

void QDlgLogin::writeSettings()
{ //�����û��������������
    QSettings   settings("WWB-Qt", "samp6_5"); //ע������
    settings.setValue("Username", m_user); //�û���
    settings.setValue("PSWD", m_pswd);   //���룬�������ܵ�
    settings.setValue("saved", ui->chkBoxSave->isChecked());
}

QString QDlgLogin::encrypt(const QString& str)
{ //�ַ���MD5�㷨����
    QByteArray btArray;

    btArray.append(str);//����ԭʼ�ַ���

    QCryptographicHash hash(QCryptographicHash::Md5);  //Md5�����㷨

    hash.addData(btArray);  //������ݵ����ܹ�ϣֵ

    QByteArray resultArray = hash.result();  //�������յĹ�ϣֵ

    QString md5 = resultArray.toHex();//ת��Ϊ16�����ַ���

    return  md5;
}

void QDlgLogin::mousePressEvent(QMouseEvent* event)
{ //��갴��������
    if (event->button() == Qt::LeftButton)
    {
        m_moving = true;
        //��¼���������ڴ��ڵ�λ��
        //event->globalPos()��갴��ʱ����������������Ļλ��
        //pos() this->pos()��갴��ʱ�����������������Ļλ��
        m_lastPos = event->globalPos() - pos();
    }
    return QDialog::mousePressEvent(event);  //
}

void QDlgLogin::mouseMoveEvent(QMouseEvent* event)
{//��갴������ƶ�
    //(event->buttons() && Qt::LeftButton)���������
    //����ƶ��¼���Ҫ�ƶ����ڣ������ƶ��������أ�����Ҫ��ȡ����ƶ��У�������������Ļ�����꣬Ȼ��move��������꣬��ô��ȡ���ꣿ
    //ͨ���¼�event->globalPos()֪��������꣬��������ȥ�������ڴ���λ�ã����Ǵ�����������Ļ������
    if (m_moving && (event->buttons() && Qt::LeftButton)
        && (event->globalPos() - m_lastPos).manhattanLength() > QApplication::startDragDistance())
    {
        move(event->globalPos() - m_lastPos);
        m_lastPos = event->globalPos() - pos();
    }
    return QDialog::mouseMoveEvent(event);
}

void QDlgLogin::mouseReleaseEvent(QMouseEvent* event)
{//��갴���ͷ�
    Q_UNUSED(event);
    m_moving = false; //ֹͣ�ƶ�
}

QDlgLogin::QDlgLogin(QWidget* parent) :
    QDialog(parent),
    ui(new Ui::dlgLogin)
{
    ui->setupUi(this);

    ui->editPSWD->setEchoMode(QLineEdit::Password); //��������༭������Ϊ��������ģʽ
    this->setAttribute(Qt::WA_DeleteOnClose);//����Ϊ�ر�ʱɾ��
    this->setWindowFlags(Qt::SplashScreen); //����ΪSplashScreen, �����ޱ߿�,������������ʾ
//    this->setWindowFlags(Qt::FramelessWindowHint);//�ޱ߿򣬵�����������ʾ�Ի������

    readSettings(); //��ȡ�洢���û���������
}

QDlgLogin::~QDlgLogin()
{
    //    QMessageBox::information(this, "��ʾ", "��¼���ڱ�ɾ��");
    delete ui;
}

void QDlgLogin::on_btnOK_clicked()
{//"ȷ��"��ť��Ӧ
    QString user = ui->editUser->text().trimmed();//�����û���
    QString pswd = ui->editPSWD->text().trimmed(); //��������

    QString encrptPSWD = encrypt(pswd); //������������м���

    if ((user == m_user) && (encrptPSWD == m_pswd)) //����û�����������ȷ
    {
        writeSettings();//��������
        m_speech = new QTextToSpeech;
        //m_speech->say("welcom!!!"); //�첽�ʶ�����
        //�ļ���·����������Դ�ļ�·��Ҳ�����Ǳ����ļ�ϵͳ·��
        QSound::play(":/sounds/musics/�񶾵Ŀ�ͨ������µ�Ц��_������_[����ID��11954].wav");
        this->accept(); //�Ի��� accept()���رնԻ���
    }
    else
    {
        m_tryCount++; //�������
        if (m_tryCount > 3)
        {
            QMessageBox::critical(this, "����", "����������̫�࣬ǿ���˳�");
            this->reject(); //�˳�
        }
        else
            QMessageBox::warning(this, "������ʾ", "�û������������");
    }
}
