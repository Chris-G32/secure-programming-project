//strtoul str to unsigned long
//Take string from unencrypted_log_eg 
#include "log_entry.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include <iterator>

std::string LogEntry::logRead(std::string logFile) {
    // Variables to track the options
    bool showState = false, showRooms = false, showTime = false, showIntersection = false;
    std::string token, name, employeeOrGuest;
    std::vector<std::string> employeesInGallery, guestsInGallery;
    std::map<int, std::vector<std::string>> roomOccupancy; // RoomID to people

    // Open log file
    std::ifstream log(logFile);
    if (!log.is_open()) {
        std::cerr << "Failed to open log file\n";
        return "error";
    }

    std::string line;
    while (std::getline(log, line)) {
        // Token validation (replace this with your token check logic)
        if (token != "expected_token") {
            std::cout << "integrity violation" << std::endl;
            return "255";
        }

        // Parse the log entry to update the gallery state
        std::istringstream iss(line);
        std::string timestamp, entryType, person, roomID;

        iss >> timestamp >> entryType >> person >> roomID;

        if (entryType == "A") {
            if (roomID.empty()) {
                if (std::find(employeesInGallery.begin(), employeesInGallery.end(), person) == employeesInGallery.end()) {
                    employeesInGallery.push_back(person);
                }
            } else {
                roomOccupancy[std::stoi(roomID)].push_back(person);
            }
        } else if (entryType == "L") {
            if (roomID.empty()) {
                employeesInGallery.erase(std::remove(employeesInGallery.begin(), employeesInGallery.end(), person), employeesInGallery.end());
            } else {
                roomOccupancy[std::stoi(roomID)].erase(std::remove(roomOccupancy[std::stoi(roomID)].begin(), roomOccupancy[std::stoi(roomID)].end(), person), roomOccupancy[std::stoi(roomID)].end());
            }
        }
    }

    if (showState) {
        std::sort(employeesInGallery.begin(), employeesInGallery.end());
        std::sort(guestsInGallery.begin(), guestsInGallery.end());
        std::cout << "Employees in gallery: " << join(employeesInGallery, ",") << "\n";
        std::cout << "Guests in gallery: " << join(guestsInGallery, ",") << "\n";

        for (const auto &room : roomOccupancy) {
            std::cout << room.first << ": " << join(room.second, ",") << "\n";
        }
    }

    if (showRooms) {
        // Show rooms a person visited
    }

    if (showTime) {
        // Calculate time spent in the gallery
    }

    if (showIntersection) {
        // Show room intersections
    }

    return "0";
}

// Helper function to join vector elements with a delimiter
std::string join(const std::vector<std::string> &elements, const std::string &delimiter) {
    std::ostringstream os;
    std::copy(elements.begin(), elements.end(), std::ostream_iterator<std::string>(os, delimiter.c_str()));
    std::string result = os.str();
    return result.substr(0, result.size() - delimiter.size());
}
