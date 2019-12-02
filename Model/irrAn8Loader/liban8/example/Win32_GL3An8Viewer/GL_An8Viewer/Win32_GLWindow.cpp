#include"Win32_GLWindow.h"

#include <commdlg.h>
#include <shlobj.h> 
#include <time.h>

bool g_bIsActive = true;


Win32_GLWindow::Win32_GLWindow(void)
{
  bIsActive=false;
  bWantToExit=false;
  width=height=originalWidth=originalHeight=0;
}

Win32_GLWindow::~Win32_GLWindow(void)
{
    bIsActive=false;
    width=height=originalWidth=originalHeight=0;
}

void Win32_GLWindow::SetScreenSize(int i_iWidth, int i_iHeight)
{
  width  = i_iWidth;
  height = i_iHeight;
}
			
bool Win32_GLWindow::IsActive(void)
{
  return bIsActive;
}

void Win32_GLWindow::IWantToExit(void)
{
  bWantToExit = true;
}

bool Win32_GLWindow::Create(char* title, int width, int height, int bits, bool fullscreenflag,DWORD dwStyle,WNDPROC WndProc)
{

	height = height + GetSystemMetrics(SM_CYMENU);

    this->width=width;
    this->height=height;
    this->originalWidth=width;
    this->originalHeight=height;
    this->style=style;
    this->fullscreen=fullscreen;
    
	GLuint		PixelFormat;			// Stock les Resultats apr�s un recherche de correspondance
	WNDCLASS	wc;						// Structure de classe de fen�tre 
	DWORD		dwExStyle;				// Style de fen�tre �tendu
	RECT		WindowRect;				// Va stocker les coordonn�es de la fen�tre
	WindowRect.left=(long)0;			// 0
	WindowRect.right=(long)width;		// Largeur
	WindowRect.top=(long)0;				// 0
	WindowRect.bottom=(long)height;		// Hauteur

	fullscreen=fullscreenflag;			// Affectation de la variable

	hInstance			= GetModuleHandle(NULL);				// R�cup�re l'Instance de la fen�tre
	wc.style			= CS_HREDRAW | CS_VREDRAW | CS_OWNDC;	// Style resize et DC non partag� pour la fen�tre.
	wc.lpfnWndProc		= (WNDPROC) WndProc;					// Proc�dure de fen�tre
	wc.cbClsExtra		= 0;									// Pas de donn�e supl�mentaire pour le fen�tre
	wc.cbWndExtra		= 0;									// Pas de donn�e supl�mentaire pour le fen�tre
	wc.hInstance		= hInstance;							// Instance
	wc.hIcon			= LoadIcon(NULL, IDI_WINLOGO);			// Charge l'ic�ne par d�faut
	wc.hCursor			= LoadCursor(NULL, IDC_ARROW);			// Charge le pointeur de souris
	wc.hbrBackground	= NULL;									// Pas de Background pour un prog OGL
	wc.lpszMenuName		= NULL;									// Pas de menu
	wc.lpszClassName	= "OpenGL";								// Nom de la Classe

	if (!RegisterClass(&wc))									// Enregistrement de la classe de fen�tre
	{
		MessageBox(NULL,"Failed To Register The Window Class.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;											
	}
	
	if (fullscreen)												// Mode Fullscreen? oui
	{
		DEVMODE dmScreenSettings;								// Device Mode
		memset(&dmScreenSettings,0,sizeof(dmScreenSettings));	// Efface la m�moire
		dmScreenSettings.dmSize=sizeof(dmScreenSettings);		// Taille de la structure Devmode 
		dmScreenSettings.dmPelsWidth	= width;				// Largeur de l'�cran
		dmScreenSettings.dmPelsHeight	= height;				// Hauteur de l'�cran
		dmScreenSettings.dmBitsPerPel	= bits;					// Nombre de bits par pixel
		dmScreenSettings.dmFields=DM_BITSPERPEL|DM_PELSWIDTH|DM_PELSHEIGHT;

		// Tantative d'application du mode souhait�e.  NOTE: CDS_FULLSCREEN enl�ve la Start Bar.
		if (ChangeDisplaySettings(&dmScreenSettings,CDS_FULLSCREEN)!=DISP_CHANGE_SUCCESSFUL)
		{
			// Si probl�me, choix entre:  Quitter ou mode fen�tr�.
			if (MessageBox(NULL,"The Requested Fullscreen Mode Is Not Supported By\nYour Video Card. Use Windowed Mode Instead?","ERROR",MB_YESNO|MB_ICONEXCLAMATION)==IDYES)
			{
				fullscreen=FALSE;		// Mode fen�tr�.  Fullscreen = FALSE
			}
			else
			{
				// Une bo�te de message informe l'utilisateur de la fermeture.
				MessageBox(NULL,"Program Will Now Close.","ERROR",MB_OK|MB_ICONSTOP);
				return FALSE;								
			}
		}
	}

	if (fullscreen)												// Mode Fullscreen ?
	{
		dwExStyle=WS_EX_APPWINDOW;								// Style �tendu 
		dwStyle=WS_POPUP;										// Style sans bordure
		ShowCursor(FALSE);										// Cache le Pointeur de souris
	}
	else
	{
		dwExStyle=WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;			// Style �tendu
	//	dwStyle=WS_OVERLAPPEDWINDOW;							// Style de fen�tre
	}

	// La taille de la zone cliente = la taille de fen�tre demand� (les bordures sont mis autour)
	AdjustWindowRectEx(&WindowRect, dwStyle, FALSE, dwExStyle);		

	// Cr�ation de la fen�tre
	if (!(hWnd=CreateWindowEx(	dwExStyle,							// Style �tendu
								"OpenGL",							// Nom de la classe
								title,								// Titre de la fen�tre
								dwStyle |							// Definition du style
								WS_CLIPSIBLINGS |					// 
								WS_CLIPCHILDREN,					// 
								0, 0,								// Position de la fen�tre
								WindowRect.right-WindowRect.left,	// Calculate Window Width
								WindowRect.bottom-WindowRect.top,	// Calculate Window Height
								NULL,								// Pas De Fen�tre Parente
								NULL,								// Pas De Menu
								hInstance,							// Instance
								NULL)))								// WM_CREATE
	{
		//Win32_KillGLWindow();					
		MessageBox(NULL,"Window Creation Error.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;								
	}

	static	PIXELFORMATDESCRIPTOR pfd=		
	{
		sizeof(PIXELFORMATDESCRIPTOR),		// Taille
		1,									// Numero de version
		PFD_DRAW_TO_WINDOW |				// Affichage dans une fen�tre
		PFD_SUPPORT_OPENGL |				// Support d'OpenGL
		PFD_DOUBLEBUFFER,					// Double Buffering
		PFD_TYPE_RGBA,						// Format RGBA
		bits,								// D�finition de couleur
		0, 0, 0, 0, 0, 0,					// Bits de couleur Ignor�
		0,									// Buffer Alpha
		0,									// Shift Bit Ignor�
		0,									// Accumulation Buffer (0 ou 1)
		0, 0, 0, 0,							// Accumulation Bits Ignor�
		32,									// 16Bit Z-Buffer (Depth Buffer)  
		0,									// Stencil Buffer (0 ou 1)
		0,									// Auxiliary Buffer (0 ou 1)
		PFD_MAIN_PLANE,						// Main Drawing Layer
		0,									// Reserv�
		0, 0, 0								// Layer Masks Ignor�
	};
	
	if (!(hDC=GetDC(hWnd)))			// Obtention du Device Context
	{
		//Win32_KillGLWindow();					
		MessageBox(NULL,"Can't Create A GL Device Context.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;							
	}

	if (!(PixelFormat=ChoosePixelFormat(hDC,&pfd)))	// Pixel Format correspondant trouv� par la fen�tre?
	{
		//Win32_KillGLWindow();								
		MessageBox(NULL,"Can't Find A Suitable PixelFormat.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;								
	}

	if(!SetPixelFormat(hDC,PixelFormat,&pfd))	// Affectation du Pixel Format
	{
		//Win32_KillGLWindow();						
		MessageBox(NULL,"Can't Set The PixelFormat.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;							
	}

	if (!(hRC=wglCreateContext(hDC)))	// Obtention du Rendering Context
	{
		//Win32_KillGLWindow();							
		MessageBox(NULL,"Can't Create A GL Rendering Context.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;							
	}

	if(!wglMakeCurrent(hDC,hRC))	// Activation du Rendering Context
	{
		//Win32_KillGLWindow();								
		MessageBox(NULL,"Can't Activate The GL Rendering Context.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;								
	}

	//ShowWindow(hWnd,SW_SHOW);						// Affichage de la fen�tre
	ShowWindow(hWnd,SW_HIDE);						// Affichage de la fen�tre
	SetForegroundWindow(hWnd);						// Plus haute priorit�
	SetFocus(hWnd);									// Focus du clavier pour la fen�tre

	UpdateWindow(hWnd);
	ShowWindow(hWnd,SW_SHOW);


	return TRUE;									// Ok
}

////////////////////////////////////////////////////////////

void Win32_GLWindow::Loop(void (*ptrFctFrameMove)(double,float),void (*ptrFctFrameRender)(double,float),void (*ptrFctOnDestroy)(void))
{
	MSG msg;


	clock_t lastClock = clock();
	clock_t currClock = lastClock;

	double currTime    = 0.0f;
	float  elapsedTime = 0.0f;

	while(!bWantToExit)									
	{
		if (PeekMessage(&msg,NULL,0,0,PM_REMOVE))	
		{
			if (msg.message==WM_QUIT)				
			{
				bWantToExit=TRUE;							
			}
			else									
			{
				TranslateMessage(&msg);				
				DispatchMessage(&msg);			
			}
		}
		else // No msg from Windows we continue									
		{					
			if(IsActive() == true)
			{
				currClock = clock();

				currTime    =  (double)currClock / CLOCKS_PER_SEC;
				elapsedTime =  (float)((double) (currClock-lastClock)) / CLOCKS_PER_SEC;

				ptrFctFrameMove(currTime,elapsedTime);
				ptrFctFrameRender(currTime,elapsedTime);
				SwapBuffers(hDC);	// Swap Buffers (Double Buffering)	

				lastClock = currClock;
			}
		}
	}
	ptrFctOnDestroy();
}

////////////////////////////////////////////////////////////
void Win32_GLWindow::Kill(void)							
{
	if (fullscreen)								// Mode plein �cran?
	{
		ChangeDisplaySettings(NULL,0);			// Si oui, retour au bureau
		ShowCursor(TRUE);						// On affiche le pointeur de la souris
	}

	if (hRC)									// Y a t-il un Rendering Context?
	{
		if (!wglMakeCurrent(NULL,NULL))	        // Peut-on lib�rer le DC et le RC Context?
		{
			MessageBox(NULL,"Release Of DC And RC Failed.","SHUTDOWN ERROR",MB_OK | MB_ICONINFORMATION);
		}

		if (!wglDeleteContext(hRC))				// Peut-on �ffacer le RC?
		{
			MessageBox(NULL,"Release Rendering Context Failed.","SHUTDOWN ERROR",MB_OK | MB_ICONINFORMATION);
		}
		hRC=NULL;									
	}

	if (hDC && !ReleaseDC(hWnd,hDC))			// Peut-on lib�rer le DC ?
	{
		MessageBox(NULL,"Release Device Context Failed.","SHUTDOWN ERROR",MB_OK | MB_ICONINFORMATION);
		hDC=NULL;									
	}

	if (hWnd && !DestroyWindow(hWnd))					// Peut-on d�truire la fen�tre?
	{
		MessageBox(NULL,"Could Not Release hWnd.","SHUTDOWN ERROR",MB_OK | MB_ICONINFORMATION);
		hWnd=NULL;									
	}

	if (!UnregisterClass("OpenGL",hInstance))			// Peut-on d�enregister la classe
	{
		MessageBox(NULL,"Could Not Unregister Class.","SHUTDOWN ERROR",MB_OK | MB_ICONINFORMATION);
		hInstance=NULL;								
	}
}





BOOL Win32_PopFileOpenDlg (HWND hwnd, char* pstrFileName, char* pstrTitleName)
{
	OPENFILENAME ofn;
	ofn.lStructSize			= sizeof(OPENFILENAME);
	ofn.hwndOwner			= NULL;
	ofn.hInstance			= 0;
	ofn.lpstrFilter			= "Anim8or .an8 file (*.an8)\0*.an8\0";
	ofn.lpstrCustomFilter	= NULL;
	ofn.nMaxCustFilter		= 0;
	ofn.nFilterIndex		= 0;
	ofn.lpstrFile			= pstrFileName;
	ofn.lpstrFile[0]		= (short)'\0';
	ofn.nMaxFile			= 256;
	ofn.lpstrFileTitle		= pstrTitleName;
	ofn.nMaxFileTitle		= 256;
	ofn.lpstrInitialDir		= NULL;
	ofn.lpstrTitle			= "Select your file:";
	ofn.Flags				= OFN_ENABLESIZING | OFN_EXPLORER | OFN_NOCHANGEDIR;
	ofn.nFileOffset			= 0;
	ofn.nFileExtension		= 0;
	ofn.lpstrDefExt			= NULL;
	ofn.lCustData			= 0;
	ofn.lpfnHook			= NULL;
	ofn.lpTemplateName		= NULL;

	return(GetOpenFileName(&ofn) ? true : false);
}

