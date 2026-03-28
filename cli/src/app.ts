#!/usr/bin/env node

import { Command } from "commander";
import { z } from "zod";
import { program } from 'commander';
import { DDRegisterCommand } from "./core/register.js";
import { NewProject } from "./commands/newProject.js";

const ddHello = new Command("new")
    .option("-n, --name <projectName>", "Nome do projeto")
    .action((options: { name: string }) => {
        console.log("Nome:", options.name);
        console.log(options);
    });
function start() {
    const program = new Command();

    program.name("dudis").description("dudis CLI").version("1.0.0");

    // program.addCommand(ddHello);

    DDRegisterCommand(program, new NewProject());

    program.parse();
}

start();