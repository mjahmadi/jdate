#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <unistd.h>

#include "jdate.h"

int         default_padding  = true;
const char *default_format   = "Y/m/d";
const char *default_timezone = "Asia/Tehran";


void print_error (const char *error_msg, int error_code)
{
	fprintf (stderr, "Error: %d - %s\n", error_code, error_msg);
	exit(error_code);
}


int main (int argc, char *argv[])
{
	int opt;
	
	const char *short_options = "hf:p:j:g:c:";
	const struct option long_options[] = {
		{ "help",			0, NULL, 'h' },
		{ "format",			1, NULL, 'f' },
		{ "no-pad",			0, NULL, 'p' },
		{ "to-jalali",		1, NULL, 'j' },
		{ "to-gregorian",	1, NULL, 'g' },
		{ "compare",		1, NULL, 'c' },
		{ "version",		0, NULL, 'V' },
		{  NULL,			0, NULL,  0  }
	};
	
	int compare_condition;
	int tmp_year1, tmp_year2,
		tmp_month1, tmp_month2,
		tmp_day1, tmp_day2;
		
	jDate jdate;
	
	program_name = argv[0];
	
	while ((opt = getopt_long(argc, argv, short_options, long_options, NULL))
			 != -1) {
		switch (opt) {
			case 'h':
				print_usage(stdout, EXIT_SUCCESS);
				break;
				
			case 'f':
				default_format = argv[optind - 1];
				break;
				
			case 'p':
				default_padding = false;
				break;
				
			case 'j':
				tmp_year1  = atoi(_substring(argv[optind - 1], 0, 4));
				tmp_month1 = atoi(_substring(argv[optind - 1], 5, 2));
				tmp_day1   = atoi(_substring(argv[optind - 1], 8, 2));
				jdate      = gregorian_to_jalali (tmp_year1, tmp_month1, tmp_day1);
				break;
				
			case 'g':
				tmp_year1  = atoi(_substring(argv[optind - 1], 0, 4));
				tmp_month1 = atoi(_substring(argv[optind - 1], 5, 2));
				tmp_day1   = atoi(_substring(argv[optind - 1], 8, 2));
				jdate      = jalali_to_gregorian (tmp_year1, tmp_month1, tmp_day1);
				break;
				
			case 'c':
				tmp_year1  = atoi(_substring(argv[optind - 1], 0, 4));
				tmp_month1 = atoi(_substring(argv[optind - 1], 5, 2));
				tmp_day1   = atoi(_substring(argv[optind - 1], 8, 2));
				
				tmp_year2  = atoi(_substring(argv[optind - 1], 11, 4));
				tmp_month2 = atoi(_substring(argv[optind - 1], 16, 2));
				tmp_day2   = atoi(_substring(argv[optind - 1], 19, 2));
				
				if (tmp_year1 == tmp_year2) {
					if (tmp_month1 == tmp_month2) {
						if (tmp_day1 == tmp_day2) {
							compare_condition = true;
						} else if (tmp_day1 > tmp_day2) {
							compare_condition = true;
						} else if (tmp_day1 < tmp_day2) {
							compare_condition = false;
						}
					} else if (tmp_month1 > tmp_month2) {
						compare_condition = true;
					} else if (tmp_month1 < tmp_month2) {
						compare_condition = false;
					}
				} else if (tmp_year1 > tmp_year2) {
					compare_condition = true;
				} else if (tmp_year1 < tmp_year2) {
					compare_condition = false;
				}
				
				if (compare_condition) {
					jdate.year  = tmp_year1;
					jdate.month = tmp_month1;
					jdate.day   = tmp_day1;
				} else {
					jdate.year  = tmp_year2;
					jdate.month = tmp_month2;
					jdate.day   = tmp_day2;
				}
				
				break;
				
			case 'V':
				print_version();
				break;
				
			default:
				print_usage(stderr, EXIT_FAILURE);
				break;
		}
	}
	
	if (argc <= 1) {
		jdate = current_jalali_date();
	}
	
	print_jdate(jdate, default_format);
	//jDate jd = current_jalali_date();
	//printf("%d", jd.year);
	
	if (optind < argc) {
		fprintf(stderr, "Expected argument after options.\n");
		exit(EXIT_FAILURE);
	}
	
	exit(EXIT_SUCCESS);
}

