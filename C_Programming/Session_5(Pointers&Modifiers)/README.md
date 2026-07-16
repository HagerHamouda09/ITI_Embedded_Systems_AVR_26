# Session 6 Pointers (Continued) & Data Modifiers

### **Lab 4:** Sum of Array Elements Using Pointers
Write a C code that calculates the summation of an array using a pointer on its first element.

**Code:**
```c
#include <stdio.h>

int sumArray(int *ptr, int size)
{
    int sum = 0;
    
    for(int i = 0; i < size; i++)
    {
        sum += *(ptr + i);
    }
    
    return sum;
}

int main()
{
    int arr[10];
    int sum = 0;
    
    for (int i = 0; i < 10; i++)
    {
        printf("Enter number %d: ", i);
        scanf("%d", &arr[i]);
    }
    
    sum = sumArray(arr, 10);
    
    printf("Sum is %d\n", sum);
    return 0;
}

```

---

---

# Session 7 Labs (Data Modifiers & Types)

### **Lab 1:** Compiler Sign Representation Test

Write a C code to check the type of sign representation technique used in your compiler.
The code sequence is:

1. Define an unsigned integer variable and assign `-1` to it.
2. Print the variable using the `%u` specifier.
3. The printed value will reveal the architecture method:
* **Sign Magnitude:** `2147483649` (`0b10000000000000000000000000000001`)
* **1's Complement:** `4294967294` (`0b11111111111111111111111111111110`)
* **2's Complement:** `4294967295` (`0b11111111111111111111111111111111`)



**Code:**

```c
#include <stdio.h>

int main()
{
    unsigned int num = -1;

    printf("Value = %u\n", num);

    return 0;
}

```

---

### **Lab 2:** Size of Basic Data Types

Write a C code to print the size of all basic data types: `char`, `int`, `float`, and `double`.

<img width="257" height="205" alt="image" src="https://github.com/user-attachments/assets/1852d272-e43b-444a-8e41-28bb621b4742" />


**Code:**

```c
#include <stdio.h>

int main()
{
    printf("Size of char   = %zu byte(s)\n", sizeof(char));
    printf("Size of int    = %zu byte(s)\n", sizeof(int));
    printf("Size of float  = %zu byte(s)\n", sizeof(float));
    printf("Size of double = %zu byte(s)\n", sizeof(double));

    return 0;
}

```
