#ifndef _FUNCS_H
#define _FUNCS_H


jDate get_cur_gdate (void)
{
	jDate gd;
	gd.day   = malloc(sizeof(char*));
	gd.month = malloc(sizeof(char*));
	gd.year  = malloc(sizeof(char*));	

	time_t rawtime = time(NULL);
	
	strftime(gd.day,   sizeof(gd.day),   "%d", localtime(&rawtime));
	strftime(gd.month, sizeof(gd.month), "%m", localtime(&rawtime));
	strftime(gd.year,  sizeof(gd.year),  "%Y", localtime(&rawtime));
	
	return gd;
}


jDate get_cur_jdate (void)
{
	jDate jd;
	jd.day   = malloc(sizeof(char*));
	jd.month = malloc(sizeof(char*));
	jd.year  = malloc(sizeof(char*));
	
	jd = get_cur_gdate();
	
	return gregorian_to_jalali(atoi(jd.year), atoi(jd.month), atoi(jd.day));
}


void print_jdate (jDate jd, char *fmt)
{
	int l = 0;
	char *buf = malloc(sizeof(char) * 4096);
	
	buf[0] = '\0';
	
	while (l < strlen(fmt)) {
	
		if (fmt[l] == '%') {
			switch (fmt[l+1]) {
				case 'd':
					buf = _strconcat(buf, jd.day);
					break;
				
				case 'D':
					if (atoi(jd.day) < 10) {
						buf = _append(buf, '0');
					}
				
					buf = _strconcat(buf, jd.day);
					break;
				
				case 'm':
					buf = _strconcat(buf, jd.month);
					break;
				
				case 'M':
					if (atoi(jd.month) < 10) {
						buf = _append(buf, '0');
					}
				
					buf = _strconcat(buf, jd.month);
					break;
				
				case 'y':
					if (atoi(jd.year) < 10) {
						buf = _append(buf, '0');
					}
	
					buf = _strconcat(buf, _substring(jd.year, 2, 2));
					break;
				
				case 'Y':
					buf = _strconcat(buf, jd.year);
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
			
		} else {
			buf = _append(buf, fmt[l]);
		}
		
		l++;
	}
	
	puts(buf);
}


jDate compare_jdate (char *str)
{
	jDate j;
	
	int tmp_year1, tmp_year2,
	tmp_month1, tmp_month2,
	tmp_day1, tmp_day2;
	
	boolean compare_condition = false;
	
	tmp_year1  = atoi(_substring(str,  0, 4));
	tmp_month1 = atoi(_substring(str,  5, 2));
	tmp_day1   = atoi(_substring(str,  8, 2));
	
	tmp_year2  = atoi(_substring(str, 11, 4));
	tmp_month2 = atoi(_substring(str, 16, 2));
	tmp_day2   = atoi(_substring(str, 19, 2));

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
		j.year  = _inttostr(tmp_year1);
		j.month = _inttostr(tmp_month1);
		j.day   = _inttostr(tmp_day1);
	} else {
		j.year  = _inttostr(tmp_year2);
		j.month = _inttostr(tmp_month2);
		j.day   = _inttostr(tmp_day2);
	}
	
	return j;
}

#endif //_FUNCS_H

