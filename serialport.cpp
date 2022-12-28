#include "serialport.h"

#define DEFAUl_BAUD 115200
#define START_BYTE 0x0A
#define STOP_BYTE 0x0B
/*
 * Contructor
*/
SerialPort::SerialPort(QObject *parent)
    : QObject{parent}
{
    m_baudRate = DEFAUl_BAUD;
    m_isPortOpened = false;
    scanSerialPort();
    connect(&m_serialPort, &QSerialPort::readyRead, this, &SerialPort::readData);
}

/*
 * Destructor
*/
SerialPort::~SerialPort()
{
    m_serialPort.close();
}

QStringList SerialPort::portList() const
{
    return m_portList;
}

void SerialPort::setPortList(const QStringList &newPortList)
{
    if (m_portList == newPortList)
        return;
    m_portList = newPortList;
    emit portListChanged();
}

int SerialPort::baudRate() const
{
    return m_baudRate;
}

void SerialPort::setBaudRate(int newBaudRate)
{
    if (m_baudRate == newBaudRate)
        return;
    m_baudRate = newBaudRate;
    qInfo() << "newBaudRate: " << newBaudRate;
    emit baudRateChanged();
}

QString SerialPort::portName() const
{
    return m_portName;
}

void SerialPort::setPortName(const QString &newPortName)
{
    if (m_portName == newPortName)
        return;
    m_portName = newPortName;
    emit portNameChanged();
}

bool SerialPort::isPortOpened() const
{
    return m_isPortOpened;
}

void SerialPort::setIsPortOpened(bool newIsPortOpened)
{
    if (m_isPortOpened == newIsPortOpened)
        return;
    m_isPortOpened = newIsPortOpened;
    emit isPortOpenedChanged();
}

void SerialPort::openSerialPort(const QString portName, const int portBaud)
{
    m_serialPort.close();
    /* Config portName and baudrate */
    m_serialPort.setPortName(portName);
    m_serialPort.setBaudRate(portBaud);

    /* Store current portName and baudrate */
    setPortName(portName);
    setBaudRate(portBaud);

    if(!m_serialPort.open(QIODevice::ReadWrite))
    {
        qInfo() << "Cannnot open port: " << portName;
        return;
    }
    else
    {
        qInfo() << "Open port success: " << portName << " baudrate: " << portBaud;
        setDataResponse("");
        setIsPortOpened(true);
    }
}

void SerialPort::closeSerialPort()
{
    if(m_serialPort.isOpen())
    {
        m_serialPort.close();
    }
    setIsPortOpened(false);
}

void SerialPort::sendData(int cmd)
{
    QByteArray temp;
    temp.append(static_cast<char>(START_BYTE));
    temp.append(static_cast<char>(cmd));
    temp.append(static_cast<char>(STOP_BYTE));
    if(m_isPortOpened)
    {
        m_serialPort.write(temp);
    }
    if(m_serialPort.waitForBytesWritten())
    {
        qInfo() << "Send command success -> " << temp;
    }
}

void SerialPort::scanSerialPort()
{
    m_portList.clear();
    const auto port = QSerialPortInfo::availablePorts();
    for(const QSerialPortInfo &i : port)
    {
        m_portList.append(i.portName());
    }
    emit portListChanged();
}

void SerialPort::readData()
{
    /* Status: START_BYTE MOTOR_SPEED FAN_STATE LIGHT_STATE SENSOR_STATE STOP_BYTE*/
    QString dataReport = "Motor speed: ";
    const QByteArray data = m_serialPort.readAll();
    if(data.at(0) == START_BYTE)
    {
        switch (data.at(1)) {
        case 0:
            dataReport += "OFF";
            break;
        case 1:
            dataReport += "1";
            break;
        case 2:
            dataReport += "2";
            break;
        case 3:
            dataReport += "3";
            break;
        case 4:
            dataReport += "4";
            break;
        default:
            break;
        }

        dataReport += " - Fan speed: ";
        if(data.at(2) == 1)
        {
            dataReport += "ON";
        }
        else
        {
            dataReport += "OFF";
        }

        dataReport += "\nLight: ";
        if(data.at(3) == 1)
        {
            dataReport += "ON";
        }
        else
        {
            dataReport += "OFF";
        }

        dataReport += " - Sensor: ";
        if(data.at(4) == 1)
        {
            dataReport += "ON";
        }
        else
        {
            dataReport += "OFF";
        }
        setDataResponse(dataReport);
    }
    else
    {
        setDataResponse(QString(data));
    }
}

QString SerialPort::message() const
{
    return m_message;
}

void SerialPort::setMessage(const QString &newMessage)
{
    if (m_message == newMessage)
        return;
    m_message = newMessage;
    emit messageChanged();
}

QString SerialPort::dataResponse() const
{
    return m_dataResponse;
}

void SerialPort::setDataResponse(const QString &newDataResponse)
{
    if (m_dataResponse == newDataResponse)
        return;
    m_dataResponse = newDataResponse;
    emit dataResponseChanged();
}
