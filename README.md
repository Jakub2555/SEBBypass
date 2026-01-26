# SEB Bypass

## About
This is a simple, easily expandable proof of concept demonstrating how to bypass some of the security mechanisms of [Safe Exam Browser](https://safeexambrowser.org/news_en.html) in order to completely hide a process from it. This allows forbidden software to run while SEB is active. It is very bare-bones and does not provide any advantage during exams.

## Features
- Hides the target process from being queried
- Hides windows of the target process
- Disables capture of keyboard and mouse input
- Prevents `WDA_EXCLUDEFROMCAPTURE` from being set, allowing capture of SEB windows
- ~~Hide window of target process from being captured in screenshots/recording~~

## How to Build
1. Install CMake, Ninja, and Clang
2. Run `BuildDebug.bat` or `BuildRelease.bat` to build the project
3. Inject `sebbypass.dll` into `SafeExamBrowser.Client.exe`

## Credits
- [MinHook (hooking library)](https://github.com/TsudaKageyu/minhook)

## Disclaimer
This project is purely for educational purposes and is not allowed during exams.