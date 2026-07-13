**Lab 3 :**

Write a C code that will ask the user to enter two values and print their summation and multiplication.

<img width="514" height="246" alt="image" src="https://github.com/user-attachments/assets/52d8aa79-0bcd-4f01-9ea0-f3bb2871638c" />

**code:**

```c
#include <stdio.h>

int main()
{
    int num1, num2;
    int sum, product;

    printf("Enter the first number: ");
    scanf("%d", &num1);

    printf("Enter the second number: ");
    scanf("%d", &num2);

    sum = num1 + num2;
    product = num1 * num2;

    printf("\nSum = %d\n", sum);
    printf("Product = %d\n", product);

    return 0;
}
```

---------------------------------------------------------------------------------------------------------------------

**Lab 4 :**
Solve these examples in a paper and confirm the that your answers are correct by writing a code printing the result

<img width="194" height="286" alt="image" src="https://github.com/user-attachments/assets/6065ec09-470e-410b-9227-649869de1ca5" />

**code :**

```c
#include <stdio.h>

int main() {
    int x = 15;
    int y = 20;

    int z = x & y;
    int k = x | y;
    int l = x ^ y;
    int m = x >> 3;
    int n = y << 4;

    printf("z (x & y)  = %d\n", z);
    printf("k (x | y)  = %d\n", k);
    printf("l (x ^ y)  = %d\n", l);
    printf("m (x >> 3) = %d\n", m);
    printf("n (y << 4) = %d\n", n);

    return 0;
}
```

---------------------------------------------------------------------------------------------------------------------

**Extra Labs:**

1) Write a C program to ask user to enter the length and width then calculate the perimeter of rectangle then print 

<img width="524" height="140" alt="image" src="https://github.com/user-attachments/assets/15d712af-049d-4040-97bb-d3c20db57238" />


**code:**
```c
#include <stdio.h>

int main()
{
    float length, width, perimeter;
    
    //  Input length and width of rectangle from user
    printf("Enter length of the rectangle: ");
    scanf("%f", &length);
    printf("Enter width of the rectangle: ");
    scanf("%f", &width);

    // Calculate perimeter of rectangle 
    perimeter = 2 * (length + width);

    // Print perimeter of rectangle 
    printf("Perimeter of rectangle = %f units ", perimeter);

    return 0;
}
```

---------------------------------------------------------------------------------------------------------------------

2) Write a C code that asks the user to Enter 2 values and swap then print

<img width="569" height="161" alt="image" src="https://github.com/user-attachments/assets/4d492de5-cebd-4bf1-afc3-a24969c78612" />


**Code:**

```c
#include <stdio.h>
int main()
{
      int firstNumber, secondNumber, tempVariable;

      printf("Enter first number: ");
      scanf("%d", &firstNumber);

      printf("Enter second number: ");
      scanf("%d",&secondNumber);

      // Value of firstNumber is assigned to tempVariable
      tempVariable = firstNumber;

      // Value of secondNumber is assigned to firstNumber
      firstNumber = secondNumber;

      // Value of tempVariable (which contains the initial value of firstNumber) is assigned to secondNumber
      secondNumber = tempVariable;
      printf("\n ......After swapping...... ");
      printf("\nfirstNumber = %d\n", firstNumber);
      printf("secondNumber = %d", secondNumber);

      return 0;
}
```

---------------------------------------------------------------------------------------------------------------------

3) Write a C code that asks the user to Enter 2 values and swap then print (Without using third variable)

**Code:**

```c
#include <stdio.h>

int main()
{
      int firstNumber, secondNumber;

      printf("Enter first number: ");
      scanf("%d", &firstNumber);

      printf("Enter second number: ");
      scanf("%d",&secondNumber);

      // the new Value of firstNumber is sum the firstNumber and the secondNumber 
      firstNumber = firstNumber+secondNumber;

      //  Value of secondNumber after swapping is subtraction the new Value of firstNumber and the secondNumber 
      secondNumber = firstNumber-secondNumber;

      // Value of firstNumber after swapping is subtraction the new Value of firstNumber and the  value of secondNumber after swapping
      firstNumber = firstNumber-secondNumber;
      printf("\n ......After swapping...... ");
      printf("\nfirstNumber = %d\n", firstNumber);
      printf("secondNumber = %d", secondNumber);

      return 0;
}
```

---------------------------------------------------------------------------------------------------------------------

4) Write a C code to input marks of 5 subjects of student and calculate Total, Average and Percentage of all subjects

<img width="563" height="228" alt="image" src="https://github.com/user-attachments/assets/799e21c3-724d-433c-bc88-71a78cfa7906" />


**Code:**

```c
#include <stdio.h>

int main()
{
    float eng, phy, chem, math, comp; 
    float total, average, percentage;

    // Input marks of all five subjects or ask user to enter them
    printf("Enter marks of five subjects: \n");
    scanf("%f%f%f%f%f", &eng, &phy, &chem, &math, &comp);

    // Calculate total, average and percentage
    total = eng + phy + chem + math + comp;
    average = total / 5.0;
    percentage = (total / 500.0) * 100;

    // Print all results 
    printf("Total marks = %.2f\n", total);
    printf("Average marks = %.2f\n", average);
    printf("Percentage = %.2f", percentage);

    return 0;
}
```
