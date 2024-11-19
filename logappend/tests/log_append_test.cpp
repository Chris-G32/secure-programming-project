#include <gtest/gtest.h>
#include "log_append.hpp"
#include <fstream>
#include <filesystem>
#include <sstream>

class LogAppendTest : public ::testing::Test {
protected:
    void SetUp() override {
        cleanupTestFiles();
    }

    void TearDown() override {
        cleanupTestFiles();
    }

    void cleanupTestFiles() {
        const std::vector<std::string> testFiles = {
            "test_log.txt",
            "test_batch.txt",
            "test_empty.txt"
        };
        
        for (const auto& file : testFiles) {
            if (std::filesystem::exists(file)) {
                std::filesystem::remove(file);
            }
        }
    }

    // Helper to create argv array from vector of strings
    std::pair<int, const char**> createArgv(const std::vector<std::string>& args) {
        const char** argv = new const char*[args.size() + 1];  // +1 for program name
        argv[0] = "logappend";  // Program name
        for (size_t i = 0; i < args.size(); i++) {
            argv[i + 1] = args[i].c_str();
        }
        return {args.size() + 1, argv};
    }

    void deleteArgv(const char** argv) {
        delete[] argv;
    }

    // Helper method to create a batch file
    void createBatchFile(const std::string& filename, const std::vector<std::string>& commands) {
        std::ofstream batchFile(filename);
        for (const auto& cmd : commands) {
            batchFile << cmd << "\n";
        }
        batchFile.close();
    }
};

// Test single command processing
TEST_F(LogAppendTest, ProcessSingleValidCommand) {
    std::vector<std::string> args = {
        "-T", "1234567890",
        "-K", "testkey123",
        "-A", "employee",
        "-E", "John",
        "test_log.txt"
    };
    
    auto [argc, argv] = createArgv(args);
    LogAppend logAppend(argc, argv);
    ASSERT_NO_THROW(logAppend.process());
    ASSERT_TRUE(std::filesystem::exists("test_log.txt"));
    deleteArgv(argv);
}

// Test argument count exceeding MAX_ARGC
TEST_F(LogAppendTest, ExceedMaxArgc) {
    std::vector<std::string> args = {
        "-T", "1234567890",
        "-K", "testkey123",
        "-A", "employee",
        "-E", "John",
        "-R", "room101",
        "-L", "arrived",
        "test_log.txt",
        "extra_arg"  // This should cause it to exceed MAX_ARGC
    };
    
    auto [argc, argv] = createArgv(args);
    ASSERT_EXIT(LogAppend(argc, argv),
                ::testing::ExitedWithCode(255),
                ".*");
    deleteArgv(argv);
}

// // Test missing required arguments
// TEST_F(LogAppendTest, MissingRequiredArgs) {
//     std::vector<std::string> args = {
//         "-T", "1234567890",
//         // Missing -K (key)
//         "-A", "employee",
//         "-E", "John",
//         "test_log.txt"
//     };
    
//     auto [argc, argv] = createArgv(args);
//     LogAppend logAppend(argc, argv);
//     ASSERT_EXIT(logAppend.process(),
//                 ::testing::ExitedWithCode(255),
//                 ".*");
//     deleteArgv(argv);
// }


// // Test non-existent batch file
// TEST_F(LogAppendTest, NonExistentBatchFile) {
//     std::vector<std::string> args = {
//         "-B",
//         "nonexistent.txt"
//     };
    
//     auto [argc, argv] = createArgv(args);
//     LogAppend logAppend(argc, argv);
//     ASSERT_EXIT(logAppend.process(),
//                 ::testing::ExitedWithCode(255),
//                 ".*");
//     deleteArgv(argv);
// }

// // Test invalid batch file format
// TEST_F(LogAppendTest, ProcessInvalidBatchFile) {
//     // Create batch file with invalid commands
//     std::vector<std::string> commands = {
//         "-T invalidtime -K testkey123 -A employee -E John test_log.txt",
//         "-T 1234567891 -K testkey123 -X invalid_flag -E Jane test_log.txt"  // Invalid flag
//     };
//     createBatchFile("test_batch.txt", commands);

//     std::vector<std::string> args = {
//         "-B",
//         "test_batch.txt"
//     };
    
//     auto [argc, argv] = createArgv(args);
//     LogAppend logAppend(argc, argv);
//     ASSERT_EXIT(logAppend.process(),
//                 ::testing::ExitedWithCode(255),
//                 ".*");
//     deleteArgv(argv);
// }

// // Test batch file processing
// TEST_F(LogAppendTest, ProcessBatchFile) {
//     // Create batch file with commands
//     std::vector<std::string> commands = {
//         "-T 1234567890 -K testkey123 -A employee -E John test_log.txt",
//         "-T 1234567891 -K testkey123 -A employee -E Jane test_log.txt"
//     };
//     createBatchFile("test_batch.txt", commands);

//     std::vector<std::string> args = {
//         "-B",
//         "test_batch.txt"
//     };
    
//     auto [argc, argv] = createArgv(args);
//     LogAppend logAppend(argc, argv);
//     ASSERT_NO_THROW(logAppend.process());
//     ASSERT_TRUE(std::filesystem::exists("test_log.txt"));
//     deleteArgv(argv);
// }