#include "global.h"
Singleton* Singleton::instance = 0;
Singleton* Singleton::getInstance() {
	if(!instance) {
		instance = new Singleton();
		return instance;
	}
	else {
		return instance;
	}
}
Singleton::Singleton(){

	frameName[0]= "Cobo";
	frameName[1]= "Eby";
	frameName[2]= "Hello";
	frameName[3]= "xml header";
	frameName[4]= "rea trace";
	frameName[5]= "rea gen";
	frameName[6]= "sirius";
	frameName[7]= "else";


	fBoardList_DSSD[0]= 169;
	fBoardList_DSSD[1]= 170;
	fBoardList_DSSD[2]= 171;
	fBoardList_DSSD[3]= 172;
	fBoardList_DSSD[4]= 173;
	fBoardList_DSSD[5]= 174;
	fBoardList_DSSD[6]= 175;
	fBoardList_DSSD[7]= 177;
	fBoardList_DSSD[8]= 179;
	fBoardList_DSSD[9]= 180;
	fBoardList_DSSD[10]= 181;
	fBoardList_DSSD[11]= 165;
	fBoardList_DSSD[12]= 178;
	fBoardList_DSSD[13]= 176;
	fBoardList_DSSD[14]= 188;
	fBoardList_DSSD[15]= 192;

	fBoardList_Tunnel[0]= 187;

	fBoardList_Tunnel[1]= 188;

	for(int board=0 ; board< NBOARDS_DSSD; board++){
		fConvertNoBoardIndexLocal[fBoardList_DSSD[board]] = board ;

	}

	for(int board=0 ; board< NBOARDS_TUNNEL; board++){
		fConvertNoBoardIndexLocal_Tunnel[fBoardList_Tunnel[board]] = board ;
	}
	ff_window = 2000;//front-front
	fb_window = 2000;//front-back
	bf_window = 2000;//back-front
	bb_window = 2000;//back-back

}

Singleton::~Singleton(){
	cout<<"singleto destrucyor called."<<endl;
	if(instance)delete instance; instance=NULL;
}
