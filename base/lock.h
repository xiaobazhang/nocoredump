/**
 * Created by suli on 7/16/17.
 */

#ifndef NOCOREDUMP_LOCK_H
#define NOCOREDUMP_LOCK_H
#include <unistd.h>
#include <pthread.h>
#include "nocopy.h"

class SpinLock :public NonCopy{
 public:
	explicit SpinLock(bool share = false){
		if(share){
			pthread_spin_init(&lock_,PTHREAD_PROCESS_SHARED);
		} else{
			pthread_spin_init(&lock_,PTHREAD_PROCESS_PRIVATE);
		}
	}

	~SpinLock(){
		pthread_spin_destroy(&lock_);
	}

	bool Lock(){
		pthread_spin_lock(&lock_);
		return true;
	}

	bool TryLock(){
		return pthread_spin_trylock(&lock_) == 0;
	}

	bool UnLock(){
		pthread_spin_unlock(&lock_);
		return true;
	}

 private:
	pthread_spinlock_t lock_;
};

#endif //NOCOREDUMP_LOCK_H
