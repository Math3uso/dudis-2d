import { Command, program } from "commander";
import type { DDCommand } from "./dd-command.js";

export const DDRegisterCommand = (program: Command, ddCmd: DDCommand) => {
    const cmd = new Command(ddCmd.name).description(ddCmd.desc);

    const config = ddCmd.configure();

    if (config.arguments) {
        config.arguments?.forEach((arg) => {
            cmd.argument(
                arg.required ? `<${arg.name}>` : `[${arg.name}]`
            );
        });

    }

    if (config.options) {
        config.options.forEach(opt => {
            if (opt.required) {
                cmd.requiredOption(`${opt.flags}`, `${opt.description}`, `${opt.defaultValue}`);
                return;
            }
            cmd.option(`${opt.flags}`, `${opt.description}`, `${opt.defaultValue}`);
        });
    }

    cmd.action((...params) => {
        const args = params.slice(0, -1);
        const options = params[params.length - 1];

        const argNames = config.arguments?.map((a) => a.name) || [];

        const argsObj = Object.fromEntries(
            argNames.map((name, i) => [name, args[i]])
        );
        return ddCmd.execute(argsObj, options);
    });
    program.addCommand(cmd);
}