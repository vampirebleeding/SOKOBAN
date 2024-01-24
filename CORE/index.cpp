
#include <ctype.h>
#include <signal.h>
#include <cstdlib>
#include <windows.h>
#include <mmsystem.h>

extern "C" {
#include "game_rankings.h"
}

#include "loop.h"

#pragma comment(lib, "winmm.lib")

#define COMMAND_NUM 4

LinkNode* L = NULL;

int main()
{   
    //1 ��Ƶ����ģ��
    mciSendString(_T("open  song.mp3 alias music"), 0, 0, 0);
    mciSendString(TEXT("play music repeat"), 0, 0, 0);

    //2 ������ģ��
    while (1) {
        
        
        //2.1 �����������ͼ
        initgraph(SCREEN_WIDTH, SCREEN_HEIGHT, 0);
        IMAGE mainMenu;
        loadimage(&mainMenu, _T("zhujiemian.bmp"), SCREEN_WIDTH, SCREEN_HEIGHT, true);
        putimage(0, 0, &mainMenu);
        

        //2.2 ʵ���������ת����Ӧ����
        MOUSEMSG msg;
        int getOut = 1;
        char name[NAME_SIZE] = { '\0' };
        do {
            if (MouseHit()) {
                MOUSEMSG msg = GetMouseMsg();
                if (msg.uMsg == WM_LBUTTONDOWN) {
                    
                    
                    //2.2.1 �½���Ϸģ��
                    if (msg.x > 145 && msg.x < 380 && msg.y > 257 && msg.y < 330) {
                        closegraph();
                        
                       
                        //2.2.1.1 ��ȡ�û���
                        char ch;
                        int pos = 0;
                        printf("\n\n\n\n\n\n\n\n\n\n\n\n                                        Please input player's name:  ");
                        while ((ch = getchar()) != '\n')
                        {
                            name[pos++] = ch;
                        }
                        name[pos] = '\0';
                        system("cls");


                        //2.2.1.2 ������Ϸ
                        int out = 0;
                        int scores = 0;                     //��Ϸ�÷�
                        loop(&out, name, &scores);          // define in "loop.cpp"
                        
                        
                        //2.2.1.3 ����Ϸ�÷ִ������а�
                        load_rankings(&L);                  // define in "game_rankings.c"
                        add_rankings(name, scores, &L);     // define in "game_rankings.c"
                        sort_rankings(&L);
                        sort_rankings(&L);                  // define in "game_rankings.c"
                        save_to_file(L);                    // define in "game_rankings.c"
                        
                        
                        getOut = 0;
                    }


                    //2.2.2 �鿴����ģ��
                    else if (msg.x > 145 && msg.x < 380 && msg.y > 345 && msg.y < 420) {
                        closegraph();
                        
                        
                        //2.2.2.1 ��ʾ���а�
                        printf("Ranking List\n");
                        show_rankings();                                // define in "game_rankings.c"
                        printf("Enter 1 to return to the main menu");
                        
                        
                        //2.2.2.2 ʵ�ּ���������1��,����������Ĺ���
                        bool goOn = true;
                        while (goOn) {
                            int a;
                            scanf("%d", &a);
                            if (a == 1) {
                                goOn = false;
                                getchar();
                            }
                            getOut = 0;
                            system("cls");
                        }
                    }


                    //2.2.3 �˳���Ϸ
                    else if (msg.x > 145 && msg.x < 380 && msg.y > 430 && msg.y < 495) {
                        closegraph();
                        exit(0);
                    }


                    //2.2.4 �������ģ��
                    else if (msg.x > 430 && msg.x < 650 && msg.y > 257 && msg.y < 330) {
                        closegraph();
                        reset_rankings(&L);  // define in "game_rankings.c"
                        delete_file();       // define in "game_rankings.c"
                        getOut = 0;
                    }


                    //2.2.5 ɾ����ҹ���
                    else if (msg.x > 430 && msg.x < 650 && msg.y > 345 && msg.y < 420) {
                        closegraph();
                        load_rankings(&L);
                        printf("Enter the ID you want to delete:");
                        
                        char ch;
                        int pos = 0;
                        while ((ch = getchar()) != '\n')
                        {
                            name[pos] = ch;
                            pos++;
                        }
                        name[pos] = '\0';
                        delete_rankings(&L, name);
                        save_to_file(L);
                        
                        system("cls");
                        getOut = 0;
                    }
                }
            } 
        } while (getOut == 1);
    }
    return 0;
}

           
       
        
        
        
  
    
