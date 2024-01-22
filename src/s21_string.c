#include "s21_string.h"

void *s21_memchr(const void *str, int c, size_t n) {
    const unsigned char *res = NULL, *tmp = str;
    while (n-- != 0 && res == NULL) {
        if (*tmp == (char)c)
            res = tmp;
        tmp++;
    }
    return (void *)res;
}

int s21_memcmp(const void *str1, const void *str2, size_t n) {
    const unsigned char *tmp1 = str1, *tmp2 = str2;
    int res = 0;
    while (n-- != 0 && res == 0) {
        res = *tmp1 - *tmp2;
        tmp1++;
        tmp2++;
    }
    return res;
}

void *s21_memcpy(void *dest, const void *src, size_t n) {
    char *d = dest;
    const char *str = src;
    while (n-- != 0) {
        *d++ = *str++;
    }
    return dest;
}

void *s21_memset(void *str, int c, size_t n) {
    unsigned char *tmp = str;
    while (n-- != 0) {
        *tmp++ = c;
    }
    return str;
}

char *s21_strncat(char *dest, const char *src, size_t n) {
    char *tmp = dest;
    while (*tmp != '\0') {
        tmp++;
    }
    while (*src != '\0' && n-- > 0) {
        *tmp++ = *src++;
    }
    *tmp = '\0';
    return dest;
}

char *s21_strchr(const char *str, int c) {
    while (*str != '\0' && *str != (char)c) {
        str++;
    }
    return (*str == (char)c) ? (char *)str : NULL;
}

int s21_strncmp(const char *str1, const char *str2, size_t n) {
    int res = 0;
    while (res == 0 && n-- > 0 && (*str1 != '\0' || *str2 != '\0')) {
        res = *str1 - *str2;
        str1++;
        str2++;
    }
    return res;
}

char *s21_strncpy(char *dest, const char *src, size_t n) {
    char *tmp = dest;
    while (n > 0 && *src != '\0') {
        *tmp++ = *src++;
        n--;
    }
    while (n-- > 0) {
        *tmp++ = '\0';
    }
    return dest;
}

size_t s21_strcspn(const char *str1, const char *str2) {
    const char *p, *r;
    size_t count = 0;
    bool flag = true;
    for (p = str1; *p != '\0' && flag; ++p) {
        for (r = str2; *r != '\0' && flag; ++r) {
            if (*p == *r) flag = false;
        }
        if (flag) count++;
    }
    return count;
}

size_t s21_strlen(const char *str) {
    const char *tmp = str;
    while (*tmp != '\0') {
        tmp++;
    }
    return tmp - str;
}

char *s21_strpbrk(const char *str1, const char *str2) {
    const char *tmp;
    char *res = NULL;
    while (*str1 != '\0' && res == NULL) {
        tmp = str2;
        while (*tmp != '\0' && res == NULL) {
            if (*str1 == *tmp) res = (char *)str1;
            tmp++;
        }
        str1++;
    }
    return res;
}

char *s21_strrchr(const char *str, int c) {
    const char *last = NULL;
    while (*str != '\0') {
        if (*str == (char)c) last = str;
        str++;
    }
    return *str == (char)c ? (char *)str : (char *)last;
}

char *s21_strstr(const char *haystack, const char *needle) {
    if (*needle != '\0') {
        bool flag = true;
        while (*haystack != '\0' && flag) {
            const char *h = haystack;
            const char *n = needle;
            while (*n != '\0' && *h == *n) {
                h++;
                n++;
            }
            if (*n == '\0')
                flag = false;
            else
                haystack++;
        }
        if (flag) haystack = NULL;
    }
    return (char *)haystack; 
}

char *s21_strtok(char *str, const char *delim) {
    static char *last_token = NULL;
    if (str != NULL) {
        last_token = str;
    } else if (last_token == NULL) {
        return NULL;
    }

    while (*last_token != '\0' && s21_strchr(delim, *last_token) != NULL) {
        last_token++;
    }

    if (*last_token == '\0') {
        return NULL;
    }

    char *token_start = last_token;

    while (*last_token != '\0' && s21_strchr(delim, *last_token) == NULL) {
        last_token++;
    }

    if (*last_token != '\0') {
        *last_token = '\0';
        last_token++;
    }

    return token_start;
}

#if defined(__APPLE__)
#define MAX_ERRLIST 107
#define MIN_ERRLIST -1

static const char *error_list[] = {
    "Undefined error: 0",
    "Operation not permitted",
    "No such file or directory",
    "No such process",
    "Interrupted system call",
    "Input/output error",
    "Device not configured",
    "Argument list too long",
    "Exec format error",
    "Bad file descriptor",
    "No child processes",
    "Resource deadlock avoided",
    "Cannot allocate memory",
    "Permission denied",
    "Bad address",
    "Block device required",
    "Resource busy",
    "File exists",
    "Cross-device link",
    "Operation not supported by device",
    "Not a directory",
    "Is a directory",
    "Invalid argument",
    "Too many open files in system",
    "Too many open files",
    "Inappropriate ioctl for device",
    "Text file busy",
    "File too large",
    "No space left on device",
    "Illegal seek",
    "Read-only file system",
    "Too many links",
    "Broken pipe",
    "Numerical argument out of domain",
    "Result too large",
    "Resource temporarily unavailable",
    "Operation now in progress",
    "Operation already in progress",
    "Socket operation on non-socket",
    "Destination address required",
    "Message too long",
    "Protocol wrong type for socket",
    "Protocol not available",
    "Protocol not supported",
    "Socket type not supported",
    "Operation not supported",
    "Protocol family not supported",
    "Address family not supported by protocol family",
    "Address already in use",
    "Can't assign requested address",
    "Network is down",
    "Network is unreachable",
    "Network dropped connection on reset",
    "Software caused connection abort",
    "Connection reset by peer",
    "No buffer space available",
    "Socket is already connected",
    "Socket is not connected",
    "Can't send after socket shutdown",
    "Too many references: can't splice",
    "Operation timed out",
    "Connection refused",
    "Too many levels of symbolic links",
    "File name too long",
    "Host is down",
    "No route to host",
    "Directory not empty",
    "Too many processes",
    "Too many users",
    "Disc quota exceeded",
    "Stale NFS file handle",
    "Too many levels of remote in path",
    "RPC struct is bad",
    "RPC version wrong",
    "RPC prog. not avail",
    "Program version wrong",
    "Bad procedure for program",
    "No locks available",
    "Function not implemented",
    "Inappropriate file type or format",
    "Authentication error",
    "Need authenticator",
    "Device power is off",
    "Device error",
    "Value too large to be stored in data type",
    "Bad executable (or shared library)",
    "Bad CPU type in executable",
    "Shared library version mismatch",
    "Malformed Mach-o file",
    "Operation canceled",
    "Identifier removed",
    "No message of desired type",
    "Illegal byte sequence",
    "Attribute not found",
    "Bad message",
    "EMULTIHOP (Reserved)",
    "No message available on STREAM",
    "ENOLINK (Reserved)",
    "No STREAM resources",
    "Not a STREAM",
    "Protocol error",
    "STREAM ioctl timeout",
    "Operation not supported on socket",
    "Policy not found",
    "State not recoverable",
    "Previous owner died",
    "Interface output queue is full"};

#elif defined(__linux__)
#define MAX_ERRLIST 134
#define MIN_ERRLIST -1

static const char *error_list[] = {
    "Success",
    "Operation not permitted",
    "No such file or directory",
    "No such process",
    "Interrupted system call",
    "Input/output error",
    "No such device or address",
    "Argument list too long",
    "Exec format error",
    "Bad file descriptor",
    "No child processes",
    "Resource temporarily unavailable",
    "Cannot allocate memory",
    "Permission denied",
    "Bad address",
    "Block device required",
    "Device or resource busy",
    "File exists",
    "Invalid cross-device link",
    "No such device",
    "Not a directory",
    "Is a directory",
    "Invalid argument",
    "Too many open files in system",
    "Too many open files",
    "Inappropriate ioctl for device",
    "Text file busy",
    "File too large",
    "No space left on device",
    "Illegal seek",
    "Read-only file system",
    "Too many links",
    "Broken pipe",
    "Numerical argument out of domain",
    "Numerical result out of range",
    "Resource deadlock avoided",
    "File name too long",
    "No locks available",
    "Function not implemented",
    "Directory not empty",
    "Too many levels of symbolic links",
    "Unknown error 41",
    "No message of desired type",
    "Identifier removed",
    "Channel number out of range",
    "Level 2 not synchronized",
    "Level 3 halted",
    "Level 3 reset",
    "Link number out of range",
    "Protocol driver not attached",
    "No CSI structure available",
    "Level 2 halted",
    "Invalid exchange",
    "Invalid request descriptor",
    "Exchange full",
    "No anode",
    "Invalid request code",
    "Invalid slot",
    "Unknown error 58",
    "Bad font file format",
    "Device not a stream",
    "No data available",
    "Timer expired",
    "Out of streams resources",
    "Machine is not on the network",
    "Package not installed",
    "Object is remote",
    "Link has been severed",
    "Advertise error",
    "Srmount error",
    "Communication error on send",
    "Protocol error",
    "Multihop attempted",
    "RFS specific error",
    "Bad message",
    "Value too large for defined data type",
    "Name not unique on network",
    "File descriptor in bad state",
    "Remote address changed",
    "Can not access a needed shared library",
    "Accessing a corrupted shared library",
    ".lib section in a.out corrupted",
    "Attempting to link in too many shared libraries",
    "Cannot exec a shared library directly",
    "Invalid or incomplete multibyte or wide character",
    "Interrupted system call should be restarted",
    "Streams pipe error",
    "Too many users",
    "Socket operation on non-socket",
    "Destination address required",
    "Message too long",
    "Protocol wrong type for socket",
    "Protocol not available",
    "Protocol not supported",
    "Socket type not supported",
    "Operation not supported",
    "Protocol family not supported",
    "Address family not supported by protocol",
    "Address already in use",
    "Cannot assign requested address",
    "Network is down",
    "Network is unreachable",
    "Network dropped connection on reset",
    "Software caused connection abort",
    "Connection reset by peer",
    "No buffer space available",
    "Transport endpoint is already connected",
    "Transport endpoint is not connected",
    "Cannot send after transport endpoint shutdown",
    "Too many references: cannot splice",
    "Connection timed out",
    "Connection refused",
    "Host is down",
    "No route to host",
    "Operation already in progress",
    "Operation now in progress",
    "Stale file handle",
    "Structure needs cleaning",
    "Not a XENIX named type file",
    "No XENIX semaphores available",
    "Is a named type file",
    "Remote I/O error",
    "Disk quota exceeded",
    "No medium found",
    "Wrong medium type",
    "Operation canceled",
    "Required key not available",
    "Key has expired",
    "Key has been revoked",
    "Key was rejected by service",
    "Owner died",
    "State not recoverable",
    "Operation not possible due to RF-kill",
    "Memory page has hardware error"};

#endif

char *s21_strerror(int errornum) {
  static char result[512] = {'\0'};

  if (errornum <= MIN_ERRLIST || errornum >= MAX_ERRLIST) {
    sprintf(result, "Unknown error: %d", errornum);
  } else {
    s21_strncpy(result, ((char *)error_list[errornum]), 512);
  }

  return result;
}