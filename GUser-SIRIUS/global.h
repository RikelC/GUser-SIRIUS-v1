#ifndef MyGlobal_h
#define MyGlobal_h 1


#include <iostream>
#include <string>
#define timestamp_unit 10 //ns
#define si_foil_distance 15 //cm
#define pre_trig_buffer 512
#define NBOARDS_DSSD 16
#define NCHANNELS 16
#define NSTRIPS_DSSD NBOARDS_DSSD * NCHANNELS
#define TRACE_SIZE 985
#define sampling_period 5 //ns
#define timestamp_unit 10 //ns
#define Resistance 700. //All the ASIC resistors are 700 k Ohms
//-----------------------
//   DSSD  NUMEXO Boards
//-----------------------
#define MB1_P4_BOARD1 180
#define MB1_P4_BOARD2 181
#define MB1_P5_BOARD1 169
#define MB1_P5_BOARD2 165

#define MB2_P4_BOARD1 175
#define MB2_P4_BOARD2 173
#define MB2_P5_BOARD1 174
#define MB2_P5_BOARD2 171

#define MB3_P4_BOARD1 192
#define MB3_P4_BOARD2 188
#define MB3_P5_BOARD1 176
#define MB3_P5_BOARD2 178

#define MB4_P4_BOARD1 172
#define MB4_P4_BOARD2 177
#define MB4_P5_BOARD1 170
#define MB4_P5_BOARD2 179


#define Si  2   // channel number
#define PMT 1
#define SED 0  //channel number
#define NBOARDS_TUNNEL 1

using namespace std;

class Singleton
{
	public:
		static Singleton *getInstance();
		string frameName[8];
		unsigned short fBoardList_Tunnel[NBOARDS_TUNNEL];
		int fConvertNoBoardIndexLocal_Tunnel[200];
		int fBoardList_DSSD[NBOARDS_DSSD];
		int fConvertNoBoardIndexLocal[200];
		int ff_window, fb_window, bf_window, bb_window;
	private:
		Singleton();
		static Singleton *instance;
		virtual ~Singleton();

};

//called by Singleton* s1 = Singleton::getInstance();
/****************

  physical
  strip      0--------------------------->127
  ------
  MB
  strip      64<-----------1------------->64            128 
  | P5 | P4 |=======| P5 | P4 |      1        ^
  ___________________________  ____ ^        |
  |   MB1           MB2       |  P4  |        |
  |                           | ____ |        |
  |                       MB3 |  P5  |        |
  |            DSSD           | ____ |        |
  |                           |               |
  |                           |      64       |
  |            Back           | ____ ^        |
  |                           |  P4  |        |
  |                       MB4 | ____ |        |
  |                           |  P5  |        | 
  |___________________________| ____ |       255
  1
  MB strip  physical strip

//--------------------
MB1<-->Box1
//-------------------
BOX ch ----> HDMI Cable
====P4====
1 ----> 008
2 ----> 009
3 ----> 010
4 ----> 011
5 ----> 012
6 ----> 013
7 ----> 015
8 ----> 056
====P5=====
9 ----> 057
10 ----> 058
11 ----> 059
12 ----> 061
13 ----> 063
14 ----> 064
15 ----> 065
16 ----> 066
//-------------
MB2<-->Box2
//------------
BOX ch ----> HDMI Cable
====P5====
1 ----> 024
2 ----> 025
3 ----> 026
4 ----> 027
5 ----> 028
6 ----> 029
7 ----> 030
8 ----> 031
====P4=====
9 ----> 032
10 ----> 033
11 ----> 034
12 ----> 035
13 ----> 036
14 ----> 037
15 ----> 038
16 ----> 039
//-------------
MB3<-->Box3
//------------
BOX ch ----> HDMI Cable
====P5====
1 ----> 040
2 ----> 041
3 ----> 042
4 ----> 043
5 ----> 044
6 ----> 045
7 ----> 046
8 ----> 047
====P4=====
9 ----> 048
10 ----> 049
11 ----> 050
12 ----> 051
13 ----> 052
14 ----> 053
15 ----> 054
16 ----> 055
//-------------
MB4<-->Box4
//------------
BOX ch ----> HDMI Cable
====P5====
1 ----> 001
2 ----> 002
3 ----> 003
4 ----> 004
5 ----> 005
6 ----> 006
7 ----> 007
8 ----> 014
====P4=====
9 ----> 016
10 ----> 017
11 ----> 018
12 ----> 019
13 ----> 020
14 ----> 021
15 ----> 022
16 ----> 023
***********************/
#endif
