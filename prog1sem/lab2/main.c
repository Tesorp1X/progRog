#include <stdio.h>
#include <string.h>
#include <ctype.h>
#define MAXLENGTH 1025
#define PTRMAXLEN 65
#define PointerShift 1

char *strempty(char *str) {
    char *temp = strcpy(str, "");
    return temp;
}

void incrPtr(int *ptrDiff, char **str, char **patr) {
    (*ptrDiff)++;
    (*str)++;
    (*patr)++;
    return;
}

void makeSubpat(char *subpat, char **pattern, char stopSymb) {
    int index = 0;
    while (**pattern != stopSymb) {
        subpat[index++] = **pattern;
        (*pattern)++;
    }
    subpat[index] = '\0';
    return;
}

char isTildaRE(char *pattern, char **str) {
    if (**str == *pattern)
        return 0;
    (*str)++;
    return 1;
}

char isSimpleRE(char *pattern, char **str, int *ptrDiff) {   //PtrDiff in str for Kleene star
    while (*pattern) {
        if (!(**str)) return 0;
        if (isalpha(*pattern) || isdigit(*pattern)) {
            if (*pattern != **str)
                return 0;
            incrPtr(ptrDiff, str, &pattern);
        }
        if (*pattern == '\\') {
            switch (*(++pattern))
            {
            case 'd':
                if (!isdigit(**str))
                    return 0;
                incrPtr(ptrDiff, str, &pattern);
                break;
            case 'D':
                if (!isalpha(**str))
                    return 0;
                incrPtr(ptrDiff, str, &pattern);
                break;
            default:
                continue;
            }
        }
    }
    return 1;
}

/* Loking after Kleene construction for the same subpattern.
    R - any valid subpattern. <R>*R transforms into <R>*.
*/
char lookafter(char *subpat, char *pattern) {
    char patlen = strlen(subpat);
    pattern += 2 * PointerShift;
    while (*subpat) {
        if (*subpat != *pattern)
            return 0;
        subpat++;
        pattern++;
    }
    return patlen;
}

char isKleeneRE(char *pattern, char **str) {
    char subpat[PTRMAXLEN] = "";
    int PtrDiff = 0;
    makeSubpat(subpat, &pattern, '>');
    while (isSimpleRE(subpat, str, &PtrDiff)) {
        PtrDiff = 0;
    }
    (*str) -= PtrDiff;
    return strlen(subpat) + 2 * PointerShift + lookafter(subpat, pattern);
}

/*Returns pattern pointer shift if true, atherwise return 0.
Pattern pointer should right after '[' symbol.
*/
char isRepeatingRE(char *pattern, char **str) {
    char subpat[PTRMAXLEN] = "";
    int PtrDiff = 0;
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
    /*Finding pattern to check.*/
    pattern += 2 * PointerShift; //To skip '*' and '('
    makeSubpat(subpat, &pattern, ')');
    /*Trying to find subpat n times in given string*/
    for (int i = 0; i < n; ++i) {
        if (**str == 0) return 0;
        if (!isSimpleRE(subpat, str, &PtrDiff)) {
            return 0;
        }
    }

    return digits + strlen(subpat) + 4 * PointerShift; // 4 symbols were skiped in pattern durring check
}

/*Main function for regular expressions. 
If given string is correct by given pattern finction returns 1, otherwise 0.
*/
char isMatch(char *pattren, char *string) {
    char *str = string;
    char *ptrn = pattren;
    int PtrDiff = 0;
    
    char subpat[PTRMAXLEN] = "";
    while (*ptrn) {
        if(isalpha(*ptrn) || *ptrn == '\\' || isdigit(*ptrn)) {
            int index = 0;
            while (isalpha(*ptrn) || *ptrn == '\\' || isdigit(*ptrn)) {
                if (*ptrn == 0) break;
                subpat[index++] = *ptrn;
                ptrn++;
            }
            subpat[index] = '\0';
            char match = isSimpleRE(subpat, &str, &PtrDiff);
            if (!match) {
                return 0;
            }
        }
        if (*ptrn == '[') {
            ptrn++;
            int result = isRepeatingRE(ptrn, &str);
            if (result == 0) {
                return 0;
            }
            else ptrn += result;
        }
        if (*ptrn == '<') {
            ptrn++;
            char result = isKleeneRE(ptrn, &str);
            ptrn += result;
        }
        if (*ptrn == '~') {
            ptrn++;
            if (!isTildaRE(ptrn, &str)){
                return 0;
            }
            ptrn++;
        }
        strempty(subpat);
    }

    if (*ptrn == 0 && *str != 0) {
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
        if (isMatch(pattern, line)){
            flag = 1;
            fprintf(out, "%d ", i);
        }
    }
    fclose(in);
    if (!flag)
        fprintf(out, "none");
    fclose(out);

    return 0;
}
