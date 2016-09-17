//
//  CameraView.hpp
//  ModelView
//
//  Created by Bowen Yang on Sept 11, 2016.
//  Copyright (c) 2016 Bowen Yang. All rights reserved.
//

# include <AllinGL.h>

# ifdef _MSC_VER

# define TRACE_MAX_STACK_FRAMES 1024
# define TRACE_MAX_FUNCTION_NAME_LENGTH 1024

# include <process.h>
# include <DbgHelp.h>

void printStackTrace()
{
# ifdef _DEBUG
	void *stack[TRACE_MAX_STACK_FRAMES];
	HANDLE process = GetCurrentProcess();
	SymInitialize(process, NULL, TRUE);
	WORD numberOfFrames = CaptureStackBackTrace(0, TRACE_MAX_STACK_FRAMES, stack, NULL);
	SYMBOL_INFO *symbol = (SYMBOL_INFO *)malloc(sizeof(SYMBOL_INFO) + (TRACE_MAX_FUNCTION_NAME_LENGTH - 1) * sizeof(TCHAR));
	symbol->MaxNameLen = TRACE_MAX_FUNCTION_NAME_LENGTH;
	symbol->SizeOfStruct = sizeof(SYMBOL_INFO);
	DWORD displacement;
	IMAGEHLP_LINE64 *line = (IMAGEHLP_LINE64 *)malloc(sizeof(IMAGEHLP_LINE64));
	line->SizeOfStruct = sizeof(IMAGEHLP_LINE64);
	for (int i = 0; i < numberOfFrames; i++)
	{
		DWORD64 address = (DWORD64)(stack[i]);
		SymFromAddr(process, address, NULL, symbol);
		if (SymGetLineFromAddr64(process, address, &displacement, line))
		{
			printf("\tat [Function: ");
			consoleWarningYellow();
			printf("%s", symbol->Name);
			consoleDefaultWhite();
			printf("][Source file: %s][Line: %lu]\n", line->FileName, line->LineNumber);
		}
	}
	free(symbol); free(line);
# else
	printf("Callstack not available during release build on Visual Studio platform.\n");
# endif
}

# else//On linux platform

int printStackTrace()
{
	
}

# endif