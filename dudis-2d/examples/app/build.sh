#!/bin/bash

# Script de build para desenvolvimento
# Reconhece novos arquivos automaticamente

set -e

echo "🔨 Configurando build..."

# Cria diretório de build se não existir
mkdir -p build

# Configura CMake com reconhecimento automático de arquivos
cd build

# Configura CMake para reconhecer mudanças
cmake .. \
    -DCMAKE_BUILD_TYPE=Debug \
    -DCMAKE_EXPORT_COMPILE_COMMANDS=ON \
    -DCMAKE_CXX_FLAGS="-Wall -Wextra"

echo "⚡ Compilando..."

# Compila com reconhecimento automático
make -j$(nproc)

echo "✅ Build concluído!"
echo "🎮 Execute com: ./build/app"
echo ""
echo "💡 Dica: Use 'make && ./build/app' para compilar e executar!"
