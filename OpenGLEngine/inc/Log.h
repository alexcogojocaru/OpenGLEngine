#pragma once

#include <stdio.h>

#define __FILENAME__ (strrchr(__FILE__, '\\') ? strrchr(__FILE__, '\\') + 1 : __FILE__)

#define LOG_TRACE_TAG	"TRACE"
#define LOG_ERROR_TAG	"ERROR"
#define LOG_WARNING_TAG "WARNING"

#define LOG(logTag, format, ...) { \
	printf("[%s] [%s] [%s] [%d] " format "\n", logTag, __FILENAME__, __FUNCTION__, __LINE__, ##__VA_ARGS__); \
}

#define LOG_ERROR(format, ...) { \
	LOG(LOG_ERROR_TAG, format, __VA_ARGS__); \
}

#define LOG_WARNING(format, ...) { \
	LOG(LOG_WARNING_TAG, format, __VA_ARGS__); \
}

#define LOG_TRACE(format, ...) { \
	LOG(LOG_TRACE_TAG, format, __VA_ARGS__); \
}