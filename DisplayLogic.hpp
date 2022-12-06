#ifndef _DISPLAY_LOGIC_H
#define _DISPLAY_LOGIC_H

#include <QObject>
#include <QString>
#include <QTimer>
#include <QJsonDocument>
#include "ProviderAPI.h"

class DisplayLogic : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString jsonStringRaw READ jsonStringRaw WRITE SetJsonStringRaw NOTIFY jsonStringRawChanged)
    Q_PROPERTY(QString someVar READ someVar WRITE setSomeVar NOTIFY someVarChanged)
    Q_PROPERTY(QString buttonText READ buttonText WRITE setButtonText NOTIFY buttonTextChanged)
public:
    explicit DisplayLogic(QObject *parent = nullptr);

    Q_INVOKABLE void getEntity(const QString& index);
    QString someVar();
    Q_INVOKABLE QString getSomeVar();
    Q_INVOKABLE void setSomeVar(const QString &someVar);
    QString buttonText();
    Q_INVOKABLE QString getButtonText();
    Q_INVOKABLE void setButtonText(const QString &buttonText);
    const QString &jsonStringRaw() const;
    void SetJsonStringRaw(const QString &newJsonStringRaw);

signals:
    void someVarChanged(const QString &someVar);
    void buttonTextChanged(const QString &buttonText);
    void jsonStringRawChanged();

public slots:

protected:

private:
    void changeFirstName(QString name);
    QJsonDocument doc;

    QString m_someVar;
    QString m_buttonText;
    QString m_jsonStringRaw;
    std::shared_ptr<Provider> mClient;
};
#endif
