/**
 * Created by suli on 7/16/17.
 */

#ifndef NOCOREDUMP_CATCH_EXCEPTIONS_H
#define NOCOREDUMP_CATCH_EXCEPTIONS_H
#include <map>
#include <setjmp.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <execinfo.h>
#include <pthread.h>
#include <iostream>
#include "stack_trace.h"
#include "../base/singletonholder.h"


typedef std::map<string, int> PageMap;
typedef std::map<string, bool> TraceFlag;

void SignalHandle(int sig);
class ExceptFrame {
 public:
	ExceptFrame() {
		signal(SIGSEGV, SignalHandle);
		ClearFlag();
	}
	int GetPageFlag(string name)//获取标记
	{
		PageMap::iterator iter = page_flag_.find(name);
		if (iter == page_flag_.end()) {
			int num = page_flag_.size();
			page_flag_[name] = num + 1;
			return num + 1;
		}
		return page_flag_[name];
	}
	int GetPageFlag() {
		if (try_name == "") {
			return -1;
		}
		PageMap::iterator iter = page_flag_.find(try_name);
		if (iter == page_flag_.end()) {
			int num = page_flag_.size();
			page_flag_[try_name] = num + 1;
			return num + 1;
		}
		return page_flag_[try_name];
	}
	bool ClearFlag() {
		bzero(env, sizeof(env));
		return true;
	}

 public:
	PageMap page_flag_;//记录上下文标记
	jmp_buf env;
	int flag_;//标志段,用于跳转代码区间
	string try_name;
	TraceFlag trace_flag_;
};
class ExceptFrameMgr {
 public:
	static ExceptFrame *GetInstance() {
		static SingletonHolder<ExceptFrame> ins;
		return ins.Get();
	}
};

void SignalHandle(int sig) {
	StackTrace stack_trace_;
	string file_name;
	string try_name = ExceptFrameMgr::GetInstance()->try_name;
	TraceFlag::iterator iter = ExceptFrameMgr::GetInstance()->trace_flag_.find(try_name);
	if (iter == ExceptFrameMgr::GetInstance()->trace_flag_.end()) {
		ConfigRead::GetDefault()->Read("corefile", "path", file_name);
		stack_trace_.SetParam("/home/uonline/" + try_name + ".core");
		stack_trace_.GetStackTraceInfo();
		ExceptFrameMgr::GetInstance()->trace_flag_[try_name] = true;
	}
	siglongjmp(ExceptFrameMgr::GetInstance()->env, ExceptFrameMgr::GetInstance()->GetPageFlag());
}

#define Try(name) \
        ExceptFrameMgr::GetInstance()->try_name = name;\
        ExceptFrameMgr::GetInstance()->flag_ = sigsetjmp(ExceptFrameMgr::GetInstance()->env,ExceptFrameMgr::GetInstance()->GetPageFlag());\
        if(ExceptFrameMgr::GetInstance()->flag_ == 0){ \

#define EndTry \
    } \

#define CatchExceptions \
        if(ExceptFrameMgr::GetInstance()->GetPageFlag() == ExceptFrameMgr::GetInstance()->flag_){ \

#define EndCatch \
        }\

#endif //NOCOREDUMP_CATCH_EXCEPTIONS_H
