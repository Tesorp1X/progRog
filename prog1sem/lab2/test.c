#include <stdio.h>
#include <string.h>
#include <ctype.h>
#define MAXLENGTH 1024
#define PTRMAXLEN 64

int isRepeatingRE(char *pattern, char **str) {
    
}

char isSimpleRE(char *pattern, char **str) {
    while (*pattern) {
        if (!(**str)) return 0;
        if (isalpha(*pattern)) {
            if (*pattern != **str)
                return 0;
            *str++;
            pattern++;
        }
        if (*pattern == '\\') {
            switch (*(++pattern))
            {
            case 'd':
                if (!isdigit(**str))
                    return 0;
                *str++;
                pattern++;
                break;
            case 'D':
                if (!isalpha(**str))
                    return 0;
                *str++;
                pattern++;
                break;
            default:
                continue;
            }
        }
    }
    return 1;
}

char isMatch(char *pattren, char *string) {
    char *str = string;
    char *ptrn = pattren;
    char subpat[PTRMAXLEN] = "";

    while (*ptrn) {
        int ptrdiff = 0;
        if(isalpha(*ptrn) || *ptrn == '\\' || isdigit(*ptrn)) {
            while (isalpha(*ptrn) || *ptrn == '\\' || isdigit(*ptrn)) {
                char buff[2];
                buff[0] = *ptrn;
                buff[1] = '\0';
                strcat(subpat, buff);
                ptrn++;
            }
            
            char match = isSimpleRE(subpat, &str);
            if (!match) return 0;

        }
        ptrn += ptrdiff;
    }
    return 1;
}

int main() {
    FILE *in, *out;
    char line[MAXLENGTH];
    char pattern[PTRMAXLEN];
    int n;
    int flag = 0;


    in = fopen("input.txt", "r");
    out = fopen("output.txt", "w+");
    fscanf(in, "%s", pattern);
    fscanf(in, "%d", &n);
    fclose(in);

    for (int i = 0; i < n; ++i) {
        flag = 0;
        fscanf(in, "%s", line);
        if (isMatch(pattern, line)){
            flag = 1;
            fprintf(out, "%d ", i);
        }
    }
    
    if (!flag)
    fprintf(out, "none");
    fclose(out);

    return 0;
}