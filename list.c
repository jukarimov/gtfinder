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

int list_files(char *parentdir)
{
  int file_count = 0;
  DIR *dir;
  struct dirent *de = NULL;
  char subdirs[1000][100];
  int isubdirs = 0;

  char rootdir[100];
  strcpy(rootdir, parentdir);

  FILE *fp = fopen("list.txt", "w");
 
seek:
  dir = opendir(rootdir);
  if (!dir) {
    printf("ERROR: [ %s ]", rootdir);
    perror("Couldn't readdir: ");
  }
  else {
    de = readdir(dir);
    if (!de) {
      printf("ERROR:[ %s ]", rootdir);
      perror("Couldn't readdir ");
      goto out;
    }
    if (strcmp(de->d_name, "..") != 0 && strcmp(de->d_name, ".") != 0) {
      fprintf(fp, "%s/%s\n", rootdir, de->d_name);
      file_count++;
    }
    while ((de = readdir(dir)) != NULL) 
    {
      if (!strcmp(de->d_name, "..") || !strcmp(de->d_name, "."))
        continue;
      fprintf(fp, "%s/%s\n", rootdir, de->d_name);
      file_count++;

      if (de->d_type == 4) {
        strcpy(subdirs[isubdirs], rootdir);
        strcat(subdirs[isubdirs], "/");
        strcat(subdirs[isubdirs], de->d_name);
	isubdirs++;
      }
    }
    closedir(dir);
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
  DIR *dir;
  struct dirent *de = NULL;
  char subdirs[1000][100];
  int isubdirs = 0;

  char rootdir[100];
  strcpy(rootdir, argv[1]);
 
seek:
  dir = opendir(rootdir);
  if (!dir) {
    printf("ERROR: [ %s ]", rootdir);
    perror("Couldn't readdir: ");
  }
  else {
    de = readdir(dir);
    if (!de) {
      printf("ERROR:[ %s ]", rootdir);
      perror("Couldn't readdir ");
      goto out;
    }
    if (strcmp(de->d_name, "..") != 0 && strcmp(de->d_name, ".") != 0)
      printf("%s/%s\n", rootdir, de->d_name);
    while ((de = readdir(dir)) != NULL) 
    {
      if (!strcmp(de->d_name, "..") || !strcmp(de->d_name, "."))
        continue;
      printf("%s/%s\n", rootdir, de->d_name);

      if (de->d_type == 4) {
        strcpy(subdirs[isubdirs], rootdir);
        strcat(subdirs[isubdirs], "/");
        strcat(subdirs[isubdirs], de->d_name);
	isubdirs++;
      }
    }
    if (isubdirs > 0) {
      strcpy(rootdir, subdirs[--isubdirs]);
      goto seek;
    }
  }
out:

  return 0;
}
*/
