/**
 * Created by suli on 7/16/17.
 */

#ifndef NOCOREDUMP_STACK_TRACE_H
#define NOCOREDUMP_STACK_TRACE_H
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include "../base/lock.h"
#include "../base/log.h"

using namespace std;

class StackTrace {
 public:
	StackTrace():file_(NULL) {
	}
	~StackTrace() {
		fclose(file_);
	}
	bool SetParam(string file_path, int length = 200) {
		name_ = file_path;
		size_ = length;
		file_ = fopen(file_path.c_str(), "w");
		if (file_ == NULL) {
			LOG(INFO,"Create file error,file name = %s!!",file_path.c_str());
			return false;
		}
		fd = fileno(file_);
		fseek(file_, 0, SEEK_END);
		return true;
	}
	bool GetStackTraceInfo() {
		void **mes_array = new void *[size_];
		size_t trace_size = 0;
		trace_size = backtrace(mes_array, size_);
		backtrace_symbols_fd(mes_array, trace_size,fd);
		delete[] mes_array;
		mes_array = NULL;
		return true;
	}
 private:
	string name_;
	int size_;
	FILE* file_;
	int fd;
};



#endif //NOCOREDUMP_STACK_TRACE_H
