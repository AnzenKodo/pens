#ifndef STD_OS_LINUX_H
#define STD_OS_LINUX_H

#include <unistd.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <time.h>

// Memory Allocation
//====================================================================

fn void *os_memory_alloc(U64 size)
{
    void *result = mmap(0, size, PROT_NONE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0);
    if(result == MAP_FAILED) { result = 0; }
    return result;
}

fn I32 os_memory_commit(void *ptr, U64 size)
{
    mprotect(ptr, size, PROT_READ|PROT_WRITE);
    return 1;
}

fn void os_memory_decommit(void *ptr, U64 size)
{
    madvise(ptr, size, MADV_DONTNEED);
    mprotect(ptr, size, PROT_NONE);
}

fn void os_memory_free(void *ptr, U64 size)
{
    munmap(ptr, size);
}

// File System
//====================================================================

fn Os_File os_file_open(Str8 path, Os_AccessFlags flags)
{
    I32 linux_flags = 0;
    if(flags & Os_AccessFlag_Read && flags & Os_AccessFlag_Write) {
        linux_flags = O_RDWR;
    } else if(flags & Os_AccessFlag_Write) {
        linux_flags = O_WRONLY|O_TRUNC;
    } else if(flags & Os_AccessFlag_Read) {
        linux_flags = O_RDONLY;
    }
    if(flags & Os_AccessFlag_Append) {
        linux_flags |= O_APPEND;
    }
    if(flags & (Os_AccessFlag_Write|Os_AccessFlag_Append)) {
        linux_flags |= O_CREAT;
    }

    I32 fd = open((char *)path.str, linux_flags, 0755);
    Os_File os_fd;
    if(fd != -1) { os_fd = (Os_File)fd; }

    return os_fd;
}

fn void os_file_close(Os_File fd)
{
    close((int)fd);
}

fn U64 os_file_read(Os_File fd, Rng1U64 rng, void *out_data)
{
    U64 total_num_bytes_to_read = dim_1u64(rng);
    U64 total_num_bytes_read = 0;
    U64 total_num_bytes_left_to_read = total_num_bytes_to_read;
    for(;total_num_bytes_left_to_read > 0;)
    {
        int read_result = pread(
            fd,
            cast(U8 *)out_data + total_num_bytes_read, total_num_bytes_left_to_read,
            rng.min + total_num_bytes_read
        );
        if(read_result >= 0)
        {
            total_num_bytes_read += read_result;
            total_num_bytes_left_to_read -= read_result;
        }
        else if(errno != EINTR)
        {
            break;
        }
    }
    return total_num_bytes_read;
}

fn U64 os_file_write(Os_File fd, Rng1U64 rng, void *data)
{
    U64 total_num_bytes_to_write = dim_1u64(rng);
    U64 total_num_bytes_written = 0;
    U64 total_num_bytes_left_to_write = total_num_bytes_to_write;
    for(;total_num_bytes_left_to_write > 0;)
    {
        int write_result = pwrite(
            fd,
            (U8 *)data + total_num_bytes_written,
            total_num_bytes_left_to_write,
            rng.min + total_num_bytes_written
        );
        if(write_result >= 0)
        {
            total_num_bytes_written += write_result;
            total_num_bytes_left_to_write -= write_result;
        }
        else if(errno != EINTR)
        {
            break;
        }
    }
    return total_num_bytes_written;
}

fn bool os_dir_make(const char *path)
{
    I32 result = mkdir(path, 0700);

    if (result == 0) {
        return true;
    } else {
        return false;
    }
}

fn bool os_exist(const char *path)
{
    struct stat buffer;

    if (stat(path, &buffer) == 0) {
        return true;
    } else {
        return false;
    }
}

// Exit
//====================================================================

fn void os_exit(I32 exit_code)
{
    _exit(exit_code);
}

// Write
//====================================================================

fn void os_write(I32 fd, void *data, U64 size)
{
    write(fd, data, size);
}

fn void os_write_str8(I32 fd, Str8 str)
{
    os_write(fd, str.str, str.size+1);
}


// Time
//====================================================================

fn DateTime os_linux_date_time_from_tm(struct tm in, U32 msec)
{
  DateTime dt = {0};
  dt.sec  = in.tm_sec;
  dt.min  = in.tm_min;
  dt.hour = in.tm_hour;
  dt.day  = in.tm_mday-1;
  dt.mon  = in.tm_mon;
  dt.year = in.tm_year+1900;
  dt.msec = msec;
  return dt;
}

fn U64 os_now_ms(void)
{
  struct timespec t;
  clock_gettime(CLOCK_MONOTONIC, &t);
  U64 result = t.tv_sec*Million(1) + (t.tv_nsec/Thousand(1));
  return result;
}

fn U32 os_now_unix(void)
{
  time_t t = time(0);
  return (U32)t;
}

fn DateTime os_now_universal_time(void)
{
  time_t t = 0;
  time(&t);
  struct tm universal_tm = {0};
  gmtime_r(&t, &universal_tm);
  DateTime result = os_linux_date_time_from_tm(universal_tm, 0);
  return result;
}

#endif // STD_OS_LINUX_H
