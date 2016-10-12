# Autonomous-Tetris-Player
  Self playing Tetris application. AI parts of the project is by me, other parts are contribution. Written with C++.

  I followed the idea of greedy algorithm to implement my bot. I did not perform a search
with greedy algorithm but instead I used it to find reasonable locations for incoming blocks. Greedy
solutions is one of the informed search strategies like A*. The difference is greedy solution uses
just h(n) (heuristic function) to get f(n). It is similer to Uniform-Cost Search but since UCS is
uninformed, it uses g(n) (path cost) instead of h(n) to get f(n).
  
  Since my f(n) = h(n), I had to choose a rational heuristic function for my bot and it had to
be compatible with the game. As the game consists of blocks I thought choosing manhattan distance
for my h(n) would be nice. The main logic is measuring the manhattan distance between the coming 
block and appropriate locations for it. After I calculated distances I picked the best one which got the highest score.
