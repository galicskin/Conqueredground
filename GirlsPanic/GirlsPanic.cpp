// GirlsPanic.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//

#include <stack>

#include "framework.h"
#include "GirlsPanic.h"

#include "GameManager.h"
#include "SceneManager.h"
#define MAX_LOADSTRING 100

using namespace Gdiplus;
ULONG_PTR g_GdiToken;
void Gdi_Init();
void Gdi_End();

HBITMAP hDoubleBufferImage;

bool onVertex = true;
bool PressArrowKey = false;
bool PressSpaceKey = false;
void Update();

enum directions { Right=10,Left,Up,Down,Stop};
int direct= directions::Stop;
void CALLBACK TimerProc(HWND hWnd, UINT uMsg, UINT idEvent, DWORD dwTime);


GameManager GM;
SceneManager SM;
StartScene start;
Stage1 stage1;
EndScene end;
RECT Clientrc;

std::stack<POINT> occupyLine;
std::stack<POINT> DrawLine;
bool isOccupy = false;

// 전역 변수:
HINSTANCE hInst;                                // 현재 인스턴스입니다.
WCHAR szTitle[MAX_LOADSTRING];                  // 제목 표시줄 텍스트입니다.
WCHAR szWindowClass[MAX_LOADSTRING];            // 기본 창 클래스 이름입니다.

// 이 코드 모듈에 포함된 함수의 선언을 전달합니다:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: 여기에 코드를 입력합니다.

    // 전역 문자열을 초기화합니다.
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_GIRLSPANIC, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    Gdi_Init();

    // 애플리케이션 초기화를 수행합니다:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_GIRLSPANIC));

    MSG msg;

    // 기본 메시지 루프입니다:
    while (true)
    {
        if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
        {
            if (msg.message == WM_QUIT)
            {
                break;
            }
            else
            {
                TranslateMessage(&msg); //메세지 번역(어떤 메세지인지
                DispatchMessage(&msg);
            }
        }
        
        
        {
            Update();
        }
    }

    Gdi_End();
    return (int) msg.wParam;
}



//
//  함수: MyRegisterClass()
//
//  용도: 창 클래스를 등록합니다.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_GIRLSPANIC));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_GIRLSPANIC);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   함수: InitInstance(HINSTANCE, int)
//
//   용도: 인스턴스 핸들을 저장하고 주 창을 만듭니다.
//
//   주석:
//
//        이 함수를 통해 인스턴스 핸들을 전역 변수에 저장하고
//        주 프로그램 창을 만든 다음 표시합니다.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // 인스턴스 핸들을 전역 변수에 저장합니다.

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  함수: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  용도: 주 창의 메시지를 처리합니다.
//
//  WM_COMMAND  - 애플리케이션 메뉴를 처리합니다.
//  WM_PAINT    - 주 창을 그립니다.
//  WM_DESTROY  - 종료 메시지를 게시하고 반환합니다.
//
//
  
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    static int WHERE = 0;
   
    switch (message)
    {
    case WM_CREATE:
    {
        GetWindowRect(hWnd, &Clientrc);

        Gdiplus::Image* pimgBack = nullptr;
        Gdiplus::Image* pimgStart = nullptr;
        Gdiplus::Image* pimgStage1 = nullptr;
        Gdiplus::Image* pPlayer = nullptr;
        Gdiplus::Image* pimgEnd = nullptr;

        //Gdiplus::Image T((WCHAR*)L"images/검배경.png");
        //CirculyDoublyLinkedList::Node* f = new CirculyDoublyLinkedList::Node;
        pimgBack = new Gdiplus::Image((WCHAR*)L"images/검배경.png");
        SM.SetImg(pimgBack);

        pimgStart = new Gdiplus::Image((WCHAR*)L"images/누르면 시작.png");
        start.SetImg(pimgStart);

        pimgStage1 = new Gdiplus::Image((WCHAR*)L"images/적 미사일 원본.png");
        stage1.SetImg(pimgStage1);

        pPlayer = new Gdiplus::Image((WCHAR*)L"images/마름모.png");
        GM.SetImg(pPlayer);

        pimgEnd= new Gdiplus::Image((WCHAR*)L"images/1.png");
        end.SetImg(pimgEnd);

        //>> 초기세팅
        int w = pimgStage1->GetWidth();
        int h = pimgStage1->GetHeight();
       // Rect((Clientrc.right - Clientrc.left - w) / 2, (Clientrc.bottom - Clientrc.top - h) / 2, w, h);

       

        CirculyDoublyLinkedList::Node* LT = new CirculyDoublyLinkedList::Node({ (Clientrc.right - Clientrc.left - w) / 2, (Clientrc.bottom - Clientrc.top - h) / 2 });
        CirculyDoublyLinkedList::Node* RT = new CirculyDoublyLinkedList::Node({ (Clientrc.right - Clientrc.left + w) / 2, (Clientrc.bottom - Clientrc.top - h) / 2 });
        CirculyDoublyLinkedList::Node* RB = new CirculyDoublyLinkedList::Node({ (Clientrc.right - Clientrc.left + w) / 2, (Clientrc.bottom - Clientrc.top + h) / 2 });
        CirculyDoublyLinkedList::Node* LB = new CirculyDoublyLinkedList::Node({ (Clientrc.right - Clientrc.left - w) / 2, (Clientrc.bottom - Clientrc.top + h) / 2 });

        LT->next = LT;
        LT->prev = LT;
        GM.GetPlayerData().Conquered->Sethead(LT);
        GM.GetPlayerData().Conquered->AddNode(RT);
        GM.GetPlayerData().Conquered->AddNode(RB);
        GM.GetPlayerData().Conquered->AddNode(LB);

        GM.GetPlayerData().Conquered->SetSize(4);
        
        GM.SetPlayerPos(LT->point.x, LT->point.y);
        GM.SetPlayerVel(5);

        GM.init_SetFront_AfterNode();

        //<<
        

       



       SetTimer(hWnd, 1, 0, (TIMERPROC)TimerProc);
    }
    break;
    case WM_KEYDOWN:
    {
        switch (WHERE)
        {
            case START:
            {
                WHERE++;
            }
            break; 
        }
    }
    break;
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // 메뉴 선택을 구문 분석합니다:
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_PAINT:
        {
            
          
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);

            
            
            HDC hMemDC;
            HBITMAP hOldBitmap;
            

            hMemDC = CreateCompatibleDC(hdc);

            if (hDoubleBufferImage == NULL)  //hdc 로 부터 비트맵 이미지 제작(도화지)
            {
                hDoubleBufferImage = CreateCompatibleBitmap(hdc, Clientrc.right, Clientrc.bottom);
            }

            hOldBitmap = (HBITMAP)SelectObject(hMemDC, hDoubleBufferImage);


                switch (WHERE)
                {
                case START:
                {

                    SM.DrawBackground(hMemDC, Clientrc);
                    start.DrawStart(hMemDC, Clientrc);
                    
                }
                break;
                case STAGE1:
                {

                    SM.DrawBackground(hMemDC, Clientrc);
                    stage1.DrawStage(hMemDC, Clientrc);
                    stage1.DrawCover(hMemDC, GM);
                    stage1.DrawPlayer(hMemDC, GM);
                   
                    stage1.DrawLine(hMemDC, occupyLine,GM);
                    

                   

                }
                break;
                case END:
                {
                    SM.DrawBackground(hMemDC, Clientrc);
                    end.DrawEnd(hMemDC);
                }
                break;
                }

                BitBlt(hdc, 0, 0, Clientrc.right, Clientrc.bottom,
                    hMemDC, 0, 0, SRCCOPY);  //현재 그려진 DC를 모니터(hdc)에 그려줌  -> 그리는 단계가 사라지고 바로 보여줌..

                SelectObject(hMemDC, hOldBitmap);  //DC해제
                DeleteDC(hMemDC);

            // TODO: 여기에 hdc를 사용하는 그리기 코드를 추가합니다...
           
            EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        KillTimer(hWnd,1);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// 정보 대화 상자의 메시지 처리기입니다.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}



void Gdi_Init()
{
    GdiplusStartupInput gpsi;
    GdiplusStartup(&g_GdiToken, &gpsi, NULL);
}

void Gdi_End()
{
    GdiplusShutdown(g_GdiToken);
}

void Update()
{
    DWORD newTime = GetTickCount();
    static DWORD oldTime = newTime;
    if (newTime - oldTime < 1)
    {
        return;
    }
    oldTime = newTime;



   

    
    
  


    if (GetAsyncKeyState(VK_SPACE) & 0x8001)// 누르고있을때
    {
        CirculyDoublyLinkedList::Node*cursor=GM.GetPlayerData().Conquered->head;
        
        bool endoccupy = false;

        switch (direct)
        {
        case directions::Right:
        {
            do {
                if (cursor->next->point.x == cursor->point.x)//y축 평행
                {
                    if (cursor->next->point.y > cursor->point.y )
                    {
                        if (GM.isYboader(cursor, directions::Right) )
                        {
                            endoccupy = true;
                            isOccupy = false;
                            break;
                        }
                    }

                }
                cursor = cursor->next;
            } while (cursor != GM.GetPlayerData().Conquered->head);

        }
        break;
        case directions::Left:
        {
            do {
                if (cursor->next->point.x == cursor->point.x)//y축 평행
                {
                    if (cursor->next->point.y < cursor->point.y)
                    {
                        if (GM.isYboader(cursor, directions::Left) )
                        {
                            endoccupy = true;
                            isOccupy = false;
                            break;
                        }
                    }

                }
                cursor = cursor->next;
            } while (cursor != GM.GetPlayerData().Conquered->head);
        }
        break;
        case directions::Up:
        {
            do {
                if (cursor->next->point.y == cursor->point.y)//x축 평행
                {
                    if (cursor->next->point.x > cursor->point.x )
                    {
                        if (GM.isXboader(cursor, directions::Up))
                        {
                            endoccupy = true;
                            isOccupy = false;
                            break;
                        }
                    }

                }
                cursor = cursor->next;
            } while (cursor != GM.GetPlayerData().Conquered->head);
        }
        break;
        case directions::Down:
        {
            do {
                if (cursor->next->point.y == cursor->point.y)//x축 평행
                {
                    if (cursor->next->point.x < cursor->point.x)
                    {
                        if (GM.isXboader(cursor, directions::Down))
                        {
                            endoccupy = true;
                            isOccupy = false;
                            break;
                        }
                    }

                }
                cursor = cursor->next;
            } while (cursor != GM.GetPlayerData().Conquered->head);
        }
        break;
        default:
            break;
        }


        if (endoccupy)//땅따먹기완료
        {
            //꼭짓점 부분에 닿았다면 굳이 안넣음
            if ((GM.GetPlayerData().xCursor == cursor->point.x && GM.GetPlayerData().yCursor == cursor->point.y)
                || (GM.GetPlayerData().xCursor == cursor->next->point.x && GM.GetPlayerData().yCursor == cursor->next->point.y))
            {
            }
            else
            {
                occupyLine.push({ GM.GetPlayerData().xCursor,GM.GetPlayerData().yCursor });
            }

            GM.GetPlayerData().Conquered->splitList


        }
        

        if (isOccupy)
        {

            if (GetAsyncKeyState(VK_RIGHT) & 0x8001)
            {
                //이동 바로가던방향
                if (direct == directions::Left)
                {
                    
                }
                else
                {
                    if (direct != directions::Right)
                    {
                        occupyLine.push({ GM.GetPlayerData().xCursor,GM.GetPlayerData().yCursor });
                        direct = directions::Right;
                    }
                    GM.MoveRight();
                }
                


            }
            else if (GetAsyncKeyState(VK_LEFT) & 0x8001)
            {
                if (direct == directions::Right)
                {

                }
                else
                {

                    if (direct != directions::Left)
                    {
                        occupyLine.push({ GM.GetPlayerData().xCursor,GM.GetPlayerData().yCursor });
                        direct = directions::Left;

                    }

                    GM.MoveLeft();
                }
            }
            else if (GetAsyncKeyState(VK_UP) & 0x8001)
            {
                if (direct == directions::Down)
                {

                }
                else
                {
                    if (direct != directions::Up)
                    {
                        occupyLine.push({ GM.GetPlayerData().xCursor,GM.GetPlayerData().yCursor });
                        direct = directions::Up;
                    }
                    GM.MoveUp();
                }

            }
            else if (GetAsyncKeyState(VK_DOWN) & 0x8001)
            {
                if (direct == directions::Up)
                {

                }
                else
                {
                    if (direct != directions::Down)
                    {
                        occupyLine.push({ GM.GetPlayerData().xCursor,GM.GetPlayerData().yCursor });
                        direct = directions::Down;
                    }
                    GM.MoveDown();
                }
            }
           


           


            //DrawLine = occupyLine;
           // DrawLine.push({ GM.GetPlayerData().xCursor,GM.GetPlayerData().yCursor });
        }
        else
        {


            //1.내가 들어갈 수 있는 방향부터 체크
            switch (GM.OcuppyLine())
            {
            case can_ocuppy::Both:
            {

                POINT MoveVector;
                if (GetAsyncKeyState(VK_RIGHT) & 0x8001)
                {
                    MoveVector = { 1, 0 };
                    if ((GM.GetprevVector().x - GM.GetVector().x) * MoveVector.x + (GM.GetprevVector().y - GM.GetVector().y) * MoveVector.y > 0)
                    {
                        occupyLine.push({ GM.GetPlayerData().xCursor,GM.GetPlayerData().yCursor });
                        GM.MoveRight();
                        direct = directions::Right;
                        isOccupy = true;
                    }
                }
                else if (GetAsyncKeyState(VK_LEFT) & 0x8001)
                {
                    MoveVector = { -1, 0 };
                    if ((GM.GetprevVector().x - GM.GetVector().x) * MoveVector.x + (GM.GetprevVector().y - GM.GetVector().y) * MoveVector.y > 0)
                    {
                        occupyLine.push({ GM.GetPlayerData().xCursor,GM.GetPlayerData().yCursor });
                        GM.MoveLeft();
                        direct = directions::Left;
                        isOccupy = true;
                    }
                }
                else if (GetAsyncKeyState(VK_UP) & 0x8001)
                {
                    MoveVector = { 0, -1 };
                    if ((GM.GetprevVector().x - GM.GetVector().x) * MoveVector.x + (GM.GetprevVector().y - GM.GetVector().y) * MoveVector.y > 0)
                    {
                        occupyLine.push({ GM.GetPlayerData().xCursor,GM.GetPlayerData().yCursor });
                        GM.MoveUp();
                        direct = directions::Up;
                        isOccupy = true;
                    }
                }
                else if (GetAsyncKeyState(VK_DOWN) & 0x8001)
                {
                    MoveVector = { 0, 1 };
                    if ((GM.GetprevVector().x - GM.GetVector().x) * MoveVector.x + (GM.GetprevVector().y - GM.GetVector().y) * MoveVector.y > 0)
                    {
                        occupyLine.push({ GM.GetPlayerData().xCursor,GM.GetPlayerData().yCursor });
                        GM.MoveDown();
                        direct = directions::Down;
                        isOccupy = true;
                    }
                }



            }
            break;
            case can_ocuppy::Only:
            {
                POINT MoveVector;
                if (GetAsyncKeyState(VK_RIGHT) & 0x8001)
                {
                    MoveVector = { 1, 0 };
                    if (MoveVector.x * GM.GetVector().y - MoveVector.y * GM.GetVector().x < 0)
                    {
                        occupyLine.push({ GM.GetPlayerData().xCursor,GM.GetPlayerData().yCursor });
                        GM.MoveRight();
                        direct = directions::Right;
                        isOccupy = true;
                    }
                }
                else if (GetAsyncKeyState(VK_LEFT) & 0x8001)
                {
                    MoveVector = { -1, 0 };
                    if (MoveVector.x * GM.GetVector().y - MoveVector.y * GM.GetVector().x < 0)
                    {
                        occupyLine.push({ GM.GetPlayerData().xCursor,GM.GetPlayerData().yCursor });
                        GM.MoveLeft();
                        direct = directions::Left;
                        isOccupy = true;
                    }
                }
                else if (GetAsyncKeyState(VK_UP) & 0x8001)
                {
                    MoveVector = { 0, -1 };
                    if (MoveVector.x * GM.GetVector().y - MoveVector.y * GM.GetVector().x < 0)
                    {
                        occupyLine.push({ GM.GetPlayerData().xCursor,GM.GetPlayerData().yCursor });
                        GM.MoveUp();
                        direct = directions::Up;
                        isOccupy = true;
                    }
                }
                else if (GetAsyncKeyState(VK_DOWN) & 0x8001)
                {
                    MoveVector = { 0, 1 };
                    if (MoveVector.x * GM.GetVector().y - MoveVector.y * GM.GetVector().x < 0)
                    {
                        occupyLine.push({ GM.GetPlayerData().xCursor,GM.GetPlayerData().yCursor });
                        GM.MoveDown();
                        direct = directions::Down;
                        isOccupy = true;
                    }
                }

            }
            break;
            case can_ocuppy::Nothing:
            {
                //멈추기
            }
            break;
            }
            //2. 밖은 막기, 안쪽은 막지는 않지만 시작점을 기록하지않기 
            //3. 방향키가 바뀔때 마다 해당 점을 기록
            //4. 임의의 선분위에 도착시 끝


               //스페이스바를 뗏을경우 바로 밑에 else 로 들어가는것이 아닌 
                    //갔던길을 돌아간 후에 들어갈 수 있도록 하기
        }
    }
    else if (isOccupy == true) //스페이스바를 뗐을경우
    {
        

            switch (direct)
            {
            case directions::Right:
            {
                GM.MoveLeft();
                if (occupyLine.top().x == GM.GetPlayerData().xCursor)
                {
                    occupyLine.pop();
                    if (occupyLine.empty())
                    {
                        isOccupy = false;
                    }
                    else if (GM.GetPlayerData().yCursor > occupyLine.top().y)
                    {
                        direct = directions::Down;
                    }
                    else
                    {
                        direct = directions::Up;
                    }
                }
            }
            break;
            case directions::Left:
            {
                GM.MoveRight();
                if (occupyLine.top().x == GM.GetPlayerData().xCursor)
                {
                    occupyLine.pop();
                    if (occupyLine.empty())
                    {
                        isOccupy = false;
                    }
                    else if (GM.GetPlayerData().yCursor > occupyLine.top().y)
                    {
                        direct = directions::Down;
                    }
                    else
                    {
                        direct = directions::Up;
                    }
                }
            }
            break;
            case directions::Up:
            {
                GM.MoveDown();
                if (occupyLine.top().y == GM.GetPlayerData().yCursor)
                {
                    occupyLine.pop();
                    if (occupyLine.empty())
                    {
                        isOccupy = false;
                    }                  
                    else if (GM.GetPlayerData().xCursor > occupyLine.top().x)
                    {
                        direct = directions::Right;
                    }
                    else
                    {
                        direct = directions::Left;
                    }
                }
            }
            break;
            case directions::Down:
            {
                GM.MoveUp();
                if (occupyLine.top().y == GM.GetPlayerData().yCursor)
                {
                    occupyLine.pop();
                    if (occupyLine.empty())
                    {
                        isOccupy = false;
                    }                   
                    else if (GM.GetPlayerData().xCursor > occupyLine.top().x)
                    {
                        direct = directions::Right;
                    }
                    else
                    {
                        direct = directions::Left;
                    }
                }
            }
            break;
            }
        
    }
    else //스페이스바를 안누를때
    {
        if (onVertex == true)
        {
            //꼭짓점 일 때 이야기 : 양끝점사이에 현재 커서가 있는지 여부를 따질것.
            if (GM.ableLine().x == 1)
            {
                if (GetAsyncKeyState(VK_RIGHT) & 0x8000) 
                {
                    GM.MoveRight();
                    //좌우
                        if (GM.backline())
                        {
                            GM.SetBackLine();
                        }
                    onVertex = false;
                    
                }
            }
            else if(GM.ableLine().x == -1)
            {
                if (GetAsyncKeyState(VK_LEFT) & 0x8000) 
                {
                    
                    GM.MoveLeft();
                    //좌우
                        if (GM.backline())
                        {
                            GM.SetBackLine();
                        }
                    onVertex = false;
                }
            }

            if (GM.ableLine().y == 1)
            {
                if(GetAsyncKeyState(VK_DOWN) & 0x8000)
                {
                GM.MoveDown();
                    if (GM.backline())
                    {
                        GM.SetBackLine();
                    }
                onVertex = false;
                }
            }
            else if (GM.ableLine().y == -1)
            {
                if(GetAsyncKeyState(VK_UP) & 0x8000) 
                {
                GM.MoveUp();
                    if (GM.backline())
                    {
                        GM.SetBackLine();
                    }
                onVertex = false;
                }
            }
            
        }
        //꼭짓점이 아닐 때
        else
        {
            //parallel{ Xaxis = 1, Yaxis, FrontPos ,AfterPos, NOT };
            switch (GM.onObjectLine())
            {
                case FrontPos:
                {
                    onVertex = true;
                }
                break;
                case AfterPos:
                {
                    //다음모서리로 이동
                    GM.SetNextLine();
                    onVertex = true;
                }
                break;
                case Xaxis:
                {
                    if (GetAsyncKeyState(VK_RIGHT) & 0x8001)
                    {
                        GM.MoveRight();
                    }
                    else if (GetAsyncKeyState(VK_LEFT) & 0x8001)
                    {
                        GM.MoveLeft();
                    }
                }
                break;
                case Yaxis:
                {
                    if (GetAsyncKeyState(VK_DOWN) & 0x8001)
                    {
                        GM.MoveDown();
                    }
                    else if (GetAsyncKeyState(VK_UP) & 0x8001)
                    {
                        GM.MoveUp();
                    }
                }
                break;
                case NOT:
                {

                }
                break;
            }
        }
    
    }
 


}

void CALLBACK TimerProc(HWND hWnd, UINT uMsg, UINT idEvent, DWORD dwTime)
{
    InvalidateRect(hWnd, NULL, FALSE);
}

  
