#include<iostream>
#include<string.h>
#include<conio.h>
#include<iomanip>
#include<string>
#include<stdio.h>
using namespace std;
class flight;
class user{
	string name;
	long int passport_number;
	float price_of_ticket;
	char seat_no[3];
	public:
		void get_price(float x){
			price_of_ticket=x;
		}
		void get_seat(char x,char y,char z){
			seat_no[0]=x;seat_no[1]=y;seat_no[2]=z;
		}
		long long int get_num(){
			return passport_number;
		}
		void user_detail();
		void show_ticket(flight*ptr);
		void display();//done
};

class Node{
public:
    int data;
    user p1;
    Node* next;
    Node(int d){
        data = d;
        next=NULL;
    }
};

struct Node2d{
    int data;
    user p2;
    Node2d* right, *down;
    Node2d(int d){
        data = d;
        right = down = NULL;
    }
};

Node* Fcseats(int x){
    Node*p=NULL;
    p=new Node(0);
    Node* head=p;
    for(int i=1;i<x;i++){
        Node* t;
        t=new Node(0);
        p->next=t;
        p=p->next;
    }

    return head;
}

Node2d*Ecoseats(int m, int n){
    Node2d* Mhead = NULL;
    Node2d* head[m];
    Node2d *pright, *temp;
    for (int i = 0; i < m; i++){
        head[i] = NULL;
        for (int j = 0; j < n; j++){
            temp = new Node2d(0);
            if (!Mhead)
                Mhead = temp;

            if (!head[i])
                head[i] = temp;
            else
                pright->right = temp;

            pright = temp;
        }
    }

    for (int i = 0; i < m - 1; i++){
        Node2d *t1 = head[i], *t2 = head[i + 1];
        while (t1 && t2){
            t1->down = t2;
            t1 = t1->right;
            t2 = t2->right;
        }
    }

    return Mhead;
}
class flight{
public:
	string flightname;
	string arrival_time;
	string departure_time;
	float price_economyclass;
	float price_firstclass;
	string dest;
	string from;
	int counteco;
	int countfirst;
    Node2d*Ehead;
    Node*Fhead;
    flight(){
        Fhead=Fcseats(5);
        Ehead=Ecoseats(6,6);
        counteco=36;
        countfirst=5;
    }
    void displaySeats();//done
    void add_details();//done
    void default_flight(string f,string at,string dt,float pe,float pf,string destination,string source){
        flightname=f;
        arrival_time=at;
        departure_time=dt;
        price_economyclass=pe;
        price_firstclass=pf;
        dest=destination;
        from=source;
    }
    void flight_info();//done
    void passenger_info(int num);
    int reservation(int x,int y,int n);//done
    ~flight(){
        Node2d*ptr,*temp1=Ehead,*temp;
        while(temp1!=NULL){
            ptr=temp1;
            while(ptr!=NULL){
                temp=ptr;
                ptr=ptr->right;
                delete temp;
            }
            temp1=temp1->down;
        }
        Node*p1=Fhead,*t1;
        while(p1!=NULL){
            t1=p1;
            p1=p1->next;
            delete t1;
        }
    }
};

class node_flight{
	public:
	flight f;
	struct node_flight*next;
};

class administrator{
	public:
	void add_flight(node_flight **head);
	void edit_flight(string s,node_flight*head);
	void delete_flight(node_flight**head,string s);
};

node_flight*traverse(node_flight*head,string name) //name must be search//
{
	node_flight*ptr=head;
	while(ptr!=NULL){
		if(ptr->f.flightname==name)
		return ptr;
		ptr=ptr->next;
	}

	return ptr;
}

void user::user_detail(){
    cout<<"\nIn order for us to do anything, first we need some details : "<<endl;
	cout<<"\nYour name :: ";
	fflush(stdin);
	getline(cin,name);
	cout<<"\nYour passport number :: ";
	cin>>passport_number;
}

void user::display(){
    cout<<"";
    if(seat_no[2]==1&&seat_no[0]=='A')
    seat_no[0]='W';
	cout<<"\nName :: "<<name<<"\tPassport number :: "<<passport_number<<"\tSeat number is :: "<<seat_no[0]<<(int)seat_no[1]<<(int)seat_no[2];
}

void user::show_ticket(flight *ptr)
{
	char c[90]={"<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>"};
	cout<<c<<endl;
	display();
	ptr->flight_info();
	cout<<"\nPrice of ticket :: "<<price_of_ticket;
	seat_no[0]=='A'?cout<<"\nFIRST CLASS":cout<<"\nECONOMY CLASS";
	if(seat_no[2]==1||seat_no[0]=='B')
	cout<<"\tWINDOW SEAT";
	if((seat_no[2]==3||seat_no[2]==4)&&seat_no[0]=='A')
	cout<<"\tAISLE SEAT";
	cout<<"\nSEAT IS CONFIRMED\n";
	cout<<c;
}

void flight :: displaySeats(){
	int i=1;
    Node2d *R, *D = Ehead;
    cout<<"economy class "<<endl;
    cout<<"\nHere 0 indicates for vaccant seat ad 1 for occupied seat \n";
    cout<<"  1 2 3 4 5 6"<<endl;
    while (D!=NULL){
        R = D;
        cout<<i<<" ";
        while (R!=NULL){
            cout << R->data << " ";
            R = R->right;
        }
        cout << endl;
        D = D->down;
        i++;
    }
    cout<<"\nfirst  class "<<endl;
    Node*head2=Fhead;
    cout<<"1 2 3 4 5"<<endl;
    while(head2!=NULL){
        cout<<head2->data<<" ";
        head2=head2->next;
    }
    cout<<endl;
}

void flight::add_details(){
	cout<<endl<<"Add schedule for a new flight -";
	cout<<endl<<"Name of flight :: ";
	fflush(stdin);
	getline(cin,flightname);
	cout<<"Arrival time :: ";
	fflush(stdin);
	getline(cin,arrival_time);
	cout<<"Departure time :: ";
    fflush(stdin);
	getline(cin,departure_time);
	cout<<"Price for an Economy Class Seat ::";
	cin>>price_economyclass;
	cout<<"Price for a Luxury Class Seat :: ";
	cin>>price_firstclass;
	cout<<"Flight will be boarding From :: ";
	fflush(stdin);
	getline(cin,from);
	cout<<"To Destination :: ";
	fflush(stdin);
	getline(cin,dest);
}

void flight::flight_info(){
	cout<<endl;
	cout<<"FLIGHT NAME:: "<<setw(20)<<flightname;
	cout<<"\nDeparture time::"<<setw(5)<<departure_time;
	cout<<"\tArrival time::"<<setw(5)<<arrival_time;
	cout<<"\tFrom "<<setw(5)<<from<<"\tto "<<setw(5)<<dest;
}
void flight::passenger_info(int num){
	Node2d*ptr,*temp=Ehead;
	while(temp!=NULL){
		ptr=temp;
		while(ptr!=NULL){
			if(ptr->p2.get_num()==num){
				ptr->p2.show_ticket(this);
				return ;
			}
			ptr=ptr->right;
		}
	temp=temp->down;
	}
	Node*p=Fhead;
	while(p!=NULL){
		if(p->p1.get_num()==num){
			p->p1.show_ticket(this);
            return ;
		}
		p=p->next;
	}
	cout<<"\nNo passemger found with this passport number";
}
int flight::reservation(int x,int y,int n)
{
    int v=n;
	   if(x==1)
	   {
	   	   if(counteco<n)
	   	   return 0;
	       Node2d*ptr,*temp=Ehead;
           int c=1,k=1,m=n;
           if(y==0)
           {
        	  while(temp!=NULL&&n!=0)
			  {
			  ptr=temp;
			  c=1;
		      while((ptr!=NULL)&(n!=0))
		      {
		          if(ptr->data==0)
				  {
			         ptr->data=1;
			         ptr->p2.user_detail();
			         ptr->p2.get_price(price_economyclass);
		             ptr->p2.get_seat('A',k,c);
			         cout<<"\nYour seat has been booked."<<endl;
			         counteco--;n--;
		          }
		           c++;
		           ptr=ptr->right;
			  }
			  k++;
			   temp=temp->down;
		     }
		     return 1;
		   }
        if(y==1)
        {
        	k=1;c=1;
        	temp=Ehead;
           while(temp!=NULL&&n!=0)
          {
        	if(temp->data==0)
        	{
        		temp->data=1;
			    temp->p2.user_detail();
			    temp->p2.get_price(price_economyclass);
		        temp->p2.get_seat('A',k,c);
			    cout<<"\nYour seat has been booked."<<endl;
			    counteco--;n--;c++;
			    ptr=temp;
			    m=n;
			    while(ptr!=NULL&&n!=0)
			      {
			      	if(ptr->data==0)
			      	m--;
			      	ptr=ptr->right;
				  }
				  break;
			}
			k++;
			temp=temp->down;
		}
		if(n==0)
		return 1;
		if(m>0)
		{
			temp=Ehead;
			k=1;c=1;
			while(temp!=NULL&&n!=0)
			{
			ptr=temp;
			c=1;
		   while(ptr!=NULL&&n!=0)
		   {
		        if(ptr->data==0)
				{
			      ptr->data=1;
			      ptr->p2.user_detail();
			      ptr->p2.get_price(price_economyclass);
		          ptr->p2.get_seat('A',k,c);
			      cout<<"\nYour seat has been booked."<<endl<<endl<<endl<<endl;
			      counteco--;n--;
		       }
		       c++;
		       ptr=ptr->right;
			}
			k++;
			temp=temp->down;
		}
		return 1;
		}
		else
		{
			c=2;
			ptr=temp->right;
			while(ptr!=NULL&&n!=0)
		   {
		        if(ptr->data==0)
				{
			      ptr->data=1;
			      ptr->p2.user_detail();
			      ptr->p2.get_price(price_economyclass);
		          ptr->p2.get_seat('A',k,c);
			      cout<<"\nSeat is booked";
			      counteco--;n--;
		       }
		       c++;
		       ptr=ptr->right;
			}
		}
	}

	}
	else
	{
		if(countfirst<n)
		return 0;
		Node*f=Fhead;
		int c=1;
		while(f!=NULL&&n!=0)
		{
			if(f->data==0){
				f->data=1;
				f->p1.user_detail();
			    f->p1.get_price(price_firstclass);
				f->p1.get_seat('B',0,c);
				cout<<"\nSEAT IS BOOKED";
				countfirst--;
				n--;
			}
			c++;
			f=f->next;
		}
		return 1;
	}
}
void administrator::add_flight(node_flight**head){
	node_flight*temp;
	temp=new node_flight;
	temp->next=NULL;
	temp->f.add_details();
	if(*head==NULL){
		*head=temp;
	}
	else{
		node_flight*ptr=*head;
		while(ptr->next!=NULL){
			ptr=ptr->next;
		}
		ptr->next=temp;
	}
	cout<<"New flight has been successfully added to the schedule."<<endl<<endl;
}
void cancel_seat(int pass_no, flight &flt){
Node2d*ptr,*temp=flt.Ehead;
	while(temp!=NULL){
		ptr=temp;
		while(ptr!=NULL){
			if(ptr->p2.get_num()==pass_no){
				ptr->data=0;
				return;
			}
			ptr=ptr->right;
		}
	temp=temp->down;
	}
	Node*p=flt.Fhead;
	while(p!=NULL){
		if(p->p1.get_num()==pass_no){
			p->data=0;
			return;
		}
		p=p->next;
	}
	cout<<"\nNo passemger has been found with this Travel Passport Number";
}
void administrator::edit_flight(string s,node_flight*head)
{
	node_flight*ptr=traverse(head,s);
	if(ptr==NULL){
		cout<<"NO flight with this name is exist";return;
	}
	cout<<"\n\nMatching Flight(s) has been Found!";
	cout<<"\nAre you sure you want to edit the selected flight? Enter 1 to confirm, else enter 0 : ";
    int k=0;
    cin>>k;
	if(k==1){
        int choice;
        m1_ef:
        cout<<"\nWhat would you like to change ?Enter the appropriate option number.";
        cout<<"Change ";
        cout<<"\n1                   Name of the Flight";
        cout<<"\n2                   Arrival of the Flight";
        cout<<"\n3                   Departure of the Flight";
        cout<<"\n4                   Seating class costs of the Flight";
        cout<<"\n5                   Destination of the Flight";
        cout<<"\nOr, would you like to";
        cout<<"\n9                   Cancel a seat on the flight";
        cout<<"\nEnter 0 to Go Back"<<endl;
        //cout<<"\n8 for edit a seat in flight";
        cout<<"\nEnter your choice :: ";
        cin>>choice;
        switch (choice){
        case 1:{
            cout<<"\nEnter new name of the flight :: ";
            fflush(stdin);
            getline(cin,ptr->f.flightname);
            break;
        }
        case 2:{
            cout<<"\nEnter new Arrival time of the flight :: ";
            fflush(stdin);
            getline(cin,ptr->f.arrival_time);
            break;
        }
        case 3 :{
            cout<<"\nEnter new Departure time of the flight :: ";
            fflush(stdin);
            getline(cin,ptr->f.departure_time);
            break;
        }
        case 4:{
            int j;
            m2_ef:
            cout<<"\nFor which seating class would you like to change the price of ?"<<endl;
            cout<<"1            for Luxury Class"<<endl;
            cout<<"2            for Economy Class"<<endl;
            cout<<"0 to return to previous menu"<<endl;
            cout<<"Enter Appropriate option number :: "<<endl;
            cin>>j;
            if(j==0)
                goto m1_ef;
            if(j==1){
                cout<<"\nEnter new price for the Luxury Class :: ";
                cin>>ptr->f.price_firstclass;
                cout<<"\nThe Data for selected flight with name has been successfully updated."<<endl<<endl;
                goto m2_ef;
            }
            else if(j==2){
                cout<<"\nEnter new price for the Economy Class :: ";
                cin>>ptr->f.price_economyclass;
                cout<<"\nThe Data for selected flight with name has been successfully updated."<<endl<<endl;
                goto m2_ef;
            }
            else{
                cout<<"You have entered an invalid choice. Please try again."<<endl;
                goto m2_ef;
            }
            break;
        }
        case 5:{
            cout<<"\nEnter new Destination for the selected flight :: ";
            fflush(stdin);
            getline(cin,ptr->f.dest);
            break;
        }
        case 9:{
            int pass_no;
            cout<<"\nEnter Travel Passport Number of the Passenger :: ";
            cin>>pass_no;
            cancel_seat(pass_no,ptr->f);
            break;
        }
        case 0:{
            return;
        }
        default:{
            cout<<"\nYou have entered an invalid choice. Please try again.";}
            goto m1_ef;
		}
		m3_ef: cout<<"\nThe Data for selected flight with name has been successfully updated."<<endl<<endl;
		goto m1_ef;
}
}
void administrator::delete_flight(node_flight **head,string s)
{
cout<<"\nAre you sure you want to  delete the selected flight? Enter 1 to confirm, else enter 0."<<endl;
        int k=0;
        cout<<"Your input :: ";
        cin>>k;
        if (k)
        {
            node_flight*ptr=*head,*preptr;
	while(ptr!=NULL)
	{
            if(ptr->f.flightname==s)
			{
                if(ptr==*head)
				{
                    *head=ptr->next;
                    delete ptr;
                }
                else{
                    preptr->next=ptr->next;
                    delete ptr;
                }
                break;
            }
            preptr=ptr;
            ptr=ptr->next;
        }

    cout<<"\nFlight schedule has been updated succesfully.\n";
        }
        else
            cout<<"\nPlease enter correct flight name";
}

void flight_schedule(node_flight**head)
{
	node_flight*ptr=*head;
	char c[90]={"-----------------------------------------------------------------"};
	cout<<c<<endl;
	while(ptr!=NULL){
		ptr->f.flight_info();
		ptr=ptr->next;
		cout<<endl;
	}
	cout<<c;
}
void display_passengers(node_flight*ptr){
	cout<<"\nPassengers in flight";
	cout<<"\nSeats in Economy Class";
	int c=0;
	Node2d*temp,*temp2=ptr->f.Ehead;
	while(temp2!=NULL)
	{
        temp=temp2;
        while(temp!=NULL){
            if(temp->data==1)
            {
                temp->p2.display();
                cout<<endl;
                c++;
            }
            temp=temp->right;
        }
        temp2=temp2->down;
    }
    cout<<"\nSeats in Luxury Class";
    Node*temp3=ptr->f.Fhead;
    while(temp3!=NULL){
        if(temp3->data==1){
            temp3->p1.display();
            cout<<endl;
            c++;
        }
        temp3=temp3->next;
    }
    if(c==0)
    cout<<"\nThere are no passenger booked till now"<<endl;
}

int main(){
    node_flight *start=NULL;
    node_flight*temp=new node_flight;
    temp->f.default_flight("AD616","2:00pm","3:00pm",450,890,"Delhi","Los Angeles");
    temp->next=NULL;
    start=temp;
    temp=new node_flight;
    temp->next=NULL;
    start->next=temp;
    temp->f.default_flight("A380","2:00pm","3:00pm",450,890,"Delhi","Vancouver");

    int choice;
    homepage:
    cout<<setw(10)<<"\nWelcome to Indira Gandhi International Airport";
    while(1){
        cout<<"\nTo begin booking your Tickets, enter 1"; //Enter 1152 for super user acoount

          cout<<"\nIf you are administrator then login";
        cout<<"\nEnter 0 to exit";

        cout<<"\n\n\n\nAnd your choice is :: ";
        cin>>choice;
        if(choice==1152){
            administrator admin;
            string s;
            m1_su:
            cout<<"Superuser has been activated.\nEnter appropriate option number :";
            cout<<"\n1            Add flight";
            cout<<"\n2            Edit a flight";
            cout<<"\n3            Delete a flight";
            cout<<"\n4            Display schedule of all flight";
            cout<<"\nEnter 0 to return to Welcome Page"<<endl;
            cout<<"\n\nYour choice  is :: ";
            cin>>choice;
            switch(choice){
                case 0:{
                    goto homepage;
                }
                case 1:{
                    admin.add_flight(&start);
                    goto m1_su;
                    break;
                }
                case 2:{
                    if(start==NULL)
                        cout<<"\nThere are no flight scheduled to take off.";
                    else{
                        flight_schedule(&start);
                        string c;
                        cout<<"\nName of the flight you want to edit : ";
                        cin>>c;
                        admin.edit_flight(c,start);
                    }
                    goto m1_su;
                    break;
                }
                case 3:{
                    if(start==NULL){
                        cout<<"\nThere are no flight scheduled to take off.";
                    }
                    else{
                        cout<<"\nName of the flight you want to delete : ";
                        cin>>s;
                        admin.delete_flight(&start,s);
                    }
                    goto m1_su;
                    break;
                }
                case 4:{
                    flight_schedule(&start);
                    goto m1_su;
                    break;
                }
                case 5:{
                    cout<<"\nYou have entered an invalid choice. Please try again.";
                    goto m1_su;
                }
            }
        }
        else if(choice==1){
            string s;
            if(start==NULL){
                cout<<"\nThere are no flight scheduled to take off.";
                //cout<<"\n*THANKS";
            }
            else{
                m1_user:
                choice = 0;
                cout<<"\nWelcome Traveller, what would you like to do? Enter appropriate choice number";
                cout<<"\n1              Book a trip around the World.";//done
                cout<<"\n2              Lookup your trip details.";
                cout<<"\n3              Lookup available seats to display all passengers.";//to display all passengers
                cout<<"\n4              Show available/booked seat in a particular flight.";
                cout<<"\n               Enter 5 to exit";
                cout<<"\nAnd your choice is :: ";
                cin>>choice;
                if(choice==5)
                {
                	cout<<"\nEXIT";
                	exit(1);
				}
                flight_schedule(&start);

                cout<<"\nEnter flight name from above scheduled flights:: ";
               //scanf(" %[^\n]s",s);
               fflush(stdin);
                getline(cin,s);
                node_flight*ptr=traverse(start,s);
                if(ptr==NULL){
                    cout<<"No search results for the flight(s) are there."<<endl<<endl<<endl<<endl<<endl;
                    goto m1_user;
                    break;
                }
                else{
                    switch(choice){
                        case 1:{
                            int eco,first,check,n=1;
                            cout<<"\nEnter the number of seats in Economy Class :: ";
                            cin>>eco;
                            cout<<"\nEnter 1 if you would like a window seat, else press 0 for any seat";
                            cin>>n;
                            check=ptr->f.reservation(1,n,eco);
                            if(!check){
                                cout<<"Seats are unavailable. Please look for an alternative.";
                                goto m1_user;
                            }

							/*	}
								else if(eco>0)
								{
								check=ptr->f.reservation(1,n,eco);
								if(!check)
									{
                                        cout<<"SEAT IS NOT AVAILIBLE";
                                    }
                                }*/
                            cout<<"All the seats in Luxury Class are by the window"<<endl;
                            cout<<"\nNumber of seats in Luxury Class :: ";
                            cin>>first;
                            if(first>0){
                                check=ptr->f.reservation(2,1,first);
                                if(!check==1)
                                    cout<<"\nSeats are unavailable. Please try an alternative."<<endl;
                            }
                        }
                        case 3:{
                            display_passengers(ptr);
                            break;
                        }
                        case 2:{
                            long long int p;
                            cout<<"\nEnter User's Travel Passport Number";
                            cin>>p;
                            ptr->f.passenger_info(p);
                            break;
                        }
                        case 4:{
                            ptr->f.displaySeats();
                            break;
                    }
                        default:{
                            cout<<"You have entered an invalid choice. Please try again.";
                        }
                    }
                }
            }
        }
        else if(choice==0){
            cout<<"\n####################THANK YOU FOR USING OUR SERVICES############################";
            exit(1);
        }
        else{
            cout<<"\nYou have entered an invalid choice. Please try again.";
        }
    }
}

