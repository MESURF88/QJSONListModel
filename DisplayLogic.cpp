﻿#include "DisplayLogic.hpp"
#include <QDebug>
#include <QJsonArray>
#include <QJsonObject>
#include <QFile>
#include "ProviderAPI.h"



static QHash<QString, int> entitymap {
        {"entitya", 1},
        {"entityb", 2}
};

DisplayLogic::DisplayLogic(QObject *parent) : QObject(parent)
{
    QFile file("../JSONViews/tmp.txt");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)){
        qDebug() << "Could not open file!";
    }
    const auto& data = QString(file.readAll());
    doc = QJsonDocument::fromJson(data.toUtf8());
    QString tmpText = doc.toJson(QJsonDocument::Compact).toStdString().c_str();
    SetJsonStringRaw(tmpText);

    m_timer = new QTimer(this);
}

void DisplayLogic::getEntity(const QString& index)
{
    if ((index != "") && (entitymap.contains(index)))
    {
        SetJsonStringRaw(QString::fromUtf8(Provider::GET(index.toUtf8())));
    }
    else
    {
        qDebug() << "Uknown GET";
    }

}

void DisplayLogic::changeFirstName(QString name)
{
    QJsonObject obj = doc.object();
    QJsonObject root = doc.object();
    QJsonObject books = root["store"].toObject();
    QJsonArray entries = books["book"].toArray();
    QJsonObject objBook1 = entries[0].toObject();
    objBook1["title"] = name;
    entries[0] = objBook1;
    books["book"] = entries;
    root["store"] = books;
    doc.setObject(root);
}

QString DisplayLogic::someVar()
{
    return m_someVar;
}

QString DisplayLogic::getSomeVar()
{
    return m_someVar;
}

void DisplayLogic::setSomeVar(const QString &someVar)
{
    if (someVar == m_someVar)
        return;
    m_someVar = someVar;
    emit someVarChanged(m_someVar);
}

QString DisplayLogic::buttonText()
{
    return m_buttonText;
}

QString DisplayLogic::getButtonText()
{
    return m_buttonText;
}

void DisplayLogic::setButtonText(const QString &buttonText)
{
    if (buttonText == m_buttonText)
        return;
    m_buttonText = buttonText;
    emit buttonTextChanged(m_buttonText);
}

const QString &DisplayLogic::jsonStringRaw() const
{
    return m_jsonStringRaw;
}

void DisplayLogic::SetJsonStringRaw(const QString &newJsonStringRaw)
{
#ifdef QT_DEBUG
      qDebug() << newJsonStringRaw << "/n";
#endif
    if (m_jsonStringRaw == newJsonStringRaw)
        return;
    m_jsonStringRaw = newJsonStringRaw;
    emit jsonStringRawChanged();
}
