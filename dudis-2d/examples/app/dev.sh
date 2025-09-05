#!/bin/bash

# Script de desenvolvimento
# Permite usar: ./dev.sh make && ./app

# Se não há argumentos, mostra ajuda
if [ $# -eq 0 ]; then
    echo "🔧 Script de Desenvolvimento"
    echo ""
    echo "Uso:"
    echo "  ./dev.sh make          # Compila o projeto"
    echo "  ./dev.sh ./app         # Executa o app"
    echo "  ./dev.sh make && ./app # Compila e executa"
    echo ""
    echo "Exemplos:"
    echo "  ./dev.sh make && ./app"
    echo "  ./dev.sh make"
    echo "  ./dev.sh ./app"
    exit 0
fi

# Executa os comandos no diretório build
cd build

# Se o comando foi ./app, executa o app compilado
if [[ "$*" == *"./app"* ]]; then
    ./app
else
    # Para outros comandos, executa normalmente
    eval "$@"
fi
