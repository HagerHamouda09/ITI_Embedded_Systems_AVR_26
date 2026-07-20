#  Session 8 Labs (Advanced Structures & Applications)

### **Lab:** Array of Structs Login System
Write a C program using structures and arrays of structures to implement a simple login system. The program handles predefined user accounts, reads credential inputs, and adds successfully verified users into an active session map.

<img width="627" height="405" alt="image" src="https://github.com/user-attachments/assets/81649bcd-ef64-4ee7-af09-8e3e02ad1ca7" />

**Code:**
```c
#include <stdio.h>
#include <string.h>

typedef struct
{
    char uname[50];
    char password[20];
} user;

int main()
{
    // Database of registered users
    user users[] =
    {
        {"admin", "1234"},
        {"guest", "2543"}
    };

    int nUsers = sizeof(users) / sizeof(users[0]);

    // Array to store users who logged in successfully
    user activeUsers[10];
    int activeCount = 0;

    char username[50];
    char password[20];
    int found = 0;

    printf("------ Login System ------\n");
    printf("Username: ");
    scanf("%s", username);

    printf("Password: ");
    scanf("%s", password);

    // Search for the entered username and password
    for(int i = 0; i < nUsers; i++)
    {
        if(strcmp(username, users[i].uname) == 0 &&
           strcmp(password, users[i].password) == 0)
        {
            found = 1;

            // Copy the user details to the active users list
            strcpy(activeUsers[activeCount].uname, users[i].uname);
            strcpy(activeUsers[activeCount].password, users[i].password);

            activeCount++;

            printf("\nLogin Successful!\n");
            break;
        }
    }

    if(!found)
    {
        printf("\nInvalid username or password.\n");
    }
    else
    {
        printf("\nActive Users:\n");
        for(int i = 0; i < activeCount; i++)
        {
            printf("%d. %s\n", i + 1, activeUsers[i].uname);
        }
    }

    return 0;
}

```

---

### **Lab :** Calculate Time Period Difference (Pass By Value)

Write a C program to calculate the difference between two time periods by using structure elements passed directly by value into a calculation block.

<img width="420" height="229" alt="image" src="https://github.com/user-attachments/assets/15a49fd5-1e5b-4ffd-971b-d3350d5a1ff7" />


**Code:**

```c
#include <stdio.h>

typedef struct
{
    int seconds;
    int minutes;
    int hours;
} TIME;

// Function prototype
TIME differenceBetweenTimePeriod(TIME start, TIME stop);

int main()
{
    TIME startTime, stopTime, diff;

    printf("Enter start time:\n");
    printf("Enter hours, minutes and seconds respectively: ");
    scanf("%d %d %d", &startTime.hours, &startTime.minutes, &startTime.seconds);

    printf("Enter stop time:\n");
    printf("Enter hours, minutes and seconds respectively: ");
    scanf("%d %d %d", &stopTime.hours, &stopTime.minutes, &stopTime.seconds);

    // Calculate the difference
    diff = differenceBetweenTimePeriod(startTime, stopTime);

    printf("\nTIME DIFFERENCE: %d:%d:%d - %d:%d:%d = %d:%d:%d\n",
           startTime.hours, startTime.minutes, startTime.seconds,
           stopTime.hours, stopTime.minutes, stopTime.seconds,
           diff.hours, diff.minutes, diff.seconds);

    return 0;
}

// Function definition
TIME differenceBetweenTimePeriod(TIME start, TIME stop)
{
    TIME diff;

    if (stop.seconds > start.seconds)
    {
        start.minutes--;
        start.seconds += 60;
    }
    diff.seconds = start.seconds - stop.seconds;

    if (stop.minutes > start.minutes)
    {
        start.hours--;
        start.minutes += 60;
    }
    diff.minutes = start.minutes - stop.minutes;
    diff.hours = start.hours - stop.hours;

    return diff;
}

```

---

### **Lab :** Calculate Time Period Difference (Pass By Address)

Optimizing Lab 5 workflows by passing a pointer parameter reference targeting the output structure memory location using arrow operators (`->`).

**Code:**

```c
#include <stdio.h>

typedef struct
{
    int seconds;
    int minutes;
    int hours;
} TIME;

void differenceBetweenTimePeriod(TIME start, TIME stop, TIME *diff);

int main()
{
    TIME startTime, stopTime, diff;

    printf("Enter start time: \n");
    printf("Enter hours, minutes and seconds respectively: ");
    scanf("%d %d %d", &startTime.hours, &startTime.minutes, &startTime.seconds);

    printf("Enter stop time: \n");
    printf("Enter hours, minutes and seconds respectively: ");
    scanf("%d %d %d", &stopTime.hours, &stopTime.minutes, &stopTime.seconds);

    // Calculate the difference between the start and stop time period
    differenceBetweenTimePeriod(startTime, stopTime, &diff);

    printf("\nTIME DIFFERENCE: %d:%d:%d - %d:%d:%d = %d:%d:%d\n", 
           startTime.hours, startTime.minutes, startTime.seconds, 
           stopTime.hours, stopTime.minutes, stopTime.seconds, 
           diff.hours, diff.minutes, diff.seconds);

    return 0;
}

void differenceBetweenTimePeriod(TIME start, TIME stop, TIME *diff)
{
    if(stop.seconds > start.seconds){
        --start.minutes;
        start.seconds += 60;
    }
    diff->seconds = start.seconds - stop.seconds;

    if(stop.minutes > start.minutes){
        --start.hours;
        start.minutes += 60;
    }
    diff->minutes = start.minutes - stop.minutes;
    diff->hours = start.hours - stop.hours;
}

```

---

---

# Session 10 Labs (Dynamic Memory & Data Structures)

### **Lab 1:** Dynamic Sized Array Bubble Sort

Write a C code that applies the Bubble Sorting Algorithm on a set of numbers allocated at runtime. The code requests a size input, allocates heap buffer frames using `malloc()`, reads items, and returns the list sorted in ascending order.

**Code:**

```c
#include <stdio.h>
#include <stdlib.h>

int main()
{
    int n, temp;
    int *arr;

    printf("Enter the number of elements: ");
    scanf("%d", &n);

    // Allocate heap memory boundaries dynamically
    arr = (int *)malloc(n * sizeof(int));

    if (arr == NULL)
    {
        printf("Memory allocation failed!\n");
        return 1;
    }

    // Input elements
    printf("Enter %d numbers:\n", n);
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &arr[i]);
    }

    // Bubble Sort (Ascending)
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - 1 - i; j++)
        {
            if (arr[j] > arr[j + 1])
            {
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }

    // Print sorted array
    printf("\nSorted Array:\n");
    for (int i = 0; i < n; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");

    // Free allocated memory space
    free(arr);

    return 0;
}

```

---

### **Lab 2:** Single Linked List Implementation

Comprehensive structural implementation tracking execution handlers to manage standard linear node behaviors: `addFirst()`, `addLast()`, and `displaylist()`.

**Code:**

```c
#include <stdio.h>
#include <stdlib.h>

// Structural self-referential template layout
typedef struct Node_t
{
    int data;
    struct Node_t *next;
} node;

// Initializing global base tracker frame mapping list head position
node *head = NULL;

// Insert a new node at the beginning of the list
void addFirst(int value)
{
    node *ptr = (node *)malloc(sizeof(node));

    if (ptr == NULL)
    {
        printf("Can't allocate memory\n");
    }
    else
    {
        ptr->data = value;

        if (head == NULL)
        {
            ptr->next = NULL;
        }
        else
        {
            ptr->next = head;
        }
        head = ptr;
    }
}

// Print all nodes currently linked within the chain sequence
void displaylist()
{
    if (head != NULL)
    {
        node *temp = head;

        while (temp != NULL)
        {
            printf("%d ", temp->data);
            temp = temp->next;
        }
        printf("\n");
    }
    else
    {
        printf("Empty list\n");
    }
}

// Insert a new node at the end of the list boundary line
void addLast(int data)
{
    node *newNode = (node *)malloc(sizeof(node));

    if (newNode != NULL)
    {
        newNode->data = data;
        newNode->next = NULL;

        if (head != NULL)
        {
            node *temp = head;

            // Traverse until reaching the final element node
            while (temp->next != NULL)
            {
                temp = temp->next;
            }
            temp->next = newNode;
        }
        else
        {
            head = newNode;
        }
    }
    else
    {
        printf("Can't allocate memory\n");
    }
}

int main()
{
    // Insertion sequences target front indices
    addFirst(4);
    addFirst(44);
    addFirst(40);

    // Insertion sequences target rear indices
    addLast(1);
    addLast(9);

    // Render final verification snapshot maps inside console output profiles
    printf("Linked List Elements: ");
    displaylist();

    return 0;
}

```
