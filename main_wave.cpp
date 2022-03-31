#include "wave.h"
#include <iostream>
using namespace std;
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
	data = getSignalData();
	SIGNAL.CalculateFFT(data);
	write_adc(data, b);

}