# 🎮 App - Exemplo de Desenvolvimento Integrado

Este é um exemplo de como desenvolver jogos usando a biblioteca **dudis2d** com **build automático**.

## 🚀 Como Usar

### **Desenvolvimento Rápido (Recomendado)**
```bash
# Compila e executa em um comando
./dev.sh make && ./app

# Ou apenas compila
./dev.sh make

# Ou apenas executa
./dev.sh ./app
```

### **Build Completo**
```bash
# Usa o script que reconhece novos arquivos automaticamente
./build.sh
```

### **Build Manual**
```bash
mkdir -p build
cd build
cmake .. -DCMAKE_BUILD_TYPE=Debug
make -j$(nproc)
```

## ✨ Características

### **🔄 Reconhecimento Automático**
- **Novos arquivos `.cpp`** são detectados automaticamente
- **Novos arquivos `.h`** são monitorados
- **Não precisa recriar build** quando adiciona arquivos
- **Recompilação inteligente** - só recompila o que mudou

### **📁 Estrutura Flexível**
```
app/
├── main.cpp              # Arquivo principal
├── game/                 # Módulos do jogo
│   ├── player.cpp
│   ├── player.h
│   ├── enemy.cpp
│   └── enemy.h
├── ui/                   # Interface
│   ├── menu.cpp
│   └── menu.h
├── CMakeLists.txt        # Configuração automática
├── build.sh             # Script de build
└── README.md            # Este arquivo
```

### **⚡ Desenvolvimento Rápido**
```bash
# Adiciona um novo arquivo
touch game/powerup.cpp
touch game/powerup.h

# Recompila e executa automaticamente
./dev.sh make && ./app

# Funciona sem problemas! 🎉
```

## 🔧 Configurações

### **CMakeLists.txt Otimizado**
- `GLOB_RECURSE` para encontrar arquivos automaticamente
- Monitoramento de headers para recompilação
- Configurações de debug ativadas
- Link automático com dudis2d

### **Script de Build**
- Configuração automática do CMake
- Compilação paralela
- Mensagens informativas
- Tratamento de erros

## 🎯 Exemplo de Uso

```cpp
// main.cpp
#include "dudis2d/dudis2d.h"
#include "game/player.h"  // ← Novo arquivo detectado automaticamente

int main() {
    // Seu código aqui
    return 0;
}
```

```bash
# Adiciona novos arquivos
echo "// player.h" > game/player.h
echo "// player.cpp" > game/player.cpp

# Recompila e executa (reconhece automaticamente!)
./dev.sh make && ./app
```

## 🐛 Debug

- **Breakpoints** funcionam em todos os arquivos
- **Modificações** são detectadas automaticamente
- **Recompilação** só do que mudou
- **Logs** detalhados durante o build

## 📋 Dicas

1. **Use `./dev.sh make && ./app`** para desenvolvimento rápido
2. **Adicione arquivos** livremente - são detectados automaticamente
3. **Não precisa recriar build** quando adiciona novos arquivos
4. **Debug** funciona perfeitamente
5. **Desenvolvimento rápido** e iterativo

**Perfeito para desenvolvimento de jogos!** 🎮
