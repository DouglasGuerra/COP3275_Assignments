/*
* Accumulator Machine
*
* Commands:
*   0 - Exit
*   1 - Add
*   2 - Inc
*   3 - Sub
*   4 - Dec
*   5 - Mult
*   6 - Div
*   7 - Mod
*   8 - Print
*   9 - Reset
*/

#include <stdio.h>

void obtainOperand(int operator, int *operand){
    if(operator == 0 || operator == 2 || operator == 4 || operator == 8 || operator == 9){
        *operand = 0;
    }
    else{
        scanf("%d", operand);
    }
}

int main(){

    int operator = 1, operand = 0, accumulator = 0, temp;

    while(operator != 0){
        //getting command
        scanf("%d", &operator);
        obtainOperand(operator, &operand);
        // printf("operator: %d, operand: %d\n", operator, operand);

        switch(operator){
            case 1:
                accumulator += operand;
                break;

            case 2:
                accumulator++;
                break;

            case 3:
                accumulator -= operand;
                break;

            case 4:
                accumulator--;
                break;

            case 5:
                accumulator *= operand;
                break;

            case 6:
                if(operand != 0){
                    temp = accumulator%operand;
                    accumulator /= operand;
                    if(temp < 0) accumulator -= 1;
                }
                break;

            case 7:
                if(operand != 0){
                    temp = accumulator%operand;
                    if(temp < 0) temp += operand;
                    accumulator = temp;
                }
                break;

            case 8:
                printf("%d\n", accumulator);
                break;

            case 9:
                accumulator = 0;
                break;

            default:
                break;
        }
    }

    return 0;
}
