#include "IR.h"

//红外用全局变量
uchar bitnum;	 //红外解码位计数变量

bit startflag;
bit irreceok;
bit irprosok;
uchar irdata[33];
uchar ircode[4];
/**红外解码处理函数*/
void IR_pros(void)
{
    //下面是解码了用户码和操作码,如果加上用户码判别,可以杜绝不同遥控器的干扰
	uchar i,j,k,value;
	k=1;
    for(i=0;i<4;i++)            //四个字节
    {
        for(j=1;j<=8;j++)        //每个字节中的八位
        {
            if(irdata[k]>14)      
            {
               	   value=value|0x80;//或上0x80 就为1	
            }
            else                                   
            {
                  
				  value=value;	   //否则就为0
            }
			if(j<8)
		    {
				value=value>>1;	    //8为数据移位
		    }
	   	    k++;		  //位数加1
        }    
        ircode[i]=value;                              //把处理完的字节放到irdate_pro里
    	value=0;
    }
	if(ircode[2]==~ircode[3]&&ircode[0]==~ircode[1]&&ircode[0]==0x00) //加入用户码判断
	irprosok=1;

/*	
//下面的只解码了用户码,所用的时间最短,但容易受到其他遥控器的干扰	
	uchar  j, k,value;
	k=17;                      //从第17位数据开始是我们需要的8位数据码
	for(j=1;j<=8;j++)      //只需处理第3个字节8位(数据码)
    {
		//cord=irdata[k];   //解码的关键是如何识别“0”和“1”，从位的定义我们可以发现“0”、“1”均以0.56ms的低电平开始，不同的是高电平的宽度不同，“0”为0.56ms,“1”为1.68ms
	    if(irdata[k]>7)     //大于某值为1	 这里也可以算一下 125*14=1.75ms   我们从原理中知道1”为1.68ms的时间长度
	    {
	    	value=value|0x80;//或上0x80 就为1	
		}
	  	else
		{
	     	value=value;	   //否则就为0
		}
	  	if(j<8)
		{
			value=value>>1;	    //8为数据移位
		}
	   	k++;		  //位数加1
     }
 	 ircode[2]=value;  //8位数据码接受完成
     value=0;    	   //变量清0
	 irprosok=1;//处理完毕标志位置1
	 */
}

/*********************************
定时器1方式0(16位自动重装载模式)定时时间为255us
(此时的晶振是22.1184M的)算一下255*33=8.415ms跟9ms差不多接近就可以了
 255*63=16.056ms 所以小于13.5<16.056 这些数据大概就可以了 没必要那么精确 但也不能太离谱
所以有了这样判断if(irtime<63&&irtime>=33) 
**********************************/
void INT1_IR (void) interrupt 2 using 0//外部中断1服务函数
{
	if(startflag)                        
    {
        if(irtime<132&&irtime>=65)	//125US
		//if(irtime<63&&irtime>=33)  //255US      //若成功接受引导码  125*108=13500us
        {                                
            bitnum=0;
        }
        irdata[bitnum]=irtime;   //把红外数据存到irdate里，第一个为引导码，后边依次为系统码及数据码
        irtime=0;
        bitnum++;
		if(bitnum==33)            //接受数据完毕
        {
            irreceok=1;       //接受完成标志位置1
            bitnum=0;
            startflag=0;      //开始接收标志位置0
        }
              
    }
    else                      //若第一个下降沿到来，则置开始接收标志位，同时bittime清零
    {
        irtime=0;
        startflag=1;
    } 
}