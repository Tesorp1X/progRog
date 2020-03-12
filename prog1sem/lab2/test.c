#include <stdio.h>
#include <string.h>
#include <ctype.h>
#define MAXLENGTH 1025
#define PTRMAXLEN 65

char *strempty(char *str) {
    strcpy(str, "");
    return strcpy(str, "");
}

char isSimpleRE(char *pattern, char **str) {
    printf("Pattern in isSimple RE is \'%s\'\n", pattern);
    while (*pattern) {
        if (!((**str) && (*pattern))) return 0;
        /*if (!((**str) && (*pattern))) {
            printf("%c %c \n", *pattern, **str);
            return 0;
        }*/
        if (isalpha(*pattern)) {
            if (*pattern != **str)
                return 0;
            (*str)++;
            pattern++;
        }
        if (*pattern == '\\') {
            switch (*(++pattern))
            {
            case 'd':
                if (!isdigit(**str))
                    return 0;
                (*str)++;
                pattern++;
                break;
            case 'D':
                if (!isalpha(**str))
                    return 0;
                (*str)++;
                pattern++;
                break;
            default:
                continue;
            }
        }
    }
    return 1;
}

/*Returns pattern pointer shift if true, atherwise return 0.
Pattern pointer should right after '[' symbol.
*/
int isRepeatingRE(char *pattern, char **str) {
    char subpat[PTRMAXLEN] = "";
    int n = 0;
    int pow = 1;
    char *endofnum = pattern;
    while (*endofnum != '*') {
        pow *= 10;
        endofnum++;
    }
    int digits = endofnum - pattern;
    endofnum = NULL;
    while (*pattern != '*') {
        pow /= 10;
        n += (*(pattern) - '0') * pow;
        pattern++;
    }
    printf("n = %d\n", n);
    /*Finding pattern to check.*/
    pattern += 2; //Should be in possition of '*' symbol, so move once to the right twice
    while (*pattern != ')') {
        if (*pattern == 0) break;
        char buff[2];
        buff[0] = *pattern;
        buff[1] = '\0';
        strcat(subpat, buff);
        pattern++;
    }
    printf("Subpattern is - %s\n", subpat);
    /*Trying to find subpat n times in given string*/
    for (int i = 0; i < n; ++i) {
        if (**str == 0) return 0;
        if (!isSimpleRE(subpat, str)) {
            printf("Iterration no. %d\t", i);
            printf("Not simple\t");
            printf("%c\n", **str);
            return 0;
        }
        //(*str)++;
    }
    printf("Subpat len in repeatingre is %d\n", strlen(subpat));
    return digits + strlen(subpat) + 3; // 3 symbols were skiped in pattern durring check
}

char isMatch(char *pattren, char *string) {
    char *str = string;
    char *ptrn = pattren;
    
    char subpat[PTRMAXLEN] = "";
    while (*ptrn) {
        if(isalpha(*ptrn) || *ptrn == '\\' || isdigit(*ptrn)) {
            while (isalpha(*ptrn) || *ptrn == '\\' || isdigit(*ptrn)) {
                if (*ptrn == 0) break;
                char buff[2];
                buff[0] = *ptrn;
                buff[1] = '\0';
                strcat(subpat, buff);
                ptrn++;
            }
            
            char match = isSimpleRE(subpat, &str);
            if (!match) {
                printf("%s - MissMatch\n", subpat);
                return 0;
            }

        }
        if (*ptrn == '[') {
            ptrn++;
            int result = isRepeatingRE(ptrn, &str);
            if (result == 0){
                printf("Not reapiating\n");
                return 0;
            }

            else ptrn += result;
        }
        strempty(subpat);
        //subpat[0] = 0;
        ptrn++;
    }

    if (*ptrn == 0 && *str != 0) {
        printf("%d %c\n", *ptrn, *str);
        return 0;
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

    for (int i = 0; i < n; ++i) {
        fscanf(in, "%s", line);
        printf("%s\n", line);
        if (isMatch(pattern, line)){
            flag = 1;
            fprintf(out, "%d ", i);
        }
        putchar('\n');
    }
    fclose(in);
    if (!flag)
        fprintf(out, "none");
    fclose(out);

    return 0;
}