/*
 *  itoa.c
 *  IFImageProcessing
 *
 *  Created by Dan JIN on 09-8-19.
 *  Copyright 2009 Weill Medical College of Cornell University. All rights reserved.
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

char *itoa(int value, char *string, int radix)
{
	char temp[33];
	char *tp = temp;
	int i;
	unsigned int v;
	int sign;
	char *sp;
	
	if(radix > 36 || radix <= 1){
		//		set_errno(EDOM);
		return 0;	
	}	
	
	sign = (radix == 10 && value < 0);
	
	if (sign){
		v = -value;
	}
	else{
		v = (unsigned)value;
	}
	
	while(v || tp == temp){
		i = v % radix;
		v = v / radix;
		if(i < 10){
			*tp++ = i + '0'; 	
		}
		else{
			*tp++ = i + '0' - 10; 	
		}
	}
	if(string == 0){
		string = (char *)malloc((tp-temp)+sign+1);	
	}
	sp = string;
	
	if(sign){
		*sp++ = '-';	
	}
	while(tp > temp){
		*sp++ = *--tp;	
	}
	*sp = 0;
	return string;
}

