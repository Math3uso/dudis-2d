# Caminho onde o CLI vai ficar
$CLI_DIR = "$HOME\dudis-cli"

# Cria pasta e copia arquivos
Write-Host "📁 Criando diretório e copiando arquivos..."
New-Item -ItemType Directory -Force -Path $CLI_DIR | Out-Null
Copy-Item -Recurse -Force ./src $CLI_DIR/
Copy-Item -Force ./package.json $CLI_DIR/

# Torna o script principal executável (no Windows não precisa chmod)
$MAIN_SCRIPT = "$CLI_DIR\src\dudis-cli.js"

# Detecta arquivo de inicialização do shell
$PROFILE_PATH = $PROFILE
if (-not (Test-Path $PROFILE_PATH)) {
    New-Item -ItemType File -Path $PROFILE_PATH -Force | Out-Null
}

# Diretório do script atual
$SCRIPT_DIR = Split-Path -Parent $MyInvocation.MyCommand.Definition

# Diretório do DUDIS2D (uma pasta acima)
$DUDIS2D_PATH = Join-Path (Split-Path -Parent $SCRIPT_DIR) "dudis-2d"

# Adiciona DUDIS2D_PATH ao perfil, se ainda não estiver
if (-not (Select-String -Path $PROFILE_PATH -Pattern "DUDIS2D_PATH" -Quiet)) {
    Add-Content $PROFILE_PATH "`n`$env:DUDIS2D_PATH = `"$DUDIS2D_PATH`""
    Write-Host "🌍 Adicionado DUDIS2D_PATH ao perfil PowerShell."
}

# Instala dependências e faz o link global
Write-Host "📦 Instalando dependências..."
Set-Location $CLI_DIR
npm install

Write-Host "🔗 Criando link global com npm link..."
npm link

Write-Host "`n✅ Setup concluído!"
Write-Host "Abra um novo terminal ou rode:"
Write-Host "`n    . `$PROFILE"
