/**
 * Created by suli on 7/16/17.
 */

#ifndef NOCOREDUMP_CATCH_EXCEPTIONS_H
#define NOCOREDUMP_CATCH_EXCEPTIONS_H
#include <map>
#include <stdio.h>
#include <signal.h>
#include <sys/ucontext.h>
#include <ucontext.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <execinfo.h>
#include <pthread.h>
#include <iostream>
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
	}
	inline bool GetCrashFlag() {
		return stack_flag_[try_name].crash;
	}
	inline bool SetCrashFlag(bool flag) {
		stack_flag_[try_name].crash = flag;
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
		stack_flag_[name] = stack_info;
		return true;
	}

 public:
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
	ExceptFrameMgr::GetInstance()->SetCrashFlag(true);
	setcontext(&ExceptFrameMgr::GetInstance()->GetStackContext());
}

#define Try(name) \
        ExceptFrameMgr::GetInstance()->SetStackName(name);\
        getcontext(&ExceptFrameMgr::GetInstance()->GetStackContext());\
        if(!ExceptFrameMgr::GetInstance()->GetCrashFlag()){ \

#define EndTry \
    } \

#define CatchExceptions \
        if(ExceptFrameMgr::GetInstance()->GetCrashFlag()){ \
          ExceptFrameMgr::GetInstance()->SetCrashFlag(false);\

#define EndCatch \
        }\


#endif //NOCOREDUMP_CATCH_EXCEPTIONS_H
