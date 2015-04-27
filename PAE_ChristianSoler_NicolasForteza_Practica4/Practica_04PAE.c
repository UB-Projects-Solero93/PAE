/******************************
 *
 * PR�CTICA 4_PIH Programaci� de Ports i pr�ctica de: "do-while" "case" "if" i "for"
 *
 *****************************/

#include <msp430x54xA.h>
#include <stdio.h>
#include "hal_lcd.h"
#include "constants.h"
#include "control_pantalla.h"
#include "envio_recibir_instruc.h"
#include "motores.h"

long int i;




/**************************************************************************
 * INICIALIZACI�N DE LOS BOTONES.
 * Configuramos botones y leds:
 *
 * Sin datos de entrada
 *
 * Sin datos de salida
 *
 **************************************************************************/

void init_botons(void)
{
  //Configuramos botones y leds:
  P1DIR |= 0x03;	//Puertos P1.0 y P1.1 como salidas (Leds)
  P1OUT |= 0x01;	//Inicializamos puerto P1.0 a 1,
  P1OUT &= 0xFD;	// y P1.1 a 0, para leds en alternancia


  P2DIR &= ~0xC0;	//Puertos P2.6 y P2.7 como entradas (botones S1 y S2)
  P2SEL &= ~0xC0;	//Puertos P2.6 y P2.7 como I/O digitales,
  P2REN |= 0xC0;	//con resistencia activada
  P2OUT |= 0xC0;	// de pull-up
  P2IE |= 0xC0; 	//Interrupciones activadas en P2.6 y P2.7,
  P2IES &= ~0xC0;	// con transicion L->H


  //Configuramos el joystick:
  P2DIR &= ~0x3E;	//Puertos P2.1 a P2.5 como entradas (joystick)
  P2SEL &= ~0x3E;	//Puertos P2.1 y P2.5 como I/O digitales,
  P2REN |= 0x3E;	//con resistencia activada
  P2OUT |= 0x3E;	// de pull-up
  P2IE |= 0x3E; 	//Interrupciones activadas en P2.1 a P2.5,
  P2IES &= ~0x3E;	// con transicion L->H

}


void escribirRx(struct RxReturn respuesta ){
	byte bCount;
	for(bCount = 0; bCount < 4; bCount++){

	sprintf(cadena," %x ", respuesta.StatusPacket[bCount]);
	escribir(cadena, bCount+1);
	}
}




/************
 * MAIN
 ************
 */
void main(void)
{
	init_UCS();
	init_UART();
   	WDTCTL = WDTPW+WDTHOLD;       	// Paramos el watchdog timer

  	init_botons();					// Iniciamos los botones y Leds.

    init_LCD();						// Inicializamos la pantalla
    _enable_interrupt();
  	linea++; 					//Aumentamos el valor de linea y con ello pasamos a la linea siguiente


  	P4OUT = 0x01;
  	//AQUI------Nuevo--------------------------

  	change_velocidad(1, 0, 1);

  	//gbpParameter[0] = P_LED; //Address of LED
  	//gbpParameter[1] = 1; //Writing Data encender
  	/*bTxPacketLength =*/
  	//TxPacket(4,0,INST_PING);
  	//escribirRx(RxPacket());
  	//TxPacket(4,2,INST_WRITE);
  	//gbpParameter[1] = 0;//apagar
  	//TxPacket(1,2,INST_WRITE);
  	//bRxPacketLength = RxPacket(DEFAULT_RETURN_PACKET_SIZE);



  	//-----------------------




  	do//do While de todo el programa
   	{

  		//el programa espera a una interrupcion

   	}while(1);
}


/**************************************************************************
 * MINIPROGRAMA DE LOS BOTONES:
 * Mediante este programa, se detectar� que bot�n se ha pulsado
 *
 * Sin Datos de entrada
 *
 * Sin datos de salida
 *
 * Actualiza el valor estado
 *
 **************************************************************************/
/*
#pragma vector=PORT2_VECTOR  //interrupci�n de los botones. Actualiza el valor de la variable global estado.
__interrupt void Port2_ISR(void)
{
	P2IE &= 0xC0; 	//interrupciones botones S1 y S2 (P2.6 y P2.7) desactivadas
	P2IE &= 0x3E;   //interrupciones joystick (2.1-2.5) desactivadas

	/**********************************************************+
		A RELLENAR POR EL ALUMNO BLOQUE CASE

	Boton S1, estado =1 y editar horas(del reloj o la alarma)
	Boton S2, estado =2 y editar minutos(del reloj o la alrma)
	Joystick left, estado =3 y los LEDs rotan a la izquierda
	Joystick right, estado =4 y los LEDs rotan a la derecha
	Joystick center, estado = 5 y Canvia Modo a Editar Reloj/Alarma
	Joystick up, estado =6 y disminuye el timer y van mas rapidos los LEDs
	Joystick down, estado =7 y aumenta el timer y van mas lentos los LEDs
	 * *********************************************************

	switch(P2IFG){

	case 2://Joystick a la izquierda
		izquierda=1;//este valor hara que giren los LEDs hacia la izquierda
		P1OUT &=0x00;
		break;
	case 4:// Joystick a l derecha
		izquierda=0;//este valor hara que giren los LEDs hacia la derecha
		P1OUT &=0x00;
		break;
	case 8://Joystick centro
		if(editAlarm==1){
			editAlarm=0;//Modo editar hora
		}else{
			editAlarm=1;//Modo editar alarma
		}
		break;
	case 16://Joystick Arriba
		if(timer>=300){//Minimo cad 300 ms
			timer-= 100;//mas rapido, disminuye el valor de timer
			borrar(linea);
			escribirTimer();//actualiza el valor de timer mostrado
		}
		P1OUT &=0x00;
		break;
	case 32://Joystick abajo
		if(timer <= 3000){//maximo cada 3 segundos
			timer+= 100;//mas lento, aumenta el valor de Timer
			borrar(linea);
			escribirTimer();//actualiza el valor de timer mostrado
		}
		P1OUT &=0x00;
		break;
	case 64://Boton S1
		if(editAlarm==1){//si esta en Modo deitar Alarma
			sumar1horaAlarma();//suma 1 a la hora de la alarma
			escribirAlarma();//actualiza la pantalla
		}else{//si esta en  Modo editar reloj
			sumar1hora();//suma 1 a la hora del reloj
			escribirHora();//actualiza la pantalla
		}
		break;
	case 128://boton S2
		if(editAlarm==1){//si esta en Modo editar alarma
			sumar1minAlarma();//suma 1 a el minutero de la alarma
			escribirAlarma();//actualiza la pantalla
		}else{//si esta en Modo editar reloj
			sumar1min();//suma 1 al minuter del reloj
			escribirHora();//actualiza la pantalla
		}
		break;
	}

	/***********************************************
   	 * HASTA AQUI BLOQUE CASE
   	 ***********************************************
	
	P2IFG = 0;		//limpiamos todas las interrupciones
	P2IE |= 0xC0; 	//interrupciones botones S1 y S2 (P2.6 y P2.7) reactivadas
	P2IE |= 0x3E;  //interrupciones joystick (2.1-2.5) reactivadas
 return;
}
*/





#pragma vector=USCI_A0_VECTOR
__interrupt void USCI_A0_ISR(void)
{
//interrupcion de recepcion en la uart A0
UCA0IE &= ~UCRXIE; //Interrupciones desactivadas en RX
DatoLeido_UART = UCA0RXBUF;
Byte_Recibido=1;

UCA0IE |= UCRXIE; //Interrupciones reactivadas en RX
}