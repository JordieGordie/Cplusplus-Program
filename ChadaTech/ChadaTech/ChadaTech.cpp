#include <iostream>
#include <iomanip>

// Function to generate a string with n characters
std::string nCharString(int n, char c) {
    return std::string(n, c);
}

// Function to format time in 12-hour format
std::string formatTime12(int hours, int minutes, int seconds) {
    std::stringstream ss;
    ss << std::setw(2) << std::setfill('0') << (hours % 12 == 0 ? 12 : hours % 12) << ":"
        << std::setw(2) << std::setfill('0') << minutes << ":"
        << std::setw(2) << std::setfill('0') << seconds
        << (hours < 12 ? " AM" : " PM");
    return ss.str();
}

// Function to format time in 24-hour format
std::string formatTime24(int hours, int minutes, int seconds) {
    std::stringstream ss;
    ss << std::setw(2) << std::setfill('0') << hours << ":"
        << std::setw(2) << std::setfill('0') << minutes << ":"
        << std::setw(2) << std::setfill('0') << seconds;
    return ss.str();
}

class Clock12 {
private:
    int hours;
    int minutes;
    int seconds;

public:
    Clock12(int h, int m, int s) : hours(h), minutes(m), seconds(s) {}

    void addHour() {
        hours = (hours + 1) % 13;
        if (hours == 0) {
            hours = 1;  // Reset to 1 if it exceeds 12
        }
    }

    void addMinute() {
        minutes = (minutes + 1) % 60;
        if (minutes == 0) {
            // If minutes overflow, add one hour
            addHour();
        }
    }

    void addSecond() {
        seconds = (seconds + 1) % 60;
        if (seconds == 0) {
            // If seconds overflow, add one minute
            addMinute();
        }
    }

    void displayTime() const {
        std::cout << "12-HOUR CLOCK: "
            << std::setw(2) << std::setfill('0') << hours << ":"
            << std::setw(2) << std::setfill('0') << minutes << ":"
            << std::setw(2) << std::setfill('0') << seconds << " ";
    }
};

class Clock24 {
private:
    int hours;
    int minutes;
    int seconds;

public:
    Clock24(int h, int m, int s) : hours(h), minutes(m), seconds(s) {}

    void addHour() {
        hours = (hours + 1) % 24;
    }

    void addMinute() {
        minutes = (minutes + 1) % 60;
        if (minutes == 0) {
            // If minutes overflow, add one hour
            addHour();
        }
    }

    void addSecond() {
        seconds = (seconds + 1) % 60;
        if (seconds == 0) {
            // If seconds overflow, add one minute
            addMinute();
        }
    }

    void displayTime() const {
        std::cout << "24-HOUR CLOCK: "
            << std::setw(2) << std::setfill('0') << hours << ":"
            << std::setw(2) << std::setfill('0') << minutes << ":"
            << std::setw(2) << std::setfill('0') << seconds << std::endl;
    }
};

// Function to display clocks in boxes
void displayClocks(unsigned int h, unsigned int m, unsigned int s) {
    // Define the width of each clock box
    const int boxWidth = 27;

    // Top border
    std::cout << nCharString(boxWidth, '*') << "  " << nCharString(boxWidth, '*') << "\n";

    // Display 12-Hour Clock in its own box
    std::cout << "* " << std::setw(6) << "12-HOUR CLOCK" << std::setw(6) << " *  "
        << "* " << std::setw(6) << "24-HOUR CLOCK" << std::setw(6) << " *\n";

    std::cout << "* " << nCharString(3, ' ') << " *\t*\t " << nCharString(3, ' ') << " *\n";

    std::string formattedTime12 = formatTime12(h, m, s);
    std::string formattedTime24 = formatTime24(h, m, s);

    std::cout << "* " << std::setw(6) << formattedTime12 << std::setw(6) << " *  "
        << "* " << std::setw(8) << formattedTime24 << std::setw(9) << " *\n";

    std::cout << "* " << nCharString(3, ' ') << " *\t*\t " << nCharString(3, ' ') << " *\n";

    // Bottom border
    std::cout << nCharString(boxWidth, '*') << "  " << nCharString(boxWidth, '*') << "\n";
}

int main() {
    Clock12 clock12(12, 0, 0);  // Initialize 12-hour clock at 12:00:00
    Clock24 clock24(0, 0, 0);   // Initialize 24-hour clock at 00:00:00

    int choice;

    do {
        // Display both clocks in a box
        displayClocks(clock12, clock24);

        // Display menu
        std::cout << "Menu:\n";
        std::cout << "1 - Add Hour\n";
        std::cout << "2 - Add Minute\n";
        std::cout << "3 - Add Second\n";
        std::cout << "4 - Exit\n";

        // Get user input for choice
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        // Process user choice
        switch (choice) {
        case 1:
            clock12.addHour();
            clock24.addHour();
            break;
        case 2:
            clock12.addMinute();
            clock24.addMinute();
            break;
        case 3:
            clock12.addSecond();
            clock24.addSecond();
            break;
        case 4:
            std::cout << "Exiting program.\n";
            break;
        default:
            std::cout << "Invalid choice. Please try again.\n";
            break;
        }

    } while (choice != 4);

    return 0;
}
