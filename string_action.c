#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include"string_action.h"

char* replace_part(const char* str, const char* old, const char* newStr) {
    char* result;
    int i, count = 0;
    int newLen = strlen(newStr);
    int oldLen = strlen(old);
    // Count occurrences of old substring
    for (i = 0; str[i] != '\0'; ) {
        if (strstr(&str[i], old) == &str[i]) {
            count++;
            i += oldLen;
        } else {
            i++;
        }
    }
    // Allocate memory for new string
    result = (char*)malloc(strlen(str) + count * (newLen - oldLen) + 1);
    if (!result) return NULL;
    i = 0;
    while (*str) {
        if (strstr(str, old) == str) {
            strcpy(&result[i], newStr);
            i += newLen;
            str += oldLen;
        } else {
            result[i++] = *str++;
        }
    }
    result[i] = '\0';
    return result;
}