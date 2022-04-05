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
	// ����������: �� ��������� ��������, ������� f1 � f3 ���������, ������� ���� ����� f3 = 400 Hz.

	double frq_sample;
	unsigned int FFT_length;
	vector <complex<float>> signal_data;			// ������ ������� ��������
	float f[4] = { 0,200.0,1024.0,400.0 }; //������ ������ �� 4 ��������� ��� �������� �������������� �������� ��� f1 = f[1]..... fn = f[n]
	float A[4] = { 0, 0.02, 0.2, 0.2 };	 // ������ ������ �� 4 ��������� ��� �������� �������������� �������� ��������, ��� �1 = �[1]..... An = A[n]											  

	complex <float> SignalHarmony(int n,int i) // �����, ������������ ������ ������� �������������� ���������
	{
		float St = A[n] * sin(2.0 * M_PI * i * f[n] / frq_sample);
		return St;
	}
	void GenerateSignal()
	{
		int x = getFFT_length();
		for (int i = 0; i < x; i++)
		{
			signal_data[i] = SignalHarmony(1,i) + SignalHarmony(2,i) + SignalHarmony(3,i);
		}
	}

	int getFFT_length() // ��������� ������ ��� ���������� ���������� � ������ ��������� ������
	{
		return FFT_length;
	}
	void setFFT_length(unsigned int set) // ��������� ������ ��� ���������� ���������� � ������ ��������� ������
	{
		FFT_length = set;
	}
	

public:
	Wave(unsigned int size = 512, double frqsmpl = 48000.0)
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
	fftwf_plan plan = fftwf_plan_dft_1d(getFFT_length(), (fftwf_complex*)& data[0], (fftwf_complex*)& data[0], FFTW_FORWARD, FFTW_ESTIMATE);
	fftwf_execute(plan);
	fftwf_destroy_plan(plan);
	}

	bool write_adc(vector<complex<float>> data, double freq_sampling)
	{
		ADCFILEHEADER head;
		head.Am = 1.0;
		head.h = 32;
		head.dt = 1.0 / freq_sampling;
		head.fN = getFFT_length();
		head.flags = ADCF_TYPE_COMPLEX | ADCF_DATA_FLOAT;
		const char* FName = "H:\\Desktop\\101.adc";
		float im = 0.0;
		ofstream out(FName, ios::binary);
		out.write((char*)& head, sizeof(head));
		for (int i = 0; i < getFFT_length(); ++i)
		{
			out.write((char*)& data[i], sizeof(data[i]));
		}
		out.close();
		return true;
	}
};
#endif // !_WAVE_H