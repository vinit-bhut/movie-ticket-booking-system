#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

//node for link list
struct node {
    struct node *lptr, *rptr;
    int data;
    char class[10], name[20];
    char status;
} *first = NULL, *last = NULL;

//insertion in Link List
void insert(int data, char class[10]) {
    struct node *newnode;
    newnode = (struct node *) malloc(sizeof(struct node));
    newnode->data = data;
    strcpy(newnode->class, class);
    newnode->status = 'X';
    if (first == NULL) {
        newnode->lptr = newnode;
        newnode->rptr = newnode;
        last = newnode;
        first = newnode;
    } else if (first->rptr == first) {
        newnode->lptr = first;
        newnode->rptr = first;
        first->rptr = newnode;
        first->lptr = newnode;
        last = newnode;
    } else {
        newnode->lptr = last;
        newnode->rptr = last->rptr;
        last->rptr = newnode;
        first->lptr = newnode;
        last = newnode;
    }
}

//function to create doubly circular link list of 100 nodes
void createList() {
    for (int i = 1; i <= 100; i++) {
        if (i <= 30)
            insert(i, "silver");
        else if (i <= 80)
            insert(i, "gold");
        else
            insert(i, "platinum");
    }
}

// function to display seating arrangements
void display() {
    system("cls");
    printf("\'--\' - Seat is Booked\n\'XX\' - Seat is Available\n");

    printf("\n\t\t\t\t<<<---Screen--->>>\n\n\n");
    struct node *temp = first;

    printf("\t\t\t\t<<*** Silver-200 ***>>\n\n");
    for (int i = 1; i <= 30; i++) {
        printf("%2d", temp->data);
        if (temp->status == 'X')
            printf("-XX\t ");
        else
            printf("---\t ");
        if (i % 10 == 0)
            printf("\n");
        temp = temp->rptr;
    }

    printf("\n\t\t\t\t<<*** Gold-250 ***>>\n\n");
    for (int i = 31; i <= 80; i++) {
        printf("%2d", temp->data);
        if (temp->status == 'X')
            printf("-XX\t ");
        else
            printf("---\t ");
        if (i % 10 == 0)
            printf("\n");
        temp = temp->rptr;
    }

    printf("\n\t\t\t\t<<*** Platinum-300 ***>>\n\n");
    for (int i = 81; i <= 100; i++) {
        printf("%2d", temp->data);
        if (temp->status == 'X')
            printf("-XX\t ");
        else
            printf("---\t ");
        if (i % 10 == 0)
            printf("\n");
        temp = temp->rptr;
    }
    printf("\n\n\n");
    getch();
}

//function to book seats
void book_seats() {
    system("cls");
    int n;
    int price = 0;
    struct node *temp = first;
    char name[20];

    printf("Enter Name:");
    scanf("\n");
    gets(name);
    printf("How many seats do you want to book?\n");
    scanf("%d", &n);
    int pin[n], seats[n];
    //searching for seats
    for (int i = 0; i < n; i++) {
        printf("Enter seat no. %d\n", i + 1);
        scanf("%d", &seats[i]);
        if (seats[i] >= 1 && seats[i] <= 100) {
            if (abs(seats[i] - (temp->data)) <= 50) {
                while (temp->data != seats[i])
                    temp = temp->rptr;
                //checks if seat is booked or not and pin is allocated to every tickets
                if (temp->status == '-') {
                    printf("Seat is already booked\n");
                    i--;
                } else {
                    temp->status = '-';
                    pin[i] = temp;
                    strcpy(temp->name, name);
                }
            } else {
                while (temp->data != seats[i])
                    temp = temp->lptr;
                if (temp->status == '-') {
                    printf("Seat is already booked\n");
                    i--;
                } else {
                    temp->status = '-';
                    pin[i] = temp;
                    strcpy(temp->name, name);
                }
            }
        } else {
            printf("Invalid seat number. Enter seat number between 1 to 100\n");
            i--;
        }
    }

    for (int i = 0; i < n; i++) {
        if (seats[i] >= 1 && seats[i] <= 30) {
            price += 200;
        } else if (seats[i] <= 80) {
            price += 250;
        } else {
            price += 300;
        }
    }
    //printing seat number and pin
    for (int (i) = 0; (i) < n; ++(i)) {
        printf("Seat no. - %d", seats[i]);
        printf("\tPin no.- %d\n", pin[i]);
    }
    //to print warnings and instructions
    printf("\nTotal Price:%d\n\n",price);
    printf("!!!!  INSTRUCTIONS  !!!!\n\n");
    printf("1. Please keep pin secure it is necessary if you want to cancel tickets\n");
    printf("2. Outside food is not allowed.\n");
    printf("3. Keep your ticket or its digital e-copy with you otherwise you will not be allowed in cinema hall\n");
    printf("4. The children above age 6 has to buy separate tickets.\n");
    getch();
}

//function to cancel seats
void cancel_seats() {
    system("cls");
    int n;

    printf("How many seats do you want to cancel?\n");
    scanf("%d", &n);
    int pin, seat;
    struct node *temp = first;

    //searching for seat to cancel
    for (int i = 1; i <= n; i++) {
        printf("Enter seat number:");
        scanf("%d", &seat);

        if (abs(seat - (temp->data)) <= 50) {
            while (temp->data != seat)
                temp = temp->rptr;
        }
        else{
            while (temp->data != seat)
                temp = temp->lptr;
        }
        //scanning pin to cancel tickets
        printf("Enter pin:");
        scanf("%d", &pin);
        if ((int) temp == pin) {
            temp->status = 'X';
            strcpy(temp->name, "");
            printf("Seat canceled\n");
        } else
            printf("Wrong pin\n");
        getch();
    }
}

int main() {
    int choice;
    createList();

    do {
        system("cls");
        printf("\n\n<< Movie ticket booking system >>\n\n");
        printf("->>1.Book ticket\n");
        printf("->>2.Cancel Ticket\n");
        printf("->>3.Show Available seats\n");
        printf("->>4.Exit\n");
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                book_seats();
                break;
            case 2:
                cancel_seats();
                break;
            case 3:
                display();
                break;
        }
    } while (choice != 4);

    return 0;
}