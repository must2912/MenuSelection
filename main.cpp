// Menu example for tjnapster
#include <iostream>
#include <conio.h>
#include <windows.h>
#include <cstdlib>
#include <dirent.h>
#include <sys/types.h>
#include <algorithm> //for replace
#include <string>
#include <vector>

using namespace std;

HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE); // used for goto
COORD CursorPosition; // used for goto

void gotoXY(int,int); // function defined below if this is new to you.

string dloc; //document location
int menu_item = 1,uicf = 0,terakhir = 0;//user input choosed file
vector <string> nama_folder;

void rso() //replace slashes operation
{
    string old("\\"), rep("\\\\");
    for (unsigned int pos=0; (pos = dloc.find(old, pos)) != std::string::npos;  pos+=rep.length())
    {
        dloc.replace(pos, old.length(), rep);
    }
}

int cdo(string fn) //c dot operation (find the dot operation)
{
    bool wdon;
    int dcv = 0;

    char searchItem = '.';
    int length = fn.size();

    for(int  i = 0;i < length;i++)
    {
        if(fn[i] == searchItem){dcv++;}
    }
    if(dcv >= 1){wdon=true;} //it has
    else{wdon=false;} //it does not

    return wdon; //true or false
} //tell if the file has or not an dot in it


void mfo(string dloc, int opt) //many functions operation
{
    DIR *dir;
    struct dirent *ent;
    int fin = 0, y = 6;


    if ((dir = opendir (dloc.c_str())) != NULL)
    {
        while ((ent = readdir (dir)) != NULL)
        {
            if(opt == 0) //showing the files and folders in an directory
            {
                gotoXY(18,7);
                cout << "->";

                nama_folder.clear();
                y++;
                gotoXY(20,y);
                terakhir = y;
                nama_folder.push_back(ent->d_name);
                fin++;
                cout<<ent->d_name<<endl;
            }
            else if(opt == 1) //entering to an user inputed file or folder
            {
                fin++;
                if(fin == menu_item)
                {
                    bool ssc;
                    dloc += ent->d_name;
                    if(cdo(ent->d_name) == false){ssc=true; dloc+= "\\\\";} //an folder
                    if(ssc != true){system(dloc.c_str());} //an file

                    system("cls");
                    rso(); //replace slashes
                    mfo(dloc, 0); //show files again in the new folder
                }
            }
        }
        closedir (dir);
    }
    else
    {
        cout<<"ERROR!"<<endl;
    }
}

void startMenuListener(int menu_item){

    switch(menu_item){

            case 1: {

                dloc = "c:";
                gotoXY(20,6);
                cout << "direktori C";
                rso(); //Replace slashes
                mfo(dloc, 0); //Show the files and folder in the user inputed directory
                break;
            }

            case 2: {
                dloc = "d:";
                gotoXY(20,6);
                cout << "direktori D";
                rso(); //Replace slashes
                mfo(dloc, 0); //Show the files and folder in the user inputed directory
                break;
            }

            case 3: {
                gotoXY(20,16);
                cout << "Buka F     ";
                break;
            }

            case 4: {
                gotoXY(20,16);
                cout << "Buka G     ";
                break;
            }

            case 5: {
                gotoXY(20,16);
                cout << "Program Ditutup!!";
                //running = false;
            }
        }
}

void showMenuAwal(){
    terakhir = 11;
    gotoXY(20,7);  cout << "1) C";
    gotoXY(20,8);  cout << "2) D";
    gotoXY(20,9);  cout << "3) E";
    gotoXY(20,10); cout << "4) F";
    gotoXY(20,11); cout << "Keluar Dari Program";
}

void foldermenuListener(){
    mfo(dloc, 1);
}

void bikinFolder(string nama){
    int check;
    string slash;
    string campur;
	const char *pathanddir;
	campur = dloc + slash + nama;
    pathanddir = campur.c_str();
    check = mkdir(pathanddir); //bikin folder
//    check = rmdir(pathanddir); //hapus folder

    // check if directory is created or not
    if (!check) {
        gotoXY(10,7);
        terakhir++;
        mfo(dloc,0);
    } else {
        gotoXY(10,7);
        cout << "Gagal buat folder";
    }
}

void deletefolder(){
    int check;
    string slash;
    string campur;
	const char *pathanddir;

	campur = dloc + slash + nama_folder[menu_item-1];
    pathanddir = campur.c_str();
    check = rmdir(pathanddir); //bikin folder
//    check = rmdir(pathanddir); //hapus folder

    // check if directory is created or not
    if (!check) {
        gotoXY(10,7);
        cout << "Berhasil delete folder";
    } else {
        gotoXY(10,7);
        cout << "Gagal delete folder";
    }
}

void kembali(){
    int terakhir = dloc.size() - 1;
    dloc = dloc.substr(0,dloc.find("/",0));

    cout << dloc;

    if(dloc.size() == 3){
        showMenuAwal();
    } else {
        mfo(dloc,1);
    }
}

int main()
{
	int run, x=7, state = 1;
	bool running = true;
	string nama;

	gotoXY(18,5); cout << "Main Menu";
	gotoXY(18,7); cout << "->";


	while(running)
	{
	    //system("cls"); //delete screen
        if(state == 1){
            showMenuAwal();
        }

//        getline(cin, dloc); //user input the location

		system("pause>nul"); // the >nul bit causes it the print no message

		if(GetAsyncKeyState(VK_DOWN) && x != terakhir) //down button pressed
			{
				gotoXY(18,x); cout << "  ";
				x++;
				gotoXY(18,x); cout << "->";
				menu_item++;
				continue;

			}

        if(GetAsyncKeyState(0x4E)) //down button pressed
			{
                system("cls");
                cout << "Masukkan Nama Folder : ";
                cin >> nama;
                bikinFolder(nama);
			}

        if(GetAsyncKeyState(0x44)) //down button pressed
			{
                system("cls");
                deletefolder();
			}

		if(GetAsyncKeyState(VK_UP) && x != 7) //up button pressed
			{
				gotoXY(18,x); cout << "  ";
				x--;
				gotoXY(18,x); cout << "->";
				menu_item--;
				continue;
			}

        if(GetAsyncKeyState(VK_BACK)) //up button pressed
			{
				kembali();
			}

		if(GetAsyncKeyState(VK_RETURN)){ // Enter key pressed
            system("cls");
            if(state == 1){
                state = 2;
                startMenuListener(menu_item);
            } else {
                state = 3;
                foldermenuListener();
            }
		}

	}

	gotoXY(20,21);
	return 0;
}

void gotoXY(int x, int y)
{
	CursorPosition.X = x;
	CursorPosition.Y = y;
	SetConsoleCursorPosition(console,CursorPosition);
}

