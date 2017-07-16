/**
 * Created by suli on 7/16/17.
 */

#ifndef NOCOREDUMP_LOG_H
#define NOCOREDUMP_LOG_H
#include <stdlib.h>
#include <stdio.h>

#define INFO 0
#define WARNING 1
#define ERROR 2
#define LOG(LEVEL, fmt, ...)\
    do {\
        if (INFO == LEVEL)\
            fprintf(stdout, "NOTICE:[%s]:[%d]:"fmt, __FILE__, __LINE__ , ##__VA_ARGS__);\
        else if (WARNING == LEVEL)\
            fprintf(stdout, "WARNING:[%s]:[%d]:"fmt, __FILE__, __LINE__ , ##__VA_ARGS__);\
        else if (ERROR == LEVEL)\
            fprintf(stderr, "ERROR:[%s]:[%d]:"fmt, __FILE__, __LINE__ , ##__VA_ARGS__);\
    } while(0)


#endif //NOCOREDUMP_LOG_H
