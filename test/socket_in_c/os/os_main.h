#ifndef OS_CORE_H
#define OS_CORE_H

// Types
//====================================================================

typedef I32 Os_File;

// Constants
//====================================================================

#define OS_STDIN  0
#define OS_STDOUT 1
#define OS_STDERR 2

// Enums
//====================================================================

enum Os_AccessFlags
{
    Os_AccessFlag_Read       = (1<<0),
    Os_AccessFlag_Write      = (1<<1),
    Os_AccessFlag_Execute    = (1<<2),
    Os_AccessFlag_Append     = (1<<3),
    Os_AccessFlag_ShareRead  = (1<<4),
    Os_AccessFlag_ShareWrite = (1<<5),
    Os_AccessFlag_Inherited  = (1<<6),
};
typedef enum Os_AccessFlags Os_AccessFlags;

// Memory Allocation
//====================================================================

fn void *os_memory_alloc(U64 size);
fn I32 os_memory_commit(void *ptr, U64 size);
fn void os_memory_decommit(void *ptr, U64 size);
fn void os_memory_free(void *ptr, U64 size);

// File System
//====================================================================

fn Os_File os_file_open(Str8 path, Os_AccessFlags flags);
fn void os_file_close(Os_File fd);
fn U64 os_file_read(Os_File fd, Rng1U64 rng, void *out_data);
fn U64 os_file_write(Os_File fd, Rng1U64 rng, void *data);
fn bool os_dir_make(const char *path);
fn bool os_exist(const char *path);

// Exit
//====================================================================

fn void os_exit(I32 exit_code);

// Write
//====================================================================

fn void os_write(I32 fd, void *data, U64 size);
fn void os_write_str8(I32 fd, Str8 str);

#endif // OS_CORE_H
