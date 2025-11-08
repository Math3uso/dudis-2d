# Começando com dudis2d

Antes de irmos para o código, vamos analisar a **estrutura básica** criada pelo dudis2d.  
Quando você cria um projeto novo, vai se deparar com algo assim:

```bash
MyGame/
├── build
├── extern
├── src/
│   ├── scenes/
│   │   ├── mainScene.cpp
│   │   └── mainScene.h
│   └── main.cpp
└── CMakeLists.txt
```
- Todo o código que vamos escrever está dentro de src/. Lá ficam nossas classes e scenes.
- O diretório extern/ contém o dudis2d e suas dependências.
- Você também pode adicionar ou alterar dependências lá, caso ache necessário.

Agora que já sabemos como é a estrutura, vamos dar uma olhada no ``src/main.cpp``:


```cpp

#include <iostream>
#include "dudis2d/dudis2d.h"
#include "scenes/mainScene.h"

int main() {

    Window window({800, 600}, "app");

    auto scene = MainScene::create();

    SceneManager manager;

    App::setSceneManager(manager);

    manager.pushScene(move(scene));

    window.SetRenderManager(manager);

    window.Running();

    return 0;
}
```
Beleza... e oq é tudo isso? vamos por partes.

Primeiro, **vamos apagar tudo e começar do básico**:

```cpp

#include <iostream>
#include "dudis2d/dudis2d.h"
#include "scenes/mainScene.h"

int main() {

    Window window({800, 600}, "app");

    return 0;
}
```

### Criando a janela

- O primeiro argumento é o **tamanho**, que no ``dudis2d`` é representado por ``Size`` ou ``SizeI``. Ele recebe **largura e altura**
- O segundo argumento é o **título da janela**.

Resumindo: criamos uma janela ``800x600`` com o título ``"app"``.


### Iniciando a janela
Para que a janela realmente funcione, precisamos iniciar o loop da janela.
Basta adicionar a linha:
```cpp
int main() {

    Window window({800, 600}, "app");

    window.Running(); // começa o loop da jánela

    return 0;
}
```

Essa é a habordagem mais simples de criar uma janela no ``dudis2d``.

### Desenhando na janela

Agora que inicializamos a janela, vamos finalmente desenhar algo nela. Podemos fazer isso de duas formas.

## Aviso ⚠️
apartir daqui vamos mostrar como desenhar na tela de **forma manual** e é totalmente opcional e não recomendado, caso queira ir para forma correta...



### desenhando de forma manual

Para desenhar manualmente, **não usaremos o método `Running`**, pois ele **abstrai** algumas coisas que vamos precisar controlar. 
vamos fazer algumas alterações no código:
```cpp
 Window window({800, 600}, "app");

    while (window.isOpen())
    {
        window.beginDrawing();

        window.SetClearColor({36, 36, 36, 255});

        window.endDrawing();
    }

    window.close();
```
bem mais código né? 

O método Running faz tudo isso por você automaticamente, mas a desvantagem é que não podemos desenhar diretamente na janela — para isso precisaríamos usar um Render Manager, que veremos mais tarde.


No código é possivel analisar que:
- Todo o código está dentro de um loop que verifica se a janela ainda está aberta ``(window.isOpen())``.
- ``window.beginDrawing();`` aqui nos iniciamos o **modo desenho** da janela, tudo abaixo disso pode ser desenhando.

- ``window.SetClearColor({36, 36, 36, 255});`` → define a cor de fundo da janela.

- ``window.close();`` → libera os recursos da janela quando o programa termina.

Até agora, nosso código só cria uma janela de forma **manual**, mas ainda **não desenha nada**.  

Para desenharmos, precisamos incluir as funcionalidades necessárias para renderização. É bem simples, basta adicionar:
```cpp
#include "dudis2d/graphics.h"
```
Se você quiser simplificar ainda mais, pode usar a macro:

```cpp
DD_RENDER // faz o include automatico
```

isso vai nos dar as funcionalidades necessarias para desenhar algo, agr sim finalmente nosso "olá, mundo!"

```cpp
#include <iostream>
#include "dudis2d/dudis2d.h"
// #include "scenes/mainScene.h" // ainda n estamos usando

DD_RENDER;

int main()
{

    Window window({800, 600}, "app");

    auto text = dudis::Text::create("Olá, Mundo!", 28);
    text->setTextColor(WHITE);

    while (window.isOpen())
    {
        window.beginDrawing();

        window.SetClearColor({36, 36, 36, 255});

        text->render();

        window.endDrawing();
    }

    window.close();

    return 0;
}
```
Parabens vc criou seu primeiro **"Olá, Mundo!"** =).

``auto text = dudis::Text::create("Olá, Mundo!", 28);`` - essa linha cria um um ponteiro da classe "text" o primeiro argumento é o conteudo e o segundo o tamanho da fonte

após isso basta usar o metodo "render" no loop que o texto será desenhado.

Mas... essa não é a forma recomendada de fazer isso, a não ser que vc queira ter total controle da renderização e usar funções do proprio **raylib** (sim vc pode fazer isso)
```cpp
 while (window.isOpen())
    {
        window.beginDrawing();

        window.SetClearColor({36, 36, 36, 255});

        DrawText("Texto", 100, 100, 20, WHITE); // isso funciona
 
        window.endDrawing();
    }
```
porem em algum momento você terá que gerenciar e criar todos os recursos por conta propria, e não é isso que queremos...

Lembra da quele codigo que foi gerado automaticamente no inicio do projeto? Vamos recria-lo e fazer um **``Olá, Mundo``** de forma correta.

## Fazendo de forma recomendada

Vamos mudar o codigo base, e deixa-lo assim:
```cpp
int main()
{

    Window window({800, 600}, "app");

    window.Running();

    return 0;
}

```

Quando usamos o método ``Running``, perdemos o acesso direto às funções de **desenho** da janela.
Por isso, precisamos de um Render Manager — um sistema responsável por cuidar da renderização.

No **dudis2d**, um ótimo exemplo de Render Manager são as **Scenes**.
Elas não apenas **renderizam** na janela, mas também gerenciam todos os recursos adicionados dentro delas, como sprites, textos e outros elementos, cuidando inclusive da memória.

Certo… vamos então criar uma **Scene**.
Se você reparar, já existe uma cena padrão chamada **MainScene**.
Antes de entendermos a fundo como ela funciona, vamos utilizá-la no nosso projeto.

Primeiro **includa** ela, provavelmenete deve ter algo assim:
```cpp
#include "scenes/mainScene.h"
```
com a **Scene** incluida vamos usa-la no projeto:
```cpp
    //antes do Running(), instancie a scene
    auto scene = MainScene::create();

    //agora vc precisa delcarar o SceneManager
    //ele vai gerenciar todas as scenes, com funções de:
    // - deletar 
    // - trocar de scene
    // - persistir uma scene
    SceneManager manager;

    //agr passe o sceneManager para uma variavel global.
    // falaremos disso mais tarde
    App::setSceneManager(manager);

    // por fim adicione a scene no manager
    manager.pushScene(move(scene));


    window.SetRenderManager(manager);

```
Esse código cria uma Scene e a “empilha” (falaremos sobre isso mais tarde).
Quando usamos window.SetRenderManager(manager);, estamos dizendo à Window:

> **“Quero que o manager cuide da renderização.”**

O ``SceneManager`` é responsável por gerenciar as scenes — por exemplo: trocar de cena, empilhar novas cenas ou removê-las.
Por conta disso, precisamos adicioná-lo ao App usando ``App::setSceneManager(manager);``.
Assim, o **SceneManager** fica acessível globalmente, sem criar cópias desnecessárias.