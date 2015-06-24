#ifndef ___LINESCAN___H__
#define ___LINESCAN___H__


//define of line scan channel
#define LINESCAN1_SI		100	//PG4
#define LINESCAN1_CLOCK		101	//PG
#define LINESCAN1_ADC		0	//PB4

#define LINESCAN2_SI		98	//PG2
#define LINESCAN2_CLOCK		99	//PG3
#define LINESCAN2_ADC		1	//PB5

//define constant for line 
//bus clock speed : 64Mhz
//MAX of lineScan Camera clock speed : 8Mhz
#define LEFT_NUM_SHIFT		4
#define RIGHT_NUM_SHIFT		2
#define NUM_LINE_DATA	125


#define BLACK_LINE	1
#define WHITE_LINE	0

//define constant for line data
#define MAX_LINE	5

//define constant for line data st
struct blackLineSt{
	int startAdd;
	int endAdd;
};
struct lineDataSt{
	int numOfLine;	//°¹¼ö
	int blackLineCount;
	struct blackLineSt blackLine[MAX_LINE];
};

//define constant for line scan status

#define TWO_LINE_CONTROL		0
#define LEFT_ONE_LINE_CONTROL	1
#define RIGHT_ONE_LINE_CONTROL	2
#define CROSS_LINE_CONTROL		3
#define SCHOOL_LINE1_CONTROL	4
#define SCHOOL_LINE2_CONTROL	5


#define SCHOOL_ZONE				200


#define SCHOOL_ZONE_ABLE		100
#define SCHOOL_ZONE_DISABLE		999


#define NOT_DETECTED	255


#define SENSING_ERROR		0
#define SENSING_SUCCESS 	1
//declaration of function
int lineScan(void);
int lineSensing(struct lineDataSt * leftlineData,struct lineDataSt * rightlineData);
int lineControl(int encoFeedback);




#endif
