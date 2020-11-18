#include <fstream>
#include <string.h>
#include <conio.h>
#include "termcolor.hpp"

#pragma once

#define min(A, B) (A) < (B) ? (A) : (B)

void error(char* A) // Function To Display The Error Occured And Print it
{
	std::cout << A;
	exit(0);
}

double sum_array(int Ar[], int n = 1) // Function to get the sum of an array of integers
{
	double sum = 0;
	for (int i = 0; i < n; ++i)
		sum += Ar[i];
	return sum;
}

class dis // Class That Holds All the Constants 
{
	typedef const unsigned int constint;
	
//                    n
//HIGHEST POSSIBLE (2)	value
	static constint maxvalue = 10000; // Maximum Used Integer Value In The Classes as Constant
	
public:
	
//COLOR DISPLAY
	static constint nocolor		= 0x00;		// Black and White Display
	static constint color		= 0x01;		// Color Display (Display should be defined as color primarily)
	
//TEXT COLOR
	static constint grey		= 0x01;
	static constint red			= 0x02;
	static constint green		= 0x03;
	static constint yellow		= 0x04;
	static constint blue		= 0x05;
	static constint magenta		= 0x06;
	static constint cyan		= 0x07;
	static constint white		= 0x08;

//BACKGROUND COLOR (Same As Above, EXCEPT left shifted by 4 bits)
	static constint ongrey		= 0x10;
	static constint onred		= 0x20;
	static constint ongreen		= 0x30;
	static constint onyellow	= 0x40;
	static constint onblue		= 0x50;
	static constint onmagenta	= 0x60;
	static constint oncyan		= 0x70;
	static constint onwhite		= 0x80;
	
//SCREEN :: DISPLAY TYPE
	static constint clear 		= 2;		// Clears The command window before printing the next screen
	static constint tab 		= 4;		// Places a tab and shifts the sceen slightly to the right
//MENU :: DISPLAY
	static constint byline		= 8;		// Displays the byline message (if any)
	static constint footer		= 16;		// Displays the footer message (if any)
//SCREEN :: BASIC METHOD
	static constint heading		= 32;		// Displays the Heading of the program
	static constint up_wall		= 64;		// Displays the wall above
	static constint right_wall	= 128;		// Displays the wall right
	static constint down_wall	= 256;		// Displays the wall below
	static constint left_wall	= 512;		// Displays the wall left
	static constint corner_wall	= 1024;		// Displays the wall corner
	static constint all_wall	= up_wall|right_wall|down_wall|left_wall|corner_wall;

//INPUT_MENU DEFAULT
	static constint tentative	= 2048;		// Retains the input the user input for further use or editing by the user
	static constint former		= 4096;		// Uses the settings that were used previously while using the class
	static constint forget		= 0;		// Displays with a setting that is not saved in 'former setting'
	
	
//INPUT_MENU :: DATATYPE
	static constint text		= 0;
	static constint fake		= 1;
	static constint upperchar	= 2;
	static constint lowerchar	= 4;
	static constint digit		= 8;
	static constint space		= 16;
	static constint underscore	= 32;
	static constint special		= 64;
//INPUT_MENU :: DISPLAYTYPES
	static constint hide		= 128;
	static constint notnull		= 256;
	static constint defined		= 512;
//INPUT_MENU :: COLORTYPE TEXT
	static constint mintype		= 1024;
	static constint maxtype		= 2048;
//INPUT_MENU :: COLORTYPE UNDERSCORE
	static constint colortype	= 4096;
	
//INPUT_MENU :: SPECIAL CASES
	static constint character	= upperchar|lowerchar;
	static constint username	= 2858;
	static constint password	= 3054;
	static constint date		= 2136;
	static constint time		= 2124;
	static constint date_time	= 2142;
	static constint noun		= 2070;
	static constint currency	= 2122;
	
//BIT-WISE FUNCTIONS
	static unsigned int separate(unsigned int, unsigned int);	// Its Similar to intersection
	static unsigned int combine(unsigned int, unsigned int);	// Its Similar to union
	static unsigned int remove(unsigned int, unsigned int);		// From first, all thats in second is removed. (MINUS)
};

//SET INERSECTION
unsigned int dis::separate(unsigned int sub1, unsigned int sub2)
{
	unsigned int i = 1, ans = 0;
	for(; i <= maxvalue;i <<= 1)
		ans += ((sub1&i) && (sub2&i))*i;
	return ans;
}
//SET UNION
unsigned int dis::combine(unsigned int sub1, unsigned int sub2)
{
	unsigned int i = 1, ans = 0;
	for(;i <= maxvalue; i <<= 1)
		ans += ((sub1&i) || (sub2&i))*i;
	return ans;
}
//SET MINUS
unsigned int dis::remove(unsigned int main, unsigned int sub)
{
	unsigned int i = 1, ans = 0;
	for(;i <= maxvalue; i <<= 1)
		ans += ((main&i) && !(sub&i))*i;
	return ans;
}

class screen
{
	bool power;
	
protected:
	
	bool color;
	static unsigned int lastbasic;
	static unsigned int lastdisplay;
	static char lasthead;
	static char lastwall;
	
	char *prog_name;
	char height, width;
	char EmptyScreen;
	char Upwall;
	char Rightwall;
	char Downwall;
	char Leftwall;
	char Cornerwall;
	char *M;		//Display
	char *C;		//Color
	
public:
	
	screen(char, char, int = 0);
	~screen();
	void update(char, char, int = 0);
	
	void setscreen(char*, char = '.', char = '.', char = '.', char = '.', char = '.', char = ' ');
	void reset();
	void basic(int how = dis::former, char wall = 0, char head = 0);
	void display(int how = dis::former);
};

// INITIALISING 
unsigned int screen::lastbasic = dis::all_wall|dis::heading;
unsigned int screen::lastdisplay = dis::clear|dis::color;
char screen::lastwall = 0;
char screen::lasthead = 0;

screen::screen(char H, char W, int Col)
{
	height = H;
	width = W;
	
	prog_name = "HELLO WORLD";
	EmptyScreen = ' ';
	Upwall = '.';
	Rightwall = '.';
	Downwall = '.';
	Leftwall = '.';
	Cornerwall = '.';
	
	M = new char[(int)H*(int)W + 1];
	
	if(Col)
	{
		C = new char[(int)H*(int)W + 1];
		if(C == NULL)
			color = 0;
		else
			color = 1;
	}
	else
		color = 0;
	
	if(M == NULL)
		power = 0;
	else
		power = 1;
	reset();
}

screen::~screen()
{
	if(power)
		delete[]M;
	if(color)
		delete[]C;
}

void screen::setscreen(char *N, char U, char R, char D, char L, char C, char E)
{
	if(N)
		prog_name = N;
	EmptyScreen = E;
	Upwall = U;
	Rightwall = R;
	Downwall = D;
	Leftwall = L;
	Cornerwall = C;
}

void screen::update(char H, char W, int Col)
{
	height = H;
	width = W;
	if(power)
		delete[] M;
	if(color)
		delete[] C;
		
	M = new char[(int)H*(int)W + 1];
		
	if(Col)
	{
		C = new char[(int)H*(int)W + 1];
		if(C == NULL)
			color = 0;
		else
			color = 1;
	}
	else
		color = 0;
	
	if(M == NULL)
		power = 0;
	else
		power = 1;
}

void screen::reset()
{
	if(power)
	{
		for (int i = 0; i < height*width; ++i)
			M[i] = EmptyScreen;
		M[height*width] = '\0';
	}
	if(color)
	{
		for (int i = 0; i <= height*width; ++i)
			C[i] = 0;
		C[height*width] = '\0';
	}
}

void screen::basic(int how, char wall, char head)
{
	if(how&dis::former)
	{
		how = lastbasic;
		if(wall)
			lastwall = wall;
		else
			wall = lastwall;
		if(head)
			lasthead = head;
		else
			head = lasthead;
	}
	else
	{
		lastbasic = dis::separate(how, dis::all_wall|dis::heading);
		lasthead = head;
		lastwall = wall;
	}
	int i;
	
	if (how & dis::heading)
	{
		int headlen = strlen(prog_name);
		int pos_w = (width - headlen) / 2;
		if (pos_w < 0)
			error("low width");
		
		for (i = 0; i < headlen; ++i)
		{
			M[2*width + pos_w + i] = prog_name[i];
			
			if(color && head)
				C[2*width + pos_w + i] = head;
		}
	}
	
	if((how&dis::up_wall)||(how&dis::down_wall))
		for (i = 1; i < width-1; ++i)
		{
			if(how&dis::up_wall)
				M[i] = Upwall;
			if(how&dis::down_wall)
				M[height*width -i -1] = Downwall;
			if(color && wall)
			{
				if(how&dis::up_wall)
					C[i] = wall;
				if(how&dis::down_wall)
					C[height*width -i -1] = wall;
			}
		}
		
	if((how&dis::left_wall)||(how&dis::right_wall))
		for (i = 1; i < height-1; ++i)
		{
			if(how&dis::left_wall)
				M[i*width] = Leftwall;
			if(how&dis::right_wall)
				M[(i+1)*width -1] = Rightwall;
			if(color && wall)
			{
				if(how&dis::left_wall)
					C[i*width] = wall;
				if(how&dis::right_wall)
					C[(i+1)*width -1] = wall;
			}
		}
		
	if(how&dis::corner_wall)
	{
		M[0] = M[width - 1] = M[height*width -1] = M[(height-1)*width] = Cornerwall;
		if(color && wall)
			C[0] = C[width - 1] = C[height*width -1] = C[(height-1)*width] = wall;
	}
	else
		M[0] = M[width - 1] = M[height*width -1] = M[(height-1)*width] = EmptyScreen;
}

void screen::display(int how)
{
	if(how&dis::former)
		how = lastdisplay;
	else
		lastdisplay = dis::separate(how, dis::clear|dis::color|dis::tab);
	
	if(how&dis::clear)
		clrscr();
		
	if ((how & dis::color) && color && power)
	{
		for(int i = 0; i < height*width; ++i)
		{
			char tmpc = C[i];
			char tmpb = (tmpc >> 4);
			tmpc = C[i] - tmpb*16;
			
			if(i % width == 0)
			{
				std::cout << std::endl;
				if(how & dis::tab)
					std::cout << "\t";
			}
			std::cout << termcolor::reset;
			
			if(tmpc == dis::grey)
				std::cout << termcolor::grey;
			else if(tmpc == dis::red)
				std::cout << termcolor::red;
			else if(tmpc == dis::green)
				std::cout << termcolor::green;
			else if(tmpc == dis::yellow)
				std::cout << termcolor::yellow;
			else if(tmpc == dis::blue)
				std::cout << termcolor::blue;
			else if(tmpc == dis::magenta)
				std::cout << termcolor::magenta;
			else if(tmpc == dis::cyan)
				std::cout << termcolor::cyan;
			else if(tmpc == dis::white)
				std::cout << termcolor::white;
			
			if(tmpb == dis::grey)
				std::cout << termcolor::on_grey;
			else if(tmpb == dis::red)
				std::cout << termcolor::on_red;
			else if(tmpb == dis::green)
				std::cout << termcolor::on_green;
			else if(tmpb == dis::yellow)
				std::cout << termcolor::on_yellow;
			else if(tmpb == dis::blue)
				std::cout << termcolor::on_blue;
			else if(tmpb == dis::magenta)
				std::cout << termcolor::on_magenta;
			else if(tmpb == dis::cyan)
				std::cout << termcolor::on_cyan;
			else if(tmpb == dis::white)
				std::cout << termcolor::on_white;
			
			std::cout << M[i];
		}
	}
	else if(power)
	{
		for(int i = 0; i < height*width; ++i)
		{
			if(i % width == 0)
			{
				std::cout << std::endl;
				if(how & dis::tab)
					std::cout << "\t";
			}
			std::cout << M[i];
		}
	}
}


class menu : protected screen
{
	bool power;
	
protected:
	
	bool color;
	static unsigned int lastdisplay;
	char Max_Footer_No;
	char Max_List_No;
	
	char* Location;
	
	char Foot_no;
	char** Footer;
	char** FC;
	
	char List_no;
	char** List;
	char** LC;
	
public:
	
	menu(char, char, char, char, int = 0);
	~menu();
	
	void insert_byline(char* loc)
	{
		Location = loc;
	}
	void setscreen(char *N, char U = '.', char R = '.', char D = '.', char L = '.', char C = '.', char E = ' ')
	{
		screen::setscreen(N, U, R, D, L, C, E);
	}
	void insert_item(char*, char* = NULL);
	void insert_list(char*, char*, int, int, char* = NULL);
	void insert_footer(char*, char*, int, int);
	void display(int = dis::former, char = 0, char = 0, char = 0, char = 0);
};

unsigned int menu::lastdisplay = screen::lastbasic|screen::lastdisplay|dis::byline|dis::footer;

menu::menu(char maxlist, char maxfooter, char H, char W, int Col) : screen(H, W, Col)
{
	Footer = 0;
	List = 0;
	Foot_no = 0;
	List_no = 0;
	FC = 0;
	LC = 0;
		
	Max_List_No = maxlist;
	Max_Footer_No = maxfooter;
	
	if(Max_Footer_No && Max_List_No)
	{
		Footer = new char*[Max_Footer_No];
		List = new char*[Max_List_No];
			
		if(screen::color && Col)
		{
			FC = new char*[Max_Footer_No];
			LC = new char*[Max_List_No];
				
			if(FC && LC)
			{
					color = 1;
					int i;
					for(i = 0;i < Max_Footer_No; ++i)
						FC[i] = 0;
					for(i = 0;i < Max_List_No; ++i)
						LC[i] = 0;
			}
			else
			{
				color = 0;
				if(FC)
					delete[] FC;
				if(LC)
					delete[] LC;
			}
		}
		else
			color = 0;
	}
		
	if(Footer && List)
		power = 1;
	else
	{
		power = 0;
		if(List)
			delete[]List;
		if(Footer)
			delete[]Footer;
	}
}

menu::~menu()
{
	if(power)
	{
		delete[]List;
		delete[]Footer;
	}
	if(color)
	{
		delete[]FC;
		delete[]LC;
	}
}

void menu::insert_item(char *list, char *lc)
{
	if(power && (List_no < Max_List_No) && list)
	{
		List[List_no] = list;
		if(color && lc)
			LC[List_no] = lc;
		++List_no;
	}
}

void menu::insert_list(char *list, char *lc, int size, int n, char* loc)
{
	if(power && list)
	{
		int small = min(n, Max_List_No);
		for(int i = 0;i < small; ++i)
		{
			List[i] = list + (int)(i*size);
			if(color && lc)
				LC[i] = lc +(int)(i*size);
		}
		List_no = small;
		if(loc)
			Location = loc;
	}
}

void menu::insert_footer(char* footer, char *fc, int size, int n)
{
	if(power && footer)
	{
		int small = min(n, Max_Footer_No);
		for(int i = 0;i < small; ++i)
		{
			Footer[i] = footer + (int)(i*size);
			if(color && fc)
				FC[i] = fc +(int)(i*size);
		}
		Foot_no = small;
	}
}

void menu::display(int how, char avoid, char wall, char head, char loc)
{
	if(!power)
		return;
	
	if(avoid >= List_no)
		return;
	
	if(how&dis::former)
		how = lastdisplay;
	else
		lastdisplay = how;
	
	int i, j, k, pos_h;
	screen::reset();
	screen::basic(how,wall,head);
	
	List_no = min(List_no, Max_List_No);
	
	int spacing = (height - 11) / (List_no - avoid);
	
	if (spacing < 1)
		error("Not enough height");
	
	int notused = ((height - 11) - spacing*((List_no - avoid) - 1)) / 2;
	for (j = 0, pos_h = 5 + notused; List[j] && j < (List_no - avoid); ++j)
	{
		int str = strlen(List[j]);
		for (i = 0; i < str; ++i)
		{
			screen::M[(pos_h + (j*spacing))*screen::width + ((screen::width - str) / 2) + i] = List[j][i];
			if(color && (how & dis::color) && LC[j])
				screen::C[(pos_h + j*spacing)*screen::width + ((screen::width - str) / 2) + i] = LC[j][i];
		}
	}
	
	if(Location && (how & dis::byline))
	{
		int loc_len = strlen(Location);
		if (loc_len < screen::width - 4)
		{
			for (i = 0; i < loc_len; ++i)
			{
				screen::M[3*screen::width + 2 + i] = Location[i];
				if(screen::color && loc && (how & dis::color))
					screen::C[3*screen::width + 2 + i] = loc;
				else if(screen::color)
					screen::C[3*screen::width + 2 + i] = 0;
			}
		}
	}
	
	if (Foot_no && (how&dis::footer))
	{
		Foot_no = min(Foot_no, Max_Footer_No);
		
		int* str = new int[Foot_no + 1];
		for (i = 0, str[Foot_no] = 0; i < Foot_no; ++i)
		{
			str[i] = strlen(Footer[i]);
			str[Foot_no] += str[i];
		}
			
		spacing = (screen::width - str[Foot_no]) / (Foot_no + 1);
		
		if (spacing < 1)
			error("Not enough Width");
			
		for (k = 0;Footer[k] &&  k < Foot_no; ++k)
		{
			for (i = 0; i < str[k]; ++i)
			{
				screen::M[(height-3)*screen::width + 2 + ((k + 1) * spacing) + sum_array(str, k) + i] = Footer[k][i];
				if(color && FC[k] && (how & dis::color))
					screen::C[(height-3)*screen::width + 2 + ((k + 1) * spacing) + sum_array(str, k) + i] = FC[k][i];
				else if(screen::color)
					screen::C[(height-3)*screen::width + 2 + ((k + 1) * spacing) + sum_array(str, k) + i] = 0;
			}
		}
		delete []str;
	}
	screen::display(how);
}


class input_menu : protected menu
{	
	char power;
	
	void create();
	void join(int, int = 0, char = 0);
	
protected:
	
	static unsigned int lastprint;
	static unsigned int lastmessage;
	char color;
	char **list_save;
	char **col_save;
	unsigned int *datatype;
	unsigned int *maxlen;
	unsigned int *minlen;
	
public:
	
	char **input_data;
	
	input_menu(char, char, char, char, int = 0);
	~input_menu();
	
	void insert(char*, char*, char, unsigned int*, unsigned int*, unsigned int*, unsigned int);
	int print(int how = dis::former);
	int printlong(char*, char*, int, char* = NULL);
	void message(char*, int how = dis::former, char = 0);
};

unsigned int input_menu::lastprint = menu::lastdisplay;
unsigned int input_menu::lastmessage = 0;

input_menu::input_menu(char maxlist, char maxfooter, char H, char W, int Col) : menu(maxlist, maxfooter, H, W, Col)
{
	color = 0;
	datatype = NULL;
	minlen = NULL;
	maxlen = NULL;
	
	if(maxlist && maxfooter)
	{
		list_save = new char*[maxlist];
		col_save = new char*[maxlist];
		input_data = new char*[maxlist];
	}
		
	if(list_save && input_data && col_save)
	{
		power = 1;
		int i;
		for(i = 0;i < Max_List_No; ++i)
			list_save[i] = col_save[i] = input_data[i] = 0;
	}
	else
	{
		power = 0;
		if(list_save)
			delete[]list_save;
		if(input_data)
			delete[]input_data;
		if(col_save)
			delete[]col_save;
	}
	create();
}	

input_menu::~input_menu()
{
	int i;
	if(power & 1)
	{
		if(power & 8)
			for(i = 0; i < menu::Max_List_No; ++i)
				delete []input_data[i];
		delete[]input_data;
		
		if(power & 4)
			for(i = 0; i < menu::Max_List_No; ++i)
				delete []menu::List[i];
		
		if(power & 2)
			for(i = 0; i < menu::Max_Footer_No; ++i)
				delete []menu::Footer[i];
		
		delete[]list_save;
		delete[]col_save;
	}
	
	if(color & 2)
			for(i = 0; i < menu::Max_List_No; ++i)
				delete []menu::LC[i];
		
	if(color & 1)
		for(i = 0; i < menu::Max_Footer_No; ++i)
			delete []menu::FC[i];
}

void input_menu::create()
{
	if(!power)
		return;
	
	int j;
	
	bool footer = 1;
	for(j = 0; (j < menu::Max_Footer_No) && footer && !(power&2); ++j)
	{
		menu::Footer[j] = new char[min(31, screen::width/2)];
		
		if(menu::Footer[j] == NULL)
			footer = 0;
		else
			menu::Footer[j][0] = '\0';
	}
	if(!footer)
		for(--j; j >= 0;--j)
			delete[]menu::Footer[j];
	else if(!(power&2))
		power += 2;
		
	bool lister = 1;
	for(j = 0; (j < menu::Max_List_No) && lister && !(power&4); ++j)
	{
		menu::List[j] = new char[screen::width - 3];
		
		if(menu::List[j] == NULL)
			footer = 0;
		else
			menu::List[j][0] = '\0';
	}
	if(!lister)
		for(j--;j >= 0;j--)
			delete[]menu::List[j];
	else if(!(power&4))
		power += 4;
	
	bool saver = 1;
	for(j = 0; (j < menu::Max_List_No) && saver && !(power&8); ++j)
	{
		input_data[j] = new char[screen::width - 6];
		
		if(input_data[j] == NULL)
			saver = 0;
		else
			input_data[j][0] = '\0';
	}
	if(!saver)
		for(j--;j >= 0;j--)
			delete[]input_data[j];
	else if(!(power&8))
		power += 8;
	
	if(!menu::color)
		return;
	
	footer = 1;
	for(j = 0; (j < menu::Max_Footer_No) && footer && !(color&1); ++j)
	{
		menu::FC[j] = new char[min(31, screen::width/2)];
		
		if(menu::FC[j] == NULL)
			footer = 0;
		else
			menu::FC[j][0] = '\0';
	}
	if(!footer)
		for(--j; j >= 0;--j)
			delete[]menu::FC[j];
	else if(!(color&1))
		color += 1;
		
	lister = 1;
	for(j = 0; (j < menu::Max_List_No) && lister && !(color&2); ++j)
	{
		menu::LC[j] = new char[screen::width - 3];
		
		if(menu::LC[j] == NULL)
			lister = 0;
		else
			menu::LC[j][0] = '\0';
	}
	if(!lister)
		for(j--;j >= 0;j--)
			delete[]menu::LC[j];
	else if(!(color&2))
		color += 2;
}

void input_menu::join(int workno, int len, char type)
{
	int temp_no1, temp_no2, i;
	
	strcpy(menu::List[workno], list_save[workno]);
	if(color && col_save[workno])
		strcpy(LC[workno], col_save[workno]);
	else if(color)
	{
		int length = strlen(list_save[workno]);
		for(i = 0; i < length; ++i)
			LC[workno][i] = 9;
		LC[workno][i] = 0;
	}
	
	if(datatype[workno] == 0)
		return;
	
	strcat_s(menu::List[workno], sizeof(menu::List[workno]), " : ");
	{
		char tmp[] = {9,9,9};
		if(color)
			strcat_s(LC[workno], sizeof(LC[workno]), tmp);
	}
	
	temp_no1 = (maxlen[workno] - len) / 2;
	temp_no2 = maxlen[workno] - len - temp_no1;
		
	for (i = 0; i < temp_no1; ++i)
		strcat_s(menu::List[workno], sizeof(menu::List[workno]), "_");
	if(color && type)
	{
		char tmp[2] = {type, 0};
		for(i = 0; i < temp_no1; ++i)
			strcat_s(menu::LC[workno], sizeof(menu::LC[workno]), tmp);
	}
	else if(color)
	{
		char tmp[2] = {9, 0};
		for(i = 0; i < temp_no1; ++i)
			strcat_s(menu::LC[workno], sizeof(menu::LC[workno]), tmp);
	}
	
	if (datatype[workno] & dis::hide)
		for (i = 0; i < len; ++i)
			strcat_s(menu::List[workno], sizeof(menu::List[workno]), "*");
	else if(len)
		strcat_s(menu::List[workno], sizeof(menu::List[workno]), input_data[workno]);
	if(color)
	{
		if(minlen && (datatype[workno]&dis::mintype) && !(datatype[workno]&dis::maxtype))
		{
			if(len < minlen[workno])
			{
				char tmp[2] = {(char)dis::red, 0};
				for (i = 0; i < len; ++i)
					strcat_s(menu::LC[workno], sizeof(menu::LC[workno]), tmp);
			}
			else if(len == minlen[workno])
			{
				char tmp[2] = {(char)dis::yellow, 0};
				for (i = 0; i < len; ++i)
					strcat_s(menu::LC[workno], sizeof(menu::LC[workno]), tmp);
			}
			else if(len > minlen[workno])
			{
				char tmp[2] = {(char)dis::green, 0};
				for (i = 0; i < len; ++i)
					strcat_s(menu::LC[workno], sizeof(menu::LC[workno]), tmp);
			}
		}
		else if(maxlen && !(datatype[workno]&dis::mintype) && (datatype[workno]&dis::maxtype))
		{
			if(len < (maxlen[workno])/4)
			{
				char tmp[2] = {(char)dis::red, 0};
				for (i = 0; i < len; ++i)
					strcat_s(menu::LC[workno], sizeof(menu::LC[workno]), tmp);
			}
			else if(len < (maxlen[workno])/2)
			{
				char tmp[2] = {(char)dis::yellow, 0};
				for (i = 0; i < len; ++i)
					strcat_s(menu::LC[workno], sizeof(menu::LC[workno]), tmp);
			}
			else if(len < (int)((maxlen[workno])*(0.75)))
			{
				char tmp[2] = {(char)dis::blue, 0};
				for (i = 0; i < len; ++i)
					strcat_s(menu::LC[workno], sizeof(menu::LC[workno]), tmp);
			}
			else
			{
				char tmp[2] = {(char)dis::green, 0};
				for (i = 0; i < len; ++i)
					strcat_s(menu::LC[workno], sizeof(menu::LC[workno]), tmp);
			}
		}
		else
		{
			char tmp[2] = {9, 0};
				for (i = 0; i < len; ++i)
					strcat_s(menu::LC[workno], sizeof(menu::LC[workno]), tmp);
		}
	}
	
	for (i = 0; i < temp_no2; ++i)
		strcat_s(menu::List[workno], sizeof(menu::List[workno]), "_");
	if(color && type)
	{
		char tmp[2] = {type, 0};
		for(i = 0; i <= temp_no1; ++i)
			strcat_s(menu::LC[workno], sizeof(menu::LC[workno]), tmp);
	}
	else if(color)
	{
		char tmp[2] = {9, 0};
		for(i = 0; i <= temp_no1; ++i)
			strcat_s(menu::LC[workno], sizeof(menu::LC[workno]), tmp);
	}
	
	strcat_s(menu::List[workno], sizeof(menu::List[workno]), ".");
	if(color)
	{
		char tmp[2] = {9, 0};
		strcat_s(menu::LC[workno], sizeof(menu::LC[workno]), tmp);
	}
}

void input_menu::message(char *content, int how, char des)
{
	if(!(power&2))
		return;
	
	if(how&dis::former)
		how = lastmessage;
	else
		lastmessage = dis::separate(how, dis::clear);
	
	bool once = 1;
	for(int i = 1; content[i-1] != '\0'; ++i)
	{
		if(once)
			once = i = 0;
		menu::Footer[(!(how&dis::clear))*(menu::Foot_no)][i] = content[i];
		
		if(des && color&1)
			menu::FC[(!(how&dis::clear))*(menu::Foot_no)][i] = des;
	}
	
	if(!(how&dis::clear) && menu::Foot_no < menu::Max_Footer_No)
		++(menu::Foot_no);
	else if(how&dis::clear)
		menu::Foot_no = 1;
		
	menu::display(dis::former);
}

void input_menu::insert(char *list, char *des, char size,unsigned int *type, unsigned int *lenmax, unsigned int *lenmin, unsigned int n)
{
	if(!power)
		return;
	
	int small = min(n, menu::Max_List_No);
	int j, i;
		
	for (j = 0; j < small; ++j)
	{
		list_save[j] = list + (int)(j*size);
		if(menu::color && des)
				col_save[j] = des + (int)(j*size);
	}
	datatype = type;
	maxlen = lenmax;
	minlen = lenmin;
	menu::List_no = small;
	menu::Location = 0;
}

int input_menu::print(int how)
{
	if((power&15) != 15)
		return -1;
	
	if(how&dis::former)
		how = lastprint;
	else
		lastprint = how;
	
	menu::Location = "Press ESC to Exit";
	
	int i = 0, j = 0, k = 0;
	int process = 0, workno = -1, len = 0;
	char letter[2];
	letter[1] = '\0';
	
	for (i = 0; i < menu::List_no; ++i)
	{
		if (datatype[i] != 0)
		{
			if(!(datatype[i]&1))
				++k;
		}
		else
			strcpy(input_data[i], "NO DATA");
		
		if(!(datatype[i]&dis::tentative))
		{
			strcpy(input_data[i], "");
			join(i, 0);
		}
		else
			join(i, strlen(input_data[i]));
	}
	menu::display(how, 0);
	
	while (k--)
	{
		process = 1;
		
		while (1)
		{
			++workno;
			if (datatype[workno] > 1)
				break;
		}
			
		strcpy(menu::Footer[0], "Input : ");
		strcat_s(menu::Footer[0], sizeof(menu::Footer[0]), list_save[workno]);
		menu::Foot_no = 1;
		
		if(color)
		{
			char tmp[] = {9,9,9,9,9,9,9,9};
			strcpy(FC[0], tmp);
			if(col_save[workno])
				strcat_s(FC[0], sizeof(FC[0]), col_save[workno]);
			else if(list_save[workno])
			{
				int length = strlen(list_save[workno]);
				char temp[] = {9};
				for(int z = 0; z < length; ++z)
					strcat_s(FC[0], sizeof(FC[0]), temp);
			}
		}
		menu::display(how);
		
		if(minlen)
			if(minlen[workno] > maxlen[workno])
				minlen[workno] = maxlen[workno];
		
		
		len = strlen(input_data[workno]);
		join(workno, len, dis::magenta);
		
		while (process)
		{
			
start_max_1:
			
			letter[0] = getch();
			
		switch (letter[0])
		{
	//CONTROL KEYS
		case '\n':
		case '\r':
			if(minlen)
			{
				if(len >= minlen[workno])
					process = 0;
				else
				{
					char tmp[16] = "MIN LENGTH ";
					int copy = minlen[workno];
					int digi, digit = 0;
					while (copy > 0)
					{
						digi = copy % 10;
						copy /= 10;
						tmp[digit + 11] = digi + 48;
	 					++digit;
					}
					tmp[digit + 11] = '\0';
					{
						for(int i = 0; i < (digit/2); ++i)
						{
							char tmp2;
							tmp2 = tmp[11 + i];
							tmp[11 + i] = tmp[11+ digit -1 -i];
							tmp[11 + digit -1 -i] = tmp2;
						}
					}
					message(tmp, dis::former, dis::red);
					--menu::Foot_no;
					goto start_max_1;
				}
			}
			else if(len == 0 && (datatype[workno]&dis::notnull))
			{
				message("NOT NULL", 0, dis::red);
					--menu::Foot_no;
				goto start_max_1;
			}
			else
				process = 0;
			break;
				
		case 27:
			return 0;
				
		case '\b':
		case 0:
			if(len > 0)
				input_data[workno][--len] = '\0';
			break;
			
	//DATA KEYS
		default	:
			if (len >= maxlen[workno])
				goto start_max_1;
			
			if(letter[0] >= 'A' && letter[0] <= 'Z')
			{
				if((datatype[workno]&dis::lowerchar) && !(datatype[workno]&dis::upperchar))
					letter[0] = tolower(letter[0]);
				else if(!(datatype[workno]&dis::character))
					goto start_max_1;
			}
			else if(letter[0] >= 'a' && letter[0] <= 'z')
			{
				if(!(datatype[workno]&dis::lowerchar) && (datatype[workno]&dis::upperchar))
					letter[0] = toupper(letter[0]);
				else if(!(datatype[workno]&dis::character))
					goto start_max_1;
			}
			else if(letter[0] >= '0' && letter[0] <= '9')
			{
				if(!(datatype[workno]&dis::digit))
					goto start_max_1;
			}
			else if(letter[0] = ' ')
			{
				if(!(datatype[workno]&dis::space))
					goto start_max_1;
			}
			else if(letter[0] = '_')
			{
				if(!(datatype[workno]&dis::underscore))
					goto start_max_1;
			}
			else if(!(datatype[workno]&(dis::special|dis::underscore)))
					goto start_max_1;
			
			strcat_s(input_data[workno], sizeof(input_data[workno]), letter);
			++len;
			break;
		};
		if(len)
			join(workno, len, dis::green);
		else
			join(workno, len, dis::red);
		
		menu::display(how);
		}
	}
	return 1;
};

int input_menu::printlong(char *answer, char *content, int Max_Len, char *def)
{
	if(!(power&1))
		return 0;
	
	int to_replace = menu::List_no;
	
	{
		int tempno = Max_Len / (screen::width - 10);
		int temprem = Max_Len - (tempno * (screen::width - 10));
		
		if(tempno > Max_List_No || (tempno == Max_List_No && temprem != 0))
			error("Exceeded Maximum Possible Lines");
		
		menu::List_no = tempno;
		if(temprem != 0)
			++menu::List_no;
		
		int x;
		
		for(x = 0; x < Max_List_No; ++x)
		{
			for(int y = 0; y < screen::width - 10; ++y)
				menu::List[x][y] = ' ';
			menu::List[x][screen::width - 10] = '\0';
		}
	}
	Location = "";
	strcpy(menu::Footer[0], "Input : ");
	strcat_s(menu::Footer[0], sizeof(menu::Footer[0]), content);
	menu::Foot_no = 1;
	
	char letter[2] = "";
	
	strcpy(answer, def);
	int len = strlen(answer);
	
	{
		int x;
		
		for(x = 0; x < len; ++x)
			menu::List[x / (screen::width - 10)][x % (screen::width - 10)] = answer[x];
		
		for(; x < Max_Len; ++x)
			menu::List[x / (screen::width - 10)][x % (screen::width - 10)] = '_';
		
		menu::display(1);
	}
	
	while(1)
	{
start_long_input:
	
		letter[0] = _getch();
	
		len = strlen(answer);
	
		switch (letter[0])
		{
		case '\n':
		case '\r':
			menu::List_no = to_replace;
			return 1;
		
		case 27:
			answer = def;
			menu::List_no = to_replace;
			return 0;
		
		case '\b':
		case 0:
			if(len != 0)
			{
				answer[len - 1] = '\0';
				--len;
			}
			break;
		
		default	:
			if (len >= Max_Len)
				goto start_long_input;
		
			strcat_s(answer, sizeof(answer), letter);
			++len;
			break;
		};
	
		{
			int x;
		
			for(x = 0; x < len; ++x)
				menu::List[x / (screen::width - 10)][x % (screen::width - 10)] = answer[x];
		
			for(; x < Max_Len; ++x)
				menu::List[x / (screen::width - 10)][x % (screen::width - 10)] = '_';
		
			menu::display(1);
		}
	}
}

class text_menu : protected screen
{
protected:
	
	int x, y;
	int start_x, last_x;
	int start_y, last_y;
	
	void initiate()
	{
		start_x = 2;
		start_y = 5;
		
		last_x = screen::width - 3;
		last_y = screen::height - 5;
		
		x = start_x;
		y = start_y;
		
		screen::reset();
		screen::basic();
	}
	
public:
	
	text_menu(char H, char W, int x = 0) : screen(H, W, x)
	{
		
	}
	
	int print(char*);
};

int text_menu::print(char *Loc)
{
	initiate();
	
	std::ifstream reader(Loc);
	
	if(reader.fail())
	{
			reader.close();
			return 0;
	}
	
	char ch;
	
	while(!reader.eof())
	{
		reader.get(ch);
		
		if(ch == '\n')
		{
			++y;
			x = start_x;
			continue;
		}
		
		if(ch == '\t')
			ch = ' ';
		
		if(y > last_y)
		{
			{
				int i, k;
				
				char Footer[][20] = 
				{
					"Any Key To Continue",
						"ESC To Exit"
				};
				int Foot_no = 2;
				
				int str[3];
				
				for (i = 0, str[Foot_no] = 0; i < Foot_no; ++i)
				{
					str[i] = strlen(Footer[i]);
					str[Foot_no] += str[i];
				}
				
				int spacing = (width - str[Foot_no]) / (Foot_no + 1);
				
				if (spacing < 1)
					error("Not Enough Width");
				
				for (k = 0; k < Foot_no; ++k)
					for (i = 0; i < str[k]; ++i)
						screen::M[(int)((screen::height - 3)*screen::width + 2 + ((k + 1) * spacing) + sum_array(str, k) + i)] = Footer[k][i];
			}
			
			screen::display();
			char what = _getch();
			
			if(what == 27)
			{
				reader.close();
				return 0;
			}
			else
				initiate();
		}
		
		if(x > last_x)
		{
			++y;
			x = start_x;
		}
		
		screen::M[y*screen::width + x] = ch;
		++x;
	}
	
	reader.close();
	screen::display();
	return 1;
}
