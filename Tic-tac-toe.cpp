/*This code is for the tic-tac-toe game which is designed in such a way that the first player has winning strategy irrespective of other player's moves .
Minimax Optimization is used for such an strategy.

-BY,    Deep Mavani        - 18ucs033
        Rahul Vaishnav     - 18ucs063
        Siddharth Singhvi  - 18ucs069
        Pinkesh Unadkat    - 18ucs091

*/

#include <bits/stdc++.h>

using namespace std;

#define COMP_MOVE 'X'      // Computer's Move is displayed as 'X'
#define PLAYER_MOVE 'O'    // User's Move is displayed as 'O'
#define EMPTY_CELL ' '   

vector<vector<pair<int, int> > > winning_pairs{ // Indicates all winning states
	// Every row
	{ make_pair(0, 0), make_pair(0, 1), make_pair(0, 2) },
	{ make_pair(1, 0), make_pair(1, 1), make_pair(1, 2) },
	{ make_pair(2, 0), make_pair(2, 1), make_pair(2, 2) },

	// Every column
	{ make_pair(0, 0), make_pair(1, 0), make_pair(2, 0) },
	{ make_pair(0, 1), make_pair(1, 1), make_pair(2, 1) },
	{ make_pair(0, 2), make_pair(1, 2), make_pair(2, 2) },

	// Every diagonal
	{ make_pair(0, 0), make_pair(1, 1), make_pair(2, 2) },
	{ make_pair(2, 0), make_pair(1, 1), make_pair(0, 2) }

};

/*Below is the function printboard which prints the current scenario of the playboard in the game*/
void printboard(char playboard[3][3])
{
	cout << endl;
	cout <<" "<< playboard[0][0] << " | " << playboard[0][1] << " | " <<playboard[0][2] << endl;
	cout << "-----------" << endl;
	cout <<" "<< playboard[1][0] << " | " << playboard[1][1] << " | " <<playboard[1][2] << endl;
	cout << "-----------" << endl;
	cout <<" "<< playboard[2][0] << " | " << playboard[2][1] << " | " <<playboard[2][2] << endl << endl;
}

/*Below is the function pos_filled which checks whether the given position(input pair) is filled or not and 
returns true if position is filled/occupied and false otherwise*/
bool pos_filled(char playboard[3][3], pair<int, int> pos)
{
	vector<pair<int, int> > fair_moves;
	for (int i = 0; i < 3; i++){					// This for loops checks for all the empty cells in the play board.
		for (int j = 0; j < 3; j++){
			if (playboard[i][j] != COMP_MOVE && playboard[i][j] != PLAYER_MOVE)
			{
				fair_moves.push_back(make_pair(i, j));
			}
		}
	}

	for (int i = 0; i < fair_moves.size(); i++){				// If any empty cell is equal to the given position , it returns false and true otherwise
		if (pos.first == fair_moves[i].first && pos.second == fair_moves[i].second){
			return false;
		}
	}

	return true;
}

/*Below is the function get_filled_position which returns all the position with the marks as specified in the parameter and returns as a vector of pairs.*/
vector<pair<int, int> > get_filled_positions(char playboard[3][3], char mark)
{
	vector<pair<int, int> > filled_positions;

	for (int i = 0; i < 3; i++){
		for (int j = 0; j < 3; j++){
			if (mark ==playboard[i][j]){
				filled_positions.push_back(make_pair(i, j));
			}
		}
	}
	return filled_positions;
}

/*Below is the function game_result which checks if any winning state/condition is reached in the game by any player and
 returns true if any player has won till the previous move played.*/
bool game_result(vector<pair<int, int> > filled_positions)
{
	bool is_game_won;

	for (int i = 0; i < winning_pairs.size(); i++){
		is_game_won = true;
		vector< pair<int, int> > curr_win_state = winning_pairs[i];
		for (int j = 0; j < 3; j++){
			if (!(find(begin(filled_positions), end(filled_positions), curr_win_state[j]) != end(filled_positions))){
				is_game_won = false;
				break;
			}
		}

		if (is_game_won)
			break;

	}
	return is_game_won;
}

/*Below is the function gamestatus which returns a number according to the state(WIN , LOSE, DRAW) of the player with the given mark. 
It returns 0 when the game is draw, 1000 for WIN with the given mark and -1000 for LOSE with the given mark.*/
int gamestatus(char playboard[3][3], char mark){
	char opp_mark;
	if (mark == PLAYER_MOVE){
		opp_mark = COMP_MOVE;
	}
	else{
		opp_mark = PLAYER_MOVE;
	}

	vector<pair<int, int> > filled_positions = get_filled_positions(playboard, mark);

	bool is_game_won = game_result(filled_positions);

	if (is_game_won)
		return 1000;

	filled_positions = get_filled_positions(playboard, opp_mark);
	bool is_game_lost = game_result(filled_positions);

	if (is_game_lost)
		return -1000;

	bool is_full=true;
	for(int i=0;i<3;i++){
		for(int j=0;j<3;j++){
			if(playboard[i][j]==EMPTY_CELL)
				is_full=false;
		}
	}

	if (is_full)
		return 0;

	return 0;

}

/*Below is the function Minimax which is a function responsible for winning strategy of first player to move , irrespective of the other players's moves.
This is quite a complex function which also uses other functions of the code and also gathers data and forms the winning strategy of the first player at every move.*/
pair<int, pair<int, int> > minimax(char playboard[3][3], char mark, int depth, int alpha, int beta)
{
	// Initialize best move
	pair<int, int> best_move = make_pair(-1, -1);
	int best_score = (mark == COMP_MOVE) ? -1000 : 1000;

	// If we hit a terminal state (leaf node), return the best score and move
	vector<pair<int, int> > fair_moves ;
	bool is_full=true;
	for(int i=0;i<3;i++){
		for(int j=0;j<3;j++){
			if(playboard[i][j]==EMPTY_CELL){
				is_full=false;
				fair_moves.push_back(make_pair(i,j));
			}
		}
	}

	if (is_full || gamestatus(playboard, COMP_MOVE)!=0 ){
		best_score = gamestatus(playboard, COMP_MOVE);
		return make_pair(best_score, best_move);
	}

	for (int i = 0; i < fair_moves.size(); i++)
	{
		pair<int, int> curr_move = fair_moves[i];
		playboard[curr_move.first][curr_move.second] = mark;

		// Maximizing player's turn
		if (mark == COMP_MOVE){
			int score = minimax(playboard, PLAYER_MOVE, depth + 1, alpha, beta).first;

			// Get the best scoring move
			if (best_score < score){
				best_score = score - depth * 10;
				best_move = curr_move;

				// Check if this branch's best move is worse than the best
				// option of a previously search branch. If it is, skip it
				alpha = max(alpha, best_score);
				playboard[curr_move.first][curr_move.second] = EMPTY_CELL;
				if (beta <= alpha){ 
					break; 
				}
			}

		} // Minimizing opponent's turn
		else{
			int score = minimax(playboard, COMP_MOVE, depth + 1, alpha, beta).first;

			if (best_score > score){
				best_score = score + depth * 10;
				best_move = curr_move;

				// Check if this branch's best move is worse than the best
				// option of a previously search branch. If it is, skip it
				beta = min(beta, best_score);
				playboard[curr_move.first][curr_move.second] = EMPTY_CELL;
				if (beta <= alpha){ 
					break; 
				}
			}

		}

		playboard[curr_move.first][curr_move.second] = EMPTY_CELL; // Undo move

	}

	return make_pair(best_score, best_move);
}

/*Below is the function gameover which checks the completion of the game, and returns true when either a game is DRAW or a WIN by any one of the two players.*/
bool gameover(char playboard[3][3]){

	bool flag=true;
	for(int i=0;i<3;i++){
		for(int j=0;j<3;j++){
			if(playboard[i][j]==EMPTY_CELL)
				flag=false;
		}
	}

	if(flag)
		return true;
	if(gamestatus(playboard,COMP_MOVE) != 0)
		return true;

	return false;
}

/*This is the main function which assembles the use of all the above functions and its own code to do the process of tic-tac-toe game. 
It is a interactive function which takes input from the user when necessary and outputs the play board at every step and step-by-step reaches to the completion of the game*/
int main(){
	char playboard[3][3] ;

	//Initially playboard is initialised as all the empty cells.
	for(int i=0;i<3;i++){
		for(int j=0;j<3;j++){
			playboard[i][j]=EMPTY_CELL;
		}
	}

	cout<<"       -----------\n\tTic Tac Toe\n       -----------" << endl << endl;
	cout<< "USER = O\t COMPUTER = X " <<endl;
	int f=0;
	while (!gameover(playboard)){
		if(f==0)
	    {
	        playboard[rand()%3][rand()%3] = COMP_MOVE;
	        printboard(playboard);
	        f=1;
	    }
		int row, col;
		cout << "Enter Row and Col (use 0 indexing) : ";   // Each user move is to be entered
		cin >> row >> col;
		cout << endl << endl;

		if (pos_filled(playboard,make_pair(row, col))){      //If user enters an cell which is already occupied, it displays an error about Invalid Move 
			cout << "Invalid Move. Try again.." << endl;
			continue;
		}
		else{
			playboard[row][col] = PLAYER_MOVE;
		}

		pair<int, pair<int, int> > comp_move = minimax(playboard, COMP_MOVE, 0 , -1000, 1000);

		playboard[comp_move.second.first][comp_move.second.second] = COMP_MOVE;

		printboard(playboard);
	}

	cout << "---- GAME OVER ----" << endl << endl;

	int user_state = gamestatus(playboard, PLAYER_MOVE);

	// Here, depending on the status of the game played , the result is being displayed.
	if (user_state==1000){
		 cout << "HURRAY..! USER WON" << endl; }
	else if (user_state==0) {
		 cout << "It's A DRAW" << endl; }
	else if (user_state==-1000) { 
		cout << "OOOOPSSS..... USER LOSE" << endl; }

	return 0;
}		

