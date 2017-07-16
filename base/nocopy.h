/**
 * Created by suli on 7/16/17.
 */

#ifndef NOCOREDUMP_NOCOPY_H
#define NOCOREDUMP_NOCOPY_H
#include <iostream>
/**
 * @brief
 * 不可进行拷贝
 */
class NonCopy {
 protected:
	NonCopy() {
	}

	virtual ~NonCopy() {
	}

 private:
	NonCopy(const NonCopy &) {
	}

	const NonCopy &operator=(const NonCopy &) {
		return *this;
	}
};

#endif //NOCOREDUMP_NOCOPY_H
