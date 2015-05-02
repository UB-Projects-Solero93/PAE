/*
 * motores.h
 *
 *  Created on: 26/4/2015
 *      Author: Administrador
 */

//--- Control Table Address ---
//EEPROM AREA
#define P_MODEL_NUMBER_L 0
#define P_MODOEL_NUMBER_H 1
#define P_VERSION 2
#define P_ID 3
#define P_BAUD_RATE 4
#define P_RETURN_DELAY_TIME 5
#define P_CW_ANGLE_LIMIT_L 0x06
#define P_CW_ANGLE_LIMIT_H 0x07
#define P_CCW_ANGLE_LIMIT_L 0x08
#define P_CCW_ANGLE_LIMIT_H 0x09
#define P_SYSTEM_DATA2 10
#define P_LIMIT_TEMPERATURE 11
#define P_DOWN_LIMIT_VOLTAGE 12
#define P_UP_LIMIT_VOLTAGE 13
#define P_MAX_TORQUE_L 14
#define P_MAX_TORQUE_H 15
#define P_RETURN_LEVEL 16
#define P_ALARM_LED 17
#define P_ALARM_SHUTDOWN 18
#define P_OPERATING_MODE 19
#define P_DOWN_CALIBRATION_L 20
#define P_DOWN_CALIBRATION_H 21
#define P_UP_CALIBRATION_L 22
#define P_UP_CALIBRATION_H 23
#define P_TORQUE_ENABLE (24)
#define P_LED (25)
#define P_CW_COMPLIANCE_MARGIN (26)
#define P_CCW_COMPLIANCE_MARGIN (27)
#define P_CW_COMPLIANCE_SLOPE (28)
#define P_CCW_COMPLIANCE_SLOPE (29)
#define P_GOAL_POSITION_L 0x1E
#define P_GOAL_POSITION_H 0x1F
#define P_GOAL_SPEED_L 0x20
#define P_GOAL_SPEED_H 0x21
#define P_TORQUE_LIMIT_L (34)
#define P_TORQUE_LIMIT_H (35)
#define P_PRESENT_POSITION_L (36)
#define P_PRESENT_POSITION_H (37)
#define P_PRESENT_SPEED_L (38)
#define P_PRESENT_SPEED_H (39)
#define P_PRESENT_LOAD_L (40)
#define P_PRESENT_LOAD_H (41)
#define P_PRESENT_VOLTAGE (42)
#define P_PRESENT_TEMPERATURE (43)
#define P_REGISTERED_INSTRUCTION (44)
#define P_PAUSE_TIME (45)
#define P_MOVING (46)
#define P_LOCK (47)
#define P_PUNCH_L (48)
#define P_PUNCH_H (49)

#define MOTOR_DEL_DERECHO 0x03
#define FORWARD_MOTOR_DEL_DERECHO 0x04
#define BACKWARD_MOTOR_DEL_DERECHO 0x04

#define MOTOR_DEL_IZQUIERDO 0x02
#define FORWARD_MOTOR_DEL_IZQUIERDO 0x04
#define BACKWARD_MOTOR_DEL_IZQUIERDO 0x04

#define MOTOR_TRAS_DERECHO 0x01
#define FORWARD_MOTOR_TRAS_DERECHO 0x04
#define BACKWARD_MOTOR_TRAS_DERECHO 0x04

#define MOTOR_TRAS_IZQUIERDO 0x04
#define FORWARD_MOTOR_TRAS_IZQUIERDO 0x04
#define BACKWARD_MOTOR_TRAS_IZQUIERDO 0x04

void angulo_a0(byte bID){
        gbpParameter[0] = P_CW_ANGLE_LIMIT_H; //high de Speed de 0 a 3
        gbpParameter[1] = 0x00;
        TxPacket(bID,2,INST_WRITE);
        escribirRx(RxPacket());

        gbpParameter[0] = P_CW_ANGLE_LIMIT_L; //low de speed de 0 a ff
        gbpParameter[1] = 0x00; //
        TxPacket(bID,2,INST_WRITE);
        escribirRx(RxPacket());

        gbpParameter[0] = P_CCW_ANGLE_LIMIT_H; //high de Speed de 0 a 3
        gbpParameter[1] = 0x00; //
        TxPacket(bID,2,INST_WRITE);
        escribirRx(RxPacket());

        gbpParameter[0] = P_CCW_ANGLE_LIMIT_L; //low de speed de 0 a ff
        gbpParameter[1] = 0x00; //
        TxPacket(bID,2,INST_WRITE);
        escribirRx(RxPacket());

        gbpParameter[0] = P_GOAL_POSITION_H; //high de Speed de 0 a 3
        gbpParameter[1] = 0x00; //
        TxPacket(bID,2,INST_WRITE);
        escribirRx(RxPacket());

        gbpParameter[0] = P_GOAL_POSITION_L; //low de speed de 0 a ff
        gbpParameter[1] = 0x00; //
        TxPacket(bID,2,INST_WRITE);
        escribirRx(RxPacket());

}

void change_velocidad(byte bID, byte H, byte L){
	gbpParameter[0] = P_GOAL_SPEED_H; //high de Speed de 0 a 3
	gbpParameter[1] = H; //
	TxPacket(bID,2,INST_WRITE);

	gbpParameter[0] = P_GOAL_SPEED_L; //low de speed de 0 a ff
	gbpParameter[1] = L; //
	TxPacket(bID,2,INST_WRITE);
}

void init_motor(byte bID){
	angulo_a0(bID);
	change_velocidad(bID, 0, 0);
}

/*
 *Hace falta probar qu� c�mo va
 */

void mover_delante(){
	change_velocidad(1, 1 | FORWARD_MOTOR_DEL_DERECHO, 0);
	change_velocidad(2, 1 | FORWARD_MOTOR_DEL_IZQUIERDO, 0);
	change_velocidad(3, 1 | BACKWARD_MOTOR_TRAS_DERECHO, 0);
	change_velocidad(4, 1 | BACKWARD_MOTOR_TRAS_IZQUIERDO, 0);
}

void mover_atras(){
	change_velocidad(1, 1 | BACKWARD_MOTOR_DEL_DERECHO, 0);
	change_velocidad(2, 1 | BACKWARD_MOTOR_DEL_IZQUIERDO, 0);
	change_velocidad(3, 1 | FORWARD_MOTOR_TRAS_DERECHO, 0);
	change_velocidad(4, 1 | FORWARD_MOTOR_TRAS_IZQUIERDO, 0);
}

void girar_derecha(){
	change_velocidad(1, 1 | FORWARD_MOTOR_DEL_DERECHO, 0);
	change_velocidad(2, 1 | FORWARD_MOTOR_DEL_IZQUIERDO, 0);
	change_velocidad(3, 1 | FORWARD_MOTOR_TRAS_DERECHO, 0);
	change_velocidad(4, 1 | FORWARD_MOTOR_TRAS_IZQUIERDO, 0);
}

void girar_izquierda(){
	change_velocidad(1, 1 | BACKWARD_MOTOR_DEL_DERECHO, 0);
	change_velocidad(2, 1 | BACKWARD_MOTOR_DEL_IZQUIERDO, 0);
	change_velocidad(3, 1 | BACKWARD_MOTOR_TRAS_DERECHO, 0);
	change_velocidad(4, 1 | BACKWARD_MOTOR_TRAS_IZQUIERDO, 0);
}


void mandar_a_todos_motores(byte numParam, byte instruction){

}

void ping(byte bID){
	TxPacket(bID,0,INST_PING);
	escribirRx(RxPacket());
}

void encender_LED(byte bID){
	gbpParameter[0] = P_LED; //Address of LED
	gbpParameter[1] = 1; //Writing Data encender
	TxPacket(bID,2,INST_WRITE);
	escribirRx(RxPacket());

}

void apagar_LED(byte bID){
	gbpParameter[0] = P_LED; //Address of LED
	gbpParameter[1] = 0; //Writing Data apagar
	TxPacket(bID,2,INST_WRITE);

}
