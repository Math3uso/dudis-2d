const fs = require("fs");
const path = require("path");

function getMainSrc(projectName) {

    const mainSrc = `#include "dudis2d/dudis2d.h"
#include "scenes/mainScene.h"

DD_NAMESPACE;

int main(){
    Window window(SizeI(800, 600), "${projectName}");
    window.keepWindowCentered(true);

    Resolution resolution = Resolution({800, 600}, ResolutionPolicy::Letterbox);

    window.setResolution(resolution);

    auto camera = DDCamera();
    window.setGlobalCamera(camera);

    SceneManager manager;

    auto mainScene = MainScene::create();

    manager.pushScene(move(mainScene));

    App::setSceneManager(manager);

    window.SetRenderManager(manager);

    window.Running();
}
`;

    return mainSrc;
}

function getSceneHeader() {
    const sceneHeader = `#pragma once
#include "dudis2d/dudis2d.h"

class MainScene : public Scene {
public:
  void start() override;
  void update() override;
  CREATE_SCENE(MainScene);
};
`;

    return sceneHeader;
}


function getSceneSrc() {
    const sceneSrc = `#include "scenes/mainScene.h"

DD_NAMESPACE

void MainScene::start() {

    this->label = "mainScene";
}

void MainScene::update() {}
`;

    return sceneSrc;
}

function getCMakeSrc(projectName) {
    return `cmake_minimum_required(VERSION 3.16)
project(${projectName} LANGUAGES CXX)


set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# busca automaticamente todos os .cpp e .h na pasta src
file(GLOB_RECURSE SRC_FILES CONFIGURE_DEPENDS
    "\${CMAKE_SOURCE_DIR}/src/*.cpp"
    "\${CMAKE_SOURCE_DIR}/src/*.h"
)

# cria o executável
add_executable(\${PROJECT_NAME} \${SRC_FILES})

# adiciona o diretório de includes da lib externa
target_include_directories(\${PROJECT_NAME} PRIVATE
    \${CMAKE_SOURCE_DIR}/extern/dudis2d/include
    \${CMAKE_SOURCE_DIR}/src 
)

target_link_libraries(\${PROJECT_NAME}
    \${CMAKE_SOURCE_DIR}/extern/dudis2d/bin/libdudis.a
     raylib
    m
    pthread
    dl
    rt
)

add_custom_command(TARGET \${PROJECT_NAME} POST_BUILD
    COMMAND\ \${CMAKE_COMMAND} -E copy_directory
    \${CMAKE_SOURCE_DIR}/assets
    \${CMAKE_SOURCE_DIR}/build/${projectName}/bin/assets
)


set_target_properties(\${PROJECT_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "$\{CMAKE_BINARY_DIR}/${projectName}/bin"
)

`;
}


function createNewProject(projectName) {
    //console.log("criando...");
    const currentPath = process.cwd();
    const dudis2d = process.env.DUDIS2D_PATH;
    const dudis2dHeaders = path.join(dudis2d, "include");
    const dudis2dLib = path.join(dudis2d, "build");

    //const dudis2dLibOut = path.join(currentPath, projectName, 'extern', 'dudis2d', 'bin');
    const dudis2dOut = path.join(currentPath, projectName, 'extern', 'dudis2d');

    const projectPath = path.join(currentPath, projectName);

    if (!fs.existsSync(dudis2d)) {
        console.log("erro: diretório DUDIS2D_PATH não encontrado!");
    }

    //criando diretorios
    fs.mkdirSync(projectPath);
    fs.mkdirSync(path.join(projectPath, "extern"));
    fs.mkdirSync(path.join(projectPath, "src", "scenes"), { recursive: true });
    fs.mkdirSync(path.join(projectPath, "assets"), { recursive: true });

    //copiando arquivos para o diretorio do projeto
    fs.cpSync(dudis2dLib, path.join(dudis2dOut, 'bin'), { recursive: true });
    fs.cpSync(dudis2dHeaders, path.join(dudis2dOut, "include"), { recursive: true });


    fs.writeFileSync(path.join(projectPath, "src", "main.cpp"), getMainSrc(projectName));
    fs.writeFileSync(path.join(projectPath, "CMakeLists.txt"), getCMakeSrc(projectName));
    fs.writeFileSync(path.join(projectPath, "src", "scenes", "mainScene.h"), getSceneHeader());
    fs.writeFileSync(path.join(projectPath, "src", "scenes", "mainScene.cpp"), getSceneSrc());
    fs.writeFileSync(path.join(projectPath, "dd-config.json"), `{
    "projectName": "${projectName}",
    "version": "1.0"
}`);

    // console.log(currentPath);
    // console.log(dudis2d);
    // console.log(dudis2dHeaders);
    // console.log(dudis2dLib);

    console.log(`Projeto ${projectName} criado com sucesso em ${projectPath}`);
    console.log("Vá para o diretorio e o compile");
    console.log(`cd ./${projectName}`);
    console.log("cmake -S . -B build");
    console.log("cmake --build build");
}

module.exports = createNewProject;