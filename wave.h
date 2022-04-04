#pragma once
#ifndef _WAVE_H
#define _WAVE_H
#define _USE_MATH_DEFINES
#include <iostream>
#include <cmath>
#include <complex>
#include <vector>
#include <fftw3.h>
#include <cmath>
#include <fstream>
using namespace std;
struct ADCFILEHEADER
{
	double dt;
	unsigned long h;
	unsigned long fN;
	float Am;
	unsigned long flags;
	char reserv[8];
};
typedef struct ADCFILEHEADER* LPADCFILEHEADER;
#define ADCF_DATA_INTEGER 0x00000000
#define ADCF_DATA_FLOAT 0x00000001
#define ADCF_TYPE_REAL 0x00000000 
#define ADCF_TYPE_COMPLEX 0x00000002
class Wave
{
private:
	// ПРИМЕЧАНИЕ: ПО СПЕЦИФИКЕ ВАРИАНТА, ЧАСТОТЫ f1 и f3 СОВПАДАЮТ, ПОЭТОМУ БЫЛО ВЗЯТО f3 = 400 Hz.

	float frq_sample;
	unsigned int FFT_length;
	vector <complex<float>> signal_data;			// вектор отсчета сигналов
	vector <float> f = { 0.0,200.0,1024.0,400.0 }; //Создан массив из 4 элементов для удобного индексирования гармоник где f1 = f[1]..... fn = f[n]
	vector <float> A = { 0, 0.02, 0.2, 0.2 };	 // Создан массив из 4 элементов для удобного индексирования амплитуд гармоник, где А1 = А[1]..... An = A[n]											  

	complex <float> SignalHarmony(int n) // Метод, возвращающий расчет сигнала соответсвующей гармоники
	{
		return sin(2 * M_PI * n * f[n] / frq_sample);
	}
	void GenerateSignal()
	{
		int x = getFFT_length();
		for (int i = 0; i < x; i++)
		{
			signal_data[i] = SignalHarmony(1) + SignalHarmony(2) + SignalHarmony(3);
		}
	}

	int getFFT_length() // приватный геттер для косвенного применения в другом публичном методе
	{
		return FFT_length;
	}
	void setFFT_length(unsigned int set) // приватный сеттер для косвенного применения в другом публичном методе
	{
		FFT_length = set;
	}
	

public:
	Wave(unsigned int size = 512, float frqsmpl = 48000.0)
	{
		FFT_length = size;
		cout << endl << size << endl;
		frq_sample = frqsmpl;
		cout << endl << frqsmpl << endl;
	}
	void setDataSize(unsigned int set = 512)
	{
		setFFT_length(set);
		signal_data.resize(getFFT_length());
	}
	vector <complex<float>> getSignalData()
	{
		return signal_data;
	}

	void CalculateFFT(vector <complex<float>> &data)
	{
		GenerateSignal();
	fftwf_plan plan = fftwf_plan_dft_1d(data.size(), (fftwf_complex*)& data[0],
		(fftwf_complex*)& data[0], FFTW_FORWARD, FFTW_ESTIMATE);
	fftwf_execute(plan);
	fftwf_destroy_plan(plan);
	}

	bool write_adc(vector<complex<float>> data, double freq_sampling)
	{
		ADCFILEHEADER head;
		head.Am = 1.0;
		head.h = 32;
		head.dt = 1.0 / freq_sampling;
		head.fN = data.size();
		head.flags = ADCF_TYPE_COMPLEX | ADCF_DATA_FLOAT;
		const char* FName = "H:\\Desktop\\101.adc";
		float im = 0.0;
		ofstream out(FName, ios::binary);
		out.write((char*)& head, sizeof(head));
		for (int i = 0; i < data.size(); ++i)
		{
			out.write((char*)& data[i], sizeof(data[i]));
		}
		out.close();
		return true;
	}
};
#endif // !_WAVE_H