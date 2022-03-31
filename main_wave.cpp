#include "wave.h"
#include <iostream>
using std::cout;
using std::cin;
int main()
{
	vector <complex<float>> data;
	vector <complex<float>> dataFFT;
	unsigned int a;
	float b;
	cout << "¬ведите с новой строки: „астоту дискретизации, количество отсчетов (или оставьте по умолчанию = 48к√ц; =512;) \n";
	cin >> a; 
	cin >> b;
	Wave SIGNAL(a,b);
	SIGNAL.setDataSize(a);
	SIGNAL.GenerateSignal();
	data = getSignalData();
	SIGNAL.CalculateFFT(data);
	dataFFT = getSpectrFFT();
	write_adc(dataFFT, b);

}