# Format for our secure log

The log file will consist of the first line which will store a digest of the token.
The log begins on the second line.

## Log Entry Format

### Elements

- Timestamp: An unsigned integer.
- Name: Starts with an E or G to denote guest or employee, then the provided name.
- Action: A or L to denote arrival or leave.
- Room ID: Optional last argument to specify the room id

### Format

Same as the arguments, for simplicity of code.

**Note: Space sensitive**
[timestamp] [name] [action] [room-id (optional)]

### Examples

#### Whole File

digestofkey
10 EJohn A
11 EJohn A 10
13 GAmy A
16 GAmy A 10
17 EJohn L 10
18 EJohn L
