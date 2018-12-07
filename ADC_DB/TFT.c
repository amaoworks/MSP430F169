#include "TFT.h"

/****************************************************************************************************
�ļ�����������320x240TFT�������򣬿���TFTʵ�ֺ���,�ַ���ʾ,���㹦�ܡ�
 ****************************************************************************************************/
#ifndef u8
#define u8 unsigned char
#endif

#ifndef u16
#define u16 unsigned int
#endif
//**************�����ⲿ�����ͱ���**************

extern unsigned int Device_code;

/****************************************************************************************************
//  ʵ�ֹ��ܣ�   ��ʱ
//  ���������   count ������ʱʱ��
 ****************************************************************************************************/
void delayms(unsigned int count)
{
    int i,j;
    for(i=0;i<count;i++)
    {
        for(j=0;j<0x640;j++);
    }
}

/********************************************************************
//  ʵ�ֹ��ܣ�   д����
//  ���������  DH ��Ҫ����16bits����ĸ�8λ
//              DL ��Ҫ����16bits����ĵ�8λ
 ********************************************************************/
void Write_Cmd(uchar DH,uchar DL)
{
    CS_CLR;
    RS_CLR;
    RD_SET;
    RW_CLR;

    //ע�⣺��ʹ��8λ���ݿ�����16λ����ģʽʱ��ʹ��74HC573��ΪIO��չ����������
    DataPort=DH;              //�͸�8λ�����573������
    LE_SET;                   //����λ
    LE_CLR;                   //�Ͽ�����,λѡ573��Q7~Q0�Ա���
    DataPort=DL;              //�͵�8λ�����TFT
    /*
  //���ʹ��16λ���ݿ�����16λ����ģʽ��������IO��չ��ֱ�ӽ������͵����ݿڼ���
  DataPort_L=DL;
  DataPort_H=DH;
     */

    RW_SET;
    CS_SET;
}

/********************************************************************
//  ʵ�ֹ��ܣ�   д����(2*8bits)
//  ���������  DH ��Ҫ����16bits���ݵĸ�8λ
//              DL ��Ҫ����16bits���ݵĵ�8λ
 ********************************************************************/
void Write_Data(uchar DH,uchar DL)
{
    CS_CLR;
    RS_SET;
    //ע�⣺��ʹ��8λ���ݿ�����16λ����ģʽʱ��ʹ��74HC573��ΪIO��չ����������
    DataPort=DH;              //�͸�8λ���ݸ�573������
    LE_SET;                   //����λ
    LE_CLR;                   //�Ͽ�����,λѡ573��Q7~Q0�Ա���
    DataPort=DL;              //�͵�8λ���ݸ�TFT

    /*
  //���ʹ��16λ���ݿ�����16λ����ģʽ��������IO��չ��ֱ�ӽ������͵����ݿڼ���
  DataPort_L=DL;
  DataPort_H=DH;
     */

    RW_CLR;
    RW_SET;
    CS_SET;
}

/****************************************************************************************************
//  ʵ�ֹ��ܣ�   д����(16λ)
//  ���������  y ��Ҫ����16bits����
 ****************************************************************************************************/
void  Write_Data_U16(unsigned int y)
{
    unsigned char m,n;
    m=y>>8;
    n=y;
    Write_Data(m,n);
}

/****************************************************************************************************
//  ʵ�ֹ��ܣ�   ��x�Ĵ���д��y����
//  ���������  x ��Ҫ��������� 16λ
//              y ��Ҫ��������� 16λ
 ****************************************************************************************************/
void  Write_Cmd_Data (unsigned char x,unsigned int y)
{
    unsigned char m,n;
    m=y>>8;
    n=y;
    Write_Cmd(0x00,x);
    Write_Data(m,n);
}

/****************************************************************************************************
//  ʵ�ֹ��ܣ�   ��������
//  ���������  x0��y0 ��ʼ����
//              x1��y1 ��������
 ****************************************************************************************************/
void LCD_SetPos(unsigned int x0,unsigned int x1,unsigned int y0,unsigned int y1)
//void LCD_SetPos(int x0,int x1,int y0,int y1)
{

    Write_Cmd_Data(0x50,x0);  // Horizontal GRAM Start Address
    Write_Cmd_Data(0x51,x1);  // Horizontal GRAM End Address
    Write_Cmd_Data(0x52,y0);  // Vertical GRAM Start Address
    Write_Cmd_Data(0x53,y1);  // Vertical GRAM Start Address
    Write_Cmd_Data(0x20,x0);  // GRAM horizontal Address
    Write_Cmd_Data(0x21,y0);  // GRAM Vertical Address
    Write_Cmd (0x00,0x22);    // 0x0022,Start to Write Data to GRAM
}

/****************************************************************************************************
//  ʵ�ֹ��ܣ�   TFT����
//  ���������   bColor ������ʹ�õı���ɫ
 ****************************************************************************************************/
void CLR_Screen(unsigned int bColor)
{
    unsigned int i,j;
    LCD_SetPos(0,239,0,319);                                                   //320x240�������0��ʼ
    for (i=0;i<240;i++)
    {
        for (j=0;j<320;j++)
            Write_Data_U16(bColor);
    }
}

/****************************************************************************************************
//  ʵ�ֹ��ܣ�   ��ʾAscii�ַ�
//  ���������  x ������
//              y ������
//              c ��Ҫ��ʾ���ַ�
//              fColor �ַ���ɫ
//              bColor �ַ�������ɫ
 ****************************************************************************************************/
void LCD_PutChar(unsigned int x, unsigned int y, char c, unsigned int fColor, unsigned int bColor)
{
    unsigned int i,j;
    LCD_SetPos(x,x+16-1,y-8+1,y);                    //�����ַ���ʾλ��
    for(i=0; i<16;i++) {                             //ѭ��д��16�ֽڣ�һ���ַ�Ϊ16�ֽ�
        unsigned char m=Font8x16[(c-0x20)*16+i];  //��ȡc�ַ��ĵ�i���ֽ���,c��ȥ0x20������Ascii����е�0~1f��ȥ��
        for(j=0;j<8;j++) {                        //ѭ��д��8λ��һ���ֽ�Ϊ8λ
            if((m&0x80)==0x80) {                  //�ж����λ�Ƿ�Ϊ1
                Write_Data_U16(fColor);           //���λΪ1��д���ַ���ɫ
            }
            else {
                Write_Data_U16(bColor);           //���λΪ0��д�뱳����ɫ
            }
            m<<=1;                                //����1λ��׼��д��һλ
        }
    }
}

/****************************************************************************************************
//  ʵ�ֹ��ܣ�   ��ʾ����Ascii�ַ�����Ҫ��Ϊ����������
//  ��������� x ������
//            y ������
//              c ��Ҫ��ʾ���ַ�
//              fColor �ַ���ɫ
//              bColor �ַ�������ɫ
 ****************************************************************************************************/
void LCD_PutSingleChar(unsigned int x, unsigned int y, char c, unsigned int fColor, unsigned int bColor)
{
    unsigned int i,j;

    i=y;
    j=x;
    x=i;
    y=319-j;

    LCD_SetPos(x,x+16-1,y-8+1,y);                    //�����ַ���ʾλ��
    for(i=0; i<16;i++) {                             //ѭ��д��16�ֽڣ�һ���ַ�Ϊ16�ֽ�
        unsigned char m=Font8x16[(c-0x20)*16+i];        //��ȡc�ַ��ĵ�i���ֽ���,c��ȥ0x20������Ascii����е�0~1f��ȥ��
        for(j=0;j<8;j++) {                              //ѭ��д��8λ��һ���ֽ�Ϊ8λ
            if((m&0x80)==0x80) {                            //�ж����λ�Ƿ�Ϊ1
                Write_Data_U16(fColor);                         //���λΪ1��д���ַ���ɫ
            }
            else {
                Write_Data_U16(bColor);                         //���λΪ0��д�뱳����ɫ
            }
            m<<=1;                                          //����1λ��׼��д��һλ
        }
    }
}

/****************************************************************************************************
//  ʵ�ֹ��ܣ�   ��ʾ16x16����
//  ��������� x ������
//            y ������
//              g ��Ҫ��ʾ���ַ�����
//              fColor �ַ���ɫ
//              bColor �ַ�������ɫ
 ****************************************************************************************************/

void Put16x16(unsigned short x, unsigned short  y, unsigned char g[2], unsigned int fColor,unsigned int bColor)
{
    unsigned int i,j,k;

    LCD_SetPos(x,  x+16-1,y-16+1, y);                       //���ú�����ʾλ��

    for (k=0;k<64;k++)                                      //ѭ��64�Σ���ѯ������ģλ��
    {
        if ((ch16[k].GBK[0]==g[0])&&(ch16[k].GBK[1]==g[1]))   //�жϵ�k�����ֵı����Ƿ������뺺��g[2]���
        {
            for(i=0;i<32;i++)                                   //�����ȣ������ҵ�����ʾ��ģλ�ã�ѭ��д��32�ֽ�
            {
                unsigned short m=ch16[k].hz16[i];                     //��ȡ32�ֽ��еĵ�i�ֽ�
                for(j=0;j<8;j++)                                      //ѭ��д��8λ����
                {
                    if((m&0x80)==0x80) Write_Data_U16(fColor);             //�ж����λ�Ƿ�Ϊ1,���λΪ1��д���ַ���ɫ
                    else              Write_Data_U16(bColor);              //���λΪ0��д�뱳����ɫ
                    m<<=1;                                             //����1λ��׼��д��һλ
                }
            }
        }
    }
}

/****************************************************************************************************
��������: ��ʾ����24x24
���������x ������
         y ������
         c ��Ҫ��ʾ�ĺ�����
           fColor �ַ���ɫ
         bColor �ַ�������ɫ
 ****************************************************************************************************/
void PutGB2424(unsigned short x, unsigned short  y, unsigned char c[2], unsigned int fColor,unsigned int bColor){
    unsigned int i,j,k;

    LCD_SetPos(x,  x+24-1,y-24+1, y);

    for (k=0;k<12;k++) {                                                             //12��ʾ�Խ����ֿ��еĸ�����ѭ����ѯ����
        if ((codeGB_24[k].Index[0]==c[0])&&(codeGB_24[k].Index[1]==c[1])){
            for(i=0;i<72;i++) {
                unsigned short m=codeGB_24[k].Msk[i];
                for(j=0;j<8;j++) {
                    if((m&0x80)==0x80) {
                        Write_Data_U16(fColor);
                    }
                    else {
                        Write_Data_U16(bColor);
                    }
                    m<<=1;
                }
            }
        }
    }
}

/****************************************************************************************************
//  ʵ�ֹ��ܣ�   ��ʾ��Ӣ���ַ���
//  ��������� x ������
//            y ������
//              *s ����ʾ���ַ���,����LCD_PutString(24,16,"123Eee",White,Blue);����"123Eee"�ĵ�һ���ַ���ַ����ָ�����s.
//              bColor �ַ�������ɫ
 ****************************************************************************************************/
void LCD_PutString(unsigned short x, unsigned short y, unsigned char *s, unsigned int fColor, unsigned int bColor)
{
    unsigned char l=0;                             //��ʾ��λ������
    unsigned short i,j;

    i=y;                                            //�����������任���������������Ҫ�任
    j=x;
    x=i;
    y=319-j;

    while(*s)
    {
        if( *s < 0x80)                                  //�ж�sָ����ַ����е�ĳ�ַ��ı���ֵ�Ƿ�С��128,���С��,��ΪASCII�ַ�
        {
            LCD_PutChar(x,y-l*8,*s,fColor,bColor);         //��ʾ���ַ�
            s++;l++;                                   //ָ���1,λ�ü�1
        }
        else
        {
            Put16x16(x,y-l*8,(unsigned char*)s,fColor,bColor);     //��ʾ�ú���
            s+=2;l+=2;                                         //��Ϊ����Ϊ����Ϊ2�ֽڣ�ָ���2,��ʾ16x16����λ�ü�2
        }
    }
}

/****************************************************************************************************
��������:��ʾ�ַ���24x24��С,������Ӣ��ͬʱ��ʾ
���������x ������
         y ������
 *s ��Ҫ��ʾ���ַ���
                 fColor �ַ���ɫ
         bColor �ַ�������ɫ
 ****************************************************************************************************/
void LCD_PutString24(unsigned short x , unsigned short y, unsigned char *s, unsigned int fColor, unsigned int bColor) {
    unsigned char l=0;
    unsigned short i,j;
    i=y;                                                                                                            //����任
    j=x;
    x=i;
    y=319-j;
    while(*s) {
        if( *s < 0x80)
        {
            LCD_PutChar(x,y-l*8,*s,fColor,bColor);
            s++;l++;
        }
        else
        {
            PutGB2424(x,y-l*12,(unsigned char*)s,fColor,bColor);
            s+=2;l+=2;
        }
    }
}

/****************************************************************************************************
//  ʵ�ֹ��ܣ�   ָ��λ����ʾRGB��ɫ
//  ��������� x0��y0 ��ʼ����
//            x1��y1 ��������
//              Color  ������ɫ
 ****************************************************************************************************/

void Show_RGB (unsigned short x0,unsigned short x1,unsigned short y0,unsigned short y1,unsigned int Color)
{
    unsigned int i,j;

    LCD_SetPos(y0,y1,319-x1,319-x0);//��������Ҫ��������任���������������ֱ����x0,x1,y0,y1������
    for (i=x0;i<=x1;i++)
    {
        for (j=y0;j<=y1;j++)
            Write_Data_U16(Color);
    }
}

/****************************************************************************************************
//  ʵ�ֹ��ܣ�   TFT��ʼ��
 ****************************************************************************************************/
void TFT_Initial(void)
{
    RST_SET;
    delayms(1);                             // Delay 1ms
    RST_CLR;
    delayms(10);                            // Delay 10ms
    RST_SET;
    delayms(50);                            // Delay 50 ms

    if(Device_code==0x9320)
    {

        //************* Start Initial Sequence **********//
        Write_Cmd_Data(0x00,0x0001);        //Set the OSC bit as ��1�� to start the internal oscillator
        Write_Cmd_Data(0x01,0x0100);      // set SS and SM bit
        Write_Cmd_Data(0x02,0x0700);        // set 1 line inversion
        Write_Cmd_Data(0x03,0x1098);        //set GRAM Write direction and BGR=1
        Write_Cmd_Data(0x04,0x0000);      // Resize register
        Write_Cmd_Data(0x08,0x0202);        // set the back porch and front porch
        Write_Cmd_Data(0x09,0x0000);      // set non-display area refresh cycle ISC[3:0]
        Write_Cmd_Data(0x0A,0x0000);      // FMARK function
        Write_Cmd_Data(0x0C,0x0000);      // RGB interface setting
        Write_Cmd_Data(0x0D,0x0000);        // Frame marker Position
        Write_Cmd_Data(0x0F,0x0000);      // RGB interface polarity
        delayms(30);
        //*************Power On sequence ****************//
        Write_Cmd_Data(0x10, 0x16b0);   // SAP, BT[3:0], AP, DSTB, SLP, STB
        delayms(30);
        Write_Cmd_Data(0x11, 0x0007);   //Write final user��s setting values to VC bit
        Write_Cmd_Data(0x12, 0x013a);   // set Internal reference voltage
        Write_Cmd_Data(0x13, 0x1a00);   // VDV[4:0] for VCOM amplitude
        delayms(30);
        Write_Cmd_Data(0x29, 0x000c);   // Set VCM[5:0] for VCOMH
        delayms(30); // Delay 50ms

        // ----------- Adjust the Gamma Curve ----------//
        Write_Cmd_Data(0x0030, 0x0000);
        Write_Cmd_Data(0x0031, 0x0505);
        Write_Cmd_Data(0x0032, 0x0304);
        Write_Cmd_Data(0x0035, 0x0006);
        Write_Cmd_Data(0x0036, 0x0707);
        Write_Cmd_Data(0x0037, 0x0105);
        Write_Cmd_Data(0x0038, 0x0002);
        Write_Cmd_Data(0x0039, 0x0707);
        Write_Cmd_Data(0x003C, 0x0704);
        Write_Cmd_Data(0x003D, 0x0807);

        //------------------ Set GRAM area ---------------//
        Write_Cmd_Data(0x0050, 0x0000); // Horizontal GRAM Start Address
        Write_Cmd_Data(0x0051, 0x00EF); // Horizontal GRAM End Address
        Write_Cmd_Data(0x0052, 0x0000); // Vertical GRAM Start Address
        Write_Cmd_Data(0x0053, 0x013F); // Vertical GRAM Start Address
        Write_Cmd_Data(0x0060, 0x2700); // Gate Scan Line
        Write_Cmd_Data(0x0061, 0x0001); // NDL,VLE, REV
        Write_Cmd_Data(0x006A, 0x0000); // set scrolling line
        Write_Cmd_Data(0x20, 0x0000);   // GRAM horizontal Address
        Write_Cmd_Data(0x21, 0x0000);   // GRAM Vertical Address

        //-------------- Partial Display Control ---------//
        Write_Cmd_Data(0x0080, 0x0000);
        Write_Cmd_Data(0x0081, 0x0000);
        Write_Cmd_Data(0x0082, 0x0000);
        Write_Cmd_Data(0x0083, 0x0000);
        Write_Cmd_Data(0x0084, 0x0000);
        Write_Cmd_Data(0x0085, 0x0000);

        //-------------- Panel Control ---------//
        Write_Cmd_Data(0x90,0x0010);   //Frame Cycle Contral
        Write_Cmd_Data(0x92,0x0000);   //Panel Interface Contral
        Write_Cmd_Data(0x93,0x0003);   //Panel Interface Contral 3.
        Write_Cmd_Data(0x95,0x0110);   //Frame Cycle Contral
        Write_Cmd_Data(0x97,0x0000);   //
        Write_Cmd_Data(0x98,0x0000);   //Frame Cycle Contral.

        //-------------- Display on ---------//
        Write_Cmd_Data(0x07,0x0173);

    }

    else if(Device_code==0x1505 )
    {

        //************* Start Initial Sequence **********//
        Write_Cmd_Data(0x00,0x0001);   //Set the OSC bit as ��1�� to start the internal oscillator
        Write_Cmd_Data(0x01,0x0100);   // set SS and SM bit
        Write_Cmd_Data(0x02,0x0700);   // set 1 line inversion
        Write_Cmd_Data(0x03,0x1030);   //set GRAM Write direction and BGR=1
        Write_Cmd_Data(0x04,0x0000);   // Resize register
        Write_Cmd_Data(0x08,0x0202);   // set the back porch and front porch
        Write_Cmd_Data(0x09,0x0000);   // set non-display area refresh cycle ISC[3:0]
        Write_Cmd_Data(0x0A,0x0000);   // FMARK function
        Write_Cmd_Data(0x0C,0x0000);   // RGB interface setting
        Write_Cmd_Data(0x0D,0x0000);   // Frame marker Position
        Write_Cmd_Data(0x0F,0x0000);   // RGB interface polarity
        delayms(30);
        //*************Power On sequence ****************//
        Write_Cmd_Data(0x10, 0x16b0);   // SAP, BT[3:0], AP, DSTB, SLP, STB
        delayms(30);
        Write_Cmd_Data(0x11, 0x0007);   //Write final user��s setting values to VC bit
        Write_Cmd_Data(0x12, 0x013a);   // set Internal reference voltage
        Write_Cmd_Data(0x13, 0x1a00);   // VDV[4:0] for VCOM amplitude
        delayms(30);
        Write_Cmd_Data(0x29, 0x000c);   // Set VCM[5:0] for VCOMH
        delayms(30); // Delay 50ms

        // ----------- Adjust the Gamma Curve ----------//
        Write_Cmd_Data(0x0030, 0x0000);
        Write_Cmd_Data(0x0031, 0x0505);
        Write_Cmd_Data(0x0032, 0x0304);
        Write_Cmd_Data(0x0035, 0x0006);
        Write_Cmd_Data(0x0036, 0x0707);
        Write_Cmd_Data(0x0037, 0x0105);
        Write_Cmd_Data(0x0038, 0x0002);
        Write_Cmd_Data(0x0039, 0x0707);
        Write_Cmd_Data(0x003C, 0x0704);
        Write_Cmd_Data(0x003D, 0x0807);

        //------------------ Set GRAM area ---------------//
        Write_Cmd_Data(0x0050, 0x0000); // Horizontal GRAM Start Address
        Write_Cmd_Data(0x0051, 0x00EF); // Horizontal GRAM End Address
        Write_Cmd_Data(0x0052, 0x0000); // Vertical GRAM Start Address
        Write_Cmd_Data(0x0053, 0x013F); // Vertical GRAM Start Address
        Write_Cmd_Data(0x0060, 0x2700); // Gate Scan Line
        Write_Cmd_Data(0x0061, 0x0001); // NDL,VLE, REV
        Write_Cmd_Data(0x006A, 0x2700); // set scrolling line
        Write_Cmd_Data(0x20, 0x0000);   // GRAM horizontal Address
        Write_Cmd_Data(0x21, 0x0000);   // GRAM Vertical Address

        //-------------- Partial Display Control ---------//
        Write_Cmd_Data(0x0080, 0x0000);
        Write_Cmd_Data(0x0081, 0x0000);
        Write_Cmd_Data(0x0082, 0x0000);
        Write_Cmd_Data(0x0083, 0x0000);
        Write_Cmd_Data(0x0084, 0x0000);
        Write_Cmd_Data(0x0085, 0x0000);

        //-------------- Panel Control ---------//
        Write_Cmd_Data(0x90,0x0010);   //Frame Cycle Contral
        Write_Cmd_Data(0x92,0x0000);   //Panel Interface Contral
        Write_Cmd_Data(0x93,0x0003);   //Panel Interface Contral 3.
        Write_Cmd_Data(0x95,0x0110);   //Frame Cycle Contral
        Write_Cmd_Data(0x97,0x0000);   //
        Write_Cmd_Data(0x98,0x0000);   //Frame Cycle Contral.

        //-------------- Display on ---------//
        Write_Cmd_Data(0x07,0x0173);

    }

    else if(Device_code==0x9328)
    {

        //************* Start Initial Sequence **********//
        Write_Cmd_Data(0x0001,0x0100);   //set SS and SM bit //����ɨ�跽��  100
        Write_Cmd_Data(0x0002,0x0700);   //EOR=1 and B/C=1 to set the line inversion  //�����з�ת
        Write_Cmd_Data(0x0003,0x1098);   //set Entry Mode  //���ý���ģʽ    1030
        Write_Cmd_Data(0x0004,0x0000);   //
        Write_Cmd_Data(0x00A4,0x0001);
        Write_Cmd_Data(0x0008,0x0202); // set the back porch and front porch
        Write_Cmd_Data(0x0009,0x0000); // set non-display area refresh cycle ISC[3:0]
        Write_Cmd_Data(0x000A,0x0000); // FMARK function
        Write_Cmd_Data(0x000C,0x0000); // RGB interface setting
        Write_Cmd_Data(0x000D, 0x0000); // Frame marker Position
        Write_Cmd_Data(0x000F, 0x0000); // RGB interface polarity



        //*************Power On sequence ****************//
        Write_Cmd_Data(0x0010, 0x0000); // SAP, BT[3:0], AP, DSTB, SLP, STB
        Write_Cmd_Data(0x0011, 0x0007); // DC1[2:0], DC0[2:0], VC[2:0]
        Write_Cmd_Data(0x0012, 0x0000); // VREG1OUT voltage
        Write_Cmd_Data(0x0013, 0x0000); // VDV[4:0] for VCOM amplitude
        delayms(30);
        Write_Cmd_Data(0x0010, 0x1690); // SAP, BT[3:0], AP, DSTB, SLP, STB
        Write_Cmd_Data(0x0011, 0x0227); // R11h=0x0221 at VCI=3.3V, DC1[2:0], DC0[2:0], VC[2:0]
        delayms(30);
        Write_Cmd_Data(0x0012, 0x001C); // External reference voltage= Vci;
        delayms(30);
        Write_Cmd_Data(0x0013, 0x1800); // R13=1200 when R12=009D;VDV[4:0] for VCOM amplitude
        Write_Cmd_Data(0x0029, 0x001C); // R29=000C when R12=009D;VCM[5:0] for VCOMH
        Write_Cmd_Data(0x002B, 0x000D); // Frame Rate = 91Hz
        delayms(30);
        Write_Cmd_Data(0x0020, 0x0000); // GRAM horizontal Address
        Write_Cmd_Data(0x0021, 0x0000); // GRAM Vertical Address
        // ----------- Adjust the Gamma Curve ----------//
        Write_Cmd_Data(0x0030, 0x0007);
        Write_Cmd_Data(0x0031, 0x0302);
        Write_Cmd_Data(0x0032, 0x0105);
        Write_Cmd_Data(0x0035, 0x0206);
        Write_Cmd_Data(0x0036, 0x0808);
        Write_Cmd_Data(0x0037, 0x0206);
        Write_Cmd_Data(0x0038, 0x0504);
        Write_Cmd_Data(0x0039, 0x0007);
        Write_Cmd_Data(0x003C, 0x0105);
        Write_Cmd_Data(0x003D, 0x0808);
        //------------------ Set GRAM area ---------------//
        Write_Cmd_Data(0x0050, 0x0000); // Horizontal GRAM Start Address
        Write_Cmd_Data(0x0051, 0x00EF); // Horizontal GRAM End Address
        Write_Cmd_Data(0x0052, 0x0000); // Vertical GRAM Start Address
        delayms(30);
        Write_Cmd_Data(0x0053, 0x013F); // Vertical GRAM End Address
        delayms(30);
        Write_Cmd_Data(0x0060, 0xA700); // Gate Scan Line
        Write_Cmd_Data(0x0061, 0x0001); // NDL,VLE, REV
        Write_Cmd_Data(0x006A, 0x0000); // set scrolling line
        //-------------- Partial Display Control ---------//
        Write_Cmd_Data(0x0080, 0x0000);
        Write_Cmd_Data(0x0081, 0x0000);
        Write_Cmd_Data(0x0082,0x0000);
        Write_Cmd_Data(0x0083,0x0000);
        Write_Cmd_Data(0x0084,0x0000);
        Write_Cmd_Data(0x0085,0x0000);
        //-------------- Panel Control -------------------//
        Write_Cmd_Data(0x0090, 0x0010);
        Write_Cmd_Data(0x0092, 0x0000);
        Write_Cmd_Data(0x0093, 0x0003);
        Write_Cmd_Data(0x0095, 0x0110);
        Write_Cmd_Data(0x0097, 0x0000);
        Write_Cmd_Data(0x0098, 0x0000);
        Write_Cmd_Data(0x0007, 0x0133); // 262K color and display ON

    }
}

/****************************************************************************************************
//  ʵ�ֹ��ܣ�   ����
//  ��������� x��y ��Ҫ��������
//            color �����ɫ
 ****************************************************************************************************/
void Put_pixel(unsigned int x,unsigned int y,unsigned int color)
{
    LCD_SetPos(y,y,319-x,319-x);                                                //��������Ҫ��������任���������������ֱ����x0,x1,y0,y1������

    Write_Data_U16(color);                                                      //��ָ����д����ɫ����
}
