#ifndef APPENUM_H
#define APPENUM_H

#include <QObject>

class AppEnum : public QObject{
    Q_OBJECT
public:
    enum CMD
    {
        CMD_TURN_OFF_ALL = 0x01,
        CMD_SET_MOTOR_SPEED_1 = 0x02,
        CMD_SET_MOTOR_SPEED_2  = 0x03,
        CMD_SET_MOTOR_SPEED_3 = 0x04,
        CMD_SET_MOTOR_SPEED_4 = 0x05,
        CMD_TURN_OFF_ALL_MOTOR = 0x06,
        CMD_TURN_ON_WARM_LIGHT = 0x07,
        CMD_TURN_OFF_WARM_LIGHT = 0x08,
        CMD_TURN_ON_FAN = 0x09,
        CMD_TURN_OFF_FAN = 0x10,
        CMD_REPORT_STATE = 0x11,
        CMD_SET_TIME_OUT = 0x12
    };
    Q_ENUM(CMD);
};

#endif // APPENUM_H
