#include <gtest/gtest.h>
#include "log_append.hpp"
#include <fstream>
#include <filesystem>
#include <sstream>
#include <thread>

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

    // Helper to create a very long string of specified length
    std::string createLongString(size_t length, char fillChar = 'A') {
        return std::string(length, fillChar);
    }

    // Helper to create string with special characters
    std::string createMaliciousString() {
        return std::string("../../etc/passwd\0\n\r%x%n\\\"';--");
    }
};

// Original Tests

// Test invalid batch file format
TEST_F(LogAppendTest, ProcessInvalidBatchFile) {
    // Create batch file with a single invalid command
    std::vector<std::string> commands = {
        "-T ABC -K testkey123 -E John test_log.txt"  // Invalid timestamp
    };
    createBatchFile("test_batch.txt", commands);

    std::vector<std::string> args = {
        "-B",
        "test_batch.txt"
    };
    
    auto [argc, argv] = createArgv(args);
    LogAppend logAppend(argc, argv);
    ASSERT_EXIT(logAppend.process(),
                ::testing::ExitedWithCode(255),
                ".*");
    deleteArgv(argv);
}

// Test batch file processing
TEST_F(LogAppendTest, ProcessBatchFile) {
    // Create batch file with commands - note the -A flag added
    std::vector<std::string> commands = {
        "-T 1284567 -K testkey123 -E John -A test_log.txt",  // Added -A flag
        "-T 1234597 -K testkey123 -E Jane -A test_log.txt"   // Added -A flag
    };
    createBatchFile("test_batch.txt", commands);

    std::vector<std::string> args = {
        "-B",
        "test_batch.txt"
    };
    
    auto [argc, argv] = createArgv(args);
    LogAppend logAppend(argc, argv);
    ASSERT_NO_THROW(logAppend.process());
    
    // Check for file in current directory
    ASSERT_TRUE(std::filesystem::exists("test_log.txt")) 
        << "Log file was not created in current directory";
        
    deleteArgv(argv);
}

// Test single command processing
TEST_F(LogAppendTest, ProcessSingleValidCommand) {
    std::vector<std::string> args = {
        "-T", "12345678",
        "-K", "testkey123",
        "-E", "John",
        "-A",
        "test_log.txt",
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

// Test missing required arguments
TEST_F(LogAppendTest, MissingRequiredArgs) {
    std::vector<std::string> args = {
        "-T", "1234567890",
        // Missing -K (key)
        "-A", "employee",
        "-E", "John",
        "test_log.txt"
    };
    
    auto [argc, argv] = createArgv(args);
    LogAppend logAppend(argc, argv);
    ASSERT_EXIT(logAppend.process(),
                ::testing::ExitedWithCode(255),
                ".*");
    deleteArgv(argv);
}

// Test non-existent batch file
TEST_F(LogAppendTest, NonExistentBatchFile) {
    std::vector<std::string> args = {
        "-B",
        "nonexistent.txt"
    };
    
    auto [argc, argv] = createArgv(args);
    LogAppend logAppend(argc, argv);
    ASSERT_EXIT(logAppend.process(),
                ::testing::ExitedWithCode(255),
                ".*");
    deleteArgv(argv);
}

// New Security Tests

// Buffer Overflow Tests
TEST_F(LogAppendTest, VeryLongEmployeeName) {
    std::string longName = createLongString(1024 * 1024); // 1MB string
    std::vector<std::string> args = {
        "-T", "12345678",
        "-K", "testkey123",
        "-E", longName,
        "-A",
        "test_log.txt"
    };
    
    auto [argc, argv] = createArgv(args);
    LogAppend logAppend(argc, argv);
    ASSERT_EXIT(logAppend.process(),
                ::testing::ExitedWithCode(255),
                ".*");
    deleteArgv(argv);
}

TEST_F(LogAppendTest, VeryLongKey) {
    std::string longKey = createLongString(8192);
    std::vector<std::string> args = {
        "-T", "12345678",
        "-K", longKey,
        "-E", "John",
        "-A",
        "test_log.txt"
    };
    
    auto [argc, argv] = createArgv(args);
    LogAppend logAppend(argc, argv);
    ASSERT_EXIT(logAppend.process(),
                ::testing::ExitedWithCode(255),
                ".*");
    deleteArgv(argv);
}

// Path Traversal Tests
TEST_F(LogAppendTest, PathTraversalInFilename) {
    std::vector<std::string> args = {
        "-T", "12345678",
        "-K", "testkey123",
        "-E", "John",
        "-A",
        "../../../etc/passwd"
    };
    
    auto [argc, argv] = createArgv(args);
    LogAppend logAppend(argc, argv);
    ASSERT_EXIT(logAppend.process(),
                ::testing::ExitedWithCode(255),
                ".*");
    deleteArgv(argv);
}

// Authentication Tests
TEST_F(LogAppendTest, EmptyKey) {
    std::vector<std::string> args = {
        "-T", "12345678",
        "-K", "",
        "-E", "John",
        "-A",
        "test_log.txt"
    };
    
    auto [argc, argv] = createArgv(args);
    LogAppend logAppend(argc, argv);
    ASSERT_EXIT(logAppend.process(),
                ::testing::ExitedWithCode(255),
                ".*");
    deleteArgv(argv);
}

TEST_F(LogAppendTest, KeyWithSpecialCharacters) {
    std::vector<std::string> args = {
        "-T", "12345678",
        "-K", "key\n\r\0;%x",
        "-E", "John",
        "-A",
        "test_log.txt"
    };
    
    auto [argc, argv] = createArgv(args);
    LogAppend logAppend(argc, argv);
    ASSERT_EXIT(logAppend.process(),
                ::testing::ExitedWithCode(255),
                ".*");
    deleteArgv(argv);
}

// Malformed Input Tests
TEST_F(LogAppendTest, InvalidTimestampFormats) {
    std::vector<std::pair<std::string, int>> timestamps = {
        {"0", 255},              // Too short
        {"-1", 255},            // Negative
        {"999999999999", 255},  // Too large
        {"12:34:56", 255},      // Wrong format
        {"'DROP TABLE users;--", 255}  // SQL injection attempt
    };

    for (const auto& [timestamp, expectedExit] : timestamps) {
        std::vector<std::string> args = {
            "-T", timestamp,
            "-K", "testkey123",
            "-E", "John",
            "-A",
            "test_log.txt"
        };
        
        auto [argc, argv] = createArgv(args);
        LogAppend logAppend(argc, argv);
        ASSERT_EXIT(logAppend.process(),
                   ::testing::ExitedWithCode(expectedExit),
                   ".*");
        deleteArgv(argv);
    }
}

// Batch File Security Tests
TEST_F(LogAppendTest, MaliciousBatchFileContent) {
    std::vector<std::string> commands = {
        "-T 12345678 -K testkey123 -E John -A test_log.txt\n\r",  // Normal command
        "rm -rf /\n",  // Malicious command
        "; echo 'malicious'\n",  // Command injection attempt
        "-T 12345678 -K testkey123 -E '../etc/passwd' -A test_log.txt"  // Path traversal
    };
    createBatchFile("test_batch.txt", commands);

    std::vector<std::string> args = {
        "-B",
        "test_batch.txt"
    };
    
    auto [argc, argv] = createArgv(args);
    LogAppend logAppend(argc, argv);
    ASSERT_EXIT(logAppend.process(),
                ::testing::ExitedWithCode(255),
                ".*");
    deleteArgv(argv);
}

// Race Condition Test
TEST_F(LogAppendTest, ConcurrentFileAccess) {
    const int NUM_THREADS = 10;
    std::vector<std::thread> threads;
    
    for (int i = 0; i < NUM_THREADS; i++) {
        threads.emplace_back([i, this]() {
            std::vector<std::string> args = {
                "-T", std::to_string(12345678 + i),
                "-K", "testkey123",
                "-E", "John",
                "-A",
                "test_log.txt"
            };
            
            auto [argc, argv] = createArgv(args);
            LogAppend logAppend(argc, argv);
            logAppend.process();
            deleteArgv(argv);
        });
    }
    
    for (auto& thread : threads) {
        thread.join();
    }
    
    // Verify file integrity after concurrent access
    std::ifstream logFile("test_log.txt");
    std::string line;
    int lineCount = 0;
    while (std::getline(logFile, line)) {
        lineCount++;
    }
    ASSERT_EQ(lineCount, NUM_THREADS) << "Missing or duplicate entries after concurrent access";
}

// Memory Exhaustion Test
TEST_F(LogAppendTest, LargeBatchFile) {
    // Create a very large batch file
    std::ofstream batchFile("test_batch.txt");
    for (int i = 0; i < 1000000; i++) {
        batchFile << "-T " << (12345678 + i) << " -K testkey123 -E John -A test_log.txt\n";
    }
    batchFile.close();

    std::vector<std::string> args = {
        "-B",
        "test_batch.txt"
    };
    
    auto [argc, argv] = createArgv(args);
    LogAppend logAppend(argc, argv);
    ASSERT_EXIT(logAppend.process(),
                ::testing::ExitedWithCode(255),
                ".*");
    deleteArgv(argv);
}