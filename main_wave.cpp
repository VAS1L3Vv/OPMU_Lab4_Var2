#include "wave.h"
#include <iostream>
using namespace std;
int main()
{
	setlocale(LC_ALL, "rus");
	vector <complex<float>> data;
	unsigned int a;
	double b;
	cout << "¬ведите с новой строки: „астоту дискретизации, количество отсчетов (или оставьте по умолчанию = 48к√ц; =512;) \n";
	cin >> b; 
	cout << endl;
	cin >> a;
	Wave SIGNAL(a,b);
	SIGNAL.setDataSize(a);
	SIGNAL.CalculateFFT();
	data = SIGNAL.getSignalData();
	SIGNAL.write_adc(data, b);
}