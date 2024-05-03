
#include <bits/stdc++.h>
using namespace std;

class board{
    public:
    virtual void boardSize(){};
    virtual void setSnakeLad(){};
    virtual void dice(){};
    virtual void getDiceVal(){};
    virtual void players(){};
    virtual ~board() {} // Virtual destructor
};

class Board : public board{
    protected:
    vector<vector<int>> myBoard;
    unordered_map<int,int> snakeLad;
    int dices,row,col,diceVal;

    public:
    Board(int row, int col){
        this->row = row;
        this->col = col;
    }
    void setSnakeLad(int start, int end){
        snakeLad[start]=end; 
    }
    void dice(){
        diceVal = rand() % 6 + 1;
    }
    void getDiceVal(){
       int max_value = dices*6;
       diceVal = rand()%max_value;
    }
};

class playerDetail : public Board{
    private: 
    queue<pair<int,int>> player;
    int newPos;

    public:
    playerDetail(int row, int col) : Board(row, col) {}
    void initializePlayers(int n){
        for(int i=0; i<n; i++)
            player.push({i+1, 0});
    }
    void play(){
        while(!player.empty()){
        pair<int,int> player_num = player.front();
        player.pop();
        dice(); // Roll the dice
        newPos = player_num.second + diceVal;
        cout << "Player " << player_num.first <<"at-"<<newPos<< endl;
        if(snakeLad.count(newPos)){
            newPos = snakeLad[newPos]; // Handle snake and ladder positions
            if(snakeLad[newPos] < newPos)
                cout<<"Bitten by snake"<<endl;
            else 
                cout<<"Got the ladder"<<endl;
        }
        if(newPos == row*col){
            cout << player_num.first << " wins";
            return;
        }
        if(newPos > row*col)
            newPos = player_num.second;
        player_num.second=newPos;
        player.push(player_num);
        }
    }
};

int main() { 
    playerDetail pd(5,5);
    pd.setSnakeLad(2,15);
    pd.setSnakeLad(10,20);
    pd.setSnakeLad(24,3);
    pd.setSnakeLad(11,16);
    
    pd.initializePlayers(2);
    pd.play();
    return 0;
}
