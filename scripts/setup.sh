# !/bin/bash

# # Caminho onde o CLI vai ficar
# CLI_DIR="$HOME/dudis-cli"

# # Cria pasta e copia arquivos
# mkdir -p "$CLI_DIR"
# cp -r ./src "$CLI_DIR/"

# # Torna o script executável
# chmod +x "$CLI_DIR/src/new_project.js"

# # Adiciona ao PATH permanentemente
# SHELL_RC="$HOME/.bashrc"
# if [[ -n "$ZSH_VERSION" ]]; then
#     SHELL_RC="$HOME/.zshrc"
# fi

# # Adiciona export PATH se não existir
# if ! grep -q "$CLI_DIR/src" "$SHELL_RC"; then
#     echo "export PATH=\"\$PATH:$CLI_DIR/src\"" >> "$SHELL_RC"
# fi

# # Cria alias dudis chamando Node
# if ! grep -q "alias dudis=" "$SHELL_RC"; then
#     echo "alias dudis=\"node $CLI_DIR/src/new_project.js\"" >> "$SHELL_RC"
# fi

# # Diretório onde o script está
# SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"

# # Diretório DUDIS2D (uma pasta acima do script)
# DUDIS2D_PATH="$(dirname "$SCRIPT_DIR")/dudis-2d"

# # Adiciona ao shell RC se não estiver definido
# if ! grep -q "DUDIS2D_PATH=" "$SHELL_RC"; then
#     echo "export DUDIS2D_PATH=\"$DUDIS2D_PATH\"" >> "$SHELL_RC"
# fi

# echo "Setup concluído! Abra um novo terminal ou rode 'source $SHELL_RC'"



#!/bin/bash

# Caminho onde o CLI vai ficar
CLI_DIR="$HOME/dudis-cli"

# Cria pasta e copia arquivos
mkdir -p "$CLI_DIR"
cp -r ./src "$CLI_DIR/"
cp package.json "$CLI_DIR/"  # importante pra npm link funcionar!

# Torna o script executável
chmod +x "$CLI_DIR/src/dudis-cli.js"

# Adiciona ao PATH permanentemente
SHELL_RC="$HOME/.bashrc"
if [[ -n "$ZSH_VERSION" ]]; then
    SHELL_RC="$HOME/.zshrc"
fi

# Adiciona export PATH se não existir
if ! grep -q "$CLI_DIR/src" "$SHELL_RC"; then
    echo "export PATH=\"\$PATH:$CLI_DIR/src\"" >> "$SHELL_RC"
fi

# Diretório onde o script está
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"

# Diretório DUDIS2D (uma pasta acima do script)
DUDIS2D_PATH="$(dirname "$SCRIPT_DIR")/dudis-2d"

# Adiciona ao shell RC se não estiver definido
if ! grep -q "DUDIS2D_PATH=" "$SHELL_RC"; then
    echo "export DUDIS2D_PATH=\"$DUDIS2D_PATH\"" >> "$SHELL_RC"
fi

# Faz o link global do CLI
echo "🔗 Fazendo npm link..."
cd "$CLI_DIR" || exit
npm link

echo "✅ Setup concluído! Abra um novo terminal ou rode 'source $SHELL_RC'"
