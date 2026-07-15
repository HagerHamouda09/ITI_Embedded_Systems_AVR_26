# Session 6 Labs 

### **Lab 1:** Pointer Basics & Modification
Write a C code that defines an int initialized with 10, prints it, defines a pointer that points to that int, changes the value of the int through the pointer to be 20, and prints it again.

<img width="576" height="224" alt="image" src="https://github.com/user-attachments/assets/f4246bac-c404-436a-a75e-d3438b8a7740" />


**Code:**
```c
#include <stdio.h>

int main()
{
    int num = 10;      // Define and initialize an integer
    int *ptr = &num;   // Pointer to the integer

    // Print the original value
    printf("Before: num = %d\n", num);

    // Change the value through the pointer
    *ptr = 20;

    // Print the updated value
    printf("After: num = %d\n", num);

    return 0;
}

```

---

### **Lab 2:** Pass by Address (Summation)

Write a C code that asks the user to enter 2 values and saves them in two variables. The program then sends these variables by address to a function that returns their summation, and prints the final result.

<img width="402" height="176" alt="image" src="https://github.com/user-attachments/assets/7f3f5ae6-9039-4c40-a533-1c712c8d3f4b" />


**Code:**

```c
#include <stdio.h>

int Sum(int *a, int *b)
{
    return *a + *b;
}

int main()
{
    int num1, num2, result;

    // Read two numbers from the user
    printf("Enter the first number: ");
    scanf("%d", &num1);

    printf("Enter the second number: ");
    scanf("%d", &num2);

    // Pass the addresses of the variables
    result = Sum(&num1, &num2);

    // Print the result
    printf("Sum = %d\n", result);

    return 0;
}

```

---

### **Lab 3:** Multiple Function Outputs Using Pointers

Write a C code that asks the user to enter 2 values and saves them in two variables. The program sends these variables to a function that calculates both their summation and subtraction. The function updates the values inside two pointers received as input arguments, and the program prints both results.

<img width="383" height="216" alt="image" src="https://github.com/user-attachments/assets/0084122c-196c-4d72-b88a-625c2a3b6c0a" />


**Code:**

```c
#include <stdio.h>

// Function to calculate sum and difference
void Calculate(int a, int b, int *sum, int *sub)
{
    *sum = a + b;
    *sub = a - b;
}

int main()
{
    int num1, num2;
    int sum, sub;

    printf("Enter the first number: ");
    scanf("%d", &num1);

    printf("Enter the second number: ");
    scanf("%d", &num2);

    // Pass the addresses of sum and sub
    Calculate(num1, num2, &sum, &sub);

    printf("Sum = %d\n", sum);
    printf("Difference = %d\n", sub);

    return 0;
}

```

---

### **Lab 4:** Find Maximum Using Pointers

Write a function that receives the addresses of two integers and returns the larger value.

**Code:**

```c
#include <stdio.h>

int Max(int *a, int *b)
{
    if (*a > *b)
        return *a;
    else
        return *b;
}

int main()
{
    int x, y;

    printf("Enter two numbers: ");
    scanf("%d%d", &x, &y);

    printf("Maximum = %d\n", Max(&x, &y));

    return 0;
}

```

---

---

# Practical Structure & String Exercises

### **Lab 5:** Draw Shape Using Nested Loops

Write a program that prompts the user to enter a number of rows and columns, then prints a solid rectangle of asterisks matching those dimensions.

<img width="542" height="381" alt="image" src="https://github.com/user-attachments/assets/a9ac0509-9f8f-4b2c-8b6b-30e215679442" />


**Code:**

```c
#include <stdio.h>

int main()
{
    int rows = 0;
    int cols = 0;
    printf("rows: ");
    scanf("%d", &rows);
    printf("cols: ");
    scanf("%d", &cols);
    
    for(int i = 0; i < rows; i++)
    {
        for(int j = 0; j < cols; j++)
            printf("* ");
        printf("\n");
    }
    return 0;
}

```

---

### **Lab 6:** Count Character Occurrences in String

Write a program that takes a string input and a target character from the user, iterates through the string until reaching the null-terminator (`\0`), and counts how many times that character appears.

<img width="638" height="179" alt="image" src="https://github.com/user-attachments/assets/77bc59e1-7ac9-4051-8013-c91a7ce5771e" />

**Code:**

```c
#include <stdio.h>

int main()
{
    char str[100];
    char ch;
    int count = 0;

    printf("Enter a string: ");
    scanf("%s", str);

    printf("Enter a character: ");
    scanf(" %c", &ch);

    int i = 0;
    while (str[i] != '\0')
    {
        if (str[i] == ch)
        {
            count++;
        }
        i++;
    }

    printf("Count = %d\n", count);

    return 0;
}

```
