/**
* Code based off of Dr. Fawcett's code from CSE687 code.
*/

#pragma once
#ifndef __BLOCKING_QUEUE_H__
#define __BLOCKING_QUEUE_H__

#include <condition_variable>
#include <mutex>
#include <thread>
#include <queue>

namespace queue {
	template <typename T>
	class BlockingQueue {
	public:
		BlockingQueue() {}

		~BlockingQueue() {
			clear();
		}

		// move constructor
		BlockingQueue(BlockingQueue<T>&& bq) noexcept {
			std::lock_guard<std::mutex> l(mutex_);
			queue_ = bq.queue_;
			while (bq.queue_.size() > 0) {
				bq.queue_.pop();
			}
		};

		// assignment operator
		BlockingQueue<T>& operator=(BlockingQueue<T>&& bq) noexcept {
			if (this == &bq) { return *this; }

			std::lock_guard<std::mutex> l(mutex_);
			queue_ = bq.queue_;
			while (bq.queue_.size() > 0) {
				bq.queue_.pop();
			}
			return *this;
		};

		BlockingQueue(const BlockingQueue<T>&) = delete;
		BlockingQueue<T>& operator=(const BlockingQueue<T>&) = delete;

		T dequeue() {
			std::unique_lock<std::mutex> l(mutex_);
			if (queue_.size() > 0)
			{
				T temp = queue_.front();
				queue_.pop();
				return temp;
			}

			while (queue_.size() == 0) {
				condition_variable_.wait(l, [this]() { return queue_.size() > 0; });
			}
			T temp = queue_.front();
			queue_.pop();
			return temp;
		}

		void enqueue(const T& t) {
			{
				std::unique_lock<std::mutex> l(mutex_);
				queue_.push(t);
			}
			condition_variable_.notify_one();
		};

		T& front() {
			std::lock_guard<std::mutex> l(mutex_);
			if (queue_.size() > 0) {
				return queue_.front();
			}
			throw std::exception("attempt to deQue empty queue");
		};

		void clear() {
			std::lock_guard<std::mutex> l(mutex_);
			while (queue_.size() > 0) {
				queue_.pop();
			}
		};

		size_t size() {
			std::lock_guard<std::mutex> l(mutex_);
			return queue_.size();
		};

	private:
		std::queue<T> queue_;
		std::mutex mutex_;
		std::condition_variable condition_variable_;
	};

}

#endif //!__BLOCKING_QUEUE_H__
