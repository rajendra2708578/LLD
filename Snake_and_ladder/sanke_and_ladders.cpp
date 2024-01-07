#include<bits/stdc++.h>
using namespace std;
// This is Player class
class Player{
    string name;
    int currentposition;
    int id;
    int getUniqueId();
    public:
    Player(string);
    string getName();
    int getPosition();
    int getId();
    void setPosition(int &);
};

Player::Player(string name)
{
    this->name=name;
    this->currentposition=0;
    this->id=getUniqueId();
}
int Player::getUniqueId()
{
    static int idval=0;
    return ++idval;
}
string Player::getName()
{
    return name;
}
int Player::getId(){
    return id;
}
int Player::getPosition(){
    return currentposition;
}
void Player::setPosition(int &currentposition)
{
    this->currentposition=currentposition;
}

//  This Game class 
class Game{
    unordered_map<int,int>board;
    vector<Player>players;
    bool iswinner;
    public:
    Game(vector<Player>);
    void addSnakes(int,int);
    void addladders(int,int);
    void rolldice(Player &);
    bool winner();
    
};
Game::Game(vector<Player>players)
{
    this->players=players;
    this->iswinner=false;
}


void Game::addladders(int start,int end)
{
    board[start]=end;
}


void Game::addSnakes(int start,int end)
{
    board[start]=end;
}


void Game::rolldice(Player &player)
{
    int destination=(rand()%6)+1;
    destination+=player.getPosition();
    if(destination>100)
    {
        cout<<"chance has elimnate becuase value is greater than 100"<<endl;
    }
    else
    {
        if(board.find(destination)!=board.end())
        {
            destination=board[destination];
        }
        cout<<player.getName()<<"move "<<player.getPosition()<<" to "<<destination<<endl;
        player.setPosition(destination);
    }

    if(destination==100)
    {
        bool iswinner=true;
    }
}
bool Game::winner()
{
    return iswinner;
}
int main()
{
    Player p1("Rajen");
    Player p2("Murmu");
    vector<Player>vec;
    vec.push_back(p1);
    vec.push_back(p2);
    Game g(vec);
    g.addladders(4,56);
    g.addladders(12,50);
    g.addladders(14,55);
    g.addladders(41,79);
    g.addladders(54,88);
    g.addSnakes(37,3);
    g.addSnakes(28,10);
    g.addSnakes(48,16);
    g.addSnakes(75,32);
    g.addSnakes(94,71);
    g.addSnakes(96,42);
    int pos=0;
  for(int i=0;i<=1000;i++)
   {
        pos=0;
        for(int i=0;i<vec.size();i++)
        {
           
            g.rolldice(vec[i]);
            if(g.winner())
            {
                cout<<"Winner is "<<vec[i].getName()<<endl;
                pos=1;
                break;
            }
        }
    }
    for(auto it:vec)
    {
        cout<<it.getName()<<" "<<it.getPosition()<<endl;
    }
    cout<<"Hello "<<endl;
    return 0;
}