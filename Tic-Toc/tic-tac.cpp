#include<bits/stdc++.h>
using namespace std;
class Player{
    string name;
    int Id;
    int getUnique();
    vector<pair<int,int>>playermoves;
    public:
    Player(string);
    int getId();
    string getName();
    vector<pair<int,int>>getMove();
    void setMove(int ,int);

};
Player::Player(string name)
{
    this->name=name;
    this->Id=getUnique();
}
 vector<pair<int,int>> Player::getMove()
{
    return playermoves;
}
void Player::setMove(int i,int j)
{
    playermoves.push_back({i,j});
}
string Player::getName()
{
    return name;
}
int Player::getUnique()
{
    static int Idval=0;
    return ++Idval;
}
int Player::getId()
{
    return Id;
}

//Game class
class Game{
    vector<vector<int>>board;
    int n;
    vector<Player>players;
    unordered_map<string,pair<int,int>>mp;
    public:
    Game(int,vector<Player>&);
    int getN();
    void moves(Player&,int);
    void display();
    bool checkwin(Player&);
};


Game::Game(int n,vector<Player>&players)
{
    this->n=n;
    this->players=players;
    board.resize(n,vector<int>(n,-1));
}
void Game::moves(Player &p,int move)
{
    int i=move/n;
    int j=move%n;
    // cout<<"move for "<<p.getName()<<" inside move function "<<endl;
    board[i][j]=p.getId();
    mp[p.getName()]={i,j};
    display();
}
void Game::display()
{
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n;j++)
        {
            cout<<board[i][j]<<" ";
        }
        cout<<endl;
    }
}
bool Game::checkwin(Player &player)
{
   int idvalue=player.getId();
   
   for(int i=0;i<n;i++)
   {
    int count=0,count1=0;
    for(int j=0;j<n;j++)
    {
        if(board[i][j]==idvalue)
        count++;
        
    }
    
    if(count==n)
    return true;
   }
   int count=0;
   for(int i=0;i<n;i++)
   {
    count=0;
    for(int j=0;j<n;j++)
    {
        if(board[j][i]==idvalue)
        count++;
    }
    if(count==n)
    return true;
   }
   return false;

   
}
int main()
{
    Player p1("Rajendra");
    Player p2("Murmu");
    vector<Player>vec;
    vec.push_back(p1);
    vec.push_back(p2);
    int n=3;
    Game g(n,vec);
    for(int i=0;i<9;i++)
    {
        int val;
        cin>>val;
        if(i%2==0)
        {
            
            g.moves(vec[0],val);
            if(g.checkwin(vec[0]))
            {
            cout<<"winner is Rajendra "<<endl;
            break;
            }
        }
        else
        {
           g.moves(vec[1],val);
           if(g.checkwin(vec[1]))
           {
            cout<<"winner is Murmu"<<endl;
            break;
           }
        }

        // if(g.checkwin(vec[i%2]))
        // {
        //     cout<<"winner is "<<vec[i%2].getName()<<endl;
        //     break;
        // }
    }
    g.display();
    cout<<"Hello "<<endl;
    return 0;
}