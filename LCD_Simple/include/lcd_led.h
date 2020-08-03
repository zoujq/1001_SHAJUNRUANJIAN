#ifndef LCD_LED_H
#define LCD_LED_H
//LXCON定义
#define LEN(N)		(N<<5) 	//N=0~6
#define LMOD(N)		(N<<4)	//N=0~1


//LXCFG定义
#define DMOD(N)		(N<<6)
#define BIAS(N)		(N<<4)

#define LDRV(N)		(N) //N=0-7

#define COMHV(N)	(N<<5)	//N=0~1
#define SEGHV(N)	(N<<4)	//N=0~1
#define BLNK(N)		(N<<3)	//N=0~1

enum 
{
  LEN_DISABLE	= 0,
  LEN_IRCL  	= 1,
  LEN_IRCH  	= 2,
  LEN_XOSCL  	= 3,
  LEN_PLL  		= 5,
  LEN_TF  		= 6,
};

enum 
{
  LMOD_lcd	= 0,
  LMOD_led  = 1,
};

enum 
{
  DMOD_5ua		= 0,
  DMOD_40ua  	= 1,
	DMOD_80ua 	= 2,
	DMOD_130ua 	= 3,
};

enum 
{
  BIAS_1_4		= 0,
  BIAS_1_2  	= 1,
	BIAS_1_3 		= 2,
};

enum 
{
	COM_L  		= 0,
  COM_H		= 1,
};

enum 
{
	SEG_L  		= 0,
  SEG_H		= 1,
};

enum 
{
  LDRV_0		= 0,
  LDRV_1		= 1,
	LDRV_2		= 2,
	LDRV_3		= 3,
	LDRV_4		= 4,
	LDRV_5		= 5,
	LDRV_6		= 6,
	LDRV_7		= 7,
};
#endif