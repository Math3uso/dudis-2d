# Dudis2D - Pequeno framework para criação de jogos 2d

## dudis2d oq é?
`dudis2d` foi escrito com raylib e ajuda na criação de jogos 2d usando C++.
descrição...

## Status
⚠️ Este projeto ainda está **em desenvolvimento**. Algumas funcionalidades podem estar faltando e podem ocorrer bugs.  
Os logs da engine ainda estão ativos para facilitar o desenvolvimento. (O README está desatualizado)

## Pre-requisitos
### Cmake
O `CMake` é necessário para gerar os arquivos de compilação do seu projeto dudis2d.
Se você ainda não tem, pode instalar rapidamente usando o gerenciador de pacotes do seu sistema:

- **Linux (Debian/Ubuntu):**  
```bash
sudo apt install cmake
```
- **Windows**
Você pode baixar o CMake no site oficial: [cmake.org](https://cmake.org/download/)

### Nodejs
todos os spripts/CLI do `dudis2d` é escrito em JavaScript (até o momento) e por isso é necessario ter instalado em sua maquina. No entando sua instalação e rapida e facil consulete a doc oficial: [nodejs.org](https://nodejs.org/)

## Instalação
clone o repositorio
```bash
git clone https://github.com/Math3uso/dudis-2d.git 
cd dudis-2d
```
entre no diretorio até a pasta de **scripts** (geralmentem em dudis-2d/scrips), lá você verá os scrips de setup execute com base no seu sistema operacional.

### Linux
```bash
bash ./setup.sh
```

### Windows
```bash
Set-ExecutionPolicy -Scope Process -ExecutionPolicy Bypass
# Scope Process → só vale pra sessão atual do PowerShell.
# Bypass → ignora restrições de script.

.\setup.ps1
```

## Criando projeto e compilando
Com o setup já configurado execute (o projeto será criado no diretorio atual):
```bash
dudis nome_do_projeto

#vá no diretorio do projeto
cd ./nome_do_projeto

#crie pasta para o build
mkdir build
cd ./build

cmake ..
make
./app

```

se tudo ocorrer bem você verá uma janela =)

## 🏗️ Como Usar
....

## 🔧 Dependências

- **Raylib** - Sistema de renderização
- **Box2D** - Motor de física 2D
- **RayGUI** - Interface gráfica

## 📦 Build

```bash

cmake -S . -B build
cmake --build build

```

A biblioteca será gerada como `libdudis.a` na pasta `build/`.

## 📋 Notas

- Todos os headers estão organizados na pasta `include/dudis2d/`
- O código fonte está na pasta `src/`
- A biblioteca é modular e pode ser usada como `.a` ou `.lib/.dll`
- Os usuários só precisam dos headers da pasta `include/`


## Contribuição
Contribuições são bem-vindas! Abra issues, pull requests ou apenas acompanhe a evolução.