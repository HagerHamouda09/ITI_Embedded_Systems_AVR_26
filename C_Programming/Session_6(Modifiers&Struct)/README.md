#  Session 7 Labs (Data Modifiers, Pointers & Const)

### **Lab 2:** Size of Basic Data Types
Write a C code to print the size of all basic data types: `char`, `int`, `float`, and `double`. Compiled with `-Wall -Wextra`.

<img width="242" height="175" alt="image" src="https://github.com/user-attachments/assets/5941cfbc-7c41-4cc5-8e92-6c3e71de271e" />

**Code:**
```c
#include <stdio.h>

int main()
{
    printf("Size of char   = %d byte(s)\n", sizeof(char));
    printf("Size of int    = %d byte(s)\n", sizeof(int));
    printf("Size of float  = %d byte(s)\n", sizeof(float));
    printf("Size of double = %d byte(s)\n", sizeof(double));

    return 0;
}

```

---

### **Lab 3:** Custom Data Type Mapping (Typedef)

Use the `typedef` keyword to define user-defined aliases for standard architectural configurations. Print their sizing using the `sizeof` operator to ensure boundaries match target constraints.

<img width="370" height="185" alt="image" src="https://github.com/user-attachments/assets/b9cbf6e8-bb01-4593-abc6-69bbbfca3bc4" />

**Code:**

```c
#include <stdio.h>

// 8-bit
typedef unsigned char u8;
typedef signed char s8;

// 16-bit
typedef unsigned short int u16;
typedef signed short int s16;

// 32-bit
typedef unsigned int u32;
typedef signed int s32;

// 64-bit
typedef unsigned long long int u64;
typedef signed long long int s64;

// Floating-point
typedef float f32;
typedef double f64;

int main()
{
    printf("Size of u8  = %d byte(s)\n", sizeof(u8));
    printf("Size of s8  = %d byte(s)\n", sizeof(s8));

    printf("Size of u16 = %d byte(s)\n", sizeof(u16));
    printf("Size of s16 = %d byte(s)\n", sizeof(s16));

    printf("Size of u32 = %d byte(s)\n", sizeof(u32));
    printf("Size of s32 = %d byte(s)\n", sizeof(s32));

    printf("Size of u64 = %d byte(s)\n", sizeof(u64));
    printf("Size of s64 = %d byte(s)\n", sizeof(s64));

    printf("Size of f32 = %d byte(s)\n", sizeof(f32));
    printf("Size of f64 = %d byte(s)\n", sizeof(f64));

    return 0;
}

```

---

### **Lab ** LED Toggle Simulation (Static Qualifier)

Write a C program that simulates the state of an LED. Create a function named `ToggleLED()` that is called 6 times from the `main()` function. Each time the function is called, it should alternate the LED state between ON and OFF using a local `static` variable and print the current state.

<img width="124" height="126" alt="image" src="https://github.com/user-attachments/assets/59437859-83a4-41b2-b4bb-54c009e5319c" />

**Code:**

```c
#include <stdio.h>

void ToggleLED(void)
{
    static int ledState = 0;

    if (ledState == 0)
    {
        printf("LED ON\n");
        ledState = 1;
    }
    else
    {
        printf("LED OFF\n");
        ledState = 0;
    }
}

int main()
{
    for (int i = 0; i < 6; i++)
    {
        ToggleLED();
    }

    return 0;
}

```

---

### **Lab** Understanding Pointer Constant Qualifiers

**Code:**

```c
#include <stdio.h>

int main()
{
    int x = 10;
    int y = 20;

    // Case 1: Normal Pointer
    printf("===== Case 1: Normal Pointer =====\n");
    int *ptr1 = &x;
    printf("Before: x = %d\n", x);
    *ptr1 = 30;      // Allowed: Value can change
    ptr1 = &y;       // Allowed: Address can change
    *ptr1 = 40;      // Allowed: Value can change
    printf("x = %d, y = %d\n\n", x, y);

    // Case 2: Pointer to Constant Value
    printf("===== Case 2: Pointer to Const =====\n");
    x = 10; y = 20;
    const int *ptr2 = &x; 
    // *ptr2 = 50;   // ERROR: Cannot modify the value through this pointer
    ptr2 = &y;       // Allowed: Address pointer holds can change
    printf("Pointer now points to y = %d\n\n", *ptr2);

    // Case 3: Constant Pointer to Variable
    printf("===== Case 3: Const Pointer =====\n");
    x = 10; y = 20;
    int *const ptr3 = &x;
    *ptr3 = 60;      // Allowed: Value target can change
    // ptr3 = &y;    // ERROR: Cannot change the address tracked by the pointer
    printf("x = %d\n\n", x);

    // Case 4: Constant Pointer to Constant Value
    printf("===== Case 4: Const Pointer to Const =====\n");
    x = 10; y = 20;
    const int *const ptr4 = &x;
    // *ptr4 = 70;   // ERROR: Cannot modify value
    // ptr4 = &y;    // ERROR: Cannot change address
    printf("Value = %d\n", *ptr4);

    return 0;
}

```

---

### **Exercise 1:** Read-Only String Printing

<img width="619" height="120" alt="image" src="https://github.com/user-attachments/assets/332b3e03-b2c9-4b99-b971-35815533ad39" />


**Code:**

```c
#include <stdio.h>

typedef unsigned char u8;

void PrintName(const u8 *ptr)
{
    while (*ptr != '\0')
    {
        printf("%c", *ptr);
        ptr++;
    }
    printf("\n");
}

int main(void)
{
    u8 name[] = "Ahmed";
    PrintName(name);

    return 0;
}

```

---

### **Exercise 2:** Fixed-Address String Modification

<img width="622" height="121" alt="image" src="https://github.com/user-attachments/assets/e298d560-8a99-4b3b-80e6-159495768f42" />

**Code:**

```c
#include <stdio.h>

typedef unsigned char u8;

void Capitalize(u8 * const ptr)
{
    for (int i = 0; ptr[i] != '\0'; i++)
    {
        if (ptr[i] >= 'a' && ptr[i] <= 'z')
        {
            ptr[i] = ptr[i] - ('a' - 'A');
        }
    }
    // ptr++; // ERROR: ptr is a constant pointer and its address cannot move
}

int main(void)
{
    u8 word[] = "computer";
    Capitalize(word);
    printf("%s\n", word);

    return 0;
}

```

---

---

#  Session 8 Labs (User-Defined Structures)

### **Lab 1:** Employee Financial Summary

Write a c code that defines a structure for employees that contains his salary,  bonus and deductions. The program shall ask the user to enter these information for three employees ( Ahmed, Waleed and Amr). 
Then the program will print the total value shall be supplied by finance team

<img width="317" height="210" alt="image" src="https://github.com/user-attachments/assets/25ce838a-169f-4727-bef3-5b01401af129" />


**Code:**

```c
#include <stdio.h>

typedef unsigned int u32;

struct Employee
{
    u32 Salary;
    u32 Bonus;
    u32 Deduction;
};

int main()
{
    struct Employee Ahmed, Waleed, Amr;
    u32 total = 0;
    
    printf("Enter Ahmed's Salary, Bonus, Deduction: ");
    scanf("%d %d %d", &Ahmed.Salary, &Ahmed.Bonus, &Ahmed.Deduction);
    
    printf("Enter Waleed's Salary, Bonus, Deduction: ");
    scanf("%d %d %d", &Waleed.Salary, &Waleed.Bonus, &Waleed.Deduction);
    
    printf("Enter Amr's Salary, Bonus, Deduction: ");
    scanf("%d %d %d", &Amr.Salary, &Amr.Bonus, &Amr.Deduction);
    
    total = (Ahmed.Salary + Ahmed.Bonus - Ahmed.Deduction) + 
            (Waleed.Salary + Waleed.Bonus - Waleed.Deduction) + 
            (Amr.Salary + Amr.Bonus - Amr.Deduction);
    
    printf("\nTotal value needed is : %d \n", total);
    
    return 0;
}

```

---

### **Lab 2:** Structure Typename Aliasing (Typedef Structure)

Optimizing Lab 1 architecture configurations cleanly by wrapping structural declarations inside `typedef` keywords to establish standard custom type instances.

**Code:**

```c
#include <stdio.h>

typedef unsigned int u32;

typedef struct {
    u32 Salary;
    u32 Bonus;
    u32 Deduction;
} Employee;

int main()
{
    Employee Ahmed, Waleed, Amr;
    u32 total = 0;
    
    printf("Enter Ahmed's Salary, Bonus, Deduction: ");
    scanf("%d %d %d", &Ahmed.Salary, &Ahmed.Bonus, &Ahmed.Deduction);
    
    printf("Enter Waleed's Salary, Bonus, Deduction: ");
    scanf("%d %d %d", &Waleed.Salary, &Waleed.Bonus, &Waleed.Deduction);
    
    printf("Enter Amr's Salary, Bonus, Deduction: ");
    scanf("%d %d %d", &Amr.Salary, &Amr.Bonus, &Amr.Deduction);
    
    total = (Ahmed.Salary + Ahmed.Bonus - Ahmed.Deduction) + 
            (Waleed.Salary + Waleed.Bonus - Waleed.Deduction) + 
            (Amr.Salary + Amr.Bonus - Amr.Deduction);
    
    printf("\nTotal value needed is : %d \n", total);
    
    return 0;
}

```

---

### **Lab 3:** Class Performance Database (Array of Structs)

Write a C code to manage a class of 10 students. Each student studies 4 subjects Math, Language, Physics and Chemistry.
First define an array of 10 elements and assign random grades for students.
The system will ask the user to enter the student ID then the system will show its grades. The software shall manage wrong IDs.

<img width="740" height="229" alt="image" src="https://github.com/user-attachments/assets/12e7d7a2-20f2-495c-9aba-6819d2b5670a" />


**Code:**

```c
#include <stdio.h>

typedef unsigned int u32;

typedef struct {
    u32 Math;
    u32 Lang;
    u32 Physics;
    u32 Chemistry;
} Student;

int main()
{
    u32 id;
    
    // Initialized database map matching 10 separate entries
    Student Class[10] = {
        {50,  60,  70,  80},  
        {100, 98,  95,  91}, 
        {47,  75,  60,  51},  
        {64,  75,  75,  90},  
        {90,  94,  89,  96},  
        {70,  80,  75,  84},  
        {46,  50,  42,  60},  
        {78,  64,  51,  90},  
        {66,  78,  63,  80},  
        {64,  67,  69,  85}   
    };
        
    printf("Enter Student ID (1-10): ");
    scanf("%d", &id);
    
    if (id >= 1 && id <= 10)
    {
        printf("\nGrades for Student %d:\n", id);
        printf("Math      : %d\n", Class[id - 1].Math);
        printf("Language  : %d\n", Class[id - 1].Lang);
        printf("Physics   : %d\n", Class[id - 1].Physics);
        printf("Chemistry : %d\n", Class[id - 1].Chemistry);
    }
    else
    {
        printf("Wrong ID!\n");
    }

    return 0;
}

```

```

```
