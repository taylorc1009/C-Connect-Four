# Connect Four
### Developed using C

Consists of both single player (player versus AI) and player versus player.

## AI features
The AI has been implemented using a scoring system which is recursively called while utilizing the **Minimax Algorithm**, an algorithm made to evaluate the outcome of every possible next move that could be made within the next X (depth) turns. The greater the depth, the more moves the AI can predict.


### Minimax Algorithm
It works by, firstly, making a copy of the board and making a move in the first column as the AI, then since the next turn is the players it will make a move as the player (again in the first column), then the AI again. This will continue until depth equals one. Once it does, depth zero tells the algorithm to return the evaluated score of the copied board's final state with those moves the algorithm made on it. It then determines if it was either good for the AI or bad for the player, compared to the previous evaluation. Then it plays the next move at depth one in the second column, evaluates the board again, then again plays in the third column and so on until the final column is reached. When it is, the algorithm then goes back to the previous players turn and moves their next move into the second column and starts making the next players moves in every column again. This continues until the AI's first move and the move at depth 1 is in the last available column.

The algorithm is very thorough but it quickly becomes a very large procedure as you increase the depth. The sum of it's recursions is given by calculating (board's length of X)^(depth + 1), so if we had the default connect 4 dimensions (7x6) with a depth of 6 then the occurances of Minimax would become 7^7 (which equals 823,543). We can prevent this many occurances by implementing what is known as **Alpha-Beta Pruning**.


### Alpha-Beta Pruning
The Minimax algorithm finds the best score of a generated series of moves, being the highest for one player (the AI) and the lowest for the other (the user). With this logic, we can cut the amount of occurances by determining if the current series of moves will be better than the previous ones or not. For example, say the AI found a series of moves where the score for the player is -30, then on the next it finds early on during evaluation that the score can only be as low as -10. This means that we can eliminate this whole branch of evaluations as the algorithm already has a better move to overcome the player. With this, we can have a greater depth without having to sacrifice processing time.
