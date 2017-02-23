/*The following program prints part of the file specified in its first
command-line argument to standard output.  The range of bytes to be
printed is specified via offset and length values in the second and
third command-line arguments.  The program creates a memory mapping
of the required pages of the file and then uses write(2) to output
the desired bytes.*/

#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <string.h>
#define handle_error(msg) \
           do { perror(msg); exit(EXIT_FAILURE); } while (0)

void printMenu();

int fd;
char * addr;
off_t offset, pa_offset;
ssize_t s;
struct stat sb;
size_t length;
int last_string;
bool Mmap_part (int start, int end, bool read)
{
    if (start < 0) start = 0;
    offset = start;

    length = end - start;
    if (offset + length > sb.st_size || end == -1) {
        length = sb.st_size - offset;
    }
    pa_offset = offset & ~(sysconf(_SC_PAGE_SIZE) - 1);
    if (read) {
        addr = mmap(NULL, length + offset - pa_offset, PROT_READ,
                    MAP_SHARED, fd, pa_offset);
    }
    else {
        addr = mmap(NULL, length + offset - pa_offset, PROT_WRITE,
                    MAP_SHARED, fd, pa_offset);
    }
    if (addr == MAP_FAILED) {
        handle_error("mmap");
        return  false;
    }

    //s = write(STDOUT_FILENO, addr + offset - pa_offset, length);
   // munmap(addr, length + offset - pa_offset);
    return true;

}

bool Munmap_part() {
    munmap(addr, length + offset - pa_offset);
    return true;
}

char Lower(char a) {
    if (a < 97) {
        return a + 'a' - 'A';
    }
    else {
        return a;
    }
}

bool Search (const char * pattern, bool check_case) {
    int stringNum = last_string;
    bool someMatch = false;
    for (int i = offset; i < offset + length; ++i) {
        if (addr[i] == pattern[0]) {
            int match = 1;
            int i_index = 0;
            bool possibleMatch = false;
            for (int j = 1; j < strlen(pattern); ++j) {
                if (addr[i+j + i_index] == pattern[j]) {
                    match++;
                }
                else if (addr[i+j+i_index] == '\n') {
                    ++i_index;
                    possibleMatch = true;
                }
                else if (!check_case) {
                    if(Lower(addr[i+j+i_index]) == Lower(pattern[j])) {
                        match++;
                        printf("sssss\n");
                    }
                    printf("aaaaaaa\n");
                }
                else {
                    break;
                }
            }
            if (possibleMatch) {
                if (addr[i + strlen(pattern)] == pattern[strlen(pattern)-1]) {
                    ++match;
                }
            }
            if (match == strlen(pattern)) {
                printf("(!) Pattern found at string %d \n", stringNum);
                someMatch = true;
            }
        }
        if (addr[i] == '\n') {
            ++stringNum;
        }
    }
    last_string = stringNum;
    return someMatch;
}


void SearchAll (const char * pattern, bool check_case)
{
    bool is_found = false;
    int prev_i = 0;
    last_string = 1;
    for (int i = 200; i < sb.st_size; i += 200) {
        Mmap_part(prev_i, i, true);
        if (Search(pattern,check_case)) {
            is_found = true;
        }
        prev_i = i;
        Munmap_part();
    }
    if (!is_found) {
        printf("\nPattern not found!\n");
    }
}
void PrintD(int a, int b)
{
    Mmap_part(a,b, true);
    s = write(STDOUT_FILENO, addr + offset - pa_offset, length);
    if (s != length) {
        if (s == -1)
            handle_error("write");

        fprintf(stderr, "partial write");
        exit(EXIT_FAILURE);
    }
    Munmap_part();
}

void check_size()
{
    if (fstat(fd, &sb) == -1)           /* To obtain file size */
        handle_error("fstat");
}

void WriteToFile (const char * string, int pos)
{
    ftruncate(fd, sb.st_size + strlen(string));
    check_size();
    int z = strlen(string);

    Mmap_part(sb.st_size - 500, sb.st_size,false);
    int x = 500;
    for (int i = sb.st_size; i >= pos + z; --i) {
        if (x == 0) {
            Munmap_part();
            Mmap_part(i - 500,i + z,false);

        }
        addr[i] = addr[i - z];
        x--;
    }
    for (int j = pos; j < pos + z; ++j) {
        addr[j] = string[j - pos];
    }
    Munmap_part();
    check_size();
    if ( msync( addr, pa_offset, MS_SYNC ) < 0 ) {
        perror("msync failed with error:");
    }
    else (void) printf("%s","msync completed successfully.\n");
}


void DeleteChars(int a, int b)
{
    int z = b- a;
    int pos = a;
    Mmap_part(pos, pos+500,false);
    int x = 500;
    for (int i = pos; i < sb.st_size - z; ++i) {
        if (x == 1) {
            Munmap_part();
            Mmap_part(i,i + 500,false);
            x = 500;
        }
        addr[i] = addr[i + z];
        x--;
    }
    //int z = MoveLeft(a,b);
    Munmap_part();
    ftruncate(fd, length - z);
    if ( msync( addr, pa_offset, MS_SYNC ) < 0 ) {
        perror("msync failed with error:");
    }
    else (void) printf("%s","msync completed successfully.");
    check_size();
}

unsigned char check_sum(const char * filename)
{
    close(fd);
    FILE *fp = fopen(filename,"rb");
    unsigned char checksum = 0;
    while (!feof(fp) && !ferror(fp)) {
        checksum ^= fgetc(fp);
    }

    fclose(fp);
    fd = open(filename, O_RDWR);//O_RDONLY);
    if (fd == -1)
        handle_error("open");
    return checksum;
}

void Count ()
{
    check_size();
    int file_size = sb.st_size;
    int file_size_check = 0;
    int file_strings = 1;
    Mmap_part(0,500,true);
    for (int i = 0; i < sb.st_size; ++i) {
        if (file_size_check % 500 == 0) {
            Munmap_part();
            Mmap_part(i, i + 500, true);
        }
        file_size_check++;
        if(addr[i] == '\n') {
            file_strings++;
        }
    }
    if (file_size_check == file_size) {
        printf("File size = %d\nNumber of strings = %d\n", file_size_check, file_strings);
    }
    else {
        printf("Wrong result!\n");
    }
}

int main(int argc, char *argv[])
{
   // char *addr;
   // int fd;
  //  struct stat sb;
   // off_t offset, pa_offset;
   // size_t length;
  //  ssize_t s;
    if (!strcmp(argv[1], "--help") || !strcmp(argv[1], "-?")) {
        printf("Usage:\n"
                       "--help -? \tshow usage\n"
                       "-r a b    \tprint file from a to b\n"
                       "-rm a b   \tdelete chars in file from a to b\n"
                       "-w a b    \twrite a in file on b position\n"
                       "-chs a    \tcheck if a = checksum of file\n"
                       "-s        \tget file size\n"
                       "-f pattern\tsearch for pattern (add --checkcase to check case)\n"
                       "filename  \tstart programm in interactive mode\n");
        return 0;
    }
    fd = open(argv[1], O_RDWR);//O_RDONLY);
    if (fd == -1)
        handle_error("open");

    if (fstat(fd, &sb) == -1)           /* To obtain file size */
        handle_error("fstat");
    if (argc > 2) {
        if (!strcmp(argv[2], "-w")) {
            if (argc == 5) {
                WriteToFile(argv[3], atoi(argv[4]));
            }
            else {
                printf("usage: -w string [data] pos [num]\n");
            }
            return 0;
        }
        else if (!strcmp(argv[2], "-r")) {
            if (argc == 5) {
                PrintD(atoi(argv[3]), atoi(argv[4]));
            }
            else {
                printf("usage: -r from [num] to [num]");
            }
            return 0;
        }
        else if (!strcmp(argv[2], "-rm")) {
            if (argc == 5) {
                DeleteChars(atoi(argv[3]),atoi(argv[4]));
            }
            else {
                printf("usage: -rm from [num] to [num]");
            }
            return 0;
        }
        else if (!strcmp(argv[2], "-chs")) {
            if (argc == 4) {
                if (atoi(argv[3]) == check_sum(argv[1])) {
                    printf("File not damaged\n");
                }
                else {
                    printf("File damaged\n");
                }
            }
            else {
                printf("usage: -chs checksum");
            }
            return 0;
        }
        else if (!strcmp(argv[2], "-s")) {
            Count();
            return 0;
        }
        else if (!strcmp(argv[2],"-f")) {
            if (argc == 4) {
                SearchAll(argv[3], false);
            }
            else if (argc == 5) {
                if (!strcmp(argv[4], "--checkcase")) {
                    SearchAll(argv[3],true);
                }
            }
            else {
                printf("usage: -f pattern --checkcase\n");
            }
            return 0;
        }
    }
    //zzzzzzzzzzzzzzzzzzzzzz

    int c;
    unsigned char old_checksum = check_sum(argv[1]);
    while (1) {
        printMenu();
        scanf("%d", &c);
        switch (c) {
            case 1:
            {
                int a, b;
                printf("From: ");
                scanf("%d", &a);
                printf("To: ");
                scanf("%d", &b);

                PrintD(a,b);

                break;
            }
            case 2:
            {
                printf("\nEnter pattern:\n");
                char pattern[256];
                scanf("%s", pattern);
                char abcd;
                bool check_case = false;
                SearchAll(pattern,check_case);

                break;
            }
            case 3:
            {
                Munmap_part();
                close(fd);
                exit(EXIT_SUCCESS);
            }
            case 4:
            {
                char string[255];
                scanf("%s", &string);
                int pos;
                scanf("%d", &pos);

                WriteToFile(string,pos);

                break;
            }
            case 5:
            {
                int from, to;
                scanf("%d %d", &from, &to);
                DeleteChars(from, to);
                break;
            }
            case 6:
            {
                Munmap_part();
                close(fd);
                printf("Enter new file:\n");
                char filename[256];
                scanf("%s", & filename);
                fd = open(filename, O_RDWR);//O_RDONLY);
                break;
            }
            case 7:
            {
                Count();
                break;
            }
            case 8:
            {
                unsigned char checksum = check_sum(argv[1]);
                if (checksum != old_checksum) {
                    printf("New checksum differs\n");
                }
                printf("%d\n",checksum);
                old_checksum = checksum;
                break;
            }
        }
    }
    exit(EXIT_SUCCESS);
}

void printMenu()
{
    printf("\n|| Menu ||\n1) Output part\n2) Search\n3) Exit\n4) Write\n5) Delete\n"
                   "6) Change file\n7) Count file size\n8) Update checksum\n");
    return;
}