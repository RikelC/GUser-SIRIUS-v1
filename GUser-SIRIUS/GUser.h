// File :  GUser.h
// Author: Luc Legeard
//Modification: Rikel CHAKMA
//////////////////////////////////////////////////////////////////////////////
//
// Class GUser
//
// This class manage user methodes
//
/////////////////////////////////////////////////////////////////////////////

// ---------------------------------------------------------------------------
// ***************************************************************************
// *                                                                         *
// *   This program is free software; you can redistribute it and/or modify  *
// *   it under the terms of the GNU General Public License as published by  *
// *   the Free Software Foundation; either version 2 of the License, or     *
// *   (at your option) any later version.                                   *
// *                                                                         *
// ***************************************************************************/


#ifndef __GUser__
#define __GUser__
#include <fstream>
#include <sstream>
#include <map>
#include <string>
#include<vector>
#include<deque>
#include <algorithm>    // std::sort
using std::ostream;
#include <iostream>
#include <TObject.h>
#include "General.h"
#include "GAcq.h"
#include "GDevice.h"
#include "TH1.h"
#include "TH2.h"
#include "TGraph.h"
#include "MFMExogamFrame.h"
#include "MFMMergeFrame.h"
#include "MFMCoboFrame.h"
#include "MFMExogamFrame.h"
#include "MFMEbyedatFrame.h"
#include "MFMNumExoFrame.h"
#include "MFMSiriusFrame.h"
#include "MFMAllFrames.h"
#include "MFMReaGenericFrame.h"
#include "Rtypes.h"
//#include  "TRandom3.h"
#include "global.h"
#include "dssdData.h"
#include "digitalFilters.h"
#include "digitalCFD.h"
#include "Calibration.h"
#include "DataPoint.h"
#include "EventPoint.h"
#define sum_neighboring_strips 1
#define print_info 0 
#define FrontBackGap 20


//_________________________________________________________________________________________

class digitalCFD;
class digitalFilters;
class dssdData;
class GUser : public  GAcq{


	protected:
		int fVerbose;               // level (0 to 10 ) of verbose default = 0  ( level 10 is good for debug)
		//-----------Frames------------
		MFMMergeFrame *  fMergeframe ;
		MFMCoboFrame *   fCoboframe ;
		MFMCommonFrame * fInsideframe ;
		MFMSiriusFrame * fSiriusframe ;
		MFMReaGenericFrame * fGenericframe;

		Int_t CheckEventNumber;
		int frameCounter[8];

	private:
		//------------------
		//long long int fBoardHitPattern[NBOARDS];
		//     std::string frameName[8];

		//unsigned short fBoardList_Tunnel[NBOARDS_TUNNEL];
		//int fConvertNoBoardIndexLocal_Tunnel[200];
		//unsigned short fBoardList_DSSD[NBOARDS_DSSD];
		//int fConvertNoBoardIndexLocal[200];
		// int ff_window, fb_window, bf_window, bb_window;

		Singleton* s1;
		digitalFilters *filter;
		digitalCFD * cfd;
		Calibration *calib;
		TH1I ***  h_tunnel;//!
		//long long int fBoardHitPattern[NBOARDS];
		//---------Histograms----------
		// TH1I * Gain    [NBOARDS][NUMEXO_NB_CHANNELS];
		//TH1I *** hGain ; //!
		//TH1I *** hFeedBack; //!
		TH2F*** hTrace_Sum ;  //! -- this silences the error
		TH1F*** hRaw; //!
		TH2F*** hTrap; //!
		TH1I* h_delT_ff; //!
		TH1I* h_delT_fb; //!
		TH1I* h_delT_bf; //!
		TH1I* h_delT_bb; //!
		TH2F* h_E_frontBack; //!
		TH2I* h_DSSD_XY_hit; //!
		TH1I*h_dssd_count; //!
		TH2F* h_calib_strip; //!
		TH2F* h_raw_strip; //!

		TH1I* h_dssd_rate; //!
		double dssd_rate_counter[256]; //!
		double dssd_rate_CMA[256]; //!
		unsigned long long int **dssd_event_counter;//!
		double dataSet_counter;

		TH2F* h_dssd_baseline;
		TH2F* h_dssd_noise;
		TGraph*** gr_baseline;//!
		/*
		   TGraph* hcfd_fracvin;
		   TGraph*  hcfd_vin;
		   TGraph* hcfd_vindelayed;
		   TGraph* hcfd;*/
		//-----------------------------
		//------------------data----------
		dssdData *dData;

		uint32_t eventnumber;
		uint64_t timestamp;
		uint16_t gain;
		int  dumpsize;
		int framesize;
		int maxdump;
		int channel, board,iboard;
		int NbItems;
		uint16_t value;
	//	UShort_t trace[TRACE_SIZE];
		//extracted data
		//double Baseline;
		//double signal_is;
		//double Noise;//sigma
		//double signalHeight;//max val - baseline
		//UShort_t RiseTime;
		//UShort_t Max_pos;
		//UShort_t Trigger;
		double filt_Amplitude;
		ULong64_t cfd_time;
		TTree* trapTree; // store trapezoidal amplitudes
		//----------
		void perform();//get amp, calibrate, get time

		DataPoint dPoint;
		EventPoint ePoint;

		Long64_t td_ff, td_fb, td_bf,td_bb;
		bool start_new_event;
		std::vector<DataPoint>dataVec;
		std::vector<DataPoint>myEvent;
		std::vector<DataPoint>myEvent_front;
		std::vector<DataPoint>myEvent_back;
		void reconstruct_events(std::vector<DataPoint> &dataSet);
		EventPoint determine_dssd_pixel(std::vector<DataPoint> &myEvent);

	public:

		GUser(GDevice* _fDevIn= NULL, GDevice* _fDevOut= NULL) ;   // default constructor of GUser object
		~GUser() ;

		virtual void InitUser();
		virtual void InitUserRun();
		virtual void User();
		virtual void EndUserRun();
		virtual void EndUser();
		virtual void InitTTreeUser();

		virtual void UserFrame(MFMCommonFrame * commonframe);
		virtual void UserMergeFrame(MFMCommonFrame * commonframe);
		virtual void UserSiriusFrame( MFMCommonFrame * commonframe);
		virtual void UserGenericFrame(MFMCommonFrame * commonframe);
		virtual void UserCoboFrame(MFMCommonFrame * commonframe);
		ClassDef (GUser ,1); // User Treatment of Data

};

#endif

