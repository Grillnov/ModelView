//
//  GLObject.h
//  ModelView
//
//  Created by Haoyan Huo on 3/19/15.
//  Copyright (c) 2015 Haoyan Huo. All rights reserved.
//
//  Modified by Bowen Yang

# ifndef __ModelView__GLObject__
# define __ModelView__GLObject__

/*!
 * @brief The root class for all GL objects.
 *
 */

class GLObject
{
public:
protected:
	/*! 
	* @brief Log messages on console.

	* @param file The source filename.

	* @param line The line number.

	* @param function The function name.

	* @param msg The formatted log message string.
	* @see Info()
	* @see Warning()
	* @see Error()
	*/
	void Log(const char* file, unsigned line, const char* function, const char* msg, ...);

	/*! 
	* @brief Log info messages on console.

	* @param file The source filename.

	* @param line The line number.

	* @param function The function name.

	* @param msg The formatted log message string.
	* @see Log()
	*/
	void Info(const char* file, unsigned line, const char* function, const char* msg, ...);

	/*! 
	* @brief Log warning messages on console.

	* @param file The source filename.

	* @param line The line number.

	* @param function The function name.

	* @param msg The formatted log message string.
	* @see Log()
	*/
	void Warning(const char* file, unsigned line, const char* function, const char* msg, ...);

	/*! 
	* @brief Log error messages on console, also shutting down the application.

	* @param file The source filename.

	* @param line The line number.

	* @param function The function name.

	* @param msg The formatted log message string.

	* @see Log()
	*/
	void Error(const char* file, unsigned line, const char* function, const char* msg, ...);

	/*! 
	* @brief Make sure no OpenGL error happened.
	* 
	* Sometimes it's necessary to make sure no OpenGL error just happened, 
	* OpenGL errors will be treated as fatal error, same as a call to Error().
	* @param who The logger name.
	* @see Error()
	*/
	void CheckStatus(const char* who);
};

extern void printStackTrace();

void consoleLogGreen();
void consoleInfoPink();
void consoleWarningYellow();
void consoleErrorRed();
void consoleDefaultWhite();

# endif