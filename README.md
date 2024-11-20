# secure-programming-project
Group project for secure programming class Fall 2024 at Kent State.

# Building the project (Linux)
## Environment Vars and Initial Setup
In `sourceme.sh` update `export SEC_PROG_PATH=""` to the path of this repo.
Run `source scripts/sourceme.sh`
Run `mkdir executables`, this is where your executable files will be copied to.
Then run `buildProj`

# Summary
Build It; Break It; Fix It: Overview
In this project, you will implement a secure log to describe the state of an art gallery: the guests and
employees who have entered and left, and people that are in rooms. The log will be used by two
programs. One program, logappend, will append new information to this file, and the other, logread, 
will read from the file and display the state-of-the-artgallery according to a given query
over the log. Both programs will use an authentication token, supplied as a command-line argument, to
authenticate each other. You will build the most secure implementation you can; then you will have the opportunity to
attack other teams’ implementations, and fix bugs that other teams identify in your implementation.

# Secure Coding Practices
## Confidentiality
We use the ChaCha20 stream cipher for encryption for confidentiality of data, ensuring only those who know the key can update or read the information. Along with this, every query or update to the data is validated by the encrypted key. T
## Integrity
## Availability
# External Libraries
We use [libsodium](https://doc.libsodium.org/) in this project for the implementation of our HMAC, Encryption, and random nonce generation.
The specific cipher used is ChaCha20. This is a stream cipher that allows for picking up encryption and decryption operations using a counter while avoiding having to completely encrypt and reencrypt the file. The initial idea behind this approach was to leave file contents ecnrypted in memory and fetch them as needed. This ended up being outside of scope to implement this level of security however so the whole file was simply encrypted and decrypted in one go with it.