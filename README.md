# Movies_Booking_System

The Movie Booking System is a C program designed to manage seat reservations for movie screenings. It supports operations such as adding bookings, cancelling reservations, transferring bookings from a waiting list to the main queue, and displaying current bookings.


# Features
--Book Reservations: Users can book reservations with their preferred seat numbers.
--Waiting List: If the main queue is full, additional bookings are placed on a waiting list.
--Cancel Reservations: Users can cancel their reservations. If there's a waiting list, the first booking from the list is automatically transferred to the main queue.
--Seat Assignment: If the requested seat is taken, the system assigns a random available seat.
--Display Bookings: View all current bookings in the main queue and the waiting list.


# Structure
         **The system uses two main data structures:**
--Booking: Represents a single booking, including customer name, seat number, and booking status.
--Queue: Manages the collection of bookings. There are two queues: the main queue for confirmed bookings and a waiting list for overflow.


# Functions

--CreateBooking: Creates a new booking record.
--CreateQueue: Initializes a new queue for bookings.
--Enqueue: Adds a new booking to the main queue or waiting list.
--Dequeue: Removes a booking from a queue.
--CancelReservation: Cancels a specific booking.
--TransferToMain: Moves a booking from the waiting list to the main queue if there's space available.
--DisplayBookings: Displays all bookings in the main queue and waiting list.


# Requirements
C compiler (GCC recommended)
Standard C library

