#include "greedy.h"

using namespace std;

const int dx[4] = {1, -1, 0, 0};
const int dy[4] = {0, 0, 1, -1};

Greedy::Greedy(int row, int col, int K){
	if (K < 0){
		cout << "K must be greater than 0" << endl;
		return;
	}
	this->row = row;
	this->col = col;
	this->K = K;
	N = (K+1)*(row+1)+1;
	M = (K+1)*(col+1)+1;
	
	MAP = new int*[N];
	for (int i = 0; i < N; ++i){
		MAP[i] = new int[M];
		//memset(MAP[i], 0, sizeof(short)*M);
		for (int j = 0; j < M; ++j)
			MAP[i][j] = -1;
	}
	Q = new int[N*M];
	D = new int[N*M];
	memset(D, 63, sizeof(int)*N*M);
	maxpoints = 0;
	minlength = 0;
}

Greedy::~Greedy(){
	for (int i = 0; i < N; ++i)
		delete[] MAP[i];
	delete[] MAP;
	delete[] Q;
}

void Greedy::greedy_algorithm(){
	if (col&1){
		//int j = (K+1)*(col+1)/2;
		for (int i = (K+1); i <= (K+1)*((row+1)/2) && i/(K+1) <= K*2+1; i += (K+1)){
			int ii = i, jj  = (K+1)*(col+1)/2;
			if (MAP[ii][jj] != -1) continue;
			while (ii != 0){
				++minlength;
				if (MAP[ii+dx[1]][jj+dy[1]] == -1){
					MAP[ii][jj] = 1;
					ii += dx[1]; jj += dy[1];
				} else
				{
					MAP[ii][jj] = 2+((i/(K+1))&1);
					ii += dx[2+((i/(K+1))&1)]; jj += dy[2+((i/(K+1))&1)];
				}
			}
			++maxpoints;
		}
		for (int i = (K+1)*row; i > (K+1)*((row+1)/2) && row-i/(K+1)+1 <= K*2+1; i -= (K+1)){
			int ii = i, jj  = (K+1)*(col+1)/2;
			if (MAP[ii][jj] != -1) continue;
			while (ii != N-1){
				++minlength;
				if (MAP[ii+dx[0]][jj+dy[0]] == -1){
					MAP[ii][jj] = 0;
					ii += dx[0]; jj += dy[0];
				} else
				{
					MAP[ii][jj] = 2+((row-i/(K+1))&1);
					ii += dx[2+((row-i/(K+1))&1)]; jj += dy[2+((row-i/(K+1))&1)];
				}
			}
			++maxpoints;
		}
	}
	if (row&1){
		//int i = (K+1)*(row+1)/2;
		for (int j = (K+1); j <= (K+1)*((col+1)/2) && j/(K+1) < K*2+1; j += (K+1)){
			int ii = (K+1)*(row+1)/2, jj = j;
			if (MAP[ii][jj] != -1) continue;
			while (jj != 0){
				++minlength;
				if (MAP[ii+dx[3]][jj+dy[3]] == -1){
					MAP[ii][jj] = 3;
					ii += dx[3]; jj += dy[3];
				} else
				{
					MAP[ii][jj] = (j/(K+1)&1);
					ii += dx[(j/(K+1)&1)]; jj += dy[(j/(K+1)&1)];
				}
			}
			++maxpoints;
		}
		for (int j = (K+1)*col; j > (K+1)*((col+1)/2) && col-j/(K+1)+1 < K*2+1; j -= (K+1)){
			int ii = (K+1)*(row+1)/2, jj = j;
			if (MAP[ii][jj] != -1) continue;
			while (jj != M-1){
				++minlength;
				if (MAP[ii+dx[2]][jj+dy[2]] == -1){
					MAP[ii][jj] = 2;
					ii += dx[2]; jj += dy[2];
				} else
				{
					MAP[ii][jj] = ((col-j/(K+1))&1);
					ii += dx[((col-j/(K+1))&1)]; jj += dy[((col-j/(K+1))&1)];
				}
			}
			++maxpoints;
		}
	}
	for (int t = 1; t <= K+1 && t <= row && t <= col; ++t){
		// down
		for (int i=(K+1)*t, j=(K+1)*t; j<=(K+1)*(col-t+1); j+=(K+1)){
			if ((col&1) && j/(K+1) == col/2+1) continue;
			int ii = i, jj  = j;
			while (ii != 0){
				++minlength;
				if (MAP[ii+dx[1]][jj+dy[1]] == -1){
					MAP[ii][jj] = 1;
					ii += dx[1]; jj += dy[1];
				} else
				{
					MAP[ii][jj] = 2+(j/(K+1)*2<=col);
					ii += dx[2+(j/(K+1)*2<=col)]; jj += dy[2+(j/(K+1)*2<=col)];
				}
			}
			++maxpoints;
		}
		// up
		for (int i=(K+1)*(row-t+1), j=(K+1)*t; j<=(K+1)*(col-t+1); j+=(K+1)){
			if ((col&1) && j/(K+1) == col/2+1) continue;
			int ii = i, jj  = j;
			while (ii != N-1){
				++minlength;
				if (MAP[ii+dx[0]][jj+dy[0]] == -1){
					MAP[ii][jj] = 0;
					ii += dx[0]; jj += dy[0];
				} else
				{
					MAP[ii][jj] = 2+(j/(K+1)*2<=col);
					ii += dx[2+(j/(K+1)*2<=col)]; jj += dy[2+(j/(K+1)*2<=col)];
				}
			}
			++maxpoints;
		}
		// left
		for (int i=(K+1)*(t+1), j=(K+1)*t; i<(K+1)*(row-t+1); i+=(K+1)){
			if ((row&1) && i/(K+1) == row/2+1) continue;
			int ii = i, jj = j;
			while (jj != 0){
				++minlength;
				if (MAP[ii+dx[3]][jj+dy[3]] == -1){
					MAP[ii][jj] = 3;
					ii += dx[3]; jj += dy[3];
				} else
				{
					MAP[ii][jj] = (i/(K+1)*2<=row);
					ii += dx[(i/(K+1)*2<=row)]; jj += dy[(i/(K+1)*2<=row)];
				}
			}
			++maxpoints;
		}
		//right
		for (int i=(K+1)*(t+1), j=(K+1)*(col-t+1); i<(K+1)*(row-t+1); i+=(K+1)){
			if ((row&1) && i/(K+1) == row/2+1) continue;
			int ii = i, jj = j;
			while (jj != M-1){
				++minlength;
				if (MAP[ii+dx[2]][jj+dy[2]] == -1){
					MAP[ii][jj] = 2;
					ii += dx[2]; jj += dy[2];
				} else
				{
					MAP[ii][jj] = (i/(K+1)*2<=row);
					ii += dx[(i/(K+1)*2<=row)]; jj += dy[(i/(K+1)*2<=row)];
				}
			}
			++maxpoints;
		}
	}
	
	for (int t = K+2; t <= row && t <= col; ++t){
		//down
		for (int i = (K+1)*t, _j = 0; ((col+1)/2)-_j > t || ((col+1)/2)+_j < (col-t+1); ++_j){
			int j = (K+1)*((col+1)/2-_j);
			if (j/(K+1) > t && j/(K+1) < col-t+1 && MAP[i][j] == -1)
				BFS(i, j, 0, 0);
			j = (K+1)*((col+1)/2+_j);
			if (j/(K+1) > t && j/(K+1) < col-t+1 && MAP[i][j] == -1)
				BFS(i, j, 0, 0);
		}
		//up
		for (int i = (K+1)*(row-t+1), _j = 0; ((col+1)/2)-_j > t || ((col+1)/2)+_j < (col-t+1); ++_j){
			int j = (K+1)*((col+1)/2-_j);
			if (j/(K+1) > t && j/(K+1) < col-t+1 && MAP[i][j] == -1)
				BFS(i, j, 1, 1);
			j = (K+1)*((col+1)/2+_j);
			if (j/(K+1) > t && j/(K+1) < col-t+1 && MAP[i][j] == -1)
				BFS(i, j, 1, 1);
		}
		//left
		for (int _i = 0, j = (K+1)*t; ((row+1)/2)-_i > t || ((row+1)/2)+_i < (row-t+1); ++_i){
			int i = (K+1)*((row+1)/2-_i);
			if (i/(K+1) > t && i/(K+1) < row-t+1 && MAP[i][j] == -1)
				BFS(i, j, 2, 2);
			i = (K+1)*((row+1)/2+_i);
			if (i/(K+1) > t && i/(K+1) < row-t+1 && MAP[i][j] == -1)
				BFS(i, j, 2, 2);
		}
		//right
		for (int _i = 0, j = (K+1)*(col-t+1); ((row+1)/2)-_i > t || ((row+1)/2)+_i < (row-t+1); ++_i){
			int i = (K+1)*((row+1)/2-_i);
			if (i/(K+1) > t && i/(K+1) < row-t+1 && MAP[i][j] == -1)
				BFS(i, j, 3, 3);
			i = (K+1)*((row+1)/2+_i);
			if (i/(K+1) > t && i/(K+1) < row-t+1 && MAP[i][j] == -1)
				BFS(i, j, 3, 3);
		}
		
		int i = (K+1)*t, j = (K+1)*t;
		BFS(i, j, -1, -1);
		j = (K+1)*(col-t+1);
		BFS(i, j, -1, -1);
		
		i = (K+1)*(row-t+1), j = (K+1)*t;
		BFS(i, j, -1, -1);
		j = (K+1)*(col-t+1);
		BFS(i, j, -1, -1);
	}
	
	for (int i = 1; i <= row; ++i)
		for (int j = 1; j <= col; ++j)
			if (MAP[i*(K+1)][j*(K+1)] == -1)
				BFS(i, j, -1, -1);
	/*
	for (int t = K+2; t <= row && t <= col; ++t){
		int i = (K+1)*t, j = (K+1)*t;
		BFS(i, j, -1, -1);
		j = (K+1)*(col-t+1);
		BFS(i, j, -1, -1);
		
		i = (K+1)*(row-t+1), j = (K+1)*t;
		BFS(i, j, -1, -1);
		j = (K+1)*(col-t+1);
		BFS(i, j, -1, -1);
	}
	*/
	/*for (int t = 1; t <= row && t <= col; ++t){
		//down
		for (int i = (K+1)*t, _j = 0; ((col+1)/2)-_j > t || ((col+1)/2)+_j < (col-t+1); ++_j){
			int j = (K+1)*((col+1)/2-_j);
			if (j/(K+1) > t && j/(K+1) < col-t+1 && MAP[i][j] == -1)
				BFS(i, j, 0, 0);
			j = (K+1)*((col+1)/2+_j);
			if (j/(K+1) > t && j/(K+1) < col-t+1 && MAP[i][j] == -1)
				BFS(i, j, 0, 0);
		}
		//up
		for (int i = (K+1)*(row-t+1), _j = 0; ((col+1)/2)-_j > t || ((col+1)/2)+_j < (col-t+1); ++_j){
			int j = (K+1)*((col+1)/2-_j);
			if (j/(K+1) > t && j/(K+1) < col-t+1 && MAP[i][j] == -1)
				BFS(i, j, 1, 1);
			j = (K+1)*((col+1)/2+_j);
			if (j/(K+1) > t && j/(K+1) < col-t+1 && MAP[i][j] == -1)
				BFS(i, j, 1, 1);
		}
		//left
		for (int _i = 0, j = (K+1)*t; ((row+1)/2)-_i > t || ((row+1)/2)+_i < (row-t+1); ++_i){
			int i = (K+1)*((row+1)/2-_i);
			if (i/(K+1) > t && i/(K+1) < row-t+1 && MAP[i][j] == -1)
				BFS(i, j, 2, 2);
			i = (K+1)*((row+1)/2+_i);
			if (i/(K+1) > t && i/(K+1) < row-t+1 && MAP[i][j] == -1)
				BFS(i, j, 2, 2);
		}
		//right
		for (int _i = 0, j = (K+1)*(col-t+1); ((row+1)/2)-_i > t || ((row+1)/2)+_i < (row-t+1); ++_i){
			int i = (K+1)*((row+1)/2-_i);
			if (i/(K+1) > t && i/(K+1) < row-t+1 && MAP[i][j] == -1)
				BFS(i, j, 3, 3);
			i = (K+1)*((row+1)/2+_i);
			if (i/(K+1) > t && i/(K+1) < row-t+1 && MAP[i][j] == -1)
				BFS(i, j, 3, 3);
		}
		int i = (K+1)*t, j = (K+1)*t;
		BFS(i, j, -1, -1);
		j = (K+1)*(col-t+1);
		BFS(i, j, -1, -1);
		
		i = (K+1)*(row-t+1), j = (K+1)*t;
		BFS(i, j, -1, -1);
		j = (K+1)*(col-t+1);
		BFS(i, j, -1, -1);
	}*/
	/*for (int t = 1; t <= row && t <= col; ++t){
		int i = (K+1)*t, j = (K+1)*t;
		BFS(i, j, -1, -1);
		j = (K+1)*(col-t+1);
		BFS(i, j, -1, -1);
		
		i = (K+1)*(row-t+1), j = (K+1)*t;
		BFS(i, j, -1, -1);
		j = (K+1)*(col-t+1);
		BFS(i, j, -1, -1);
	}*/
}

void Greedy::BFS(int sx, int sy, int ban, int kd){
	int _d[4];
	if (ban == -1){
		_d[0] = 0;
		_d[1] = 1;
		_d[2] = 2;
		_d[3] = 3;
	} else
	{
		_d[0] = ban^1;
		_d[1] = 4-(ban|1);
		_d[2] = (4-(ban|1))^1;
		_d[3] = ban;
	}
	Q[0] = sx*M+sy;
	D[sx*M+sy] = 0;
	int top, tail;
	for (top=0, tail=0; top <= tail && MAP[sx][sy]==-1; top++){
		int x = Q[top]/M, y = Q[top]%M;
		for (int d = 0; d < 4; ++d)
		if (_d[d] != ban)
		{
			if (((kd==-1 || kd==0) && x+dx[_d[d]] == 0) ||
				((kd==-1 || kd==1) && x+dx[_d[d]] == N-1) || 
				((kd==-1 || kd==2) && y+dy[_d[d]] == 0) || 
				((kd==-1 || kd==3) && y+dy[_d[d]] == M-1)){
				minlength+=D[x*M+y]+1;
				++maxpoints;
				MAP[x][y] = _d[d];
				while (x!=sx || y!=sy){
					for (int dd = 3; dd >= 0; --dd)
					if (	_d[dd] != ban && D[(x-dx[_d[dd]])*M+y-dy[_d[dd]]]+1 == D[x*M+y]){
						x = x-dx[_d[dd]];
						y = y-dy[_d[dd]];
						MAP[x][y] = _d[dd];
						break;
					}
				}
				break;
			}
			if (x+dx[_d[d]] == 0 || x+dx[_d[d]] == N-1 || y+dy[_d[d]] == 0 || y+dy[_d[d]] == M-1) continue;
			
			if ((x+dx[_d[d]])%(K+1)==0 && (y+dy[_d[d]])%(K+1)==0) continue;
			if (MAP[x+dx[_d[d]]][y+dy[_d[d]]] == -1 && D[(x+dx[_d[d]])*M+y+dy[_d[d]]] > D[x*M+y]+1){
				Q[++tail] = (x+dx[_d[d]])*M+y+dy[_d[d]];
				D[Q[tail]] = D[x*M+y]+1;
			}
		}
	}
	for (int i = 0; i <= tail; ++i)
		D[Q[i]] = D[0];
}