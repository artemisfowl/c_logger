#include "../inc/log.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

/**
 * DONE: Add the respective function as present in the header file in this
 * source file
 * DONE: Write the log_level_information(__FILE__, __LINE__, __FUNCTION__)
 * as a formatted
 * string using the log_append_file function
 * DONE: Implement variadic function for formatted string input to the log
 * write function
 */

static char *lf;                        /* log filename */
static enum log_level l;                /* log level */
static bool linit = FALSE;		/* logging initialised or not */

static const char *log_get_ll_identifier(enum log_level ll) {
        /* this function will be returning the log level identifier that
         * will be written into the log file */
        switch (ll) {
                case DEBUG:
                        return "DEBUG : ";
                case WARN:
                        return "WARN  : ";
                case ERROR:
                        return "ERROR : ";
                case INFO:
                        return "INFO  : ";
        }
        return NULL;
}

static void log_malloc(const char *f) {
        unsigned long len = strlen(f) + 1;
        lf = (char *)malloc(len * sizeof(char));
        strncpy(lf, f, len);
        LOGFD("Log filename : %s", lf);
}

static char *get_local_time(void)
{
	time_t rawtime;
	struct tm *time_info;

	time(&rawtime);
	time_info = localtime(&rawtime);


	/* there seems to be a newline appended at the end of the string */
	/* remove this newline from the string */
	char *ltime = asctime(time_info);
	char *index = strchr(ltime, '\n');
	if (index)
		*index = '\0';
	return ltime;
}

void log_init(const char *f, enum log_level ll) {
        if (!ll)
                return;
        else
                l = ll;
        if (!f)
                return;
        else
                log_malloc(f);
	linit = TRUE;
}

void log_write_fmt(const char *fmt, const char *fi, const char *fu, long ln,
                int ll, ...) {
        if (!fmt)
                return;                 /* nothing to log */
	if (!linit)
		return;			/* not initialised, nothing to log */
        va_list vp;                     /* variable argument pointer */
        va_start(vp, ll);               /* point vp to the first parameter */
        FILE *f = fopen(lf, "a+");      /* if file present - append,
                                                else create & write */

        /*  first the usual stuff from the LOG_STR will be printed out */
        if (ll >= (int)l) {
                fprintf(f, LOG_STRF, get_local_time(),
				log_get_ll_identifier(ll), fi, fu, ln);
		fputc(' ', f);
		/* then the next formatted string will be written to the file */
		vfprintf(f, fmt, vp);   /* send in the argument pointer
					   for writing */
		fputc('\n', f);         /* as a precaution */
	}

        fclose(f);                      /* close the file */
        va_end(vp);                     /* for portability purposes */
}

void log_free_lf(void) {
        free(lf);
}

