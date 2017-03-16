- CHECKING RESULT -

The console window will print a list of all of the nodes this program generates from user input in addition to the generated KeyID and starting node. You can check the visiting order and finger table of each visited node against this list. 

- IMPLEMENTATION DETAILS -

User input: First, the program checks to see if the user input can be stored as an integer via the getValidInt() function. If it can, the input is then checked to see if it exists within valid parameters (e.g. B has to be an integer value between 5 and 10 inclusive, N has to be an integer value between 5 and 15 inclusive). If either of these conditions are not met, the program prompts the user to re-enter the requested information.

Creating nodes: Once the program has stored valid inputs for B and N, it generates an array of length 2^B and initializes every index of this array to zero. Then, it enumerates over the first N indices of this array and generates a random node ID for each. Before adding this ID to the array, however, it's first checked against every existing node ID in the array to ensure that it is unique. If it is not unique, the node ID is re-generated. 

Creating finger tables: Each finger table has its zero index reserved to store the ID of its source node. From there, 1-m (or 1 through 2^(B-1)) values for N+1, N+2, N+4, N+8... N+m are generated. For each of these, the closest node of greater or equal value is selected and stored in the finger table. Each finger table is stored in an array of finger table arrays to be referenced later.

Checking for KeyID: First, we check to see if our current node's finger table contains a node that would have our key. If not, we look for the last node in its finger table and move to that one. This process is repeated until the key is located.

