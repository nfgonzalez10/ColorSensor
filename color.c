
#include <K:\VII Semestre\Sensórica\Llamados\llamados.c>
#include <K:\VII Semestre\Sensórica\LCD\LCD.c>

void reconocer_dato(int16 dato){
int udmil,centenas,decenas, unidades,mod1,x;
if(dato>=1000){
x=dato/100;
udmil=x/10;
centenas=x%10;
mod1=dato%100;
decenas=mod1/10;
unidades=mod1%10;
}

if(dato>=100 && dato<1000){
udmil=0;
centenas=dato/100;
mod1=dato%100;
decenas=mod1/10;
unidades=mod1%10;

}

if(dato<100){
udmil=0;
centenas=0;
decenas=dato/10;
unidades=dato%10;

}

enviar(comando,0x88);
mensaje(udmil+0x30);
enviar(comando,0x89);
mensaje(centenas+0x30);
enviar(comando,0x8a);
mensaje(decenas+0x30);
enviar(comando,0x8b);
mensaje(unidades+0x30);
}
void voltaje(int16 dato){
int32 voltaje1=0, voltaje2=0, voltaje3=0;
voltaje1=5*dato;
voltaje2=voltaje1*100;
voltaje3=voltaje2/1023;

if(voltaje3>=156 && voltaje3<171){
enviar(comando,0xc6);
mensaje("no");
enviar(comando,0xc8);
mensaje("       ");

}

if(voltaje3>=225 && voltaje3<245){
enviar(comando,0xc6);
mensaje("negro");
enviar(comando,0xcb);
mensaje("       ");

}
if(voltaje3>=172 && voltaje3<225){
enviar(comando,0xc6);
mensaje("verde");
enviar(comando,0xcb);
mensaje("       ");

}

if(voltaje3>=87 && voltaje3<123){
enviar(comando,0xc6);
mensaje("Rojo");
enviar(comando,0xca);
mensaje("       ");
}

if(voltaje3>=50 && voltaje3<87){
enviar(comando,0xc6);
mensaje("Naranja");
enviar(comando,0xcd);
mensaje(" ");

}



enviar(comando,0xc0);
mensaje("Color:");

}


void main()

{
int16 datos=0;

trisa=0x01;
trisb=0;
trisc=0;
ADCON0=0X01;
ADCON1=0X0E;
ADCON2= 0x87;
 rcsta=0x90;
 txsta=0x24;
 spbrg=0x19;
inicio();
while(1){
bit_set(ADCON0,1);
while(bit_test(ADCON0,1)==1){}
datos=datos+ADRESH;
datos=ADRESH<<8;
datos=datos+ADRESL;
voltaje(datos);
reconocer_dato(datos);

}
}
