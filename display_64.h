#pragma once

class dis // Class That Holds All the Constants 
{
	typedef const unsigned __int8 const_8;
	typedef const unsigned __int64 const_64;
	typedef const char constchar;

	//				   n
	// HIGHEST USED (2) value
	static const_64 maxvalue =	10000; // Maximum Used Integer Value In The Classes as Constant

public:
	// TEXT COLOR (IN ASSOCIATION WITH TERMCOLOR.HPP)
	static const_8 grey =		0x01;
	static const_8 red =		0x02;
	static const_8 green =		0x03;
	static const_8 yellow =		0x04;
	static const_8 blue =		0x05;
	static const_8 magenta =	0x06;
	static const_8 cyan =		0x07;
	static const_8 white =		0x08;

	// BACKGROUND COLOR (Same As Above, EXCEPT left shifted by 4 bits)
	static const_8 ongrey =		0x10;
	static const_8 onred =		0x20;
	static const_8 ongreen =	0x30;
	static const_8 onyellow = 	0x40;
	static const_8 onblue =		0x50;
	static const_8 onmagenta =	0x60;
	static const_8 oncyan =		0x70;
	static const_8 onwhite =	0x80;

	// DEFAULT VALUES USED
	static constchar def_emptyScreen =	' ';
	static constchar def_wall =			'.';

	// SETTING PREFERENCES
	static const_64 former =		0x00001;	// Previously used Settings will be used without any new changes
												// (first call results in default in this case) */
	static const_64 temp =			0x00002;	// The settings used will not be saved in history as last used

	static const_64 color =			0x00004;	// Color display will be used
	static const_64 content =		0x00008;	// Contents were made or used

	static const_64 copy;		// Copies content from one to another
	static const_64 cut;		// Cuts content from the former to latter


	static const_64 space =			0x00010;	// space*number gives the spaces to be left at the beginning (max 31)
	static const_64 h_mirror =		0x00200;	// Mirrors the screen Horizontally
	static const_64 v_mirror =		0x00400;	// Mirrors the screen Vertically
	static const_64 clear =			0x00800;	// Clears the screen according to the other settings
	

	static const_64 u_wall =		0x01000;	// Upper Wall
	static const_64 d_wall =		0x02000;	// Lower Wall
	static const_64 l_wall =		0x04000;	// Left-side Wall
	static const_64 r_wall =		0x08000;	// Right-side Wall
	static const_64 c_wall =		0x10000;	// Corner Walls
	static const_64 all_wall =		0x1F000;	// All walls will be used


	// DEFAULT SETTING PREFERENCES
	// CLASS SCREEN
	static const_64 def_screen = content|clear;


};

class screen
{
	unsigned __int64 setting;					// Retains the setting information related to the class
	//unsigned __int64 show_setting;				// Retains the setting information used to call cchow function

protected:
	char* m;									// Points to the matrix with the contents to be displayed
	char* c;									// Points to the matrix that controls the color of each printed character
	short height, width;						// The width and height of the entire matrix (width without accounting '\0')
	short st_x, st_y, end_x, end_y;				// The co-ordinates of the total workable area in the whole matrix



	// THE DEFAULT SPECIAL CHARACTERS TO BE USED
	char emptyScreen;							// Screen-Area with no contents (Default space)
	char u_wall;								//  Upper Partition Wall
	char r_wall;								//  Right Partition Wall
	char d_wall;								//  Lower Partition Wall
	char l_wall;								//   Left Partition Wall
	char c_wall;								// Corner Partition Wall

public:
	// CONSTRUCTORS
	screen(short/*width*/, short/*height*/, unsigned int = dis::def_screen/*settings (default value = def_screen)*/);		// Creates a new matrix dynamically
	screen(char*, int, int, int = dis::def_screen);				// Takes the matrix from the user
	screen(char*, char*, int, int, int = dis::def_screen);		// Takes both matrices from the user
	screen(screen& original, int = dis::def_screen);
	~screen();

};

screen::screen(short w, short h, unsigned int s)
{
	height = h;
	width = w;

	if (s & dis::temp)
		setting = dis::def_screen;
	else
		setting = s;

	if (s & dis::l_wall)
	{
		l_wall = dis::def_wall;
		st_x = 2;
	}
	else
	{
		l_wall = dis::def_emptyScreen;
		st_x = 0;
	}

	if (s & dis::u_wall)
	{
		u_wall = dis::def_wall;
		st_y = 2;
	}
	else
	{
		u_wall = dis::def_emptyScreen;
		st_y = 0;
	}

	if (s & dis::r_wall)
	{
		r_wall = dis::def_wall;
		end_x = width - 3;
	}
	else
	{
		r_wall = dis::def_emptyScreen;
		end_x = width - 1;
	}

	if (s & dis::d_wall)
	{
		d_wall = dis::def_wall;
		end_y = height - 3;
	}
	else
	{
		d_wall = dis::def_emptyScreen;
		end_y = height - 1;
	}

	if (s & dis::all_wall)
		c_wall = dis::def_wall;

	emptyScreen = dis::def_emptyScreen;


	if (s & dis::content)
		m = new char[((__int64)h * w + 1)];
	else
		m = 0;

	if (s & dis::color)
		c = new char[((__int64)h*w + 1)];
	else
		c = 0;

	if (m)
		setting |= dis::content;
	if (c)
		setting |= dis::color;
}

screen::screen(char* matrix, int w, int h, int s)
{
	height = h;
	width = w;

	if (s & dis::temp)
		setting = dis::def_screen;
	else
		setting = s;

	st_x = st_y = 2;
	end_x = width - 3;
	end_y = height - 3;

	if (s & dis::l_wall)
	{
		l_wall = dis::def_wall;
		st_x = 2;
	}
	else
	{
		l_wall = dis::def_emptyScreen;
		st_x = 0;
	}

	if (s & dis::u_wall)
	{
		u_wall = dis::def_wall;
		st_y = 2;
	}
	else
	{
		u_wall = dis::def_emptyScreen;
		st_y = 0;
	}

	if (s & dis::r_wall)
	{
		r_wall = dis::def_wall;
		end_x = width - 3;
	}
	else
	{
		r_wall = dis::def_emptyScreen;
		end_x = width - 1;
	}

	if (s & dis::d_wall)
	{
		d_wall = dis::def_wall;
		end_y = height - 3;
	}
	else
	{
		d_wall = dis::def_emptyScreen;
		end_y = height - 1;
	}

	if (s & dis::all_wall)
		c_wall = dis::def_wall;

	emptyScreen = dis::def_emptyScreen;

	if (s & dis::content && !(s & dis::color))
	{
		m = matrix;
		if (s & dis::color)
			c = new char[((__int64)h * w + 1)];
		else
			c = 0;
		if (c)
			setting |= dis::color;
	}
	else if (s & dis::color && !(s & dis::content))
	{
		c = matrix;
		m = new char[((__int64)h * w + 1)];
		if (m)
			setting |= dis::content;
	}
	else
		m = c = 0;
}

//screen::screen(char* Matrix, char* Color, int w, int h, int setting)
//{

//}

screen::~screen()
{
	if (setting & dis::content)
		delete []m;
	if (setting & dis::color)
		delete []c;
}