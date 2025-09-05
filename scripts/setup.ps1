# Caminho onde o CLI vai ficar
$CLI_DIR = "$env:USERPROFILE\dudis-cli"

# Cria pasta e copia arquivos
New-Item -ItemType Directory -Force -Path $CLI_DIR
Copy-Item -Path .\src -Destination $CLI_DIR -Recurse -Force

# Torna executável (Windows não precisa do chmod)

# Adiciona PATH temporário e permanente
$oldPath = [Environment]::GetEnvironmentVariable("PATH", "User")
if ($oldPath -notlike "*$CLI_DIR*") {
    [Environment]::SetEnvironmentVariable("PATH", "$oldPath;$CLI_DIR", "User")
}

# Cria alias dudis
if (-not (Test-Path Function:\dudis)) {
    Set-Alias dudis "$CLI_DIR\src\new_project.js"
}

Write-Host "Setup concluído! Abra um novo PowerShell e rode 'dudis new MyApp'"
