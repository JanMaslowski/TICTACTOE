#include <iostream>
#include <iomanip>
#include <utility> 
#include <vector> 
#include <algorithm>
#include <limits>
#include <bits/stdc++.h>

using namespace std;


//Klasa Gra w której znajdują się wszytskie zmienne i funkcje
//niezbędne do działania programu
class Gra 
{
    // X czlowiek
    // O komputer
    public:

    int size; //rozmiar tablicy size x size
    int glebokosc; //Glebia dzialania minimax`a

/////////////////////////// FUNCKCJA //////////////////////////////
    //konstruktor gry 
    // uzupełnia tablice pustymi miejscami czyli - 
    // pobiera odpowiednie wartosci size i glebokosc

    Gra (char **board,int siz,int gleb) 
    {
        size=siz;
        glebokosc=gleb;
        for (int i = 0; i < size; i++)
        {
            for (int j = 0; j < size; j++)
            {
                board[i][j] = '-';
            }
        }

    }
/////////////////////////// FUNCKCJA //////////////////////////////
    // funkcja wyswiela bieżącą tablice 

    void Wyswietl_plansze(char **board)
    {

        int k=0;
        for (int i = 0; i < size; i++)
        {
            cout << "\n Kolumna:"<<k<<"|";
            for (int j = 0; j < size; j++)
            {
                cout << setw(2) << board[i][j] << setw(2) << " |";
            }
            k++;
        }
        cout<<endl;
    }
    
/////////////////////////// FUNCKCJA //////////////////////////////
    // funkcja sprawdza czy sa puste miejsca
    // jesli sa zwraca falsz
    // jesli nie ma prawde 
    //moze powinna byc Nieobecnosc pustych

    bool Obecnosc_pustych(char **board)
    {
        for (int i = 0; i < size; i++)
        {
            for (int j = 0; j < size; j++)
            {
                if(board[i][j] == '-')
                return false;
            }
        }
        return true;
    }

/////////////////////////// FUNCKCJA //////////////////////////////
    // Funkcja w prosty sposob sprawdza czy ktos wygrał
    // pobiera gracza dla jakiego ma sprawdzic zwyciestwo    
    int Wygrana(char gracz,char **board)
    {
        if (size==3)
        {
        for (int i = 0; i < 3; i++)
        {
            if (board[i][0] == gracz && board[i][1] == gracz && board[i][2] == gracz)
            return true;

            if (board[0][i] == gracz && board[1][i] == gracz && board[2][i] == gracz)
            return true;
        }
        

        if (board[0][0] == gracz && board[1][1] == gracz && board[2][2] == gracz)
        return true;

        if (board[0][2] == gracz && board[1][1] == gracz && board[2][0] == gracz)
        return true;
       }
        
        if (size==4)
        {
        for (unsigned int i = 0; i < 4; i++)
        {
            
            if (board[i][0] == gracz && board[i][1] == gracz && board[i][2] == gracz && board[i][3] == gracz)
            return true;

            
            if (board[0][i] == gracz && board[1][i] == gracz && board[2][i] == gracz&& board[3][i] == gracz)
            return true;

        }
        
        if (board[0][0] == gracz && board[1][1] == gracz && board[2][2] == gracz&& board[3][3] == gracz)
            return true;

        if (board[0][3] == gracz && board[1][2] == gracz && board[2][1] == gracz && board[3][0] == gracz)
            return true;
        }
    return false;
    }




/////////////////////////// FUNCKCJA //////////////////////////////
// funkcja zwraca wartosc w przypadku wygranej 
// jesli wygral komputer 1000
//jesli człowiek to -1000
// remis to 0 punktów 

    int result (char gracz,char **board)
    {
        if(Wygrana('O',board))
        {
            return 1000;
        }
        if(Wygrana('X',board))
        {
            return -1000;
        }
        else {
            return 0;
        }

    }

/////////////////////////// FUNCKCJA //////////////////////////////
//funkcja sprawdza ilosc wolnych miejsc oraz zwraca wektor tych miejsc 
// w postaci ich wspołrzednych

    vector<pair<int, int>> Pobierz_mozliwe_ruchy (char **board){ 
        vector<pair<int, int>> legal_moves;

        for (int i = 0; i < size; i++)
        { 
            for (int j=0; j < size; j++)
        { 
            if (board[i][j] != 'O' && board[i][j] != 'X'){
            legal_moves.push_back(make_pair(i, j));
            }

        }
        }
        return legal_moves;
    }


/////////////////////////// FUNCKCJA //////////////////////////////
//Fukcja alfabeta to funkcja minimax z alfabeta cieciami

        pair<int,pair<int,int>> AlfaBeta(char **board, int alfa, int beta, char player, int glebia)
    {
        pair<int,int> best_move = make_pair(-1,-1);
        int best_score =(player=='O')? -1000:1000;
        vector<pair<int,int>> legal_moves = Pobierz_mozliwe_ruchy(board);

        if(Obecnosc_pustych(board) ||0 != result('O',board))
        {
            best_score=result('O',board);
            return make_pair(best_score, best_move);
        }
    
        for (int i=0; i<legal_moves.size(); i++){
            pair<int,int> curr_move = legal_moves[i];
            board[curr_move.first][curr_move.second]=player;

            if(player=='O')
            {
            int score=AlfaBeta(board,alfa,beta,'X',glebia-1).first;

                if(best_score<score){
                    best_score=score-glebia*10;
                    best_move=curr_move;

                    alfa=max(alfa,best_score);
                    board[curr_move.first][curr_move.second]= '-';
                    if(beta<=alfa)
                    {
                        break;
                    }    
                }

            }
            else{
                int score= AlfaBeta(board,alfa,beta,'O',glebia-1).first;

                if(best_score>score){
                    best_score=score+glebia*10;
                    best_move=curr_move;

                    beta=min(beta,best_score);
                    board[curr_move.first][curr_move.second]= '-';
                    if(beta<=alfa)
                    {
                        break;
                    }    
                }
            }
            board[curr_move.first][curr_move.second]= '-';
        }
    return make_pair(best_score,best_move);
    }

/////////////////////////// FUNCKCJA //////////////////////////////
// funkcja pobiera ruch czlowieka i wpisuje do planszy X

void Pobierz_ruch(char **board)
    {
        bool fail = true;
        int x = -1, y = -1;

        do
        {
            cout << "Twój ruch: ";

            char c;
            cin >> c;
            x = c - '0';
            cin >> c;
            y = c - '0';

            fail = board[x][y] != '-';

            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

        } while (fail);

        board[x][y] = 'X';
    }

/////////////////////////// FUNCKCJA //////////////////////////////
//funkcja odpowiada za przebieg gry

    void play(char **board)
    {
        int turn = 0;
        bool exit = false;

        Wyswietl_plansze(board);
        cout <<endl<< "Proszę wpisać ruch wybierając najpierw kolumnę a potem rząd np. 32\n";

        do
        {

            if (turn%2 == 0)
            {
                Pobierz_ruch(board);

                if (Wygrana('X',board))
                {
                    cout << "Człowiek wygrywa (COS SIE ZEPSUŁO)\n";
                    exit = true;
                }
            }
            else 
            {
                cout << "\nTrwa ruch komputera: "<<endl;

                pair<int,pair<int,int>> jakos = AlfaBeta(board,-1000,1000,'O',glebokosc);
                board[jakos.second.first][jakos.second.second]='O';


                if (Wygrana('O',board))
                {
                    cout << "Przegrałeś \n";
                    exit = true;
                }
            }

            if (Obecnosc_pustych(board))
            {
                cout << "\nRemis\n";
                exit = true;
            }

            turn++;
            Wyswietl_plansze(board);

        } while (!exit);
    }
};



///////////////////////////////////////////////////////////////////////
//*******************************************************************//
/////////////////////////// FUNCKCJA MAIN//////////////////////////////
//*******************************************************************//
///////////////////////////////////////////////////////////////////////

int main()
{

    cout<<"\tPodaj wielkość planszy"<<endl;
    cout<<"\tDo wybory wielkości:"<<endl;
    cout<<"\t3x3 (Wciśnij 1) lub 4x4 (Wcisnij 2)"<<endl;
    int w=1;
    int sizem=3;
    int depth=9;
    cin>>w;
    if (w==1){
    sizem=3;
    depth=9;}
    if (w==2){
    sizem=4;
    depth=3;}

    char** board = new char*[sizem];
    for (int p = 0; p < sizem; p++){
    board[p] = new char[sizem];}

    Gra tictactoe(board,sizem,depth);
    cout<<"Głębia minimax`a : "<<tictactoe.glebokosc<<endl;

    tictactoe.play(board);
    cin.ignore();
    delete [] board;
    return 0;
}


