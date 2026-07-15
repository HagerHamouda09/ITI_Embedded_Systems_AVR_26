#  Session 4 Labs

### **Lab 1:** Circle Area & Cylinder Volume (Without Prototypes)
Write a C program to calculate the area of a circle and the volume of a cylinder. In this version, helper functions are defined directly above the `main()` function.

<img width="566" height="259" alt="image" src="https://github.com/user-attachments/assets/544578c7-cee1-4564-abba-c1d216b63e30" />


**Code:**
```c
#include <stdio.h>

float CalculateCircleArea(float rad)
{
    return 3.14 * rad * rad;
}

float CalculateCylinderVolume(float rad, float height)
{
    return CalculateCircleArea(rad) * height;
}

int main()
{
    float cir_rad, cyl_rad, cyl_height;
    printf("Enter rad of the circle:\n");
    scanf("%f", &cir_rad);
    
    printf("Enter rad of the cylinder then the height :\n");
    scanf("%f%f", &cyl_rad, &cyl_height);
    
    printf("Circle area is %f\n", CalculateCircleArea(cir_rad));
    printf("Cyl volume is %f\n", CalculateCylinderVolume(cyl_rad, cyl_height));
    
    return 0;
}

```

---

### **Lab 2:** Circle Area & Cylinder Volume (With Prototypes)

Write a C program to calculate the area of a circle and the volume of a cylinder. In this version, function prototypes are declared at the top, and the actual definitions are placed below the `main()` function.

<img width="580" height="263" alt="image" src="https://github.com/user-attachments/assets/2add3653-2220-4588-8108-f8840b38c4bc" />


**Code:**

```c
#include <stdio.h>

float CalculateCircleArea(float rad);
float CalculateCylinderVolume(float rad, float height);

int main()
{
    float cir_rad, cyl_rad, cyl_height;
    printf("Enter rad of the circle:\n");
    scanf("%f", &cir_rad);
    
    printf("Enter rad of the cylinder then the height :\n");
    scanf("%f%f", &cyl_rad, &cyl_height);
    
    printf("Circle area is %f\n", CalculateCircleArea(cir_rad));
    printf("Cyl volume is %f\n", CalculateCylinderVolume(cyl_rad, cyl_height));
    
    return 0;
}

float CalculateCircleArea(float rad)
{
    return 3.14 * rad * rad;
}

float CalculateCylinderVolume(float rad, float height)
{
    return CalculateCircleArea(rad) * height;
}

```

---

---

#  Session 5 Labs

### **Lab 1:** Array Input & Reverse Print

Write a C code that asks the user to enter 10 values and saves them in an array using a `for` loop. Then, print the values entered by the user in reverse order using another `for` loop.

<img width="235" height="319" alt="image" src="https://github.com/user-attachments/assets/6c0271f5-feaf-43aa-b452-7c0bdb060568" />


**Code:**

```c
#include <stdio.h>

int main()
{
    int arr[10];
    for(int i = 0; i < 10; i++)
    {
        printf("Enter the number at index %d\n", i);
        scanf("%d", &arr[i]);
    }
    for(int i = 9; i >= 0; i--)
    {
        printf("%d\n", arr[i]);
    }
    return 0;
}

```

---

### **Lab 2:** Array Summation & Average

Write a C code that asks the user to enter 10 values and saves them in an array using a `for` loop. Then, print the summation and the average of the values entered.

<img width="644" height="265" alt="image" src="https://github.com/user-attachments/assets/633f076e-2f44-440f-8ad5-a1ee582c6a86" />


**Code:**

```c
#include <stdio.h>

int main()
{
    int summation = 0;
    float average = 0.0;
    int arr[10] = {0};
    for(int i = 0; i < 10; i++)
    {
        printf("Enter the number at index %d\n", i);
        scanf("%d", &arr[i]);
        summation += arr[i];
    }
    average = summation / 10.0;
    printf("the summation is %d\n", summation);
    printf("the average is %f\n", average);
    
    return 0;
}

```
---

# Extra Labs

### **Exercise 1:** Custom Power Function

Write a C program that asks the user to enter a base and an exponent. Create a custom function named `Power()` that calculates and returns the computed result.

**Code:**

```c
#include <stdio.h>

int Power(int base, int exponent)
{
    int result = 1;

    for (int i = 0; i < exponent; i++)
    {
        result *= base;
    }

    return result;
}

int main()
{
    int base, exponent;

    printf("Enter base: ");
    scanf("%d", &base);

    printf("Enter exponent: ");
    scanf("%d", &exponent);

    printf("Result = %d\n", Power(base, exponent));

    return 0;
}

```

---

### **Exercise 2:** Palindrome Number Checker

Write a C program that asks the user to enter an integer. Create a function named `IsPalindrome()` that determines if the integer reads the same backward as forward.

**Code:**

```c
#include <stdio.h>

int IsPalindrome(int num)
{
    int original = num;
    int reverse = 0;
    int remainder;

    while (num != 0)
    {
        remainder = num % 10;
        reverse = reverse * 10 + remainder;
        num /= 10;
    }

    if (original == reverse)
        return 1;
    else
        return 0;
}

int main()
{
    int num;

    printf("Enter a number: ");
    scanf("%d", &num);

    if (IsPalindrome(num))
        printf("Palindrome Number\n");
    else
        printf("Not Palindrome Number\n");

    return 0;
}

```
