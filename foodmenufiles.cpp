#include<fstream.h>
#include<conio.h>
#include<process.h>
#include<dos.h>
#include<stdio.h>
#include<string.h>

/*
	Aim - To design an interface for food delivery app
	Made By - Saiyam Kalra
*/

const top=10;                           // constant for displaying as menu
int b1=21,b2=22;                        // variables for displaying as menu
int y1,y2;                              // variables for displaying as menu

void masterread(); 			//To Read from file and display as a Menu
void mastersort();		       	//To Sort the master file

void drawline()
{
	int i;
	for( i=0 ; i<10 ; ++i)
		cout<<" ";
	for( i=0 ; i<60 ; ++i)
		cout<<"*";
	cout<<endl;
}

class food                                 // class for dish name, code and price of the dish
{
	int code;
	char name[40];
	float price;

	public:
		void getf()
		{
			cout<<"Enter Code: ";
			cin>>code;
			cout<<"Enter Name of Dish: ";
			gets(name);
			cout<<"Enter Price: ";
			cin>>price;
		}
		void show()
		{
			cout<<"\nCode: "<<code<<endl;
			cout<<"Name of Dish: "<<name<<endl;
			cout<<"Price: "<<price<<endl;
		}

		void get_only_code()			//To get only code from user
		{
			cout<<"Enter Code: ";
			cin>>code;
		}

		void ch_code( int t )
		{
			code=t;
		}

		void showf();

		int getcode()                        		   //To return code
		{
			return code;
		}
		char* getname()
		{
			 return name;
		}
		void cprice( float f)				//To change the price of an item
		{
			price=f;
		}
		float getprice()				//To return price
		{
			return price;
		}
		void assign( food f )
		{
			strcpy(name,f.name);
			price=f.price;
		}

};

class order: public food				//a class to store order of a customer
{
	int quantity;
	public:
		void get_order();		//To accept the order

		int g_qty()			//To return the quantity of an item
		{
			 return quantity;
		}
		void disp_order()		//To display the order
		{
			show();
			cout<<endl<<"Quantity : "<<quantity<<endl<<endl;
		}
};

void order::get_order()                         //To accept the order
{
	get_only_code();
	if( getcode()!=0 )
	{
		cout<<"Enter the quantity : ";
		cin>>quantity;
		cout<<endl;
	}
}

class customer                                  //A class to store customers and their orders in a file
{
	char n[20];
	char address[40];
	char mob_no[11];
	order ob[40];
	int no;
	int bill;
	public:
		void get_name()			//To get the name of the customer
		{
			cout<<" Enter your name : ";
			gets(n);
		}

		void disp_name()			//To display name
		{
			cout<<n;
		}

		void show_cus();

		void or_cpy( order[],int);      //To copy the order in class object

		void get_add_mob()		//To get all details except name
		{
			cout<<endl<<endl<<" Enter your address : ";
			gets(address);
			cout<<" Enter your mobile number : ";
			cin>>mob_no;
		}
		void calc_bill(order[]);		//To Calculate and Display the Bill

		int ret_bill()                    //To return the bill
		{
			return bill;
		}

		char* ret_mob()
		{
			return mob_no;
		}

		void assign( int n )
		{
			no=n;
		}
};

void customer::show_cus()			//show as reciept
{
	clrscr();
	drawline();
	cout<<"				      BILL "<<endl<<endl;
	cout<<" Name of customer : "<<n<<endl
	<<" Address of customer : "<<address<<endl
	<<" Mobile Number of customer : "<<mob_no<<endl<<"Order is"<<endl;
	for( int i=0 ; i<no ; ++i )
		ob[i].show();
	cout<<" Your Bill : "<<bill<<endl;
	drawline();
	getch();
}

void customer::or_cpy( order o[] , int m )	//To copy the order in class object
{
	for( int i=0 ; i<m ; ++i )
	{
		ob[i]=o[i];
	}

}

void customer::calc_bill( order o[] )   	//To Calculate and Display the Bill
{
	bill=0;
	fstream file("MASTER.txt",ios::in|ios::binary);
	int i=0;
	food f;
	while(file.read((char*)&f,sizeof(f)))
	{
		if (o[i].getcode()==f.getcode())
		{
			bill+=(f.getprice()*o[i].g_qty());
			if ((i+1)%2==0)
				getch();
			i++;
		}
	}
	file.close();
	cout<<"\n\n Your Bill Amount is: "<<bill<<endl<<endl;
}

void food::showf()			//Used in Displaying Menu acc. to codes
{
	if( code<=20 )
	{
		cout<<"  "<<code<<". ";
		gotoxy(8,y1);
		cout<<name;
		gotoxy(34,y1);
		cout<<price;
		y1++;
		if(y1==b1)
			y1=top;
	}
	else if( code<=40 )
	{
		gotoxy(42,y2);
		cout<<"  "<<code<<". ";
		gotoxy(50,y2);
		cout<<name;
		gotoxy(74,y2);
		cout<<price;
		y2++;
		if(y2==b2)
			y2=top;
	}
	else if( code<=50 )
	{
		gotoxy(0,y1);
		cout<<"  "<<code<<". ";
		gotoxy(8,y1);
		cout<<name;
		gotoxy(34,y1);
		cout<<price;
		y1++;
		if(y1==b1)
			y1=top;
	}
	else if( code<=70 )
	{
		gotoxy(42,y2);
		cout<<"  "<<code<<". ";
		gotoxy(50,y2);
		cout<<name;
		gotoxy(74,y2);
		cout<<price;
		y2++;
		if(y2==b2)
			y2=top;
	}
}

void Sort_order( order A[] , int m )		//To sort the order taken from user in ascending order
{
	order least,t;
	int i,j,pos;
	for( i=0 ; i<m-1 ; ++i )
	{
		least=A[i],pos=i,j=i+1;
		for( ; j<m ; ++j )
			if( A[j].getcode()<least.getcode() )
				pos=j,least=A[j];
		t=A[i],A[i]=A[pos],A[pos]=t;
	}
}

void load()                     	//Loading Screen
{
	int i=0,j=0;
	gotoxy(25,13);
	cout<<"Loading";
	gotoxy(31,15);
	cout<<"±±±±±±±±±±";
	for(j=1 ; j<11 ; ++j)
	{
		for(i=0 ; i<3 ; ++i)
		{
			gotoxy(32+i,13);
			cout<<".";
		       	delay(200);
		}
		gotoxy(32,13);
		cout<<"   ";
		gotoxy(30+j,15);
		cout<<"²";
		delay(300);
	}
	cout<<"\n\nPress any key to continue";
	getch();
	clrscr();
}

void home()                             //Home Delivery Portal
{
	int i=0;
	order o[50];
	char ch;
	food fd;
	customer c;
	fstream f,f1;
	f.open("ORDERCUS.txt",ios::app|ios::binary);
	cout<<endl<<"\tYou have chosen Home Delivery!"<<endl
	<<"\t24 Hours Service Available to You"<<endl<<endl;
	c.get_name();
	cout<<"\n   Hi! ";
	c.disp_name();
	gotoxy(1,24);
	cout<<"					Press ENTER to see the Menu ";
	getch();
	masterread();
	gotoxy(1,24);
	cout<<"				Press ENTER to go to the selection screen ";
	getch();
	clrscr();
	cout<<"\n Please Enter Your Order (Enter 0 in code to Terminate) : "<<endl<<endl;
	do
	{
		o[i].get_order();
		++i;
	}while(o[i-1].getcode()!=0);
	--i;
	c.assign(i);
	f1.open("MASTER.txt",ios::in|ios::binary);
	do
	{
		Sort_order(o,i);        		//To Sort the Order of Codes given by the User\
		int j=0;
		while(f1.read((char*)&fd,sizeof(fd)))		//to get objects from master file
		{
			if( o[j].getcode()==fd.getcode() )
			{	o[j].assign(fd);
				++j;
			}
		}
		c.or_cpy(o,i);
		clrscr();
		cout<<"\n\n Your Order is : ";
		for( int n=0 ; n<i ; ++n )
			o[n].disp_order();
		c.calc_bill(o);
		cout<<"\n\n Do you want to Place your order (Y or N) ? ";
		cin>>ch;
		if (ch=='Y'||ch=='y')
		{
			c.get_add_mob();
			f.write((char*)&c,sizeof(c));
			cout<<"\n\n  Order Placed"<<endl;
			delay(2000);
			cout<<"  Order Packed"<<endl;
			delay(2000);
			cout<<"  Out For Delivery"<<endl;
			delay(2000);
			cout<<"  Order Delivered! Bon Apetite!"<<endl<<endl;
			cout<<"\n Thank You! Hope You enjoyed your service "<<endl<<endl;
			drawline();
			getch();
			break;
		}
	}while( ch=='Y'|| ch=='y' );
	f.close();
}

void masterupdate()                 //To Update the Price of an item
{
	fstream file("MASTER.txt",ios::in|ios::binary);
	fstream nfile("nMASTER.txt",ios::out|ios::binary);
	int code,found=0;
	food f;
	cout<<"Enter the Code to be updated: ";
	cin>>code;
	while(file.read((char*)&f,sizeof(f)))
	{
		if(f.getcode()==code)
		{
			float fl;
			f.show();
			cout<<endl<<endl<<"Enter the New Price: ";
			cin>>fl;
			f.cprice(fl);
			cout<<"\nUpdated";
			found=1;
		}
		nfile.write((char*)&f,sizeof(f));
	}
	if(found==0)
		cout<<"Code Not Found";
	file.close();
	nfile.close();
	remove("MASTER.txt");
	rename("nMASTER.txt","MASTER.txt");
}

void masterread()			//To Read from file and display as a Menu
{

	clrscr();
	char ch;
	y1=top,y2=top;
	cout<<endl<<"\t\t\t\t\t ****"<<endl<<"\t\t\t\t\t*MENU*"<<endl<<"\t\t\t\t\t ****"<<endl<<endl;
	cout<<"		STARTERS                            MAIN COURSE"<<endl<<endl;
	cout<<" S.No."<<"    "<<"\tDISH";
	gotoxy(33,8);
	cout<<"PRICE";
	gotoxy(42,8);
	cout<<" S.No."<<"    "<<"\tDISH";
	gotoxy(73,8);
	cout<<"PRICE   "<<endl;
	fstream file("MASTER.txt",ios::in|ios::binary);
	food f;
	file.read((char*)&f,sizeof(f));
	while(f.getcode()<=40)
	{
		f.showf();
		cout<<endl;
		file.read((char*)&f,sizeof(f));
	}
	gotoxy(1,24);
	cout<<"						Press -> For Next Page";
	getch();
	ch=getch();
	if (ch==77)
	{
		clrscr();
		cout<<endl<<"\t\t\t\t\t ****"<<endl<<"\t\t\t\t\t*MENU*"<<endl<<"\t\t\t\t\t ****"<<endl<<endl;
		cout<<"		 BREADS                            DESSERTS"<<endl<<endl;
		cout<<" S.No."<<"    "<<"\tDISH";
		gotoxy(33,8);
		cout<<"PRICE";
		gotoxy(42,8);
		cout<<" S.No."<<"    "<<"\tDISH";
		gotoxy(73,8);
		cout<<"PRICE   "<<endl;
		y1=10;
		y2=10;
		while(!file.eof())
		{

			f.showf();
			cout<<endl;
			file.read((char*)&f,sizeof(f));
		}
	}
	file.close();
}

void masterwrite()      		//To Insert Data into File
{
	fstream file("MASTER.txt",ios::app|ios::binary);
	food f;
	char ch;
	do
	{
		f.getf();
		file.write((char*)&f,sizeof(f));
		cout<<"Do you want to Enter more data?: ";
		cin>>ch;
		if( f.getcode()<=20 )
			b1=b1+1;
		else if( f.getcode()<=40 )
			b2=b2+1;
		else if(f.getcode()<=50)
			b1=b1+1;
		mastersort();
	}while(ch=='Y'||ch=='y');
	file.close();
}

void masterdelete()                    	       //To Delete Data from the File
{
	fstream file("MASTER.txt",ios::in|ios::binary);
	fstream nfile("nMASTER.txt",ios::out|ios::binary);
	int code,found=0;
	food f;
	cout<<"Enter the Code to be deleted: ";
	cin>>code;
	while(file.read((char*)&f,sizeof(f)))
	{
		if(f.getcode()==code)
		{
			cout<<"\nDeleted";
			found=1;
		}
		else
			nfile.write((char*)&f,sizeof(f));
	}
	if(found==0)
		cout<<"Code Not Found";
	if( code<=20 )
		b1=b1-1;
	else if( code<=40 )
		b2=b2-1;
	file.close();
	nfile.close();
	remove("MASTER.txt");
	rename("nMASTER.txt","MASTER.txt");
}

void mastersort()    		//To Sort the Items in the File
{
	int i,pos,j,n;
	fstream file("MASTER.txt",ios::in|ios::binary);
	food f[100],least,t;
	for ( i=0 ; file.read((char*)&f[i],sizeof(f[i])) ; ++i );
	for ( n=0 ; n<i ; ++n )
	{
		least=f[n];
		pos=n;
		j=n+1;
		for ( ; j<i; ++j )
		{	if(f[j].getcode()<least.getcode())
			{
				pos=j;
				least=f[j];
			}
			t=f[n];
			f[n]=f[pos];
			f[pos]=t;
		}
	}
	file.close();
	file.open("MASTER.txt",ios::out|ios::binary);
	for ( n=0 ; n<i ; ++n )
		file.write((char*)&f[n],sizeof(f[n]));
	file.close();
}

void calc_sales()				//calculate total sales 
{
	customer t;
	int total_sales=0;
	fstream f("ORDERCUS.txt",ios::in|ios::binary);
	while(f.read((char*)&t,sizeof(t)))
	{
		total_sales+=t.ret_bill();
	}
	cout<<endl<<" Total sales is "<<total_sales<<endl<<endl;
	f.close();
}

void display()					//show details of customer using mobile no
{
	fstream f;
	f.open("ORDERCUS.txt",ios::in|ios::binary);
	customer c;
	char mob[12];
	cout<<" Enter mobile number of customer : ";
	cin>>mob;
	while(f.read((char*)&c,sizeof(c)))
	{
		if( strcmp(mob,c.ret_mob())==0 )
			c.show_cus();
	}
	getch();
	f.close();
}

void main()
{
	int o,i;
	clrscr();
	load();
	do
	{
		clrscr();
		cout<<" \t\t\t\tFood On Wheels"<<endl
		<<" \t\t\t Delivering Food Hot and Spicy!..."<<endl
		<<" Welcome! What would you like to do?"<<endl
		<<" 1. Show Menu"<<endl
		<<" 2. Delivery To Home"<<endl
		<<" 3. ONLY FOR STAFF"<<endl
		<<" Enter any other key to Exit...."<<endl<<endl;
		drawline();
		cout<<endl<<" Enter Your Choice: ";
		cin>>o;
		switch(o)
		{

			case 1: masterread();
				gotoxy(1,24);
				cout<<"				      Press ENTER to return to Main Menu ";
				break;

			case 2: home();
				break;

			case 3: char pass[5];
				cout<<"Enter Password: ";
				for( i=0 ; i<5 ; ++i )
				{
					pass[i]=getch();
					cout<<'*';
				}
				cout<<endl;
				getch();
				if(strcmp(pass,"Mandy")==0)
				{
					int t;
					do
					{
						clrscr();
						cout<<" Welcome to the staff screen"<<endl<<endl;
						cout<<" 1. Add item to the Menu"<<endl
						<<" 2. Delete an item from the Menu"<<endl
						<<" 3. Update price of an item "<<endl
						<<" 4. Show Total Sales"<<endl
						<<" 5. Show Customer details"<<endl
						<<" 6. Exit to Main Menu"<<endl<<endl;
						cout<<" Enter your choice : ";
						cin>>t;
						switch(t)
						{
							case 1: masterwrite();
								mastersort();
								break;
							case 2:	masterdelete();
								getch();
								break;
							case 3: masterupdate();
								getch();
								break;
							case 4: calc_sales();
								getch();
								break;
							case 5: display();
								break;
							case 6: break;
							default:cout<<" WRONG INPUT"<<endl<<endl;
						}
					}while(t!=6);
				}
				else
					cout<<endl<<"Incorrect Password"<<endl;
				break;
			default:cout<<"Thank You for joining in!";
				getch();
				exit(0);

		}
		getch();
	}while(1);
}
