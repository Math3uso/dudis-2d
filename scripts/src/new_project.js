#!/usr/bin/env node


const fs = require("fs");
const path = require("path");

const origem = process.env.DUDIS2D_PATH;

if (!fs.existsSync(origem)) {
    console.error("Erro: diretório DUDIS2D_PATH não encontrado!");
    process.exit(1);
}

// Diretório atual de execução (onde você chamou o script)
const cwd = process.cwd();

const projeto = process.argv[2] || 'MyProject';

const projectPath = path.join(cwd, projeto);

// const origem = path.join(__dirname, "../../dudis-2d");
const libDestino = path.join(projectPath, 'extern', 'dudis2d');

fs.mkdirSync(path.join(projectPath, 'src', 'scenes'), { recursive: true });
fs.mkdirSync(path.join(projectPath, 'src'), { recursive: true });
fs.mkdirSync(path.join(projectPath, 'extern'), { recursive: true });

fs.cpSync(origem, libDestino, { recursive: true });


fs.writeFileSync(path.join(projectPath, 'src', 'main.cpp'), `#include <iostream>
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
`);

fs.writeFileSync(path.join(projectPath, 'src', 'scenes', 'mainScene.h'), `#pragma once

#include "dudis2d/dudis2d.h"

class MainScene : public Scene
{
public:
    void start() override;
    void update() override;
    CREATE_SCENE(MainScene);
};
`);

// mainScene.cpp
fs.writeFileSync(path.join(projectPath, 'src', 'scenes', 'mainScene.cpp'), `#include "scenes/mainScene.h"

void MainScene::start()
{
    label = "scene main";
}

void MainScene::update() {}
`);

fs.writeFileSync(path.join(projectPath, 'CMakeLists.txt'), `cmake_minimum_required(VERSION 3.10)
project(app)

set(CMAKE_CXX_STANDARD 17)

# Adiciona a lib externa
add_subdirectory(./extern/dudis2d build_dudis)

file(GLOB_RECURSE SRC_FILES src/*.cpp)

# Executável
add_executable(app \${SRC_FILES})

# Linka a lib
target_link_libraries(app dudis)

# Inclui os headers do próprio app (src/)
target_include_directories(app PRIVATE \${CMAKE_CURRENT_SOURCE_DIR}/src)
`);


console.log(`Projeto "${projeto}" criado com sucesso em ${projectPath}!`);
console.log("Vá para o diretorio e o compile");
console.log(`cd ./${projeto}`);
console.log("mkdir build && cd build");
console.log("cmake ..");
console.log("make && ./app");
