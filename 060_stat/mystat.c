#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <pwd.h>
#include <grp.h>
#include <unistd.h>

struct stat {
  dev_t     st_dev;     /* ID of device containing file */
  ino_t     st_ino;     /* inode number */
  mode_t    st_mode;    /* protection */
  nlink_t   st_nlink;   /* number of hard links */
  uid_t     st_uid;     /* user ID of owner */
  gid_t     st_gid;     /* group ID of owner */
  dev_t     st_rdev;    /* device ID (if special file) */
  off_t     st_size;    /* total size, in bytes */
  blksize_t st_blksize; /* blocksize for file system I/O */
  blkcnt_t  st_blocks;  /* number of 512B blocks allocated */
  time_t    st_atime;   /* time of last access */
  time_t    st_mtime;   /* time of last modification */
  time_t    st_ctime;   /* time of last status change */
};
typedef struct stat stat;

//This function is for Step 4
char * time2str(const time_t * when, long ns) {
  char * ans = malloc(128 * sizeof(*ans));
  char temp1[64];
  char temp2[32];
  const struct tm * t= localtime(when);
  strftime(temp1,512,"%Y-%m-%d %H:%M:%S",t);  
  strftime(temp2,32,"%z",t);
  snprintf(ans,128,"%s.%09ld %s", temp1, ns, temp2);
  return ans;
}

int main(int argc, char ** argv){
  if(argc!=2){
    fprintf(stderr,"too much input file");
    return EXIT_FAILURE;
  }
  stat * buf=malloc(sizeof(*buf));
  if(lstat(argv[1],buf)==-1){
    fprintf(stderr,"Cannot read file status");
    return EXIT_FAILURE;
  }
  printf("  File: ‘%s’\n",argv[1]);
  printf("  Size: %-10lu\tBlocks: %-10lu IO Block: %-6lu %s\n");
  printf("Device: %lxh/%lud\tInode: %-10lu  Links: %lu\n");
}
