#include<bits/stdc++.h>
using namespace std;
class Meeting;
typedef vector<Meeting>Calendar;
// room class start from here
class Room{
    string name;
    Calendar calendar;
    public:
    Room(string);
    bool book(int,int);
    string getName();
};


// Meeting class start from here
class Meeting{
    int start,end;
    Room room;
    public:
    Meeting(int,int,Room);
    int getEnd();
    int getStart();
};
// Scheduler class start from here
class Scheduler{
    vector<Room>rooms;
    public:
    Scheduler(vector<Room>rooms);
    string book(int,int);
};
// Scheduler class end
string Room::getName(){
    return name;
}
Room::Room(string name)
{
    this->name=name;
}
bool Room::book(int start,int end)
{
    for(Meeting m:calendar)
    {
        if(m.getStart()<end && start<m.getEnd())
        return false; 
    }
    Meeting meeting(start,end,*this);
    calendar.push_back(meeting);
    return true;
}
Meeting::Meeting(int start,int end,Room room):room(room)
{
   
    this->start=start;
    this->end=end;
}
int Meeting::getEnd(){
    return end;
}
int Meeting::getStart(){
    return start;
}
Scheduler::Scheduler(vector<Room>rooms)
{
    this->rooms=rooms;
}
string Scheduler::book(int start,int end)
{
    for(Room &room:rooms)
    {
        bool flag=room.book(start,end);
        if(flag==true)
        return room.getName();
    }
    return "No rooms available";
}
int main()
{
   Room room1("Atlas");
   Room room2("Nexus");
   Room room3("HolyCow");
   vector<Room>roomVec;
   roomVec.push_back(room1);
   roomVec.push_back(room2);
   roomVec.push_back(room3);

   Scheduler scheduler(roomVec);
   cout<<scheduler.book(2,5)<<endl;
   cout<<scheduler.book(5,8)<<endl;
   cout<<scheduler.book(4,8)<<endl;
   cout<<scheduler.book(3,6)<<endl;
   cout<<scheduler.book(7,8)<<endl;
    return 0;
}

