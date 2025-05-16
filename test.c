#include <stdio.h>
#include <string.h>
#define MAX 1000
int main(){
    // char str[MAX][MAX]; This is a 2D array, but we only need a 1D array
    char str[MAX];
    char c; // We need to declare a variable to store the character read from the input
    int length = 0;
    while (length < MAX && (c = getchar()) != EOF){
        c = getchar();
//         if (c == '\n' || c == '\0' ){ // This is not necessary
//             str[i][length] = '\0'; // This is not necessary
// //            printf("%s\n", str[i]); // We need to print the string in reverse order so we can't print it here
//             length = 0;
//             i++;
        // } else{
            str[length] = c;
            length++;
        // }
        // if(c==EOF) break; // This is the correct way to check for EOF but we can also use the while loop condition
    }
   
    // for (int k = i -1; k >= 0; k--){ // We only need to print the string in reverse order so we don't need two loops
        // for (int p = strlen(str[k]) ; p >=0; p--){ // We start from the length of the string - 1 and go to 0
    for (int p = length - 1; p >=0; p--){
        // printf("%c", str[k][p]); // We need to print the character at index p of the string
        printf("%c", str[p]);   
    }
        // printf("\n"); // We don't need to print a new line
   // }

   // Read a line from the input using fgets
    // char str[MAX];
    // fgets(str, MAX, stdin);
    // int length = strlen(str);
    // for (int i = length - 1; i >= 0; i--){
    //     printf("%c", str[i]);
    // }    
    
    return 0;
    
    

}