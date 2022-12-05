#include "DisplayLogic.hpp"
#include <QDebug>
#include <QJsonArray>
#include <QJsonObject>
#include <QFile>
#include "ProviderAPI.h"


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
    const char* tmp = Provider::hello();
    qDebug()<< QString::fromUtf8(tmp);
}

void DisplayLogic::startGame()
{
    qDebug("started");
    connect(m_timer, SIGNAL(timeout()), this, SLOT(processTheMove()));
    m_timer->start(500);
}

void DisplayLogic::processTheMove()
{
    static int p1_turn = 1;
        if (p1_turn)
        {
            changeFirstName("Wuthering Heights");

            QString tmpText = doc.toJson(QJsonDocument::Compact).toStdString().c_str();
            SetJsonStringRaw(tmpText);
            p1_turn = 0;
        }
        else
        {
            changeFirstName("Beowulf");

            QString tmpText = doc.toJson(QJsonDocument::Compact).toStdString().c_str();
            SetJsonStringRaw(tmpText);
            p1_turn = 1;
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
    if (m_jsonStringRaw == newJsonStringRaw)
        return;
    m_jsonStringRaw = newJsonStringRaw;
    emit jsonStringRawChanged();
}
