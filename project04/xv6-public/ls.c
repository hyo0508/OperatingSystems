#include "types.h"
#include "stat.h"
#include "user.h"
#include "fs.h"

char*
fmtname(char *path)
{
  static char buf[DIRSIZ+1];
  char *p;

  // Find first character after last slash.
  for(p=path+strlen(path); p >= path && *p != '/'; p--)
    ;
  p++;

  // Return blank-padded name.
  if(strlen(p) >= DIRSIZ)
    return p;
  memmove(buf, p, strlen(p));
  memset(buf+strlen(p), ' ', DIRSIZ-strlen(p));
  return buf;
}

char*
fmtowner(char *owner)
{
  static char buf[16];
  char *s;

  s = owner;
  memmove(buf, s, strlen(s));
  memset(buf+strlen(s), ' ', 15-strlen(s));
  return buf;
}

char*
fmtmode(int type, int mode)
{
  static char buf[8];

  if (type == 1)
    buf[0] = 'd';
  else
    buf[0] = '-';
  if (mode & MODE_RUSR)
    buf[1] = 'r';
  else
    buf[1] = '-';
  if (mode & MODE_WUSR)
    buf[2] = 'w';
  else
    buf[2] = '-';
  if (mode & MODE_XUSR)
    buf[3] = 'x';
  else
    buf[3] = '-';
  if (mode & MODE_ROTH)
    buf[4] = 'r';
  else
    buf[4] = '-';
  if (mode & MODE_WOTH)
    buf[5] = 'w';
  else
    buf[5] = '-';
  if (mode & MODE_XOTH)
    buf[6] = 'x';
  else
    buf[6] = '-';
  buf[7] = 0;
  return buf;
}

// ls.c
void
ls(char *path)
{
  char buf[512], *p;
  int fd;
  struct dirent de;
  struct stat st;

  if((fd = open(path, 0)) < 0){
    printf(2, "ls: cannot open %s\n", path);
    return;
  }

  if(fstat(fd, &st) < 0){
    printf(2, "ls: cannot stat %s\n", path);
    close(fd);
    return;
  }

  switch(st.type){
  case T_FILE:
    printf(1, "%s %s %s %d %d %d\n", fmtmode(st.type, st.mode), fmtowner(st.owner), fmtname(path), st.type, st.ino, st.size);
    break;

  case T_DIR:
    if(strlen(path) + 1 + DIRSIZ + 1 > sizeof buf){
      printf(1, "ls: path too long\n");
      break;
    }
    strcpy(buf, path);
    p = buf+strlen(buf);
    *p++ = '/';
    while(read(fd, &de, sizeof(de)) == sizeof(de)){
      if(de.inum == 0)
        continue;
      memmove(p, de.name, DIRSIZ);
      p[DIRSIZ] = 0;
      if(stat(buf, &st) < 0){
        printf(1, "ls: cannot stat %s\n", buf);
        continue;
      }
      printf(1, "%s %s %s %d %d %d\n", fmtmode(st.type, st.mode), fmtowner(st.owner), fmtname(buf), st.type, st.ino, st.size);
    }
    break;
  }
  close(fd);
}

int
main(int argc, char *argv[])
{
  int i;

  if(argc < 2){
    ls(".");
    exit();
  }
  for(i=1; i<argc; i++)
    ls(argv[i]);
  exit();
}
