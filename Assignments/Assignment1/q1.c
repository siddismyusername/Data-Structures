#include<stdio.h>

void getString(char str[]){
    printf("Enter a string: ");
    scanf("%s", str);
}

int stringLength(char str[]){
    char *ptr = str;
    // calculate string length
    int length = 0;
    while (*ptr != '\0') {
        ptr++;
        length++;
    }
    return length;
};

void stringCopy(char str1[],char str2[]){
    char *ptr = str1,*p2=str2;
    while(*ptr != '\0'){
        *p2 = *ptr;
        ptr++;
        p2++;
    }
    *p2 = '\0';
};

void stringConcatinate(char str1[],char str2[]){
    char *ptr = str1,*p2;
    ptr = str1;
    p2 = str2;
    while(*ptr!='\0'){
        ptr++;
    }
    while(*p2!='\0'){
        *ptr = *p2;
        p2++;
        ptr++;
    }
    *ptr = '\0';
}

void stringCompare(char str1[],char str2[]){
    char *ptr = str1,*p2;
    ptr = str1;
    p2 = str2;
    while (*ptr != '\0' && *p2 != '\0' && *ptr == *p2) {
        ptr++;
        p2++;
    }
    if (*ptr == '\0' && *p2 == '\0') {
        printf("Strings are the same \n");
    } else {
        printf("Strings are not the same \n");
    }
}

void stringSearch(char str1[],char c){
    int found = 0;
    char *ptr = str1;
    while(*ptr != '\0'){
        if(*ptr == c){
            found = 1;
            break; 
        }
        ptr++;
    }
    
    if (found) {
        printf("Match found \n");
    } else {
        printf("Match not found \n");
    }
}

int main() {
    int choice = 0;
    char str[100],str2[100],s;
    getString(str); 
    while(choice != 7){
        printf("==========");
        printf("==========");
        printf("==========");
        printf("==========\n");
        printf("Select your choice: \n");
        printf("1. Find String length\n");
        printf("2. Create String Copy\n");
        printf("3. Concatinate String\n");
        printf("4. Compare two String\n");
        printf("5. Search the String\n");
        printf("6. Re-enter String\n");
        printf("7. Exit\n");

        printf("\nEnter your choice : ");
        scanf("%d",&choice);
    
        switch (choice){
            case 1:
                //string length
                printf("The length of the string is %d \n",stringLength(str));
                break;

            case 2:
                // string copy 
                stringCopy(str,str2);
                printf("String 2 is  %s \n",str2);
                break;
            case 3:
                //string concatenating
                printf("Enter a string to concatinate to %s : ",str);
                scanf("%s",str2);
                stringConcatinate(str,str2);    
                printf("String after concatenating: %s \n",str);
                break;
            case 4:
                //string comparison
                printf("Enter a string to compare to %s : ",str);
                scanf("%s",str2);
                stringCompare(str,str2);
                break;
            case 5:
                //searching the strings
                printf("Enter a character to search in string : ");
                scanf(" %c",&s);
                stringSearch(str,s);
                break;
            case 6:
                getString(str); 
                break;
            case 7:
                printf("Thankyou!! \n");
                break;
            default:
                printf("Invalid Choice!!! \n");
                break;

        }
    }
    
    printf("Made by Siddharth and Parth");
    return 0;
}