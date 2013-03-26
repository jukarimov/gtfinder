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
#include <stdlib.h>
#include <gtk/gtk.h>
#include <sys/stat.h>

int list_files(char *parentdir)
{
  int file_count = 0;
  GDir *dir;
  GError *err = NULL;
  char *subdirs[1000];
  int isubdirs = 0;

  char rootdir[1000];
  strcpy(rootdir, parentdir);

  FILE *fp = fopen("list.txt", "w");

seek:
  dir = g_dir_open(rootdir, 0, &err);
  if (err) {
    printf("ERROR: [ %s ]", rootdir);
    perror("Couldn't opendir: ");
    err = NULL;
  }
  else {
    const gchar *de;
    while ((de = g_dir_read_name(dir)) != NULL)
    {

      file_count++;

      char path[1000];
      sprintf(path, "%s\\%s", rootdir, de);
      fprintf(fp, "%s\n", path);

      if (g_file_test(path, G_FILE_TEST_IS_DIR)) {
        subdirs[isubdirs] = strdup(path);
        if (!subdirs[isubdirs]) {
            fprintf(fp, "\n\n\n!!!FATAL ERROR OME!!!\n\n\n");
            goto out;
        }
        isubdirs++;
      }
    }
    g_dir_close(dir);
    if (isubdirs > 0) {
      memset(rootdir, 0, sizeof(rootdir));
      strcpy(rootdir, subdirs[--isubdirs]);
      free(subdirs[isubdirs]);
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
