**The key insight** is dead simple: `arr[row][col]` means the first index picks the row, second picks the column. So:

- `arr[i][j]` → outer `i` pins the **row**, inner `j` walks across it → you're summing **rows**
- `arr[j][i]` → outer `i` now sits in the **column** slot, inner `j` walks **down** it → you're summing **columns**

💡 The trick: In arr[row][col], whichever index you put 
first is the one the outer loop controls. 
arr[i][j] → outer loop controls row. arr[j][i] → outer loop controls column. 
Same two loops, same two variables — just flip which dimension is "pinned".
