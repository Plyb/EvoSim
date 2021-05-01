#ifndef CONSUMER_PRODUCER_QUEUE_H
#define CONSUMER_PRODUCER_QUEUE_H

#include <queue>
#include <semaphore>

template <class T>
class ConsumerProducerQueue {
public:
	ConsumerProducerQueue<T>();

	void push(T item);
	T pop();
private:
	std::queue<T> internalQueue;
	sem_t mutex;
};

#endif // !CONSUMER_PRODUCER_QUEUE_H


