# Session 2 Labs

### **Lab 1:** Drive Eligibility Check
Write a simple program that checks if a person can drive or not. The program should ask the user to enter their age. If the age is greater than or equal to 16, print a message stating they can drive; otherwise, print that they cannot drive.

<img width="485" height="140" alt="image" src="https://github.com/user-attachments/assets/985cda0c-f8e2-4ca2-b125-9c347c815651" />


**Code:**
```c
#include <stdio.h>

int main()
{
    int age;

    printf("Enter your age: ");
    scanf("%d", &age);

    if (age >= 16)
    {
        printf("You can drive.\n");
    }
    else
    {
        printf("You cannot drive.\n");
    }

    return 0;
}

```

---

### **Lab 2:** Score Rating System

Write a simple program that asks the user to enter their score and prints their rating according to the following rules:

* `0 <= grade < 50`  -> Failed
* `50 <= grade < 65` -> Pass
* `65 <= grade < 75` -> Good
* `75 <= grade < 85` -> Very Good
* `85 <= grade <= 100` -> Excellent

  <img width="475" height="119" alt="image" src="https://github.com/user-attachments/assets/8120b2f3-4c29-4615-a056-a9e0e84fd910" />


**Code:**

```c
#include <stdio.h>

int main()
{
    int grade;

    printf("Enter your grade: ");
    scanf("%d", &grade);

    if (grade < 0 || grade > 100)
    {
        printf("Invalid grade.\n");
    }
    else if (grade < 50)
    {
        printf("Failed\n");
    }
    else if (grade < 65)
    {
        printf("Pass\n");
    }
    else if (grade < 75)
    {
        printf("Good\n");
    }
    else if (grade < 85)
    {
        printf("Very Good\n");
    }
    else
    {
        printf("Excellent\n");
    }

    return 0;
}

```

---

### **Lab 3:** Simple Login System

Write a code for a simple login system. The system should ask the user to enter their ID and then print their corresponding name.
Available IDs are:

* `1234` -> Ahmed
* `5677` -> Youssef
* `1145` -> Mina
* Any other ID should print "Wrong ID".

<img width="421" height="104" alt="image" src="https://github.com/user-attachments/assets/6e3e4409-655b-4e7f-9e5e-12f404680300" />


**Code:**

```c
#include <stdio.h>

int main()
{
    int id;

    printf("Enter your ID: ");
    scanf("%d", &id);

    if (id == 1234)
    {
        printf("Welcome Ahmed\n");
    }
    else if (id == 5677)
    {
        printf("Welcome Youssef\n");
    }
    else if (id == 1145)
    {
        printf("Welcome Mina\n");
    }
    else
    {
        printf("Wrong ID\n");
    }

    return 0;
}

```

---

---

# Session 3 Labs

### **Lab 1:** Print Even Numbers (0 to 20)

Write a code that prints the even numbers in the range from 0 to 20.
*(Note: Solution 2 is more efficient because it eliminates the internal condition evaluation and increments directly by 2).*

<img width="399" height="196" alt="image" src="https://github.com/user-attachments/assets/40798523-3fd9-42f3-804a-632995d40eae" />


**Solution 1 (Using Condition):**

```c
#include <stdio.h>

int main()
{
    int i;

    for (i = 0; i <= 20; i++)
    {
        if (i % 2 == 0)
        {
            printf("%d ", i);
        }
    }

    return 0;
}

```

**Solution 2 (Direct Increments - More Efficient):**

```c
#include <stdio.h>

int main()
{
    int i;

    for (i = 0; i <= 20; i += 2)
    {
        printf("%d ", i);
    }

    return 0;
}

```

---

### **Lab 2:** Summation of 10 Numbers

Write a code that asks the user to enter 10 numbers and prints the total summation of those numbers.

<img width="396" height="187" alt="image" src="https://github.com/user-attachments/assets/0903b8b1-06fd-4c79-85c0-1ad4a89bf354" />


**Code:**

```c
#include <stdio.h>

int main()
{
    int num, sum = 0;

    for (int i = 1; i <= 10; i++)
    {
        printf("Enter number %d: ", i);
        scanf("%d", &num);

        sum += num;
    }

    printf("The summation = %d\n", sum);

    return 0;
}

```

---

### **Lab 3:** Input Validation Loop

Write a code that asks the user to enter a number less than 100. The program shall keep looping and asking for input if the user enters a number greater than or equal to 100.

<img width="461" height="187" alt="image" src="https://github.com/user-attachments/assets/72109962-4768-4703-a3b7-c7605e9f52b5" />


**Code:**

```c
#include <stdio.h>

int main()
{
    int num;

    printf("Enter a number less than 100: ");
    scanf("%d", &num);

    while (num >= 100)
    {
        printf("Invalid input. Please enter a number less than 100: ");
        scanf("%d", &num);
    }

    printf("You entered: %d\n", num);

    return 0;
}

```

---

### **Lab 4:** Number Countdown

Write a code that asks the user to enter a number and displays a countdown from that number down to 0.

<img width="532" height="250" alt="image" src="https://github.com/user-attachments/assets/896e59b8-7fa7-4e68-b587-96e60c8e9d1b" />


**Solution 1 (Using While Loop):**

```c
#include <stdio.h>

int main()
{
    int num;

    printf("Enter a number: ");
    scanf("%d", &num);

    while (num >= 0)
    {
        printf("%d\n", num);
        num--;
    }

    return 0;
}

```

**Solution 2 (Using For Loop):**

```c
#include <stdio.h>

int main()
{
    int num, i;

    printf("Enter a number: ");
    scanf("%d", &num);

    for (i = num; i >= 0; i--)
    {
        printf("%d\n", i);
    }

    return 0;
}

```

---

### **Lab 5:** Factorial Calculation

Write a program in C to calculate the factorial of an integer entered by the user using a loop.

<img width="429" height="174" alt="image" src="https://github.com/user-attachments/assets/f8ac4121-c585-4bdf-8062-da28c999e3ce" />

**Solution 1 (Using While Loop):**

```c
#include <stdio.h>

int main()
{
    int num, i = 1;
    long long factorial = 1;

    printf("Enter a positive integer: ");
    scanf("%d", &num);

    if (num < 0)
    {
        printf("Factorial is not defined for negative numbers.\n");
    }
    else
    {
        while (i <= num)
        {
            factorial *= i;
            i++;
        }

        printf("Factorial = %lld\n", factorial);
    }

    return 0;
}

```

**Solution 2 (Using Do-While Loop):**

```c
#include <stdio.h>

int main()
{
    int num, i = 1;
    long long fact = 1;

    printf("Enter a number: ");
    scanf("%d", &num);

    if (num < 0)
    {
        printf("Factorial is not defined for negative numbers.\n");
    }
    else
    {
        do
        {
            fact *= i;
            i++;
        }
        while (i <= num);

        printf("Factorial = %lld\n", fact);
    }

    return 0;
}

```

---

---

# Extra labs

### **Exercise 1:** Bit Manipulation Demo on x = 10

Demonstration of register-level bitwise masking configurations (Set, Clear, Toggle, and Read status).

**Code:**

```c
#include <stdio.h>

int main()
{
    char x = 10;   // Binary: 00001010

    x |= (1 << 0);          // Set bit 0 (Result: 11)
    printf("%d\n", x);	
		
    x &= ~(1 << 1);         // Clear bit 1 (Result: 9)
    printf("%d\n", x);	

    x ^= (1 << 3);          // Toggle bit 3 (Result: 1)
    printf("%d\n", x);

    printf("Bit 2 = %d\n", (x >> 2) & 1); // Read status of bit 2 (Result: 0)

    return 0;
}

```

---

### **Exercise 2:** Maximum Between Three Numbers Using Ternary

Write a C program to input three numbers and find the maximum between the three numbers using the conditional/ternary operator `?:`.

**Code:**

```c
#include <stdio.h>

int main()
{
    int num1, num2, num3, max;
     
    printf("Enter three numbers: ");
    scanf("%d%d%d", &num1, &num2, &num3);

    // Nested ternary implementation
    max = (num1 > num2 && num1 > num3) ? num1 :
          (num2 > num3) ? num2 : num3;

    printf("\nMaximum between %d, %d and %d = %d\n", num1, num2, num3, max);

    return 0;
}

```
