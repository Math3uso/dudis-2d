import { DDCommand } from "@/core/dd-command.js";

interface INewProject {
    name: string;
    dir: string;
}

export class NewProject extends DDCommand<INewProject> {
    name: string = "new";
    desc: string = "cria um novo projeto dudis";
    configure() {
        return {
            options: [
                {
                    flags: "-n, --name <nome do projeto>",
                    description: "",
                    required: true
                },
                {
                    flags: "-d, --dir <diretorio>",
                    description: "diretorio do projeto. (por padrão diretorio atual)"
                }
            ]
        }
    }
    execute(args: Record<string, string>, options: INewProject): Promise<void> | void {
        console.log(options.name);
        return;
    }

}