const os = require("os");
const { exec } = require("child_process");
const path = require("path");

const colors = {
    reset: "\x1b[0m",
    cyan: "\x1b[36m",
    green: "\x1b[32m",
    yellow: "\x1b[33m",
    magenta: "\x1b[35m",
    blue: "\x1b[34m"
};


function run(cmd, opts = {}) {
    return new Promise((resolve, reject) => {
        exec(cmd, opts, (err, stdout, stderr) => {
            if (err) return reject(err);
            resolve(stdout.trim());
        });
    });
}

async function setEnv(name, value) {
    console.log("checando sistema");
    const plataform = os.platform();

    console.log("plataforma:", plataform);

    if (plataform == "win32") {
        // Windows
        await run(`setx ${name} "${value}"`);
    }

    // Linux / macOS
    const shellFile = process.env.SHELL.includes("zsh") ? "~/.zshrc" : "~/.bashrc";
    await run(`echo "export ${name}=${value}" >> ${shellFile}`);
}

async function setup() {

    console.log(`${colors.cyan}🔧 Iniciando setup...${colors.reset}`);
    //

    console.log(`${colors.yellow}📦 Criando variáveis de ambiente...${colors.reset}`);

    const dudisPath = path.join(process.cwd(), "..", "dudis-2d");
    setEnv("DUDIS2D_PATH", dudisPath);

    console.log(`${colors.green}✔ Variável DUDIS2D_PATH adicionada:${colors.reset}`, dudisPath);

    console.log(`${colors.yellow}⬇️  Instalando dependências...${colors.reset}`);

    await run("npm install");

    console.log(`${colors.green}✔ Dependências instaladas!${colors.reset}`);

    console.log(`${colors.yellow}🔗 Criando link global...${colors.reset}`);
    await run("npm link");
    console.log(`${colors.green}✔ Link global criado!${colors.reset}`);


    console.log(`${colors.yellow}⚙️  Compilando engine...${colors.reset}`);
    await run("cmake -S . -B build && cmake --build build", { cwd: dudisPath });
    console.log(`${colors.green}✔ Compilação concluída!${colors.reset}`);

    console.log(`${colors.magenta}🎉 Configuração completa!${colors.reset}`);

}

setup();