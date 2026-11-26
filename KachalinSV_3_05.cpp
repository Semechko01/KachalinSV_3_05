

#include <iostream>
#include <string>
#include <stdexcept>
#include <fstream>
#include <Windows.h>




int main() {
    setlocale(LC_ALL, "Russian");
    LPCSTR name = "sema";
    int maxInstances = 2;

    HANDLE sema = CreateSemaphoreA(NULL, maxInstances, maxInstances, name);
    if (sema == NULL) {
        std::cout << "Ошибка создания семафора. Код: " << GetLastError() << std::endl;
        return 1;
    }
    DWORD res = WaitForSingleObject(sema, 0);

    if (res == WAIT_TIMEOUT) {
        std::cout << "Превышено количество копий завершение работы...\n";
        CloseHandle(sema);
        Sleep(2000);
        return 1;
    }
    else if (res == WAIT_OBJECT_0) {
        std::cout << "Программа запусилась\n";
        std::cout << "Нажмите Enter для завершения\n";
        std::cin.get();
        ReleaseSemaphore(sema, 1, NULL);
        CloseHandle(sema);
    }
    else {
        std::cout << "Ошибка: " << GetLastError() << std::endl;
        CloseHandle(sema);
        return 1;
    }

    return 0;
}

