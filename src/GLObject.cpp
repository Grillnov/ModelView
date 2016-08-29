//
//  GLObject.cpp
//  ModelView
//
//  Created by Haoyan Huo on 3/19/15.
//  Copyright (c) 2015 Haoyan Huo. All rights reserved.
//
//  Modified by Bowen Yang

# include "GLObject.h"
# include "GLApplication.h"

# ifdef _MSC_VER

# include <Windows.h>
HANDLE consoleH = nullptr;
WORD defaultAttr;
CONSOLE_SCREEN_BUFFER_INFO csbInfo;

# else

# define RESET_F "\033[0m"
# define PURPLE_F "\033[0;35m"
# define RED_F "\033[0;31m"
# define YELLOW_F "\033[0;33m"
# define GREEN_F "\033[0;32m"

# endif
// TODO: Add color to these titles shown on the console

void GLObject::CheckStatus(const char* function)
{
# ifndef DEBUGBUILD//Check errors during debug session only.
	return;
# endif
	GLenum error = glGetError();
	static bool firstCall = true;
	if (error != GL_NO_ERROR)
	{
		Warning(debugMsg, "Error spotted during the execution of function: %s!", function);
		Error(debugMsg, "Fatal OpenGL Error %d:\n %s", error, glewGetErrorString(error));
	}
}

void GLObject::Log(const char* file, unsigned line, const char* function, const char* msg, ...)
{
# ifndef LOGDEBUGMSG
	return;
# endif

	va_list ap;
# ifndef _MSC_VER
	printf(GREEN_F"[LOG]"RESET_F"[file: %s][at line: %u][at function: %s]: ", file, line, function);
# else
	if (!consoleH)
	{
		consoleH = GetStdHandle(STD_OUTPUT_HANDLE);
		GetConsoleScreenBufferInfo(consoleH, &csbInfo);
		defaultAttr = csbInfo.wAttributes;
	}
	SetConsoleTextAttribute(consoleH, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
	printf("[LOG]");
	SetConsoleTextAttribute(consoleH, defaultAttr);
	printf("[File: %s][Line: %u][Function: %s]: ", file, line, function);
# endif
	va_start(ap, msg);
	vprintf(msg, ap);
	printf("\n");
	va_end(ap);
}

void GLObject::Info(const char* file, unsigned line, const char* function, const char* msg, ...)
{
# ifndef LOGDEBUGMSG
	return;
# endif

	va_list ap;
# ifndef _MSC_VER
	printf(PURPLE_F"[LOG]"RESET_F"[file: %s][at line: %u][at function: %s]: ", file, line, function);
# else
	if (!consoleH)
	{
		consoleH = GetStdHandle(STD_OUTPUT_HANDLE);
		GetConsoleScreenBufferInfo(consoleH, &csbInfo);
		defaultAttr = csbInfo.wAttributes;
	}
	SetConsoleTextAttribute(consoleH, FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_INTENSITY);
	printf("[INFO]");
	SetConsoleTextAttribute(consoleH, defaultAttr);
	printf("[File: %s][Line: %u][Function: %s]: ", file, line, function);
# endif
	va_start(ap, msg);
	vprintf(msg, ap);
	printf("\n");
	va_end(ap);
}

void GLObject::Warning(const char* file, unsigned line, const char* function, const char* msg, ...)
{
	va_list ap;
# ifndef _MSC_VER
	printf(YELLOW_F"[LOG]"RESET_F"[file: %s][at line: %u][at function: %s]: ", file, line, function);
# else
	if (!consoleH)
	{
		consoleH = GetStdHandle(STD_OUTPUT_HANDLE);
		GetConsoleScreenBufferInfo(consoleH, &csbInfo);
		defaultAttr = csbInfo.wAttributes;
	}
	SetConsoleTextAttribute(consoleH, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY);
	printf("[WARNING]");
	SetConsoleTextAttribute(consoleH, defaultAttr);
	printf("[File: %s][Line: %u][Function: %s]: ", file, line, function);
# endif
	va_start(ap, msg);
	vprintf(msg, ap);
	printf("\n");
	va_end(ap);
}

void GLObject::Error(const char* file, unsigned line, const char* function, const char* msg, ...)
{
	va_list ap;
# ifndef _MSC_VER
	printf(RED_F"[LOG]"RESET_F"[file: %s][at line: %u][at function: %s]: ", file, line, function);
# else
	if (!consoleH)
	{
		consoleH = GetStdHandle(STD_OUTPUT_HANDLE);
		GetConsoleScreenBufferInfo(consoleH, &csbInfo);
		defaultAttr = csbInfo.wAttributes;
	}
	SetConsoleTextAttribute(consoleH, FOREGROUND_RED | FOREGROUND_INTENSITY);
	printf("[ERROR]");
	SetConsoleTextAttribute(consoleH, defaultAttr);
	printf("[File: %s][Line: %u][Function: %s]: ", file, line, function);
# endif
	va_start(ap, msg);
	vprintf(msg, ap);
	printf("\n");
	va_end(ap);

	char numb = 0;
	
	while (numb != 'y' && numb != 'Y')
	{
		Info(debugMsg, "\nContinue with this operation anyway? (y/n)\n");
		std::cin >> numb;
		if (numb == 'n' || numb == 'N')
			exit(-1);
	}
	//FIXME: is this error checking function performing what it's supposed to perform?
}