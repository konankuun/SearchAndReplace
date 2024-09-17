#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <unistd.h>

void search_and_replace(const char *path, const char *search_word, const char *replace_word);

void search_and_delete(const char *path, const char *search_word)
{
    DIR *dir;
    struct dirent *entry;
    char new_path[1024];

    if (!(dir = opendir(path)))
        return;

    while ((entry = readdir(dir)) != NULL)
    {
        if (entry->d_type == DT_DIR)
        {
            if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
                continue;
            snprintf(new_path, sizeof(new_path), "%s/%s", path, entry->d_name);
            search_and_delete(new_path, search_word);
        }
        else
        {
            snprintf(new_path, sizeof(new_path), "%s/%s", path, entry->d_name);
            FILE *file = fopen(new_path, "r+");
            if (file)
            {
                fseek(file, 0, SEEK_END);
                long fsize = ftell(file);
                fseek(file, 0, SEEK_SET);

                char *content = malloc(fsize + 1);
                fread(content, 1, fsize, file);
                content[fsize] = '\0';

                char *pos = strstr(content, search_word);
                if (pos)
                {
                    fseek(file, 0, SEEK_SET);
                    while ((pos = strstr(content, search_word)) != NULL)
                    {
                        fwrite(content, 1, pos - content, file);
                        content = pos + strlen(search_word);
                    }
                    fwrite(content, 1, strlen(content), file);
                    ftruncate(fileno(file), ftell(file));
                }

                free(content);
                fclose(file);
            }
        }
    }
    closedir(dir);
}