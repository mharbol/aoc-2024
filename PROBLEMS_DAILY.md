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
I am sure there is a faster way to do this but not about to optimize something that runs in a few seconds.
