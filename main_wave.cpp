#include "wave.h"
#include <iostream>
using std::cout;
using std::cin;
int main()
{
	vector <complex<float>> 
	unsigned int a;
	float b;
	cout << "������� � ����� ������: ������� �������������, ���������� �������� (��� �������� �� ��������� = 48���; =512;) \n";
	cin >> a; 
	cin >> b;
	Wave SIGNAL(a,b);
	SIGNAL.setDataSize(a);
	SIGNAL.GenerateSignal();
	SIGNAL.CalculateFFT();


}