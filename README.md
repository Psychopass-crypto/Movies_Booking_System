# Movies_Booking_System

The Movie Booking System is a C program designed to manage seat reservations for movie screenings. It supports operations such as adding bookings, cancelling reservations, transferring bookings from a waiting list to the main queue, and displaying current bookings.


# Introduction:
This is a full documentation of the program. The program is created to be as a Movie_Bookin_System that uses dynamically seat selection and implement queues using Linked Lists.

# Features
--Dynamic Seat Booking && Automatic Seat Assignment--
       Users choose a specific seat to book, if the seat is already taken, the system will give them the closest seat available.

--Waiting List Management && Cancellation and Transfer--
        When the Main list is full, the system automatically transfer them to a WaitingList, If someone from the main list cancelled, the system give first one on the waiting list the place with the seat.

--Display Bookings--
        Users can view all bookings in the main queue and waiting list.


# Function Descriptions
    createBooking(char customerName[], int seatNumber, char status[])
Creates a new booking with the customer's name, desired seat number, and booking status. It dynamically allocates memory for a new Booking structure and initializes it with provided values.

    createQueue(char movieName[], int maxSeats)
Initializes a queue for managing bookings for a specific movie, setting up the maximum number of seats available for reservation.

     isEmpty(Queue *queue)
Checks whether a given queue is empty, facilitating decisions in other functions regarding queue operations.

    enqueue(Queue *mainQueue, Queue *waitingList, char customerName[], int seatNumber, char status[])
Handles the addition of new bookings. It places bookings in the main queue until it reaches capacity, after which bookings are added to the waiting list. This function also deals with automatic seat reassignment if the chosen seat is already taken.

    dequeue(Queue *queue)
Removes a booking from the front of the queue, typically used for managing cancellations in the main queue.

    cancelReservation(Queue *queue, char customerName[], int seatNumber)
Allows users to cancel their reservations. It searches for the booking by name and seat number, marking it as "cancelled" or removing it from the queue.

    transferToMain(Queue *mainQueue, Queue *waitingList)
Automatically transfers the first booking from the waiting list to the main queue when a spot becomes available, ensuring the booking's seat number is valid and not already taken.

    displayBookings(Queue *queue)
Displays all bookings in a queue, including the waiting list, providing users with information about current reservations.
