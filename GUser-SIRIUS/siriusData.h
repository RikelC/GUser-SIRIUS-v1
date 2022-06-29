#ifndef siriusData_h
#define siriusData_h 1
#include "global.h"
#include "Rtypes.h"
class siriusData
{
	protected:

		UShort_t gain;
		UInt_t eventnumber;
		ULong64_t timestamp;
		UShort_t trace[TRACE_SIZE];
		int boardID;
		int boardIdx;
		int channelID;
		//extracted data
		double Baseline;
		double Noise;//sigma
		double signalHeight;//max val - baseline
		UShort_t RiseTime;
		UShort_t Max_pos;
		UShort_t Trigger;
		double filt_Amplitude;
		ULong64_t cfd_time;
	public:
		siriusData();
		~siriusData();
		void set_eventnumber(UInt_t i){eventnumber =i;}
		void set_timestamp(ULong64_t i){timestamp =i;}
		void set_boardID(int i){boardID =i;}
		void set_boardIdx(int i){boardIdx =i;}
		void set_channelID(int i){channelID = i;}
		void set_gain( UShort_t i){gain = i;}
		void set_trace_value(int i, UShort_t v){trace[i] = v;}

		void set_Baseline(double x){Baseline = x;}
		void set_Noise(double x){ Noise =x;}//sigma
		void set_signalHeight(double x) { signalHeight =x;}//max val - baseline
		void set_RiseTime(UShort_t x){ RiseTime =x;}
		void set_MaxPos( UShort_t x) {Max_pos =x;}
		void set_Trigger (UShort_t x){ Trigger =x;}
		void set_filterAmplitude(double x) {filt_Amplitude = x;}
		void set_cfdTime(ULong64_t x){ cfd_time =x ;}


		UInt_t get_eventnumber()const {return eventnumber;}
		ULong64_t get_timestamp()const {return timestamp;}
		int get_boardID()const {return boardID;}
		int get_boardIdx()const {return boardIdx;}
		int get_channelID()const{return channelID;}
		UShort_t get_gain()const{return gain;}
		UShort_t get_trace_value(int i)const {return trace[i];}
		UShort_t* get_trace(){return trace;}


		double get_Baseline()const{return Baseline;}
		double get_Noise()const{return Noise;}//sigma
		double get_signalHeight()const{return signalHeight;}//max val - baseline
		UShort_t get_RiseTime()const{return RiseTime;}
		UShort_t get_Max_pos()const{return Max_pos;}
		UShort_t get_Trigger()const{return Trigger;}
		double get_filter_Amplitude()const{return filt_Amplitude;}
		ULong64_t get_cfd_time()const{return cfd_time;}

		//address

		UInt_t* address_of_eventnumber() {return &eventnumber;}
		ULong64_t* address_of_timestamp() {return &timestamp;}
		int* address_of_boardID() {return &boardID;}
		int* address_of_channelID(){return &channelID;}
		UShort_t* address_of_gain(){return &gain;}
		UShort_t* address_of_trace(){return trace;}

		//ClassDef (siriusData ,1); 
};

#endif
