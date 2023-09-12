// ConsoleApplication1.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>
#include <conio.h> // _getch 함수를 사용하기 위한 헤더 파일

int main() {
    char choice;

    while (true) {
        std::cout << "\t12312314\n";
        std::cout << "\t이은석님의\n";
        std::cout << "\tApplication\n";

        std::cout << "command> ";
        choice = _getch(); // 사용자 입력을 바로 읽어옴

        if (choice == 27) { // ESC 키를 누르면 프로그램 종료
            std::cout << "프로그램을 종료합니다.\n";
            break; // 루프를 종료하여 프로그램 종료
        }

        switch (choice) {
        case 'p':
            std::cout << "나는 과제를 겁나 잘하는 학생이다\n";
            break;
        case 'f':
            std::cout << "나는 과제가 너무 즐겁다\n";
            break;
        case 'j':
            std::cout << "교수님 과제 더 내주세요\n";
            break;
        default:
            std::cout << "잘못된 입력입니다. 다시 시도하세요.\n";
            break;
        }
    }

    return 0;
}



// 프로그램 실행: <Ctrl+F5> 또는 [디버그] > [디버깅하지 않고 시작] 메뉴
// 프로그램 디버그: <F5> 키 또는 [디버그] > [디버깅 시작] 메뉴

// 시작을 위한 팁: 
//   1. [솔루션 탐색기] 창을 사용하여 파일을 추가/관리합니다.
//   2. [팀 탐색기] 창을 사용하여 소스 제어에 연결합니다.
//   3. [출력] 창을 사용하여 빌드 출력 및 기타 메시지를 확인합니다.
//   4. [오류 목록] 창을 사용하여 오류를 봅니다.
//   5. [프로젝트] > [새 항목 추가]로 이동하여 새 코드 파일을 만들거나, [프로젝트] > [기존 항목 추가]로 이동하여 기존 코드 파일을 프로젝트에 추가합니다.
//   6. 나중에 이 프로젝트를 다시 열려면 [파일] > [열기] > [프로젝트]로 이동하고 .sln 파일을 선택합니다.
