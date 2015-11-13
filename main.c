#include <stdio.h>
#include <stdlib.h>
#include "identity.c"
#include "hush.c"

int main(){

    int cmd;
    int choice;

    printf("#####################################\n");
    printf("# 1. Save in Binary Tree form       #\n");
    printf("# 2. Save in Chain Hashing form     #\n");
    printf("# 3. Exit                           #\n");
    printf("#####################################\n");
    printf("Enter your choice: ");

    switch(cmd){
        case 1:
            printf("#####################################\n");
            printf("# 1. Sort by identity number        #\n");
            printf("# 2. Sort by grade                  #\n");
            printf("# 3. Return to previous menu        #\n");
            printf("#####################################\n");
            printf("Enter your choice: ");

            switch(choice){
                case 1:
                    //identity();
                    break;

                case 2:
                    //grade();
                    break;

                case 3:
                    break;
            }

        case 2:
            //hush();
            break;

        case 3:

            return 0;

    }

    return 0;
}
