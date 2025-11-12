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

echo "🚀 Iniciando setup do DUDIS CLI..."

# === Checa dependências ===
if ! command -v node &> /dev/null; then
    echo "❌ Node.js não encontrado! Instale com: https://nodejs.org/"
    exit 1
fi

if ! command -v npm &> /dev/null; then
    echo "❌ npm não encontrado! Instale junto com o Node.js."
    exit 1
fi

# === Caminhos base ===
CLI_DIR="$HOME/dudis-cli"
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
DUDIS2D_PATH="$(dirname "$SCRIPT_DIR")/dudis-2d"

# === Cria pasta e copia arquivos ===
echo "📁 Copiando arquivos para $CLI_DIR ..."
mkdir -p "$CLI_DIR"
cp -r ./src "$CLI_DIR/"
cp package.json "$CLI_DIR/"

# === Permissão de execução ===
chmod +x "$CLI_DIR/src/dudis-cli.js"

# === Instala dependências ===
echo "📦 Instalando dependências npm..."
cd "$CLI_DIR" || exit
npm install --silent

# === Garante que o npm global está no user path (sem sudo) ===
SHELL_RC="$HOME/.bashrc"
if [[ -n "$ZSH_VERSION" ]]; then
    SHELL_RC="$HOME/.zshrc"
fi

NPM_PREFIX=$(npm config get prefix)
if [[ "$NPM_PREFIX" == "/usr" ]]; then
    echo "⚙️ Ajustando npm prefix para ~/.npm-global ..."
    mkdir -p ~/.npm-global
    npm config set prefix '~/.npm-global'
    if ! grep -q ".npm-global/bin" "$SHELL_RC"; then
        echo 'export PATH=$PATH:~/.npm-global/bin' >> "$SHELL_RC"
        echo "✅ PATH atualizado no $SHELL_RC"
    fi
    source "$SHELL_RC"
fi

# === Adiciona CLI_DIR/src ao PATH (caso queira rodar direto sem link) ===
if ! grep -q "$CLI_DIR/src" "$SHELL_RC"; then
    echo "export PATH=\"\$PATH:$CLI_DIR/src\"" >> "$SHELL_RC"
    echo "✅ PATH do CLI adicionado no $SHELL_RC"
fi

# === Exporta DUDIS2D_PATH ===
if ! grep -q "DUDIS2D_PATH=" "$SHELL_RC"; then
    echo "export DUDIS2D_PATH=\"$DUDIS2D_PATH\"" >> "$SHELL_RC"
    echo "✅ DUDIS2D_PATH configurado em $SHELL_RC"
fi

# === Faz link global (sem sudo) ===
echo "🔗 Criando link global do DUDIS..."
npm link

# === Finalização ===
echo ""
echo "🎉 Setup concluído com sucesso!"
echo "👉 Agora abra um novo terminal ou rode: source $SHELL_RC"
echo "✅ Você já pode usar o comando: dudis"
