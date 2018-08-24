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

	template<typename T, int N>                   //计算平均值
	static T dcValue(T(&data)[N]);



	template<typename T, int N>                  //计算RMS 
	static T caculateRMS(T(&data)[N]); 

	template<typename T, int N>                  //计算峰峰值 
	static T caculatePKtoPk(T(&data)[N]);


	//快速傅里叶变换函数
	static void FFT(int n, fftw_complex* in, fftw_complex* out);

	//通道幅值和相位提取
	//输入为FFT变换后的数据长度及数据，指定的频率，输出为计算后得到的幅值 和  相位
	static void caculateAmp_Pha(int n, fftw_complex* in, int frequency, double &amplitude, double &phase);

	template <typename T>                        //生成hanning窗口
	static vector<T> hanning(int N, T amp);
	
	template <typename T>                        //生成hamming窗口
	static vector<T> hamming(int N, T amp);

	//统计计算
};


#include "Caculation.inl"

