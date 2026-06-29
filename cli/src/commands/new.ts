import { defineCommand } from "citty";
import path from "path";
import fs from "fs";

export const create = defineCommand({
    meta: { name: "create", description: "cria um projeto dudis-2d" },
    args: {
        name: {
            type: "string",
            alias: "n",
            description: "nome do projeto",
            required: true
        },
        dir: {
            type: "string",
            alias: "d",
            description: "onde o projeto deve ser criado",
            default: path.join(process.cwd())
        }
    },
    run({ args }) {

        const { name, dir } = args;

        console.log("nome do projeto: ", args.name);
        console.log(`diretorio: ${args.dir}`);

        const projectPath = path.join(dir);

        // fs.mkdirSync(`${projectPath}/${name}`);
    }
});