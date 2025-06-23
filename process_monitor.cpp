#include <windows.h>
#include <tlhelp32.h>
#include <string>
#include <sstream>

#define ID_LISTBOX 101

const char CLASS_NAME[] = "ProcessMonitorWindow";
HWND hListBox;  // ListBox handle (global for now)

// Function to fetch and display processes
void PopulateProcessList(HWND hList) {
    SendMessage(hList, LB_RESETCONTENT, 0, 0); // Clear listbox

    HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (hSnapshot == INVALID_HANDLE_VALUE) {
        MessageBox(NULL, "Failed to take process snapshot.", "Error", MB_OK);
        return;
    }

    PROCESSENTRY32 pe32;
    pe32.dwSize = sizeof(PROCESSENTRY32);

    if (Process32First(hSnapshot, &pe32)) {
        do {
            std::wstringstream ss;
            ss << pe32.th32ProcessID << L"  -  " << pe32.szExeFile;
            std::wstring entry = ss.str();

            // Add to ListBox
            SendMessageW(hList, LB_ADDSTRING, 0, (LPARAM)entry.c_str());

        } while (Process32Next(hSnapshot, &pe32));
    }

    CloseHandle(hSnapshot);
}

// Handle window messages
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {

    case WM_CREATE:
        // Create a ListBox inside the window
        hListBox = CreateWindowEx(WS_EX_CLIENTEDGE, "LISTBOX", NULL,
            WS_CHILD | WS_VISIBLE | WS_VSCROLL | LBS_NOTIFY,
            20, 20, 540, 300, hwnd, (HMENU)ID_LISTBOX,
            GetModuleHandle(NULL), NULL);

        // Populate the list
        PopulateProcessList(hListBox);
        return 0;

    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    }

    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

// Entry point
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
                   LPSTR lpCmdLine, int nCmdShow) {

    WNDCLASS wc = {};
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = CLASS_NAME;
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);

    RegisterClass(&wc);

    HWND hwnd = CreateWindowEx(0, CLASS_NAME, "Process Monitor (GUI)",
        WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 600, 400,
        NULL, NULL, hInstance, NULL);

    if (!hwnd) return 0;

    ShowWindow(hwnd, nCmdShow);

    // Message loop
    MSG msg = {};
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}
