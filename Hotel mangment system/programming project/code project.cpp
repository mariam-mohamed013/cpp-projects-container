#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <ctime>
#include <sstream>
#include <algorithm> // for std::transform

using namespace std;

const int max_rooms = 350;
const int max_bookings = 100;

// Enumeration for types of beds
enum class bedtype {
    king,
    queen,
    single
};

// Structure to represent a Room
struct room {
    int roomnumber;          // Room number
    int numofbeds;           // Number of beds in the room
    bedtype typeofbed;       // Type of bed in the room
    string bookingstartdate; // Start date of booking
    string bookingenddate;   // End date of booking
    double pricepernight;    // Price per night (default 0.0)
};

// Structure to represent a Booking
struct booking {
    int bookingid;           // Booking ID
    int roomnumber;          // Room number
    bedtype typeofbed;       // Type of bed
    string startdate;        // Start date of booking
    string enddate;          // End date of booking
};

// Convert bedtype from int to enum
bedtype inttobedtype(int type) {
    switch (type) {
    case 0: return bedtype::king;
    case 1: return bedtype::queen;
    case 2: return bedtype::single;
    default: return bedtype::single;
    }
}

// Array to store booked rooms
booking bookedRooms[max_bookings]; // Array of bookings
int numBookedRooms = 0; // Number of booked rooms

// Function to check if a room is available
bool isRoomAvailable(bedtype selectedBed, const string& startDate, const string& endDate) {
    for (int i = 0; i < numBookedRooms; ++i) {
        const booking& booking = bookedRooms[i];
        if (booking.typeofbed == selectedBed &&
            (startDate <= booking.enddate && endDate >= booking.startdate)) {
            return false; // Room is not available for this date range
        }
    }
    return true; // Room is available for this date range
}

// Function to book a room with a specified bed type for a given date range
void bookRoom(bedtype selectedBed, const string& startDate, const string& endDate) {
    if (isRoomAvailable(selectedBed, startDate, endDate)) {
        static int nextBookingID = 1;

        booking newBooking{ nextBookingID++, -1, selectedBed, startDate, endDate };

        bookedRooms[numBookedRooms++] = newBooking;

        cout << "Booking ID: " << newBooking.bookingid << endl;
        cout << "Booking a room from " << startDate << " to " << endDate << " with ";
        switch (selectedBed) {
        case bedtype::single:
            cout << "a single bed.";
            break;
        case bedtype::queen:
            cout << "a queen bed.";
            break;
        case bedtype::king:
            cout << "a king bed.";
            break;
        }
        cout << " Room booked successfully!" << endl;
    }
    else {
        cout << "Sorry, the room is not available for the specified date range." << endl;
    }
}

// Function to add a room
void addRoom(room rooms[], int& numrooms, int numofbeds, bedtype typeofbed) {
    if (numrooms >= max_rooms) {
        cout << "You've reached the maximum number of rooms" << endl;
        return;
    }
    int newRoomNumber = numrooms + 1;
    room newroom = { newRoomNumber, numofbeds, typeofbed, "", "", 0.0 };

    rooms[numrooms] = newroom;
    numrooms++;
    cout << "Room added: " << newRoomNumber << ": " << numofbeds << " beds, "
        << "Bed type: " << (typeofbed == bedtype::king ? "King" :
            typeofbed == bedtype::queen ? "Queen" : "Single") << endl;
}

// Function to delete a room
void deleteRoom(room rooms[], int& numrooms, int roomnumber) {
    for (int i = 0; i < numrooms; i++) {
        if (rooms[i].roomnumber == roomnumber) {
            for (int j = i; j < numrooms - 1; j++) {
                rooms[j] = rooms[j + 1];
            }
            numrooms--;
            cout << "The room " << roomnumber << " is deleted" << endl;
            return;
        }
    }
    cout << "Room " << roomnumber << " not found" << endl;
}

// Function to print all rooms
void printRooms(const room rooms[], int numrooms) {
    cout << "Current number of rooms: " << numrooms << endl;
    for (int i = 0; i < numrooms; i++) {
        cout << "Room " << rooms[i].roomnumber << ": "
            << rooms[i].numofbeds << " beds, "
            << "Bed type: " << (rooms[i].typeofbed == bedtype::king ? "King" :
                rooms[i].typeofbed == bedtype::queen ? "Queen" : "Single")
            << endl;
    }
    cout << endl;
}

// Function to print bookings
void printBookings(const booking bookings[], int numbookings) {
    cout << "Current bookings: " << numbookings << endl;
    for (int i = 0; i < numbookings; i++) {
        cout << "Booking ID: " << bookings[i].bookingid << ", Room number: " << bookings[i].roomnumber
            << ", Start date: " << bookings[i].startdate << ", End date: " << bookings[i].enddate << endl;
    }
    cout << endl;
}

// Function to add a booking
void addBooking(booking bookings[], int& numbookings, int bookingid, int roomnumber, bedtype typeofbed, const string& startdate, const string& enddate) {
    bookings[numbookings] = { bookingid, roomnumber, typeofbed, startdate, enddate };
    numbookings++;
    cout << "Booking added: ID " << bookingid << ", Room number " << roomnumber << endl;
}

// Function to delete a booking
void deleteBooking(booking bookings[], int& numbookings, int bookingid) {
    for (int i = 0; i < numbookings; i++) {
        if (bookings[i].bookingid == bookingid) {
            for (int j = i; j < numbookings - 1; j++) {
                bookings[j] = bookings[j + 1];
            }
            numbookings--;
            cout << "Booking ID " << bookingid << " is deleted" << endl;
            return;
        }
    }
    cout << "Booking ID " << bookingid << " not found" << endl;
}

// Function to save inventory to file
void saveInventoryToFile(int roomnumber, const room rooms[]) {
    ofstream output("hotel.txt");
    if (!output) {
        cout << "Error opening file for writing!" << endl;
        return;
    }
    for (int i = 0; i < roomnumber; ++i) {
        output << setw(10) << rooms[i].bookingstartdate
            << setw(10) << rooms[i].bookingenddate
            << setw(5) << rooms[i].roomnumber
            << setw(5) << rooms[i].numofbeds
            << setw(5) << static_cast<int>(rooms[i].typeofbed)
            << setw(10) << rooms[i].pricepernight << endl;
    }
    output.close();
}

// Function to load inventory from file
void loadInventoryFromFile(int& roomnumber, room rooms[]) {
    ifstream input("hotel.txt");
    if (!input) {
        cout << "Error opening file for reading!" << endl;
        return;
    }

    roomnumber = 0;
    int bedtypeInt;
    while (input >> rooms[roomnumber].bookingstartdate >> rooms[roomnumber].bookingenddate >> rooms[roomnumber].roomnumber >> rooms[roomnumber].numofbeds >> bedtypeInt >> rooms[roomnumber].pricepernight) {
        rooms[roomnumber].typeofbed = static_cast<bedtype>(bedtypeInt);
        roomnumber++;
        if (roomnumber >= max_rooms) {
            cout << "Maximum room capacity reached." << endl;
            break;
        }
    }
    input.close();
}

int calculateBill(const string& startdate, const string& enddate, double pricepernight) {
    struct tm starttm = {};
    struct tm endtm = {};
    istringstream start(startdate);
    istringstream end(enddate);

    start >> get_time(&starttm, "%Y-%m-%d");
    end >> get_time(&endtm, "%Y-%m-%d");

    time_t start_time = mktime(&starttm);
    time_t end_time = mktime(&endtm);

    if (start_time == -1 || end_time == -1) {
        cerr << "Error parsing dates!" << endl;
        return 0;
    }

    int number_of_nights = (difftime(end_time, start_time) + 86400) / (60 * 60 * 24); // Adding 1 day to include the last day
    double totalfees = number_of_nights * pricepernight;
    return totalfees;
}

// Function to get bed type from user
bedtype getBedtypeFromUser() {
    int choice;
    cout << "Choose bed type (0 = king, 1 = queen, 2 = single): ";
    cin >> choice;
    while (choice < 0 || choice > 2) {
        cout << "Invalid choice. Choose bed type (0 = king, 1 = queen, 2 = single): ";
        cin >> choice;
    }
    return static_cast<bedtype>(choice);
}

int main() {
    room rooms[max_rooms];
    int roomnumber = 0;

    char addAnother = 'y';
    while (addAnother == 'y' || addAnother == 'Y') {
        room newRoom;
        cout << "Enter room number: ";
        cin >> newRoom.roomnumber;
        cout << "Enter number of beds: ";
        cin >> newRoom.numofbeds;
        newRoom.typeofbed = getBedtypeFromUser();

        switch (newRoom.typeofbed) {
        case bedtype::king:
            newRoom.pricepernight = 10000;
            break;
        case bedtype::queen:
            newRoom.pricepernight = 8000;
            break;
        case bedtype::single:
            newRoom.pricepernight = 5000;
            break;
        }

        cout << "Enter booking start date (YYYY-MM-DD): ";
        cin >> newRoom.bookingstartdate;
        cout << "Enter booking end date (YYYY-MM-DD): ";
        cin >> newRoom.bookingenddate;

        rooms[roomnumber++] = newRoom;

        cout << "Add another room? (y/n): ";
        cin >> addAnother;
    }

    saveInventoryToFile(roomnumber, rooms);

    roomnumber = 0; // Reset before loading
    loadInventoryFromFile(roomnumber, rooms);

    for (int i = 0; i < roomnumber; ++i) {
        int bill = calculateBill(rooms[i].bookingstartdate, rooms[i].bookingenddate, rooms[i].pricepernight);
        cout << "Room " << rooms[i].roomnumber << " bill: " << bill << " EGP" << endl;
    }

    char action;
    do {
        cout << "Choose an action: (a)dd room, (d)elete room, (p)rint rooms, (b)ook room, (e)xit: ";
        cin >> action;
        switch (action) {
        case 'a': {
            int numofbeds;
            bedtype typeofbed;
            cout << "Enter number of beds: ";
            cin >> numofbeds;
            typeofbed = getBedtypeFromUser();
            addRoom(rooms, roomnumber, numofbeds, typeofbed);
            break;
        }
        case 'd': {
            int roomnum;
            cout << "Enter room number to delete: ";
            cin >> roomnum;
            deleteRoom(rooms, roomnumber, roomnum);
            break;
        }
        case 'p': {
            printRooms(rooms, roomnumber);
            break;
        }
        case 'b': {
            bedtype selectedBed = getBedtypeFromUser();
            string startDate, endDate;
            cout << "Enter booking start date (YYYY-MM-DD): ";
            cin >> startDate;
            cout << "Enter booking end date (YYYY-MM-DD): ";
            cin >> endDate;
            bookRoom(selectedBed, startDate, endDate);
            break;
        }
        case 'e':
            break;
        default:
            cout << "Invalid choice. Please try again." << endl;
        }
    } while (action != 'e');

    return 0;
}