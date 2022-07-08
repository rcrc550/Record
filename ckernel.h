#ifndef CKERNEL_H
#define CKERNEL_H

#include <QObject>

#include "netapi/mediator/TcpClientMediator.h"
#include "netapi/net/packdef.h"
#include "logindialog.h"
#include"recorddialog.h"

//协议映射表使用的类型
class Ckernel;
typedef void (Ckernel::*PFUN)(uint sock ,char* buf,int nlen );

class Ckernel : public QObject
{
    Q_OBJECT
public:
    explicit Ckernel(QObject *parent = 0);

    //单例
    static Ckernel* GetInstance()
    {
        static Ckernel kernel;
        return &kernel;
    }

signals:

public slots:
    void setNetPackMap();

    void slot_destroy();
    //发送登录信息
    void slot_loginCommit(QString tel ,QString pass);
    //发送注册信息
    void slot_registerCommit(QString tel,QString pass,QString name);


    ///网络信息处理
    ///
    void slot_dealData(uint sock ,char* buf,int nlen );
    //登录回复
    void slot_dealLoginRs(uint sock ,char* buf,int nlen );
    //注册回复
    void slot_dealRegisterRs(uint sock ,char* buf,int nlen );


private:

    LoginDialog * m_pLoginDlg;
    INetMediator * m_pClient;
    RecordDialog *record;
    //协议映射表
    PFUN m_netPackMap[ DEF_PACK_COUNT ];

    int m_id;
    int m_roomid;
    QString m_name;
};

#endif // CKERNEL_H
