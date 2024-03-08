#include <stdio.h>
#include <errno.h>

#define WIN32_LEAN_AND_MEAN
#define NOCOMM
#include <windows.h>

#if _MSC_VER
#	include <stdarg.h>
#endif // _MSC_VER

#define PROJECT_TITLE "SpectrumV"
#define MAIN_FILE "src/main.c"
#define BUILD_DIR "build"

const char *HELP_MESSAGE = "build.c: A C file that build's C files\n"
"Version: 0.1"
"Usage:\n"
"	CMD: build.exe [options]\n"
"	PowerShell: ./build.exe [options]\n"
"	Bash & Others: ./build [options]\n"
"Options:\n"
"	b	Build\n"
"	br	Build and Run project\n"
"	r	Only run program\n"
"	c	Only compile\n"
"	h	Print help\n";

char cmd[100] = "";

typedef enum {
	BUILD_LOG_ALL,
	BUILD_LOG_DEBUG,
    BUILD_LOG_INFO,
    BUILD_LOG_WARNING,
    BUILD_LOG_ERROR,
    BUILD_LOG_NONE
} Build_Log_Levels;

static Build_Log_Levels BUILD_LOG_LEVEL = BUILD_LOG_INFO;

extern void build_cmd_append(char *cmd, char *src, ...);
extern void build_cmd_finish(char *cmd);
extern void build_cmd_run(char *cmd);
extern void build_dir_make(char *path);
extern void build_log(Build_Log_Levels level, char *fmt, ...);
extern int build_file_exists(char *path);

void build_proj_compile(char *cmd) {
	build_log(BUILD_LOG_INFO, "Compiling Project:\n");
	build_cmd_append(cmd, "cl.exe "MAIN_FILE); 					  	  // Main
	build_cmd_append(cmd, " -nologo -c");							  // Misc
	build_cmd_append(cmd, " -Iincludes");							  // Includes
	build_cmd_append(cmd, " -Fo"BUILD_DIR"/"PROJECT_TITLE".obj"); 	  // Object file
	build_cmd_append(cmd, " -Z7");									  // Debug
	build_cmd_append(cmd, " -W4 -analyze");							  // Warning
	// Security
	build_cmd_append(cmd, " -GS -EHa /guard:cf -sdl -Qspectre -fsanitize=address");
	build_cmd_finish(cmd);
}

void build_proj_link(char *cmd) {
	build_log(BUILD_LOG_INFO, "Linking Project:\n");
	build_cmd_append(cmd, "link.exe "BUILD_DIR"/"PROJECT_TITLE".obj -nologo");  // Main
	build_cmd_append(cmd, " -LIBPATH:libs");									// Libs
	build_cmd_append(cmd, " -DEBUG:FULL");				   				 		// Debug
	build_cmd_append(cmd, " -OUT:"BUILD_DIR"/"PROJECT_TITLE".exe");			 	// Output
	build_cmd_append(cmd, " -CETCOMPAT -DYNAMICBASE -HIGHENTROPYVA");	 		// Security
	build_cmd_finish(cmd);
}

void build_proj_run(char *cmd) {
	build_log(BUILD_LOG_INFO, "Running Project:\n");
	build_cmd_append(cmd, BUILD_DIR"\\"PROJECT_TITLE".exe");
	build_cmd_finish(cmd);
}

int main(int argc, char *argv[]) {
	char *args = argv[1];

	build_dir_make(BUILD_DIR);

	if (!args) {
		printf(HELP_MESSAGE);
	} else if (strcmp(args, "h") == 0) {
		printf(HELP_MESSAGE);
	} else if (strcmp(args, "b") == 0) {
		build_proj_compile(cmd);
		build_proj_link(cmd);
	} else if (strcmp(args, "br") == 0) {
		build_proj_compile(cmd);
		build_proj_link(cmd);
		build_proj_run(cmd);
	} else if (strcmp(args, "r") == 0) {
		build_proj_run(cmd);
	} else if (strcmp(args, "c") == 0) {
		build_proj_compile(cmd);
	} else {
		build_log(BUILD_LOG_ERROR, "Wrong argument provided: %s\n%s", args, HELP_MESSAGE);
		return 1;
	}

	return 0;
}

void build_cmd_append(char *cmd, char *src, ...) {
	strcat(cmd, src);
}

void build_cmd_run(char *cmd) {
	build_log(BUILD_LOG_DEBUG, "%s\n", cmd);
	int err = system(cmd);
	if (err) {
		build_log(BUILD_LOG_ERROR, strerror(err));
		exit(err);
	}
}

void build_cmd_finish(char *cmd) {
	build_cmd_run(cmd);
	memset(cmd, 0, strlen(cmd));
}

int build_file_exists(char *path) {
    DWORD dwAttrib = GetFileAttributesA(path);
    return dwAttrib != INVALID_FILE_ATTRIBUTES;
}

void build_dir_make(char *path) {
	if (build_file_exists(BUILD_DIR)) return;

    int result = mkdir(path);
    if (result < 0) {
		build_log(BUILD_LOG_ERROR, "Unable to create directory `%s`: %s", path, strerror(errno));
        exit(1);
    }
    build_log(BUILD_LOG_INFO, "Created directory: %s\n", path);
}

void build_log(Build_Log_Levels level, char *fmt, ...)
{
	if (level < BUILD_LOG_LEVEL) return;
    va_list args;
    va_start(args, fmt);
    switch (level) {
    	case BUILD_LOG_DEBUG:
    		fprintf(stdout, "[DEBUG] ");
    		vfprintf(stdout, fmt, args);
    		break;
    	case BUILD_LOG_INFO:
    	    fprintf(stdout, "[INFO] ");
    		vfprintf(stdout, fmt, args);
    	    break;
    	case BUILD_LOG_WARNING:
    	    fprintf(stderr, "[WARNING] ");
    		vfprintf(stderr, fmt, args);
    	    break;
    	case BUILD_LOG_ERROR:
    	    fprintf(stderr, "[ERROR] ");
    		vfprintf(stderr, fmt, args);
    	    break;
    	default:
			build_log(BUILD_LOG_ERROR, "Error: Wrong BUILD_LOG_LEVEL enterd in build_log");
			exit(1);
			break;
    }
    va_end(args);
}
