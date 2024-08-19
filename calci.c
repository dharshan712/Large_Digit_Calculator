#include <stdio.h>
#include <string.h>
#include <math.h>

//Pre-defined Macros
#define Array_size 50

//Global Variables

char input1[Array_size],input2[Array_size];

int input1_length,input2_length;
int iterator_i,iterator_j;

//Function Prototype

void addition(void);
void subtraction(void);
void multiplication(void);
void division_modulus(char);
void removeLeadingZeros(char*);

int main()
{
    printf("/******************************************************************************************************/");
    printf("\n                                   %d - Digit Calculator",Array_size);

    printf("\nInstructions: ");
    printf("\n      1 -> Enter the number in below mentioned format.");
    printf("\n              number1 Operator number2 Eg: 51+24,51-24");
    printf("\n      2 -> This calculator can perform five operations: ");
    printf("\n              i) Addition       ->  '+'");
    printf("\n             ii) Subtraction    ->  '-'");
    printf("\n            iii) Multiplication ->  '*'");
    printf("\n             iv) Division       ->  '/'");
    printf("\n              v) Modulus        ->  '%%'");
    printf("\n      3 -> It can handle Invalid numbers.");
    printf("\n              Eg: If user enters 12a456+987, it says please enter valid number.");
    printf("\n      4 -> It will always prompt for input, if you need to exit just enter exit, it will terminate.");
    printf("\n      5 -> It also removes leading zeros.");
    printf("\n/******************************************************************************************************/");


    char combinedInput[2*Array_size];
    char string_seperate_flag=0,InputOperator,valid_Num=1,exit_flag=0;
    int iterator=0;

    while(!exit_flag)                                             //Checking whether user enters exit by checking its corresponding flag.
    {
        string_seperate_flag=0;
        printf("\n\nCalc> ");
        scanf("%s",combinedInput);

        if(!strcmp(combinedInput,"exit"))                        //Checking whether user enters exit.If yes, set its corresponding flag.
        {
             exit_flag=1;
        }
        else
        {
            for(iterator=0 ; combinedInput[iterator]!='\0' && valid_Num ; iterator++)
            {
                if( combinedInput[iterator]<48 || combinedInput[iterator]>57 )  //Checking for an invalid number.
                {
                    string_seperate_flag=iterator;
                    InputOperator = combinedInput[iterator];
                    if(InputOperator!='+' && InputOperator!='-' && InputOperator!='*' && InputOperator!='/' && InputOperator!='%')
                    {
                        valid_Num=0;
                        printf("Please Enter Valid Number");
                    }
                }
                if(string_seperate_flag==0)                                     //Seperating the inputs with the help of operator position.
                {
                    input1[iterator]=combinedInput[iterator];
                    input1[iterator+1]='\0';
                }
                else
                {
                    input2[iterator-string_seperate_flag-1]=combinedInput[iterator];
                    input2[iterator-string_seperate_flag]='\0';
                }
            }

            removeLeadingZeros(input1);                                         //Removing Leading zeros for both inputs
            removeLeadingZeros(input2);

            if(valid_Num)
            {

                switch(InputOperator)
                {
                case '+':
                    addition();
                    break;

                case '-':
                    subtraction();
                    break;

                case '*':
                    multiplication();
                    break;

                case '/':
                case '%':
                    division_modulus(InputOperator);
                }
            }
        }
    }
}

//Function Definitions

void addition()
{
    char output_addition[Array_size+1];
    int output_addition_int[Array_size+1]={0};

    input1_length = strlen(input1);
    input2_length = strlen(input2);

    iterator_i = input1_length -1;
    iterator_j = input2_length -1;

    int big_num = iterator_i>iterator_j?iterator_i:iterator_j;
    int big_num_store = big_num;

    while(big_num>=0)
    {
        if(iterator_i>=0 && iterator_j>=0)
        {
            output_addition_int[big_num] = (input1[iterator_i]+input2[iterator_j]-(2*48));
        }
        else if(iterator_i>=0)
        {
            output_addition_int[big_num] = (input1[iterator_i]-48);
        }
        else
        {
            output_addition_int[big_num] = (input2[iterator_j]-48);
        }
        big_num--;
        iterator_i--;
        iterator_j--;
    }

    big_num = big_num_store;

    while(big_num>=0)
    {
        output_addition_int[big_num+1]=output_addition_int[big_num];                        //Allocating one space for carry.
        big_num--;
    }
    output_addition_int[0]=0;
    big_num_store+=1;

    big_num = big_num_store;

    while(big_num>=0)
    {
        if(output_addition_int[big_num]>9)                                                  //Doing some operations to make all the digits in the array to single digit.
        {
            output_addition_int[big_num-1]+= (output_addition_int[big_num]/10);
            output_addition_int[big_num]%=10;
        }
        big_num--;
    }

    big_num = big_num_store;

    while(big_num>=0)
    {
        output_addition[big_num] = output_addition_int[big_num]+48;                         //Converting from int to char
        big_num--;
    }
    output_addition[big_num_store+1]='\0';

    removeLeadingZeros(output_addition);                                                    //Removing Leading Zeros

    printf("\nAddition Result: %s",output_addition);

}

void subtraction()
{
    char output_subtraction[Array_size+1];
    int output_subtraction_int[Array_size+1]={0};

    char pos_neg='+';
    char pos_neg_flag=0;            //0 -> Positive, 1-> Negative
    int all_pos_flag=0;             //Checking whether all the digits in array are positive

    int iterator = 0;
    int larger=0;

    input1_length = strlen(input1);
    input2_length = strlen(input2);

    iterator_i = input1_length -1;
    iterator_j = input2_length -1;

    int big_num = iterator_i>iterator_j?iterator_i:iterator_j;
    int big_num_store = big_num;

    if(iterator_i==iterator_j)                      //Checking whether second number is larger than first number, if both the numbers have same number of digits.
    {
        while(input1[iterator]==input2[iterator])
        {
            iterator++;
        }
        if(input1[iterator]<input2[iterator])
        {
            larger=1;
        }
    }

    if(input1_length>=input2_length && !larger)
    {
        while(big_num>=0)
        {
            if(iterator_i>=0 && iterator_j>=0)
            {
                output_subtraction_int[big_num] = (input1[iterator_i]-input2[iterator_j]);
            }
            else
            {
                output_subtraction_int[big_num] = (input1[iterator_i]-48);
            }
            big_num--;
            iterator_i--;
            iterator_j--;
        }
    }
    else
    {
        pos_neg_flag=1;
        while(big_num>=0)
        {
            if(iterator_i>=0 && iterator_j>=0)
            {
                output_subtraction_int[big_num] = (input2[iterator_j]-input1[iterator_i]);
            }
            else
            {
                output_subtraction_int[big_num] = (input2[iterator_j]-48);
            }
            big_num--;
            iterator_i--;
            iterator_j--;
        }
    }

    while(!all_pos_flag && big_num_store!=0)
    {
        if(output_subtraction_int[0]<0)
            iterator =2;
        else
            iterator=1;

        while(iterator<=big_num_store)
        {
            if(output_subtraction_int[iterator]<0)                          //Borrowing from neighbor if required.
            {
                output_subtraction_int[iterator-1] -= 1;
                output_subtraction_int[iterator] += 10;
            }
            iterator++;
        }

        iterator=0;
        while(iterator<=big_num_store)
        {
            if(output_subtraction_int[iterator]<0)
            {
                all_pos_flag=0;
                break;
            }
            else
                all_pos_flag=1;

            iterator++;
        }
    }

    big_num = big_num_store;

    while(big_num>=0)
    {
        output_subtraction[big_num] = abs(output_subtraction_int[big_num])+48;
        big_num--;
    }

    output_subtraction[big_num_store+1]='\0';

    removeLeadingZeros(output_subtraction);

    if(pos_neg_flag)
    {
        pos_neg ='-';
        printf("\nSubtraction Result: %c%s",pos_neg,output_subtraction);
    }
    else
        printf("\nSubtraction Result: %s",output_subtraction);
}

void multiplication()
{
    char output_multiplication[2*Array_size];
    int output_multiplication_int[2*Array_size]={0};

    int iterator = 0;
    int pos_iterator;

    input1_length = strlen(input1);
    input2_length = strlen(input2);

    iterator_i = input1_length -1;
    iterator_j = input2_length -1;

    while(iterator_j>=0)
    {
        pos_iterator = 1;
        iterator_i = input1_length-1;
        while(iterator_i>=0)
        {
            output_multiplication_int[input1_length + input2_length - pos_iterator - iterator] += ((input1[iterator_i]-48)*(input2[iterator_j]-48));
            iterator_i--;
            pos_iterator++;
        }
        iterator_j--;
        iterator++;
    }

    iterator = input1_length+input2_length-1;

    while(iterator>=0)
    {
        if(output_multiplication_int[iterator]>9)
        {
            output_multiplication_int[iterator-1]+= (output_multiplication_int[iterator]/10);
            output_multiplication_int[iterator]%=10;
        }
        iterator--;
    }

   iterator = input1_length+input2_length-1;

   output_multiplication[iterator+1]='\0';

    while(iterator>=0)
    {
        output_multiplication[iterator] = output_multiplication_int[iterator]+48;
        iterator--;
    }

    removeLeadingZeros(output_multiplication);

    printf("\nMultiplication Result : %s",output_multiplication);
}


void division_modulus(char InputOperator)
{

	char store_divisor[Array_size] = {'\0'};
	char output_division_quotient[Array_size] = {'\0'};
	char output_division_remainder[Array_size] = {'\0'};

	int output_division_quotient_int[Array_size]={0};
    int output_division_remainder_int[Array_size]={0};

    int iterator =0;
    int quotient_arr_iterator= Array_size-1;

    char pos_neg='+';
    char pos_neg_flag=0;
    int all_pos_flag =0;
    int repeat_flag=1;                     //Repeating the operation until dividend can be subtracted from divisor.
    int new_divisor_flag=0;

    int larger =0;

    strcpy(store_divisor,input2);

    input1_length = strlen(input1);
    input2_length = strlen(input2);

    iterator_i = input1_length-1;           //Dividend length
    iterator_j = input2_length-1;           //Divisor length

    int big_num = iterator_i;
    int big_num_store = big_num;

	int num_of_zeros_added = 0;

	if(iterator_i>iterator_j && input1_length-1!=input2_length)     //Modifying divisor length to calculate result faster
	{
		int i=0;
		for(i=0;i<(input1_length-input2_length-1);i++)
		{
			input2[input2_length+i]='0';
		}
		input2[input2_length+i]='\0';
		new_divisor_flag = 1;
		num_of_zeros_added = input1_length-input2_length-1;
	}

	if(new_divisor_flag)
		iterator_j = strlen(input2)-1;

	if(iterator_i==iterator_j)                  //Checking whether divisor is larger than dividend
    {
        while(input1[iterator]==input2[iterator])
        {
            iterator++;
        }
        if(input1[iterator]<input2[iterator])
        {
            larger=1;
        }
    }

    //Computation Begins here

    if(iterator_j==0 && input2[0]=='1')         //If divisor is 1, then quotient will be dividend and remainder will be 0
    {
        if(InputOperator=='/')
            printf("\nQuotient: %s",input1);

        printf("\nRemainder : 0");
    }
    else if(input2[0]=='0')                     //If divisor is zero
    {
        printf("Infinity");
    }
    else if(iterator_i<iterator_j || larger)
    {
        strcpy(output_division_remainder,input1);
        output_division_quotient[0]='0';
        output_division_quotient[1]='\0';

        if(InputOperator=='/')
            printf("\nQuotient: %s",output_division_quotient);

        printf("\nRemainder: %s",output_division_remainder);
    }
	else
	{
		 while(repeat_flag==1)
        {
            iterator=0;
            while(big_num>=0)
            {
                if(iterator_i>=0 && iterator_j>=0)
                {
                    output_division_remainder_int[big_num] = (input1[iterator_i]-input2[iterator_j]);
                }
                else
                {
                output_division_remainder_int[big_num] = (input1[iterator_i]-48);
                }
                big_num--;
                iterator_i--;
                iterator_j--;
            }
			while(!all_pos_flag && big_num_store!=0)
            {
                if(output_division_remainder_int[0]<0)
                    iterator =2;
                else
                    iterator=1;

                while(iterator<=big_num_store)
                {
                    if(output_division_remainder_int[iterator]<0)
                    {
                        output_division_remainder_int[iterator-1] -= 1;
                        output_division_remainder_int[iterator] += 10;
                    }
                    iterator++;
                }

                iterator=0;

                while(iterator<=big_num_store)
                {
                    if(output_division_remainder_int[iterator]<0)
                    {
                        all_pos_flag=0;
                        break;
                    }
                    else
                        all_pos_flag=1;

                    iterator++;
                }
            }

			big_num = big_num_store;

            while(big_num>=0)
            {
                output_division_remainder[big_num] = abs(output_division_remainder_int[big_num])+48;
                big_num--;
            }

            output_division_remainder[big_num_store+1]='\0';

            removeLeadingZeros(output_division_remainder);

			if(new_divisor_flag==0)
            {
                output_division_quotient_int[Array_size-1] += 1;        //For every one time, divisor is subtracted from dividend, 1 will be added in quotient.

                if(output_division_quotient_int[Array_size-1]==10)      //Making all the digit in array as single digits.
                {
                    quotient_arr_iterator=Array_size-1;
                    while(quotient_arr_iterator>=0)
                    {
                        if(output_division_quotient_int[quotient_arr_iterator]>9)
                        {
                            output_division_quotient_int[quotient_arr_iterator-1] += (output_division_quotient_int[quotient_arr_iterator]/10);
                            output_division_quotient_int[quotient_arr_iterator] %=10;
                        }
                        quotient_arr_iterator--;
                    }
                }
            }
			else
            {
                output_division_quotient_int[Array_size-1-num_of_zeros_added] += 1;        //For every one time, divisor is subtracted from dividend, 1 will be added in quotient.

                if(output_division_quotient_int[Array_size-1-(num_of_zeros_added)]==10)      //Making all the digit in array as single digits.
                {
                    quotient_arr_iterator=Array_size-1;
                    while(quotient_arr_iterator>=0)
                    {
                        if(output_division_quotient_int[quotient_arr_iterator]>9)
                        {
                            output_division_quotient_int[quotient_arr_iterator-1] += (output_division_quotient_int[quotient_arr_iterator]/10);
                            output_division_quotient_int[quotient_arr_iterator] %=10;
                        }
                        quotient_arr_iterator--;
                    }
                }
            }

			iterator_i = strlen(output_division_remainder)-1;
            strcpy(input1,output_division_remainder);               //Making the remainder as new dividend for next loop.

            big_num=iterator_i;
            big_num_store=big_num;

            iterator=0;

            if(!new_divisor_flag)
                iterator_j = input2_length-1;
            else
                iterator_j = strlen(input2)-1;

            all_pos_flag=0;

			if(iterator_i < iterator_j && num_of_zeros_added!=0)
			{
				int i=0;
				for(i=0;i<(iterator_j-iterator_i) && num_of_zeros_added!=0;i++)
				{
					input2[iterator_j-i]='\0';
					num_of_zeros_added--;
				}
				new_divisor_flag = 1;
					iterator_j = strlen(input2)-1;
			}

			if(num_of_zeros_added==0)
			{
				strcpy(input2,store_divisor);
                new_divisor_flag=0;
                iterator_j = strlen(input2)-1;
			}

            if(iterator_i==iterator_j)
            {
                while(input1[iterator]==input2[iterator] && input1[iterator]!='\0')
                {
                    iterator++;
                }
                if(input1[iterator]<input2[iterator])
                {
					if(num_of_zeros_added==0)
					larger=1;
					else
					{
						input2[iterator_j]='\0';
						num_of_zeros_added--;
						iterator_j=strlen(input2)-1;
					}
                }
            }

            if((iterator_i<iterator_j || larger) && !new_divisor_flag)                     //Checking whether another iteration possible
            {
                repeat_flag=0;
            }
            else if((iterator_i<iterator_j || larger) && new_divisor_flag)
            {
                strcpy(input2,store_divisor);
                new_divisor_flag=0;
                larger=0;
                 iterator_j = strlen(input2)-1;
            }
        }

        int i=0;
        for(i=0;i<Array_size;i++)
        {
             output_division_quotient[i]=output_division_quotient_int[i]+48;
        }

        output_division_quotient[i]='\0';

        removeLeadingZeros(output_division_quotient);

        if(InputOperator=='/')
            printf("\nQuotient: %s",output_division_quotient);

        if(output_division_remainder[0]=='\0')
            printf("\nRemainder: 0");
        else
            printf("\nRemainder: %s",output_division_remainder);
    }
}

void removeLeadingZeros(char *arr)
{
    int num_of_leadingZeros=0;
    int i=0;
    while(*(arr+i)!='\0')
    {
        if(*(arr+i)!='0')
            break;
        i++;
    }
    num_of_leadingZeros=i;
    if(*(arr+num_of_leadingZeros)=='\0')            //If in case user enters 0000 as one number, in that case we keep only one 0.
    {
        *(arr+0)='0';
        *(arr+1)='\0';
    }
    else
    {
        for(i=0;*(arr+i)!='\0';i++)
        {
            *(arr+i)=*(arr+num_of_leadingZeros+i);
        }
        *(arr+i)='\0';
    }
}
