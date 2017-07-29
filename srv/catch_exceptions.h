/**
 * Created by suli on 7/16/17.
 */

#ifndef NOCOREDUMP_CATCH_EXCEPTIONS_H
#define NOCOREDUMP_CATCH_EXCEPTIONS_H
#include <map>
#include <signal.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <execinfo.h>
#include <pthread.h>
#include <iostream>
#include <ucontext.h>
#include <stdio.h>
#include "stack_trace.h"
#include "../base/singletonholder.h"

struct StackInfo {
	ucontext_t ucontext;
	bool crash;
	bool trace;
};

typedef std::map<string, StackInfo> StackMap; // 记录当前程序运行状态

static const string core_file = "/home/uonline/";

void SignalHandle(int sig);
class ExceptFrame {
 public:
	ExceptFrame() {
		signal(SIGSEGV, SignalHandle);
		signal(SIGFPE, SignalHandle);
		signal(SIGILL, SignalHandle);
		ClearFlag();
	}
	bool GetCrashFlag() {
		return stack_flag_[try_name].crash;
	}
	ucontext_t &GetStackContext() {
		return stack_flag_[try_name].ucontext;
	}
	bool SetStackName(string name) {
		if (name == "") {
			return false;
		}
		try_name = name;
		StackInfo stack_info;
		ucontext_t uc_t;
		stack_info.crash = false;
		stack_info.trace = false;
		stack_info.ucontext = uc_t;
		return true;
	}

 private:
	StackMap stack_flag_;//记录上下文标记
	string try_name;

};
class ExceptFrameMgr {
 public:
	static ExceptFrame *GetInstance() {
		static SingletonHolder<ExceptFrame> ins;
		return ins.Get();
	}
};

void SignalHandle(int sig) {
	setcontext(&ExceptFrameMgr::GetInstance()->GetStackContext());
}

#define Try(name) \
        ExceptFrameMgr::GetInstance()->try_name = name;\
        getcsontext(&ExceptFrameMgr::GetInstance()->GetStackContext());\
        if(!ExceptFrameMgr::GetInstance()->GetCrashFlag()){ \

#define EndTry \
    } \

#define CatchExceptions \
        if(ExceptFrameMgr::GetInstance()->GetCrashFlag()){ \

#define EndCatch \
        }\

#endif //NOCOREDUMP_CATCH_EXCEPTIONS_H
