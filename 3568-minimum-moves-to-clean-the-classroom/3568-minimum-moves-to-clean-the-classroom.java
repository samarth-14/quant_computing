class Solution {
    public int minMoves(String[] classroom, int energy) {
        int m = classroom.length;
        int n = classroom[0].length();
        
        int startX = -1, startY = -1;
        List<int[]> litters = new ArrayList<>();
        
        for (int r = 0; r < m; r++) {
            for (int c = 0; c < n; c++) {
                char ch = classroom[r].charAt(c);
                if (ch == 'S') {
                    startX = r;
                    startY = c;
                } else if (ch == 'L') {
                    litters.add(new int[]{r, c});
                }
            }
        }
        
        int numLitters = litters.size();
        if (numLitters == 0) return 0;
        
        // Map (r, c) of each litter to an index 0..K-1
        int[][] litterIdx = new int[m][n];
        for (int i = 0; i < m; i++) Arrays.fill(litterIdx[i], -1);
        for (int i = 0; i < numLitters; i++) {
            litterIdx[litters.get(i)[0]][litters.get(i)[1]] = i;
        }
        
        int fullMask = (1 << numLitters) - 1;
        int maxMask = 1 << numLitters;
        
        // Track the maximum energy remaining for each (r, c, mask)
        int[][][] bestEnergy = new int[m][n][maxMask];
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                Arrays.fill(bestEnergy[i][j], -1);
            }
        }
        
        // Queue stores: {r, c, mask, current_energy}
        Queue<int[]> queue = new LinkedList<>();
        queue.offer(new int[]{startX, startY, 0, energy});
        bestEnergy[startX][startY][0] = energy;
        
        int steps = 0;
        int[][] dirs = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
        
        while (!queue.isEmpty()) {
            int size = queue.size();
            for (int i = 0; i < size; i++) {
                int[] curr = queue.poll();
                int r = curr[0], c = curr[1], mask = curr[2], e = curr[3];
                
                if (mask == fullMask) {
                    return steps;
                }
                
                if (e == 0) continue; // Out of energy, cannot move further
                
                for (int[] dir : dirs) {
                    int nr = r + dir[0];
                    int nc = c + dir[1];
                    
                    if (nr < 0 || nr >= m || nc < 0 || nc >= n) continue;
                    char cell = classroom[nr].charAt(nc);
                    if (cell == 'X') continue;
                    
                    int nextE = e - 1;
                    int nextMask = mask;
                    
                    if (cell == 'R') {
                        nextE = energy; // Reset energy to full
                    } else if (cell == 'L' && litterIdx[nr][nc] != -1) {
                        nextMask |= (1 << litterIdx[nr][nc]);
                    }
                    
                    if (nextE > bestEnergy[nr][nc][nextMask]) {
                        bestEnergy[nr][nc][nextMask] = nextE;
                        queue.offer(new int[]{nr, nc, nextMask, nextE});
                    }
                }
            }
            steps++;
        }
        
        return -1;
    }
}