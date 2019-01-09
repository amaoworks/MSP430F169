/*===================================================================================================
�ļ�����������320x240TFT�������򣬿���TFTʵ�ֺ���,�ַ���ʾ,���㹦�ܡ�
====================================================================================================*/

//**************�����ⲿ�����ͱ���**************
#include "TFT2.8.h"
extern unsigned int Device_code;

//================================================================================================
//  ʵ�ֹ��ܣ�   ��ʱ
//  ���������   count ������ʱʱ��
//================================================================================================
void delayms(unsigned int count)
{
    int i,j;
    for(i=0;i<count;i++)
       {
         for(j=0;j<255;j++);
       }
}

//================================================================================================
//  ʵ�ֹ��ܣ�   д����
//  ���������  DH ��Ҫ����16bits����ĸ�8λ
//              DL ��Ҫ����16bits����ĵ�8λ
//================================================================================================
void Write_Cmd(unsigned char DH,unsigned char DL)
{
    CS_CLR;
    RS_CLR;
        RD_SET;
        RW_CLR;

    //ע�⣺��ʹ��8λ���ݿ�����16λ����ģʽʱ��ʹ��74HC573��ΪIO��չ����������
    DataPort=DH;              //�͸�8λ�����573������
    LE_SET;                   //����λ
    LE_CLR;                   //�Ͽ�����,λѡ573��Q7~Q0�Ա���

    DataPort=DL;          //�͵�8λ�����TFT

    /*
    //���ʹ��16λ���ݿ�����16λ����ģʽ��������IO��չ��ֱ�ӽ������͵����ݿڼ���
    DataPort_L=DL;
    DataPort_H=DH;
    */

    RW_SET;
    CS_SET;
}

//================================================================================================
//  ʵ�ֹ��ܣ�   д����(2*8bits)
//  ���������  DH ��Ҫ����16bits���ݵĸ�8λ
//              DL ��Ҫ����16bits���ݵĵ�8λ
//================================================================================================
void Write_Data(unsigned char DH,unsigned char DL)
{

    CS_CLR;
    RS_SET;

    //ע�⣺��ʹ��8λ���ݿ�����16λ����ģʽʱ��ʹ��74HC573��ΪIO��չ����������
    DataPort=DH;            //�͸�8λ���ݸ�573������
    LE_SET;                   //����λ
    LE_CLR;                   //�Ͽ�����,λѡ573��Q7~Q0�Ա���

    DataPort=DL;            //�͵�8λ���ݸ�TFT

    /*
    //���ʹ��16λ���ݿ�����16λ����ģʽ��������IO��չ��ֱ�ӽ������͵����ݿڼ���
    DataPort_L=DL;
    DataPort_H=DH;
    */

    RW_CLR;
    RW_SET;
    CS_SET;
}

//================================================================================================
//  ʵ�ֹ��ܣ�   д����(16λ)
//  ���������  y ��Ҫ����16bits����
//================================================================================================
void  Write_Data_U16(unsigned int y)
{
    unsigned char m,n;
    m=y>>8;
    n=y;
    Write_Data(m,n);
}

//================================================================================================
//  ʵ�ֹ��ܣ�   ��x�Ĵ���д��y����
//  ���������  x ��Ҫ��������� 16λ
//              y ��Ҫ��������� 16λ
//================================================================================================
void  Write_Cmd_Data (unsigned char x,unsigned int y)
{
    unsigned char m,n;
    m=y>>8;
    n=y;
    Write_Cmd(0x00,x);
    Write_Data(m,n);
}

//================================================================================================
//  ʵ�ֹ��ܣ�   TFT����
//  ���������   bColor ������ʹ�õı���ɫ
//================================================================================================
void CLR_Screen(unsigned int bColor)
{
 unsigned int i,j;
 LCD_SetPos(0,240,0,320);//320x240
 for (i=0;i<320;i++)
    {
       for (j=0;j<240;j++)
           Write_Data_U16(bColor);
    }
}

//================================================================================================
//  ʵ�ֹ��ܣ�   ��ʾAscii�ַ�
//  ���������  x ������
//              y ������
//              c ��Ҫ��ʾ���ַ�
//              fColor �ַ���ɫ
//              bColor �ַ�������ɫ
//================================================================================================

void Show_Image(unsigned int x0,unsigned int x1,unsigned int y0,unsigned int y1,const unsigned char *gImage)
{
    unsigned int i,j;
    LCD_SetPos(x0,x1-1,y0,y1-1);      //������ʾλ��
    for (i=y0-y0;i<y1-y0;i++)         //��ʼλ��Ӧ�ô�0��ʼ��������ȡ����
    {
       for (j=x0-x0;j<x1-x0;j++)      //��ʼλ��Ӧ�ô�0��ʼ��������ȡ����
        //С�����ݸ�ʽ����pgm_read_byte������FLASH�ж�ȡͼ�����ݣ�ͼ��������Image2LCD�����ȡ��16λ��ɫ
        Write_Data(gImage[i*(x1-x0)*2+j*2+1],gImage[i*(x1-x0)*2+j*2]);//ע���㷨
    }
}

//#include "Ascii_8x16.h"
void LCD_PutChar(unsigned short x, unsigned short y, char c, unsigned int fColor, unsigned int bColor)
{
 unsigned int i,j;
 LCD_SetPos(x,x+8-1,y,y+16-1);                    //�����ַ���ʾλ��
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

//================================================================================================
//  ʵ�ֹ��ܣ�   ��ʾ16x16����
//  ���������  x ������
//              y ������
//              g ��Ҫ��ʾ���ַ�����
//              fColor �ַ���ɫ
//              bColor �ַ�������ɫ
//================================================================================================

void Put16x16(unsigned short x, unsigned short  y, unsigned char g[2], unsigned int fColor,unsigned int bColor)
{
    unsigned int i,j,k;
    LCD_SetPos(x,  x+16-1,y, y+16-1);                       //���ú�����ʾλ��
    for (k=0;k<64;k++)                                      //ѭ��64�Σ���ѯ������ģλ��
    {
      if ((ch16[k].GBK[0]==g[0])&&(ch16[k].GBK[1]==g[1]))   //�жϵ�k�����ֵı����Ƿ������뺺��g[2]���
      {
        for(i=0;i<32;i++)                                   //�����ȣ������ҵ�����ʾ��ģλ�ã�ѭ��д��32�ֽ�
        {
          unsigned short m=ch16[k].hz16[i];                 //��ȡ32�ֽ��еĵ�i�ֽ�
          for(j=0;j<8;j++)                                  //ѭ��д��8λ����
           {
             if((m&0x80)==0x80) Write_Data_U16(fColor);     //�ж����λ�Ƿ�Ϊ1,���λΪ1��д���ַ���ɫ
             else              Write_Data_U16(bColor);      //���λΪ0��д�뱳����ɫ
             m<<=1;                                         //����1λ��׼��д��һλ
           }
        }
      break;}
    }
}

/**********************************************************************
��������: ��ʾ����24x24
���������x ������
          y ������
          c ��Ҫ��ʾ�ĺ�����
      fColor �ַ���ɫ
          bColor �ַ�������ɫ
***********************************************************************/
void PutGB2424(unsigned short x, unsigned short  y, unsigned char c[2], unsigned int fColor,unsigned int bColor)
{
    unsigned int i,j,k;
    LCD_SetPos(x,x+24-1,y, y+24-1);
    for (k=0;k<128;k++) { //64��ʾ�Խ����ֿ��еĸ�����ѭ����ѯ����
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
        break;}
      }
}

//================================================================================================
//  ʵ�ֹ��ܣ�   ��ʾ��Ӣ���ַ���
//  ���������  x ������
//              y ������
//              *s ����ʾ���ַ���,����LCD_PutString(24,16,"123��о",White,Blue);����"123��о"�ĵ�һ���ַ���ַ����ָ�����s.
//              bColor �ַ�������ɫ
//================================================================================================
void LCD_PutString(unsigned short x, unsigned short y, unsigned char *s, unsigned int fColor, unsigned int bColor)
{
     unsigned char l=0;                            //��ʾ��λ������
     while(*s)
     {
        if( *s < 0x80)                             //�ж�sָ����ַ����е�ĳ�ַ��ı���ֵ�Ƿ�С��128,���С��,��ΪASCII�ַ�
            {
             LCD_PutChar(x+l*8,y,*s,fColor,bColor);//��ʾ���ַ�
             s++;l++;                              //ָ���1,λ�ü�1

            }
        else
            {
             Put16x16(x+l*8,y,(unsigned char*)s,fColor,bColor);//��ʾ�ú���
             s+=2;l+=2;                                        //��Ϊ����Ϊ����Ϊ2�ֽڣ�ָ���2,��ʾ16x16����λ�ü�2
            }
     }
}

/**********************************************************************
��������:��ʾ�ַ���,������Ӣ��ͬʱ��ʾ
���������x ������
          y ������
         *s ��Ҫ��ʾ���ַ���
      fColor �ַ���ɫ
          bColor �ַ�������ɫ
***********************************************************************/
void LCD_PutString24(unsigned short x, unsigned short y, unsigned char *s, unsigned int fColor, unsigned int bColor) {
     unsigned char l=0,pos;
     pos=x;
    while(*s) {
        if( *s < 0x80)
            {
            LCD_PutChar(x,y,*s,fColor,bColor);
            s++;l++;
            x=l*8+pos;
            }
        else
            {
            PutGB2424(x,y,(unsigned char*)s,fColor,bColor);
            s+=2;l+=3;
            x=l*8+pos;
            }

        }
    }

//================================================================================================
//  ʵ�ֹ��ܣ�   ָ��λ����ʾRGB��ɫ
//  ���������  x0��y0 ��ʼ����
//              x1��y1 ��������
//              Color  ������ɫ
//================================================================================================

void Show_RGB (unsigned int x0,unsigned int x1,unsigned int y0,unsigned int y1,unsigned int Color)
{
    unsigned int i,j;
    LCD_SetPos(x0,x1,y0,y1);      //������ʾλ��
    for (i=y0;i<=y1;i++)
    {
       for (j=x0;j<=x1;j++)
           Write_Data_U16(Color);
    }
}

//================================================================================================
//  ʵ�ֹ��ܣ�   TFT��ʼ��
//================================================================================================
void TFT_Initial(void)
{

    RST_SET;
    delay_ms(1);                    // Delay 1ms
    RST_CLR;
    delay_ms(10);                   // Delay 10ms
    RST_SET;
    delay_ms(50);                   // Delay 50 ms

    if(Device_code==0x9320)
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
     Write_Cmd_Data(0x0001,0x0100);   //set SS and SM bit //����ɨ�跽��
    Write_Cmd_Data(0x0002,0x0700);   //EOR=1 and B/C=1 to set the line inversion  //�����з�ת
    Write_Cmd_Data(0x0003,0x1030);   //set Entry Mode  //���ý���ģʽ
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
    Write_Cmd_Data(0x0053, 0x013F); // Vertical GRAM Start Address
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

//================================================================================================
//  ʵ�ֹ��ܣ�   ��������
//  ���������  x0��y0 ��ʼ����
//              x1��y1 ��������
//================================================================================================
void LCD_SetPos(unsigned int x0,unsigned int x1,unsigned int y0,unsigned int y1)
{

  Write_Cmd_Data(0x50,x0);  // Horizontal GRAM Start Address
  Write_Cmd_Data(0x51,x1);  // Horizontal GRAM End Address
  Write_Cmd_Data(0x52,y0);  // Vertical GRAM Start Address
  Write_Cmd_Data(0x53,y1);  // Vertical GRAM Start Address
  Write_Cmd_Data(0x20,x0);  // GRAM horizontal Address
  Write_Cmd_Data(0x21,y0);  // GRAM Vertical Address
  Write_Cmd (0x00,0x22);    // 0x0022,Start to Write Data to GRAM
}
//================================================================================================
//  ʵ�ֹ��ܣ�   ����
//  ���������  x��y ��Ҫ��������
//              color �����ɫ
//================================================================================================
void Put_pixel(unsigned int x,unsigned int y,unsigned int color)
{
    LCD_SetPos(x,x,y,y);        //���ô���������
    Write_Data_U16(color);      //��ָ����д����ɫ����
}



