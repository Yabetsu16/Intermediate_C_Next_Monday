#include <stdio.h>
#include <time.h>

int february(int year)
{
	if( (year%400)==0 )
		return(29);
	if( (year%100)==0 )
		return(28);
	if( (year%4)==0 )
		return(29);
	return(28);
}

char *ordinal(int v)
{
	if( v==11 || v==12 || v==13 )
		return("th");

	v %= 10;
	if( v==1 )
		return("st");
	if( v==2 )
		return("nd");
	if( v==3 )
		return("rd");
	return("th");
}

int main()
{
	time_t now;
	int months[] = {
		31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31
	};
	char *mnames[] = { "January", "February", "March",
		"April", "May", "June", "July", "August",
		"September", "October", "November", "December"
	};
	char *days[] = { "Sunday", "Monday", "Tuesday",
		"Wednesday", "Thursday", "Friday", "Saturday"
	};
	struct tm *today;
	int monday,mflag;

	time(&now);
	today = localtime(&now);

	printf("Today is %s, %s %d%s, %d\n",
			days[today->tm_wday],
			mnames[today->tm_mon],
			today->tm_mday,
			ordinal(today->tm_mday),
			today->tm_year+1900
		  );

	months[1] = february(today->tm_year+1900);

	monday = ( 1 - today->tm_wday );
	if( monday<1 )
		monday += 7+today->tm_mday;
	else
		monday+=today->tm_mday;

	mflag = today->tm_mon;
	if(monday > months[today->tm_mon])
	{
		monday -= months[today->tm_mon];
		mflag++;
		mflag %= 12;
	}

	printf("Next Monday will be the %d%s of %s\n",
			monday,
			ordinal(monday),
			mnames[mflag]
		  );

	return(0);
}
