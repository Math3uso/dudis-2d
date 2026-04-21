import { defineCommand } from "citty";

export const version = defineCommand({
    meta: { name: "version", description: "versão atual do dudis-2d" },
    run() {
        return console.log("1.0.0");
    }
});