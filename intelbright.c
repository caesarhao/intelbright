#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_BRIGHT	"/sys/class/backlight/intel_backlight/max_brightness"
#define GSET_BRIGHT	"/sys/class/backlight/intel_backlight/brightness"

int isint(char *str){
	char *c = NULL;
	for (c = str; '\0' != *c && '\n' != *c; c++){
		if ('-' == *c){
			continue;
		}
		else if ('0' > *c || '9' < *c){
			return -1;
		}
		else{
			continue;
		}
	}
	return 0;
}

int pows(int base, int po){
	int resu = 1;
	int i = 0;
	for (i = 0; i < po; i++){
		resu *= base;
	}
	return resu;
}

int toint(char *str){
	int resu = 0;
	int len = strlen(str);
	int i = 0;
	if ('-' == *str){
		len--;
	}
	for (i = 0; i < len; i++){
		resu += pows(10, i) * (*(str+len-i-1)-'0');
	}
	if ('-' == *str){
		resu = 0 - resu;
	}
	return resu;
}



int main(int argc, char *argv[]){
	FILE *fi, *fo;
	int bright, maxbright;
	if (argc < 2){ // get current brightness.
		fi = fopen(GSET_BRIGHT, "r");
		fscanf(fi, "%d", &bright);
		fclose(fi);
		printf("%d\n", bright);
		return bright;
	}
	if (argc == 2){
		fi = fopen(MAX_BRIGHT, "r");
		fscanf(fi, "%d", &maxbright);
		fclose(fi);
		if (0 == strcmp(argv[1], "-m")){
			printf("%d\n", maxbright);
			return maxbright;
		}
		else if (0 == isint(argv[1])){
			bright = toint(argv[1]);
			if (bright > maxbright)
				return -1;

			fo = fopen(GSET_BRIGHT, "w");
			fprintf(fo, "%d", bright);
			fclose(fo);
			printf("%d\n", bright);
			return bright;
		}
		else{
			return 0;
		}
	}
	return 0;
}
