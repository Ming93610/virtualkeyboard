#include "CReadWriteColor.h"
#include <QDebug>
#include <QFile>
#include <QCoreApplication>

CReadWriteColor* CReadWriteColor::m_spInstance = NULL;

CReadWriteColor::CReadWriteColor(QObject *parent) : QObject(parent)
{
    m_strFilePath = QCoreApplication::applicationDirPath() + QLatin1String("/keyboardcolor.txt");
    m_strBoardBackgroundColor = QLatin1String("#D2ECF5FC");
    m_strKeyBackgroundColor = QLatin1String("#FFFFFF");
    m_strKeyTextColor = QLatin1String("#000000");

    readColorFile();

    qDebug()<<"键盘配色:"<<m_strFilePath<<m_strBoardBackgroundColor<<m_strKeyBackgroundColor<<m_strKeyTextColor;
}

CReadWriteColor* CReadWriteColor::GetInstance()
{
    if(NULL == m_spInstance)
        m_spInstance = new CReadWriteColor;
    return m_spInstance;
}

bool CReadWriteColor::readColorFile()
{
    QFile file(m_strFilePath);
    if(!file.open(QIODevice::ReadWrite))
        return false;

    QByteArray byteData = file.readAll();
    file.close();

    QString strData = QString::fromLocal8Bit(byteData);
    QString strSp = QLatin1String(";");
    QStringList strList =  strData.split(strSp);

    if(strList.size() >= 3)
    {
        m_strBoardBackgroundColor = strList.at(0);
        m_strKeyBackgroundColor = strList.at(1);
        m_strKeyTextColor = strList.at(2);
        m_strKeyTextColor.remove(QLatin1String("\r")).remove(QLatin1String("\n"));
    }
    else
    {
        return false;
    }

    return true;
}

void CReadWriteColor::_WriteColorFile()
{
//    QString strData = m_strBoardBackgroundColor + QLatin1String(";")
//            + m_strKeyBackgroundColor + QLatin1String(";")
//            + m_strKeyTextColor;
//    QFile file(m_strFilePath);
//    if(!file.open(QIODevice::ReadWrite))
//        return;
//    file.write(strData.toLocal8Bit());
//    file.close();
//    system("sync");
}

QVariant CReadWriteColor::getBoardBackgroundColor()
{
    return m_strBoardBackgroundColor;
}

QVariant CReadWriteColor::getKeyBackgroundColor()
{
    return m_strKeyBackgroundColor;
}

QVariant CReadWriteColor::getKeyTextColor()
{
    return m_strKeyTextColor;
}

void CReadWriteColor::setBoardBackgroundColor(QString strColor)
{
    m_strBoardBackgroundColor = strColor;
    _WriteColorFile();
}

void CReadWriteColor::setKeyBackgroundColor(QString strColor)
{
    m_strKeyBackgroundColor = strColor;
    _WriteColorFile();
}

void CReadWriteColor::setKeyTextColor(QString strColor)
{
    m_strKeyTextColor = strColor;
    _WriteColorFile();
}
