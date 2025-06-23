# 🪟 Windows Process Monitor (C++ Win32 GUI)

A simple Windows desktop application written in **C++ using the Win32 API**, which displays all currently running processes in a GUI window. This project demonstrates how to interact with the Windows OS at the API level and build native GUI applications using C++ — a great starting point for future system programming or driver development.

---

## 🚀 Features

- 🧠 Uses `CreateToolhelp32Snapshot` to list running processes
- 🪟 Native GUI using `WinMain` and `CreateWindowEx`
- 📋 Displays Process ID and Executable Name in a scrollable `ListBox`
- 🔁 Easily extendable with "Refresh" and "Kill" buttons (coming soon)

---

## 🛠️ Requirements

- Windows 10 or 11
- [MSYS2](https://www.msys2.org/) with UCRT64 environment
- `g++` compiler (`mingw-w64-ucrt-x86_64-gcc`)

---

## 🧑‍💻 How to Build

### 🧱 1. Install MSYS2 + Toolchain

Open **MSYS2 UCRT64 terminal** and run:

```bash
pacman -S --needed base-devel mingw-w64-ucrt-x86_64-toolchain
