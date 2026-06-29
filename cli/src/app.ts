import { defineCommand, runMain } from "citty";
import { version } from "./commands/version";
import { create } from "./commands/new";
import { test } from "./commands/dd-test";

const dudis = defineCommand({
    meta: { name: "dudis", description: "dudis cli" },
    args: {
        version: {
            type: "boolean",
            alias: "v",
            description: "Mostrar versão atual do dudis-2d"
        }
    },
    run({ args }) {
        if (args.version) {
            console.log("1.0.0");
        }
    },
    subCommands: {
        version,
        create,
        test
    },
});

runMain(dudis);