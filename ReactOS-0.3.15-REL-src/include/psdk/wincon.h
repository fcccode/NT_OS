#ifndef _WINCON_H
#define _WINCON_H

#ifdef __cplusplus
extern "C" {
#endif

#if (_WIN32_WINNT >= 0x0600) && !defined(NOGDI)
#  include "wingdi.h"
#endif

#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable:4820)
#endif

#define FOREGROUND_BLUE	1
#define FOREGROUND_GREEN	2
#define FOREGROUND_RED	4
#define FOREGROUND_INTENSITY	8
#define BACKGROUND_BLUE	16
#define BACKGROUND_GREEN	32
#define BACKGROUND_RED	64
#define BACKGROUND_INTENSITY	128
#define CTRL_C_EVENT 0
#define CTRL_BREAK_EVENT 1
#define CTRL_CLOSE_EVENT 2
#define CTRL_LOGOFF_EVENT 5
#define CTRL_SHUTDOWN_EVENT 6
#define ENABLE_LINE_INPUT 2
#define ENABLE_ECHO_INPUT 4
#define ENABLE_PROCESSED_INPUT 1
#define ENABLE_WINDOW_INPUT 8
#define ENABLE_MOUSE_INPUT 16
#define ENABLE_PROCESSED_OUTPUT 1
#define ENABLE_WRAP_AT_EOL_OUTPUT 2
#define KEY_EVENT 1
#define MOUSE_EVENT 2
#define WINDOW_BUFFER_SIZE_EVENT 4
#define MENU_EVENT 8
#define FOCUS_EVENT 16
#define CAPSLOCK_ON 128
#define ENHANCED_KEY 256
#define RIGHT_ALT_PRESSED 1
#define LEFT_ALT_PRESSED 2
#define RIGHT_CTRL_PRESSED 4
#define LEFT_CTRL_PRESSED 8
#define SHIFT_PRESSED 16
#define NUMLOCK_ON 32
#define SCROLLLOCK_ON 64
#define FROM_LEFT_1ST_BUTTON_PRESSED 1
#define RIGHTMOST_BUTTON_PRESSED 2
#define FROM_LEFT_2ND_BUTTON_PRESSED 4
#define FROM_LEFT_3RD_BUTTON_PRESSED 8
#define FROM_LEFT_4TH_BUTTON_PRESSED 16
#define MOUSE_MOVED	1
#define DOUBLE_CLICK	2
#define MOUSE_WHEELED	4

typedef struct _CONSOLE_READCONSOLE_CONTROL {
    ULONG nLength;
    ULONG nInitialChars;
    ULONG dwCtrlWakeupMask;
    ULONG dwControlKeyState;
} CONSOLE_READCONSOLE_CONTROL, *PCONSOLE_READCONSOLE_CONTROL;

typedef struct _CHAR_INFO {
	union {
		WCHAR UnicodeChar;
		CHAR AsciiChar;
	} Char;
	WORD Attributes;
} CHAR_INFO,*PCHAR_INFO;
typedef struct _SMALL_RECT {
	SHORT Left;
	SHORT Top;
	SHORT Right;
	SHORT Bottom;
} SMALL_RECT,*PSMALL_RECT;
typedef struct _CONSOLE_CURSOR_INFO {
	DWORD	dwSize;
	BOOL	bVisible;
} CONSOLE_CURSOR_INFO,*PCONSOLE_CURSOR_INFO;
typedef struct _COORD {
	SHORT X;
	SHORT Y;
} COORD, *PCOORD;
typedef struct _CONSOLE_SELECTION_INFO {
  DWORD dwFlags;
  COORD dwSelectionAnchor;
  SMALL_RECT srSelection;
} CONSOLE_SELECTION_INFO, *PCONSOLE_SELECTION_INFO;
typedef struct _CONSOLE_FONT_INFO {
	DWORD nFont;
	COORD dwFontSize;
} CONSOLE_FONT_INFO, *PCONSOLE_FONT_INFO;
typedef struct _CONSOLE_SCREEN_BUFFER_INFO {
	COORD	dwSize;
	COORD	dwCursorPosition;
	WORD	wAttributes;
	SMALL_RECT srWindow;
	COORD	dwMaximumWindowSize;
} CONSOLE_SCREEN_BUFFER_INFO,*PCONSOLE_SCREEN_BUFFER_INFO;
typedef BOOL(CALLBACK *PHANDLER_ROUTINE)(_In_ DWORD);
typedef struct _KEY_EVENT_RECORD {
	BOOL bKeyDown;
	WORD wRepeatCount;
	WORD wVirtualKeyCode;
	WORD wVirtualScanCode;
	union {
		WCHAR UnicodeChar;
		CHAR AsciiChar;
	} uChar;
	DWORD dwControlKeyState;
}
#ifdef __GNUC__
/* gcc's alignment is not what win32 expects */
 PACKED
#endif
KEY_EVENT_RECORD;
typedef struct _MOUSE_EVENT_RECORD {
	COORD dwMousePosition;
	DWORD dwButtonState;
	DWORD dwControlKeyState;
	DWORD dwEventFlags;
} MOUSE_EVENT_RECORD;
typedef struct _WINDOW_BUFFER_SIZE_RECORD {	COORD dwSize; } WINDOW_BUFFER_SIZE_RECORD;
typedef struct _MENU_EVENT_RECORD {	UINT dwCommandId; } MENU_EVENT_RECORD,*PMENU_EVENT_RECORD;
typedef struct _FOCUS_EVENT_RECORD { BOOL bSetFocus; } FOCUS_EVENT_RECORD;
typedef struct _INPUT_RECORD {
	WORD EventType;
	union {
		KEY_EVENT_RECORD KeyEvent;
		MOUSE_EVENT_RECORD MouseEvent;
		WINDOW_BUFFER_SIZE_RECORD WindowBufferSizeEvent;
		MENU_EVENT_RECORD MenuEvent;
		FOCUS_EVENT_RECORD FocusEvent;
	} Event;
} INPUT_RECORD,*PINPUT_RECORD;

#if (_WIN32_WINNT >= 0x0600)
#define HISTORY_NO_DUP_FLAG 0x1
#define CONSOLE_OVERSTRIKE  0x1

typedef struct _CONSOLE_HISTORY_INFO {
    UINT cbSize;
    UINT HistoryBufferSize;
    UINT NumberOfHistoryBuffers;
    DWORD dwFlags;
} CONSOLE_HISTORY_INFO, *PCONSOLE_HISTORY_INFO;

typedef struct _CONSOLE_SCREEN_BUFFER_INFOEX {
    ULONG cbSize;
    COORD dwSize;
    COORD dwCursorPosition;
    WORD wAttributes;
    SMALL_RECT srWindow;
    COORD dwMaximumWindowSize;
    WORD wPopupAttributes;
    COLORREF ColorTable[16];
} CONSOLE_SCREEN_BUFFER_INFOEX, *PCONSOLE_SCREEN_BUFFER_INFOEX;

#ifndef NOGDI
typedef struct _CONSOLE_FONT_INFOEX {
    ULONG cbSize;
    DWORD nFont;
    COORD dwFontSize;
    UINT FontFamily;
    UINT FontWeight;
    WCHAR FaceName[LF_FACESIZE];
} CONSOLE_FONT_INFOEX, *PCONSOLE_FONT_INFOEX;
#endif
#endif

BOOL WINAPI AllocConsole(void);
#if (_WIN32_WINNT >= 0x0501)
#define ATTACH_PARENT_PROCESS (DWORD)-1
BOOL WINAPI AttachConsole(_In_ DWORD);
BOOL WINAPI AddConsoleAliasA(_In_ LPCSTR, _In_ LPCSTR, _In_ LPCSTR);
BOOL WINAPI AddConsoleAliasW(_In_ LPCWSTR, _In_ LPCWSTR, _In_ LPCWSTR);

DWORD
WINAPI
GetConsoleAliasA(
  _In_ LPSTR Source,
  _Out_writes_(TargetBufferLength) LPSTR TargetBuffer,
  _In_ DWORD TargetBufferLength,
  _In_ LPSTR ExeName);

DWORD
WINAPI
GetConsoleAliasW(
  _In_ LPWSTR Source,
  _Out_writes_(TargetBufferLength) LPWSTR TargetBuffer,
  _In_ DWORD TargetBufferLength,
  _In_ LPWSTR ExeName);

DWORD
WINAPI
GetConsoleAliasesA(
  _Out_writes_(AliasBufferLength) LPSTR AliasBuffer,
  _In_ DWORD AliasBufferLength,
  _In_ LPSTR ExeName);

DWORD
WINAPI
GetConsoleAliasesW(
  _Out_writes_(AliasBufferLength) LPWSTR AliasBuffer,
  _In_ DWORD AliasBufferLength,
  _In_ LPWSTR ExeName);

DWORD WINAPI GetConsoleAliasesLengthA(_In_ LPSTR);
DWORD WINAPI GetConsoleAliasesLengthW(_In_ LPWSTR);
#endif
HANDLE WINAPI CreateConsoleScreenBuffer(_In_ DWORD, _In_ DWORD, _In_opt_ CONST SECURITY_ATTRIBUTES*, _In_ DWORD, _Reserved_ LPVOID);
BOOL WINAPI FillConsoleOutputAttribute(_In_ HANDLE, _In_ WORD, _In_ DWORD, _In_ COORD, _Out_ PDWORD);
BOOL WINAPI FillConsoleOutputCharacterA(_In_ HANDLE, _In_ CHAR, _In_ DWORD, _In_ COORD, _Out_ PDWORD);
BOOL WINAPI FillConsoleOutputCharacterW(_In_ HANDLE, _In_ WCHAR, _In_ DWORD, _In_ COORD, _Out_ PDWORD);
BOOL WINAPI FlushConsoleInputBuffer(_In_ HANDLE);
BOOL WINAPI FreeConsole(void);
BOOL WINAPI GenerateConsoleCtrlEvent(_In_ DWORD, _In_ DWORD);
UINT WINAPI GetConsoleCP(void);
BOOL WINAPI GetConsoleCursorInfo(_In_ HANDLE, _Out_ PCONSOLE_CURSOR_INFO);
BOOL WINAPI GetConsoleMode(HANDLE,PDWORD);
UINT WINAPI GetConsoleOutputCP(void);
BOOL WINAPI GetConsoleScreenBufferInfo(_In_ HANDLE, _Out_ PCONSOLE_SCREEN_BUFFER_INFO);

DWORD
WINAPI
GetConsoleTitleA(
  _Out_writes_(nSize) LPSTR lpConsoleTitle,
  _In_ DWORD nSize);

DWORD
WINAPI
GetConsoleTitleW(
  _Out_writes_(nSize) LPWSTR lpConsoleTitle,
  _In_ DWORD nSize);

#if (_WIN32_WINNT >= 0x0500)
HWND WINAPI GetConsoleWindow(void);
WINBASEAPI BOOL APIENTRY GetConsoleDisplayMode(_Out_ LPDWORD lpModeFlags);
BOOL APIENTRY SetConsoleDisplayMode(_In_ HANDLE hConsoleOutput, _In_ DWORD dwFlags, _Out_opt_ PCOORD lpNewScreenBufferDimensions);
#endif
COORD WINAPI GetLargestConsoleWindowSize(_In_ HANDLE);
BOOL WINAPI GetNumberOfConsoleInputEvents(HANDLE,PDWORD);
BOOL WINAPI GetNumberOfConsoleMouseButtons(_Out_ PDWORD);
BOOL WINAPI PeekConsoleInputA(HANDLE,PINPUT_RECORD,DWORD,PDWORD);

BOOL
WINAPI
PeekConsoleInputW(
  _In_ HANDLE hConsoleInput,
  _Out_writes_(nLength) PINPUT_RECORD lpBuffer,
  _In_ DWORD nLength,
  _Out_ LPDWORD lpNumberOfEventsRead);

BOOL WINAPI ReadConsoleA(HANDLE,PVOID,DWORD,PDWORD,PCONSOLE_READCONSOLE_CONTROL);
BOOL WINAPI ReadConsoleW(HANDLE,PVOID,DWORD,PDWORD,PCONSOLE_READCONSOLE_CONTROL);
BOOL WINAPI ReadConsoleInputA(HANDLE,PINPUT_RECORD,DWORD,PDWORD);
BOOL WINAPI ReadConsoleInputW(HANDLE,PINPUT_RECORD,DWORD,PDWORD);

BOOL
WINAPI
ReadConsoleOutputAttribute(
  _In_ HANDLE hConsoleOutput,
  _Out_writes_(nLength) LPWORD lpAttribute,
  _In_ DWORD nLength,
  _In_ COORD dwReadCoord,
  _Out_ LPDWORD lpNumberOfAttrsRead);

BOOL
WINAPI
ReadConsoleOutputCharacterA(
  _In_ HANDLE hConsoleOutput,
  _Out_writes_(nLength) LPSTR lpCharacter,
  _In_ DWORD nLength,
  _In_ COORD dwReadCoord,
  _Out_ LPDWORD lpNumberOfCharsRead);

BOOL
WINAPI
ReadConsoleOutputCharacterW(
  _In_ HANDLE hConsoleOutput,
  _Out_writes_(nLength) LPWSTR lpCharacter,
  _In_ DWORD nLength,
  _In_ COORD dwReadCoord,
  _Out_ LPDWORD lpNumberOfCharsRead);

BOOL
WINAPI
ReadConsoleOutputA(
  _In_ HANDLE hConsoleOutput,
  _Out_writes_(dwBufferSize.X * dwBufferSize.Y) PCHAR_INFO lpBuffer,
  _In_ COORD dwBufferSize,
  _In_ COORD dwBufferCoord,
  _Inout_ PSMALL_RECT lpReadRegion);

BOOL
WINAPI
ReadConsoleOutputW(
  _In_ HANDLE hConsoleOutput,
  _Out_writes_(dwBufferSize.X * dwBufferSize.Y) PCHAR_INFO lpBuffer,
  _In_ COORD dwBufferSize,
  _In_ COORD dwBufferCoord,
  _Inout_ PSMALL_RECT lpReadRegion);

BOOL WINAPI ScrollConsoleScreenBufferA(_In_ HANDLE, _In_ const SMALL_RECT*, _In_opt_ const SMALL_RECT*, _In_ COORD, _In_ const CHAR_INFO*);
BOOL WINAPI ScrollConsoleScreenBufferW(_In_ HANDLE, _In_ const SMALL_RECT*, _In_opt_ const SMALL_RECT*, _In_ COORD, _In_ const CHAR_INFO*);
BOOL WINAPI SetConsoleActiveScreenBuffer(_In_ HANDLE);
BOOL WINAPI SetConsoleCP(_In_ UINT);
BOOL WINAPI SetConsoleCtrlHandler(PHANDLER_ROUTINE,BOOL);
BOOL WINAPI SetConsoleCursorInfo(_In_ HANDLE, _In_ const CONSOLE_CURSOR_INFO*);
BOOL WINAPI SetConsoleCursorPosition(_In_ HANDLE, _In_ COORD);
BOOL WINAPI SetConsoleMode(HANDLE,DWORD);
BOOL WINAPI SetConsoleOutputCP(_In_ UINT);
BOOL WINAPI SetConsoleScreenBufferSize(_In_ HANDLE, _In_ COORD);
BOOL WINAPI SetConsoleTextAttribute(_In_ HANDLE, _In_ WORD);
BOOL WINAPI SetConsoleTitleA(_In_ LPCSTR);
BOOL WINAPI SetConsoleTitleW(_In_ LPCWSTR);
BOOL WINAPI SetConsoleWindowInfo(_In_ HANDLE, _In_ BOOL, _In_ const SMALL_RECT*);
BOOL WINAPI WriteConsoleA(HANDLE,CONST VOID*,DWORD,LPDWORD,LPVOID);
BOOL WINAPI WriteConsoleW(HANDLE,CONST VOID*,DWORD,LPDWORD,LPVOID);

BOOL
WINAPI
WriteConsoleInputA(
  _In_ HANDLE hConsoleInput,
  _In_reads_(nLength) CONST INPUT_RECORD *lpBuffer,
  _In_ DWORD nLength,
  _Out_ LPDWORD lpNumberOfEventsWritten);

BOOL
WINAPI
WriteConsoleInputW(
  _In_ HANDLE hConsoleInput,
  _In_reads_(nLength) CONST INPUT_RECORD *lpBuffer,
  _In_ DWORD nLength,
  _Out_ LPDWORD lpNumberOfEventsWritten);

BOOL
WINAPI
WriteConsoleOutputA(
  _In_ HANDLE hConsoleOutput,
  _In_reads_(dwBufferSize.X * dwBufferSize.Y) CONST CHAR_INFO *lpBuffer,
  _In_ COORD dwBufferSize,
  _In_ COORD dwBufferCoord,
  _Inout_ PSMALL_RECT lpWriteRegion);

BOOL
WINAPI
WriteConsoleOutputW(
  _In_ HANDLE hConsoleOutput,
  _In_reads_(dwBufferSize.X * dwBufferSize.Y) CONST CHAR_INFO *lpBuffer,
  _In_ COORD dwBufferSize,
  _In_ COORD dwBufferCoord,
  _Inout_ PSMALL_RECT lpWriteRegion);

BOOL
WINAPI
WriteConsoleOutputAttribute(
  _In_ HANDLE hConsoleOutput,
  _In_reads_(nLength) CONST WORD *lpAttribute,
  _In_ DWORD nLength,
  _In_ COORD dwWriteCoord,
  _Out_ LPDWORD lpNumberOfAttrsWritten);

BOOL
WINAPI
WriteConsoleOutputCharacterA(
  _In_ HANDLE hConsoleOutput,
  _In_reads_(nLength) LPCSTR lpCharacter,
  _In_ DWORD nLength,
  _In_ COORD dwWriteCoord,
  _Out_ LPDWORD lpNumberOfCharsWritten);

BOOL
WINAPI
WriteConsoleOutputCharacterW(
  _In_ HANDLE hConsoleOutput,
  _In_reads_(nLength) LPCWSTR lpCharacter,
  _In_ DWORD nLength,
  _In_ COORD dwWriteCoord,
  _Out_ LPDWORD lpNumberOfCharsWritten);

#define CONSOLE_FULLSCREEN 1
#define CONSOLE_FULLSCREEN_HARDWARE 2
#define CONSOLE_FULLSCREEN_MODE 1
#define CONSOLE_WINDOWED_MODE 2

#ifdef UNICODE
#define FillConsoleOutputCharacter FillConsoleOutputCharacterW
#define AddConsoleAlias AddConsoleAliasW
#define GetConsoleAlias GetConsoleAliasW
#define GetConsoleAliases GetConsoleAliasesW
#define GetConsoleAliasesLength GetConsoleAliasesLengthW
#define GetConsoleTitle GetConsoleTitleW
#define PeekConsoleInput PeekConsoleInputW
#define ReadConsole ReadConsoleW
#define ReadConsoleInput ReadConsoleInputW
#define ReadConsoleOutput ReadConsoleOutputW
#define ReadConsoleOutputCharacter ReadConsoleOutputCharacterW
#define ScrollConsoleScreenBuffer ScrollConsoleScreenBufferW
#define SetConsoleTitle SetConsoleTitleW
#define WriteConsole WriteConsoleW
#define WriteConsoleInput WriteConsoleInputW
#define WriteConsoleOutput WriteConsoleOutputW
#define WriteConsoleOutputCharacter WriteConsoleOutputCharacterW
#else
#define AddConsoleAlias AddConsoleAliasA
#define FillConsoleOutputCharacter FillConsoleOutputCharacterA
#define GetConsoleAlias GetConsoleAliasA
#define GetConsoleAliases GetConsoleAliasesA
#define GetConsoleAliasesLength GetConsoleAliasesLengthA
#define GetConsoleTitle GetConsoleTitleA
#define PeekConsoleInput PeekConsoleInputA
#define ReadConsole ReadConsoleA
#define ReadConsoleInput ReadConsoleInputA
#define ReadConsoleOutput ReadConsoleOutputA
#define ReadConsoleOutputCharacter ReadConsoleOutputCharacterA
#define ScrollConsoleScreenBuffer ScrollConsoleScreenBufferA
#define SetConsoleTitle SetConsoleTitleA
#define WriteConsole WriteConsoleA
#define WriteConsoleInput WriteConsoleInputA
#define WriteConsoleOutput WriteConsoleOutputA
#define WriteConsoleOutputCharacter WriteConsoleOutputCharacterA
#endif

#ifdef _MSC_VER
#pragma warning(pop)
#endif

#ifdef __cplusplus
}
#endif
#endif
