#include "board.hh"
using namespace std;


Board::Board(int n, const set<string>& p) {
    board = vector<vector<char>>(n, vector<char>(n, '0'));
    
    for (auto it = p.begin(); it != p.end(); ++it) {
        string s = *it;

        while(true){
            int x = rand()%n;
            int y = rand()%n; 

            if (place_string(s, 0, x, y))
                break;
        }
        
    }

    //Acabar d'omplir amb lletres leatories
    for (int x = 0; x < n; ++x)
        for (int y = 0; y < n; ++y)
        {
            if (board[x][y] == '0') board[x][y] = randomLetter();
        }
    
}

char Board::randomLetter() {
    int rnd = rand()%26;
    return 'A' + rnd;
}


const void Board::print(){
	cout << endl;
	for (int i = 0; i < board.size(); ++i){
        for (int j = 0; j < board.size(); ++j)
            cout << board[i][j] << ' ';
        cout << endl;

	}
}
const char Board::getCasella(int x, int y){
    if (x < 0 || x >= board.size() || y < 0 || y >= board.size()) return '0';

    return board[x][y];
}

bool Board::place_string(string s, int i, int posx, int posy) {
    if (s.size() == i) return true;
    if (posx < 0 || posx >= board.size() || posy < 0 || posy >= board.size()) return false;
    if (board[posx][posy] != '0') return false;


    board[posx][posy] = s[i];

    vector<int> v = {0, 1, 2, 3, 4, 5, 6, 7};
    std::random_shuffle(v.begin(), v.end());
    
    for (int j = 0; j < 8; ++j) {
        switch (v[j])
        {
        case 0:
            if (place_string(s, i + 1, posx, posy + 1)) return true;
            break;
        
        case 1:
            if (place_string(s, i + 1, posx + 1, posy)) return true;
            break;
            
        case 2:
            if (place_string(s, i + 1, posx - 1, posy)) return true;
            break;

        case 3:
            if (place_string(s, i + 1, posx, posy - 1)) return true;
            break;

        case 4:
            if (place_string(s, i + 1, posx - 1, posy - 1)) return true;
            break;
        
        case 5:
            if (place_string(s, i + 1, posx + 1, posy + 1)) return true;
            break;

        case 6:
            if (place_string(s, i + 1, posx + 1, posy - 1)) return true;
            break;
        
        case 7:
            if (place_string(s, i + 1, posx - 1, posy + 1)) return true;
            break;
        }
    }
    //fi bucle
    board[posx][posy] = '0';
    return false;

    
}

const int Board::getSize() {
    return board.size();
}