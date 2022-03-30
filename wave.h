#include <iostream>
#include <cmath>
#include <complex>
#include <vector>
#include <fftw3.h>

fftwf_plan fftwf_plan_dft_1d(int n, fftwf_complex* sample_in, fftwf_complex* sample_out, fftwf_direction direction, int flags);
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
	unsigned int SizeFFT = 512;
	std::vector <float> f = { 0.0,200.0,1024.0,400.0 }; //Создан массив из 4 элементов для удобного индексирования гармоник где f1 = f[1]..... fn = f[n]

			// ПРИМЕЧАНИЕ: ПО СПЕЦИФИКЕ ВАРИАНТА, ЧАСТОТЫ f1 и f3 СОВПАДАЮТ, ПОЭТОМУ БЫЛО ВЗЯТО f3 = 400 Hz.
	std::vector <float> A = {0, 0.02, 0.2, 0.2}; // Создан массив из 4 элементов для удобного индексирования амплитуд гармоник, где А1 = А[1]..... An = A[n]

public:
	int getSizeFFT()
	{
		return SizeFFT;
	}

};