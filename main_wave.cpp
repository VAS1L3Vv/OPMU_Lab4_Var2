#include "wave.h"
#include <iostream>
using namespace std;
int main()
{
	vector <complex<float>> data;
	vector <complex<float>> dataFFT;
	unsigned int a;
	float b;
	cout << "������� � ����� ������: ������� �������������, ���������� �������� (��� �������� �� ��������� = 48���; =512;) \n";
	cin >> a; 
	cin >> b;
	Wave SIGNAL(a,b);
	SIGNAL.setDataSize(a);
	data = getSignalData();
	SIGNAL.CalculateFFT(data);
	write_adc(data, b);

}