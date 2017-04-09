/*****************************************
��������־ǿ
ʱ�䣺2010.6.12
���ܣ�NRF24L01��Ƶģ��C�ļ�(�������ղ���)
*****************************************/
#include"NRF24L01.h"
//sbit CE=P1^2;  //RX/TXģʽѡ���
//sbit IRQ=P1^3; //�������ж϶�
//sbit CSN=P1^4; //SPIƬѡ��//����SS
//sbit MOSI=P1^5;	//SPI��������ӻ������
//sbit MISO=P1^6;	//SPI��������ӻ������
//sbit SCLK=P1^7;	//SPIʱ�Ӷ�
  sbit IRQ = P3^7;
  sbit CE =  P3^2;
  sbit CSN=  P3^3;
  sbit SCLK=  P3^4;
  sbit MOSI= P3^5;
  sbit MISO= P3^6;
unsigned char RevTempDate[5]={0,0,0,0,0};//���һλ������Ž�����־
unsigned char code TxAddr[]={0x34,0x43,0x10,0x10,0x01};//���͵�ַ
/*****************״̬��־*****************************************/
unsigned char  bdata sta;   //״̬��־
sbit RX_DR=sta^6;
sbit TX_DS=sta^5;
sbit MAX_RT=sta^4;
/*****************SPIʱ����******************************************/
unsigned char NRFSPI(unsigned char date)
{
    unsigned char i;
   	for(i=0;i<8;i++)          // ѭ��8��
   	{
	  if(date&0x80)
	    MOSI=1;
	  else
	    MOSI=0;   // byte���λ�����MOSI
   	  date<<=1;             // ��һλ��λ�����λ
   	  SCLK=1; 
	  if(MISO)               // ����SCK��nRF24L01��MOSI����1λ���ݣ�ͬʱ��MISO���1λ����
   	    date|=0x01;       	// ��MISO��byte���λ
   	  SCLK=0;            	// SCK�õ�
   	}
    return(date);           	// ���ض�����һ�ֽ�
}
/**********************NRF24L01��ʼ������*******************************/
void NRF24L01Int()
{
//	NRFDelay(2);//��ϵͳʲô������
	CE=0;
	CSN=1;  
	SCLK=0;
	IRQ=1; 
}
/*****************SPI���Ĵ���һ�ֽں���*********************************/
unsigned char NRFReadReg(unsigned char RegAddr)
{
   unsigned char BackDate;
   CSN=0;//����ʱ��
   NRFSPI(RegAddr);//д�Ĵ�����ַ
   BackDate=NRFSPI(0x00);//д����Ĵ���ָ��  
   CSN=1;
   return(BackDate); //����״̬
}
/*****************SPIд�Ĵ���һ�ֽں���*********************************/
unsigned char NRFWriteReg(unsigned char RegAddr,unsigned char date)
{
   unsigned char BackDate;
   CSN=0;//����ʱ��
   BackDate=NRFSPI(RegAddr);//д���ַ
   NRFSPI(date);//д��ֵ
   CSN=1;  
   return(BackDate);
}
/*****************SPI��ȡRXFIFO�Ĵ�����ֵ********************************/
unsigned char NRFReadRxDate(unsigned char RegAddr,unsigned char *RxDate,unsigned char DateLen)
{  //�Ĵ�����ַ//��ȡ���ݴ�ű���//��ȡ���ݳ���//���ڽ���
    unsigned char BackDate,i;
	CSN=0;//����ʱ��
	BackDate=NRFSPI(RegAddr);//д��Ҫ��ȡ�ļĴ�����ַ
	for(i=0;i<DateLen;i++) //��ȡ����
	  {
	     RxDate[i]=NRFSPI(0);
	  } 
    CSN=1;
   return(BackDate); 
}
/*****************SPIд��TXFIFO�Ĵ�����ֵ**********************************/
unsigned char NRFWriteTxDate(unsigned char RegAddr,unsigned char *TxDate,unsigned char DateLen)
{ //�Ĵ�����ַ//д�����ݴ�ű���//��ȡ���ݳ���//���ڷ���
   unsigned char BackDate,i;
   CSN=0;
   BackDate=NRFSPI(RegAddr);//д��Ҫд��Ĵ����ĵ�ַ
   for(i=0;i<DateLen;i++)//д������
     {
	    NRFSPI(*(TxDate+i));
	 }   
   CSN=1;
   return(BackDate);
}
/*****************NRF����Ϊ����ģʽ����������******************************/
//CE��ʼ����󣬱���10us������
void NRFSetTxMode(char *TxDate)
{  //����ģʽ 
   CE=0; 
   	NRFWriteTxDate(W_REGISTER+TX_ADDR,TxAddr,TX_ADDR_WITDH);//д�Ĵ���ָ��+���յ�ַʹ��ָ��+���յ�ַ+��ַ����
	NRFWriteTxDate(W_REGISTER+RX_ADDR_P0,TxAddr,TX_ADDR_WITDH);//Ϊ��Ӧ������豸������ͨ��0��ַ�ͷ��͵�ַ��ͬ
	NRFWriteTxDate(W_TX_PAYLOAD,TxDate,TX_DATA_WITDH);//д������ 
	/******�����йؼĴ�������**************/
  	NRFWriteReg(W_REGISTER+EN_AA,0x01);       // ʹ�ܽ���ͨ��0�Զ�Ӧ��
  	NRFWriteReg(W_REGISTER+EN_RXADDR,0x01);   // ʹ�ܽ���ͨ��0
  	NRFWriteReg(W_REGISTER+SETUP_RETR,0x0a);  // �Զ��ط���ʱ�ȴ�250us+86us���Զ��ط�10��
  	NRFWriteReg(W_REGISTER+RF_CH,0x40);         // ѡ����Ƶͨ��0x40
  	NRFWriteReg(W_REGISTER+RF_SETUP,0x07);    // ���ݴ�����1Mbps�����书��0dBm���������Ŵ�������
	NRFWriteReg(W_REGISTER+CONFIG,0x0e);      // CRCʹ�ܣ�16λCRCУ�飬�ϵ�  
	CE=1;
	//NRFDelay(5);//����10us������
} 
/*****************NRF����Ϊ����ģʽ����������******************************/

 //����ģʽ
//CE��ʼ����󣬱���10us������
void NRFSetRXMode()
{
    CE=0;
  	NRFWriteTxDate(W_REGISTER+RX_ADDR_P0,TxAddr,TX_ADDR_WITDH);  // �����豸����ͨ��0ʹ�úͷ����豸��ͬ�ķ��͵�ַ
  	NRFWriteReg(W_REGISTER+EN_AA,0x01);               // ʹ�ܽ���ͨ��0�Զ�Ӧ��
  	NRFWriteReg(W_REGISTER+EN_RXADDR,0x01);           // ʹ�ܽ���ͨ��0
  	NRFWriteReg(W_REGISTER+RF_CH,0x40);                 // ѡ����Ƶͨ��0x40
  	NRFWriteReg(W_REGISTER+RX_PW_P0,TX_DATA_WITDH);  // ����ͨ��0ѡ��ͷ���ͨ����ͬ��Ч���ݿ���
  	NRFWriteReg(W_REGISTER+RF_SETUP,0x07);            // ���ݴ�����1Mbps�����书��0dBm���������Ŵ�������
	NRFWriteReg(W_REGISTER+CONFIG,0x0f);             // CRCʹ�ܣ�16λCRCУ�飬�ϵ磬����ģʽ     
  	CE = 1; 
//	NRFDelay(5);    
}
/****************************����Ƿ��н��յ�����******************************/
unsigned char CheckACK()
{  //���ڷ���
	sta=NRFReadReg(R_REGISTER+STATUS);                    // ����״̬�Ĵ���
	if(TX_DS||MAX_RT) //��������ж�
	{
	   NRFWriteReg(W_REGISTER+STATUS,0xff);  // ���TX_DS��MAX_RT�жϱ�־
	   CSN=0;
	   NRFSPI(FLUSH_TX);//�������FIFO �����ؼ�������Ȼ��������벻���ĺ����������Ҽ�ס����  
       CSN=1; 
	   return(0);
	}
	else
	   return(1);
}
/*************************��������*********************************************/
void GetDate()				 
{
  sta=NRFReadReg(R_REGISTER+STATUS);//�������ݺ��ȡ״̬�Ĵ���
    if(RX_DR)				// �ж��Ƿ���յ�����
     {
	   CE=0;//����
	   NRFReadRxDate(R_RX_PAYLOAD,RevTempDate,RX_DATA_WITDH);// ��RXFIFO��ȡ���� ����4λ���ɣ���һλλ����λ
	   NRFWriteReg(W_REGISTER+STATUS,0xff); //���յ����ݺ�RX_DR,TX_DS,MAX_PT���ø�Ϊ1��ͨ��д1������жϱ�
	   CSN=0;
	   NRFSPI(FLUSH_RX);//�������FIFO �����ؼ�������Ȼ��������벻���ĺ����������Ҽ�ס���� 
	   CSN=1;		 
     }
    NRFWriteReg(W_REGISTER+STATUS,0xff); //���յ����ݺ�RX_DR,TX_DS,MAX_PT���ø�Ϊ1��ͨ��д1������жϱ�	  	  
} 