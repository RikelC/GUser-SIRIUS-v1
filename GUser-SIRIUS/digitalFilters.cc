#include "digitalFilters.h"

digitalFilters::digitalFilters(){

	s1 = Singleton::getInstance();
	Capacitance = 1.;//in pF
	RC_constant = 700.;
	trapezoidal_shaper_M = 0. ;
	trapezoidal_shaper_m2 = 0.;
	trapezoidal_shaper_m1 = 0.;
	array_u = new Double_t[TRACE_SIZE];
	array_v = new Double_t[TRACE_SIZE];
	array_d = new Double_t[TRACE_SIZE];
	array_p = new Double_t[TRACE_SIZE];
	Rectangular = new Double_t[TRACE_SIZE];
	Trapezoidal = new Double_t[TRACE_SIZE];
	kPar = new UShort_t*[NBOARDS_DSSD];
	mPar = new UShort_t*[NBOARDS_DSSD];
	for(int i = 0; i < NBOARDS_DSSD; i++){
		kPar[i] = new UShort_t[NCHANNELS];
		mPar[i] = new UShort_t[NCHANNELS];
		for(int j = 0; j < NCHANNELS; j++){
			kPar[i][j] = 200;
			mPar[i][j] = 50;
		}
	}




}

digitalFilters::~digitalFilters(){
	delete [] array_u;
	delete [] array_v;
	delete [] array_d;
	delete [] array_p;
	delete [] Rectangular;
	delete [] Trapezoidal;
	for(int i = 0; i < NBOARDS_DSSD; i++){
		delete [] kPar[i];
		delete [] mPar[i];
	}
	delete [] kPar;
	delete [] mPar;
}


void digitalFilters::assign_k_m_values(){
	std::string line; UShort_t boardID, bIdx, chID, k_val, m_val;

	std::ifstream myfile;
	myfile.open("min_trapezoidal_parameters.txt",std::ifstream::in);
	if (myfile.is_open())
	{
		getline (myfile,line);
		while (!myfile.eof() )
		{
			myfile >> boardID >> chID >> k_val >> m_val;
			bIdx = s1->fConvertNoBoardIndexLocal[boardID];
			kPar[bIdx][chID] = k_val;
			mPar[bIdx][chID] = m_val;
		}
		myfile.close();
	}else{std::cout<<"min_trapezoidal_parameters.txt"<<std::endl;}

}


void digitalFilters::set_DSSD_gain(Double_t gain){
	Capacitance = gain; RC_constant =  Resistance*Capacitance;
	trapezoidal_shaper_M = pow((exp(sampling_period/RC_constant) - 1.), -1.);
	trapezoidal_shaper_m2 = 1.;// Gain of the Shaper Amplifier
	trapezoidal_shaper_m1 =  trapezoidal_shaper_m2 *  trapezoidal_shaper_M;
}

void digitalFilters::set_RC_constant(Double_t  r){
	RC_constant = r;
	trapezoidal_shaper_M = pow((exp(sampling_period/RC_constant) - 1.), -1.);
	trapezoidal_shaper_m2 = 1.;// Gain of the Shaper Amplifier
	trapezoidal_shaper_m1 =  trapezoidal_shaper_m2 *  trapezoidal_shaper_M;
}


Double_t digitalFilters::trapezoidal_filter_algorithm1(  dssdData* const data, TH1* h){
	Double_t max_val =0.;
	UShort_t max_pos = 0;
	int b = data->get_boardIdx();
	int ch = data->get_channelID();
	UShort_t k = kPar[b][ch];
	UShort_t m = mPar[b][ch];
	UShort_t l = k+m;
	Double_t signalAmplitude = 0.;
	
//cout<<"baseline "<<data->get_Baseline()<<"  risetime "<<data->get_RiseTime()<<"  noise "<<data->get_Noise()<<" height  "<<data->get_signalHeight()<<"  maxpos "<<data->get_Max_pos()<<"  trigger "<<data->get_Trigger()<<endl;


//cout<<"board "<<b<<"  ch "<<ch<<endl;
//cout<<" k "<<k<<"  m "<<m<<" l "<<l<<endl;

for(UShort_t n =0; n < 5; n++){
array_u[n] = data->get_Baseline();
array_v[n] = data->get_Baseline();
array_d[n] = 0.;
Rectangular[n] =0.;
Trapezoidal[n] = 0.;
}


for(UShort_t n = 5; n <TRACE_SIZE; n++){
		
if(n < k){
			array_u[n] =(Double_t) data->get_trace_value(n) - data->get_Baseline();
			array_v[n] = (Double_t)data->get_trace_value(n) - data->get_Baseline();
		}

		else{
			array_u[n]= (Double_t)(data->get_trace_value(n)- data->get_trace_value(n-k));
		}

		if(n >= l+k){
			array_v[n] = (Double_t)(data->get_trace_value( n-l) - data->get_trace_value( n-l-k));
		}

		array_d[n] = array_u[n] - array_v[n];

		Rectangular[n] = Rectangular[n-1] + array_d[n] - (exp(- sampling_period /RC_constant) *array_d[n-1]);

		Trapezoidal[n] = Trapezoidal[n-1] + Rectangular[n];

		 signalAmplitude = Trapezoidal[n]/k;
                 h->Fill(n+1, signalAmplitude);

		//	//get max position here
		if(data->get_signal_is() > 0.){
			if(Trapezoidal[n] > max_val){
				max_val = Trapezoidal[n];
				max_pos = n;
			}
		}else{
			if(Trapezoidal[n] < max_val){
				max_val = Trapezoidal[n];
				max_pos = n;
			}
		}


	}
	//--
	Double_t maxR =0.; Double_t maxL = 0.;Double_t rR =0.; Double_t rL =0.;
	UShort_t j2 = max_pos + 1;
	UShort_t j1 = max_pos -1;
	// take the average from Trigger+risetime --> k+m > risetime
	if(l >= data->get_RiseTime()/sampling_period){
		j1 = data->get_Trigger() + data->get_RiseTime()/sampling_period;
		j2 = data->get_Trigger() + l;
		for(UShort_t i = j1;i <j2;i++){
			maxR += Trapezoidal[j2];
		}
		max_val = maxR /(Double_t)(j2-j1);

	}else{
		if(data->get_signal_is() > 0.){
			while(Trapezoidal[j2] > 0.999 * max_val){
				maxR += Trapezoidal[j2];
				j2++;
				rR++;
			}

			while(Trapezoidal[j1] > 0.999 * max_val){
				maxL += Trapezoidal[j1];
				j1--;
				rL++;
			}

		}else{
			while(Trapezoidal[j2] < 0.999 * max_val){
				maxR += Trapezoidal[j2];
				j2++;
				rR++;
			}
			while(Trapezoidal[j1] < 0.9999 * max_val){
				maxL += Trapezoidal[j1];
				j1--;
				rL++;
			}

		}
		//compute average
		max_val = max_val + maxL + maxR;
		max_val = max_val /(rR+rL+1.);
	}
	//-------------
	signalAmplitude = max_val /(Double_t)(k);
//	 cout<<"amplitude "<<signalAmplitude<<endl;
	return std::abs(signalAmplitude);
}



Double_t digitalFilters::trapezoidal_filter_algorithm1(  dssdData* const data, UShort_t k , UShort_t m){
	Double_t max_val =0.;
	UShort_t max_pos = 0;
	UShort_t l = k+m;
	Double_t signalAmplitude = 0.;

	for(UShort_t n = 0; n <TRACE_SIZE; n++){
		if(n < k){
			array_u[n] =(Double_t) data->get_trace_value(n) - data->get_Baseline();
			array_v[n] = (Double_t)data->get_trace_value(n) - data->get_Baseline();
		}

		else{
			array_u[n]= (Double_t)(data->get_trace_value(n)- data->get_trace_value( -k));
		}

		if(n >= l+k){
			array_v[n] = (Double_t)(data->get_trace_value( n-l) - data->get_trace_value( n-l-k));
		}

		array_d[n] = array_u[n] - array_v[n];

		Rectangular[n] = Rectangular[n-1] + array_d[n] - (exp(- sampling_period /RC_constant) *array_d[n-1]);

		Trapezoidal[n] = Trapezoidal[n-1] + Rectangular[n];

		// signalAmplitude = Trapezoidal[n]/k;

		// hTrap[iboard][channel]->Fill(n+1, signalAmplitude);
		//get max position here
		if(data->get_signal_is() > 0.){
			if(Trapezoidal[n] > max_val){
				max_val = Trapezoidal[n];
				max_pos = n;
			}
		}else{
			if(Trapezoidal[n] < max_val){
				max_val = Trapezoidal[n];
				max_pos = n;
			}
		}


	}
	//--
	Double_t maxR =0.; Double_t maxL = 0.;Double_t rR =0.; Double_t rL =0.;
	UShort_t j2 = max_pos + 1;
	UShort_t j1 = max_pos -1;	
		if(data->get_signal_is() > 0.){
			while(Trapezoidal[j2] > 0.999 * max_val){
				maxR += Trapezoidal[j2];
				j2++;
				rR++;
			}

			while(Trapezoidal[j1] > 0.999 * max_val){
				maxL += Trapezoidal[j1];
				j1--;
				rL++;
			}

		}else{
			while(Trapezoidal[j2] < 0.999 * max_val){
				maxR += Trapezoidal[j2];
				j2++;
				rR++;
			}
			while(Trapezoidal[j1] < 0.9999 * max_val){
				maxL += Trapezoidal[j1];
				j1--;
				rL++;
			}

		}
		//compute average
		max_val = max_val + maxL + maxR;
		max_val = max_val /(rR+rL+1.);
	
	//-------------
	signalAmplitude = max_val /(Double_t)(k);
	// cout<<"amplitude "<<signalAmplitude<<endl;
	return std::abs(signalAmplitude);
}
