#include <iostream>  // For input/output (cin/cout) operations
#include <string>  // For string class (text)
#include <vector>  // For vector class (dynamic array)
#include <algorithm>  // For find_if, any_of (for searching)
#include <iomanip>  // For setw (set width) to format output
#include <limits>  // For numeric_limits and streamsize (for input validation)

using namespace std;  // Using standard namespace (for cin, cout, vector, string, etc.)

// Room structure
struct Room {
    string id;
    string type;
    string category;
    double price;
    bool available;
};
// Booking structure
struct Booking {
    string guestName;
    vector<Room> roomsBooked;
    double totalPrice;
    int numDays;
    string checkInDate;
};

// Function prototypes (declarations)
void login();
void systemMenu(vector<Room>& rooms, vector<Booking>& bookings);
void roomManagement(vector<Room>& rooms, vector<Booking>& bookings);
void bookRoom(vector<Room>& rooms, vector<Booking>& bookings);
void cancelRoom(vector<Room>& rooms, vector<Booking>& bookings);
void bookingManagement(const vector<Booking>& bookings);
void searchRoom(const vector<Room>& rooms);
void displayAvailableRooms(const vector<Room>& rooms);
void prepareBills(const vector<Booking>& bookings);
void displayBookings(const vector<Booking>& bookings);


// Main function (entry point)
int main() {
    login();
    // Vector to store room details (ID, type, category, price, availability)
    vector<Room> rooms = {
            {"101", "Single Room", "AC", 50.0, true},
            {"102", "Double Room", "Non-AC", 70.0, true},
            {"103", "Family Room", "AC", 100.0, true},
            {"104", "Twin Room", "AC", 60.0, true},
            {"105", "Standard Room", "Non-AC", 80.0, true},
            {"106", "Deluxe Room", "AC", 120.0, true},
            {"107", "Suite", "AC", 150.0, true},
            {"108", "Penthouse", "AC", 200.0, true},
            {"109", "Economy Room", "Non-AC", 40.0, true},
            {"110", "VIP Room", "AC", 250.0, true}
    };
    vector<Booking> bookings;  // Vector to store bookings

    systemMenu(rooms, bookings);  // Display system menu

    return 0;  // Return 0 to indicate successful completion of program execution (exit status)
}


void login() {
    string username, password;
    const string correctUsername = "user";  // Correct username
    const string correctPassword = "user";  // Correct password

    do {
        cout << "*****************************" << endl;
        cout << "         USER LOGIN          " << endl;
        cout << "*****************************" << endl;
        cout << "Enter username: " << endl;
        cin >> username;
        cout << "Enter password: " << endl;
        cin >> password;

        if (username != correctUsername || password != correctPassword) {
            cout << "Invalid username or password. Please try again." << endl;
        }
        // Clear input buffer
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    } while (username != correctUsername || password != correctPassword);

    cout << "Logged in successfully!" << endl;
    cout << "\n--- Welcome To Moon Hotel Management System ---" << endl;
}


void systemMenu(vector<Room>& rooms, vector<Booking>& bookings) {
    int choice;
    do {
        std::cout << std::endl;  // New line
        cout << "*****************************" << endl;
        cout << "          MAIN MENU          " << endl;
        cout << "*****************************" << endl;
        cout << "1. Room Management" << endl;
        cout << "2. Booking Management" << endl;
        cout << "3. Exit" << endl;
        cout << "Enter your choice (1-3): ";

        // Input validation
        while (!(cin >> choice)) {
            cout << "Invalid input... Please enter valid input: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        switch (choice) {
            case 1:
                roomManagement(rooms, bookings);
                break;
            case 2:
                bookingManagement(bookings);
                break;
            case 3:
                std::cout << std::endl;
                cout << "Exiting program... Thank you!" << endl;
                break;
            default:
                cout << "Invalid choice... Please try again." << endl;
                break;
        }
    } while (choice != 3);
}


void roomManagement(vector<Room>& rooms, vector<Booking>& bookings) {
    int choice;
    do {
        std::cout << std::endl;  // New line
        cout << "*****************************" << endl;
        cout << "       ROOM MANAGEMENT       " << endl;
        cout << "*****************************" << endl;
        cout << "1. Search Room" << endl;
        cout << "2. Display Available Rooms" << endl;
        cout << "3. Book Room" << endl;
        cout << "4. Cancel Booking Room" << endl;
        cout << "5. Back to Main Menu" << endl;
        cout << "Enter your choice (1-5): ";

        while (!(cin >> choice)) {
            cout << "Invalid input... Please enter valid input: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        switch (choice) {
            case 1:
                searchRoom(rooms);
                break;
            case 2:
                displayAvailableRooms(rooms);
                break;
            case 3:
                bookRoom(rooms, bookings);
                break;
            case 4:
                cancelRoom(rooms, bookings);
                break;
            case 5:
                cout << "Returning to main menu." << endl;
                break;
            default:
                cout << "Invalid choice... Please try again." << endl;
                break;
        }
    } while (choice != 5);
}


void bookRoom(vector<Room>& rooms, vector<Booking>& bookings) {
    string roomId, guestName, checkInDate;
    int numDays;
    std::cout << std::endl;
    cout << "Enter Room ID to book: " << endl;
    cin >> roomId;  // Input room ID

    // Find room by ID and available status
    auto it = find_if(rooms.begin(), rooms.end(), [roomId](const Room& room) {
        return room.id == roomId && room.available;
    });

    // If room found and available, book room and add booking to bookings vector
    if (it != rooms.end()) {
        cout << "Enter guest name: " << endl;
        cin >> guestName;

        cout << "Enter check-in date (YYYY-MM-DD): " << endl;
        cin >> checkInDate;

        cout << "Enter number of days for stay: " << endl;
        cin >> numDays;

        it->available = false;  // Set room as not available

        [[maybe_unused]] double totalPrice = it->price * numDays;  // Calculate total price

        bookings.push_back({guestName, {*it}, totalPrice, numDays, checkInDate});  // Add booking to bookings vector

        cout << "Room booked successfully!" << endl;
    } else {
        cout << "Room not found or already booked." << endl;
    }
}


void cancelRoom(vector<Room>& rooms, vector<Booking>& bookings) {
    string roomId;
    std::cout << std::endl;
    cout << "Enter Room ID to cancel booking: ";
    cin >> roomId;  // Input room ID

    // Find booking by room ID using
    auto bookingIt = find_if(bookings.begin(), bookings.end(), [roomId](const Booking& booking) {
        return any_of(booking.roomsBooked.begin(), booking.roomsBooked.end(), [roomId](const Room& room) {
            return room.id == roomId;
        });
    });

    // If booking found, set room as available and remove booking from bookings vector
    if (bookingIt != bookings.end()) {
        auto roomIt = find_if(rooms.begin(), rooms.end(), [roomId](const Room& room) {
            return room.id == roomId;
        });

        if (roomIt != rooms.end()) {
            roomIt->available = true;  // Set room as available
            bookings.erase(bookingIt);  // Remove booking from bookings vector
            cout << "Room booking canceled successfully!" << endl;
        }
    } else {
        cout << "Room booking not found." << endl;
    }
}


void bookingManagement(const vector<Booking>& bookings) {
    int choice;
    do {
        std::cout << std::endl;
        cout << "*****************************" << endl;
        cout << "    BOOKING MANAGEMENT       " << endl;
        cout << "*****************************" << endl;
        cout << "1. Prepare Bills" << endl;
        cout << "2. Display Bookings" << endl;
        cout << "3. Back to Main Menu" << endl;
        cout << "Enter your choice (1-3): ";

        while (!(cin >> choice)) {
            cout << "Invalid input... Please enter valid input: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        switch (choice) {
            case 1:
                prepareBills(bookings);
                break;
            case 2:
                displayBookings(bookings);
                break;
            case 3:
                cout << "Returning to main menu." << endl;
                break;
            default:
                cout << "Invalid choice... Please try again." << endl;
                break;
        }
    } while (choice != 3);
}


void searchRoom(const vector<Room>& rooms) {
    string roomId;
    std::cout << std::endl;
    cout << "Enter Room ID to search: ";
    cin >> roomId;  // Input room ID

    for (const auto& room : rooms) {
        if (room.id == roomId) {
            cout << "Room found!" << endl;
            cout << "Room ID: " << room.id << endl;
            cout << "Room Type: " << room.type << endl;
            cout << "Room Category: " << room.category << endl;
            cout << "Room Price: " << room.price << " USD per night" << endl;
            cout << "Room Availability: " << (room.available ? "Available" : "Not Available") << endl;
            return;
        }
    }
    cout << "Room not found." << endl;
}


void displayAvailableRooms(const vector<Room>& rooms) {
    std::cout << std::endl;  // New line
    cout << "Available Rooms:" << endl;
    // Display available rooms
    for (const auto& room : rooms) {
        if (room.available) {
            cout << "Room ID: " << room.id << " | Type: " << room.type << " | Category: " << room.category << " | Price: " << room.price << " USD per night" << endl;
        }
    }
}


void prepareBills(const vector<Booking>& bookings) {
    string roomId;
    std::cout << std::endl;  // New line
    cout << "Enter Room ID to prepare bill: ";
    cin >> roomId;  // Input room ID

    // Find booking by room ID using l
    auto bookingIt = find_if(bookings.begin(), bookings.end(), [roomId](const Booking& booking) {
        return any_of(booking.roomsBooked.begin(), booking.roomsBooked.end(), [roomId](const Room& room) {
            return room.id == roomId;  // Check if room ID matches
        });
    });

    if (bookingIt != bookings.end()) {
        const Booking& booking = *bookingIt;  // Get booking reference
        std::cout << std::endl;
        cout << "*****************************" << endl;
        cout << "          BILL               " << endl;
        cout << "*****************************" << endl;
        std::cout << std::endl;
        // Display bill details
        cout << setw(20) << left << "Guest Name" << setw(20) << left << "Room ID" << setw(20) << left << "Check-in Date" << setw(20) << left << "Number of Days" << setw(20) << left << "Price Per Night" << setw(20) << left << "Total Price" << endl;
        for (const auto& room : booking.roomsBooked) {
            if (room.id == roomId) {
                double pricePerNight = booking.totalPrice / booking.numDays;
                cout << setw(20) << left << booking.guestName << setw(20) << left << room.id << setw(20) << left << booking.checkInDate << setw(20) << left << booking.numDays << setw(20) << left << pricePerNight << setw(20) << left << booking.totalPrice << endl;
                return;
            }
        }
    }
    std::cout << std::endl;
    cout << "Room booking not found." << endl;
}


void displayBookings(const vector<Booking>& bookings) {
    if (bookings.empty()) {
        std::cout << std::endl;
        cout << "No bookings to display." << endl;
    } else {
        std::cout << std::endl;
        cout << "*****************************" << endl;
        cout << "      DISPLAY BOOKINGS       " << endl;
        cout << "*****************************" << endl;
        std::cout << std::endl;
        // Display booking details
        cout << setw(20) << left << "Guest Name" << setw(20) << left << "Room(s) Booked" << setw(20) << left << "Check-in Date" << setw(20) << left << "Number of Days" << setw(20) << left << "Price Per Night" << setw(20) << left << "Total Price" << endl;
        for (const auto& booking : bookings) {
            string roomsBooked;
            double pricePerNight = booking.totalPrice / booking.numDays;
            for (const auto& room : booking.roomsBooked) {
                roomsBooked += room.id + ", ";  // Add room ID to roomsBooked string
            }
            // Remove last comma and space from roomsBooked string
            cout << setw(20) << left << booking.guestName << setw(20) << left << roomsBooked << setw(20) << left << booking.checkInDate << setw(20) << left << booking.numDays << setw(20) << left << pricePerNight << setw(20) << left << booking.totalPrice << endl;
        }
    }
}
