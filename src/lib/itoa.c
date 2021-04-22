/*
 * lib/itoa.c
 *
 * @author: Miguel Angel Garcia
 * @date: 2007-02-05
 */

/*
 * itoa K&R implementation
 */

void itoa(int n, char *s) {
	int i, sign;
	unsigned int tmp;
	
	if(n < 0) {
		tmp = -n;
		sign = -1;
	}
	else {
		tmp = n;
		sign = 0;
	}
		
	i = 0;
	do  {
		s[i++] = tmp % 10 + '0';
	} while((tmp /=10) > 0);
	
	if(sign < 0)
		s[i++] = '-';
	
	s[i] = '\0';

	reverse(s);
}
