#include <stdio.h>

unsigned int g_year(unsigned int date)
{
	date = date>>9;
	printf("YEAR is %d\n", date);
	return date;
}

unsigned int g_month(unsigned int date)
{
	date = date&0x01FF;
	date = date>>4;
	printf("MONTH is %d\n", date);
	return date;
}


unsigned int g_day(unsigned int date)
{
	date = date&0x0F;
	printf("DAY is %d\n", date);
	return date;
}

int main()
{
	unsigned int date = 1032310;

	g_year(date);
	g_month(date);
	g_day(date);

	return 0;
}
