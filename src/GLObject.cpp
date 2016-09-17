//
//  GLObject.cpp
//  ModelView
//
//  Created by Haoyan Huo on 3/19/15.
//  Copyright (c) 2015 Haoyan Huo. All rights reserved.
//
//  Modified by Bowen Yang

# include <GLObject.h>
# include <GLApplication.h>

# ifdef _MSC_VER

HANDLE consoleH = nullptr;
WORD defaultAttr;
CONSOLE_SCREEN_BUFFER_INFO csbInfo;

void consoleLogGreen()
{
	if (!consoleH)
	{
		consoleH = GetStdHandle(STD_OUTPUT_HANDLE);
		GetConsoleScreenBufferInfo(consoleH, &csbInfo);
		defaultAttr = csbInfo.wAttributes;
	}
	SetConsoleTextAttribute(consoleH, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
}

void consoleInfoPink()
{
	if (!consoleH)
	{
		consoleH = GetStdHandle(STD_OUTPUT_HANDLE);
		GetConsoleScreenBufferInfo(consoleH, &csbInfo);
		defaultAttr = csbInfo.wAttributes;
	}
	SetConsoleTextAttribute(consoleH, FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_INTENSITY);
}

void consoleWarningYellow()
{
	if (!consoleH)
	{
		consoleH = GetStdHandle(STD_OUTPUT_HANDLE);
		GetConsoleScreenBufferInfo(consoleH, &csbInfo);
		defaultAttr = csbInfo.wAttributes;
	}
	SetConsoleTextAttribute(consoleH, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY);
}

void consoleErrorRed()
{
	if (!consoleH)
	{
		consoleH = GetStdHandle(STD_OUTPUT_HANDLE);
		GetConsoleScreenBufferInfo(consoleH, &csbInfo);
		defaultAttr = csbInfo.wAttributes;
	}
	SetConsoleTextAttribute(consoleH, FOREGROUND_RED | FOREGROUND_INTENSITY);
}

void consoleDefaultWhite()
{
	if (!consoleH)
	{
		consoleH = GetStdHandle(STD_OUTPUT_HANDLE);
		GetConsoleScreenBufferInfo(consoleH, &csbInfo);
		defaultAttr = csbInfo.wAttributes;
	}
	SetConsoleTextAttribute(consoleH, defaultAttr);
}

# else

void consoleLogGreen()
{
	printf("\033[0;32m");
}

void consoleInfoPink()
{
	printf("\033[0;35m");
}

void consoleWarningYellow()
{
	printf("\033[0;33m");
}

void consoleErrorRed()
{
	printf("\033[0;31m");
}

void consoleContentWhite()
{
	printf("\033[0m");
}

# endif





void GLObject::CheckStatus(const char* function)
{
# ifndef DEBUGBUILD//Check errors during debug session only.
	return;
# endif
	GLenum error = glGetError();
	static bool firstCall = true;
	if (error != GL_NO_ERROR)
	{
		Error(debugMsg, "Error spotted during the execution of function: %s!\n"
			"Fatal OpenGL Error %d:\n %s", function, error, glewGetErrorString(error));
	}
}

void GLObject::Log(const char* file, unsigned line, const char* function, const char* msg, ...)
{
# ifndef LOGDEBUGMSG
	return;
# endif

	va_list ap;

	consoleLogGreen();
	printf("[LOG]");
	consoleDefaultWhite();
	printf("[File: %s][Line: %u][Function: %s]: ", file, line, function);

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

	consoleInfoPink();
	printf("[INFO]");
	consoleDefaultWhite();
	printf("[File: %s][Line: %u][Function: %s]: ", file, line, function);

	va_start(ap, msg);
	vprintf(msg, ap);
	printf("\n");
	va_end(ap);
}

void GLObject::Warning(const char* file, unsigned line, const char* function, const char* msg, ...)
{
	va_list ap;

	consoleWarningYellow();
	printf("[WARNING]");
	consoleDefaultWhite();
	printf("[File: %s][Line: %u][Function: %s]: ", file, line, function);

	va_start(ap, msg);
	vprintf(msg, ap);
	printf("\n");
	va_end(ap);

	printf("Dumped callstack:\n");
	printStackTrace();
}

void GLObject::Error(const char* file, unsigned line, const char* function, const char* msg, ...)
{
	va_list ap;

	consoleErrorRed();
	printf("[ERROR]");
	consoleDefaultWhite();
	printf("[File: %s][Line: %u][Function: %s]: ", file, line, function);

	va_start(ap, msg);
	vprintf(msg, ap);
	printf("\n");
	va_end(ap);
	
	printf("Dumped callstack:\n");
	printStackTrace();
	//FIXME: is this error checking function performing what it's supposed to perform?
}