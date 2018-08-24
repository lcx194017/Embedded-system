
Caculation::Caculation()
{
}

Caculation::~Caculation()
{
}

/************************************************************************/
/*�����������ݵ����ֵ                                                  */
/************************************************************************/
template<typename T, int N>
T Caculation::maxValue(T(&data)[N])
{
	if (0 == N) return 0;
	T max = data[0];
	for (int i = 1; i < N; i++)
		if (max < data[i])
			max = data[i];
	return max;
}

/************************************************************************/
/*�����������ݵ���Сֵ                                                  */
/************************************************************************/
template<typename T, int N>
T Caculation::minValue(T(&data)[N])
{
	if (0 == N) return 0;
	T min = data[0];
	for (int i = 1; i < N; i++)
		if (min > data[i])
			min = data[i];
	return min;
}

/************************************************************************/
/*�����������ݵ�ƽ��ֵ                                                  */
/************************************************************************/
template<typename T, int N>
T Caculation::dcValue(T(&data)[N])
{
	if (0 == N) return 0;
	T sum = 0;
	for (int i = 0; i < N; i++)
		sum += data[i];
	return sum / N;
}


/************************************************************************/
/* ������������RMS                                                      */
/************************************************************************/
template<typename T, int N>
T Caculation::caculateRMS(T(&data)[N])
{
	if (0 == N) return 0;
	T fSum = 0;
	for (int i = 0; i < N; i++)
		fSum += data[i] * data[i];
	return sqrt(fSum / N);
}

/************************************************************************/
/* �����������ݷ��ֵ                                                   */
/************************************************************************/
template<typename T, int N>
T Caculation::caculatePKtoPk(T(&data)[N])
{
	if (0 == N) return 0;
	T min = data[0];
	T max = data[0];
	for (int i = 1; i < N; i++)
	{
		if (data[i] < min) min = data[i];
		if (data[i] > max) max = data[i];
	}
	return max - min;
}

/************************************************************************/
/* һά���ݵĿ��ٸ���Ҷ�任                                             */
/************************************************************************/
void Caculation::FFT(int n, fftw_complex* in, fftw_complex* out)
{
	if (in == NULL || out == NULL) return;
	fftw_plan p;
	p = fftw_plan_dft_1d(n, in, out, FFTW_FORWARD, FFTW_ESTIMATE);
	fftw_execute(p);
	fftw_destroy_plan(p);
	fftw_cleanup();
}

//************************************
// Method:    caculateAmp_Pha
// FullName:  Caculation::caculateAmp_Pha
// Access:    public static 
// Returns:   void
// Qualifier:
// Parameter: int n
// Parameter: fftw_complex * in
// Parameter: int frequency
// Parameter: double & amplitude
// Parameter: double & phase
// ���������Ǽ����ض�Ƶ�ʵķ�ֵ����λ��ԭ�����������Ǵ���һ���ض���Ƶ�ʣ�Ȼ���ڸ�����Ƶ�����ҷ�Χ���ҷ�ֵ����λ
// Ŀǰ�ĺ���ʵ���Ǽ���FFT�任���ض���ķ�ֵ����λ
// Ȼ����һ���ط���Ҫ�޸ģ�������Ƶ�ʺ�FFT�任�������
//************************************
void Caculation::caculateAmp_Pha(int n, fftw_complex* in, int frequency, double &amplitude, double &phase)
{
	int  index = frequency;
	amplitude = 2 * sqrt((in[index][0] / n) * (in[index][0] / n) + (in[index][1] / n) * (in[index][1] / n));
	phase = 180 * atan(in[index][1] / in[index][0]) / M_PI;
}

/************************************************************************/
/* ����hanning����                                                      */
/************************************************************************/
template <typename T>                        
vector<T> Caculation::hanning(int N, T amp)
{
	vector<T> win(N);

	for (int i = 0; i < (N + 1) / 2; ++i)
	{
		win[i] = amp * T(0.5 - 0.5*cos(2 * M_PI*i / (N - 1)));
		win[N - 1 - i] = win[i];
	}

	return win;
}


/************************************************************************/
/* ����hamming����                                                      */
/************************************************************************/
template <typename T>                    
vector<T> Caculation::hamming(int N, T amp)
{
	vector<T> win(N);

	for (int i = 0; i < (N + 1) / 2; ++i)
	{
		win[i] = amp * T(0.54 - 0.46*cos(2 * M_PI*i / (N - 1.0)));
		win[N - 1 - i] = win[i];
	}

	return win;
}