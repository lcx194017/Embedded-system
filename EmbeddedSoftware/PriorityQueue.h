#pragma once
#include <queue>
#include <mutex>
using namespace std;

/****************************************************************************************/
/*
�ļ�����: PriorityQueue.h
��    ��: �̰߳�ȫ�����ȼ����У�ϵͳ�д��ڶ���̷߳���ȫ�ֱ�������������Խ���mutex��ԭ�еĶ���lock,
		  ʹ���ܹ��������ʣ������ȼ�����ʹ����template����Ӷ�����Ҫ�� comparable
��    ��: lcx
С    ��: 
��ϵ��ʽ: liu.changxin@qq.com
��������: 2018/08/17 15:02
�� �� ��: V0.0.0.1
*/
/****************************************************************************************/

template<class T>
class PriorityQueue
{
public:
	PriorityQueue();
	~PriorityQueue();
	T pop();
	void push(T t);
	bool empty();

private:
	priority_queue<T> queue;              //���ȼ�����
	mutex mt;                             //����
};

template<class T>
PriorityQueue<T>::PriorityQueue()
{
}

template<class T>
PriorityQueue<T>::~PriorityQueue()
{
}

template<class T>
bool PriorityQueue<T>::empty()
{
	return queue.empty();
}

//�����ȼ����������Ԫ��
template<class T>
void PriorityQueue<T>::push(T t)      
{
	mt.lock();
	queue.push(t);
	mt.unlock();
}

//�����ȼ�������ȡ��Ԫ��
template<class T>
T PriorityQueue<T>::pop()
{
	mt.lock();
	T result = queue.top();
	queue.pop();
	mt.unlock();
	return result;
}

