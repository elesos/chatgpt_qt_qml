//
// Created by 17305 on 2023/5/11.
//

#include "PostData.h"
#include <QJsonArray>
#include <QFile>
#include "QJsonDocument"
PostData::PostData() {
    initPostDatas();
}

PostData::~PostData() {

}

void PostData::initPostDatas() {

    QJsonObject _parameters;
    _parameters.insert("role","system");
    _parameters.insert("content",QString("用中文回答问题"));
    m_jsonArray.append(_parameters);
    m_postDatas["model"] = "gpt-3.5-turbo";
    m_postDatas["max_tokens"] = 1024;
    m_postDatas["temperature"] = 1;
    m_postDatas.insert("messages",m_jsonArray);
}

void PostData::addSinglePostData(const QString& role, QString& msg)
{
    QJsonObject parameters;
    parameters.insert("role",role);
    parameters.insert("content",msg);
    m_jsonArray.append(parameters);
    if(m_postDatas.contains("messages"))
    {
        m_postDatas.remove("messages");
    }
    m_postDatas.insert("messages",m_jsonArray);

    //todo test
    saveToLocalJson();
}

const QJsonObject &PostData::getPostDatas() {
    return m_postDatas;
}

void PostData::saveToLocalJson() {
    QFile file("E:/chatGpt_session.json");
    if (!file.open(QIODevice::WriteOnly)) {
        qDebug() << "File open error";
    }
    else {
        qDebug() << "File open!";
    }
    QJsonDocument jsonDoc;
    jsonDoc.setObject(m_postDatas);
    // 将json以文本形式写入文件并关闭文件。
    file.write(jsonDoc.toJson());
    file.close();
}
