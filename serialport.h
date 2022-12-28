#ifndef SERIALPORT_H
#define SERIALPORT_H

#include <QObject>
#include <QThread>
#include <QMutex>
#include <QIODevice>
#include <QDebug>
#include <QtSerialPort/QSerialPortInfo>
#include <QSerialPort>
#include "appenum.h"

class SerialPort : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QStringList portList READ portList WRITE setPortList NOTIFY portListChanged)
    Q_PROPERTY(int baudRate READ baudRate WRITE setBaudRate NOTIFY baudRateChanged)
    Q_PROPERTY(QString portName READ portName WRITE setPortName NOTIFY portNameChanged)
    Q_PROPERTY(bool isPortOpened READ isPortOpened WRITE setIsPortOpened NOTIFY isPortOpenedChanged)
    Q_PROPERTY(QString message READ message WRITE setMessage NOTIFY messageChanged)
    Q_PROPERTY(QString dataResponse READ dataResponse WRITE setDataResponse NOTIFY dataResponseChanged)

public:
    explicit SerialPort(QObject *parent = nullptr);
    ~SerialPort();

    QStringList portList() const;
    void setPortList(const QStringList &newPortList);

    int baudRate() const;
    void setBaudRate(int newBaudRate);

    QString portName() const;
    void setPortName(const QString &newPortName);

    bool isPortOpened() const;
    void setIsPortOpened(bool newIsPortOpened);

    /* Make can be invoke side QML */
    Q_INVOKABLE void openSerialPort(const QString portName, const int portBaud);
    Q_INVOKABLE void closeSerialPort();
    Q_INVOKABLE void sendData(int cmd);
    Q_INVOKABLE void scanSerialPort();

    /* Loop infinity */
    void readData();

    QString message() const;
    void setMessage(const QString &newMessage);

    QString dataResponse() const;
    void setDataResponse(const QString &newDataResponse);

signals:

    void portListChanged();
    void baudRateChanged();
    void portNameChanged();
    void isPortOpenedChanged();

    void messageChanged();

    void dataResponseChanged();

private:
    QStringList m_portList;
    int m_baudRate;
    QString m_portName;
    bool m_isPortOpened;

    QSerialPort m_serialPort;
    QMutex m_mutex;
    QString m_message;
    QString m_dataResponse;
};

#endif // SERIALPORT_H
