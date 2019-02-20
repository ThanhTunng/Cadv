#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX 1000

int min(int x, int y) {
  return (x < y ? x : y);
}

typedef struct {
  int x, y;
} re;

int M, N;
int f[MAX][MAX], top, bot, deg[MAX][MAX];
re q[MAX*MAX], trace[MAX][MAX], e[MAX][MAX][6];

int inside(int x, int y) {
  return (x >= 0 && x <= M && y >= 0 && y <= N);
}

void check(int x, int y, int u, int v) {
  if (!inside(u, v) || x == u && y == v) return;
  for (int i = 0; i < deg[x][y]; i++) {
    if (u == e[x][y][i].x && v == e[x][y][i].y) return;
  }
  e[x][y][deg[x][y]++] = (re) {u, v};
}

void push(int x, int y, int u, int v, int _f) {
  if (!inside(x, y) || f[x][y] != -1) return;
  q[top++] = (re) {x, y};
  trace[x][y] = (re) {u, v};
  f[x][y] = _f;
}

int bfs(int x, int y, int nstep) {
  memset(f, 255, sizeof(f));
  bot = 0; top = 0;
  push(x, y, -1, -1, 0);
  while (bot < top) {
    re u = q[bot++];
    if (f[u.x][u.y] == nstep) break;
    for (int i = 0; i < deg[u.x][u.y]; i++) {
      push(e[u.x][u.y][i].x, e[u.x][u.y][i].y, u.x, u.y, f[u.x][u.y] + 1);
    }
  }
  return top;
}

void readMN() {
  printf("Enter value for M and N: ");
  scanf("%d %d", &M, &N);
  printf("NUMBER OF VERTICES: %d\n", (M+1)*(N+1));
  memset(deg, 0, sizeof(deg));
  int res = 0;
  for (int i = 0; i <= M; i++) {
    for (int j = 0; j <= N; j++) {
      check(i, j, M, j);
      check(i, j, i, N);
      check(i, j, 0, j);
      check(i, j, i, 0);
      check(i, j, i + min(M - i, j), j - min(M - i, j));
      check(i, j, i - min(i, N - j), j + min(i, N - j));
      res += deg[i][j];
      /*for (int k = 0; k < deg[i][j]; k++) {
        printf("%d %d -> %d %d\n", i, j, e[i][j][k].x, e[i][j][k].y);
        }*/
    }
  }
  printf("NUMBER OF EDGES: %d\n", res);
}

void readAB_nextstate() {
  int a, b;
  printf("Enter a and b: ");
  scanf("%d %d", &a, &b);
  printf("ALL POSSIBLE NEXT STATES:\n");
  for (int i = 0; i < deg[a][b]; i++) {
    printf("(%d , %d)\n", e[a][b][i].x, e[a][b][i].y);
  }
}

void readAB_nextstate_n() {
  int a, b, n;
  printf("Enter a and b: ");
  scanf("%d %d", &a, &b);
  printf("Enter number n: ");
  scanf("%d", &n);
  printf("NUMBER OF POSSIBLE REACHABLE STATES AFTER N TRANSITIONS: %d\n", bfs(a, b, n));
  /*for (int i = 0; i < top; i++) {
    printf("%d %d\n", q[i].x, q[i].y);
    }*/
}

void backtrack(int x, int y) {
  if (trace[x][y].x != -1) backtrack(trace[x][y].x, trace[x][y].y);
  printf("(%d, %d)\n", x, y);
}

void readK() {
  int k;
  printf("Enter k: ");
  scanf("%d", &k);
  bfs(0, 0, -1);
  for (int i = 0; i < top; i++)
  if (f[q[i].x][q[i].y] != -1) {
    if (q[i].x == k || q[i].y == k) {
      printf("SOLUTION:\n");
      backtrack(q[i].x, q[i].y);
      return;
    }
  }
  printf("IMPOSSIBLE TO TAKE OUT K LITTERS.\n");
}

int main() {
  printf("MENU:\n");
  while (1) {
    printf("\n");
    printf("1. Read M and N. Print numbers of vertices and edges of graph.\n");
    printf("2. Read a and b (a <= M, b <= N); print all next states.\n");
    printf("3. Read a, b (a <= M, b <= N) and n; print all next states after n transitions.\n");
    printf("4. Read k. Print one solution to take out k liters of water.\n");
    printf("5. Read k. Print the best solution to take out k liters of water.\n");
    printf("PRESS ANY OTHER KEY TO EXIT THE PROGRAM.\n");

    int key;
    scanf("%d", &key);
    switch(key) {
    case 1: readMN(); break;
    case 2: readAB_nextstate(); break;
    case 3: readAB_nextstate_n(); break;
    case 4: readK(); break;
    case 5: readK(); break;
    default: printf("EXIT.\n"); return 0;
    }
  }
}
