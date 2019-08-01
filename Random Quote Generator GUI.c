#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define IDB_BUT 1001
#define IDC_LISTBOX_TEXT 1000

int quote_number = 5;
const char g_szClassName[] = "myWindowClass";
char quote_random[500] = "Waiting For Quote.";
char genre_set[][20] = {"Books", "Inspiration", "Knowledge", "Life", "Love", "Random","Relationship", "Science", "Success"};

HWND title_Project, random_quote_button, quote, genre, hwndList;

void getQuote(int choice);

// Step 4: the Window Procedure
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch(msg)
	{
        case WM_CREATE:
            title_Project = CreateWindow("STATIC", 
                                "Random Quote Generator",
                                WS_VISIBLE | WS_CHILD,
                                115, 20, 170, 20, hwnd, 
                                NULL, NULL, NULL);
                                    
            quote = CreateWindow("STATIC", 
                                "",
                                WS_VISIBLE | WS_CHILD | WS_BORDER | WS_VSCROLL | WS_HSCROLL,
                                45, 150, 300, 150, hwnd, 
                                NULL, NULL, NULL);

            genre =  CreateWindow("LISTBOX", NULL,
                                WS_CHILD | WS_VISIBLE | LBS_STANDARD | WS_BORDER | LBS_NOTIFY , 
                                125, 60, 150, 80, 
                                hwnd, (HMENU) IDC_LISTBOX_TEXT, 
                                (HINSTANCE) GetWindowLong(hwnd, GWLP_HINSTANCE), NULL);
                                
            SendMessage(genre, LB_ADDSTRING, 0, (LPARAM)"Books");
            SendMessage(genre, LB_ADDSTRING, 0, (LPARAM)"Inspiration");
            SendMessage(genre, LB_ADDSTRING, 0, (LPARAM)"Knowledge");
            SendMessage(genre, LB_ADDSTRING, 0, (LPARAM)"Life");
            SendMessage(genre, LB_ADDSTRING, 0, (LPARAM)"Love");
            SendMessage(genre, LB_ADDSTRING, 0, (LPARAM)"Random");
            SendMessage(genre, LB_ADDSTRING, 0, (LPARAM)"Relationship");
            SendMessage(genre, LB_ADDSTRING, 0, (LPARAM)"Science");
            SendMessage(genre, LB_ADDSTRING, 0, (LPARAM)"Success");
            
            random_quote_button = CreateWindow("BUTTON", 
                                "Generate Quote",
                                WS_VISIBLE | WS_CHILD,
                                125, 320, 150, 20, hwnd, 
                                NULL, (HMENU) IDB_BUT, NULL);
            break;
        case WM_COMMAND:
        {
            switch(LOWORD(wParam))
            {
                case BN_CLICKED:
                {
                    MessageBeep(MB_ICONINFORMATION);
                    
                    getQuote(quote_number);
                    quote = CreateWindow("STATIC", 
                                    quote_random ,
                                    WS_VISIBLE | WS_CHILD | WS_BORDER | WS_VSCROLL | WS_HSCROLL,
                                    45, 150, 300, 150, hwnd, 
                                    NULL, NULL, NULL);
                    memset(quote_random, 0, 500);
                }
                break;
                
                case IDC_LISTBOX_TEXT:
                {
                    switch(HIWORD(wParam))
                    {
                        case LBN_SELCHANGE:
                        {
                            char Buffer[256];
                            int index = SendMessage((HWND)lParam, LB_GETCARETINDEX, 0, 0);
                            SendMessage((HWND)lParam, LB_GETTEXT, (LPARAM)index, (WPARAM)Buffer);
                            SetWindowText(hwnd, Buffer);
                            quote_number = index + 1;
                            if(index == 0)
                                printf("\tBooks.\n");
                            if(index == 1)
                                printf("\tInspiration\n");
                            if(index == 2)
                                printf("\tKnowledge\n");
                            if(index == 3)
                                printf("\tLife\n");
                            if(index == 4)
                                printf("\tLove\n");
                            if(index == 5)
                                printf("\tRandom\n");
                            if(index == 6)
                                printf("\tRelationship\n");
                            if(index == 7)
                                printf("\tScience\n");
                            if(index == 8)
                                printf("\tSuccess\n");
                            
                        }
                    }
                }
                break;
				default:
                break;
            }
        }
        break;
		case WM_CLOSE:
			DestroyWindow(hwnd);
		break;
		case WM_DESTROY:
			PostQuitMessage(0);
		break;
		default:
			return DefWindowProc(hwnd, msg, wParam, lParam);
	}
	return 0;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR lpCmdLine, int nCmdShow)
{
	WNDCLASSEX wc;
	HWND hwnd;
	MSG Msg;

	//Step 1: Registering the Window Class
	wc.cbSize		 = sizeof(WNDCLASSEX);
	wc.style		 = 0;
	wc.lpfnWndProc	 = WndProc;
	wc.cbClsExtra	 = 0;
	wc.cbWndExtra	 = 0;
	wc.hInstance	 = hInstance;
	wc.hIcon		 = LoadIcon(NULL, IDI_APPLICATION);
	wc.hCursor		 = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
	wc.lpszMenuName  = NULL;
	wc.lpszClassName = g_szClassName;
	wc.hIconSm		 = LoadIcon(NULL, IDI_APPLICATION);

	if(!RegisterClassEx(&wc))
	{
		MessageBox(NULL, "Window Registration Failed!", "Error!",
			MB_ICONEXCLAMATION | MB_OK);
		return 0;
	}

	// Step 2: Creating the Window
	hwnd = CreateWindowEx(
		WS_EX_CLIENTEDGE,
		g_szClassName,
		"Random Quote Generator",
		WS_MINIMIZEBOX | WS_SYSMENU,
		CW_USEDEFAULT, CW_USEDEFAULT,
        400, 400,
		HWND_DESKTOP, 
        NULL, hInstance, NULL);

	if(hwnd == NULL)
	{
		MessageBox(NULL, "Window Creation Failed!", "Error!",
			MB_ICONEXCLAMATION | MB_OK);
		return 0;
	}

	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);

	// Step 3: The Message Loop
	while(GetMessage(&Msg, NULL, 0, 0) > 0)
	{
		TranslateMessage(&Msg);
		DispatchMessage(&Msg);
	}
	return Msg.wParam;
}

void getQuote(int choice)
{   
    char a;
    int i = 0, n, iter = 0;
    FILE *fptr;
    srand(time(NULL));
    switch(choice)
    {
        case 1: fptr = fopen(".\\data\\books.txt", "r");
                n = (rand()%2932)+1;
                printf("Books Random: %d\n", n);
                break;
        case 2: fptr = fopen(".\\data\\inspiration.txt", "r");
                n = (rand()%2973)+1;
                printf("Inspiration Random: %d\n", n);
                break;
        case 3: fptr = fopen(".\\data\\knowledge.txt", "r");
                n = (rand()%2965)+1;
                printf("Knowledge Random: %d\n", n);
                break;
        case 4: fptr = fopen(".\\data\\life.txt", "r");
                n = (rand()%2963)+1;
                printf("Life Random: %d\n", n);
                break;
        case 5: fptr = fopen(".\\data\\love.txt", "r");
                n = (rand()%2972)+1;
                printf("Love Random: %d\n", n);
                break;
        case 6: n = (rand()%8)+1;
                printf("Random Random: %d\n", n);
                getQuote(n);
                break;
        case 7: fptr = fopen(".\\data\\relationships.txt", "r");
                n = (rand()%2950)+1;
                printf("Relationship Random: %d\n", n);
                break;
        case 8: fptr = fopen(".\\data\\science.txt", "r");
                n = (rand()%2911)+1;
                printf("Science Random: %d\n", n);
                break;
        case 9: fptr = fopen(".\\data\\success.txt", "r");
                n = (rand()%2973)+1;
                printf("Success Random: %d\n", n);
                break;
    }
    
    if(choice != 6)
    {
        printf("Getting the Quote.\n");
        if(fptr == NULL)
            MessageBox(NULL, "Data Retrival Failed!", "Error!",
                                    MB_ICONEXCLAMATION | MB_OK);
        else 
        {
            while(1)
            {   
                a = (char)fgetc(fptr);
                if(i == n-1) {
                    quote_random[iter++] = a;
                }
                if (a == '\n')
                    ++i;
                if(i == n)
                    break;
            }
        } 
        
        printf("Quote Printed\n");
        printf("%s", quote_random);
        fclose(fptr);
    }
}