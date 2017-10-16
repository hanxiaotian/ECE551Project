#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <pwd.h>
#include <grp.h>
#include <unistd.h>

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

int humread(struct stat buf,char * s){
  switch (buf.st_mode & S_IFMT) {
  case S_IFBLK:  s[0]='b';            break;
  case S_IFCHR:  s[0]='c';        break;
  case S_IFDIR:  s[0]='d';               break;
  case S_IFIFO:  s[0]='p';               break;
  case S_IFLNK:  s[0]='l';                 break;
  case S_IFREG:  s[0]='-';            break;
  case S_IFSOCK: s[0]='s';                
  }
  if(buf.st_mode & S_IRUSR) s[1]='r';
  else s[1]='-';
  if(buf.st_mode & S_IWUSR) s[2]='w';
  else s[2]='-';
  if(buf.st_mode & S_IXUSR) s[3]='x';
  else s[3]='-';
  if(buf.st_mode & S_IRGRP) s[4]='r';
  else s[4]='-';
  if(buf.st_mode & S_IWGRP) s[5]='w';
  else s[5]='-';
  if(buf.st_mode & S_IXGRP) s[6]='x';
  else s[6]='-';
  if(buf.st_mode & S_IROTH) s[7]='r';
  else s[7]='-';
  if(buf.st_mode & S_IWOTH) s[8]='w';
  else s[8]='-';
  if(buf.st_mode & S_IXOTH) s[9]='x';
  else s[9]='-';
  return EXIT_SUCCESS;
}

void mystat(char * filename){
  struct stat buf;
  if(lstat(filename,&buf)==-1){
    fprintf(stderr,"Cannot read file status");
    exit(EXIT_FAILURE);
  }
  char * mode=NULL;
  switch (buf.st_mode & S_IFMT) {
  case S_IFBLK:  mode="block special file";            break;
  case S_IFCHR:  mode="character special file";        break;
  case S_IFDIR:  mode="directory";               break;
  case S_IFIFO:  mode="fifo";               break;
  case S_IFLNK:  mode="symbolic link";                 break;
  case S_IFREG:  mode="regular file";            break;
  case S_IFSOCK: mode="socket";                  break;
  default:       mode="unknown?";                break;
  }
  if(S_ISLNK(buf.st_mode)){
    char linktarget[256]={0};
    readlink(filename,linktarget,256);
    printf("  File: '%s' -> '%s'\n",filename,linktarget);
  }
  else printf("  File: '%s'\n",filename);
  printf("  Size: %-10lu\tBlocks: %-10lu IO Block: %-6lu %s\n",buf.st_size,buf.st_blocks,buf.st_blksize,mode);
  if(S_ISCHR(buf.st_mode)||S_ISBLK(buf.st_mode)){
    printf("Device: %lxh/%lud\tInode: %-10lu  Links: %-5lu Device type: %d,%d\n",buf.st_dev,buf.st_dev,buf.st_ino,buf.st_nlink,major(buf.st_rdev),minor(buf.st_rdev));
  }
  else printf("Device: %lxh/%lud\tInode: %-10lu  Links: %lu\n",buf.st_dev,buf.st_dev,buf.st_ino,buf.st_nlink);
  char s[11]={0};
  humread(buf,s);
  struct passwd * pd=getpwuid(buf.st_uid);
  struct group * gp=getgrgid(buf.st_gid);
  printf("Access: (%04o/%s)  Uid: (%5d/%8s)   Gid: (%5d/%8s)\n",(buf.st_mode&~S_IFMT),s,buf.st_uid,pd->pw_name,buf.st_gid,gp->gr_name);
  char *timestr = time2str(&buf.st_atime,buf.st_atim.tv_nsec);
  printf("Access: %s\n",timestr);
  free(timestr);
  timestr = time2str(&buf.st_mtime,buf.st_mtim.tv_nsec);
  printf("Modify: %s\n",timestr);
  free(timestr);
  timestr = time2str(&buf.st_ctime,buf.st_ctim.tv_nsec);
  printf("Change: %s\n",timestr);
  free(timestr);
  printf(" Birth: -\n");
}

int main(int argc, char ** argv){
  if(argc==1){
    perror("stat: missing operand\nTry 'stat --help' for more information.\n");
    return EXIT_FAILURE;
  }
  for(int i=1;i<argc;i++){
    mystat(argv[i]);
  }
  return EXIT_SUCCESS;
}
