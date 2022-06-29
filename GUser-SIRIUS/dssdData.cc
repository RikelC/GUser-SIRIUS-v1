#include "dssdData.h"

dssdData::dssdData(){

	trace = new UShort_t[TRACE_SIZE];
}


dssdData::~dssdData(){

	delete [] trace;
}


void dssdData::GetSignalInfo(){
	//Reset the values
	Baseline = 0;
	signal_is=0;
	Noise=0;//sigma
	signalHeight=0;//max val - baseline
	RiseTime=0;
	Max_pos=0;
	Trigger=0;

Int_t n1 = 200;
Int_t n2 = TRACE_SIZE -200;
	//calculate baseline
	double temp =0.;
	for (UShort_t i = n1; i < n1+51; i++) {
		Baseline += (Double_t)trace[i];
	}
	Baseline /=  (Double_t)(50);
	//calculate the noise
	for (UShort_t i = n1; i < n1+51; i++) {
		temp = ((Double_t)trace[i] - Baseline);
		Noise += temp*temp;
	}
	Noise = TMath::Sqrt(Noise/ (Double_t)(50));

	//determine the polarity of the signal
	for(UShort_t n = n1; n < n2; n++){
		signal_is+=trace[n]- Baseline;
	}

	//Get max value and max pos
	UShort_t max_val = trace[0];
	UShort_t max_pos = 0;
	for (UShort_t i = n1; i < n2; i++) {
		if(signal_is > 0.){
			if(trace[i] > max_val){
				max_val = trace[i];
				max_pos = i;
			}
		}
		else{
			if(trace[i] < max_val){
				max_val = trace[i];
				max_pos = i;
			}
		}
	}
	signalHeight = double(max_val - Baseline);
	Max_pos = max_pos;
	//calculate the trigger
	for (UShort_t i = max_pos; i >0; i--) {
		temp =  static_cast<double>(trace[i] - Baseline);
		if(temp <= 0.3*signalHeight){
			Trigger = i; break;
		}
	}

	//calculate risetime
	UShort_t interval =0;
	temp = signalHeight;
	UShort_t i = max_pos;
	if(signal_is > 0.){
		while(temp > (3.*Noise) && i > 0){
			temp = static_cast<double>(trace[i] - Baseline);
			i--;
			interval++;
		}
	}
	else{
		while(temp < - (3.*Noise) && i > 0){
			temp = static_cast<double>(trace[i] - Baseline);
			i--;
			interval++;
		}
	}  

	RiseTime = interval * sampling_period;

	stripnumber = get_DSSD_strip_number(&boardID,&channelID);

}


int dssdData::get_DSSD_strip_number(int *p_board, int *p_channel){

	int StripNo = 0;
	switch (*p_board) {
		//-----------------MB1-------------
		case MB1_P4_BOARD1:
			StripNo = 63 - *p_channel;
			break;
		case MB1_P4_BOARD2:
			StripNo =  63 - *p_channel - NCHANNELS;
			break;
		case MB1_P5_BOARD1:
			StripNo = 63 - *p_channel - 2*NCHANNELS;
			break;
		case MB1_P5_BOARD2:
			StripNo = 63 - *p_channel - 3*NCHANNELS;
			break;
			//-----------------MB2-------------
		case MB2_P5_BOARD1:
			StripNo = 64 + *p_channel;
			break;
		case MB2_P5_BOARD2:
			StripNo = 64 + *p_channel + NCHANNELS;
			break;
		case MB2_P4_BOARD1:
			StripNo = 64 + *p_channel + 2* NCHANNELS;
			break;
		case MB2_P4_BOARD2:
			StripNo =  64 + *p_channel + 3*NCHANNELS;
			break;
			//-----------------MB3-------------
		case MB3_P4_BOARD1:
			StripNo = 128 + *p_channel;
			break;
		case MB3_P4_BOARD2:
			StripNo = 128 + *p_channel + NCHANNELS;
			break;
		case MB3_P5_BOARD1:
			StripNo = 128 + *p_channel + 2* NCHANNELS;
			break;
		case MB3_P5_BOARD2:
			StripNo = 128 + *p_channel + 3*NCHANNELS;
			break;
			//-----------------MB4-------------
		case MB4_P5_BOARD1:
			StripNo = 255 - *p_channel;
			break;
		case MB4_P5_BOARD2:
			StripNo = 255 - *p_channel - NCHANNELS;
			break;
		case MB4_P4_BOARD1:
			StripNo = 255 - *p_channel -2*NCHANNELS;
			break;
		case MB4_P4_BOARD2:
			StripNo = 255 - *p_channel -3*NCHANNELS;
			break;
		default:
			break;
	}
	stripnumber = StripNo;
	return StripNo;
}
