#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>
#include <time.h>
#include <string.h>


#include "helper.h"
#include "jdate.h"
#include "about.h"
#include "funcs.h"


char *_format = "%Y-%M-%D";


int main (int argc, char *argv[])
{
	int opt;
	
	const char *short_options = "f:j:g:c:";
	const struct option long_options[] = {
		{ "help",			0, NULL, 'h' },
		{ "format",			1, NULL, 'f' },
		{ "to-jalali",		1, NULL, 'j' },
		{ "to-gregorian",	1, NULL, 'g' },
		{ "compare",		1, NULL, 'c' },
		{ "version",		0, NULL, 'v' },
		{  NULL,			0, NULL,  0  }
	};
	
	jDate _jdate = get_cur_jdate();
	
	while ((opt = getopt_long(argc, argv, short_options, long_options, NULL)) != -1) {
		switch (opt) {
			//--help
			case 'h':
				print_usage(stdout, EXIT_SUCCESS);
				break;
				
			//--format
			case 'f':
				_format = argv[optind - 1];
				break;
				
			//--to-jalali
			case 'j':
				_jdate = gregorian_to_jalali(atoi(_substring(argv[optind - 1], 0, 4)),
										     atoi(_substring(argv[optind - 1], 5, 2)),
											 atoi(_substring(argv[optind - 1], 8, 2)));
				break;
				
			//--to-gregorian
			case 'g':
				_jdate = jalali_to_gregorian(atoi(_substring(argv[optind - 1], 0, 4)),
										     atoi(_substring(argv[optind - 1], 5, 2)),
											 atoi(_substring(argv[optind - 1], 8, 2)));
				break;
				
			//--compare
			case 'c':
				_jdate = compare_jdate(argv[optind - 1]);
				break;
				
			//--version
			case 'v':
				print_version();
				break;
				
			default:
				print_usage(stderr, EXIT_FAILURE);
				exit(EXIT_SUCCESS);
				break;
		}
	}
	
	print_jdate(_jdate, _format);
	
	if (optind < argc) {
		fprintf(stderr, "Expected argument after options.\n");
		exit(EXIT_FAILURE);
	}

	
	return EXIT_SUCCESS;
}

