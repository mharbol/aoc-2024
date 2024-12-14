# Rationale by Day

## [Day 1](https://adventofcode.com/2024/day/1)
[My solution](src/solution/Day01.cpp) is nothing too special.
I decided to not get fancy with the parser and just used the numbers' fixed lengths.
Part 1, sum the absolute differences in the sorted vectors.
Part 2 was a classic `map` scenario made easier by not needing to keep track of the numbers already counted.
C++ inserts a value not present in the map when using the bracket operator, that cleaned up the code a little when counting and summing.

## [Day 2](https://adventofcode.com/2024/day/2)
Not very proud of [my solution](src/solution/Day02.cpp).
For Part 1, I made a vector of the differences and checked if they were within the rules of the problem.
With part 2 I decided to be lazy and just dropped indexes and ran my part 2 check on the result.
Not the most optimal, but it works.

## [Day 3](https://adventofcode.com/2024/day/3)
[My solution](src/solution/Day03.cpp) makes great use of `std::regex`.
I heard that library was terrible but it was not too bad to make a pretty simple solution.
For part 2 I had a bit of a gotcha in that the "do" state would get reset to true on each line.
Once I figured that out it was not too bad of a problem.
Of course I got a little help verifying my patterns with [regex101](https://regex101.com/).

## [Day 4](https://adventofcode.com/2024/day/4)
For [today](src/solution/Day04.cpp), part 2 was easier than part 1.
Making an 'X' finder function made what would be a lot of checks really quick.
For part 1 I had to do the classic search all 8 ways and worry about out of bounds...
one day I'll do that efficiently.

## [Day 5](https://adventofcode.com/2024/day/5)
[Today's solution](src/solution/Day04.cpp) took a minute to get up and going.
For part one I made a map to all the pages that must be after a number and made sure they were not before it.
In part two, I built up the correct ordering by adding a new page and bubbling it down to where it was valid before inserting
and bubbling down the next one.

## [Day 6](https://adventofcode.com/2024/day/6)
[Today](src/solution/Day06.cpp) was not the prettiest but it works.
I used a slightly different implementation originally for part 1 (marked the visited grids with a different character for counting),
but creating the set of pairs was needed for part 2 so I cleaned up the first one to use that utility instead.
For part 2, I realized I only needed to test the positions that would be in the path followed by part 1 and tested them all.
The only consideration to add was that I needed to account for direction travelled to be sure I was in a cyclic state.
To make it a bit faster, I only logged when the guard took a turn and checked for cycles then.

## [Day 7](https://adventofcode.com/2024/day/7)
[Today's solution](src/solution/Day07.cpp) was a fun recursion problem.
The hardest part was finally getting to a place where `std::stoi` throws because a parsed value is greater than 32 bits.
It took me a bit of time to realize that and replace it with `std::stoul` and then the rest was smooth sailing.

## [Day 8](https://adventofcode.com/2024/day/8)
[Today](src/solution/Day08.cpp) looks pretty scary but it was overall alright.
In part 1 I just had to make sure all of my rules and checks worked both if the antennas were offset to the left or right.
With part 2, my part 1 solution adapted fairly easily using the `gcd` of the row and column distances to get the antinodes.

## [Day 9](https://adventofcode.com/2024/day/9)
[Today](src/solution/Day09.cpp) was not super good.
Finding the open spaces on the left and filled spaces on the right for part 1 was pretty simple.
Part 2's open block finding was a little ugly but it works fast enough so I am not going to optimize it;
I pretty much did exactly as the puzzle described and kept finding the nearest open spot on the left for the next file on the right.

## [Day 10](https://adventofcode.com/2024/day/10)
Got a bit upset with myself on [today](src/solution/Day10.cpp)'s puzzle.
Did part 2 first by accident by not reading the prompt carefully enough.
It was a little disheartening to think I was messing up a simple depth first search before realizing that was not what the problem asked.
Part 1 ended up being pretty much the same as part 2 but with counting distinct endpoints rather than distinct paths.
My old friend `std::set` coming to the rescue again.

## [Day 11](https://adventofcode.com/2024/day/11)
[Today](src/solution/Day11.cpp) was a fun exercise in memoization.
Originally in part 1 I followed what the problem said to a T;
I left `Day11::blink()` in the source just for reference.
After the expand-and-add-to-the-list approach did not scale well, I heard "Hello, I'm Johnny Cache" and got to work on the final solution.
I am amazed at the speed that approach achieved.

## [Day 12](https://adventofcode.com/2024/day/12)
[This one](src/solution/Day12.cpp) has to be on the top of my list to clean up.
I tried all sorts of silly things in part 1 before finally deciding to get the perimeters as part of my flood fill.
Part 2 is where it gets really bad.
I eventually got the `checkSides()` function working after an embarrassing amount of code duplication.

## [Day 13](https://adventofcode.com/2024/day/13)
Very happy with [today](src/solution/Day13.cpp).
Right away, I realized this was just solving a system of linear equations and decided bust out the inverse 2x2 matrix formula to solve it.
The red herring of today in the question was stating that you were looking for the minimum cost of pressing buttons.
In a system like this, there are 0, 1, or infinite solutions.
Fortunately none of the systems here were linearly dependant so I didn't have to handle that case, might be a cool go-back to add that
just for completeness.
