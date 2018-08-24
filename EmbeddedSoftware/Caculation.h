#pragma once
#include <vector>
#define _USE_MATH_DEFINES
#include <math.h>
#include "fftw3.h"
using namespace std;

class Caculation
{
public:
	Caculation();
	~Caculation();

	template<typename T, int N>                   
	static T maxValue(T(&data)[N]);

	template<typename T, int N>                   
	static T minValue(T(&data)[N]);

	template<typename T, int N>                   //����ƽ��ֵ
	static T dcValue(T(&data)[N]);



	template<typename T, int N>                  //����RMS 
	static T caculateRMS(T(&data)[N]); 

	template<typename T, int N>                  //������ֵ 
	static T caculatePKtoPk(T(&data)[N]);


	//���ٸ���Ҷ�任����
	static void FFT(int n, fftw_complex* in, fftw_complex* out);

	//ͨ����ֵ����λ��ȡ
	//����ΪFFT�任������ݳ��ȼ����ݣ�ָ����Ƶ�ʣ����Ϊ�����õ��ķ�ֵ ��  ��λ
	static void caculateAmp_Pha(int n, fftw_complex* in, int frequency, double &amplitude, double &phase);

	template <typename T>                        //����hanning����
	static vector<T> hanning(int N, T amp);
	
	template <typename T>                        //����hamming����
	static vector<T> hamming(int N, T amp);

	//ͳ�Ƽ���
};


#include "Caculation.inl"

