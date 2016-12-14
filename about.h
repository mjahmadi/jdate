#ifndef _ABOUT_H
#define _ABOUT_H


void print_version (void)
{
	printf ("jdate 0.0.1\n"
			"Copyright (C) 2016.\n"
			"This is free software; see the source for copying conditions."
			"There is \nNO warranty; not even for MERCHANTABILITY or FITNESS"
			"FOR A PARTICULAR PURPOSE.\n");
			
	printf ("\nWritten by Mohammad Javad Ahmadi.\n");
}


void print_usage (FILE* stream, int exit_code)
{
	if (exit_code == EXIT_SUCCESS) {
		fprintf (stream, "Display persian date in jalali calendar command line tool.\n");
		fprintf (stream, "Usage: %s [OPTION]... [+FORMAT]\n", program_name);
	} else {
		fprintf (stream, "Try '%s --help' for more information.\n", program_name);
	}
	
	if (exit_code == EXIT_SUCCESS) {
		fprintf (stream,
				"  -h   --help          Display this usage information and exit.\n"
				"  -f   --format        Formats output with the given pattern.\n"
				"  -p   --no-pad        Won't pad numeric fields with zero.\n"
				"  -j   --to-jalali     Converts given gregorian date to persian jalali date.\n"
				"  -g   --to-gregorian  Converts given persian jalali date to gregorian date.\n"
				"  -c   --compare       Will compare two different persian jalali date.\n"
				"                       this option returns the bigger date. [YYYY-MM-DD:YYYY-MM-DD]\n"
				"       --version       Output version information and exit.\n\n"
				
				"FORMAT controls the output. Interpreted sequences are:\n"
				"  'a'   locale's abbreviated weekday name.\n"
				"  'A'   locale's full weekday name.\n"
				"  'b'   locale's abbreviated month name.\n"
				"  'B'   locale's full month name.\n"
				"  'd'   day of month (e.g., 14).\n"
				"  'm'   month (01..12).\n"
				"  'Y'   year.\n"
				"  'j'   day of year (001..366).\n"
				"  'u'   day of week (1..7).\n"
				"  'U'   week number of year.\n\n"
				
				"Examples:\n"
				"   To get current persian jalali date issue the following:\n"
				"   $ %s \n\n"
				"   To convert gregorian date to persian jalali date issue the following:\n"
				"   $ %s -g '1395-09-20'\n\n"
				"   To convert persian jalali date to gregorian date issue the following:\n"
				"   $ %s -j '2016-12-20'\n\n"
				"   To compare two different persian jalali date issue the following:\n"
				"   [NOTE: The below command will return the bigger date]\n"
				"   $ %s -c '1395-09-10' '1396-08-06'\n\n"
				"   To change the format of the output issue the following:\n"
				"   $ %s -f 'YY-MM-DD' \n\n", program_name, program_name,
											  program_name, program_name,
											  program_name);
				
		fprintf (stream, "Report bugs to mohammad.j.ahmadi@gmail.com\n"
						 "Project home page: <https://github.com/MJAhmadi/jdate>\n\n");
	}
	
	exit(exit_code);
}

#endif //_ABOUT_H

