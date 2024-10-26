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
	/* fixme: first need to change the log_init macro call */
	/* first init the logger module */
	init(DEBUG);
	log_set_stream(TRUE, TRUE);

	/* Debug log */
	debug("This is the debug log");

	/* Warning log */
	warning("This is the warning log");

	/* Error log */
	error("This is the error log");

	/* Info log */
	info("This is the info log");

	/* free the resources */
	log_free_lf();
	return 0;
}
