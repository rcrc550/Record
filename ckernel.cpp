#include "ckernel.h"
#include"qDebug"
#include"md5.h"
#include<QMessageBox>

#define NetPackMap(a) m_netPackMap[ a - DEF_PACK_BASE ]
//设置协议映射关系
void Ckernel::setNetPackMap()
{
    memset(m_netPackMap,0 , sizeof(m_netPackMap));

    //m_netPackMap[ DEF_PACK_LOGIN_RS - DEF_PACK_BASE ] = &Ckernel::slot_dealLoginRs;
    NetPackMap(DEF_PACK_LOGIN_RS)       = &Ckernel::slot_dealLoginRs;
    NetPackMap(DEF_PACK_REGISTER_RS)    = &Ckernel::slot_dealRegisterRs;

}


Ckernel::Ckernel(QObject *parent) : QObject(parent)
  ,m_id(0),m_roomid(0)
{
    setNetPackMap();

//    m_pWeChatDlg->show();
     record=new RecordDialog;
    m_pLoginDlg = new LoginDialog;
    connect( m_pLoginDlg , SIGNAL(SIG_loginCommit(QString,QString))
             , this , SLOT( slot_loginCommit(QString,QString)));
    connect( m_pLoginDlg , SIGNAL( SIG_close())
             , this , SLOT(slot_destroy()) );
    connect( m_pLoginDlg , SIGNAL(SIG_registerCommit(QString,QString,QString))
             , this , SLOT( slot_registerCommit(QString,QString,QString)));
    m_pLoginDlg->show();

    //添加网络
    m_pClient = new TcpClientMediator;

    m_pClient->OpenNet( _DEF_SERVERIP , _DEF_PORT );
    connect( m_pClient , SIGNAL( SIG_ReadyData(uint,char*,int))
             , this , SLOT( slot_dealData(uint,char*,int) ) );
}



//回收
void Ckernel::slot_destroy()
{
    qDebug() << __func__;

    if(m_pLoginDlg)
    {
        m_pLoginDlg->hide();
        delete m_pLoginDlg; m_pLoginDlg = NULL;
    }
    if( m_pClient )
    {
        m_pClient->CloseNet();
        delete m_pClient; m_pClient = NULL;
    }
    exit(0);
}
#define MD5_KEY (1234)
static std::string GetMD5(QString value )
{
    QString str = QString("%1_%2").arg(value).arg(MD5_KEY);
    std::string strSrc = str.toStdString();
    MD5 md5( strSrc );
    return md5.toString();
}

//提交登录信息
void Ckernel::slot_loginCommit(QString tel, QString pass)
{
    std::string strTel = tel.toStdString();
    //std::string strPass = pass.toStdString();

    STRU_LOGIN_RQ rq;
    strcpy( rq.m_tel, strTel.c_str() );

    std::string strPassMD5 = GetMD5( pass );
    qDebug()<< strPassMD5.c_str();


    strcpy( rq.m_password , strPassMD5.c_str() );



    m_pClient->SendData( 0 , (char*)&rq , sizeof(rq) );
}

//发送注册信息
void Ckernel::slot_registerCommit(QString tel, QString pass, QString name)
{
    std::string strTel = tel.toStdString();
    //std::string strPass = pass.toStdString();
    //中文
    std::string strName = name.toStdString(); // 格式 utf8

    STRU_REGISTER_RQ rq;
    strcpy( rq.m_tel, strTel.c_str() );

    std::string strPassMD5 = GetMD5( pass );
    qDebug()<< strPassMD5.c_str();

    //兼容中文 utf8 QString->std::string  --> char*
    strcpy( rq.m_name , strName.c_str() );

    //1_1234 -> ea135e06cd37ab7e304e1dc440c93ea2
    //          ea135e06cd37ab7e304e1dc440c93ea2

    strcpy( rq.m_password , strPassMD5.c_str() );

    // 1 ->c4ca4238a0b923820dcc509a6f75849b
    //     c4ca4238a0b923820dcc509a6f75849b

    m_pClient->SendData( 0 , (char*)&rq , sizeof(rq) );
}

//创建房间


#include<QInputDialog>
#include"QRegExp"
//加入房间



//网络处理
void Ckernel::slot_dealData(uint sock, char *buf, int nlen)
{
    int type = *(int*)buf;
    if( type >= DEF_PACK_BASE && type < DEF_PACK_BASE + DEF_PACK_COUNT )
    {
        //取得协议头 , 根据协议映射关系, 找到函数指针
        PFUN pf = NetPackMap( type );
        if( pf )
        {
            (this->*pf)( sock , buf , nlen );
        }
    }
    delete[] buf;
}

//登录回复处理
void Ckernel::slot_dealLoginRs(uint sock, char *buf, int nlen)
{
    qDebug()<< __func__;
    //拆包
    STRU_LOGIN_RS* rs = (STRU_LOGIN_RS*)buf;
    //根据返回结果, 得到不同信息
    switch( rs->m_lResult )
    {
    case user_not_exist:
        QMessageBox::about( m_pLoginDlg , "提示", "用户不存在, 登录失败" );
        break;
    case password_error:
        QMessageBox::about( m_pLoginDlg , "提示", "密码错误, 登录失败" );
        break;
    case login_success:
        {
            //QString strName =QString("用户[%1]登录成功").arg( rs->m_name );
            //QMessageBox::about( m_pLoginDlg , "提示", strName );
            //id 记录
            m_name = QString::fromStdString( rs->m_name );

            m_id = rs->m_userid;
            //ui跳转
            m_pLoginDlg->hide();
            record->showNormal();
        }
        break;
    }
}

//注册回复处理
void Ckernel::slot_dealRegisterRs(uint sock, char *buf, int nlen)
{
    //拆包
    STRU_REGISTER_RS * rs = (STRU_REGISTER_RS *)buf;
    //根据不同的结果 弹出不同的提示窗
    switch( rs->m_lResult )
    {
    case tel_is_exist:
        QMessageBox::about( m_pLoginDlg , "提示", "手机号已存在, 注册失败" );
        break;
    case register_success:
        QMessageBox::about( m_pLoginDlg , "提示", "注册成功" );
        break;
    case name_is_exist:
        QMessageBox::about( m_pLoginDlg , "提示", "昵称已存在, 注册失败" );
        break;
    default:break;
    }
}
