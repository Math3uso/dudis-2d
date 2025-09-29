# Dudis2D - Pequeno framework para criação de jogos 2d

Dudis2d foi escrito com raylib e ajuda na criação de jogos 2d usando C++.

## Status
⚠️ Este projeto ainda está **em desenvolvimento**. Algumas funcionalidades podem estar faltando e podem ocorrer bugs.  
Os logs da engine ainda estão ativos para facilitar o desenvolvimento. (O README está desatualizado)

## Contribuição
Contribuições são bem-vindas! Abra issues, pull requests ou apenas acompanhe a evolução.

## 📁 Estrutura do Projeto

### **Estrutura Modular**

```
dudis-2d/
├── include/                    # Headers públicos da API
│   └── dudis2d/
│       ├── dudis2d.h          # Header principal
│       ├── physics.h          # Sistema de física
│       ├── graphics.h         # Sistema de renderização
│       ├── core/              # Componentes fundamentais
│       │   ├── log/           # Sistema de logging
│       │   ├── model/         # Modelos de dados
│       │   ├── physicsComponent/ # Componentes de física
│       │   ├── utils/         # Utilitários
│       │   └── window/        # Gerenciamento de janelas
│       ├── graphics/          # Sistema de renderização
│       │   ├── sprites/       # Sprites e retângulos
│       │   ├── ui/            # Interface do usuário
│       │   └── utils/         # Utilitários gráficos
│       ├── globals/           # Variáveis e estado global
│       └── scenes/            # Sistema de cenas
│           ├── scene/         # Gerenciamento de cenas
│           └── sceneManager/  # Gerenciador de cenas
├── src/                       # Código fonte (implementação)
│   ├── core/                  # Implementação dos componentes fundamentais
│   ├── graphics/              # Implementação do sistema de renderização
│   ├── globals/               # Implementação das variáveis globais
│   └── scenes/                # Implementação do sistema de cenas
├── extern/                    # Dependências externas
│   ├── box2d/                 # Motor de física 2D
│   └── raygui/                # Interface gráfica
├── build/                     # Arquivos de compilação
└── CMakeLists.txt             # Sistema de build
```

## 🎯 Características

- **Motor de Física 2D** baseado no Box2D
- **Sistema de Renderização** com Raylib
- **Interface Gráfica** com RayGUI
- **Arquitetura Modular** com separação clara de responsabilidades
- **Sistema de Cenas** para organização do código
- **Build System** com CMake

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
mkdir build
cd build
cmake ..
make
```

A biblioteca será gerada como `libdudis.a` na pasta `build/`.

## 📋 Notas

- Todos os headers estão organizados na pasta `include/dudis2d/`
- O código fonte está na pasta `src/`
- A biblioteca é modular e pode ser usada como `.a` ou `.lib/.dll`
- Os usuários só precisam dos headers da pasta `include/`
