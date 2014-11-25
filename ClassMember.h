#ifndef CLASSMEMBER_H
#define CLASSMEMBER_H

#include <QObject>

class ClassMember : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString name MEMBER m_name READ name NOTIFY nameChanged)
    Q_PROPERTY(QString type MEMBER m_type READ type NOTIFY typeChanged)
    Q_PROPERTY(bool generateMember MEMBER m_generateMember NOTIFY generateMemberChanged)
    Q_PROPERTY(bool generateProperty MEMBER m_generateProperty NOTIFY generatePropertyChanged)
    Q_PROPERTY(bool generateRead MEMBER m_generateRead NOTIFY generateReadChanged)
    Q_PROPERTY(bool generateWrite MEMBER m_generateWrite NOTIFY generateWriteChanged)
public:
    explicit ClassMember(QObject *parent = 0, QString name = "", QString type = "", bool generateMember = false, bool generateProperty = false, bool generateRead = false, bool generateWrite = false);

    QString name();
    QString type();
    QString memberName();
    QString capitalName();

    QString getMemberDeclaration();
    QString getPropertyDeclaration();
    QString getNotifyDeclaration();
    QString getReadMethodDeclaration();
    QString getWriteMethodDeclaration();

    QString getReadMethod(QString className);
    QString getWriteMethod(QString className, QString logPropertyName);

signals:
    void nameChanged(QString);
    void typeChanged(QString);
    void generateMemberChanged(bool);
    void generatePropertyChanged(bool);
    void generateReadChanged(bool);
    void generateWriteChanged(bool);

public slots:

private:
    QString m_name;
    QString m_type;
    bool m_generateMember;
    bool m_generateProperty;
    bool m_generateRead;
    bool m_generateWrite;

};

#endif // CLASSMEMBER_H
