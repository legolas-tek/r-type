#!/bin/bash

# Liste des répertoires à exclure
exclude_dirs=("libs/deps" "build")

# Récupérer la liste des fichiers à valider
files_to_format=$(git diff --cached --name-only | grep -E '\.cpp$|\.hpp$')

# Formater les fichiers
for file in $files_to_format; do
    exclude=false

    # Vérifie si le fichier se trouve dans un répertoire exclu
    for dir in "${exclude_dirs[@]}"; do
        if [[ "$file" == *"$dir"* ]]; then
            exclude=true
            break
        fi
    done

    # Si le fichier n'est pas exclu, exécute clang-format
    if [ "$exclude" = false ]; then
        clang-format -i "$file"
    fi
done
