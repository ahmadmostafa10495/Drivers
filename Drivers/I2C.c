#include "I2C.h"
void I2C_Init (){
	TWBR = 0x02;
	TWSR = 0x00;
	TWAR = 0b00000010;
	TWCR = (1<<TWEN);
}
void I2C_Start(){
	TWCR = (1 << TWINT) | (1 << TWSTA) | (1 << TWEN);
	while(BIT_IS_CLEAR(TWCR,TWINT));
}
void I2C_Stop(){
	TWCR = (1<<TWINT)|(1<<TWSTO)|(1<<TWEN);
}
unsigned char I2C_ReadACK(){
	TWCR = (1<<TWINT)|(1<<TWEN)|(1<<TWEA);
	while(BIT_IS_CLEAR(TWCR,TWINT));
	return TWDR;
}
unsigned char I2C_ReadNACK(){
	TWCR = (1<<TWINT)|(1<<TWEN);
	while(BIT_IS_CLEAR(TWCR,TWINT));
	return TWDR;
}
void I2C_Write(unsigned char toWrite){
	TWDR=toWrite;
	TWCR = (1<<TWINT)|(1<<TWEN);
	while(BIT_IS_CLEAR(TWCR,TWINT));
}
unsigned char I2C_GetStatus(){
	unsigned char status;
	status = TWSR & 0xF8;
	return status;
}
