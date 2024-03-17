#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <time.h>
#include <stdbool.h>
typedef struct Booking
{
    char customerName[50];
    int seatNumber;
    char status[20]; 
    struct Booking *next;
} Booking;

typedef struct Queue
{
    char movieName[100];
    int maxSeats;
    int currentSeats; 
    Booking *front;
    Booking *rear;
} Queue;

// Function prototypes
Booking *createBooking(char customerName[], int seatNumber, char status[]);
Queue *createQueue(char movieName[], int maxSeats);
int isEmpty(Queue *queue);
void enqueue(Queue *mainQueue, Queue *waitingList, char customerName[], int seatNumber, char status[]);
void dequeue(Queue *queue);
void cancelReservation(Queue *queue, char customerName[], int seatNumber);
void transferToMain(Queue *mainQueue, Queue *waitingList);
void displayBookings(Queue *queue);


Booking *createBooking(char customerName[], int seatNumber, char status[])
{
    Booking *newBooking = (Booking *)malloc(sizeof(Booking));
    if (!newBooking)
        return NULL;
    strcpy(newBooking->customerName, customerName);
    newBooking->seatNumber = seatNumber;
    strcpy(newBooking->status, status);
    newBooking->next = NULL;
    return newBooking;
}

Queue *createQueue(char movieName[], int maxSeats)
{
    Queue *queue = (Queue *)malloc(sizeof(Queue));
    if (!queue)
        return NULL;
    strcpy(queue->movieName, movieName);
    queue->maxSeats = maxSeats;
    queue->currentSeats = 0;
    queue->front = NULL;
    queue->rear = NULL;
    return queue;
}

int isEmpty(Queue *queue)
{
    return queue->front == NULL;
}

void enqueue(Queue *mainQueue, Queue *waitingList, char customerName[], int seatNumber, char status[])
{
    if (seatNumber < 1 || seatNumber > mainQueue->maxSeats)
    {
        printf("Invalid seat number. Please choose a seat number between 1 and %d.\n", mainQueue->maxSeats);
        return; 
    }
    
    Queue *targetQueue = mainQueue->currentSeats < mainQueue->maxSeats ? mainQueue : waitingList;

    
    if (targetQueue == mainQueue && mainQueue->currentSeats < mainQueue->maxSeats)
    {
        bool seatTaken = false;
        for (Booking *current = mainQueue->front; current != NULL; current = current->next)
        {
            if (current->seatNumber == seatNumber && strcmp(current->status, "cancelled") != 0)
            {
                seatTaken = true;
                break;
            }
        }

        
        if (seatTaken)
        {
            do
            {
                seatNumber = rand() % mainQueue->maxSeats + 1; 
                seatTaken = false;
                for (Booking *current = mainQueue->front; current != NULL; current = current->next)
                {
                    if (current->seatNumber == seatNumber && strcmp(current->status, "cancelled") != 0)
                    {
                        seatTaken = true;
                        break;
                    }
                }
            } while (seatTaken);
            printf("Original seat was taken. Assigned random seat: %d\n", seatNumber);
        }
    }

    
    Booking *newBooking = createBooking(customerName, seatNumber, status);
    if (!newBooking)
        return; 

    
    if (isEmpty(targetQueue))
    {
        targetQueue->front = targetQueue->rear = newBooking;
    }
    else
    {
        targetQueue->rear->next = newBooking;
        targetQueue->rear = newBooking;
    }

    
    if (targetQueue == mainQueue)
    {
        targetQueue->currentSeats++;
    }
    else
    {
        printf("Added to the waiting list.\n");
    }
}

void dequeue(Queue *queue)
{
    if (isEmpty(queue))
    {
        printf("Queue is empty.\n");
        return;
    }
    Booking *temp = queue->front;
    queue->front = queue->front->next;
    if (queue->front == NULL)
    {
        queue->rear = NULL;
    }
    free(temp);
    queue->currentSeats--;
}

void cancelReservation(Queue *queue, char customerName[], int seatNumber)
{
    Booking *current = queue->front;
    Booking *previous = NULL;
    while (current != NULL)
    {
        if (strcmp(current->customerName, customerName) == 0 && current->seatNumber == seatNumber)
        {
            if (previous == NULL)
            { 
                queue->front = current->next;
            }
            else
            { 
                previous->next = current->next;
                if (current->next == NULL)
                { 
                    queue->rear = previous;
                }
            }
            free(current);
            printf("Reservation cancelled for %s, seat number %d.\n", customerName, seatNumber);
            queue->currentSeats--; 
            return;
        }
        previous = current;
        current = current->next;
    }
    printf("Reservation not found.\n");
}

void transferToMain(Queue *mainQueue, Queue *waitingList)
{
    if (isEmpty(waitingList))
    {
        printf("Waiting list is empty.\n");
        return;
    }
    if (mainQueue->currentSeats < mainQueue->maxSeats)
    {
        Booking *transfer = waitingList->front;
        waitingList->front = waitingList->front->next;
        if (waitingList->front == NULL)
        {
            waitingList->rear = NULL; 
        }

      
        bool seatTaken = false;
        for (Booking *current = mainQueue->front; current != NULL; current = current->next)
        {
            if (current->seatNumber == transfer->seatNumber)
            {
                seatTaken = true;
                break;
            }
        }

       
        if (seatTaken || transfer->seatNumber < 1 || transfer->seatNumber > mainQueue->maxSeats)
        {
            do
            {
                transfer->seatNumber = rand() % mainQueue->maxSeats + 1; 
                seatTaken = false;
                for (Booking *current = mainQueue->front; current != NULL; current = current->next)
                {
                    if (current->seatNumber == transfer->seatNumber)
                    {
                        seatTaken = true;
                        break;
                    }
                }
            } while (seatTaken); 
            printf("Assigned new seat number %d to transferred booking.\n", transfer->seatNumber);
        }

      
        transfer->next = NULL;
        if (isEmpty(mainQueue))
        {
            mainQueue->front = mainQueue->rear = transfer;
        }
        else
        {
            mainQueue->rear->next = transfer;
            mainQueue->rear = transfer;
        }
        mainQueue->currentSeats++; 

        printf("Transferred booking for %s, seat number %d, from the waiting list to the main queue.\n", transfer->customerName, transfer->seatNumber);
    }
    else
    {
        printf("No space available in the main queue for transfer.\n");
    }
}

void displayBookings(Queue *queue)
{
    if (isEmpty(queue))
    {
        printf("No bookings available for %s.\n", queue->movieName);
        return;
    }
    Booking *current = queue->front;
    printf("\nBookings for '%s':\n", queue->movieName);
    while (current)
    {
        printf("Customer: %s, Seat Number: %d, Status: %s\n", current->customerName, current->seatNumber, current->status);
        current = current->next;
    }
}


int main()
{
    srand(time(NULL)); 

    Queue *movieQueue = createQueue("SpiderMan: No Way Home", 3);                       
    Queue *waitingList = createQueue("Waiting List for SipderMan: No Way Home", INT_MAX); 

    int choice;
    char customerName[50];
    int seatNumber;
    char status[20];

    do
    {
        printf("\n=== Movie Booking System ===\n");
        printf("1. Add Booking\n2. Cancel Reservation\n3. Display Bookings\n4. Exit\nEnter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            printf("Enter customer name: ");
            scanf("%49s", customerName);
            printf("Enter seat number: ");
            scanf("%d", &seatNumber);
            printf("Enter status (confirmed/pending): ");
            scanf("%19s", status);
            enqueue(movieQueue, waitingList, customerName, seatNumber, status);
            break;
        case 2:
            printf("Enter customer name to cancel reservation: ");
            scanf("%49s", customerName);
            printf("Enter seat number: ");
            scanf("%d", &seatNumber);
            cancelReservation(movieQueue, customerName, seatNumber);
            transferToMain(movieQueue, waitingList);
            break;
        case 3:
            printf("\n--- Main List ---\n");
            displayBookings(movieQueue);
            printf("\n--- Waiting List ---\n");
            displayBookings(waitingList);
            break;
        case 4:
            printf("Exiting program.\n");
            break;
        default:
            printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 4);

    return 0;
}
