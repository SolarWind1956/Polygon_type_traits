//	color_output.hpp
#pragma once
#include <string>
#if defined(_WIN32)
#include <windows.h>
#endif
/*
	
blue 		- 	информационный заголовок

cyan 		- 	нейтральное оформление

yellow 		- 	внимание

green 		- 	успех

Красный 	-	ошибками/предупреждениями.
*/
/*
Structure of an ANSI Code

An ANSI escape sequence always starts with an Escape character, 
often represented as \033 (octal), \x1b (hexadecimal), or \e in some contexts (like bash). 

This is followed by an opening square bracket `[`, 
one or more parameters separated by semicolons `;`, 
and finally the letter `m`. 

A common sequence looks like \x1b[...m. 

Common ANSI Color Codes
The most common colors involve 8 basic colors and their "bright" 
variations for both foreground (text) and background. 
-------------------------------------------------------------------------------------------------------------------------------------------------------
Color 		Foreground Code		Background Code		Bright Foreground		Bright Background
-------------------------------------------------------------------------------------------------------------------------------------------------------
Black		30					40					90					100
Red			31					41					91					101
Green		32					42					92					102
Yellow		33					43					93					103
Blue			34					44					94					104
Magenta		35					45					95					105
Cyan		36					46					96					106
White		37					47					97					107

Reset		0					0					0					0
-------------------------------------------------------------------------------------------------------------------------------------------------------

Other Formatting Codes
ANSI codes can also be used for text styles: 

0: 	Reset/Normal (resets all styles and colors)
1: 	Bold/Bright
4: 	Underline
7: 	Inverse/Reverse (swaps foreground and background colors) 

Example Usage (in Bash/Python)
To use these codes, you embed them within your output string. 
*/
namespace color_output {
	// ============================================================
    //  1) Состояние поддержки ANSI
    // ============================================================
    inline bool ansi_enabled 		= false;
    inline bool winapi_enabled 	= false;

    // ============================================================
    //  2) Включение поддержки ANSI под Windows
    // ============================================================
    
	inline void enable_ansi_for_windows() {
#if defined(_WIN32)
        HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
        if (hOut == INVALID_HANDLE_VALUE) return;

        DWORD dwMode = 0;
        if (!GetConsoleMode(hOut, &dwMode)) return;

        dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
        if (SetConsoleMode(hOut, dwMode))
            ansi_enabled = true;
#endif
    }

    // ============================================================
    //  3) Проверяем: stdout → терминал?
    // ============================================================
    inline bool is_stdout_terminal() {
#if defined(_WIN32)
        DWORD mode = 0;
        return GetConsoleMode(GetStdHandle(STD_OUTPUT_HANDLE), &mode);
#else
        return isatty(fileno(stdout));
#endif
    }
    // ============================================================
    //  4) Инициализация цветовой подсистемы
    // ============================================================
    inline void init() {
        if (!is_stdout_terminal()) {
            ansi_enabled 	= false;
            winapi_enabled 	= false;
            return;
        }

#if defined(_WIN32)
    
		enable_ansi_for_windows();

        if (!ansi_enabled) {
            winapi_enabled = true;
        }
#else
        ansi_enabled = true;
#endif
    }

    // ============================================================
    //  5) WinAPI обработчик цвета
    // ============================================================
#if defined(_WIN32)
    inline void set_win_color(WORD color) {
        if (winapi_enabled) {
            HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
            SetConsoleTextAttribute(h, color);
        }
    }
#endif

    // ============================================================
    //  6) Класс-манипулятор ANSI/WinAPI
    // ============================================================
    struct Color {
        int ansi_code;

#if defined(_WIN32)
        WORD win_color;
#endif

        Color(int ansi, 
#if defined(_WIN32)
              WORD win
#else
              int
#endif
        )
            : ansi_code(ansi)
#if defined(_WIN32)
            , win_color(win)
#endif
        {}

        friend std::ostream& operator<<(std::ostream& os, const Color& c) {
            if (ansi_enabled) {
                os << "\033[" << c.ansi_code << "m";
            }
#if defined(_WIN32)
            else if (winapi_enabled) {
                set_win_color(c.win_color);
            }
#endif
            return os;
        }
    };

    // ============================================================
    //  Цветовые константы (ANSI + WinAPI соответствия)
    // ============================================================
    inline const Color reset   		{	0,
#if defined(_WIN32)
										7
#endif
    };
	//	-------------- black ----------------------------------------------------------------------------------------------------------------
    inline const Color black   		{	30,
#if defined(_WIN32)
										0
#endif
    };

	inline const Color bright_black   {	90,
#if defined(_WIN32)
										0 | FOREGROUND_INTENSITY
#endif
    };
	//	-------------- red ----------------------------------------------------------------------------------------------------------------
    inline const Color red     		{	31,
#if defined(_WIN32)
										FOREGROUND_RED
#endif
    };

	inline const Color bright_red     {	91,
#if defined(_WIN32)
										FOREGROUND_RED | FOREGROUND_INTENSITY
#endif
    };
	//	-------------- green ----------------------------------------------------------------------------------------------------------------
    inline const Color green   		{	32,
#if defined(_WIN32)
										FOREGROUND_GREEN
#endif
    };

	inline const Color bright_green   {	92,
#if defined(_WIN32)
										FOREGROUND_GREEN | FOREGROUND_INTENSITY
#endif
    };
	//	-------------- yellow ----------------------------------------------------------------------------------------------------------------
    inline const Color yellow  		{	33,
#if defined(_WIN32)
										FOREGROUND_RED | FOREGROUND_GREEN
#endif
    };
	
	inline const Color bright_yellow  {	93,
#if defined(_WIN32)
										FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY
#endif
    };
	//	-------------- blue ----------------------------------------------------------------------------------------------------------------
    inline const Color blue    		{	34,
#if defined(_WIN32)
										FOREGROUND_BLUE
#endif
    };

	inline const Color bright_blue    {	34,
#if defined(_WIN32)
										FOREGROUND_BLUE | FOREGROUND_INTENSITY
#endif
    };
	//	-------------- magenta ----------------------------------------------------------------------------------------------------------------
    inline const Color magenta 		{	35,
#if defined(_WIN32)
										FOREGROUND_RED | FOREGROUND_BLUE
#endif
    };

	inline const Color bright_magenta {	95,
#if defined(_WIN32)
										FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY
#endif
    };
	//	-------------- cyan ----------------------------------------------------------------------------------------------------------------
    inline const Color cyan    		{	36,
#if defined(_WIN32)
										FOREGROUND_GREEN | FOREGROUND_BLUE
#endif
    };

	inline const Color bright_cyan    {	96,
#if defined(_WIN32)
										FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY
#endif
    };
	//	-------------- white ----------------------------------------------------------------------------------------------------------------
    inline const Color white   		{	37,
#if defined(_WIN32)
										FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE
#endif
    };
	
	inline const Color bright_white   {	97,
#if defined(_WIN32)
										FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY
#endif
	//	-------------- end of colors --------------------------------------------------------------------------------------------------------
    };
}	//	end of `namespace color_output`
