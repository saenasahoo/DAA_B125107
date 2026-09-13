README – Triangle Coin Repositioning
1. Problem Description

The program considers a triangle of coins arranged in n rows and finds the best placement of an inverted triangle using the minimum number of coin moves.

It:

Creates an upright triangle containing n(n+1)/2 coins.
Creates an inverted triangle of the same size.
Searches for the shift of the inverted triangle that gives the maximum overlap with the original triangle.
The coins that do not overlap need to be moved.
It also prints one explicit list of the required coin movements.
2. Algorithm
Read the number of rows n.

Calculate the total number of coins:

T = n(n+1)/2
Build the upright triangle and store the coordinates of all coins in up[].
Build the inverted triangle and store its coordinates in down[].
Create an occupancy grid for the upright triangle.
Try different horizontal and vertical shifts (dx, dy) of the inverted triangle.
For every shift:
Compare every coin in the shifted inverted triangle with the original triangle.
Count how many positions overlap.
Store the shift having the maximum overlap.

Calculate minimum moves as:

Minimum Moves = Total Coins - Maximum Overlap
Calculate the closed-form result:
floor(n(n+1)/6)
Compare the formula result with the result obtained through the search.
Finally, identify:
Coins that must be moved from the original position.
Empty positions where those coins must be placed.
Print the complete list of moves.
3. Time Complexity

Let the number of coins be:

T = O(n²)

The program checks:

O(n) possible values of dy
O(n) possible values of dx
O(n²) coins for every shift

Therefore:

Time Complexity = O(n⁴)

The construction of the triangles and grids takes O(n²), but the shift search dominates the running time.

4. Space Complexity

The program stores:

up[] → O(n²)
down[] → O(n²)
grid → O(n²)
bestGrid → O(n²)
from[] → O(n²)
to[] → O(n²)

Therefore:

Space Complexity = O(n²)
5. Formula Used

The program also uses the closed-form formula:

Minimum Moves = floor(n(n+1)/6)

The function:

static long formulaMoves(long n) {
    return (n * (n + 1)) / 6;
}

uses integer division to obtain the floor value.

The program compares this formula with the result obtained by searching all possible placements.

6. Example

For:

n = 4

Number of coins:

T = 4(5)/2 = 10

The minimum number of moves is:

floor(4 × 5 / 6)
= floor(20/6)
= 3

So the program should find:

Minimum moves = 3
7. Complexity Summary
Operation	                              Complexity
Building triangles                       	O(n²)
Creating occupancy grid                 	O(n²)
Searching shifts	                        O(n⁴)
Finding explicit moves	                    O(n²)
Overall Time Complexity                 	O(n⁴)
Space Complexity	                        O(n²)