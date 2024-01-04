#include<bits/stdc++.h>
using namespace std;


class Task;
class User;
// this is the enum for TaskType
enum TaskType {STORY,FEATURE,BUG};
// this is the enum for taskStatus
enum TaskStatus {OPEN,IN_PROGRESS,RESOLVED,DELAYED,COMPLETED};

// Sprint class start from here
class Sprint{
    int begin,end;
    string name;
    vector<Task>tasks;
    public:
    Sprint(int begin,int end,string name);// constructor form the sprint
    void addTask(Task&);// adding new task
    void printDetails();// print the detail of the task
    bool operator==(Sprint sprint);
    vector<Task>getTasks();// return of task.
    void eraseTask(int taskNumber);
};



// User class start from here
class User{
    vector<Task>taskList;
    vector<Sprint>sprintList;
    public:
        Task createTask(TaskType);
        Task createTask(string);
        Sprint createSprint(int,int,string);
        bool addToSprint(Sprint,Task);
        bool removeFromSprint(Sprint,Task);
        void printAllTasks();
        bool changeStatus(Task,TaskStatus);

};



// Task class start from here
class Task{
    int id;// autogeneated
    string subtract;// should be by default
    User user;// task assign to the user *at time creation where are not sure who is user.
    TaskType taskType;// tasktype such as Feature,bug;
    TaskStatus taskStatus;// taskStatus such as completed/delay/in_progress etc.
     int getUniqueId();// no external party can generate id.
    public:
    Task();
    int getId();
    void setUser(User);
    void setSubtract(string);
    void setTaskStatus(TaskStatus);
    void setTaskType(TaskType);
   
};

Sprint::Sprint(int begin,int end,string name)
{
    this->begin=begin;
    this->end=end;
    this->name=name;

}


void Sprint::addTask(Task& task)
{
    tasks.push_back(task);
}


void Sprint::printDetails()
{
    cout<<"sprint name "<<this->name<<endl<<" Sprint Begins: "<<this->begin<<endl<<" Sprints Ends:"<<this->end<<endl;
}


// this is getter for tasks in a sprint.
vector<Task>Sprint::getTasks()
{
    return tasks;
}


bool Sprint::operator==(Sprint sprint){
    return (this->begin == sprint.begin) && (this->end == sprint.end) && (this->name == sprint.name);

}
void Sprint::eraseTask(int taskNumber)
{
    tasks.erase(tasks.begin()+taskNumber);
}
Task::Task()
{
    this->id=getUniqueId();
    this->taskStatus=TaskStatus::OPEN;
}


int Task::getId(){
    return id;
}
void Task::setSubtract(string subtract){
    this->subtract=subtract;
}


void Task::setTaskStatus(TaskStatus taskStatus){
    this->taskStatus=taskStatus;
}


void Task::setTaskType(TaskType taskType)
{
    this->taskType=taskType;
}


void Task::setUser(User user)
{
    this->user=user;
}


int Task::getUniqueId(){
    static int taskId=1;
    return taskId++;
}


Task User::createTask(TaskType taskType)
{
    if(taskType==TaskType::STORY)
    {
        cout<<"Warning! Task of type STORY is being created with no subtract."<<endl;
    }
    Task task;
    task.setTaskType(taskType);
    task.setUser(*this);
    taskList.push_back(task);
    return task;
}


Task User::createTask(string subtract)
{
    
    Task task;
    task.setTaskType(TaskType::STORY);
    task.setSubtract(subtract);
    task.setUser(*this);
    taskList.push_back(task);
    return task;
}
Sprint User::createSprint(int begin,int end,string name)
{
    Sprint sprint(begin,end,name);
    sprintList.push_back(sprint);

    return sprint;
}


bool User::addToSprint(Sprint sprint,Task task)
{
        for(Sprint spr:sprintList)
        {
            if(spr==sprint)
            {
                sprint.addTask(task);
                return true;
            }
        }
        return false;
}
bool User::removeFromSprint(Sprint sprint,Task task)
{
    vector<Task>taskList;
    for(Sprint spr:sprintList)
    {
        if(spr==sprint)
        {
            taskList=sprint.getTasks();
            break;
        }
    }
    int i=0;
    for(Task t:taskList)
    {
        if(t.getId()==task.getId())
        {
            sprint.eraseTask(i);
            return true;
        }
        i++;
    }
    return false;
}
void User::printAllTasks()
{
    for(Task task:taskList){
        cout<<task.getId()<<" ";
    }
    cout<<endl;
}
bool User::changeStatus(Task task,TaskStatus status)
{
    for(Task& t:taskList)
    {
        if(t.getId()==task.getId())
        {
            t.setTaskStatus(status);
            return true;
        }
    }
    return false;
}
int main()
{
       User user1, user2;
	Task task1 = user1.createTask(TaskType::FEATURE);
	Task task11 = user1.createTask(TaskType::BUG);
	Task task2 = user2.createTask(TaskType::BUG);
	Task task22 = user2.createTask("This is a subtract");

	Sprint sprint1 = user1.createSprint(22,33,"Sprint1");
	Sprint sprint2 = user2.createSprint(44,55,"Sprint2");

	cout << user1.changeStatus(task11, TaskStatus::IN_PROGRESS) <<endl ;//1

	cout << user1.addToSprint(sprint1, task1) << "\n"; //1
	cout << user1.addToSprint(sprint1, task11) << "\n"; //1
	cout << user1.addToSprint(sprint2, task1) << "\n"; //0
	cout << user1.removeFromSprint(sprint1, task11) << "\n"; //1
	cout << user2.addToSprint(sprint1, task1) << "\n"; //0
	cout << user2.removeFromSprint(sprint1, task2) << "\n"; //0
	cout << user2.addToSprint(sprint2, task1) << "\n"; //1
	cout << user2.addToSprint(sprint2, task2) << "\n"; //1

	sprint1.printDetails();
	cout << endl;
	user1.printAllTasks();
	user2.printAllTasks();

    // cout<<"Hello world "<<endl;
    return 0;
}