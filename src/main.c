/**
 * @file main.c
 * @author sb
 */

#include "../inc/log.h"

/*
 * DONE : Add a makefile script to this project
 * DONE : Profile the output program with valgrind
 * DONE : Write a few lines in the main program
 * DONE : Add the logging priority to the log writing function
 * TODO : Add local time stamp to the log writing function
 */

int main(void)
{
	/* first init the logger module */
	LOG_INIT(DEBUG);

	/* Debug log */
	LOGD("This is the debug log");

	/* Warning log */
	LOGW("This is the warning log");

	/* Error log */
	LOGE("This is the error log");

	/* Info log */
	LOGI("This is the info log");

	/* free the resources */
	log_free_lf();
	return 0;
}
