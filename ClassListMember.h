#ifndef CLASSLISTMEMBER_H
#define CLASSLISTMEMBER_H

#include <QObject>
#include <QQmlListProperty>

class ClassListMember : public QObject
{

    Q_OBJECT
    Q_PROPERTY(quint32 id MEMBER m_id NOTIFY idChanged)
    Q_PROPERTY(QString name MEMBER m_name NOTIFY nameChanged)
    Q_PROPERTY(QString className MEMBER m_className NOTIFY classNameChanged)
    Q_PROPERTY(bool generateProperty MEMBER m_generateProperty NOTIFY generatePropertyChanged)
    Q_PROPERTY(bool generateMember MEMBER m_generateMember NOTIFY generateMemberChanged)
    Q_PROPERTY(bool generateAdd MEMBER m_generateAdd NOTIFY generateAddChanged)
    Q_PROPERTY(bool generateGet MEMBER m_generateGet NOTIFY generateGetChanged)
    Q_PROPERTY(bool generateRemove MEMBER m_generateRemove NOTIFY generateRemoveChanged)
    Q_PROPERTY(bool generateQList MEMBER m_generateQList NOTIFY generateQListChanged)
public:
    explicit ClassListMember(QObject *parent = 0, quint32 id = 0, QString name = "", QString className = "", bool generateProperty = false, bool generateMember = false, bool generateAdd = false, bool generateGet = false, bool generateRemove = false, bool generateQList = false);

    QString type();
    QString memberName();
    QString capitalName();

    QString getMemberDeclaration();
    QString getPropertyDeclaration();
    QString getNotifyDeclaration();

    QString getAccessorsDeclaration();
    QString getAccessorsSource();

signals:
    void idChanged(quint32);
    void nameChanged(QString);
    void classNameChanged(QString);
    void generatePropertyChanged(bool);
    void generateMemberChanged(bool);
    void generateAddChanged(bool);
    void generateGetChanged(bool);
    void generateRemoveChanged(bool);
    void generateQListChanged(bool);

public slots:

private:
    quint32 m_id;
    QString m_name;
    QString m_className;
    bool m_generateProperty;
    bool m_generateMember;
    bool m_generateAdd;
    bool m_generateGet;
    bool m_generateRemove;
    bool m_generateQList;

};

#endif // CLASSLISTMEMBER_H
