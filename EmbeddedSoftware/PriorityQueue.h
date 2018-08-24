#pragma once
#include <queue>
#include <mutex>
using namespace std;

/****************************************************************************************/
/*
文件名称: PriorityQueue.h
功    能: 线程安全的优先级队列，系统中存在多个线程访问全局变量的情况，所以借助mutex对原有的队列lock,
		  使起能够并发访问，该优先级队列使用了template，添加对象需要能 comparable
作    者: lcx
小    组: 
联系方式: liu.changxin@qq.com
生成日期: 2018/08/17 15:02
版 本 号: V0.0.0.1
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
	priority_queue<T> queue;              //优先级队列
	mutex mt;                             //互斥
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

//向优先级队列中添加元素
template<class T>
void PriorityQueue<T>::push(T t)      
{
	mt.lock();
	queue.push(t);
	mt.unlock();
}

//从优先级队列中取出元素
template<class T>
T PriorityQueue<T>::pop()
{
	mt.lock();
	T result = queue.top();
	queue.pop();
	mt.unlock();
	return result;
}

