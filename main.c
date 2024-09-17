void search_and_replace(const char *path, const char *search_word, const char *replace_word);

void search_and_delete(const char *path, const char *search_word);

int main()
{
    char path[1024];
    char search_word[256];
    char replace_word[256];
    int choice;

    printf("Entrez le chemin du répertoire: ");
    scanf("%s", path);
    printf("Entrez le mot à rechercher: ");
    scanf("%s", search_word);
    printf("Voulez-vous remplacer (1) ou supprimer (2) le mot? ");
    scanf("%d", &choice);

    if (choice == 1)
    {
        printf("Entrez le mot de remplacement: ");
        scanf("%s", replace_word);
        search_and_replace(path, search_word, replace_word);
    }
    else if (choice == 2)
    {
        search_and_delete(path, search_word);
    }
    else
    {
        printf("Choix invalide.\n");
    }

    return 0;
}
