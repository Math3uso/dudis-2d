#!/usr/bin/env node

const fs = require("fs");
const path = require("path");
const { Command } = require('commander');

const program = new Command();


program.name("dudis2d")
    .description("CLI para gerenciamento de projetos DUDIS-2D")
    .version("1.0.0")
    .action(() => {
        console.log("Use um comando para continuar. Use --help para ver os comandos disponíveis.");
    });

program.command("new")
    .description("Cria um novo projeto DUDIS-2D")
    .argument("<projectName>", "Nome do novo projeto")
    .action((projectName) => {
        console.log(`Criando novo projeto: ${projectName}`);
    });


program.command("scene")
    .description("Cria uma nova cena")
    .argument("<sceneName>", "Nome da nova cena")
    .action((sceneName) => {

        const currentDir = process.cwd();
        const sceneDir = path.join(currentDir, sceneName);

        if (!fs.existsSync(sceneDir)) {
            fs.mkdirSync(sceneDir);
        }

        let clasName = sceneName.charAt(0).toUpperCase() + sceneName.slice(1);

        fs.writeFileSync(
            path.join(sceneDir, `${sceneName}.h`), `
// Cena: ${sceneName}
#pragma once
#include "dudis2d/dudis2d.h"

class ${clasName} : public Scene {
public:
  void start() override;
  void update() override;
  CREATE_SCENE(${clasName});
};
            `
        );

        fs.writeFileSync(
            path.join(sceneDir, `${sceneName}.cpp`), `
// Cena: ${sceneName}
#include "scenes/${sceneName}/${sceneName}.h"

DD_NAMESPACE;

void ${clasName}::start() {

  // Inicialização da cena

  this->label = "${sceneName}";
}

void ${clasName}::update() {
  // Lógica de atualização da cena
}
            `
        );

        console.log(`✅ Scene '${sceneName}' criada em: ${sceneDir}`);
    });


program.parse(process.argv);