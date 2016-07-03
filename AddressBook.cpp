#include <iostream>
#include<fstream>
#include<time.h>
#include<dos.h>
#include<string.h>
#include<ctype.h>

using namespace std;

class Address_book;
class log;

class contact
{
private:
     char name[20];
     char mobno[15];


public:
    friend istream& operator >> ( istream &in , contact &arg )
    {
	cout << "Enter details ( name & mob no, )" << endl;
	in >> arg.name >>arg.mobno;
	return in;
    }

friend ostream & operator << ( ostream &out , contact &arg )
   {
	out <<"name: "<< arg.name << endl
		<<"mobile number :" << arg.mobno << endl
		<<"------------------\n\n";
	return out;
   }

char * getname()
{
    return name;
}
 char * getno()
 {
     return mobno;
 }

 friend class Address_book;

};

class Address_book
{
private:
    static int index;
    contact obj[100];

public:
    void add();
    void findc_num();
    void findc_name();
    void update();
    void dlet();
    void listall();
    int loadcontact();
    //int getcontctCount();
    //void storecontact();
    //void storecontact1();
    //friend class log;
};
int Address_book::index=-1;


void Address_book::add()
{
    fstream fp;
    contact a;
    index=loadcontact();
    if(index==-1)
        index++;
    cin>>a;
    fp.open("f:/contact.txt",ios::out);
    strcpy(obj[index].name,a.getname());
    strcpy(obj[index].mobno,a.getno());
    for(int i=0;i<=index;i++)
    {
        fp.write((char *)&obj[i],sizeof(a));
    }
    fp.close();
}

void Address_book::update()
{
    fstream fp;
    int i;
    contact a;
    char nnam[20],nmob[15];
    index=loadcontact();
    if(index==-1)
    {
        cout<<"\n\nThere is no contact to edit \n\n";
    }
    else
    {
        cout<<"Enter the index no : ";
    cin>>i;
    if(i<0||i>100||i>=index)
    {
        cout<<"invalid entry\n\n";
    }
    else
    {
        cout<<"enter new name:\n\n";
        cin>>nnam;
        cout<<"enter new mob no: ";
        cin>>nmob;
        strcpy(obj[i].name,nnam);
        strcpy(obj[i].mobno,nmob);
    }
    fp.open("f:/contact.txt",ios::out);
    for(int j=0;j<index;j++)
    {
        fp.write((char *)&obj[j],sizeof(a));
    }
    fp.close();
    }

   // storecontact();
}

/*int Address_book::getcontctCount()
{
    contact c;
    fstream fp;
    loadcontact();
    fp.open("f:/contact.txt",ios::in);
    fp.seekg(0,ios::end);
    int recs = fp.tellg()/sizeof(c);
    fp.seekg(0,ios::beg);
    fp.close();
    return recs;
}*/


/*void Address_book::storecontact()
{
    fstream fp;
    contact c1;
    fp.open("f:/contact.txt",ios::app);
    for(int i=0;i<=index;i++)
    {
         fp.write( (char *)&obj[i], sizeof(c1));
    }
    fp.close();
}

void Address_book::storecontact1()
{
    fstream fp;
    contact c;
    fp.open("f:/contact.txt",ios::out);
    for(int i=0;i<=index;i++)
    {
         fp.write( (char *)&obj[i], sizeof(c));
    }
    fp.close();
}*/

int Address_book::loadcontact()
{
    contact c;
    int i=-1;
    fstream fp;
    fp.open("f:/contact.txt",ios::in);
    if(fp.fail())
    {
       cout<<"YOUR CONTACT LIST IS EMPTY. START SAVING NOW   :\n\n";
    }
    else
    {
        while(!fp.eof())
        {
        i++;
        fp.read((char *)&c,sizeof(c));
        strcpy(obj[i].name,c.name);
        strcpy(obj[i].mobno,c.mobno);
        }
    }
     fp.close();
     return i;
}

void Address_book::findc_num()
{
    char mob[15];
    int flag=0;
    index=loadcontact();
    if(index==-1)
    {
        cout<<"\n\nThere is no contact in the phone book\n\n";
    }
    else
    {
        cout<<"enter the mobile no:\n\n";
    cin>>mob;
    for(int i=0;i<=index;i++)
    {
        if(strcmp(obj[i].mobno,mob)==0)
        {
            flag=1;
            cout<<"found:\n\n";
            cout<<obj[i];
            break;
        }
    }
    if(flag==0)
    {
         cout<<"Not found\n\n";
    }

    }

}

void Address_book::findc_name()
{
    char nam[20];
    int flag=0;
    index=loadcontact();
    if(index==-1)
    {
        cout<<"\n\nThere is no contact in the phone book\n\n";
    }
    else
    {
        cout<<"enter the name:\n\n";
    cin>>nam;
    for(int i=0;i<=index;i++)
    {
        if(strcmp(obj[i].name,nam)==0)
        {
            flag=1;
            cout<<"found:\n\n";
            cout<<obj[i];
            break;
        }
    }
    if(flag==0)
    {
         cout<<"Not found\n\n";
    }
    }
}



void Address_book::listall()
{
    index=loadcontact();
    if(index==-1)
    {
        cout<<"\n\nThere is no contact to display\n\n";
    }
    else
    {
        for(int i=0;i<index;i++)
        {
        cout<<i<<". ";
        cout<<obj[i];
        cout<<"\n\n";
        }
    }
}

void Address_book::dlet()
{
    int n,i;
    fstream fp;
    contact a;
    index=loadcontact();
    if(index<0)
    {
        cout<<"\n\nThere is no contact to delete\n\n";
    }
    else
    {
    listall();
    cout<<"\n\n Enter the index number:\n\n";
    cin>>n;
    cout<<"deleted contact is:\n\n";
    cout<<obj[n];
    for(i=n;i<index;i++)
    {
        strcpy(obj[i].name,obj[i+1].name);
        strcpy(obj[i].mobno,obj[i+1].mobno);
    }

    fp.open("f:/contact.txt",ios::out);
    for(i=0;i<index;i++)
    {
        if(i!=n)
        fp.write((char *)&obj[i],sizeof(a));
    }

    fp.close();
    delete(&obj[index]);
    }
}



class log:public Address_book
{
private:
    contact num;
    char status[10];
    char date[20];
    char time[15];
    char duration[15];

public:
    void placecall();
    void display();
    void storelog();
};

void log::storelog()
{
    log l;
    fstream fp;
    char day[25];
    strcat(day,"f:/");
    strcat(day,__DATE__);
    strcat(day,".txt");
    fp.open("day",ios::app);
    fp.write((char *)&l,sizeof(l));
    fp.close();
}

void log::placecall()
{
    log l;
    Address_book a;
    int ch;
    a.listall();
    cout<<"\n\nSelect the contact(index number) : ";
    cin>>ch;
    strcpy(l.date,__DATE__);
    strcpy(l.duration,"3:30min");
    strcpy(l.status,"outgoing");
    strcpy(l.time,__TIME__);
    cout<<"successful\n\n";
    storelog();
}

/*void log::display()
{
    fstream fp;
    char day[15];
    char rec[100];
    strcpy(day,"f:/");
    strcat(day,__DATE__);
    strcat(day,".txt");
    fp.open("day",ios::in);
    fp.read((char *)&rec,sizeof(rec));
    cout<<rec;
    fp.close();

}
*/

int main()
{
    log l;
    Address_book a;
    int choice;
while(1)
{
       cin.ignore();
       cout<<"Enter The Choice\n\n";
       cout<<"1. Add contact\n\n"
		   <<"2. Delete a contact\n\n"
		   <<"3. Edit contact\n\n"
		   <<"4. Search based on name\n\n"
		   <<"5. Search based on contact number\n\n"
           <<"6. Display all contacts\n\n"

		   <<"7. Call\n\n"
		   <<"8. Save log in a file\n\n"
		   <<"9. List all logs\n\n"
		   <<"10. List only incoming calls\n\n"
		   <<"11.List only outgoing calls\n\n"
           <<"12.Exit\n\n";

    cin>>choice;

    switch(choice)
    {
        case 1: a.add();
                break;

        case 2: a.dlet();
                 break;

        case 3: a.update();
                break;

        case 4: a.findc_name();
                break;

        case 5: a.findc_num();
                break;

        case 6: a.listall();
                break;

        case 7: l.placecall();
                break;

        case 8 : l.storelog();
                break;

        case 9 :
                 break;


        case 10 :
                 break;

        case 11:
                 break;


        case 12:   return 0;
                   break;

        default : cout<<"ENTER A VALID CHOICE :- \n\n";
                    break;
    }
}
    return 0;
}


