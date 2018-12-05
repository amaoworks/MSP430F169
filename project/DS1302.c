#include <msp430f169.h>
typedef unsigned char uchar;
typedef unsigned int  uint;

/**************�궨��***************/
#define DS_RST  BIT7        //DS_RST = P2.7
#define DS_SCL  BIT5        //DS_SCL = P2.5
#define DS_SDA  BIT6        //DS_SDA = P2.6
#define DS_RST_IN P2DIR &= ~DS_RST
#define DS_RST_OUT P2DIR |= DS_RST
#define DS_RST0 P2OUT &= ~DS_RST
#define DS_RST1 P2OUT |= DS_RST
#define DS_SCL_IN P2DIR &= ~DS_SCL
#define DS_SCL_OUT P2DIR |= DS_SCL
#define DS_SCL0 P2OUT &= ~DS_SCL
#define DS_SCL1 P2OUT |= DS_SCL
#define DS_SDA_IN P2DIR &= ~DS_SDA
#define DS_SDA_OUT P2DIR |= DS_SDA
#define DS_SDA0 P2OUT &= ~DS_SDA
#define DS_SDA1 P2OUT |= DS_SDA
#define DS_SDA_BIT P2IN & DS_SDA

/*******************************************
�������ƣ�delay
��    �ܣ���ʱһ��ʱ��
��    ����time--��ʱ����
����ֵ  ����
********************************************/
void delay(uint time)
{
    uint i;
    for(i=0;i<time;i++)     _NOP();
}
/*******************************************
�������ƣ�Reset_DS1302
��    �ܣ���DS1302���и�λ����
��    ������
����ֵ  ����
********************************************/
void Reset_DS1302(void)
{
    DS_RST_OUT;  //RST��Ӧ��IO����Ϊ���״̬
    DS_SCL_OUT;  //SCLK��Ӧ��IO����Ϊ���״̬
    DS_SCL0;     //SCLK=0
    DS_RST0;     //RST=0
    delay(10);
    DS_SCL1;    //SCLK=1
}
/*******************************************
�������ƣ�Write1Byte
��    �ܣ���DS1302д��1���ֽڵ�����
��    ����wdata--д�������
����ֵ  ����
********************************************/
void Write1Byte(uchar wdata)
{
    uchar i;

    DS_SDA_OUT;     //SDA��Ӧ��IO����Ϊ���״̬
    DS_RST1;        //REST=1;

    for(i=8; i>0; i--)
    {
        if(wdata&0x01)  DS_SDA1;
        else            DS_SDA0;
        DS_SCL0;
        delay(10);
        DS_SCL1;
        delay(10);
        wdata >>=1;
    }
}
/*******************************************
�������ƣ�Read1Byte
��    �ܣ���DS1302����1���ֽڵ�����
��    ������
����ֵ  ��������һ���ֽ�����
********************************************/
uchar Read1Byte(void)
{
    uchar i;
    uchar rdata=0X00;

    DS_SDA_IN;  //SDA��Ӧ��IO����Ϊ����״̬
    DS_RST1;    //REST=1;

    for(i=8; i>0; i--)
    {
        DS_SCL1;
        delay(10);
        DS_SCL0;
        delay(10);
        rdata >>=1;
        if(DS_SDA_BIT)  rdata |= 0x80;
    }

    return(rdata);
}
/*******************************************
�������ƣ�W_Data
��    �ܣ���ĳ���Ĵ���д��һ���ֽ�����
��    ����addr--�Ĵ�����ַ
          wdata--д�������
����ֵ  ����
********************************************/
void W_Data(uchar addr, uchar wdata)
{
    DS_RST0;
    DS_SCL0;
    _NOP();
    DS_RST1;
    Write1Byte(addr);   //д���ַ
    Write1Byte(wdata);  //д������
    DS_SCL1;
    DS_RST0;
}
/*******************************************
�������ƣ�R_Data
��    �ܣ���ĳ���Ĵ�������һ���ֽ�����
��    ����addr--�Ĵ�����ַ
����ֵ  ������������
********************************************/
uchar R_Data(uchar addr)
{
    uchar rdata;

    DS_RST0;
    DS_SCL0;
    _NOP();
    DS_RST1;
    Write1Byte(addr);    //д���ַ
    rdata = Read1Byte();  //��������
    DS_SCL1;
    DS_RST0;

    return(rdata);
}
/*******************************************
�������ƣ�BurstWrite1302
��    �ܣ���burst��ʽ��DS1302д������ʱ������
��    ����ptr--ָ��ʱ�����ݴ�ŵ�ַ��ָ��
����ֵ  ������������
˵    ����ʱ�����ݵĴ�Ÿ�ʽ�ǣ�
          �룬�֣�ʱ���գ��£����ڣ��꣬����
            ��7�����ݣ�BCD��ʽ��+1�����ơ�
********************************************/
void BurstWrite1302(uchar *ptr)
{
    uchar i;

    W_Data(0x8e,0x00);      //����д��
    DS_RST0;
    DS_SCL0;
    _NOP();
    DS_RST1;
    Write1Byte(0xbe);       // 0xbe:ʱ�Ӷ��ֽ�д������
    for (i=8; i>0; i--)
    {
        Write1Byte(*ptr++);
    }
    DS_SCL1;
    DS_RST0;
    W_Data(0x8e,0x80);      // ��ֹд��
}
/*******************************************
�������ƣ�BurstRead1302
��    �ܣ���burst��ʽ��DS1302��������ʱ������
��    ����ptr--ָ����ʱ�����ݵ�ַ��ָ��
����ֵ  ����
˵    ����ʱ�����ݵĴ�Ÿ�ʽ�ǣ�
          �룬�֣�ʱ���գ��£����ڣ��꣬����
            ��7�����ݣ�BCD��ʽ��+1�����ơ�
********************************************/
void BurstRead1302(uchar *ptr)
{
    uchar i;

    DS_RST0;
    DS_SCL0;
    _NOP();
    DS_RST1;
    Write1Byte(0xbf);             //0xbf:ʱ�Ӷ��ֽڶ�����
    for (i=8; i>0; i--)
    {
       *ptr++ = Read1Byte();
    }
    DS_SCL1;
    DS_RST0;
}
/*******************************************
�������ƣ�BurstWriteRAM
��    �ܣ���burst��ʽ��DS1302��RAM��д����������
��    ����ptr--ָ�������ݵ�ַ��ָ��
����ֵ  ����
˵��    ����д��31���ֽڵ�����
********************************************/
void BurstWriteRAM(uchar *ptr)
{
    uchar i;

    W_Data(0x8e,0x00);         //����д��
    DS_RST0;
    DS_SCL0;
    _NOP();
    DS_RST1;
    Write1Byte(0xfe);          //0xfe:RAM���ֽ�д����
    for (i = 31; i>0; i--)     //RAM����31���ֽ�
    {
        Write1Byte(*ptr++);
    }
    DS_SCL1;
    DS_RST0;
    W_Data(0x8e,0x80);          //��ֹд��
}
/*******************************************
�������ƣ�BurstReadRAM
��    �ܣ���burst��ʽ��DS1302��RAM�ж�����������
��    ����ptr--ָ�����ݴ�ŵ�ַ��ָ��
����ֵ  ����
˵��    ��������31���ֽڵ�����
********************************************/
void BurstReadRAM(uchar *ptr)
{
    uchar i;

    DS_RST0;
    DS_SCL0;
    _NOP();
    DS_RST1;
    Write1Byte(0xff);             //0xff:RAM�Ķ��ֽڶ�����
    for (i=31; i>0; i--)
    {
       *ptr++ = Read1Byte();
    }
    DS_SCL1;
    DS_RST0;
}
/*******************************************
�������ƣ�Set_DS1302
��    �ܣ�����DS1302�ڲ���ʱ��
��    ����ptr--ָ�������ݵ�ַ��ָ��
����ֵ  ����
˵��    ��д�����ݵĸ�ʽ��
            �� �� ʱ �� �� ���� ��  ����7���ֽڡ�
********************************************/
void Set_DS1302(uchar *ptr)
{
    uchar i;
    uchar addr = 0x80;

    W_Data(0x8e,0x00);    //����д��

    for(i =7;i>0;i--)
    {
        W_Data(addr,*ptr++);
        addr += 2;
    }
    W_Data(0x8e,0x80);      //��ֹ
}
/********************************************************************
*
* ����: Get_DS1302
* ˵��:
* ����: ��ȡDS1302��ǰʱ��
* ����: R_Data(uchar addr)
* ����: ucCurtime: ���浱ǰʱ���ַ����ǰʱ���ʽΪ: �� �� ʱ �� �� ���� ��
* 7Byte (BCD��) 1B 1B 1B 1B 1B 1B 1B
* ����ֵ: ��
***********************************************************************/
/*******************************************
�������ƣ�Get_DS1302
��    �ܣ���ȡDS1302�ڲ���ʱ��
��    ����ptr--ָ�����ݴ�ŵ�ַ��ָ��
����ֵ  ����
˵��    ���������ݵĸ�ʽ��
            �� �� ʱ �� �� ���� ��  ����7���ֽڡ�
********************************************/
void Get_DS1302(uchar *ptr)
{
    uchar i;
    uchar addr=0x81;

    for(i=0;i<7;i++)
    {
        ptr[i]=R_Data(addr);
        addr+=2;
    }
}
