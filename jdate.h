#ifndef _JDATE_H
#define _JDATE_H

const char *program_name = NULL;

#include "helper.h"
#include "about.h"

#define true  1
#define false 0

typedef struct {
	int year,
		month,
		day;
}jDate;


void print_jdate (jDate jd, const char *fmt)
{
	int l = 0;
	char *buf = malloc(sizeof(fmt) * 10);
	
	buf[0] = '\0';
	
	while (l < strlen(fmt)) {
	
		switch (fmt[l]) {
			case 'd':
				buf = _strconcat(buf, _inttostr(jd.day));
				break;
				
			case 'm':
				buf = _strconcat(buf, _inttostr(jd.month));
				break;
				
			case 'y':
				buf = _strconcat(buf, _inttostr(jd.year));
				break;
				
			case 'j':
				break;
				
			case 'u':
				break;
				
			case 'U':
				break;
				
			default:
				buf = _append(buf, fmt[l]);
				break;
		}
		l++;
	}
	
	puts(buf);
}


jDate jalali_to_gregorian(int j_y, int j_m, int j_d)
{
	int i;
	int g_days_in_month[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
	int j_days_in_month[] = {31, 31, 31, 31, 31, 31, 30, 30, 30, 30, 30, 29};
	int jy = j_y - 979;
	int jm = j_m - 1;
	int jd = j_d - 1;

	int j_day_no = 365 * jy + _div(jy, 33) * 8 + _div(jy % 33 + 3, 4);
	for (i = 0; i < jm; ++i) {
		j_day_no += j_days_in_month[i];
	}

	j_day_no += jd;

	int g_day_no = j_day_no + 79;

	int gy = 1600 + 400 * _div(g_day_no, 146097);
	g_day_no = g_day_no % 146097;

	int leap = true;
	if (g_day_no >= 36525) {
		g_day_no--;
		gy += 100 * _div(g_day_no,  36524);
		g_day_no = g_day_no % 36524;

		if (g_day_no >= 365) {
			g_day_no++;
		} else {
			leap = false;
		}
	}

	gy += 4 * _div(g_day_no, 1461);
	g_day_no %= 1461;

	if (g_day_no >= 366) {
		leap = false;

		g_day_no--;
		gy += _div(g_day_no, 365);
		g_day_no = g_day_no % 365;
	}

	for (i = 0; g_day_no >= g_days_in_month[i] + (i == 1 && leap); i++) {
		g_day_no -= g_days_in_month[i] + (i == 1 && leap);
	}
	
	int gm = i + 1;
	int gd = g_day_no + 1;
	
	jDate jdate;
	jdate.year  = gy;
	jdate.month = gm;
	jdate.day   = gd;
	
	return jdate;
}


jDate gregorian_to_jalali (int g_y, int g_m, int g_d)
{
	int i;
	int g_days_in_month[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
	int j_days_in_month[] = {31, 31, 31, 31, 31, 31, 30, 30, 30, 30, 30, 29};
	int gy = g_y - 1600;
	int gm = g_m - 1;
	int gd = g_d - 1;

	int g_day_no = 365 * gy + _div(gy + 3, 4) - _div(gy + 99, 100) + _div(gy + 399, 400);

	for (i=0; i < gm; ++i) {
		g_day_no += g_days_in_month[i];
	}


	if (gm > 1 && ((gy % 4 == 0 && gy % 100 != 0) || (gy % 400 == 0))) {
		g_day_no++;
	}

	g_day_no += gd;

	int j_day_no = g_day_no - 79;

	int j_np = _div(j_day_no, 12053);
	j_day_no = j_day_no % 12053;

	int jy = 979 + 33 * j_np + 4 * _div(j_day_no, 1461);

	j_day_no %= 1461;

	if (j_day_no >= 366) {
		jy += _div(j_day_no - 1, 365);
		j_day_no = (j_day_no-1) % 365;
	}

	for (i = 0; i < 11 && j_day_no >= j_days_in_month[i]; ++i) {
		j_day_no -= j_days_in_month[i];
	}

	int jm = i+1;
	int jd = j_day_no + 1;

	jDate jdate;
	jdate.year  = jy;
	jdate.month = jm;
	jdate.day   = jd;

	return jdate;
}

jDate current_jalali_date (void)
{
	char cur_g_year[5],
		 cur_g_month[3],
		 cur_g_day[3];
		 
	time_t time_raw_format;
	struct tm * ptr_time;

	time(&time_raw_format);
	ptr_time = localtime(&time_raw_format);
	
	strftime(cur_g_year, sizeof(cur_g_year), "%Y", ptr_time);
	strftime(cur_g_month, sizeof(cur_g_month), "%m", ptr_time);
	strftime(cur_g_day, sizeof(cur_g_day), "%d", ptr_time);
	
	return gregorian_to_jalali(atoi(cur_g_year), 
							   atoi(cur_g_month),
							   atoi(cur_g_day));
}

#endif //_JDATE_H

