#!/bin/bash

# Script que compila e executa o app
# Uso: ./run.sh

echo "🔨 Compilando..."
./dev.sh make

if [ $? -eq 0 ]; then
    echo "🎮 Executando..."
    ./dev.sh ./app
else
    echo "❌ Erro na compilação!"
    exit 1
fi
