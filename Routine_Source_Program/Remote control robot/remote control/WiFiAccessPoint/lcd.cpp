/*
BILIBILI:技术宅物语
*/
#include "lcd.h"
#include "lcdfont.h"


//u16 lcdCanvas[LCD_H][LCD_W]={0};//����

/******************************************************************************
      ����˵������ָ�����������ɫ
      ������ݣ�xsta,ysta   ��ʼ����
                xend,yend   ��ֹ����
								color       Ҫ������ɫ
      ����ֵ��  ��
******************************************************************************/
void LCD_Fill(u16 xsta,u16 ysta,u16 xend,u16 yend,u16 color)
{          
	u16 i,j; 
	/*if((xsta<LCD_W)&&(ysta<LCD_H)&&(xend<LCD_W)&&(yend<LCD_H))
	{
		for(i=ysta;i<=yend;i++)
		{													   	 	
			for(j=xsta;j<=xend;j++)
			{
				lcdCanvas[i][j]=(color<<8)|(color>>8);
			}
		} 
	}	*/
  LCD_Address_Set(xsta,ysta,xend-1,yend-1);//设置显示范围
  for(i=ysta;i<yend;i++)
  {                               
    for(j=xsta;j<xend;j++)
    {
      LCD_WR_DATA(color);
    }
  }           						  	    
}

/******************************************************************************
      ����˵������ָ��λ�û���
      ������ݣ�x,y ��������
                color �����ɫ
      ����ֵ��  ��
******************************************************************************/
void LCD_DrawPoint(u16 x,u16 y,u16 color)
{
	/*if((x<LCD_W)&&(y<LCD_H))
	{
		lcdCanvas[y][x]=(color<<8)|(color>>8);
	}*/
  LCD_Address_Set(x,y,x,y);//设置光标位置 
  LCD_WR_DATA(color);
} 


/******************************************************************************
      ����˵��������
      ������ݣ�x1,y1   ��ʼ����
                x2,y2   ��ֹ����
                color   �ߵ���ɫ
      ����ֵ��  ��
******************************************************************************/
void LCD_DrawLine(u16 x1,u16 y1,u16 x2,u16 y2,u16 color)
{
	u16 t; 
	int xerr=0,yerr=0,delta_x,delta_y,distance;
	int incx,incy,uRow,uCol;
	delta_x=x2-x1; //������������ 
	delta_y=y2-y1;
	uRow=x1;//�����������
	uCol=y1;
	if(delta_x>0)incx=1; //���õ������� 
	else if (delta_x==0)incx=0;//��ֱ�� 
	else {incx=-1;delta_x=-delta_x;}
	if(delta_y>0)incy=1;
	else if (delta_y==0)incy=0;//ˮƽ�� 
	else {incy=-1;delta_y=-delta_x;}
	if(delta_x>delta_y)distance=delta_x; //ѡȡ�������������� 
	else distance=delta_y;
	for(t=0;t<distance+1;t++)
	{
		LCD_DrawPoint(uRow,uCol,color);//����
		xerr+=delta_x;
		yerr+=delta_y;
		if(xerr>distance)
		{
			xerr-=distance;
			uRow+=incx;
		}
		if(yerr>distance)
		{
			yerr-=distance;
			uCol+=incy;
		}
	}
}


/******************************************************************************
      ����˵����������
      ������ݣ�x1,y1   ��ʼ����
                x2,y2   ��ֹ����
                color   ���ε���ɫ
      ����ֵ��  ��
******************************************************************************/
void LCD_DrawRectangle(u16 x1, u16 y1, u16 x2, u16 y2,u16 color)
{
	LCD_DrawLine(x1,y1,x2,y1,color);
	LCD_DrawLine(x1,y1,x1,y2,color);
	LCD_DrawLine(x1,y2,x2,y2,color);
	LCD_DrawLine(x2,y1,x2,y2,color);
}


/******************************************************************************
      ����˵������Բ
      ������ݣ�x0,y0   Բ������
                r       �뾶
                color   Բ����ɫ
      ����ֵ��  ��
******************************************************************************/
void Draw_Circle(u16 x0,u16 y0,u8 r,u16 color)
{
	int a,b;
	a=0;b=r;	  
	while(a<=b)
	{
		LCD_DrawPoint(x0-b,y0-a,color);             //3           
		LCD_DrawPoint(x0+b,y0-a,color);             //0           
		LCD_DrawPoint(x0-a,y0+b,color);             //1                
		LCD_DrawPoint(x0-a,y0-b,color);             //2             
		LCD_DrawPoint(x0+b,y0+a,color);             //4               
		LCD_DrawPoint(x0+a,y0-b,color);             //5
		LCD_DrawPoint(x0+a,y0+b,color);             //6 
		LCD_DrawPoint(x0-b,y0+a,color);             //7
		a++;
		if((a*a+b*b)>(r*r))//�ж�Ҫ���ĵ��Ƿ��Զ
		{
			b--;
		}
	}
}

/******************************************************************************
      ����˵������ʾ�����ַ�
      ������ݣ�x,y��ʾ����
                num Ҫ��ʾ���ַ�
                fc �ֵ���ɫ
                bc �ֵı���ɫ
                sizey �ֺ�
      ����ֵ��  ��
******************************************************************************/
void LCD_ShowChar(u16 x,u16 y,char num1,u16 fc,u16 bc,u8 sizey)
{
	u8 temp,sizex,t,num=(u8)num1;
	u16 i,TypefaceNum;//һ���ַ���ռ�ֽڴ�С
	u16 x0=x;
	sizex=sizey/2;
	TypefaceNum=sizex/8*sizey;
	num=num-' ';    //�õ�ƫ�ƺ��ֵ
	for(i=0;i<TypefaceNum;i++)
	{ 
		if(sizey==16)temp=ascii_1608[num][i];		       //����8x16����
		else if(sizey==32)temp=ascii_3216[num][i];		 //����16x32����
		else return;
		for(t=0;t<8;t++)
		{
			if(temp&(0x01<<t))
				LCD_DrawPoint(x,y,fc);//��һ����
			else 
				LCD_DrawPoint(x,y,bc);//��һ����
			x++;
			if((x-x0)==sizex)
			{
				x=x0;
				y++;
				break;
			}
		}
	}   	 	  
}


/******************************************************************************
      ����˵������ʾ�ַ���
      ������ݣ�x,y��ʾ����
                *p Ҫ��ʾ���ַ���
                fc �ֵ���ɫ
                bc �ֵı���ɫ
                sizey �ֺ�
                mode:  0�ǵ���ģʽ  1����ģʽ
      ����ֵ��  ��
******************************************************************************/
void LCD_ShowString(u16 x,u16 y,char *p,u16 fc,u16 bc,u8 sizey)
{         
	while(*p!='\0')
	{       
		LCD_ShowChar(x,y,*p,fc,bc,sizey);
		x+=sizey/2;
		p++;
	}  
}


/******************************************************************************
      ����˵������ʾ����
      ������ݣ�m������nָ��
      ����ֵ��  ��
******************************************************************************/
u32 mypow(u8 m,u8 n)
{
	u32 result=1;	 
	while(n--)result*=m;
	return result;
}


/******************************************************************************
      ����˵������ʾ��������
      ������ݣ�x,y��ʾ����
                num Ҫ��ʾ��������
                len Ҫ��ʾ��λ��
                fc �ֵ���ɫ
                bc �ֵı���ɫ
                sizey �ֺ�
      ����ֵ��  ��
******************************************************************************/
void LCD_ShowIntNum(u16 x,u16 y,u16 num,u8 len,u16 fc,u16 bc,u8 sizey)
{         	
	char temp;
	u8 t,enshow=0;
	u8 sizex=sizey/2;
	for(t=0;t<len;t++)
	{
		temp=(char)(num/mypow(10,len-t-1))%10;
		if(enshow==0&&t<(len-1))
		{
			if(temp==0)
			{
				LCD_ShowChar(x+t*sizex,y,' ',fc,bc,sizey);
				continue;
			}else enshow=1; 
		 	 
		}
	 	LCD_ShowChar(x+t*sizex,y,temp+48,fc,bc,sizey);
	}
} 


/******************************************************************************
      ����˵������ʾ��λС������
      ������ݣ�x,y��ʾ����
                num Ҫ��ʾС������
                len Ҫ��ʾ��λ��
                fc �ֵ���ɫ
                bc �ֵı���ɫ
                sizey �ֺ�
      ����ֵ��  ��
******************************************************************************/
void LCD_ShowFloatNum1(u16 x,u16 y,float num,u8 len,u16 fc,u16 bc,u8 sizey)
{        
	char temp; 	
	u8 t,sizex;
	u16 num1;
	sizex=sizey/2;
	num1=num*100;
	for(t=0;t<len;t++)
	{
		temp=(char)(num1/mypow(10,len-t-1))%10;
		if(t==(len-2))
		{
			LCD_ShowChar(x+(len-2)*sizex,y,'.',fc,bc,sizey);
			t++;
			len+=1;
		}
	 	LCD_ShowChar(x+t*sizex,y,temp+48,fc,bc,sizey);
	}
}

/******************************************************************************
      ����˵������ʾ����16x16����
      ������ݣ�x,y��ʾ����
                *s Ҫ��ʾ�ĺ���
                fc �ֵ���ɫ
                bc �ֵı���ɫ
                sizey �ֺ�
                mode:  0�ǵ���ģʽ  1����ģʽ
      ����ֵ��  ��
******************************************************************************/
void LCD_ShowChinese16x16(u16 x,u16 y,char *s,u16 fc,u16 bc,u8 len)
{
	u8 l,n,m,x1,y1;
	char *p = s;

	for(l=0;l<len;l++)
	{
		y1=y;
		for(m=0;m<16;m++)
		{
			y1=y+m;
			x1=x+l*16;
			for(n=0;n<8;n++)
			{
				if((*p<<n)&0x80)
					LCD_DrawPoint(x1+n,y1,fc);//��һ����
				else
					LCD_DrawPoint(x1+n,y1,bc);//��һ����
			}
			x1+=n;
			p++;
			for(n=0;n<8;n++)
			{
				if((*p<<n)&0x80)
					LCD_DrawPoint(x1+n,y1,fc);//��һ����
				else
					LCD_DrawPoint(x1+n,y1,bc);//��һ����
			}
			p++;
		}
	}
} 


/******************************************************************************
      ����˵������ʾ����24x24����
      ������ݣ�x,y��ʾ����
                *s Ҫ��ʾ�ĺ���
                fc �ֵ���ɫ
                bc �ֵı���ɫ
                sizey �ֺ�
                mode:  0�ǵ���ģʽ  1����ģʽ
      ����ֵ��  ��
******************************************************************************/
void LCD_ShowChinese24x24(u16 x,u16 y,char *s,u16 fc,u16 bc,u8 len)
{
	u8 l,n,m,x1,y1;
	char *p = s;

	for(l=0;l<len;l++)
	{
		y1=y;
		for(m=0;m<24;m++)
		{
			y1=y+m;
			x1=x+l*24;
			for(n=0;n<8;n++)
			{
				if((*p<<n)&0x80)
					LCD_DrawPoint(x1+n,y1,fc);//��һ����
				else
					LCD_DrawPoint(x1+n,y1,bc);//��һ����
			}
			x1+=n;
			p++;
			for(n=0;n<8;n++)
			{
				if((*p<<n)&0x80)
					LCD_DrawPoint(x1+n,y1,fc);//��һ����
				else
					LCD_DrawPoint(x1+n,y1,bc);//��һ����
			}
			x1+=n;
			p++;
			for(n=0;n<8;n++)
			{
				if((*p<<n)&0x80)
					LCD_DrawPoint(x1+n,y1,fc);//��һ����
				else
					LCD_DrawPoint(x1+n,y1,bc);//��һ����
			}
			p++;
		}
	}
} 

/******************************************************************************
      ����˵������ʾͼƬ
      ������ݣ�x,y�������
                length ͼƬ����
                width  ͼƬ���
                pic[]  ͼƬ����    
      ����ֵ��  ��
******************************************************************************/
void LCD_ShowPicture(u16 x,u16 y,u16 length,u16 width,const u8 pic[])
{
	u16 i,j,k=0;
	LCD_Address_Set(x,y,x+length,y+width);
	for(i=0;i<length;i++)
	{
		for(j=0;j<width;j++)
		{
			LCD_WR_DATA8(pic[k*2]);
			LCD_WR_DATA8(pic[k*2+1]);
			//lcdCanvas[i][j] = ((uint16_t)pic[k*2+1]<<8)+pic[k*2];
			k++;
		}
	}

}

//RGB��ɫת��
u16 RGB(u32 color)
{
	u8 r,g,b;
	u16 rgb565;
	r = (color&0x00ff0000)>>16;
	g = (color&0x0000ff00)>>8;
	b = color&0x000000ff;
	rgb565 = (r&0xf8)<<8;
	rgb565 |= (g&0xfc)<<3;
	rgb565 |= (b&0xf8)>>3;
	return rgb565;
}
