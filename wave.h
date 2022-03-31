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
using std::vector;
using std::complex;
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
// head.flags = ADCF_TYPE_COMPLEX | ADCF_DATA_FLOAT;
class Wave
{
	Wave(unsigned int size = 512, float frqsmpl = 48000.0)
	{
		FFT_length = size;
		frq_sample = frqsmpl;
	}
private:
	// ПРИМЕЧАНИЕ: ПО СПЕЦИФИКЕ ВАРИАНТА, ЧАСТОТЫ f1 и f3 СОВПАДАЮТ, ПОЭТОМУ БЫЛО ВЗЯТО f3 = 400 Hz.

	float frq_sample;
	unsigned int FFT_length;
	vector <complex<float>> signal_data;			// вектор отсчета сигналов
	vector <float> f = { 0.0,200.0,1024.0,400.0 }; //Создан массив из 4 элементов для удобного индексирования гармоник где f1 = f[1]..... fn = f[n]
	vector <float> A = { 0, 0.02, 0.2, 0.2 };		  // Создан массив из 4 элементов для удобного индексирования амплитуд гармоник, где А1 = А[1]..... An = A[n]											  

	complex <float> SignalHarmony(int n) // Метод, возвращающий расчет сигнала соответсвующей гармоники
	{
		return sin(2 * M_PI * n * f[n] / frq_sample);
	}
	void setFFT_length(unsigned int set) // приватный сеттер для косвенного применения в другом публичном методе
	{
		FFT_length = set;
	}
	int getFFT_length() // приватный геттер для косвенного применения в другом публичном методе
	{
		return FFT_length;
	}

public:
	void setDataSize(unsigned int set)
	{
		setFFT_length(set);
		signal_data.resize(getFFT_length());
	}
	vector <complex<float>> getSignalData()
	{
		return signal_data;
	}
};
#endif // !_WAVE_H