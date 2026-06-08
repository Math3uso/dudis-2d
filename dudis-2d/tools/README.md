# Tools

Scripts auxiliares para compilar e rodar os testes do projeto.

## Compilar testes

```bash
./build_test.sh unit
./build_test.sh platform
./build_test.sh all
```

Pelo wrapper:

```bash
./ddtools.sh build unit
./ddtools.sh build platform
```

## Rodar testes

```bash
./run_test.sh unit
./run_test.sh platform
./run_test.sh all
```

Pelo wrapper:

```bash
./ddtools.sh run unit
./ddtools.sh run platform
```

## Rodar um TEST_CASE especifico

Ao chamar apenas o target, o script lista os `TEST_CASE`s com indice:

```bash
./run_test.sh ddgl_render_gl_platform
```

Exemplo de saida:

```text
0 - ddgl render gl platform context initializes and shuts down
1 - should be able to draw a quad
2 - should be able to draw a quad with a texture
```

Para nao precisar passar por todos os testes manuais, rode o target do teste e passe o nome do `TEST_CASE` como filtro do Catch2:

```bash
./run_test.sh ddgl_render_gl_platform "sem nome por enquanto" -s
```

Ou passe o indice mostrado na lista:

```bash
./run_test.sh ddgl_render_gl_platform 7 -s
```

Ou pelo wrapper:

```bash
./ddtools.sh run ddgl_render_gl_platform "sem nome por enquanto" -s
./ddtools.sh run ddgl_render_gl_platform 7 -s
```

O `-s` mostra a saida completa do Catch2.

Tambem da para filtrar por tags:

```bash
./run_test.sh ddgl_render_gl_platform "[platform][ddgl]" -s
```

Para rodar todos os `TEST_CASE`s de um target especifico:

```bash
./run_test.sh ddgl_render_gl_platform --all-tests
```

Os binarios sao executados a partir da pasta `tests/`, entao caminhos relativos como `assets/player.png` continuam funcionando.
