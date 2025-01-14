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

## [Day 14](https://adventofcode.com/2024/day/14)
I did not like the premise [today](src/solution/Day14.cpp)'s part 2.
Personally, the problems should be well-defined and "most of the robots should arrange themselves into a picture of a Christmas tree"
does not sit well with me.
I know that sometimes the customer does not give good specifications or that you have to do a little digging to figure out what is going
on or what you are looking for out of software behavior, but this misses both of those a bit too much for me.
Either way, for part 1 I anticipated there being a really long series of steps for part 2 so I did some cool mod math to determine the final
positions on one step.
For part 2, I guessed that the tree would be solid and looked for an arbitrary amount of points that would all be right on top of each other.

## [Day 15](https://adventofcode.com/2024/day/15)
[Today](src/solution/Day15.cpp) is the first day of not doing the problems all on the day of.
Not that either part needed a load of time to reason over and get a good solution on, they took just enough time and I have other things going on.
In part 1 I could do the pushes in a while loop both ways.
For part 2 I had to break the logic into can push and doing the push to avoid having to undo my steps if it turns out I could not move in that direction.
The horizontal movement was pretty easy, but the vertical movement took some time before I was able to trust the recursion pushing the boxes vertically.
Effectively I travel to the end of the stack and pull each box to it's spot from the top (or bottom, depending on the direction).
Hopefully I close out these problems before January is too far gone.

## [Day 16](https://adventofcode.com/2024/day/16)
[Today](src/solution/Day16.cpp) is the new one on the top of the list to speed up.
For whatever reason, I could not get a fast solution going to find all the tiles in all the best paths.
At long last, I made a good enough solution that found the part 2 solution correctly... but I don't like it.

## [Day 17](https://adventofcode.com/2024/day/17)
[Today](src/solution/Day17.cpp) ended up becoming a week to figure out;
I am happy to have still not needed to look up any hints along the way even if that means it takes a lot longer to complete these.
In doing part 1 I didn't know what was going wrong with my program and introduced a lot of [new tests](test/test_ElfComputer.cpp)
before realizing I had two `bxc` calls in my program switch statement.
Part 2 took almost a week to figure out, but I had a blast sleuthing out the result.
The trailing `5,5,3,0` (for my input at least) prints the B register and returns to start if A is not zero.
Some other logic divides A by 8 at each iteration while the rest of the logic manipulates the B and C registers.
Looking over the structure of the program and how the values were output, I determined I could build up a solution
back to front by multiplying an initial value by 8, and adding up to 7 to smoke out the next output value.
The tricky setback was that a desired value was not guaranteed to be in that set of 8 exactly once which means some lead to dead ends.
I resolved that with a maze traversal approach and it worked on the first try (albeit, first try after a week of struggling).

## [Day 18](https://adventofcode.com/2024/day/18)
[Today](src/solution/Day18.cpp) was the first time I ever wrote an A* by name.
Once I got myself comfortable with the heuristic in the priority queue, it was a pretty easy implementation to find the shortest path.
Flood filling would have probably also been fast enough.
For part 2, I originally brute forced my way to the blocking byte but went back with a binary search so as to not make today many times slower than it could be.
Very good and relaxing day as opposed to the previous one.

## [Day 19](https://adventofcode.com/2024/day/19)
The first way I solved [today](src/solution/Day19.cpp)'s puzzle was actually by building a regex with a quick Python script
and finding all the matches in [regex101](https://regex101.com/).
In homage to that, I made and kept the `regexPart1()` solution. It is effective and easy but also slow.
I ended up making a substring pattern checker which would call itself on the next chunk for part 1.
In part 2, I already had a rep in with memoization from [Day 11](src/solution/Day11.cpp) so it felt pretty natural to do it again to find all the constructions.
I am always amazed with how effective that approach is.

## [Day 20](https://adventofcode.com/2024/day/20)
[Today](src/solution/Day20.cpp) went through a few iterations.
While looking over the problem and coming up with a good way to only check anti-collisions along the travelled path, I realized I could also check if a point 2 moves away was also on the original path.
Keeping the distance with a map I could see if that point was within the cheating threshold.
With part 2, anti-collision could cover more than one wall, so I decided to use the index in a vector tracking the path as the distance and checked all the points past the threshold.
I started to consolidate the logic in `Day20::countReductions()` but ended up leaving it in to reason through later if I ever go back to it.
I confirmed this new approach worked in general by replacing my part 1 solution with the new implementation.

## [Day 21](https://adventofcode.com/2024/day/21)
Taking my time paid off for [today](src/solution/Day21.cpp).
I took a somewhat complicated approach to get the right patterns and guessed lucky that part 2 was going to be part 1 with more arrowpads.
The key, for me, was realizing that any button press at one level means a chain of `A` button presses all the way down the line before.
This means that the traversal for any sequence starts and ends at the `A` button, therefore the problem can be broken down to the lengths of ideal traversals for subsequences at the current "depth" (number of keypads away from the narrator).
Memoization saves the day again and makes a super fast solution.

## [Day 22](https://adventofcode.com/2024/day/22)
Normally, I would be upset at slower runtime but [today](src/solution/Day22.cpp) was just a get-it-done-and-move-on kind of day.
For part 1 I followed the directions exactly and got a correct answer.
In part 2, I kept track of all the combo values at all the previous four differences and just returned the max after going through all the secret numbers.
The earlier solution used a tuple, I sped that up later with bit shifts and unordered sets.

## [Day 23](https://adventofcode.com/2024/day/23)
[Today](src/solution/Day23.cpp)'s problem brought some serious math and graph theory to the table.
In part 1 I decided to not get super fancy and just found cycles of three by seeing if any pairs of neighbors for some starting node were also neighbors.
With part 2 I had to look up and implement [Bron–Kerbosch](https://en.wikipedia.org/wiki/Bron%E2%80%93Kerbosch_algorithm)
to find the largest complete subgraph of the network.
On a go-back, I sped up the solution by implementing Bron-Kerbosch with a pivot node and using `std::unordered_set` where I could.
Great day!

## [Day 24](https://adventofcode.com/2024/day/24)
[Today](src/solution/Day24.cpp) went on for a very long time in part 2.
I decided to verify each adder and keep going until I came across a failure in the logic.
Once I found a failure, I looked at the inputs to determine the output which needed to be swapped.
Of course, hard-coding these swaps is not a very general solution so this is the first problem I will have to go back to and actually do algorithmically.
It was nice to get it finally working though...

## [Day 25](https://adventofcode.com/2024/day/25)
[Finally done](src/solution/Day25.cpp) with 2024!
I wrote a fast and easy part 1 and was surprised to see no part 2 (maybe that is the norm).
