#include <windows.h>
#include <tlhelp32.h>
#include <iostream>

int main() {
    HANDLE hProcessSnap;
    PROCESSENTRY32 pe32;

    // Take a snapshot of all processes in the system
    hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

    if (hProcessSnap == INVALID_HANDLE_VALUE) {
        std::cerr << "Failed to take snapshot." << std::endl;
        return 1;
    }

    pe32.dwSize = sizeof(PROCESSENTRY32);

    // Get the first process
    if (!Process32First(hProcessSnap, &pe32)) {
        std::cerr << "Failed to get first process." << std::endl;
        CloseHandle(hProcessSnap);
        return 1;
    }

    std::cout << "PID\t\tProcess Name\n";
    std::cout << "------------------------------\n";

    do {
        std::wcout << pe32.th32ProcessID << "\t\t" << pe32.szExeFile << std::endl;
    } while (Process32Next(hProcessSnap, &pe32));

    CloseHandle(hProcessSnap);
    return 0;
}
