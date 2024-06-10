#include "RX8010SJ.h"

#define SDA 4
#define SCL 5

int RX_sec;
int RX_min;
int RX_hour;
int RX_week;
int RX_day;
int RX_month;
int RX_year;

int decimal_bcd_code(int decimal)
{
	int sum = 0, i;
	for ( i = 0; decimal > 0; i++)
	{
		sum |= ((decimal % 10 ) << ( 4*i));
		decimal /= 10;
	}
	return sum;
}

int bcd_decimal_code( int bcd)
{
	int sum = 0, c = 1;  // sum返回十进制，c每次翻10倍
 
	for(int i = 1; bcd > 0; i++)
	{
		if( i >= 2)
		{
			c*=10;
		}
 
		sum += (bcd%16) * c;
 
		bcd /= 16;  // 除以16同理与十进制除10将小数点左移一次，取余16也同理
	}
 
	return sum;
}

uint8_t hex_to_bcd(uint8_t data)
{
    uint8_t temp;

    temp = (((data/10)<<4) + (data%10));

    return temp;
}

uint8_t bcd_to_hex(uint8_t data)
{
    uint8_t temp;

    temp = ((data>>4)*10 + (data&0x0f));
    return temp;
}
void iic_init(){

    pinMode(SDA, OUTPUT);
    pinMode(SCL, OUTPUT);
}

//0为输出模式 1为输入模式
void SDA_Mode(uint8_t m){
    if (m == 0) 
    {
        pinMode(SDA,OUTPUT);
    }
    else if (m == 1)
    {
        pinMode(SDA, INPUT);
    }
    
}

uint8_t SDA_Read(){

    if (digitalRead(SDA)) return 1;
    else return 0;
    
}

//0为低电平 1为高电平
void SDA_Pin(uint8_t m){
    if (!m)
    {
        digitalWrite(SDA, LOW);
    }
    else if (m)
    {
        digitalWrite(SDA, HIGH);
    }
}

//0为低电平 1为高电平
void SCL_Pin(uint8_t m){
    if (!m)
    {
        digitalWrite(SCL, LOW);
    }
    else if (m)
    {
        digitalWrite(SCL, HIGH);
    }
}

void iic_start(){

    SDA_Mode(0);
    SDA_Pin(1);
    delayMicroseconds(10);
    SCL_Pin(1);
    delayMicroseconds(10);
    SDA_Pin(0);
    delayMicroseconds(10);
    SCL_Pin(0);

}

void iic_restart(){

    SDA_Mode(0);
    SDA_Pin(1);
    delayMicroseconds(10);
    SCL_Pin(1);
    delayMicroseconds(10);
    SDA_Pin(0);



}


void iic_stop(){
    SDA_Mode(0);    
    SDA_Pin(0);
    delayMicroseconds(10);
    SCL_Pin(0);
    delayMicroseconds(10);
    SCL_Pin(1);
    delayMicroseconds(10);
    SDA_Pin(1);


}

void iic_send_ack(){

	SCL_Pin(0);    	
	SDA_Mode(0);		
	SDA_Pin(0);		
	delayMicroseconds(10);	
	SCL_Pin(1);		
	delayMicroseconds(10);	
	SCL_Pin(0);		

}

void iic_send_nack(){

    SCL_Pin(0);
    SDA_Mode(0);
    SDA_Pin(0);
    delayMicroseconds(10);
    SDA_Pin(0);
    delayMicroseconds(10);
    SCL_Pin(0);

}

uint8_t iic_wait_ack(){

    SCL_Pin(0);
    SDA_Mode(1);
    delayMicroseconds(10);
    SCL_Pin(1);
    delayMicroseconds(10);
    SDA_Read();
    delayMicroseconds(10);
    SCL_Pin(0);
    delayMicroseconds(10);
    if (!SDA_Read())
    {
        return 0;
    }
    else return 1;

}

void iic_Ack(void)
{
    SCL_Pin(0);   
    SDA_Mode(1);    
    delayMicroseconds(10);
    SDA_Pin(0);    
    delayMicroseconds(10);
    SCL_Pin(1);   
    delayMicroseconds(10);
    SCL_Pin(0);   
}

void iic_send_byte(uint8_t data){
    uint8_t i;
    SDA_Mode(0);
    SCL_Pin(0);
    for ( i = 0; i < 8; i++)
    {
        SDA_Pin((data&0x80)>>7);
        data<<=1;
        delayMicroseconds(10);
        SCL_Pin(1);
        delayMicroseconds(10);
        SCL_Pin(0);

    }

}

int iic_recv_byte(uint8_t ack){
    uint8_t i,data;
    SDA_Mode(1);
    for ( i = 0; i < 8; i++)
    {
        SCL_Pin(0);
        delayMicroseconds(10);
        SCL_Pin(1);
        data<<=1;
        if (SDA_Read())data++;
        delayMicroseconds(10);
    }
    if (ack) iic_send_ack();
    else     iic_send_nack();
    return ((data>>4)*10 + (data&0x0f));
}


void Time_Read_RX8010(tm *time1){

    iic_start();
    iic_send_byte(Write);
    iic_wait_ack();
    iic_send_byte(SEC);
    iic_wait_ack();
    iic_start();
    iic_send_byte(Read);
    iic_wait_ack();
    time1->tm_sec=iic_recv_byte(1);
    time1->tm_min=iic_recv_byte(1);
    time1->tm_hour=iic_recv_byte(1);
    time1->tm_wday=iic_recv_byte(1);
    time1->tm_mday=iic_recv_byte(1);
    time1->tm_mon=iic_recv_byte(1);
    time1->tm_year=iic_recv_byte(1);
    iic_stop();

}

void Write_num(int sec, int min, int hour, int week,int day, int month, int year){

    iic_start();
    iic_send_byte(Write);
    iic_wait_ack();
    iic_send_byte(SEC);
    iic_wait_ack();
    iic_send_byte(sec);
    iic_wait_ack();
    iic_send_byte(min);
    iic_wait_ack();
    iic_send_byte(hour);
    iic_wait_ack();
    iic_send_byte(week);
    iic_wait_ack();
    iic_send_byte(day);
    iic_wait_ack();
    iic_send_byte(month);
    iic_wait_ack();
    iic_send_byte(year);
    iic_wait_ack();
    iic_stop();    
}






void Time_write(tm time2){
    RX_sec=hex_to_bcd(time2.tm_sec);
    RX_min=hex_to_bcd(time2.tm_min);
    RX_hour=hex_to_bcd(time2.tm_hour);
    switch (time2.tm_wday)
    {
    case 0: time2.tm_wday=0x01; break;
    case 1: time2.tm_wday=0x02; break;    
    case 2: time2.tm_wday=0x04; break;
    case 3: time2.tm_wday=0x08; break;    
    case 4: time2.tm_wday=0x10; break;
    case 5: time2.tm_wday=0x20; break;
    case 6: time2.tm_wday=0x40; break;
    default:
        break;
    }
    RX_week=time2.tm_wday;
    RX_day=hex_to_bcd(time2.tm_mday);
    RX_month=hex_to_bcd(time2.tm_mon+1);
    RX_year=hex_to_bcd(time2.tm_year-100);
    Write_num(RX_sec, RX_min, RX_hour, RX_week, RX_day, RX_month, RX_year);


}

void time_init(){
    
    Write_num(hex_to_bcd(0),hex_to_bcd(0),hex_to_bcd(0),hex_to_bcd(0),hex_to_bcd(7),hex_to_bcd(1),hex_to_bcd(1970));

}