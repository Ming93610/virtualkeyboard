#ifndef CREADWRITECOLOR_H
#define CREADWRITECOLOR_H

#include <QObject>
#include <QVariant>
#include <QQmlEngine>

class CReadWriteColor : public QObject
{
    Q_OBJECT
public:
    explicit CReadWriteColor(QObject *parent = nullptr);

    static QObject* qmlSingletonInstance(QQmlEngine* engine,QJSEngine* scriptEngine )
     {
         Q_UNUSED(engine)
         Q_UNUSED(scriptEngine)
         return GetInstance();
     }

    static CReadWriteColor* GetInstance();

    Q_INVOKABLE bool readColorFile();
    Q_INVOKABLE QVariant getBoardBackgroundColor();
    Q_INVOKABLE QVariant getKeyBackgroundColor();
    Q_INVOKABLE QVariant getKeyTextColor();

    Q_INVOKABLE void setBoardBackgroundColor(QString strColor);
    Q_INVOKABLE void setKeyBackgroundColor(QString strColor);
    Q_INVOKABLE void setKeyTextColor(QString strColor);

private:
    static CReadWriteColor* m_spInstance;

    QString m_strFilePath;
    QString m_strBoardBackgroundColor;
    QString m_strKeyBackgroundColor;
    QString m_strKeyTextColor;

private:
    void _WriteColorFile();
};

#endif // CREADWRITECOLOR_H
