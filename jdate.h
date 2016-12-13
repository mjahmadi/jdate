#ifndef _JDATE_H
#define _JDATE_H

#define true  1
#define false 0

typedef struct {
	int year,
		month,
		day;
}jDate;


int _div (int a, int b)
{
	return ((int)(a / b));
}


char *_substring(char s[], int p, int l) {
   int c = 0;
   char *sub =  malloc(strlen(s) + 1);
 
   while (c < l) {
      sub[c++] = s[p + c - 1];
   }
   
   sub[c] = '\0';
   
   return sub;
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

#endif //_JDATE_H

