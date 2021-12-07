/* Logic Homework 3, Part 1 */
/* Team Number: 6 */
/* Team Members:
1. <Ruban SriramBabu> <2019A7PS0097H>
2. <Chandra Vamsi TV> <2019A7PS0033H>
3. <Kaustubh Bhanj> <2019A7PS0009H>
4. <Om Agarwal> <2019A7PS0052H>
*/


#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX 100 // macro indicating the maximum size of stack




/***************************************************************/
/********************stack operations***************************/

// Inserting data onto top of stack. Takes as arguments the data to be pushed, the array used for implementing the stack and an integer pointer referencing the index of the top of that stack.

void push(char data, char stack[], int *top)  
{ 
   if(*top != MAX-1) // if stack is not full
   {  *top = *top + 1;   
      stack[*top] = data;
   } 	
   else 
   {
      printf("Could not insert data, Stack is full.\n");
   }
}


// Removing element from top of stack. Takes as arguments the array used for implementing the stack and an integer pointer referencing the index of the top of that stack. Returns the popped character.

char pop(char stack[], int *top) 
{
   char data;
	
   if(*top != -1) //checking whether stack contains some elements
   {
      data = stack[*top];
      *top = *top - 1;   
      return data;
   }

   else 
   {
      printf("Could not retrieve data, Stack is empty.\n");
   }
}

// NOTE:
// A pointer to the variable top is passed instead of passing the top variable itself. This is done to ensure top is passed as reference and any modifications to the top variable 
// would be reflected in the calling function



/***************************************************************/
/********************* implementation **************************/

// function to implement the solution for Part 1. Takes as arguments the number of atoms, the character array to store the completely parenthesized input formula and the array to store the valuation of the atoms
// returns the final result of evaluating the formula (either T or F)

char eval_formula(int n, char formula[], char operand_val[])    
{
   char operand_stack[MAX];  // character array to implement operand stack
   char operator_stack[MAX]; // character array to implement operator stack 
   int operand_top = -1; // integer pointing to the top of the operand stack
   int operator_top = -1;  // integer pointing to the top of the operand stack
   int i ;
   for (i = 0; i < strlen(formula); i++) // iterating through the characters of the formula
   {
      char ch = formula[i];
      if (ch == ' ') // handling spaces present in input
      {
         continue;
      }
      else if (ch >= '1' && ch <= '9') 
      {
         char operand = operand_val[ch - '1']; // character containing the value (T or F) corresponding to index ch in the operand_val array
         push(operand, operand_stack, &operand_top); // pushing the character to operand stack if it belongs to {'T', 'F'}
      }
      else if (ch != ')')
      {
         push(ch, operator_stack, &operator_top); // pushing the character to the operator stack if it belongs to {'(', 'V', '^', '>', '~'}
      }
      else // ')' character is encountered. We will evaluate the statement in the brackets
      {
         while (operator_stack[operator_top] != '(') // once ')' is at the top of the operator stack
         {
            if (operator_stack[operator_top] == '~') // top of operator stack is a unary operator (negation)
            {
               char ch_operand = pop(operand_stack, &operand_top); // popping the literal from operand stack
               pop(operator_stack, &operator_top); // popping the operator '~' from the operator stack
               push(((ch_operand == 'T') ? 'F' : 'T'), operand_stack, &operand_top); // negation of the literal is pushed into operator stack
            }
            else // top of the operator stack is a binary operator
            {
               char ch_operand2 = pop(operand_stack, &operand_top); // popping the second operand (inside the brackets) from the operand stack
               char ch_operator = pop(operator_stack, &operator_top); // popping the operator from the operator stack 
               char ch_operand1 = pop(operand_stack, &operand_top); // popping the first operand (inside the brackets) from the operand stack
               int val1 = (ch_operand1 == 'T') ? 1 : 0; // setting binary values to apply binary operations
               int val2 = (ch_operand2 == 'T') ? 1 : 0;

               if (ch_operator == 'V')
               {
                  push(((val1|val2 == 1) ? 'T' : 'F'), operand_stack, &operand_top); // binary OR is applied and the value (T if value is 1, else F) is pushed into the operand stack
               }
               else if (ch_operator == '^')
               {
                  push(((val1&val2 == 1) ? 'T' : 'F'), operand_stack, &operand_top); // binary AND is applied and the value (T if value is 1, else F) is pushed into the operand stack
               }
               else
               {
                  push(((val1 == 1 && val2 == 0) ? 'F' : 'T'), operand_stack, &operand_top); // implication p > q is F when p is T and q F. Evaluates to T in all other cases
               }
            }
            pop(operator_stack, &operator_top); // popping the opening bracket '(' from the operator stack once the statement in the brackets has been evaluated
            if (operator_top == -1) // if there are no elements remaining in the operator stack, then the formula has been evaluated
            {
               break; // break from the while loop
            }
         }
      }
      if (operator_top == -1) // formula has been evaluated
      {
         break; // break from the for loop
      }
   }
   
   return operand_stack[operand_top]; // returning the truth value of the formula for the valuation given

}





/***************************************************************/
/***********************main function***************************/

int main()
{  
   int n; // number of operands
   char formula[MAX]; // character array to store the input formula
   char operand_val[10]; // array to store the valuation of operands (either T or F)
   
   scanf("%d\n%[^\n]%*c%s", &n, formula, operand_val); // taking the 3 inputs

   printf("%c", eval_formula(n, formula, operand_val));

   return 0;
   
}
