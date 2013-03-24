/*
    This file is a part of GTFinder
    Copyright (C) 2012 Jalil Karimov <jukarimov@gmail.com>

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.*/
#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <unistd.h>
#include <gtk/gtk.h>
#include <sys/stat.h>

int list_files(char *parentdir)
{
  int file_count = 0;
  GDir *dir;
  GError *err;
  char subdirs[1000][100];
  int isubdirs = 0;

  char rootdir[100];
  strcpy(rootdir, parentdir);

  FILE *fp = fopen("list.txt", "w");
 
seek:
  dir = g_dir_open(rootdir, 0, &err);
  if (!dir) {
    printf("ERROR: [ %s ]", rootdir);
    perror("Couldn't readdir: ");
  }
  else {
    const gchar *de;
    while ((de = g_dir_read_name(dir)) != NULL) 
    {
      fprintf(fp, "%s/%s\n", rootdir, de);
      file_count++;

      struct stat s;
      char path[1000];
      sprintf(path, "%s/%s", rootdir, de);
      if (stat(path, &s) == -1)
        perror("stat");

      if (S_ISDIR(s.st_mode)) {
        strcpy(subdirs[isubdirs], rootdir);
        strcat(subdirs[isubdirs], "/");
        strcat(subdirs[isubdirs], de);
	isubdirs++;
      }
    }
    g_dir_close(dir);
    if (isubdirs > 0) {
      strcpy(rootdir, subdirs[--isubdirs]);
      goto seek;
    }
  }
out:

  fclose(fp);

  return file_count;
}

/*
int main(int argc, char *argv[])
{
  list_files(argv[1]);
  return 0;
}
*/
