#include "wave.h"
#include <iostream>
using std::cout;
using std::cin;
int main()
{
	vector <complex<float>> 
	unsigned int a;
	float b;
	cout << "¬ведите с новой строки: „астоту дискретизации, количество отсчетов (или оставьте по умолчанию = 48к√ц; =512;) \n";
	cin >> a; 
	cin >> b;
	Wave SIGNAL(a,b);
	SIGNAL.setDataSize(a);
	SIGNAL.GenerateSignal();
	SIGNAL.CalculateFFT();


}