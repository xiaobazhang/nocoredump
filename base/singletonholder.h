/**
 * Created by suli on 7/16/17.
 */

#ifndef NOCOREDUMP_SINGLETONHOLDER_H
#define NOCOREDUMP_SINGLETONHOLDER_H
#include <iostream>
#include "nocopy.h"
#include "lock.h"

template <class T>
class SingletonHolder : public NonCopy {
 public:
	SingletonHolder():instance_(NULL),exit_release_(true){
	}
	explicit SingletonHolder(bool exit_release):instance_(NULL){
	};
	~SingletonHolder(){
		if(exit_release_){
			if(instance_){
				delete instance_;
			}
		}
	}

	T* Get(){
		if(instance_ == NULL){
			spin_lock_.Lock();
			if(instance_ == NULL){
				T* tmp = new T();
				instance_ = tmp;
			}
			spin_lock_.UnLock();
		}
		return instance_;
	}

	T& operator*(){
		return *Get();
	}

	T* operator->(){
		return Get();
	}

 private:
	SpinLock spin_lock_;
	T* volatile instance_;
	bool exit_release_;
};




#endif //NOCOREDUMP_SINGLETONHOLDER_H
