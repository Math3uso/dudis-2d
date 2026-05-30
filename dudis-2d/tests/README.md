# Testes do `dudis-2d`

Este diretório concentra os testes automatizados e os benchmarks manuais do projeto.

Hoje a estrutura está separada por objetivo:

- `unit/`: testes rápidos, determinísticos, sem janela.
- `platform/`: testes de backend, janela, input e render de baixo nível.
- `smoke/`: testes de integração curtos com janela/contexto gráfico real.
- `benchmarks/`: binários manuais para medir performance.
- `support/`: helpers compartilhados entre testes.
- `assets/`: assets usados pelos testes.

## Índice

- [Visão Geral do Fluxo](#visao-geral-do-fluxo)
- [Presets Disponíveis](#presets-disponiveis)
- [Estrutura Atual](#estrutura-atual)
- [Como Configurar com Preset](#como-configurar-com-preset)
- [Como Compilar com Preset](#como-compilar-com-preset)
- [Como Configurar Manualmente](#como-configurar-manualmente)
- [Como Compilar Manualmente](#como-compilar-manualmente)
- [Como Listar os Testes](#como-listar-os-testes)
- [Como Rodar os Testes](#como-rodar-os-testes)
- [Como Rodar Benchmarks](#como-rodar-benchmarks)
- [Como Criar Novos Testes](#como-criar-novos-testes)
- [Script para Criar Teste](#script-para-criar-teste)
- [Scripts em `dudis-2d/tools`](#scripts-em-dudis-2dtools)
- [Helpers Compartilhados](#helpers-compartilhados)
- [Convenções Recomendadas](#convencoes-recomendadas)
- [Resumo Rápido](#resumo-rapido)

## Visão Geral do Fluxo

Há dois fluxos principais:

1. Fluxo rápido
Usa o preset `tests-debug`.
Compila:

- `unit`
- `benchmarks`

2. Fluxo gráfico
Usa o preset `tests-debug-graphics`.
Compila:

- `unit`
- `platform`
- `smoke`
- `benchmarks`

Isso existe para o ciclo de desenvolvimento rápido não depender de janela nem de ambiente gráfico.

Também é possível fazer exatamente o mesmo fluxo sem preset, usando `cmake -S ... -B ...` manualmente. As duas formas estão documentadas abaixo.

## Presets Disponíveis

Os presets ficam em [CMakePresets.json](/home/r6/pasta/dudis-2d/dudis-2d/tests/CMakePresets.json).

- `tests-debug`
Build rápido de desenvolvimento.
Diretório: `tests/build/unit-debug`

- `tests-debug-graphics`
Build com suites gráficas.
Diretório: `tests/build/graphics-debug`

- `tests-release`
Build release sem suites gráficas.
Diretório: `tests/build/unit-release`

## Estrutura Atual

Exemplos reais da árvore:

- [tests/unit/entity/entity.test.cpp](/home/r6/pasta/dudis-2d/dudis-2d/tests/unit/entity/entity.test.cpp)
- [tests/platform/ddgl/render_gl.test.cpp](/home/r6/pasta/dudis-2d/dudis-2d/tests/platform/ddgl/render_gl.test.cpp)
- [tests/platform/window/window_context.test.cpp](/home/r6/pasta/dudis-2d/dudis-2d/tests/platform/window/window_context.test.cpp)
- [tests/smoke/window/init_window.test.cpp](/home/r6/pasta/dudis-2d/dudis-2d/tests/smoke/window/init_window.test.cpp)
- [tests/smoke/scene/scene_smoke.test.cpp](/home/r6/pasta/dudis-2d/dudis-2d/tests/smoke/scene/scene_smoke.test.cpp)
- [tests/benchmarks/scene_benchmark.cpp](/home/r6/pasta/dudis-2d/dudis-2d/tests/benchmarks/scene_benchmark.cpp)

## Como Configurar com Preset

Entre na pasta de testes:

```bash
cd dudis-2d/tests
```

### Configurar o build rápido

```bash
cmake --preset tests-debug
```

### Configurar o build gráfico

```bash
cmake --preset tests-debug-graphics
```

### Configurar o build release

```bash
cmake --preset tests-release
```

Configurar não compila. Depois de qualquer `cmake --preset ...`, rode também `cmake --build ...` antes de usar `ctest`.

## Como Compilar com Preset

### Compilar tudo do fluxo rápido

```bash
cmake --build --preset tests-debug
```

Isso compila:

- `unit`
- `benchmarks`

### Compilar tudo do fluxo gráfico

```bash
cmake --build --preset tests-debug-graphics
```

Isso compila:

- `unit`
- `platform`
- `smoke`
- `benchmarks`

### Compilar todos os testes de uma categoria

Na prática, hoje a compilação por categoria funciona assim:

- `unit`: use o preset rápido e compile o build todo, ou um target específico.
- `platform`: use o preset gráfico.
- `smoke`: use o preset gráfico.
- `benchmarks`: pode compilar só o target de benchmark.

Exemplos:

```bash
cmake --preset tests-debug
cmake --build --preset tests-debug
```

```bash
cmake --preset tests-debug-graphics
cmake --build --preset tests-debug-graphics
```

```bash
cmake --preset tests-debug
cmake --build build/unit-debug --target scene_benchmark
```

### Compilar apenas 1 target de teste

Para `unit`, use o nome do target no build rápido:

```bash
cmake --preset tests-debug
cmake --build build/unit-debug --target entity_unit
```

Para `platform` e `smoke`, use o build gráfico:

```bash
cmake --preset tests-debug-graphics
cmake --build build/graphics-debug --target ddgl_render_gl_platform
cmake --build build/graphics-debug --target window_context_platform
cmake --build build/graphics-debug --target window_smoke
cmake --build build/graphics-debug --target scene_smoke
```

## Como Configurar Manualmente

Entre na pasta de testes:

```bash
cd dudis-2d/tests
```

### Configurar build sem suites gráficas

Esse build gera a pasta `build/unit-debug` e deixa `platform` e `smoke` de fora.

```bash
cmake -S . -B build/unit-debug -G Ninja \
  -DCMAKE_BUILD_TYPE=Debug \
  -DDD_BUILD_GRAPHICAL_TESTS=OFF
```

### Configurar build com suites gráficas

Esse build gera a pasta `build/graphics-debug` e inclui `platform` e `smoke`.

```bash
cmake -S . -B build/graphics-debug -G Ninja \
  -DCMAKE_BUILD_TYPE=Debug \
  -DDD_BUILD_GRAPHICAL_TESTS=ON
```

### Configurar build release sem suites gráficas

```bash
cmake -S . -B build/unit-release -G Ninja \
  -DCMAKE_BUILD_TYPE=Release \
  -DDD_BUILD_GRAPHICAL_TESTS=OFF
```

### Trocar o compilador manualmente

Se você quiser testar outro compilador sem depender de preset, basta configurar o build com `CC` e `CXX`.

Exemplo com `clang`:

```bash
CC=clang CXX=clang++ cmake -S . -B build/unit-debug-clang -G Ninja \
  -DCMAKE_BUILD_TYPE=Debug \
  -DDD_BUILD_GRAPHICAL_TESTS=OFF
```

Exemplo com build gráfico em `clang`:

```bash
CC=clang CXX=clang++ cmake -S . -B build/graphics-debug-clang -G Ninja \
  -DCMAKE_BUILD_TYPE=Debug \
  -DDD_BUILD_GRAPHICAL_TESTS=ON
```

Se o diretório de build já tiver sido configurado com outro compilador, o ideal é usar outro `-B` ou limpar o cache antes de reconfigurar.

## Como Compilar Manualmente

### Compilar tudo do build sem suites gráficas

```bash
cmake --build build/unit-debug
```

Isso compila:

- `unit`
- `benchmarks`

### Compilar tudo do build com suites gráficas

```bash
cmake --build build/graphics-debug
```

Isso compila:

- `unit`
- `platform`
- `smoke`
- `benchmarks`

### Compilar todos os testes de uma categoria

Na prática, hoje a compilação por categoria funciona assim:

- `unit`: configure com `DD_BUILD_GRAPHICAL_TESTS=OFF` e compile o build inteiro, ou um target específico.
- `platform`: configure com `DD_BUILD_GRAPHICAL_TESTS=ON`.
- `smoke`: configure com `DD_BUILD_GRAPHICAL_TESTS=ON`.
- `benchmarks`: pode compilar só o target de benchmark.

Exemplos:

```bash
cmake -S . -B build/unit-debug -G Ninja \
  -DCMAKE_BUILD_TYPE=Debug \
  -DDD_BUILD_GRAPHICAL_TESTS=OFF
cmake --build build/unit-debug
```

```bash
cmake -S . -B build/graphics-debug -G Ninja \
  -DCMAKE_BUILD_TYPE=Debug \
  -DDD_BUILD_GRAPHICAL_TESTS=ON
cmake --build build/graphics-debug
```

```bash
cmake --build build/unit-debug --target scene_benchmark
```

### Compilar apenas 1 target de teste

Para `unit`:

```bash
cmake --build build/unit-debug --target entity_unit
```

Para `platform` e `smoke`:

```bash
cmake --build build/graphics-debug --target ddgl_render_gl_platform
cmake --build build/graphics-debug --target window_context_platform
cmake --build build/graphics-debug --target window_smoke
cmake --build build/graphics-debug --target scene_smoke
```

## Como Listar os Testes

O `ctest -N` lista os testes descobertos no build. Se o build acabou de ser configurado e ainda não foi compilado, o Catch2 pode listar alvos `*_NOT_BUILT`; compile primeiro com `cmake --build ...`.

### Listar os testes do build rápido

```bash
ctest --test-dir build/unit-debug -N
```

### Listar os testes do build gráfico

```bash
ctest --test-dir build/graphics-debug -N
```

## Como Rodar os Testes

### Rodar todos os testes do build rápido

```bash
ctest --test-dir build/unit-debug --output-on-failure
```

### Rodar todos os testes do build gráfico

```bash
ctest --test-dir build/graphics-debug --output-on-failure
```

### Rodar todos os testes de uma categoria

#### Unit

```bash
ctest --test-dir build/unit-debug -L unit --output-on-failure
```

#### Smoke

```bash
ctest --test-dir build/graphics-debug -L smoke --output-on-failure
```

#### Platform

```bash
ctest --test-dir build/graphics-debug -L platform --output-on-failure
```

### Rodar apenas 1 teste pelo nome

Você pode filtrar pelo nome do teste com `-R`.

Exemplos:

```bash
ctest --test-dir build/unit-debug -R "entity" --output-on-failure
```

```bash
ctest --test-dir build/graphics-debug -R "window initializes" --output-on-failure
```

### Rodar 1 executável de teste diretamente

Às vezes isso é útil para depurar.

Exemplo com `unit`:

```bash
./build/unit-debug/bin/entity_unit
```

Exemplo filtrando dentro do executável:

```bash
./build/unit-debug/bin/entity_unit "entity creation keeps the tag"
```

Exemplo com `smoke`:

```bash
./build/graphics-debug/bin/window_smoke
```

Exemplo com `platform`:

```bash
./build/graphics-debug/bin/ddgl_render_gl_platform
```

## Como Rodar Benchmarks

Benchmarks não entram no `ctest`.
Eles são binários manuais.

Exemplo com preset:

```bash
cmake --preset tests-debug
cmake --build build/unit-debug --target scene_benchmark
./build/unit-debug/bin/scene_benchmark
```

Exemplo manual:

```bash
cmake -S . -B build/unit-debug -G Ninja \
  -DCMAKE_BUILD_TYPE=Debug \
  -DDD_BUILD_GRAPHICAL_TESTS=OFF
cmake --build build/unit-debug --target scene_benchmark
./build/unit-debug/bin/scene_benchmark
```

Se você quiser medir cenários gráficos reais, normalmente faz mais sentido usar o build gráfico e rodar o benchmark a partir de `build/graphics-debug/bin`.

## Como Criar Novos Testes

Os testes são registrados em um único lugar: [tests/CMakeLists.txt](/home/r6/pasta/dudis-2d/dudis-2d/tests/CMakeLists.txt).
As subpastas guardam só os arquivos `.test.cpp`.

### Criar um novo teste `unit`

Estrutura sugerida:

```text
tests/unit/<nome>/
  <nome>.test.cpp
```

Exemplo:

```text
tests/unit/collision/
  collision.test.cpp
```

Registro em `tests/CMakeLists.txt`:

```cmake
dd_add_test(collision_unit
  SUITE unit
  SOURCES
    unit/collision/collision.test.cpp
)
```

### Criar um novo teste `platform`

Estrutura:

```text
tests/platform/<grupo>/
  <nome>.test.cpp
```

Registro em `tests/CMakeLists.txt`:

```cmake
dd_add_test(render_gl_platform
  SUITE platform
  SOURCES
    platform/ddgl/render_gl.test.cpp
)
```

### Criar um novo teste `smoke`

Estrutura:

```text
tests/smoke/<nome>/
  <nome>.test.cpp
```

Registro em `tests/CMakeLists.txt`:

```cmake
dd_add_test(audio_smoke
  SUITE smoke
  SOURCES
    smoke/audio/audio_smoke.test.cpp
)
```

### Criar um novo benchmark

Estrutura:

```text
tests/benchmarks/
  <nome>.cpp
```

E registrar em [tests/CMakeLists.txt](/home/r6/pasta/dudis-2d/dudis-2d/tests/CMakeLists.txt):

```cmake
dd_add_benchmark(my_benchmark
  SOURCES
    my_benchmark.cpp
)
```

## Script para Criar Teste

Existe um gerador simples em [tools/new_test.sh](/home/r6/pasta/dudis-2d/dudis-2d/tools/new_test.sh).

Uso:

```bash
cd dudis-2d/tools
./new_test.sh physics unit
```

Isso cria:

```text
tests/unit/physics/
  physics.test.cpp
```

E adiciona o bloco `dd_add_test(...)` correspondente em `tests/CMakeLists.txt`.

Outro exemplo:

```bash
./new_test.sh startup smoke
```

Observações:

- se você não informar a categoria, ele usa `unit`
- hoje ele só gera `unit`, `platform` ou `smoke`
- ele gera um esqueleto simples; talvez você queira ajustar o nome do target manualmente depois

## Scripts em `dudis-2d/tools`

### `build_test.sh`

Arquivo: [tools/build_test.sh](/home/r6/pasta/dudis-2d/dudis-2d/tools/build_test.sh)

Serve para configurar e compilar testes sem digitar todos os comandos do CMake.

Uso:

```bash
cd dudis-2d/tools
./build_test.sh all
./build_test.sh unit
./build_test.sh platform
./build_test.sh smoke
./build_test.sh benchmarks
./build_test.sh entity_unit
```

O que cada modo faz:

- `all`: configura `tests-debug` e `tests-debug-graphics`, depois compila os dois builds
- `unit`: configura `tests-debug` e compila o build rápido inteiro
- `platform`: configura `tests-debug-graphics` e compila o build gráfico inteiro
- `smoke`: configura `tests-debug-graphics` e compila o build gráfico inteiro
- `benchmarks`: configura `tests-debug` e compila o target `dd_benchmarks`
- `<nome_do_target>`: tenta compilar apenas um target no build rápido

Importante:

- targets `platform` e `smoke` individuais precisam do build gráfico
- o modo `<nome_do_target>` hoje assume o build rápido
- então `ddgl_render_gl_platform` e `window_smoke` são melhores de compilar manualmente com `build/graphics-debug`

Exemplo manual correto:

```bash
cd dudis-2d/tests
cmake --preset tests-debug-graphics
cmake --build build/graphics-debug --target ddgl_render_gl_platform
cmake --build build/graphics-debug --target window_smoke
```

### `run_test.sh`

Arquivo: [tools/run_test.sh](/home/r6/pasta/dudis-2d/dudis-2d/tools/run_test.sh)

Serve para rodar suites por categoria ou um binário específico.

Uso:

```bash
cd dudis-2d/tools
./run_test.sh all
./run_test.sh unit
./run_test.sh platform
./run_test.sh smoke
./run_test.sh benchmarks
./run_test.sh entity_unit
```

O que ele faz:

- `all`: roda `ctest` no build rápido e no build gráfico
- `unit`: roda `ctest -L unit` no build rápido
- `platform`: roda `ctest -L platform` no build gráfico
- `smoke`: roda `ctest -L smoke` no build gráfico
- `benchmarks`: roda `scene_benchmark`
- `<nome_do_target>`: executa um binário de `build/unit-debug/bin` ou `build/graphics-debug/bin`

Importante:

- no modo `<nome_do_target>`, ele procura primeiro em `build/unit-debug/bin` e depois em `build/graphics-debug/bin`
- para targets gráficos, o build gráfico precisa ter sido compilado antes

Exemplo:

```bash
./build/graphics-debug/bin/ddgl_render_gl_platform
./build/graphics-debug/bin/window_smoke
```

### `new_test.sh`

Arquivo: [tools/new_test.sh](/home/r6/pasta/dudis-2d/dudis-2d/tools/new_test.sh)

Gera o esqueleto de um novo teste.

Uso:

```bash
cd dudis-2d/tools
./new_test.sh entity unit
./new_test.sh ddgl/render platform
./new_test.sh startup smoke
```

## Helpers Compartilhados

Os testes compartilham utilitários em:

- [tests/support/test_context.h](/home/r6/pasta/dudis-2d/dudis-2d/tests/support/test_context.h)
- [tests/support/test_context.cpp](/home/r6/pasta/dudis-2d/dudis-2d/tests/support/test_context.cpp)
- [tests/support/platform_test_context.h](/home/r6/pasta/dudis-2d/dudis-2d/tests/support/platform_test_context.h)
- [tests/support/platform_test_context.cpp](/home/r6/pasta/dudis-2d/dudis-2d/tests/support/platform_test_context.cpp)
- [tests/support/test_paths.h](/home/r6/pasta/dudis-2d/dudis-2d/tests/support/test_paths.h)

Se você estiver criando `platform`, `smoke` ou benchmark, o ideal é reaproveitar esses helpers.

## Convenções Recomendadas

- nomeie targets com o tipo no final
Ex.: `entity_unit`, `ddgl_render_gl_platform`, `window_smoke`

- nomeie o arquivo com `.test.cpp`
Ex.: `entity.test.cpp`, `render_gl.test.cpp`, `window_smoke.test.cpp`

- use a tag correspondente no `TEST_CASE`
Ex.: `"[unit]"`, `"[platform][ddgl]"`, `"[smoke]"`

- mantenha `unit` sem dependência de janela, render ou assets externos sempre que possível

- use `platform` para validar backend, janela, input, render device e integrações de plataforma

- use `smoke` para validar integração e "não crasha"

- use `benchmarks` para medição manual, não para gating do `ctest`

## Resumo Rápido

### Build rápido com preset

```bash
cd dudis-2d/tests
cmake --preset tests-debug
cmake --build --preset tests-debug
ctest --test-dir build/unit-debug -L unit --output-on-failure
```

### Build gráfico com preset

```bash
cd dudis-2d/tests
cmake --preset tests-debug-graphics
cmake --build --preset tests-debug-graphics
ctest --test-dir build/graphics-debug -L platform --output-on-failure
ctest --test-dir build/graphics-debug -L smoke --output-on-failure
```

### Build manual sem suites gráficas

```bash
cd dudis-2d/tests
cmake -S . -B build/unit-debug -G Ninja \
  -DCMAKE_BUILD_TYPE=Debug \
  -DDD_BUILD_GRAPHICAL_TESTS=OFF
cmake --build build/unit-debug
ctest --test-dir build/unit-debug -L unit --output-on-failure
```

### Build manual com suites gráficas

```bash
cd dudis-2d/tests
cmake -S . -B build/graphics-debug -G Ninja \
  -DCMAKE_BUILD_TYPE=Debug \
  -DDD_BUILD_GRAPHICAL_TESTS=ON
cmake --build build/graphics-debug
ctest --test-dir build/graphics-debug -L platform --output-on-failure
ctest --test-dir build/graphics-debug -L smoke --output-on-failure
```

### Um target específico

```bash
cmake --build build/unit-debug --target entity_unit
ctest --test-dir build/unit-debug -R "entity" --output-on-failure
```

### Benchmark

```bash
cmake --build build/unit-debug --target scene_benchmark
./build/unit-debug/bin/scene_benchmark
```
