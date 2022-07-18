#include <iostream>
#include<fstream>
#include<vector>
#include<list>
using namespace std;
//MADE BY
// SHAHEER AHMAD: 20L-1003
// AUN ALI      : 20L-1300


//A HELPER CLASS FOR USER NODE CLASS !
//KEEPS USER ID AND ITS OPERATION TYPE.
class Info
{
    int id;
    char operation;

public:
    Info(int id = -99, char operation = '-') :id(id), operation(operation)
    {

    }

    template<class T>
    friend class UNode;
    template<class T>
    friend class PriorityQueue;
};


//KEEPS INFORMATION I.E USERID/OPERATION and KEY i.e PRIORITY.
template<class T>
class UNode
{

private:
    T key;
    Info information;

public:

    UNode()
    {

    }

    UNode(T key, Info information) :key(key), information(information)
    {

    }

    UNode(T key, int id, char op)
    {
        this->key = key;
        this->information.id = id;
        this->information.operation = op;
    }
    //OPERTOR USED IN UPCOMING CODE !
    void operator=(const UNode<T>& temp)
    {
        this->key = temp.key;
        this->information = temp.information;
    }


    //PRINTS USER INFORMATION
    void printUser()
    {
        cout << "Id: " << information.id << "  Operation: ";
        if (this->information.operation == 'R')
        {
            cout << "Read " << endl;
        }
        else if (this->information.operation == 'W')
        {
            cout << "Write " << endl;
        }
    }
    //PRINTS USER INFORMATION AND PRIORITY.
    void printwithPriority()
    {
        this->printUser();
        cout << "Priority: " << this->key << endl;
    }


    //OPERTOR USED IN UPCOMING CODE !
    bool operator>(const UNode<T>temp)
    {
        return (this->key > temp.key);
    }

    //OPERTOR USED IN UPCOMING CODE !
    bool operator==(const int I)
    {
        return(this->information.id == I);
    }

    //OPERTOR USED IN UPCOMING CODE !
    bool operator!=(const int i)
    {
        return(this->information.id != i);
    }

    template<class T>
    friend class PriorityQueue;

};



//PRIORITY QUEUE TO MAINTAIN USERS IN PRIOROTY! 
template<class T>
class PriorityQueue
{
private:
    vector<UNode<T>>que;    //A VECTOR OR TYPE UNODE(USERS NODES) BASED IN TEMPLATE T.
    int currentsize;       //TO KEEP THE SIZE OF QUEUE.
    T minimum;             //TO RETRIEVE MINIMUM PRIORITY IN O(1) TIME. DR. ZAREEN ASKED TO DO SO.
public:
    PriorityQueue() //CONSTRUCTOR.
    {
        this->currentsize = 0;
        this->que.resize(5);
        minimum = 0;
    }

    void BuildQueue(vector<UNode<T>>arr)//REQUIRED FUNCTION. FIRST COPIES THE GIVEN VECTOR.
    {                                   //MAINTAINS THE PROPERTIES OF HEEP FROM LEAF NOTES USING REHEAPDOWN.
        this->que = arr;
        this->currentsize = arr.size();

        int start = (que.size() / 2) - 1;
        while (start >= 0)
        {
            ReHeapDown(start);
            start--;
        }
    }


    void DeleteUser(int id)      //FIRSTLY PLACES THE LAST ELEMENT ON THE GIVEN ELEMENT. 
    {                           //THE GIVEN ELEMENT IS KILLED AND SIZE IS DECREASED IN CODE. 
                               // REHEAP THE REMAINING ARRAY. 
        int index;            //LOGIC SIMILAR TO DELETE MAX.
        bool found = false;
        for (index = 0; index < this->que.size() && !found; index++)  //FINDS THE KEY
        {
            if (que[index] == id)//OPERATOR IS OVERLOADED TO COMPARE USER TO INT I.E USER.ID==ID
            {
                found = true;
            }
        }
        if (!found)
        {
            return;
        }
        else//KEY IS FOUND.
        {
            que[index] = que[que.size() - 1];
            que.resize(que.size() - 1);
            this->currentsize--;
            this->ReHeapDown(index);
        }
    }


    void ReHeapDown(int index)//EXPLAINED IN THE COURSE. SIMPLY MAINTAINS HEAP PROPERTIES.
    {                        // FINDS MAX CHILD FROM TWO CHILDS AND COPY/REPLACE.
        if (index >= currentsize)
            return;
        int child1, child2;
        child1 = 2 * index + 1;
        child2 = 2 * index + 2;
        if (child1 >= currentsize || child2 >= currentsize)
            return;
        if (que[child1] > que[child2])
        {
            UNode<T>temp = que[index];
            this->que[index] = que[child1];
            que[child1] = temp;
            ReHeapDown(child1);
        }
        else
        {
            UNode<T>temp = que[index];
            this->que[index] = que[child2];
            que[child2] = temp;
            ReHeapDown(child2);
        }
    }

    void ReheapUp(int index) // EXPLAINED IN THE COURSE.SIMPLY MAINTAINS HEAP PROPERTIES.
    {
        if (index == 0)
            return;

        if (que[index] > que[(index - 1) / 2])
        {
            UNode<T> temp = que[index];
            this->que[index] = que[(index - 1) / 2];
            que[(index - 1) / 2] = temp;
        }
        ReheapUp((index - 1) / 2);
    }

    UNode<T> ExtractMax()   //EXTRACTS i.e RETURNS THE MAX AND ALSO DELETE IT FROM THE QUE. O(1).
    {
        UNode<T>* temp = new UNode<T>();
        if (currentsize == 0)
            throw("Empty Heap");
        *temp = this->que[0];
        que[0] = que[currentsize - 1];
        currentsize--;
        que.resize(que.size() - 1);
        ReHeapDown(0);
        return *temp;
    }

    UNode<T> FindMax()  //JUST RETURNS MAX NOT TO DELETE IT FRON QUEUE. O(1).
    {
        return(this->que[0]);
    }

    T FindMaxPriority() //RETURNS MAX KEY(PRIORITY) NOT THE WHOLE NODE.
    {
        if (this->currentsize == 0)
            return 0;
        return(this->que[0].key);
    }

    T FindMinPriority()//RETURNS MIN KEY(PRIORITY) NOT THE WHOLE NODE.
    {
        return(this->minimum);
    }

    void Insert(T priority, int id, char operation)//INSERTS A NODE INTO PRIORITY QUEUE.
    {
        Info* I = new Info(id, operation);
        UNode<T>* U = new UNode<T>(priority, *I);

        if (this->currentsize == que.size())
        {
            this->que.resize(currentsize * 2);
        }
        if (this->minimum > priority)//MAINTAINS MINIMUM.
        {
            this->minimum = priority;
        }
        this->que[currentsize] = *U;    //NEW ELEMENT PLACED AT THE END.
        ReheapUp(currentsize);         // PROPERTY IS MAINTAINED.
        this->currentsize++;          //SIZE IS INCREMENTED.

    }

    bool IsReader()             // RETURNS TRUE IF THE USER WITH MAX PRIORITY IS A READER.
    {
        if (this->currentsize == 0)
            return false;
        else
        {
            return(que[0].information.operation == 'R');
        }
    }

    int Size()      //RETURNS CURRENT SIZE.
    {
        return this->currentsize;
    }

    void Empty()    //MAKES THE PRIORITY QEUE EMPTY.
    {
        que._Destroy();
        this->currentsize = 0;
    }

    bool isEmpty()  //RETURNS TRUE IF QUEUE IS EMPTY.
    {
        return(this->currentsize == 0);
    }

    void PrintQueue()   //SIMPLY PRINT THE VECTOR.
    {
        if (que.size() != 0)
        {
            for (int i = 0; i < currentsize; i++)
            {
                que[i].printwithPriority();
                cout << endl;
            }
            cout << endl;
        }
    }
};


class FileNode
{
private:
    int Fid;         //File key.
    PriorityQueue<int>* WaitingQueue;   //POINTER TO USERS IN WAITING QUEUE.
    vector<UNode<int>>CurrentUserAccess;    //AN VECTOR OF USERS WHO HAVE CURRENTLY ACCESS.  
                                          //IF A WRITER HAS ACCESS. THE VECTOR HAS ONE ELEMENTS ONLY 
public:                              //ELSE IF READERS HAVE ACCESS, WE NEED TO STORE MULTIPLE USERS WITH ACCESS
    FileNode() :Fid(-99), WaitingQueue(nullptr)
    {}

    FileNode(int key)
    {
        this->Fid = key;
        WaitingQueue = new PriorityQueue<int>();
    }

    void printFile()    //SIMPLY PRINTS THE FILE FOR WHICH THIS FUNCTION IS CALLED !
    {
        cout << "File Id: " << Fid << endl;
        if (CurrentUserAccess.size() != 0)
        {
            cout << "Access Granted to:  ";
            for (int i = 0; i < CurrentUserAccess.size(); i++)//PRINTS THE USERS WITH ACCESS.
            {
                if (this->CurrentUserAccess[i] != -99)//IN SOME POINTS, DUMMY USERS ARE INSERTED AS DELETION 
                {                                    //OPERATION MIGHT BE CONSTLY.
                    CurrentUserAccess[i].printUser();
                }
            }
        }
        cout << endl << "Waiting Queue: " << "  ";
        this->WaitingQueue->PrintQueue();//PRINTS THE USERS WAITING.
        cout << "......................................................." << endl;
    }

    //NEEDED IN THE CODE !
    bool operator==(const FileNode& F)
    {
        return(this->Fid == F.Fid);
    }

    //NEEDED IN THE CODE !
    bool operator!=(const FileNode& F)
    {
        return(this->Fid != F.Fid);
    }

    //NEEDED IN THE CODE !
    bool operator==(int F)
    {
        return(this->Fid == F);
    }

    friend class HashTable;
};



class HashTable
{
private:
    vector<list<FileNode>>Map;
    /*THIS IS A VECTOR OF LINKED LIST. EACH ROW IN MAPPED VECTOR TABLE CONTAINS A LINKEDLIST
    EACH LINKEDLIST CONTAINS NODES OF FILENODE BASED IN TEMPLATE INT.*/
    int currentsize;

    /* THE BELOW TWO FUNCTIONS ARE KEPT PRIVATE FROM THE OUTER WORLD AS THE SYSTEM DECIDES WHO SHOULD
    BE GRANTED ACCESS OR WHEN THE ACCESS SHOULD BE GRANTED. NOT THE USER ! */

    void GrantAccessToHP(list<FileNode>::iterator L)//Grants Access to the highest priority User in for given File id
    {
        UNode<int>* User;
        User = &(L->WaitingQueue->ExtractMax());
        L->CurrentUserAccess.push_back(*User);
    }

    void GrantAccess(list < FileNode>::iterator I)//GRANTS ACCESS TO THE NEXT USER(S). CALLED BY RELEASE.
    {
        if (!I->WaitingQueue->IsReader())//If The Next User is Writer, Grant him Access !
        {
            GrantAccessToHP(I);
        }
        else   //If He is a Reader, Until Readers are placed in list, give them access.
        {
            while (I->WaitingQueue->IsReader())
            {
                GrantAccessToHP(I);
            }
        }
    }



public:
    HashTable()
    {

        Map.resize(31);
        this->currentsize = 31;
    }
    HashTable(int size)
    {
        Map.resize(size);
        this->currentsize = size;
    }

    void InsertaFile(int id)
    {
        if (!(this->FileExists(id)))//CHECKS IF FILE ALREADY EXISTS IN THE SYSTEM TO AVOID DUPLICATION.
        {//IF NOT, INSERT IT IN THE SYSTEM.
            FileNode* temp = new FileNode(id);
            int index = id % currentsize;
            Map[index].push_back(*temp);
        }

    }


    bool FileExists(int Fileid)//THIS FUNCTION CHECKS IF FILE ALREADY EXISTS IN THE SYSTEM TO AVOID DUPLICATION.
    {
        int index = Fileid % currentsize;
        list < FileNode>::iterator I;
        bool found = false;
        for (I = Map[index].begin(); I != Map[index].end() && !found; ++I)
        {
            if (I->Fid == Fileid)
                found = true;
        }
        return found;
    }

    void RequestFileAccess(int UserId, int Fileid, int priority, char operation)
    {
        int index = Fileid % currentsize; //FINDS THE INDEX WHERE THE FILE CAN BE AT THE TABLE.
        list < FileNode>::iterator I;
        bool found = false;
        for (I = Map[index].begin(); I != Map[index].end() && !found; ++I)//FIND THE FILE.
        {
            if (I->Fid == Fileid)
                found = true;
        }
        if (!found)
        {
            cout << "File Not Found " << endl;
        }
        else
        {//FILE IS NOW FOUND AT --I. BUT THE I WAS INCREMENTED SO WE DECREMENT IT OURSELF.
            --I;
            bool flag = (I->WaitingQueue->isEmpty() && I->CurrentUserAccess.size() == 0);
            I->WaitingQueue->Insert(priority, UserId, operation);//INSERT USER IN THE WAITING QUEUE.
            if (flag)//IF THE WAITING QUEUE WAS PREVIOUSLY EMPTY AND CURRENTLY NO USERS WERE ACCESSING IT,
            {       // THIS COMING USER WAS FIRST SO GRANTED ACCESS.
                this->GrantAccessToHP(I);
            }
        }

    }

    //This one runs for H/L priority
    //OVERLOADED FUNCTION FOLLOWING THE SAME LOGIC WITH PRIORITY AS A CHARACTER PARAMETER.
    void RequestFileAccess(int UserId, int Fileid, char priority, char operation)
    {
        int index = Fileid % currentsize; //FINDS THE INDEX WHERE THE FILE CAN BE AT THE TABLE.
        list < FileNode>::iterator I;
        bool found = false;
        for (I = Map[index].begin(); I != Map[index].end() && !found; ++I)
        {
            if (I->Fid == Fileid)
                found = true;
        }
        if (!found)
        {
            cout << "File Not Found " << endl;
        }
        else
        {//FILE IS NOW FOUND AT --I. BUT THE I WAS INCREMENTED SO WE DECREMENT IT OURSELF.

            --I;
            bool flag = (I->WaitingQueue->isEmpty() && I->CurrentUserAccess.size() == 0);
            int pri;
            if (priority == 'H')
                pri = (I->WaitingQueue->FindMaxPriority()) + 1;
            else
                pri = I->WaitingQueue->FindMinPriority() - 1;

            I->WaitingQueue->Insert(pri, UserId, operation);
            if (flag) //IF THE WAITING QUEUE WAS PREVIOUSLY EMPTY AND CURRENTLY NO USERS WERE ACCESSING IT,
              // THIS COMING USER WAS FIRST SO GRANTED ACCESS.
            {
                this->GrantAccessToHP(I);
            }
        }

    }


    void ReleaseFile(int UserId, int FileId) //FINDS THE INDEX WHERE THE FILE CAN BE AT THE TABLE.
    {
        int index = FileId % currentsize;
        list < FileNode>::iterator I;
        bool found = false;
        for (I = Map[index].begin(); I != Map[index].end() && !found; ++I)//FINDS THE FILE.
        {
            if (I->Fid == FileId)
                found = true;
        }
        if (!found)
        {
            cout << "File Not Found " << endl;
        }
        else
        {
            //FILE IS NOW FOUND AT --I. BUT THE I WAS INCREMENTED SO WE DECREMENT IT OURSELF.

            /*USER CAN BE SOMEONE WHO IS CURRENTLY ACCESSING THE FILE i.e MIGHT BE IN CURRENTLYACCESS USER
            VECTOR OR SOMEONE WHO IS TIRED OF WAITING IN THE QUEUE AND WANT TO LEAVE. BOTH THE CASES ARE
            HANDLED.*/

            --I;
            bool userfound = false;
            //FIND AND DELETE THE GIVEN USER IN THE CURRENTLY ACCESSING ARRAY.
            for (index = 0; index < I->CurrentUserAccess.size() && !userfound; index++)
            {
                if (I->CurrentUserAccess[index] == UserId)
                {
                    UNode<int>* U = new UNode<int>(-99, -99, 'N');
                    I->CurrentUserAccess[index] = *U;//REPLACE WITH DUMMY AS ACTUAL DELETE MIGHT BE CONSTLY.
                    userfound = true;
                }
            }
            if (!userfound)//IF USER IS NOT ACCESSING THEN HE MIGHT BE WAITING IN THE QUEUE.
            {
                //APPARENTLY IT DELETES THE USER IN THE WAITING QUEUE BUT ALSO IT CHECKS IN THE QUEUE IF USER
               //WAS PRESENT OR NOT IN THE QUEUE. IF YES DELETE. IF NO, RETURN AND DO NOTHING.
                I->WaitingQueue->DeleteUser(UserId);
            }
            else
            {
                //GRANT ACCESS TO THE NEXT WAITING USERS. PRIVATE FUNCTION IN THE CLASS AT BEGINNING.
                this->GrantAccess(I);
            }
        }
    }


    //GETS A NAME OF COMMA SEPRATED FILE AND LOADS THE DATA.
    void LoadData(const char* FileName)
    {
        ifstream in(FileName);
        int Fileid, userid, priority;
        char operation;
        /* THESE VARIABLES ARE DECLARED AS THE DATA WAS IN FORM
            FILEID,USERID,PRIORITY,OPERATION
            252334, 1003 ,    5   , 'R'
        */
        while (!in.eof())
        {
            in >> Fileid;
            this->InsertaFile(Fileid);
            in.ignore();
            in >> userid;
            in.ignore();
            in >> priority;
            in.ignore();
            in >> operation;
            this->RequestFileAccess(userid, Fileid, priority, operation);
        }
        return;
    }


    void DeleteaFile(int Fileno)
    {
        int index = Fileno % currentsize;   //CALCULATE INDEX.
        list < FileNode>::iterator I;
        bool found = false;
        for (I = Map[index].begin(); I != Map[index].end() && !found; ++I)//FIND THE GIVEN FILE.
        {
            if (I->Fid == Fileno)
                found = true;
        }
        if (!found)
        {
            cout << "File not found !!" << endl;
        }
        else
        {//FILE IS NOW FOUND AT --I. BUT THE I WAS INCREMENTED SO WE DECREMENT IT OURSELF.

            --I;
            if (I->WaitingQueue->Size() == 0)
            {
                Map[index].erase(I);
            }
        }

    }

    //PRINTS THE HASH TABLE.
    void print()
    {
        cout << endl << "Hash Table " << endl << endl;
        for (int i = 0; i < currentsize; i++)
        {
            list < FileNode>::iterator I;

            for (I = Map[i].begin(); I != Map[i].end(); ++I)
            {
                I->printFile();
                cout << endl;
            }

        }
    }



    void Menu()
    {
        bool end = false;
        while (!end)
        {
            cout << "File Repository System ! " << endl << "Select One To Continue " << endl;
            cout << 1 << " Print Table With File Info " << endl;
            cout << 2 << " Load Data " << endl;
            cout << 3 << " Insert File" << endl;
            cout << 4 << " Delete File " << endl;
            cout << 5 << " Request Access to a File" << endl;
            cout << 6 << " Release File by User" << endl;
            cout << " Any Other Number To Exit " << endl;
            int i;
            cin >> i;
            switch (i)
            {
            case 1: this->print();
                break;
            case 2: this->LoadData("Data.txt");
                break;
            case 3: cout << "Enter File Id " << endl;
                int id;
                cin >> id;
                this->InsertaFile(id);
                break;
            case 4: cout << "Enter File Id " << endl;

                cin >> id;
                this->DeleteaFile(id);
                break;
            case 5:
                int fid, uid, pri;
                char op;
                cout << "Enter File Id " << endl;
                cin >> fid;
                cout << "Enter User Id " << endl;
                cin >> uid;
                cout << "Enter Priority" << endl;
                cin >> pri;
                cout << "Enter Operation 'R'/'W' " << endl;
                cin >> op;
                this->RequestFileAccess(uid, fid, pri, op);
                break;
            case 6:

                cout << "Enter File Id " << endl;
                cin >> fid;
                cout << "Enter User Id " << endl;
                cin >> uid;
                this->ReleaseFile(uid, fid);
                break;
            default:
                cout << "Table Before Exiting the System " << endl;
                this->print();
                end = true;
            }
        }
    }

};



int main()
{

    HashTable H;


    /* H.InsertaFile(1);
     H.InsertaFile(2);
     H.InsertaFile(4);
     H.InsertaFile(7);
     H.RequestFileAccess(1003, 1, 3, 'R');
     H.RequestFileAccess(1004, 1, 2, 'R');
     H.RequestFileAccess(1005, 1, 7, 'R');
     H.RequestFileAccess(1008, 1, 5, 'W');
     H.RequestFileAccess(2003, 4, 'H', 'W');
     H.RequestFileAccess(3003, 4, 'L', 'R');
     H.RequestFileAccess(3004, 4, 2, 'R');

     H.RequestFileAccess(4003, 7, 3, 'R');
     H.RequestFileAccess(4004, 7, 99, 'W');
     H.print();

     cout << "After Releasing"<<endl<<endl;
     H.ReleaseFile(2003, 4);

     H.ReleaseFile(4003, 7);
     H.ReleaseFile(1008, 1);
     H.print();*/


     /* cout << endl << endl << "After Deleting " << endl;
      H.DeleteaFile(1);
      H.print();*/

      /*H.LoadData("Data.txt");
      H.print();*/

    H.Menu();

    return 0;
}




