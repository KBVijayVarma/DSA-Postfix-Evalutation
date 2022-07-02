#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define N 500

struct stack{
    double arr[N];
    int top;
};
typedef struct stack stack;

// Function that creates and returns Empty Stack Pointer
stack* createEmptyStack()
{
    stack *s; // Creating Empty Stack Pointer
    s = (stack*) malloc(sizeof(stack)); // Allocating memory address to the Pointer
    s->top = -1; // Setting top of the Stack Pointer to -1
    return s; // Returning the Stack Pointer
}

// Function to check if the given Stack is Empty
// Returns 1 if Stack is Empty
// Returns 0 if given Stack is Empty
int isEmpty(stack *s)
{
    if(s->top == -1) // If the top of the Stack is -1 then it implies the Stack is Empty
    {
        return 1; // Returns 1 if Stack is Empty
    }
    return 0; // Returns 0 if Stack is not Empty
}

// Function to push a given x into the Stack s
void push(stack *s, double x)
{
    s->top = s->top + 1; // Increases the top of the Stack by 1
    s->arr[s->top] = x; // Assigning the top place of the Stack as x 
}

// Function to pop an element from given Stack s
double pop(stack *s)
{
    if(isEmpty(s)) return -1; // Unable to pop from Stack s if s is Empty, so it returns -1
    s->top = s->top - 1; // Decreases the top of the Stack by 1
    return s->arr[s->top + 1]; // Returns the top element of the stack if it is not Empty
}

// Function to evaluate a given String str[] (Postfix Expression) and returns the top element of the Stack
double postfix(char str[])
{
    
    stack* s = createEmptyStack(); // Creating an Empty Stack Pointer
    
    // Initialising required variables
    char c;
    double d;
    double a,b;
    int j;
    
    // for loop to iterate through all the characters in the String
    for(int i=0;str[i] != '\0';i++)
    {
        double n = 0;
        c = str[i]; // Assigning str[i] to a char variable c
        if(c == ',') // If c is ',' then continue
        {
            continue;
        }
        else // If c is not ','
        {
            if(c == '+') // If c is '+'
            {
                a = pop(s); // Popping the most recent item in the Stack s and storing it in a
                b = pop(s); // Popping the most recent item in the Stack s and storing it in b
                push(s,b+a); // Pushing b+a into the Stack s
            }
            else if(c == '-' && (str[i+1] == ',' || str[i+1] == '\0')) // If c is '-' and str[i+1] is either ',' or '\0' (it means c is definitely an operator and not a negative integer)
            {
                a = pop(s); // Popping the most recent item in the Stack s and storing it in a
                b = pop(s); // Popping the most recent item in the Stack s and storing it in b
                push(s,b-a); // Pushing b-a into the Stack s
            }
            else if(c == '*') // If c is '*'
            {
                a = pop(s); // Popping the most recent item in the Stack s and storing it in a
                b = pop(s); // Popping the most recent item in the Stack s and storing it in b
                push(s,b*a); // Pushing b*a into the Stack s
            }
            else if(c == '/') // If c is '/'
            {
                a = pop(s); // Popping the most recent item in the Stack s and storing it in a
                b = pop(s); // Popping the most recent item in the Stack s and storing it in b
                push(s,b/a); // Pushing b/a into the Stack s
            }
            else // If c = str[i] is (a digit) or ('-' if str[i+1] is a digit)
            {
                if(c == '-') // If c (= str[i]) == '-' and str[i+1] is a digit so the given number is a Negative Number
                {
                    // The digits after c ('-') form a negative number
                    // If str[i+2] is not a digit(either ',' or operator or '\0'), then the given item (str[i+1]) has only 1 digit, so it is a single negative number
                    // Then n is equal to that single negative number (-c)
                    // If str[i+3] is also a digit, then the given item has multiple digits, so the number has multiple digits
                    // So we have to convert all the digits till ',' or '\0' into a single number
                    // All the digits (single digit or multiple digits) are stored in n and we push -n into the Stack s
                    // We put the index j to i+1 (since str[i+1] is a digit) and store number in n
                    for(j=i+1; str[j] != ',' && str[j] != '\0' ;j++)
                    {
                        // Each digit is multiplied by 10 and added to the next digit until the next character is ',' or '\0'
                        n = 10*n + (double)(str[j] - '0');
                    }
                    i = j - 1; // Returning i to the position before the ','
                    push(s,-n); // The number -n (since the given item is negative) is pushed into the Stack s
                }
                
                else // So str[i] is a Digit and the given item is a Positive Number
                {
                    // If str[i+1] is not a digit(',' or '\0'), then the given item(str[i])has only 1 digit, so it is a single positive number
                    // Then n is equal to that single number c
                    // If str[i+1] is a digit, then the given item has only multiple digits, so the number has multiple digits
                    // So we have to convert all the digits till ',' or '\0' into a single number
                    // All the digits (single digit or multiple digits) are stored in n and we push n into the Stack s
                    // We put the index j to i (since str[i] is a digit) and store number in n
                    for(j=i; str[j] != ',' && str[j] != '\0' ;j++)
                    {
                        // Each digit is multiplied by 10 and added to the next digit until the next character is ',' or '\0'
                        n = 10*n + (double)(str[j] - '0');
                    }
                    i = j - 1; // Returning i to the position before the ','
                    push(s,n); // The number n (since n is positive) is pushed into the Stack s
                }
            }
        }
    }
    
    // The top element of the Stack s is popped and the Stack is Emptied
    return pop(s);
}

// Function to check if the given String str[] (Postfix Expression) is a Valid Postfix Expression 
int checkpostfix(char str[])
{
    // Initialising required variables
    char c;
    int a = 0; // Variable a is used to count total number of Operators in the given String
    int b = 0; // Variable b is used to count total number of Numbers in the given String
    int j;
    
    // for loop to count number of Operators and Numbers in the given String and check if it is a valid Postfix Expression
    for(int i = 0 ; str[i] != '\0' ;i++)
    {
        c = str[i];
        if(c == ',') // If c is ',' then continue
        {
            continue;
        }
        else // If c is not ','
        {
            // If c is definitely an operator ('+' or '-' or '*' or '/')
            // If c == '-' then it maybe a chance that it is a Negative Number
            // So to avoid the above possibility, the condition str[i+1] should be either ',' or '\0' should be satisfied
            if(c == '+' || (c == '-' && (str[i+1] == ',' || str[i+1] == '\0')) || c == '*' || c == '/') // If x is '+' or '-' or '*' or '/'
            {
                a++; // Increase the value of a (count of Operators) by 1
            }
            else // If c = str[i] is a digit or ('-' if str[i+1] is a digit)
            {
                // If c (= str[i]) == '-' and str[i+1] is a digit so the given number is a Negative Number
                if(c == '-')
                {
                    // We put the index j to i+1 (since str[i+1] is a digit)
                    // Same as above but here we need to move the index j to non-digit character (either ',' or '\0' (end of string))
                    for(j=i+1; str[j] != ',' && str[j] != '\0' ;j++)
                    {
                        // This for loop is just to place index j to either nearest ',' or '\0'
                    }
                    i = j - 1; // Returning index i to the position before the ',' or '\0' (end of string)
                    // For every one Negative number we increase the count of b (Count of Numbers) by one
                    b++; // Increasing the value of b (count of Numbers) by one
                }
                
                else // So str[i] is a Digit and the given item is a Positive Number
                {
                    // We put the index j to i (since str[i] is a digit)
                    // Same as above but here we need to move the index j to non-digit character (either ',' or '\0' (end of string))
                    for(j=i;str[j] != ',' && str[j] != '\0' ;j++)
                    {
                        // This for loop is just to place index j to either nearest ',' or '\0' 
                    }
                    i = j - 1; // Returning index i to the position before the ',' or '\0' (end of string)
                    // For every one Positive number we increase the count of b (Count of Numbers) by one
                    b++; // Increasing the value of b (count of Numbers) by one
                }
            }
        }
        if(a >= b) // If a >= b (Count of Operators >= Count of Numbers) while checking the Expression, then the given Expression is an Invalid Postfix Expression
        {
            return -1; // Returns -1 if the given Expression is an Invalid Postfix Expression
        }
    }
    
    if(b > (a + 1)) // If b > (a + 1) (Total Count of Numbers > Total Count of Operators + 1) , then the given Expression is an Invalid Postfix Expression
    {
        return -1; // Returns -1 if the given Expression is an Invalid Postfix Expression
    }
    return 1; // Returns 1 if the given Expression is a Valid Postfix Expression
}

int main()
{
    // String to store the given Postfix Expression in String psfx[N]
    char psfx[N];
    printf("Enter the Postfix Expression :\n");
    scanf("%s",psfx);
    
    // Checks if given Postfix Expression is a Postfix Expression
    if(checkpostfix(psfx) == -1)
    {
        // Prints "Invalid Postfix Expression" if given Postfix Expression is Invalid and stops
        printf("Invalid Postfix Expression");
        return 0;
    }
    
    // Variable to store the value of given Postfix Expression
    double result;
    result = postfix(psfx);
    printf("Postfix Value = %.6lf",result);
  
    return 0;
}
